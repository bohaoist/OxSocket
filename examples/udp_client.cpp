#include <iostream>
#include <string>
#include <cstdlib>
#include <OxSocket.h>

using namespace std;
using namespace OxSocket;

int main(int argc, char* argv[]) {

	if (argc != 4) {
		cout << "usage: " << argv[0] << " [url] [port] [message]" << endl;
		cout << endl;
		return 1;
	}
	//
	char buf[255];
	int nbytes = 0;
	//
	string server = argv[1];
	unsigned int port = atoi(argv[2]);
	string msg = argv[3];
	//
	try {
		//
		cout << "Creating UDP Client Socket ... " << flush;
		UDPClientSocket sock(server, port);
		cout << " ok" << endl;
		//
		cout << "Setting Timeout on Socket ... " << flush;
		if (0 == sock.setTimeout(5, 0)) {
			cout << "ok" << endl;
			//
			cout << "Sending Data ... " << flush;
			nbytes = sock.send(msg.data(), msg.size());
			if (nbytes > 0) {
				cout << "ok" << endl;
				cout << " send Data to " << sock.targetaddr << endl;
				cout << "< " << msg << endl;
				//
				cout << "Recving Data ... " << flush;
				nbytes = sock.recv(buf, sizeof(buf));
				if (nbytes > 0) {
					msg = string(buf, nbytes);
					cout << "ok" << endl;
					cout << " recved Data from " << sock.targetaddr << endl;
					cout << "> " << msg << endl;
					return 0;
				}
			}
		}
	} catch (runtime_error& error) {
		cout << error.what() << " ... " << endl;
	}
	cout << "failed" << endl;
	return 1;
}
