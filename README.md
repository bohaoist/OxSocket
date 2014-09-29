## What is libSocket ?
A object abstraction layer for networking communications calls in C++

## How do i build it?
```Bash
    git clone https://github.com/inbre001/Socket.git;
    cd Socket/build;
    make;
```
##### How do i use it? 
Include <Socket.h> in your Code
```C++
#include <Socket.h> 
```
now you can initialize TCP, UDP or UNIX Sockets. Like this:
```C++
TCPServerSocket tcp_server(int port)
TCPClientSocket tcp_client(char* server_addr, int port);

UDPSocket udp_server(int port);
UDPSocket udp_client(int port, char* server_addr);

UNIXServerSocket unix_ss(char *path_to_sockfile);
UNIXClientSocket unix_cs(char* path_to_sockfile);
```
ServerSockets provide the accept() function to listen for incoming Connections
ClientSockets provide the corresponding connect() function

Have a look at the Short Examples to get started quickly.

## Short Examples

*  TCP [Server](examples/TCPEchoServer.cpp) and [Client](examples/TCPEchoClient.cpp)
*  UDP [Server](examples/UDPEchoServer.cpp) and [Client](examples/UDPEchoClient.cpp)
* UNIX [Server](examples/UNIXEchoServer.cpp) and [Client](examples/UNIXEchoClient.cpp)


## Advanced Stuff:
TODO: write examples for async. communication and timeouts



