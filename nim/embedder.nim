#[ 
Author: @naksyn (c) 2024

Description: A Simple nim program to embed Python interpeter and load the strictly required libraries to bootstrap Pyramid 

Copyright 2024
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
]#

import dynlib, os, strutils

proc loadLibrary(name: string): pointer =
  let libHandle = loadLib(name)
  if libHandle == nil:
    echo("Failed to load ", name)
  return libHandle

# Declare the types for the Python C API functions with dynamic linking
proc Py_InitializeEx(initsigs: cint) {.cdecl, dynlib: "python310.dll", importc: "Py_InitializeEx".}
proc PyRun_SimpleString(code: cstring): cint {.cdecl, dynlib: "python310.dll", importc: "PyRun_SimpleString".}
proc Py_Finalize() {.cdecl, dynlib: "python310.dll", importc: "Py_Finalize".}

proc main() =
  
  discard loadLibrary("python310.dll")
  discard loadLibrary("libffi-7.dll")  # Loaded for dependency purposes
  discard loadLibrary("_ctypes.pyd")   # Loaded for dependency purposes

  Py_InitializeEx(0)

  
  let pythonCode = """
print("paste Pyramid cradle here")
""".cstring  # Convert Nim string to C string for compatibility

  if PyRun_SimpleString(pythonCode) != 0:
    echo "Failed to execute Python code!"
  
  Py_Finalize()

when isMainModule:
  main()
