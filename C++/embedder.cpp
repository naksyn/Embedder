/*
Author: @naksyn (c) 2024

Description: A Simple C++ program to embed Python interpeter and load the strictly required libraries to bootstrap Pyramid 

Copyright 2024
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <iostream>
#include <Windows.h>



int main() {
    
    const LPCWSTR dllNames[] = {
        L"python310.dll",  //put the interpreter dll as first in the array
        L"libffi-7.dll",  // needed to access ctypes
        L"_ctypes.pyd"   // needed to access ctypes
    };
    const int numDLLs = sizeof(dllNames) / sizeof(LPCWSTR);

    HMODULE hModules[numDLLs];
    for (int i = 0; i < numDLLs; ++i) {
        hModules[i] = LoadLibrary(dllNames[i]);
        if (hModules[i] == NULL) {
            std::cerr << "Failed to load DLL: " << dllNames[i] << std::endl;
            for (int j = 0; j < i; ++j) {
                FreeLibrary(hModules[j]);
            }
            return 1;
        }
    }
    std::cout << "All DLLs loaded successfully." << std::endl;
    

    // Resolve Py_InitializeEx
    typedef void (*PINITIALIZEEXFN)(int);
    PINITIALIZEEXFN pInitializeEx = reinterpret_cast<PINITIALIZEEXFN>(GetProcAddress(hModules[0], "Py_InitializeEx"));
    if (pInitializeEx == NULL) {
        std::cerr << "Failed to resolve Py_InitializeEx function!" << std::endl;
        FreeLibrary(hModules[0]);
        return 1;
    }

    pInitializeEx(0);

    typedef int (*PRUNSINGLESTRING)(const char*);
    PRUNSINGLESTRING pRunSimpleString = reinterpret_cast<PRUNSINGLESTRING>(GetProcAddress(hModules[0], "PyRun_SimpleString"));
    if (pRunSimpleString == NULL) {
        std::cerr << "Failed to resolve PyRun_SimpleString function!" << std::endl;
        FreeLibrary(hModules[0]);
        return 1;
    }


    const char* pythonCode = R"(
print("paste Pyramid cradle here")
)";
    if (pRunSimpleString(pythonCode) != 0) {
        std::cerr << "Failed to execute Python code!" << std::endl;
        FreeLibrary(hModules[0]);
        return 1;
    }

   
    typedef void (*PFINALIZEFN)();
    PFINALIZEFN pFinalize = reinterpret_cast<PFINALIZEFN>(GetProcAddress(hModules[0], "Py_Finalize"));
    if (pFinalize != NULL) {
        pFinalize();
    }


    for (int i = 0; i < numDLLs; ++i) {
        FreeLibrary(hModules[i]);
    }

    return 0;

}

