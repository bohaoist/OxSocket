#include <iostream>
#include <string>
#include <0xSocket.h>

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
