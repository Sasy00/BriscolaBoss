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
        TCPSocket();
        ~TCPSocket();
        /**
         * @brief initialize socket
         * @param ip: ip address of server to connect to. If this socket is used as server socket then ip should be nullptr
         * @param port: port of the server.
         * @returns 0 if no errors, 1 if errors. Check cerr for error text
         */
        int createSocket(char *ip, char *port);

        /**
         * @brief binds the socket
         * @returns 0 if no errors, 1 if errors. Check cerr for error text.
         */
        int bind();
        /**
         * @brief Listens on the socket
         * @param backlog: max connections in a single time.
         * @returns 0 if no error, 1 if errors. Check cerr for error text.
         */
        int listen(int backlog);
        /**
         * @brief accepts incoming connession requests.
         * @returns the client socket if no errors, an invalid socket if errors. use .isInvalid() to check if socket is invalid. Also check cerr for error text.
         */
        TCPSocket accept();

        /**
         * @brief waits for incoming packet from this socket.
         * @param recvbuf: buffer where the packet will be stored.
         * @param recvbuflen: size of recvbuf.
         * @returns 0 if socket host closed the connection, <0 if error occurred (check cerr for error text), else returns the size of the packet in bytes.
         */
        int recv(char *recvbuf, int recvbuflen);

        /**
         * 
         */
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
        TCPSocket(SOCKET s);
#else
        int fd;
#endif
    };

    /**
     * @brief initializes Networking library.
     * @returns 0 if no errors, 1 if errors. Check cerr for error text.
     */
    int initNetworking();
    /**
     * deinitializes Networking library
     */
    int cleanup();
};

#endif