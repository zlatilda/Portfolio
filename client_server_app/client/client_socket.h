#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32
    #include <winsock2.h>
    #include <Windows.h>
    typedef int socklen_t;
    #define bzero(b,len) (memset((b), '\0', (len)), (void) 0)

#elif __linux__
    #include <arpa/inet.h>
#endif

#define SIZE 1024

#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

class client_socket
{
private:
    const char *ip;
    int port;
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t addr_size;

    void write_file(int, const char*);
public:
    client_socket();
    client_socket(int);
    void connect_to_server();
    void send_text(const char*);
    void send_file(const char*);
    const char* receive_text();
    void receive_file(const char*);
    ~client_socket();
};

#endif
