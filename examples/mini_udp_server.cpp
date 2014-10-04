#include <iostream>
#include <string>
#include <0xSocket.h>

int main() {

	OxSocket::UDPServerSocket sock(1234);
	char buf[255];
	int bsize = 0;

	while (true) {
		bsize = sock.recv(buf, sizeof(buf));
		std::cout << std::string(buf, bsize) << std::endl;
		sock.send(buf, bsize);
	}
	return 1;
}

