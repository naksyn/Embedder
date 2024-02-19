![Supported Python versions](https://img.shields.io/badge/python-3.7+-blue.svg) [![Twitter](https://img.shields.io/twitter/follow/naksyn?label=naksyn&style=social)](https://twitter.com/intent/follow?screen_name=naksyn)

# Embedder

## What is it

Embedder is a collection of sources in different programming languages (C++, Go, Nim, C#) that leverages the [Embedding techinque](https://docs.python.org/3/extending/embedding.html) to obtain execution of Python code.
Embedder also aims at generating programs with **small size** that can run meaningful Python code, by loading only the minimum required dependencies to access the ctypes module (ctypes allows you to call Windows APIs directly with Python).

## Why is it useful

This is a way to run [Pyramid](https://github.com/naksyn/Pyramid) without python.exe, using small PEs compiled in different languages in its place. Apart from its original purpose, this technique can be used to bring Python code execution virtually in every language that lets you interact with Windows APIs.

## Usage

### Drop depencencies
Drop **python310.dll** or your preferred version, **_ctypes.pyd**, **libffi-7.dll** and **python310.zip** on the folder where your executable is running, or change the load path accordingly in the source. You can find these files in the embeddable package downloadable from python.org (e.g. https://www.python.org/downloads/release/python-31010/).

### Insert your Python code in the source
paste your Python code and assign it to the `pythoncode` variable in the source. If using Pyramid, first start the server and use the python code generated.


### Compile source

 * C#: `csc.exe embedder.cs`
 * cpp: `cl /EHsc /Fe:embedder.exe embedder.cpp`
 * nim: create a nim.cfg file like the following:
```
amd64.windows.gcc.path = "/usr/bin/"
amd64.windows.gcc.exe = "x86_64-w64-mingw32-gcc"
amd64.windows.gcc.linkerexe = "x86_64-w64-mingw32-gcc"
```
Then `nim c --os:windows --cpu:amd64 -d:mingw embedder.nim`
 * go:
   ```
   go mod init main
   
   CGO_ENABLED=1 GOOS=windows GOARCH=amd64 CC=x86_64-w64-mingw32-gcc go build -o embedder.exe
   ```

## Demo

#### Using a **13 kB**  C# embedder assembly to run Python code bootstrapping a Pyramid module that injects mimikatz.exe with arguments.


https://github.com/naksyn/embedder/assets/59816245/204efba1-06ea-4ea3-9029-09ca3f9890cc

#### Using a 267 kB C++ exe to run Python code bootstrapping a Pyramid module that injects chisel.exe with arguments

https://github.com/naksyn/embedder/assets/59816245/f6a9ed44-3f51-41e6-a5c4-6986609aa429

# Disclaimer

Embedder is developed for educational, research, and legal security testing purposes. It is intended for use by security professionals and researchers with authorization to evaluate and improve security systems in a lawful manner.
Users must comply with all applicable laws and ethical guidelines.

# Limitations

If you need to execute complex Python code with lots of dependencies, currently you need to drop all the pyd files that will be loaded during code execution and find a way to import also needed Python modules (drop on disk or in-memory).
**I won't provide support for Python code that it's not working**. My focus is to make embedder work with some Pyramid modules using its in-memory import technique.

