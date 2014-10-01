## What is libSocket ?
A object abstraction layer for networking communications calls in C++

## How do i build it?
```Bash
    git clone https://github.com/inbre001/Socket.git;
    cd Socket/Debug;
    make;
    cd ..;
    cd Examples;
    make
```
##### How do i use it? 
Include <Socket.h> in your Code
```C++
#include <Socket.h> 
```
now you can initialize TCP, UDP or UNIX Sockets. Like this:

Have a look at the Examples to get started quickly.

## Examples

*  [Echo Server and Client Examples for TCP,UDP and UNIX ](src/Examples.cpp)


## Advanced Stuff:
TODO: write examples for async. communication and timeouts



