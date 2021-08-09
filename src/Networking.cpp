#include "Networking.h"

int Networking::initNetworking()
{
#ifdef _WIN32
    WSAData wsadata;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsadata);
    if (iResult != 0)
    {
        std::cerr << "WSAStartup failed: " << iResult;
        return 1;
    }
    return 0;
#else

#endif
}

int Networking::cleanup()
{
#ifdef _WIN32
    WSACleanup();
    return 0;
#else
#endif
}

Networking::TCPSocket::TCPSocket() : sock(INVALID_SOCKET), info(nullptr)
{
}

#ifdef _WIN32
Networking::TCPSocket::TCPSocket(SOCKET s) : sock(s), info(nullptr)
{
}
#endif

Networking::TCPSocket::~TCPSocket()
{
#ifdef _WIN32
    freeaddrinfo(info);
#endif
}

int Networking::TCPSocket::createSocket(char *ip, char *port)
{
#ifdef _WIN32
    addrinfo hints;
    int iResult;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    if (!ip) //SERVER SOCKET
    {
        hints.ai_flags = AI_PASSIVE;
    }

    iResult = getaddrinfo(ip, port, &hints, &info);
    if (iResult != 0)
    {
        std::cerr << "getaddrinfo failed: " << iResult << std::endl;
        return 1;
    }

    sock = socket(info->ai_family, info->ai_socktype, info->ai_protocol);
    if (sock == INVALID_SOCKET)
    {
        std::cerr << "Error at socket(): " << WSAGetLastError() << std::endl;
        return 1;
    }
    return 0;
#else
//TO DO
#endif
}

int Networking::TCPSocket::bind()
{
#ifdef _WIN32
    int iResult = ::bind(sock, info->ai_addr, (int)info->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        std::cerr << "bind failed with error: %d\n"
                  << WSAGetLastError() << std::endl;
        return 1;
    }
    return 0;
#else
#endif
}

int Networking::TCPSocket::listen(int backlog = SOMAXCONN)
{
#ifdef _WIN32
    int iResult = ::listen(sock, backlog);
    if (iResult == SOCKET_ERROR)
    {
        std::cerr << "Listen failed with error: " << WSAGetLastError() << std::endl;
        return 1;
    }
    return 0;
#else
#endif
}

Networking::TCPSocket Networking::TCPSocket::accept()
{
#ifdef _WIN32
    SOCKET client = ::accept(sock, NULL, NULL);
    if (client == INVALID_SOCKET)
    {
        std::cout << "Accept failed: " << WSAGetLastError() << std::endl;
        return TCPSocket(INVALID_SOCKET);
    }
    return TCPSocket(client);
#else
#endif
}

int Networking::TCPSocket::recv(char *recvbuf, int recvbuflen)
{
#ifdef _WIN32
    int iResult = ::recv(sock, recvbuf, recvbuflen, 0);
    if (iResult < 0)
    {
        std::cerr << "recv failed: " << WSAGetLastError() << std::endl;
    }
    return iResult;
#else
#endif
}

int Networking::TCPSocket::send(char *sendbuf, int sendbuflen)
{
#ifdef _WIN32
    int iResult = ::send(sock, sendbuf, sendbuflen, 0);
    if (iResult == SOCKET_ERROR)
    {
        std::cerr << "send failed: " << WSAGetLastError() << std::endl;
    }
    return iResult;
#else
#endif
}

int Networking::TCPSocket::connect()
{
#ifdef _WIN32
    int iResult = ::connect(sock, info->ai_addr, info->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        closesocket(sock);
        sock = INVALID_SOCKET;
        freeaddrinfo(info);
    }
    if (sock == INVALID_SOCKET)
    {
        std::cerr << "Error, cannot connect to server: " << std::endl;
        return 1;
    }

    return 0;
#else
#endif
}

int Networking::TCPSocket::close()
{
#ifdef _WIN32
    int iResult = closesocket(sock);
    if (iResult != 0)
    {
        std::cerr << "Error on close: " << WSAGetLastError() << std::endl;
        return 1;
    }
    return 0;
#else
#endif
}