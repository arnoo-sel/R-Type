#include "library/libraryUnix.hpp"

LibraryUnix::LibraryUnix(const string& libName)
{
    hLibrary = dlopen((libName + ".so").c_str(), RTLD_LAZY);
    if(hLibrary == NULL)
        throw new LibraryException("Could not open library", (libName + ".so"));
}

LibraryUnix::~LibraryUnix()
{
    dlclose(hLibrary);
}

ILibrary::voidFuncPtr      LibraryUnix::getVoidSym(const string &name)
{
    void* initializer = dlsym(hLibrary, name.c_str());
    if(initializer == NULL) {
        throw new LibraryException("Could not find symbol " + name);
    } else {
        return (reinterpret_cast<voidFuncPtr>(initializer));
    }
}
