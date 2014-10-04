
## What is 0xSocket ?
A C++ object abstraction layer for TCP, UDP and UNIX Socket communications
It makes Socket Communication and file aka. data transfer or 
interprocess or thread communication a bit more fun.

## Build the Library?

```Bash

    git clone https://github.com/inbre001/0xSocket.git;
    cd 0xSocket/lib;
    make;
```

## How do i use it?

* include **\<0xSocket.h\>** in your code
* initalize 0xSocket Object of your choice.
* add include path **-I/path/to/0xSocket/include** to your compiler options (cflags)
* add lastly add the linker flag **-l0xSocket** (ldflags)

**Here are 2 minimal examples with download links and build commands to get you started.**

```C++
	// Mini UDP Server 
	#include <iostream>   /* cout, endl      */
	#include <string>     /* string          */
	#include <0xSocket.h> /* UDPServerSocket */

	int main() {

		OxSocket::UDPServerSocket sock(1234);
		char buf[255];
		int bsize = 0;
		
		while (true) {
			bsize = sock.recv(buf, sizeof(buf));
			std::cout << std::string(buf,bsize) << std::endl;
			sock.send(buf, bsize);
		}
		return 1;
	}
```
save as [mini_udp_server.cpp](examples/mini_udp_server.cpp) and build with:

```Bash
c++ -I0xSocket/include -l0xSocket -L0xSocket/lib mini_udp_server.cpp -o mini_udp_server.exe
```
```C++
	// Mini UDP Client
	#include <iostream>   /* cout, endl      */
	#include <string>     /* string          */
	#include <0xSocket.h> /* UDPClientSocket */

	int main() {

		char buf[255];
		int bsize = 0;
		std::string msg = "Hello World";
		
		OxSocket::UDPClientSocket sock("127.0.0.1", 1234);
		sock.send(msg.data(), msg.size());		
		bsize = sock.recv(buf, sizeof(buf));
		std::cout << std::string(buf, bsize) << std::endl;
		
		return 0;
	}
```
save as [mini_udp_client.cpp](examples/mini_udp_client.cpp) and build with:

```Bash
c++ -I0xSocket/include -l0xSocket -L0xSocket/lib mini_udp_client.cpp -o mini_udp_client.exe	
```

## Some more Examples
Have a look at the source files in the examples folder to get started quickly.

*  UDP [Client](examples/udp_client.cpp) and [Server](examples/udp_server.cpp)  
*  TCP [Client](examples/tcp_client.cpp) and [Server](examples/tcp_server.cpp)   
* UNIX [Client](examples/unix_client.cpp) and [Server](examples/unix_server.cpp) 
* HTTP [Client](examples/http_client.cpp) 
*  FTP TODO

## What next?
Try writing your own IRC Client or a DNS or even NTP Client.

## Happy hacking.

##### Whats with the '0x' Prefix?
No Reason, except to make it a bit more distinguishable from other libs.
I was trying to choose a name that was unused and i stumbled over some files with hex number.
At the time i thought that the 0x should be "disgustin/unique" enought to not cause any confusion.


