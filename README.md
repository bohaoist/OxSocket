
## What is lib0xSocket ?
A object abstraction layer for networking communications calls in C++

It makes Socket Communication as easy as this:

```C++

	#include <iostream> /* cout */
	#include <string>   /* string */
	#include <Socket.h>

	using namespace std;

	int main() {

		UDPServerSocket sock(1234);
		char buf[255];
		string msg = "";
		
		while (true) {
			n = sock.recv(buf, sizeof(buf));
			cout << string(buf,n) << endl;
			sock.send(buf, n);
		}
		return 1;
	}
```
save as udp\_echo\_server.cpp and build with:

c++ -I0xSocket/include -l0xSocket -L0xSocket/lib udp\_echo\_server.cpp -o udp\_ecoh\_server.exe


```C++

	/**
	 *  UDP Client that Send and Recv a Message
	 *  (with no error handling)
	 */
	#include <iostream>  /* cout, endl */
	#include <string>    /* string */
	#include <Socket.h>  

	using namespace std;

	int main() {

		char buf[255];
		string msg = "Hello World";
		
		UDPClientSocket sock("127.0.0.1", 1234);
		sock.send(msg.data(), msg.size());		
		sock.recv(buf, sizeof(buf));
		cout << string(recvbuf, nbytes) << endl;
		
		return 0;
	}
```
save as udp\_echo\_client.cpp and build with:

c++ -I0xSocket/include -l0xSocket -L0xSocket/lib udp\_echo\_client.cpp -o udp\_echo\_client.exe



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

*  UDP [Client](examples/udp_client.cpp) and [Server](examples/udp_server.cpp)  
*  TCP [Client](examples/tcp_client.cpp) and [Server](examples/tcp_server.cpp)   
* UNIX [Client](examples/unix_client.cpp) and [Server](examples/unix_server.cpp) 
* HTTP [Client](examples/http_client.cpp) 

## What next?
Try writing your own IRC Client or a DNS or even NTP Client.

#### Happy hacking.

