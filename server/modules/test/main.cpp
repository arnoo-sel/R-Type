#include "main.h"
#include <iostream>

// a sample exported function
int testFunction(const char* data)
{
    MessageBoxA(0, data, "DLL Message", MB_OK | MB_ICONINFORMATION);
    return 42;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            std::cout << "attach to process" << std::endl;
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            std::cout << "detach from process" << std::endl;
            break;

        case DLL_THREAD_ATTACH:
            std::cout << "attach to thread" << std::endl;
            break;

        case DLL_THREAD_DETACH:
            std::cout << "detach from thread" << std::endl;
            break;
    }
    return TRUE; // succesful
}
