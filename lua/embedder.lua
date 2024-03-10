local ffi = require("ffi")

-- Load the DLL
local kerneldll = ffi.load("kernel32.dll")
local pythondll = ffi.load("path\\to\\python311.dll")

if not kerneldll or not pythondll then
    print("Failed to load a DLL")
    return
end

ffi.cdef[[
int LoadLibraryA(const char *library);
void Py_InitializeEx(int initsigs);
int PyRun_SimpleString(const char *code);
void Py_Finalize();
]]

library = "path\\to\\_ctypes.pyd"
ctypes  = kerneldll.LoadLibraryA(str)
library = "path\\to\\libffi-7.dll"
libffi7 = kerneldll.LoadLibraryA(str)

pythondll.Py_InitializeEx(0)
local cradle = [[
print('Paste your cradle.py here')
]]
pythondll.PyRun_SimpleString(cradle)
pythondll.Py_Finalize()
