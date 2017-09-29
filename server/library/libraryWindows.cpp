#include "library/libraryWindows.hpp"
#include "utils.hpp"

LibraryWindows::LibraryWindows(const string& libName)
{
    hLibrary = LoadLibrary(Utils::StringToWString(libName + ".dll").c_str());
    if(hLibrary == NULL)
        throw new LibraryException("Could not open library", (libName + ".dll"));
}

LibraryWindows::~LibraryWindows()
{
    FreeLibrary(hLibrary);
}

ILibrary::voidFuncPtr      LibraryWindows::getVoidSym(const string &name)
{
    FARPROC initializer = GetProcAddress(hLibrary, name.c_str());
    if(initializer == NULL) {
        throw new LibraryException("Could not find symbol " + name);
    } else {
        return (reinterpret_cast<voidFuncPtr>(initializer));
    }
}
