#include <iostream>
#include <string>
#include <cstdlib>
#include <0xSocket.h>

using namespace std;

int main(int argc, char* argv[]) {

	if (argc == 2) {

		string msg = "";
		int n = 0;
		string line = "";
		char buf = '\0';
		char pbuf = '\0';
		int content_length = 0;
		//
		string host = argv[1];
		unsigned port = 80;
		//
		try {

			TCPClientSocket sock(host, port);
			sock.setTimeout(5, 0);

			msg = "GET / HTTP/1.1\n"
					"Host: " + host + "\n"
					"\n\r";

			n = sock.send(msg.data(), msg.size());
			if (n > 0) {

				msg = "";

				// RECV HEADER
				while (0 < sock.recv(&buf, sizeof(buf))) {

					if (buf == '\n') { // END OF LINE
						if (string::npos != line.find("Content-Length:")) {
							string val = line.substr(line.find(":") + 1);
							content_length = atoi(val.data());
						}
						msg += line; // SAVE LINE
						line = "";
					} else if (buf == '\r' and pbuf == '\n') { // END OF HEADER
						break;
					} else { // BUFFER LINE
						line += buf;
					}
					// SAVE PREV CHAR
					pbuf = buf;
				}

				// RECV BODY
				if (content_length > 0) {
					char body[content_length];
					n = sock.recv(body, content_length);
					if (n > 0) {
						msg += string(body, n);
					}
				}

				// SHOW RESPONSE
				if (msg.size() > 0) {
					cout << msg << endl;
				}
			} else {
				cout << "http_client send() failed" << endl;
			}
		} catch (runtime_error& error) {
			cout << error.what() << endl;
		}
	} else {
		cout << "usage: " << argv[0] << " [url]" << endl << endl;
		return 1;
	}
	return 0;
}

// EOF 
