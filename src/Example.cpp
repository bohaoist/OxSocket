#include <iostream> /* cout */
#include <Socket.h> /* TCP/UNIXClientSocket, Connection */
#include <string>   /* string */
#include <sstream>

using namespace std;

/* helper for stream based Sockets */
void stream_server(ServerSocket&);
void stream_client(Connection&);

const static char EOM = '\n';

#define DEFAULTPORT 1234
#define DEFAULTMSGC "Hello here Client"
#define DEFAULTMSGS "Hello here Server"
#define DEFAULTUNIX "echo_socket"
#define DEFAULTSERV "127.0.0.1"

/**
 * \brief Convert a String to a T Object
 * \details This Function tries to convert any string into any Type
 *         the Template Function was called with.
 * \param[in]
 * \return
 **/
template<class T> T str2(const string str) {
	T tmp;
	stringstream ss(str, stringstream::in);
	ss >> tmp;
	return (tmp);
}
/**
 * \brief     Removes trailing Spaces and Tabs
 * \details   Removes trailing Spaces and Tabs
 * \param[in] str String to
 * \return    trimmed String
 * */
string rtrim(const string str) {
	size_t pos = str.find_last_not_of(" \t\n\r");
	if (string::npos == pos) {
		return ("");
	}
	return (str.substr(0, pos + 1));
}

/**
 * \brief     Removes leading Spaces and Tabs
 * \details   Removes leading Spaces and Tabs
 * \param[in] str String to
 * \return    trimmed String
 **/
string ltrim(const string str) {
	size_t pos = str.find_first_not_of(" \t\n\r");
	if (string::npos == pos) {
		return ("");
	}
	return (str.substr(pos));
}

/**
 * \brief     Removes leading and trailing Spaces and Tabs
 * \details   Removes leading and trailing Spaces and Tabs
 * \param[in] str String to
 * \return    trimmed String
 * */
string trim(const string str) {
	return (rtrim(ltrim(str)));
}

void printusage(char* name) {
	cout << "usage: " << name << " [sc] [utx]" << endl;
	cout << endl;
	cout << "	 (u)dp (s)erver: " << name << " s u" << endl;
	cout << "	 (u)dp (c)lient: " << name << " c u" << endl;
	cout << "	 (t)cp (s)erver: " << name << " s t" << endl;
	cout << "	 (t)cp (c)lient: " << name << " c t" << endl;
	cout << "	uni(x) (s)erver: " << name << " s x" << endl;
	cout << "	uni(x) (c)lient: " << name << " c x" << endl;

	cout << "	  (h)ttp client: " << name << " h <url>" << endl;
	cout << "	<url> := www.example.org " << endl;
	cout << endl;
}

int main(int argc, char* argv[]) {

	char re1 = '\0';
	char re2 = '\0';
	if (argc != 3) {
		printusage(argv[0]);
		return 1;
	}
	re1 = argv[1][0];
	re2 = argv[2][0];

	//
	if (re1 == 'h') {
		/**
		 * HTTP Client
		 */
		///--------------------------------------------------
		string server = argv[2];
		TCPClientSocket sock(server.c_str(), 80);

		string msg = "GET / HTTP/1.1\n"
				"Host: " + server + "\n"
				"\n\r";
		sock.send(msg.data(), msg.size());

		string line = "";
		char buf = '\0';
		char pbuf = '\0';
		int n = 0;
		int content_length = 0;

		sock.setTimeout(5, 0);
		while (0 < (n = sock.recv(&buf, sizeof(buf)))) {

			line += buf;

			// RECV BODY
			if (buf == '\r' and pbuf == '\n') {
				char buf2[content_length];
				n = sock.recv(buf2, content_length);
				if (n > 0) {
					msg += string(buf2, n);

				}
				break;
			} else if (buf == '\n') {
				if (string::npos != line.find("Content-Length")) {
					content_length = str2<int>(
							trim(line.substr(line.find(":") + 1)));
				}
				msg += line;
				line = "";

			}
			pbuf = buf;

		}
		// print the entire RESPONSE
		cout << msg << endl;
		cout << endl;
		cout << "HTTP Client finished successfully" << endl;
		///--------------------------------------------------
	} else if (re1 == 's') {
		switch (re2) {
		case 'u': {
			///--------------------------------------------------
			/**
			 *  UDP Server
			 **/
			UDPServerSocket udpsock(DEFAULTPORT);
			char buf[255];
			int n = 0;
			string msg = "";
			while (true) {
				cout << endl;
				cout << "Waiting for incoming Data" << endl;
				n = udpsock.recv(buf, sizeof(buf));
				msg = string(buf, n);
				cout << "Got Message: '" << msg << "'" << endl;
				msg = DEFAULTMSGS;
				cout << "Sending: '" << msg << "'" << endl;
				udpsock.send(msg.data(), msg.size());
			}
			///--------------------------------------------------
		}
			break;
		case 't': {
			///--------------------------------------------------
			/**
			 *  TCP Server
			 **/
			TCPServerSocket sock(DEFAULTPORT);
			stream_server(sock);
			///--------------------------------------------------
		}
			break;
		case 'x': {
			///--------------------------------------------------
			/**
			 * UNIX Server
			 **/
			UNIXServerSocket sock(DEFAULTUNIX);
			stream_server(sock);
			///--------------------------------------------------
		}
			break;
		default:
			printusage(argv[0]);
			cerr << "unknown 2d argument use 't', 'u' or 'x'" << endl;
			return 1;
		}
	} else if (re1 == 'c') {
		switch (re2) {
		case 'u': {
			///--------------------------------------------------
			/**
			 * UDP Client
			 **/
			char buf[255];
			string msg = DEFAULTMSGC;
			int n = 0;
			UDPClientSocket udpsock(DEFAULTSERV, DEFAULTPORT);
			cout << "Sending: '" << msg << "'" << endl;
			udpsock.send(msg.c_str(), msg.size());
			n = udpsock.recv(buf, sizeof(buf));
			msg = string(buf, n);
			cout << "Got Message: '" << msg << "'" << endl;
			///--------------------------------------------------
		}
			break;

		case 't': {
			///--------------------------------------------------
			/**
			 * TCP Client
			 **/
			TCPClientSocket sock(DEFAULTSERV, DEFAULTPORT);
			stream_client(sock);
			///--------------------------------------------------
		}
			break;
		case 'x': {
			///--------------------------------------------------
			/**
			 * UNIX Client
			 **/
			UNIXClientSocket sock(DEFAULTUNIX);
			stream_client(sock);
			///--------------------------------------------------
		}
			break;
		default: {
			printusage(argv[0]);
			cerr << "unknown 2nd argument use 't', 'u' or 'x'" << endl;
			return 1;
		}
			break;
		}
	} else {
		printusage(argv[0]);
		cout << "unknown 1st argument use 's' or 'c'" << endl;
		return 1;
	}

	return 0;
}

/**
 * Accept Connections on ServerSockets 
 * and  sends ans recv some data
 * */
void stream_server(ServerSocket &sock) {

	while (true) {
		cout << endl;
		cout << "Waiting for incoming Connections" << endl;
		Connection *con = sock.accept();

		if (NULL != con) {
			char buf = '-';
			int n = 0;
			string msg = "";

			/*
			 * Tells the Socket Timeout after 3 seconds
			 * just so we wont wait forever for a recv or send
			 * */
			con->setTimeout(3, 0);
			bool ok = false;

			/**
			 *  We recv one Byte at a time
			 *  till we get the End of Message (EOM) Character
			 *  or recv detects an error and return a value less then Zero
			 *
			 *  If you want to recv larger amounts of data make sure
			 *  not to miscalculate. Otherwise recv will block indefinetly
			 *  for the remaining Bytes ... so design your protocol whisely.
			 *
			 **/
			while (0 < (n = con->recv(&buf, sizeof(buf)))) {
				if (buf == EOM) {
					ok = true; // Everything ok
					break;
				}
				msg += buf;
			}

			if (n > 0 and ok) { // iv we got a well terminated message from the Client
				cout << "Got Message: '" << msg << "'" << endl;

				// For the Sake of Echo send it back to the Client
				//
				msg = DEFAULTMSGS;

				// dont forget the append the EOM Sign ...
				cout << "Sending: '" << msg << "'" << endl;
				msg += EOM;
				n = con->send(msg.data(), msg.size());

				// Some Error Checking
				if (n < 0) {
					cout << "send() failed" << endl;
				}
			} else {
				cout << "recv() failed" << endl;
			}

			// Make shure to DELETE the Connection when you are finished
			delete con;

		} else {
			cout << "accept() failed" << endl;
		}
	}

}

/**
 * sends ans recv some data over a Connection
 **/
void stream_client(Connection &con) {

	int n = 0;
	string msg = DEFAULTMSGC;
	cout << "Sending: '" << msg << "'" << endl;

// Append the End of Message Character to the Message
	msg += EOM;

//  Send the Message to the Server
	if (0 < (n = con.send(msg.data(), msg.size()))) {

		char buf = '\0';
		msg = "";
		bool ok = false;

		// We Expect the Server to Send something Back
		/**
		 *  We recv one Byte at a time
		 *  till we get the End of Message (EOM) Character
		 *  or recv detects an error and return a value less then Zero
		 *
		 *  If you want to recv larger amounts of Data make sure
		 *  not to expect to much otherwise recv will block indefinetly
		 *  for the remaining Bytes ... so design your Protocol whisely.
		 *
		 **/
		while (0 < (n = con.recv(&buf, sizeof(buf)))) {
			if (buf == EOM) {
				ok = true;
				break;
			}
			msg += buf;
		}

		if (n > 0 and ok) {
			// The Message we got from the Server
			cout << "Got Message: '" << msg << "'" << endl;

			// some error checking
		} else {
			cout << "recv() failed " << endl;
		}
	} else {
		cout << "send() failed " << endl;
	}
}

// EOF 
