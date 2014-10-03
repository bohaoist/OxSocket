#include <iostream> /* cout */
#include <Socket.h> /* TCP/UNIXClientSocket, Connection */
#include <string>   /* string */
#include <sstream>

using namespace std;

/**
 * convert a string to a T object
 **/
template<class T> T str2(const string str) {
	T tmp;
	stringstream ss(str, stringstream::in);
	ss >> tmp;
	return (tmp);
}

/**
 * Removes leading and trailing Spaces and Tabs
 **/
string trim(const string str) {
	size_t beg = str.find_first_not_of(" \t\n\r");
	size_t end = str.find_last_not_of(" \t\n\r");
	if (string::npos == beg or string::npos == end) {
		return ("");
	}
	return (str.substr(beg, end + 1));
}

int main(int argc, char* argv[]) {

	string host = "";
	string msg = "";
	int n = 0;
	string line = "";
	char buf = '\0';
	char pbuf = '\0';
	int content_length = 0;

	if (argc == 2) {

		host = argv[1];
		try {

			TCPClientSocket sock(host, 80);
			sock.setTimeout(5, 0);

			msg = "GET / HTTP/1.1\n"
					"Host: " + host + "\n"
					"\n\r";

			n = sock.send(msg);
			if (n > 0) {

				msg = "";

				// RECV HEADER
				while (0 < sock.recv(&buf, sizeof(buf))) {

					if (buf == '\n') { // END OF LINE
						if (string::npos != line.find("Content-Length:")) {
							string val = line.substr(line.find(":") + 1);
							content_length = str2<int>(trim(val));
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
					cout << endl;
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
