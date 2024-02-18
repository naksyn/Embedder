/*
Author: @naksyn (c) 2024

Description: A Simple Go program to embed Python interpeter and load the strictly required libraries to bootstrap Pyramid 

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

package main

/*
#cgo LDFLAGS: -lkernel32
#include <windows.h>
#include <stdio.h>


void (*Py_Initialize)(void);
int (*PyRun_SimpleString)(const char *);
void (*Py_Finalize)(void);


HMODULE loadLibrary(const char* name) {
    HMODULE hModule = LoadLibraryA(name);
    if (hModule == NULL) {
        fprintf(stderr, "Failed to load %s\n", name);
    }
    return hModule;
}


void loadPythonFunctions() {
    HMODULE pythonDLL = loadLibrary("python310.dll");
    HMODULE libFFIDLL = loadLibrary("libffi-7.dll"); // Not directly used here, but loaded for dependency
    HMODULE ctypesDLL = loadLibrary("_ctypes.pyd");  // Not directly used here, but loaded for dependency

    if (!(pythonDLL && libFFIDLL && ctypesDLL)) {
        fprintf(stderr, "Failed to load one or more DLLs\n");
        return;
    }

    *(FARPROC *)&Py_Initialize = GetProcAddress(pythonDLL, "Py_Initialize");
    *(FARPROC *)&PyRun_SimpleString = GetProcAddress(pythonDLL, "PyRun_SimpleString");
    *(FARPROC *)&Py_Finalize = GetProcAddress(pythonDLL, "Py_Finalize");

    if (!Py_Initialize || !PyRun_SimpleString || !Py_Finalize) {
        fprintf(stderr, "Failed to load one or more Python API functions\n");
    }
}

// Wrappers
void cPyInitialize() {
    Py_Initialize();
}

void cPyRun_SimpleString(const char* str) {
    PyRun_SimpleString(str);
}

void cPyFinalize() {
    Py_Finalize();
}
*/
import "C"
import "unsafe"

func main() {
    
    C.loadPythonFunctions()
    C.cPyInitialize()
	
// Execute Python Code
    
	pythonCode := `
print("paste Pyramid cradle here")
`
    cPythonCode := C.CString(pythonCode)
    defer C.free(unsafe.Pointer(cPythonCode))
    C.cPyRun_SimpleString(C.CString(pythonCode))
    C.cPyFinalize()
}
