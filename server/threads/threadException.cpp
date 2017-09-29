#include "threads/threadException.hpp"
#include <cstring>

ThreadException::ThreadException(string const& error) : msg(error)
{}

ThreadException::~ThreadException() throw()
{}

const char* ThreadException::what() const throw()
{
    string out = "ThreadError: ";
    out += msg;
    return (strdup(out.c_str()));
}
