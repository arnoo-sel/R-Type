#ifndef LIBRARYUNIX
# define LIBRARYUNIX

#include <iostream>
#include <dlfcn.h>
#include "library/iLibrary.hpp"

class LibraryUnix : public ILibrary
{
public:
    LibraryUnix();
    ~LibraryUnix();
    LibraryUnix(const string&);
    voidFuncPtr      getVoidSym(const string &name);

private:
    void*			hLibrary;
};

typedef LibraryUnix AbstractLibrary;

#endif //LIBRARYUNIX
