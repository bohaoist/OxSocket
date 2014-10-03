#include <iostream>  /* cout, endl */
#include <string>    /* string */
#include <Socket.h>

using namespace std;

int main() {

	char buf[255];
	string msg = "Hello World";

	UDPClientSocket sock("127.0.0.1", 1234);
	sock.send(msg.data(), msg.size());
	int bsize = sock.recv(buf, sizeof(buf));
	cout << string(buf, bsize) << endl;

	return 0;
}
