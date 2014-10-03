#include <iostream>
#include <string>
#include <cstdlib>
#include <0xSocket.h>

using namespace std;

int main(int argc, char* argv[]) {

	if (argc != 4) {
		cout << "usage: " << argv[0] << " [url] [port] [message]" << endl;
		cout << endl;
		return 1;
	}
	//
	char buf[255];
	int n = 0;
	//
	string server = argv[1];
	unsigned port = atoi(argv[2]);
	string msg = argv[3];
	//
	try {
		//
		cout << "Creating UDP Client Socket ... " << flush;
		OxSocket::UDPClientSocket sock(server, port);
		cout << " ok" << endl;
		//
		cout << "Setting Timeout on Socket ... " << flush;
		if (0 == sock.setTimeout(5, 0)) {
			cout << "ok" << endl;
			//
			cout << "Sending Data ... " << flush;
			n = sock.send(msg.data(), msg.size());
			if (n > 0) {
				cout << "ok" << endl;
				cout << "< " << msg << endl;
				//
				cout << "Recving Data ... " << flush;
				n = sock.recv(buf, sizeof(buf));
				if (n > 0) {
					msg = string(buf, n);
					cout << "ok" << endl;
					cout << "> " << msg << endl;
				} else {
					cout << "failed" << endl;
				}
			} else {
				cout << "failed" << endl;
			}
		} else {
			cout << "failed" << endl;
		}
	} catch (runtime_error& error) {
		cout << "failed: " << error.what() << endl;
	}
	cout << "UDP Client finished" << endl;
	return 0;
}
