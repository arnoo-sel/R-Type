#ifndef IFILE
# define IFILE

#include <string>
#include "filesystem/fileException.hpp"

using std::string;

class IFile
{
public:
	virtual ~IFile() {};

    virtual void    open(const string &path) = 0;
	virtual void    close() = 0;
	virtual string  read(int len) = 0;
	string           getLine()
	{
        string       v, tmp;

        while ((tmp = read(1)) != "\n" && tmp != "")
            v += tmp;
        return (v);
    }
	virtual int     write(const string &buff) = 0;
};

#ifdef WIN32
  #include "filesystem/fileWindows.hpp"
#else
  #include "filesystem/fileUnix.hpp"
#endif

#endif //IFILE
