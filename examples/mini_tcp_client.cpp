#include <iostream>
#include <string>
#include <OxSocket.h>

using namespace std;
using namespace OxSocket;

int main(int argc, char* argv[]) {

	const char EOM = '\n';
	char buf = '\0';

	string msg = "Hello World";

	TCPClientSocket con("127.0.0.1", 1234);
	con.setTimeout(5, 0);

	msg += EOM;
	con.send(msg.data(), msg.size());

	while (0 < con.recv(&buf, sizeof(buf)) and (buf != EOM)) {
		cout << buf;
	}
	cout << endl;

	return 0;
}

// EOF 
