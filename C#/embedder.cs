/*
Author: @naksyn (c) 2024

Description: A Simple C# program to embed Python interpeter and load the strictly required libraries to bootstrap Pyramid 

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

using System;
using System.Runtime.InteropServices;

class Program
{
    [DllImport("kernel32.dll", SetLastError = true)]
    private static extern IntPtr LoadLibrary(string lpFileName);

    [DllImport("python310.dll", EntryPoint = "Py_InitializeEx", CallingConvention = CallingConvention.Cdecl)]
    public static extern void Py_InitializeEx(int initsigs);

    [DllImport("python310.dll", EntryPoint = "PyRun_SimpleString", CallingConvention = CallingConvention.Cdecl)]
    public static extern int PyRun_SimpleString(string code);

    [DllImport("python310.dll", EntryPoint = "Py_Finalize", CallingConvention = CallingConvention.Cdecl)]
    public static extern void Py_Finalize();

    static void Main(string[] args)
    {
		IntPtr ctypesHandle = LoadLibrary("_ctypes.pyd");
        IntPtr libffiHandle = LoadLibrary("libffi-7.dll");
        Py_InitializeEx(0); 

        
        string pythonCode = @"
print("paste Pyramid cradle here")
";
		
        if (PyRun_SimpleString(pythonCode) != 0)
        {
            Console.WriteLine("Failed to execute Python code!");
        }

        Py_Finalize();
    }
}

