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



##### UDP Echo Server
 ```C++   
    #include "Socket.h"
    #include <iostream>
    #include <string>

    int main(int argc, char *argv[]) {
    
        int port = 1234;
        char buf[255];

        UDPServerSocket udpsock(port);
    
        while(true){
            int nbytes = udpsock->recv(buf, sizeof(buf));
            if (nbytes >= 0) {
                std::cout << "Echo Server: recved message '" //
                << std::string(buf,nbytes) << "'" << std::endl;
            }
            c->send(buf,nbytes);
        }
        return 0;
    }
```
   
##### UDP Echo Client
 ```C++   
    #include "Socket.h"
    #include  <iostream>
    #include  <string>

    int main(int argc, char *argv[]) {
    
        int port = 1234;
        char buf[255];
        std::string msg = "Echo";
        std::string server = "127.0.0.1";

        UDPClientSocket udpsock(server,port);
        c->send(msg,msg.size());

        int nbytes = c->recv(buf,sizeof(buf));
        if (nbytes >= 0) {
                std::cout << "Echo Client: recved message '"  //
                << std::string(buf,nbytes) << "'" << std::endl;
        }
        delete c;

        return 0;
    }
```
   
## Advanced Stuff

### Socket Timeouts
   TODO  write Example
### Async. Communication (Blocking an Non-Blocking)
   TODO  write Example

