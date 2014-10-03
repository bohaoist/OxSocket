#include <iostream> /* cout */
#include <string>   /* string */
#include <cstdlib>   /* atoi */

#include <Socket.h>

using namespace std;

const static char END_OF_MESSAGE = '\n';

int main(int argc, char* argv[]) {

	if (argc != 4) {
		cout << "usage: " << argv[0] << " [url] [port] [message]" << endl;
		return 1;
	}

	char buf = '\0';
	bool ok = false;
	int nbytes = 0;
	//
	std::string server = argv[1];
	unsigned port = atoi(argv[2]);
	string msg = argv[3];

	try {

		cout << "Creating TCP Client Socket ... " << flush;
		TCPClientSocket con(server, port);

		cout << " ok" << endl;
		//
		cout << "Setting Timeout on Socket ... " << flush;
		if (0 == con.setTimeout(5, 0)) {
			cout << "ok" << endl;
			//
			cout << "Sending Message ... " << flush;
			msg += END_OF_MESSAGE;
			nbytes = con.send(msg.data(), msg.size());
			if (nbytes > 0) {
				cout << "ok" << endl;
				//
				msg = "";
				cout << "Recving Message ... " << flush;
				while ((nbytes = con.recv(&buf, sizeof(buf))) > 0) {
					if (buf == END_OF_MESSAGE) {
						ok = true;
						break;
					}
					msg += buf;
				}
				if (nbytes > 0 and ok) {
					cout << "ok" << endl;
					cout << "> " << msg << "" << endl;
				} else {
					cout << "failed " << endl;
				}
			} else {
				cout << "failed " << endl;
			}
		} else {
			cout << "failed" << endl;
		}
	} catch (const runtime_error& error) {
		cout << error.what() << endl;
	}
	cout << "TCP Client finished" << endl;
	return 0;
}

// EOF 
