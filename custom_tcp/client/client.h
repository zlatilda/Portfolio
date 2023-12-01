#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <features.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <netinet/in.h>
#include <strings.h>
#include <cstring>
#include <arpa/inet.h>
#include <iostream>

#ifndef CLIENT_H
#define CLIENT_H


class client
{
    public:
        client() = default;
        virtual ~client();
        int CreateRawSocket(int);
        int BindRawSocketToInterface(char*, int, int);
        void PrintInHex(unsigned char*, int, char*);
        void ParseEthernetHeader(unsigned char*, int);
        void ParseIpHeader(unsigned char*, int);
        void ParseTcpHeader(unsigned char*, int);
        int IsIpAndTcpPacket(unsigned char*, int);
        int ParseData(unsigned char*, int);
        void Receive(char**);

        void print();

    private:
        unsigned char* packet;
        int packet_len;
        unsigned char* dst_mac;
        unsigned char* src_mac;
        unsigned char* protocol;
        uint16_t src_port;
        uint16_t dst_port;
        unsigned char* data;
        int data_len;
        struct iphdr* ip_header;
};

#endif // CLIENT_H
