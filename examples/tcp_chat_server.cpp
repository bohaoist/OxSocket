#include <iostream>
#include <string>
#include <cstdlib>
#include <0xSocket.h>
#include <map>
#include <iterator>

using namespace std;
using namespace OxSocket;

const static char EOM = '\n';
map<string, Connection*> clients;
map<string, Connection*>::iterator cliter;

void rm_client(string client_id) {
	delete clients[client_id];
	clients.erase(client_id);
}

int recvOneMsg(Connection* con, string& msg) {
	char buf = '\0';
	msg = "";
	int n = 0;
	while (0 < (n = con->recv(&buf, sizeof(buf))) and EOM != buf) {
		msg += buf;
	}
	return n;
}
void broadcast(string client_id, string msg) {
	Connection *con = NULL;
	for (cliter = clients.begin(); cliter != clients.end(); cliter++) {
		if (client_id != cliter->first) {
			con = cliter->second;
			msg = client_id + msg;
			msg += EOM;
			if (0 < con->send(msg.data(), msg.size())) {
				rm_client(cliter->first);
			}
		}
	}
}

void CheckForNewMessages() {
	Connection *con = NULL;
	string msg = "";
	for (cliter = clients.begin(); cliter != clients.end(); cliter++) {
		con = cliter->second;
		recvOneMsg(con, msg);
		if (msg.size() > 0) {
			broadcast(cliter->first, msg);
		}
	}
}

int main(int argc, char* argv[]) {

//	if (argc != 2) {
//		cout << "usage: " << argv[0] << " [port]" << endl;
//		return 1;
//	}

	char buf = '\0';
	int n = 0;
	string msg = "";
	Connection *con = NULL;
	//
	unsigned port = 1234;//atoi(argv[1]);

	try {

		cout << "Creating TCP Server Socket ... " << flush;
		TCPServerSocket sock(port);
		cout << "ok" << endl;

		//
		while (true) {
			//
//			cout << "Accepting Connection ... " << flush;
			sock.setNonBlocking();
			con = sock.accept();
			if (NULL != con) {
//				cout << "ok" << endl;
				//
//				cout << "Setting Timeout on Socket ... " << flush;
//				if (0 == con->setTimeout(3, 0))
//				con->setNonBlocking();
//				{
//					cout << "ok" << endl;
				//
//				cout << "Recving Message... " << flush;
				msg = "";
//				while (0 < (n = con->recv(&buf, sizeof(buf))) and EOM != buf) {
//					msg += buf;
//				}
				recvOneMsg(con, msg);

				if (msg.size() > 0) {
					cout << "added new client" << endl;
					clients[msg] = con;
				}

//					if (n > 0) {
//						cout << "ok" << endl;
//						cout << "> " << msg << "" << endl;
				//
//						cout << "Sending Message ... " << flush;
//						msg += EOM;
//						n = con->send(msg.data(), msg.size());
//						if (n > 0) {
//							cout << "ok" << endl;
//						} else {
//							cout << "failed" << endl;
//						}
//					} else {
//						cout << "failed" << endl;
//					}
//				cout << "Closing Connection ... " << flush;
//				delete con;
//				cout << "ok" << endl;
			} else {
//				cout << "failed" << endl;

			}
//			} else {
//				cout << "failed" << endl;
//			}
		} // end while
	} catch (const runtime_error& error) {
		cout << "failed: " << error.what() << endl;
	}
	return 1;
}

// EOF

