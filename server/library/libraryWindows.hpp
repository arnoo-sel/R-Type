#ifndef FILEWINDOWS
# define FILEWINDOWS

#include <Windows.h>
#include <iostream>
#include "library/iLibrary.hpp"

class LibraryWindows : public ILibrary
{
public:
    LibraryWindows(const string& libName);
    ~LibraryWindows();
    voidFuncPtr      getVoidSym(const string &name);

private:
    HMODULE  hLibrary;
};

typedef LibraryWindows AbstractLibrary;

#endif //FILEWINDOWS
