#ifndef FILEWINDOWS
# define FILEWINDOWS

#include <Windows.h>
#include <iostream>
#include <algorithm>
#include "filesystem/iFile.hpp"

class FileWindows : public IFile
{
public:
    FileWindows();
    FileWindows(const string&);
    void    open(const string &path);
	void    close();
	string  read(int len);
	int     write(const string &buff);

private:
    HANDLE  hFile;
    bool    opened;
};

typedef FileWindows AbstractFile;

#endif //FILEWINDOWS
