#include <iostream>
#include <string>
#include <cstdlib>
#include <OxSocket.h>

using namespace std;
using namespace OxSocket;

int main(int argc, char* argv[]) {

	if (argc != 4) {
		cout << "usage: " << argv[0] << " [url] [port] [message]" << endl;
		return 1;
	}

	const char EOM = '\n';
	char buf = '\0';
	int n = 0;
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
			cout << "Sending Data ... " << flush;
			msg += EOM;
			n = con.send(msg.data(), msg.size());
			if (n > 0) {
				cout << "ok" << endl;
				//
				msg = "";
				cout << "Recving Data ... " << flush;
				while (0 < (n = con.recv(&buf, sizeof(buf))) and EOM != buf) {
					msg += buf;
				}
				if (n > 0) {
					cout << "ok" << endl;
					cout << "> " << msg << "" << endl;
					return 0;
				}
			}
		}
	} catch (const runtime_error& error) {
		cout << error.what() << " ... " << endl;
	}
	cout << "failed" << endl;
	return 1;
}

// EOF 
