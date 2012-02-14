#include "filesystem/fileException.hpp"
#include <cstring>

FileException::FileException(string const& error, string const& filename) : msg(error), path(filename)
{}

FileException::~FileException() throw()
{}

const char* FileException::what() const throw()
{
    string out = "FileError: ";
    if (path != "")
        out += path + ": ";
    out += msg;
    return (strdup(out.c_str()));
}
