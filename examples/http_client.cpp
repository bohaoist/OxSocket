#include <iostream>
#include <string>
#include <cstdlib>
#include <0xSocket.h>

using namespace std;
using namespace OxSocket;

int main(int argc, char* argv[]) {
	//
	if (2 != argc) {
		cout << "usage: " << argv[0] << " [url]" << endl << endl;
		return 1;
	}
	//
	string msg = "", line = "", host = argv[1];
	int nbytes = 0, content_length = 0;
	char buf = '\0', pbuf = '\0', port = 80;
	//
	try {

		TCPClientSocket sock(host, port);
		sock.setTimeout(5, 0);

		msg = "GET / HTTP/1.1\n"
				"Host: " + host + "\n"
				"\n\r";

		nbytes = sock.send(msg.data(), msg.size());
		if (nbytes > 0) {
			//
			msg = "";
			//
			// RECV HEADER
			while (0 < sock.recv(&buf, sizeof(buf))) {

				if ('\n' == buf) { // END OF LINE
					if (string::npos != line.find("Content-Length:")) {
						string val = line.substr(line.find(":") + 1);
						content_length = atoi(val.data());
					}
					msg += line; // SAVE LINE
					line = "";
				} else if ('\r' == buf and '\n' == pbuf) { // END OF HEADER
					break;
				} else { // BUFFER LINE
					line += buf;
				}
				// SAVE PREV CHAR
				pbuf = buf;
			}

			// RECV BODY
			if (0 < content_length) {
				char body[content_length];
				nbytes = sock.recv(body, content_length);
				if (nbytes > 0) {
					msg += string(body, nbytes);
				}
			}

			// SHOW RESPONSE
			if (0 < msg.size()) {
				cout << msg << endl;
				return 0;
			}
		}
	} catch (runtime_error& error) {
		cout << error.what() << " ... " << endl;
	}
	cout << "http_client failed" << endl;
	return 1;
}

// EOF 
