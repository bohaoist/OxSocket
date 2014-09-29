## What is netlib ?
A object abstraction layer for networking communications calls in C++

## How do i build it?
```Bash
    git clone https://github.com/inbre001/Socket.git;
    cd Socket;
    ./build.sh;
```
##### How do i use it? 
Just include the "Socket.h" Header in your Code.
```C++   
#include "Socket.h"
```
Now you can initialize TCP, UDP or UNIX Sockets

#### Examples

* [TCP Echo Server](examples/TCPEchoServer.cpp)
* [TCP Echo Client](examples/TCPEchoClient.cpp)
* [UDP Echo Server](examples/UDPEchoServer.cpp)
* [UDP Echo Client](examples/UDPEchoClient.cpp)
* [UNIX Echo Server](examples/UNIXEchoServer.cpp)
* [UNIX Echo Client](examples/UNIXEchoClient.cpp)


## Advanced Stuff

### Socket Timeouts
   TODO  write Example
### Async. Communication (Blocking an Non-Blocking)
   TODO  write Example

