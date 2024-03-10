Running the embedder.lua script requires the luajit.exe and lua51.dll files on your Windows target.

You can build these, on you Kali or Windows machine, following the steps described here:

https://luajit.org/install.html

Once built and uploaded, you can run the embedder.lua like this:

`.\luajit.exe .\embedder.lua`

I am working on the following ideas:

+ Use wininet.dll to download the Python files from a server (supporting NTLM/Kerberos proxies)
+ Use wininet.dll to download the cradle itself from a server
