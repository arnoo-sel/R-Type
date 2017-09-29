#ifndef SOCKETEXCEPTION
# define SOCKETEXCEPTION

#include <exception>
#include <string>

using std::string;

class SocketException : public std::exception
{
public:
    SocketException(string const& error) throw();
    ~SocketException() throw();
    const char* what() const throw();

private:
    const string    msg;
};

#endif //SOCKETEXCEPTION

