#ifndef FILEEXCEPTION
# define FILEEXCEPTION

#include <exception>
#include <string>

using std::string;

class FileException : public std::exception
{
public:
    FileException(string const& error, string const& filename = "");
    ~FileException() throw();
    const char* what() const throw();

private:
    const string    msg, path;
};

#endif //FILEEXCEPTION

