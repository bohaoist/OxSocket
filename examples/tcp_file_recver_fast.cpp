#include <iostream>
#include <string>
#include <OxSocket.h>

using namespace std;

int main(int argc, char* argv[]) {

	if (argc != 3) {
		return 1;
	}
	unsigned port = atoi(argv[1]);

	OxSocket::TCPServerSocket sock(port);

	OxSocket::Connection *con = sock.accept();

	// First recv size of file
	unsigned long int size = 0;
	con->recv((char*) &size, sizeof(size));

	// Now recv File
	con->recvfile_fast(argv[2], size);

	return 0;
}

// EOF 
