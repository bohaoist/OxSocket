#include <iostream> /* cout */
#include <string>   /* string */
#include <Socket.h>

using namespace std;

int main() {

	UDPServerSocket sock(1234);
	char buf[255];
	int bsize = 0;

	while (true) {
		bsize = sock.recv(buf, sizeof(buf));
		cout << string(buf, bsize) << endl;
		sock.send(buf, bsize);
	}
	return 1;
}

