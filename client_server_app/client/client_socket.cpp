
#include "client_socket.h"

client_socket::client_socket()
{
    #ifdef _WIN32
        WSADATA Data;
        WSAStartup(MAKEWORD(2, 2), &Data);
    #endif

    this->ip = "127.0.0.1";
    this->port = 7500;
    this->sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(sockfd < 0)
    {
        perror("[-]Error in socket");
        exit(1);
    }

    printf("[+]Client socket created successfully.\n");
}

client_socket::client_socket(int port)
{
     #ifdef _WIN32
        WSADATA Data;
        WSAStartup(MAKEWORD(2, 2), &Data);
    #endif

    this->ip = "127.0.0.1";
    this->port = port;
    this->sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd < 0)
    {
        perror("[-]Error in socket");
        exit(1);
    }

    printf("[+]Client socket created successfully.\n");
}

client_socket::~client_socket()
{
    close(sockfd);

    #ifdef _WIN32
        WSACleanup();
    #endif
}

void client_socket::connect_to_server()
{
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    int is_connected = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(is_connected == -1)
    {
        perror("No connection");
        exit(1);
    }
     printf("[+]Connected to Server.\n");
}

void client_socket::send_file(const char* filename)
{
    FILE* fp;
    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        perror("[-]Error in reading file.");
        exit(1);
    }

    char data[SIZE] = {0};

    while(fgets(data, SIZE, fp) != NULL)
    {
        if (send(sockfd, data, sizeof(data), 0) == -1)
        {
            perror("[-]Error in sending file.");
            exit(1);
        }
        bzero(data, SIZE);
    }

    printf("[+]File sent successfully.\n");
}

void client_socket::send_text(const char* message)
{
    char buffer[SIZE];
    strcpy(buffer, message);

    int is_sent = send(sockfd, buffer, strlen(buffer), 0);

    if (is_sent < 0)
    {
        perror("[-]Error in sending a message.");
        exit(1);
    }
}

const char* client_socket::receive_text()
{
    char buffer[SIZE];
    memset(buffer, 0, SIZE);
    int is_received = recv(sockfd, buffer, SIZE, 0);
    if(is_received < 0)
    {
        perror("[-]Error in receiving a message");
        exit(1);
    }
    printf("RECIEVED MESSAGE: %s\n", buffer);

    const char* recieved_text = buffer;

    return recieved_text;
}
