#include "sockets/socketException.hpp"
#include <cstring>

SocketException::SocketException(string const& error) throw() : msg(error)
{}

SocketException::~SocketException() throw()
{}

const char* SocketException::what() const throw()
{
    string out = "SocketError: ";
    out += msg;
    return (strdup(out.c_str()));
}
