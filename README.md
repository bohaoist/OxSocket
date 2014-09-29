## What is libSocket ?
A object abstraction layer for networking communications calls in C++

## How do i build it?
```Bash
    git clone https://github.com/inbre001/Socket.git;
    cd Socket/bin;
    make;
```
##### How do i use it? 
Just include 
```C++   
#include "Socket.h"
```
and you can initialize TCP, UDP or UNIX Sockets.

## Simple Examples

* [TCP Echo Server](examples/TCPEchoServer.cpp) and [Client](examples/TCPEchoClient.cpp)
* [UDP Echo Server](examples/UDPEchoServer.cpp) and [Client](examples/UDPEchoClient.cpp)
* [UNIX Echo Server](examples/UNIXEchoServer.cpp) and [Client](examples/UNIXEchoClient.cpp)
