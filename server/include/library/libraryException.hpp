#ifndef LIBRARYEXCEPTION
# define LIBRARYEXCEPTION

#include <exception>
#include <string>

using std::string;

class LibraryException : public std::exception
{
public:
    LibraryException(string const& error, string const& libraryname = "");
    ~LibraryException() throw();
    const char* what() const throw();

private:
    const string    msg, path;
    string			whatMsg;
};

#endif // LIBRARYEXCEPTION

