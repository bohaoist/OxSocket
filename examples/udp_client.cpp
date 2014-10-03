#include <iostream>  /* cout, endl */
#include <string>    /* string */
#include <cstdlib>   /* atoi */
//
#include <Socket.h>  /* Magic */

using namespace std;

int main(int argc, char* argv[]) {

	if (argc != 4) {
		cout << "usage: " << argv[0] << " [url] [port] [message]" << endl;
		cout << endl;
		return 1;
	}
	//
	char recvbuf[255];
	int nbytes = 0;
	//
	string server = argv[1];
	unsigned port = atoi(argv[2]);
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
			cout << "Sending Message ... " << flush;
			nbytes = sock.send(msg.data(), msg.size());
			if (nbytes > 0) {
				cout << "ok" << endl;
				cout << "< " << msg << endl;
				//
				cout << "Recving Message ... " << flush;
				nbytes = sock.recv(recvbuf, sizeof(recvbuf));
				if (nbytes > 0) {
					msg = string(recvbuf, nbytes);
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
