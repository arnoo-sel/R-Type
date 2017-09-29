#ifndef SOCKETUNIX
# define SOCKETUNIX

#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include "sockets/iSocket.hpp"
#include "netinet/in.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
       
class SocketUnix : public ISocket
{
public:
    SocketUnix(const std::string, int, const std::string mode = "UDP");
    SocketUnix(int, int = 42, const std::string mode = "UDP");
    SocketUnix(int, struct sockaddr_in);
    virtual ~SocketUnix();

    void connect();
    ISocket* accept();
    void send(const std::string&, std::string ip = "", int port = 0);
	std::string recv(int, std::string* ip = NULL);

private:
    void bind();
    void listen(int);

    int                 hSocket;
    struct sockaddr_in  hSin;
    std::string			hMode;
};

#ifndef WIN32
typedef SocketUnix AbstractSocket;
#endif

#endif //SOCKETUNIX
