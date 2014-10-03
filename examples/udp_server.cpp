#include <iostream>
#include <string>
#include <cstdlib>
#include <0xSocket.h>

using namespace std;

int main(int argc, char* argv[]) {

	if (argc != 2) {
		cout << "usage: " << argv[0] << " [port]" << endl;
		cout << endl;
		return 1;
	}

	unsigned port = atoi(argv[1]);

	try {
		cout << "Creating UDP Server Socket ..." << flush;
		OxSocket::UDPServerSocket sock(port);
		cout << "ok" << endl;

//		cout << "Setting Timeout ...";
//		if (0 == sock.setTimeout(5, 0)) {
//			cout << "ok" << endl;

		char buf[255];
		string msg = "";
		while (true) {
			//
			cout << "Recving Data ... " << flush;
			int n = sock.recv(buf, sizeof(buf));
			if (n > 0) {
				cout << "ok" << endl;
				//
				msg = string(buf, n);
				cout << "> " << msg << endl;
				//
				// msg = "Understood! Thanks Bye.";
				//
				cout << "Sending Data ... " << flush;
				n = sock.send(msg.data(), msg.size());
				if (n > 0) {
					cout << "ok" << endl;
				} else {
					cout << "failed" << endl;
				}
			} else {
				cout << "failed" << endl;
			}
		} // end while

//		} else {
//			cout << "failed" << endl;
//		}
	} catch (const runtime_error& error) {
		cout << "failed: " << error.what() << endl;
	}
	return 1;
}
// EOF 
