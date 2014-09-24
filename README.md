# netlib
## What is it ?
A Object abstraction Layer for Networking Communications Calls in C++

## What do i need to build it?
A C++ Compiler and stdlib and some magic.

## How do i build it?
```Bash
    git clone https://github.com/inbre001/netlib.git;
    cd netlib/lib/;
    make;
```
##### How do i use it? 
Just include the "Net.h" Header in your Code.
```C++   
#include "Net.h"
```
Now you can initialize TCP and UDP "Sockets"

#### Examples

Here are some simple Examples 

##### TCP Echo Server
```C++   
    #include "Net.h"
    #include <iostream>
    #include <string>

    int main(int argc, char *argv[]) {
    
        int port = 1234;
        char buf[255];

        ServerSocket serversock(port);
        Connection *c = NULL;
    
        while(true){
            c = serversock.accept(); // wait for Connections
            int nbytes = c->recv(buf, sizeof(buf));
            if (nbytes >= 0) {
                std::cout << "Echo Server: recved message '" //
                << std::string(buf,nbytes) << "'" << std::endl;
            }
            c->send(buf,nbytes);
            delete c;
        }
        return 0;
    }
```
##### TCP Echo Client
```C++   
    #include "Net.h"
    #include  <iostream>
    #include  <string>

    int main(int argc, char *argv[]) {
    
        int port = 1234;
        char buf[255];
        std::string msg = "Echo";
        std::string server = "127.0.0.1";

        Socket sock(server,port);
        Connection *c = sock.connect(); 

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

##### UDP Echo Server
 ```C++   
    #include "Net.h"
    #include <iostream>
    #include <string>

    int main(int argc, char *argv[]) {
    
        int port = 1234;
        char buf[255];

        UDPSocket udpsock(port);
    
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
    #include "Net.h"
    #include  <iostream>
    #include  <string>

    int main(int argc, char *argv[]) {
    
        int port = 1234;
        char buf[255];
        std::string msg = "Echo";
        std::string server = "127.0.0.1";

        UDPSocket udpsock(server,port);
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

