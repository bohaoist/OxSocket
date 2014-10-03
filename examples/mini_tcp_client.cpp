#include <iostream> /* cout */
#include <string>   /* string */

#include <Socket.h>

using namespace std;

int main(int argc, char* argv[]) {

	const char EOM = '\n';
	char buf = '\0';
	bool ok = false;
	int nbytes = 0;
	//
	string msg = "Hello World";

	TCPClientSocket con("127.0.0.1", 1234);
	con.setTimeout(5, 0);

	msg += EOM;
	con.send(msg.data(), msg.size());

	while (con.recv(&buf, sizeof(buf)) > 0 and (buf != EOM)) {
		cout << buf;
	}
	cout << endl;

	return 0;
}

// EOF 
