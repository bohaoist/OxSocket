## What is libSocket ?
A object abstraction layer for networking communications calls in C++

It makes Socket Communication as easy as this:
```C++
// Sender 
UDPClientSocket mysock(  "www.example.org" , 1234 );
std::string msg = "Hello World";
mysock.send(msg.data(),msg.size());
```
and at the recv side simply do
```C++
// Recv 
UDPServerSocket mysock( 1234 );
char buf[255];
int bsize = mysock.recv(buf,sizeof(buf));
std::cout << std::string(buf,bsize) << std::endl;
```
Thats it. 

## Build the Library and Examples?
```Bash
    git clone https://github.com/inbre001/Socket.git;
    cd Socket/Debug;
    make;
    cd ../Examples;
    make;
```
## How do i use it? 
* Add \<Socket.h\> to your sourcefile
* Add the include path -I/path/to/0xSocket/include to your compiler options (cflags)
* Add lastly add the linker flag -l0xSocket (ldflags)

## 


Have a look at the Examples to get started quickly.
## Examples

*  [Echo Server and Client Examples for TCP,UDP and UNIX ](src/Examples.cpp)

## Running the Examples
```BASH
usage: Examples.exe [sc] [tux]
All Examples:
     TCP Server Examples.exe s t
     TCP Client Examples.exe c t
     UDP Server Examples.exe s u
     UDP Client Examples.exe c u
    UNIX Server Examples.exe s x
    UNIX Client Examples.exe c x
```
## Advanced Stuff:
TODO: write examples for async. communication and timeouts



