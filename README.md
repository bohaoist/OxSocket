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
// init Sockets

TCPServerSocket tcp_server_sock(int port);
TCPClientSocket tcp_client_sock(char* server_addr, int port);

UNIXServerSocket unix_server_sock(char *path_to_sockfile);
UNIXClientSocket unix_client_sock(char* path_to_sockfile);


// Connection Objects  provide send() and recv() functions 

Connection *tcp_to_client = tcp_server_sock.accept();
Connection *tcp_to_server = tcp_client_sock.connect();
Connection *unix_to_client = unix_server_sock.accept();
Connection *unix_to_server = unix_client_sock.connect();


// For UDPSockets no accept() or connect() is necessary 
// A UDP Socket is directly a Connection Object

UDPSocket udp_server_sock(int port);
UDPSocket udp_client_sock(int port, char* server_addr);

udp_server_sock.send(...);
udp_server_sock.recv(...);

```

ServerSockets provide the accept() function to listen for incoming Connections
ClientSockets provide the corresponding connect() function.

Have a look at the Short Examples to get started quickly.

## Short Examples

*  TCP [Server](examples/TCPEchoServer.cpp) and [Client](examples/TCPEchoClient.cpp)
*  UDP [Server](examples/UDPEchoServer.cpp) and [Client](examples/UDPEchoClient.cpp)
* UNIX [Server](examples/UNIXEchoServer.cpp) and [Client](examples/UNIXEchoClient.cpp)


## Advanced Stuff:
TODO: write examples for async. communication and timeouts



