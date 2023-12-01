#include "client.h"

client::~client()
{
    free(packet);
    free(dst_mac);
    free(src_mac);
    free(protocol);
    free(data);
}

int client::CreateRawSocket(int protocol_to_sniff)
{
    int rawsock;

    if((rawsock = socket(PF_PACKET, SOCK_RAW, htons(protocol_to_sniff))) == -1)
    {
        perror("Error creating raw socket: ");
        exit(-1);
    }

    return rawsock;
}

int client::BindRawSocketToInterface(char* device, int rawsock, int protocol)
{
    struct sockaddr_ll sll;
    struct ifreq ifr;

    bzero(&sll, sizeof(sll));
    bzero(&ifr, sizeof(ifr));

    strncpy((char*)ifr.ifr_name, device, IFNAMSIZ);
    if((ioctl(rawsock, SIOCGIFINDEX, &ifr)) == -1)
    {
        perror("Error getting interface index!\n");
        exit(-1);
    }

    sll.sll_family = AF_PACKET;
    sll.sll_ifindex = ifr.ifr_ifindex;
    sll.sll_protocol = htons(protocol);

    if((bind(rawsock, (struct sockaddr*)&sll, sizeof(sll))) == -1)
    {
        perror("Error binding raw socket to the interface\n");
        exit(-1);
    }

    return 1;
}

void client::PrintInHex(unsigned char* p, int len, char* mesg = "")
{
    printf(mesg);
    char buffer[20];
    while(len--)
    {
        printf("%.2X ", *p);
        sprintf(buffer, "%x", *p);
        p++;
    }

}

void client::ParseEthernetHeader(unsigned char* packet, int len)
{
    struct ethhdr* ethernet_header;

    if(len > sizeof(struct ethhdr))
    {
        ethernet_header = (struct ethhdr*)packet;

        dst_mac = ethernet_header->h_dest;
        //printf("\n");
        //PrintInHex(ethernet_header->h_dest, 6, "Destinstion MAC: ");
        //printf("\n");

        src_mac = ethernet_header->h_source;
        //PrintInHex(ethernet_header->h_source, 6, "Source MAC: ");
        //printf("\n");

        protocol = (unsigned char*)&ethernet_header->h_proto;
        //PrintInHex((unsigned char*)&ethernet_header->h_proto, 2, "Protocol: ");
        //printf("\n");
    }
    else
    {
        printf("Packet size too small \n");
    }
}

void client::ParseIpHeader(unsigned char* packet, int len)
{
    struct ethhdr* ethernet_header;
    struct iphdr* ip_header;

    ethernet_header = (struct ethhdr*)packet;

    if(ntohs(ethernet_header->h_proto) == ETH_P_IP)
    {
        if(len >= (sizeof(struct ethhdr) + sizeof(struct iphdr)))
        {
            ip_header = (struct iphdr*)(packet + sizeof(struct ethhdr));

            //printf("Dest IP address: %s\n", inet_ntoa(ip_header->daddr));
            //printf("Source IP address: %s\n", inet_ntoa(ip_header->saddr));
            this->ip_header = ip_header;

            //std::cout << "IP address: " << inet_addr("192.168.233.128") << std::endl;
        }
        else
        {
            printf("IP packet does not have full header \n");
        }
    }
    else
    {
        printf("Not at IP packet \n");
    }
}

void client::ParseTcpHeader(unsigned char* packet, int len)
{
    struct ethhdr* ethernet_header;
    struct iphdr* ip_header;
    struct tcphdr* tcp_header;

    if(len >= (sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct tcphdr)))
    {
        ethernet_header = (struct ethhdr*)packet;
        if(ntohs(ethernet_header->h_proto) == ETH_P_IP)
        {
            ip_header = (struct iphdr*)(packet + sizeof(struct ethhdr));

            if(ip_header->protocol == IPPROTO_TCP)
            {
                tcp_header = (struct tcphdr*)(packet + sizeof(struct ethhdr) + ip_header->ihl*4);

                src_port = ntohs(tcp_header->source);
                dst_port = ntohs(tcp_header->dest);
                //printf("Source Port: %d\n", ntohs(tcp_header->source));
                //printf("Dest Port: %d\n", ntohs(tcp_header->dest));
            }
            else
            {
                printf("Not a TCP packet \n");
            }
        }
        else
        {
            printf("Not an IP packet \n");
        }
    }
    else
    {
        printf("TCP header is not present \n");
    }
}

int client::IsIpAndTcpPacket(unsigned char* packet, int len)
{
    struct ethhdr* ethernet_header;
    struct iphdr*  ip_header;

    ethernet_header = (struct ethhdr*)packet;

    if(ntohs(ethernet_header->h_proto) == ETH_P_IP)
    {
        ip_header = (struct iphdr*)(packet + sizeof(struct ethhdr));

        if(ip_header->protocol == IPPROTO_TCP)
            return 1;
        else
            return -1;
    }
    else
        return -1;
}

int client::ParseData(unsigned char* packet, int len)
{
    struct ethhdr* ethernet_header;
    struct iphdr* ip_header;
    struct tcphdr* tcp_header;
    unsigned char* data;
    int data_len;

    if(len > (sizeof(struct ethhdr) + sizeof(struct iphdr) + sizeof(struct tcphdr)))
    {
        ip_header = (struct iphdr*)(packet + sizeof(struct ethhdr));
        data = (packet + sizeof(struct ethhdr) + ip_header->ihl*4 + sizeof(struct tcphdr));
        data_len = ntohs(ip_header->tot_len) - ip_header->ihl*4 - sizeof(struct tcphdr);

        if(data_len)
        {
            //printf("Data Len: %d\n", data_len);
            //PrintInHex(data, data_len, "Data: ");
            //printf("\n\n");

            this->data = data;
            this->data_len = data_len;

            return 1;
        }
        else
        {
            printf("No data in the packet \n");
            return 0;
        }
    }
    else
    {
        printf("No data in the packet \n");
        return 0;
    }
}

void client::Receive(char** argv)
{
    int raw;
    unsigned char packet_buffer[2048];
    int len;
    int packets_to_sniff;
    struct sockaddr_ll packet_info;
    int packet_info_size = sizeof(packet_info);

    raw = CreateRawSocket(ETH_P_IP);

    BindRawSocketToInterface(argv[1], raw, ETH_P_IP);

    packets_to_sniff = 1;

    while(true)
    {
        if((len = recvfrom(raw, packet_buffer, 2048, 0, (struct sockaddr*)&packet_info, (socklen_t*)&packet_info_size)) == -1)
        {
            perror("Recv from returned -1:");
            exit(-1);
        }
        else
        {
            //PrintInHex(packet_buffer, len);
            this->packet = packet_buffer;
            this->packet_len = len;

            ParseEthernetHeader(packet_buffer, len);

            ParseIpHeader(packet_buffer, len);

            if(this->ip_header->saddr == inet_addr("192.168.233.128"))
            {

                ParseTcpHeader(packet_buffer, len);

                if((this->src_port == 80) && (this->dst_port == 100))
                {
                    if(IsIpAndTcpPacket(packet_buffer, len))
                    {
                        if(!ParseData(packet_buffer, len))
                            packets_to_sniff++;

                        print();
                    }
                }

            }
        }
    }
}

void client::print()
{
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

    printf("\n");
    PrintInHex(this->packet, this->packet_len, "Packet: ");
    printf("\n");

    printf("\n");
    PrintInHex(this->dst_mac, 6, "Destinstion MAC: ");
    printf("\n");

    PrintInHex(this->src_mac, 6, "Source MAC: ");
    printf("\n");

    PrintInHex(this->protocol, 2, "Protocol: ");
    printf("\n");

    std::cout << "Source IP address: " << this->ip_header->saddr << std::endl;

    printf("Source Port: %d\n", this->src_port);
    printf("Dest Port: %d\n", this->dst_port);

    printf("Data Len: %d\n", this->data_len);
    PrintInHex(this->data, this->data_len, "Data: ");
    printf("\n\n");
}
