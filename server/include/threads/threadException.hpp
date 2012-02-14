#ifndef THREADEXCEPTION
# define THREADEXCEPTION

#include <exception>
#include <string>

using std::string;

class ThreadException : public std::exception
{
public:
    ThreadException(string const& error);
    ~ThreadException() throw();
    const char* what() const throw();

private:
    const string    msg;
};

#endif //THREADEXCEPTION

