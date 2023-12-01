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

#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

class server_socket
{
private:
    const char *ip;
    int port;
    int sockfd;
    int new_sock;
    struct sockaddr_in server_addr;
    socklen_t addr_size;  // client

    void write_file(int, const char*);
public:
    server_socket();
    server_socket(int);
    void binding();
    void listening(int);
    void accept_connection();
    void send_text(const char*); // ??
    void send_file(const char*);
    void receive_text();
    void receive_file(const char*);
    ~server_socket();
};

#endif
