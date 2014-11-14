#include <iostream>
#include <string>
#include <OxSocket.h>

using namespace std;
using namespace OxSocket;

int TCPClient_main(int argc, char* argv[]) {

	const char EOM = '\n';
	char buf = '\0';

	string msg = "Hello World";

	TCPClientSocket con(argv[1], atoi(argv[2]));
	con.setTimeout(5, 0);

	msg += EOM;
	con.send(msg.data(), msg.size());

	while (0 < con.recv(&buf, sizeof(buf)) and (buf != EOM)) {
		cout << buf;
	}
	cout << endl;

	return 0;
}

int TCPServer_main(int argc, char* argv[]) {

	const char EOM = '\n';
	char buf = '\0';
	string msg = "";
	Connection * con = NULL;
	TCPServerSocket sock(atoi(argv[1]));

	while (true) {
		con = sock.accept();
		con->setTimeout(3, 0);

		msg = "";
		while (0 < con->recv(&buf, sizeof(buf)) and EOM != buf) {
			msg += buf;
		}
		cout << msg << endl;
		msg += EOM;
		con->send(msg.data(), msg.size());
		delete con;
	}

	return 1;
}

int UDPClient_main(int argc, char* argv[]) {

	char buf[255];
	int bsize = 0;
	std::string msg = "Hello World";

	OxSocket::UDPClientSocket sock(argv[1], atoi(argv[2]));
	sock.send(msg.data(), msg.size());
	bsize = sock.recv(buf, sizeof(buf));
	std::cout << std::string(buf, bsize) << std::endl;

	return 0;
}

int UDPServer_main(int argc, char* argv[]) {

	OxSocket::UDPServerSocket sock(atoi(argv[1]));
	char buf[255];
	int bsize = 0;

	while (true) {
		bsize = sock.recv(buf, sizeof(buf));
		std::cout << std::string(buf, bsize) << std::endl;
		sock.send(buf, bsize);
	}
	return 1;
}

