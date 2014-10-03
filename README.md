
## What is lib0xSocket ?
A object abstraction layer for networking communications calls in C++

It makes Socket Communication as easy as this:
```C++
// Sender 
std::string msg = "Hello World";
UDPClientSocket sock(  "www.example.org" , 1234 );
sock.send(msg.data(),msg.size());
```
```C++
// Receiver
UDPServerSocket sock( 1234 );
char buf[255];
int bsize = sock.recv(buf,sizeof(buf));
std::cout << std::string(buf,bsize) << std::endl;
```

## Build the Library?

```Bash
    git clone https://github.com/inbre001/0xSocket.git;
    cd Socket/lib;
    make;
```

## How do i use it? 

* include \<Socket.h\> to your code
* add the include path -I/path/to/0xSocket/include to your compiler options (cflags)
* add lastly add the linker flag -l0xSocket (ldflags)

## Examples

Have a look at Examples in the examples folder to get started quickly.

| ---------------------------------------- |:---------------------------------------:|
|  [ UDP Client ](example/udp_client.cpp)  | [ UDP Server ](example/udp_server.cpp)  |
|  [ TCP Client ](example/tcp_client.cpp)  |[ TCP Server ](example/tcp_server.cpp)   |
|  [ UNIX Client ](example/unix_client.cpp)| [ UNIX Server ](example/unix_server.cpp)|
|  [ HTTP Client ](example/http_client.cpp)| [ HTTP Client ](example/http_server.cpp)|

## What next?

Try writing your own IRC Client or a DNS or even NTP Client, with the help of lib0xSocket.


#### Happy hacking.

