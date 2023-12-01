#include "server.h"

int server::CreateRawSocket(int protocol)
{
    int rawsock;

    if((rawsock = socket(PF_PACKET, SOCK_RAW, htons(protocol))) == -1)
    {
        perror("Error creating raw socket: ");
        exit(-1);
    }

    return rawsock;
}

int server::BindRawSocketToInterface(char* device, int rawsock, int protocol)
{
    struct sockaddr_ll sll;
    struct ifreq ifr;

    bzero(&sll, sizeof(sll));
    bzero(&ifr, sizeof(ifr));

    strncpy((char*)ifr.ifr_name, device, IFNAMSIZ);

    if((ioctl(rawsock, SIOCGIFINDEX, &ifr)) == -1)
    {
        perror("Error getting interface index \n ");
        exit(-1);
    }

    sll.sll_family = AF_PACKET;
    sll.sll_ifindex = ifr.ifr_ifindex;
    sll.sll_protocol = htons(protocol);

    if((bind(rawsock, (struct sockaddr*)&sll, sizeof(sll))) == -1)
    {
        perror("Error binding raw socket to interface \n ");
        exit(-1);
    }
    return 1;
}

int server::SendRawPakcet(int rawsock, unsigned char* pkt, int pkt_len)
{
    int sent = 0;
    printf("Packet len: %d\n", pkt_len);

    if((sent = write(rawsock, pkt, pkt_len)) != pkt_len)
    {
        printf("Could only send %d bytes of packets of length %d\n", sent, pkt_len);
        return 0;
    }

    return 1;
}

struct ethhdr* server::CreateEthernetHeader(char* src_mac, char* dst_mac, int protocol)
{
    struct ethhdr* ethernet_header;

    ethernet_header = (struct ethhdr*)malloc(sizeof(struct ethhdr));

    memcpy(ethernet_header->h_source, (void*)ether_aton(src_mac), 6);

    memcpy(ethernet_header->h_dest, (void*)ether_aton(dst_mac), 6);

    ethernet_header->h_proto = htons(protocol);

    return ethernet_header;
}

unsigned short server::ComputeIpChecksum(unsigned char* header, int len)
{
    long sum = 0;
    unsigned short* ip_header = (unsigned short*)header;

    while(len > 1)
    {
        sum += *ip_header++;
        if(sum & 0x80000000)
            sum = (sum & 0xFFFF) + (sum >> 16);
        len -= 2;
    }

    if(len)
        sum += (unsigned short) *((unsigned char*)ip_header);

    while(sum >> 16)
        sum = (sum & 0xFFFF) + (sum >> 16);

    return ~sum;
}

struct iphdr* server::CreateIPHeader()
{
    struct iphdr* ip_header;

    ip_header = (struct iphdr*)malloc(sizeof(struct iphdr));

    ip_header->version = 4;
    ip_header->ihl = (sizeof(struct iphdr))/4;
    ip_header->tos = 0;
    ip_header->tot_len = htons(sizeof(struct iphdr) + sizeof(struct tcphdr) + DATA_SIZE);
    ip_header->frag_off = 0;
    ip_header->ttl = 111;
    ip_header->protocol = IPPROTO_TCP;
    ip_header->check = 0;
    ip_header->saddr = inet_addr(SRC_IP);
    ip_header->daddr = inet_addr(DST_IP);

    ip_header->check = ComputeIpChecksum((unsigned char*)ip_header, ip_header->ihl*4);

    return ip_header;
}

struct tcphdr* server::CreateTcpHeader()
{
    struct tcphdr* tcp_header;

    tcp_header = (struct tcphdr*)malloc(sizeof(struct tcphdr));

    tcp_header->source = htons(SRC_PORT);
    tcp_header->dest = htons(DST_PORT);
    tcp_header->seq = htonl(111);
    tcp_header->ack_seq = htonl(111);
    tcp_header->res1 = 0;
    tcp_header->doff = (sizeof(struct tcphdr))/4;
    tcp_header->syn = 1;
    tcp_header->window = htons(100);
    tcp_header->check = 0;
    tcp_header->urg_ptr = 0;

    return tcp_header;
}

void server::CreatePseudoHeaderAndComputeTcpChecksum(struct tcphdr* tcp_header, struct iphdr* ip_header, unsigned char* data)
{
    int segment_len = ntohs(ip_header->tot_len) - ip_header->ihl*4;
    int header_len = sizeof(PseudoHeader) + segment_len;
    unsigned char* hdr = (unsigned char*)malloc(header_len);

    PseudoHeader* pseudo_header = (PseudoHeader*)hdr;

    pseudo_header->source_ip = ip_header->saddr;
    pseudo_header->dest_ip = ip_header->daddr;
    pseudo_header->reserved = 0;

    memcpy((hdr + sizeof(PseudoHeader)), (void*)tcp_header, tcp_header->doff*4);

    tcp_header->check = ComputeIpChecksum(hdr, header_len);

    free(hdr);
}

unsigned char* server::CreateData(int len)
{
    unsigned char* data = (unsigned char*)malloc(len);
    struct timeval tv;
    struct timezone tz;
    int counter = len;

    gettimeofday(&tv, &tz);
    srand(tv.tv_sec);

    for(counter = 0; counter < len; counter++)
        data[counter] = 255.0 * rand()/(RAND_MAX + 1.0);

    return data;
}

void server::Send(char** argv)
{
    int raw;
    unsigned char* packet;
    struct ethhdr* ethernet_header;
    struct iphdr* ip_header;
    struct tcphdr* tcp_header;
    unsigned char* data;
    int pkt_len;

    raw = CreateRawSocket(ETH_P_ALL);
    BindRawSocketToInterface(argv[1], raw, ETH_P_ALL);
    ethernet_header = CreateEthernetHeader(SRC_ETHER_ADDR, DST_ETHER_ADDR, ETHERTYPE_IP);
    ip_header = CreateIPHeader();
    tcp_header = CreateTcpHeader();
    data = CreateData(DATA_SIZE);
    CreatePseudoHeaderAndComputeTcpChecksum(tcp_header, (struct iphdr*)ip_header, data);
    pkt_len = sizeof(struct ethhdr) + ntohs(ip_header->tot_len);
    packet = (unsigned char*)malloc(pkt_len);

    memcpy(packet, ethernet_header, sizeof(struct ethhdr));
    memcpy((packet + sizeof(struct ethhdr)), ip_header, ip_header->ihl*4);
    memcpy((packet + sizeof(struct ethhdr) + ip_header->ihl*4), tcp_header, tcp_header->doff*4);
    memcpy((packet + sizeof(struct ethhdr) + ip_header->ihl*4 + tcp_header->doff*4), data, DATA_SIZE);

    if(!SendRawPakcet(raw, packet, pkt_len))
    {
        perror("Error sending packet");
    }
    else
        printf("Packet sent successfully\n");

    free(ethernet_header);
    free(ip_header);
    free(tcp_header);
    free(data);
    free(packet);
    close(raw);
}
