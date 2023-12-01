#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <features.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <netinet/ether.h>
#include <stdlib.h>

#define DATA_SIZE 100
#define SRC_ETHER_ADDR "aa:aa:aa:aa:aa:aa"
#define DST_ETHER_ADDR "bb:bb:bb:bb:bb:bb"
#define SRC_IP "192.168.233.128"
#define DST_IP "192.168.233.129"
#define SRC_PORT 80
#define DST_PORT 100

#ifndef SERVER_H
#define SERVER_H


class server
{
    public:
        server() = default;
        virtual ~server() = default;
        int CreateRawSocket(int);
        int BindRawSocketToInterface(char*, int, int);
        int SendRawPakcet(int, unsigned char*, int);
        struct ethhdr* CreateEthernetHeader(char*, char*, int);
        unsigned short ComputeIpChecksum(unsigned char*, int);
        struct iphdr* CreateIPHeader();
        struct tcphdr* CreateTcpHeader();
        void CreatePseudoHeaderAndComputeTcpChecksum(struct tcphdr*, struct iphdr*, unsigned char*);
        unsigned char* CreateData(int);
        void Send(char**);

    private:
        typedef struct PseudoHeader
        {
            unsigned long int source_ip;
            unsigned long int dest_ip;
            unsigned char reserved;
            unsigned char protocol;
            unsigned short int top_length;
        }PseudoHeader;
};

#endif // SERVER_H
