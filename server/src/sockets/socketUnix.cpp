#include "sockets/socketUnix.hpp"


SocketUnix::SocketUnix(const std::string ip, int port, const std::string mode) : hSocket(0)
{
	hMode = mode;
    hSin.sin_addr.s_addr	= inet_addr(ip.c_str());
    hSin.sin_family		= AF_INET;
    hSin.sin_port		= htons(port);
    if ((hSocket = socket(AF_INET, (mode == "UDP" ? (SOCK_DGRAM) : (SOCK_STREAM)), 0)) == -1)
        throw new SocketException("Could not create client socket");
    if (mode != "UDP")
        this->connect();
}


SocketUnix::SocketUnix(int port, int queue, const std::string mode)
{

	hMode = mode;
    hSin.sin_addr.s_addr	= htonl(INADDR_ANY);
    hSin.sin_family		= AF_INET;
    hSin.sin_port		= htons(port);
    if ((hSocket = socket(AF_INET, (mode == "UDP" ? (SOCK_DGRAM) : (SOCK_STREAM)), 0)) == -1)
        throw new SocketException("Could not create server socket");
    this->bind();
    if (mode != "UDP")
        this->listen(queue);
}

SocketUnix::SocketUnix(int sock, struct sockaddr_in sin)
{
	hSocket = sock;
    hSin = sin;
}

void SocketUnix::bind()
{
    if (::bind(this->hSocket, (struct sockaddr *)&(this->hSin), sizeof(this->hSin)) != 0)
        throw new SocketException("Can't bind socket");
}

void SocketUnix::listen(int queue)
{
    if (::listen(this->hSocket, queue) != 0)
        throw new SocketException("Could not listen to socket");
}

void SocketUnix::connect()
{
    if (::connect(this->hSocket, (struct sockaddr *)&(this->hSin), sizeof(this->hSin)) != 0)
        throw new SocketException("Could not connect through socket");
}

ISocket* SocketUnix::accept()
{
    ISocket* clientSocket;
    int newSock;
    struct sockaddr_in csin;
    unsigned int csinSize = sizeof(csin);

    if ((newSock = ::accept(this->hSocket, (struct sockaddr *)&csin, &csinSize)) == -1)
        throw new SocketException("Accept failed");
    clientSocket = new SocketUnix(newSock, csin);
    return clientSocket;
}

void	SocketUnix::send(const std::string& buf, std::string ip, int port)
{
    if (this->hMode == "UDP")
    {
        struct sockaddr_in toSin;
        toSin.sin_addr.s_addr = inet_addr(ip.c_str());
        toSin.sin_family = AF_INET;
        toSin.sin_port	= htons(port);
        if (::sendto(this->hSocket, buf.c_str(), buf.size(), 0, (struct sockaddr *)&toSin, sizeof(toSin)) == -1)
            throw new SocketException("Could not write to adress.");
    }
    else
    {
        if (::send(this->hSocket, buf.c_str(), buf.size(), 0) == -1)
            throw new SocketException("Could not write to socket.");
    }
}

std::string SocketUnix::recv(int len, std::string* ip)
{
	char *buf = new char[len];
    int   size;

    if (this->hMode == "UDP")
    {
        struct sockaddr_in fromSin;
        unsigned int fromLen = sizeof(fromSin);
        if ((size = recvfrom(this->hSocket, buf, len, 0, (struct sockaddr *)&fromSin, &fromLen)) == -1)
            throw new SocketException("Could not read on UDP socket.");
		if (ip) // Give the sender ip back to the caller
			(*ip) = inet_ntoa(fromSin.sin_addr);
    }
    else
    {
        if ((size = read((this->hSocket), buf, len)) == -1)
            throw new SocketException("Could not read on TCP socket.");
    }
    std::string res(buf, size);
    return (res);
}

SocketUnix::~SocketUnix()
{
    if (close(this->hSocket))
        throw new SocketException("Can't close socket");
}
