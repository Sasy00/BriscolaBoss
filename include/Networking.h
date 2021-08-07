#ifndef NETWORKING_H
#define NETWORKING_H

#include <iostream>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
//#include <socket.h>
#endif
namespace Networking
{
    class TCPSocket
    {
    public:
        /**
         * @brief Constructor of class TCPSocket
         * @param ip: ip address of server to connect to. If this socket is used as server socket then ip should be nullptr
         * @param port: port of the server.
         */
        TCPSocket(char *ip, char *port);
        int bind();
        int listen();
        TCPSocket accept();
        int recv(char *recvbuf, int recvbuflen);
        int send(char *recvbuf, int recvbuflen);
        int connect();
        int close();
        int shutdown(int how);

        inline static const char *DEFAULT_PORT = "8080";
        static const int DEFAULT_BUFLEN = 512;

    private:
#ifdef _WIN32
        SOCKET sock;
        addrinfo *info;
#else
        int fd;
#endif
    };
    int initNetworking();
    int cleanup();
};

#endif