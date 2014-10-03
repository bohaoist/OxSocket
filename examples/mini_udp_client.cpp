#include <iostream>
#include <string>
#include <0xSocket.h>

using namespace std;

int main() {

	char buf[255];
	string msg = "Hello World";

	UDPClientSocket sock("127.0.0.1", 1234);
	sock.send(msg.data(), msg.size());
	int n = sock.recv(buf, sizeof(buf));
	cout << string(buf, n) << endl;

	return 0;
}
