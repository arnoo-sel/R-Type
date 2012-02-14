#include "library/libraryException.hpp"
#include <cstring>

LibraryException::LibraryException(string const& error, string const& libraryname) : msg(error), path(libraryname)
{
    whatMsg = "LibraryError: ";
    if (path != "")
        whatMsg += path + ": ";
    whatMsg += msg;
}

LibraryException::~LibraryException() throw()
{}

const char* LibraryException::what() const throw()
{
    return (whatMsg.c_str());
}
