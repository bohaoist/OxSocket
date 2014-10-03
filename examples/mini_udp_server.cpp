#include <iostream>
#include <string>
#include <0xSocket.h>

using namespace std;

int main() {

	OxSocket::UDPServerSocket sock(1234);
	char buf[255];
	int n = 0;

	while (true) {
		n = sock.recv(buf, sizeof(buf));
		cout << string(buf, n) << endl;
		sock.send(buf, n);
	}
	return 1;
}

