#include <iostream>
#include <string>
#include <cstdlib>
#include <0xSocket.h>

using namespace std;

int main(int argc, char* argv[]) {

	if (argc != 3) {
		cout << "usage: " << argv[0] << " [socketfile] [message]" << endl;
		return 1;
	}

	const static char EOM = '\n';
	char buf = '\0';
	int n = 0;
	//
	std::string sockfile = argv[1];
	string msg = argv[2];

	try {

		cout << "Creating UNIX Client Socket ... " << flush;
		UNIXClientSocket con(sockfile);
		cout << " ok" << endl;
		//
		cout << "Setting Timeout on Socket ... " << flush;
		if (0 == con.setTimeout(5, 0)) {
			cout << "ok" << endl;
			//
			cout << "Sending Message ... " << flush;
			msg += EOM;
			n = con.send(msg.data(), msg.size());
			if (n > 0) {
				cout << "ok" << endl;
				//
				msg = "";
				cout << "Recving Message ... " << flush;
				while (0 < (n = con.recv(&buf, sizeof(buf))) and EOM != buf) {
					msg += buf;
				}
				if (n > 0) {
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
