#include "sockets/socketWindows.hpp"
#include <stdio.h>
#include <unistd.h>

SocketWindows::SocketWindows(const std::string ip, int port, const std::string mode) : hSocket(0)
{
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2,2), &WSAData);

    hMode = mode;
    hSin.sin_addr.s_addr	= inet_addr(ip.c_str());
    hSin.sin_family		= AF_INET;
    hSin.sin_port		= htons(port);
    if ((hSocket = socket(AF_INET, (mode == "UDP" ? (SOCK_DGRAM) : (SOCK_STREAM)), 0)) == INVALID_SOCKET)
        throw new SocketException("Could not create client socket");
    if (mode != "UDP")
        this->connect();
}


SocketWindows::SocketWindows(int port, int queue, const std::string mode)
{
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2,2), &WSAData);

    hMode = mode;
    hSin.sin_addr.s_addr	= htonl(INADDR_ANY);
    hSin.sin_family		= AF_INET;
    hSin.sin_port		= htons(port);
    if ((hSocket = socket(AF_INET, (mode == "UDP" ? (SOCK_DGRAM) : (SOCK_STREAM)), 0)) == INVALID_SOCKET)
        throw new SocketException("Could not create server socket");
    this->bind();
    if (mode != "UDP")
        this->listen(queue);
}

SocketWindows::SocketWindows(SOCKET sock, SOCKADDR_IN sin)
{
    hSocket = sock;
    hSin = sin;
}

void SocketWindows::bind()
{
    if (::bind(this->hSocket, (SOCKADDR *)&(this->hSin), sizeof(this->hSin)) != 0)
        throw new SocketException("Can't bind socket");
}

void SocketWindows::listen(int queue)
{
    if (::listen(this->hSocket, queue) != 0)
        throw new SocketException("Could not listen to socket");
}

void SocketWindows::connect()
{
    if (::connect(this->hSocket, (SOCKADDR *)&(this->hSin), sizeof(this->hSin)) != 0)
        throw new SocketException("Could not connect through socket");
}

ISocket* SocketWindows::accept()
{
    ISocket* clientSocket;
    SOCKET newSock;
    SOCKADDR_IN csin;
    int csinSize;

    if ((newSock = ::accept(this->hSocket, (SOCKADDR *)&csin, &csinSize)) == INVALID_SOCKET)
    {
        perror("toz :");
        throw new SocketException("Accept failed");
    }
    clientSocket = new SocketWindows(newSock, csin);
    return clientSocket;
}

void SocketWindows::send(const std::string& buf, std::string ip, int port)
{
    if (this->hMode == "UDP")
    {
        SOCKADDR_IN toSin;
        toSin.sin_addr.s_addr = inet_addr(ip.c_str());
        toSin.sin_family = AF_INET;
        toSin.sin_port	= htons(port);
        if (::sendto(this->hSocket, buf.c_str(), buf.size(), 0, (SOCKADDR *)&toSin, sizeof(toSin)) == -1)
            throw new SocketException("Could not write to adress.");
    }
    else
    {
        if (::send(this->hSocket, buf.c_str(), buf.size(), 0) == -1)
            throw new SocketException("Could not write to socket.");
    }
}

std::string SocketWindows::recv(int len, string* ip)
{
    char *buf = new char[len];
    int   size;

    if (this->hMode == "UDP")
    {
        SOCKADDR_IN fromSin;
        int fromLen = sizeof(fromSin);
        if ((size = recvfrom(this->hSocket, buf, len, 0, (SOCKADDR *)&fromSin, &fromLen)) == -1)
            throw new SocketException("Could not read on UDP socket.");
        if (ip)
            (*ip) = inet_ntoa(fromSin.sin_addr);
    }
    else
    {
        if ((size = read(this->hSocket, buf, len)) == -1)
            throw new SocketException("Could not read on TCP socket.");
    }
    std::string res(buf, size);
    delete[] buf;
    return (res);
}

SocketWindows::~SocketWindows()
{
    if (::closesocket(this->hSocket))
        throw new SocketException("Can't close socket");
    WSACleanup();
}
