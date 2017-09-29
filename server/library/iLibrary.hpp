#ifndef ILIBRARY
# define ILIBRARY

#include <string>
#include "library/libraryException.hpp"

using std::string;

class ILibrary
{
public:
    typedef void*   (*voidFuncPtr)();
    virtual ~ILibrary() {};

    template<typename ptrType>
    ptrType             getSym(const string &name)
    {
        return (reinterpret_cast<ptrType>(getVoidSym(name)));
    }
    virtual voidFuncPtr      getVoidSym(const string &name) = 0;
};

#ifdef WIN32
  #include "library/libraryWindows.hpp"
#else
  #include "library/libraryUnix.hpp"
#endif

#endif //ILIBRARY
