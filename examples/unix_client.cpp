#include <iostream> /* cout */
#include <string>   /* string */
#include <cstdlib>   /* atoi */

#include <Socket.h>

using namespace std;

const static char END_OF_MESSAGE = '\n';

int main(int argc, char* argv[]) {

	if (argc != 3) {
		cout << "usage: " << argv[0] << " [socketfile] [message]" << endl;
		return 1;
	}

	char recvbuf = '\0';
	bool recvok = false;
	int nbytes = 0;
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
			msg += END_OF_MESSAGE;
			nbytes = con.send(msg.c_str(), msg.size());
			if (nbytes > 0) {
				cout << "ok" << endl;
				//
				msg = "";
				cout << "Recving Message ... " << flush;
				while ((nbytes = con.recv(&recvbuf, sizeof(recvbuf))) > 0) {
					if (recvbuf == END_OF_MESSAGE) {
						recvok = true;
						break;
					}
					msg += recvbuf;
				}
				if (nbytes > 0 and recvok) {
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
