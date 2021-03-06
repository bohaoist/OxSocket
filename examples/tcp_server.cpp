#include <iostream>
#include <string>
#include <cstdlib>
#include <OxSocket.h>

using namespace std;
using namespace OxSocket;

int main(int argc, char* argv[]) {

	if (argc != 2) {
		cout << "usage: " << argv[0] << " [port]" << endl;
		return 1;
	}
	const char EOM = '\n';
	char buf = '\0';
	int n = 0;
	string msg = "";
	Connection *con = NULL;
	//
	unsigned port = atoi(argv[1]);

	try {

		cout << "Creating TCP Server Socket ... " << flush;
		TCPServerSocket sock(port);
		cout << "ok" << endl;

		//
		while (true) {
			//
			cout << "Accepting Connection ... " << flush;
			con = sock.accept();
			if (NULL != con) {
				cout << "ok" << endl;
				//
				cout << "Setting Timeout on Socket ... " << flush;
				if (0 == con->setTimeout(3, 0)) {
					cout << "ok" << endl;
					//
					cout << "Recving Data... " << flush;
					msg = "";
					while (0 < (n = con->recv(&buf, sizeof(buf))) and EOM != buf) {
						msg += buf;
					}

					if (n > 0) {
						cout << "ok" << endl;
						cout << "> " << msg << "" << endl;
						//
						cout << "Sending Data ... " << flush;
						msg += EOM;
						n = con->send(msg.data(), msg.size());
						if (n > 0) {
							cout << "ok" << endl;
						} else {
							cout << "failed" << endl;
						}
					} else {
						cout << "failed" << endl;
					}
				} else {
					cout << "failed" << endl;
				}
				cout << "Closing Connection ... " << flush;
				delete con;
				cout << "ok" << endl;
			} else {
				cout << "failed" << endl;
			}
		} // end while
	} catch (const runtime_error& error) {
		cout << error.what() << " ... failed" << endl;
	}
	return 1;
}

// EOF 
