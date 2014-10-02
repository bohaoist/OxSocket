
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
## Build the Library and Examples?
```Bash
    git clone https://github.com/inbre001/0xSocket.git;
    cd Socket/Debug;
    make;
    cd ../Example;
    make;
```

## How do i use it? 
* Add \<Socket.h\> to your sourcefile
* Add the include path -I/path/to/0xSocket/include to your compiler options (cflags)
* Add lastly add the linker flag -l0xSocket (ldflags)

## Examples

Have a look at Examples.cpp to get started quickly.

*  [Server and Client Examples for TCP,UDP and UNIX ](src/Example.cpp)

## What next?

Try writing your own IRC Client or a DNS or even NTP Client, with the help of lib0xSocket.


### Happy hacking.

