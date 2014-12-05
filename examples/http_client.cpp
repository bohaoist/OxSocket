#include <iostream>
#include <string>
#include <cstdlib>
#include <OxSocket.h>

using namespace std;
using namespace OxSocket;

int main(int argc, char* argv[]) {
	//
	if (4 != argc) {
		cout << "usage: " << argv[0] << "[example.net] [index.html]" << endl << endl;
		cout << "       " << argv[0] << "[gdata.youtube.com] [feeds/base/users/Bruugar/uploads?alt=rss&v=2&orderby=published] [index.html]" << endl << endl;
		return 1;
	}
	//
	string line = "", host = argv[1], url = argv[2], msg = argv[3];
	int nbytes = 0, content_length = 0;
	char buf = '\0', pbuf = '\0', port = 80;
	//
	try {

		TCPClientSocket sock(host, port);
		sock.setTimeout(15, 0);

        /*msg = "GET /" + url + " HTTP/1.1\n"
				"Host: " + host + "\n"
				"\n\r";*/
        msg = "";
        msg += "POST "+ url + " HTTP/1.1\n";
        msg += "Host: "+ host + "\n";
        msg += "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:33.0) Gecko/20100101 Firefox/33.0\n";
        msg += "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\n";
        msg += "Referer: http://hsp-hh.sport.uni-hamburg.de/angebote/aktueller_zeitraum/_Gruppentraining_im_Uni-Studio.html\n";
        msg += "Content-Type: application/x-www-form-urlencoded\n";
        msg += "Content-Length: 28\n";
        msg += "BS_Kursid_27375=Vormerkliste";
        msg += "\n\r";


		cout << msg;

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
                    cout << line;
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
		}else{
            cout << "send bytes < 0 " << endl;
        }
	} catch (runtime_error& error) {
		cout << error.what() << " ... " << endl;
	}
	cout << "http_client failed" << endl;
	return 1;
}

// EOF 
