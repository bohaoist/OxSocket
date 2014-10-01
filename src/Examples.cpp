#include <iostream> /* cout */
#include <Socket.h> /* TCP/UNIXClientSocket, Connection */
#include <string>   /* string */

void stream_server(ServerSocket&);

const static char EOM = '\n';

#define DEFAULTPORT 1234
#define DEFAULTMSG  "Hello World"
#define DEFAULTUNIX "echo_socket"
#define DEFAULTSERVERADDR "127.0.0.1"
#define NOTINTERACTIV

void tcp_server() {
	unsigned int port = DEFAULTPORT;
#ifndef NOTINTERACTIV
	do {
		std::cout << "Enter Server Port (1024 - 9999) : ";
		std::cin >> port;
		if (port > 1024 and port < 9999) {
			break;
		}
		std::cout << "invalid port" << std::endl;
	}while (true);
#endif
	TCPServerSocket sock(port);

	stream_server(sock);
}

void unix_server() {
	std::string file = DEFAULTUNIX;
#ifndef NOTINTERACTIV
	std::cout << "Enter UNIX Socket Filename: ";
	std::cin >> file;
#endif
	UNIXServerSocket sock(file.c_str());

	stream_server(sock);
}
void udp_server() {
	unsigned int port = DEFAULTPORT;
#ifndef NOTINTERACTIV
	do {
		std::cout << "Enter Server Port (1024 - 9999) : ";
		std::cin >> port;
		if (port > 1024 and port < 9999) {
			break;
		}
		std::cout << "invalid port" << std::endl;
	}while (true);
#endif
	char buf[255];
	std::string msg = "";

	UDPServerSocket udpsock(port);

	int n = udpsock.recv(buf, sizeof(buf));

	std::cout << " got #Bytes: " << n << std::endl;
	if (n > 0) {
		msg = std::string(buf, n);
		std::cout << "Got Message: '" << msg << "'" << std::endl;
	}
	udpsock.send(buf, n);

}

void stream_server(ServerSocket &sock) {

	Connection *con = sock.accept();

	if (NULL != con) {
		char buf = '-';
		int n = 0, sum = 0;
		std::string msg = "";
		con->setTimeout(3, 0); // we will wait 3 seconds untill we timeout ...
		// if no timeout is set the connection will close when the client disconnects
		bool okdokie = false;
		while (0 < (n = con->recv(&buf, sizeof(buf)))) {
			if (buf == EOM) {
				okdokie = true;
				break;
			}
			sum += n;
			msg += buf;
		}

		if (n > 0 && okdokie) {
			std::cout << "Got Message: '" << msg << "'" << std::endl;

			n = con->send(msg.data(), msg.size());
			if (n < 0) {
				std::cout << "send failed" << std::endl;
			}
		} else {
			std::cout << "error on recv" << std::endl;
		}
		delete con;
	} else {
		std::cout << "invalid Connection on accept" << std::endl;
	}
}

void stream_client(Connection *con) {

	std::string msg = DEFAULTMSG;

#ifndef NOTINTERACTIV
	std::cout << "Enter Message: ";
	std::cin >> msg;
#endif

	if (NULL != con) {
		int nbytes = 0;

		msg += EOM;
		if (0 < (nbytes = con->send(msg.data(), msg.size()))) {

			int sum = 0;

			char buf = '\0';
			msg = "";

			while (0 < (nbytes = con->recv(&buf, sizeof(buf)))) {
				if (buf == EOM) {
					break;
				}
				sum += nbytes;
				msg += buf;
			}

			std::cout << "Got Message from Server: '" << msg << "'"
					<< std::endl;

		} else {
			std::cout << "send failed " << std::endl;
		}
	} else {
		std::cout << "invalid Connection on connect" << std::endl;
	}

}

void unix_client() {
	std::string file = DEFAULTUNIX;
#ifndef NOTINTERACTIV
	std::cout << "Enter UNIX Socket Filename: ";
	std::cin >> file;
#endif
	UNIXClientSocket sock(file.c_str());

	stream_client(&sock);
}

void tcp_client() {
	unsigned int port = DEFAULTPORT;
	std::string serveraddr = DEFAULTSERVERADDR;
#ifndef NOTINTERACTIV
	do {
		std::cout << "Enter Server Port (1024 - 9999) : ";
		std::cin >> port;
		if (port > 1024 and port < 9999) {
			break;
		}
		std::cout << "invalid port" << std::endl;
	}while (true);

	std::cout << "Enter Server IP/Addr (127.0.0.1): ";
	std::cin >> serveraddr;
#endif

	TCPClientSocket sock(serveraddr.c_str(), port);

	stream_client(&sock);
}

void udp_client() {

	unsigned int port = DEFAULTPORT;
	std::string serveraddr = DEFAULTSERVERADDR;
	std::string msg = DEFAULTMSG;

#ifndef NOTINTERACTIV
	do {
		std::cout << "Enter Server Port (1024 - 9999) : ";
		std::cin >> port;
		if (port > 1024 and port < 9999) {
			break;
		}
		std::cout << "invalid port" << std::endl;
	}while (true);

	std::cout << "Enter Server IP/Addr (127.0.0.1): ";
	std::cin >> serveraddr;

	std::cout << "Enter Message: ";
	std::cin >> msg;
#endif

	UDPClientSocket udpsock(port, serveraddr.c_str());
	char buf[255];
	udpsock.send(msg.c_str(), msg.size());

	int n = udpsock.recv(buf, sizeof(buf));
	msg = std::string(buf, n);
	std::cout << "Got Message: '" << msg << "'" << std::endl;

}

int main(int argc, char* argv[]) {

	char re1 = '\0';
	char re2 = '\0';
#ifndef NOTINTERACTIV

	do {
		std::cout << "Start (s)erver or (c)lient (s/c): " << std::endl;
		std::cin >> re1;
		if (std::string::npos != std::string("sc").find(re1)) {
			break;
		}
		std::cout << "invalid choice" << std::endl;
	}while (true);

	do {
		std::cout << "which type? (t)cp, (u)dp, uni(x)? (t/u/x)" << std::endl;
		std::cin >> re2;
		if (std::string::npos != std::string("tux").find(re2)) {
			break;
		}
		std::cout << "invalid choice" << std::endl;
	}while (true);
#else
	if (argc != 3) {
		std::cout << "usage: " << argv[0] << " [sc] [tux]" << std::endl;
		std::cout << "All Examples:" << std::endl;
		std::cout << "	 TCP Server " << argv[0] << " s t" << std::endl;
		std::cout << "	 TCP Client " << argv[0] << " c t" << std::endl;
		std::cout << "	 UDP Server " << argv[0] << " s u" << std::endl;
		std::cout << "	 UDP Client " << argv[0] << " c u" << std::endl;
		std::cout << "	UNIX Server " << argv[0] << " s x" << std::endl;
		std::cout << "	UNIX Client " << argv[0] << " c x" << std::endl;
		std::cout << std::endl;
		return 1;
	}
	re1 = argv[1][0];
	re2 = argv[2][0];
	std::cout << "re1: " << re1 << std::endl;
	std::cout << "re2: " << re2 << std::endl;
#endif
	///

	if (re1 == 's') {
		switch (re2) {
		case 't':
			tcp_server();
			break;
		case 'u':
			udp_server();
			break;
		case 'x':
			unix_server();
			break;
		}
	} else if (re1 == 'c') {
		switch (re2) {
		case 't':
			tcp_client();
			break;
		case 'u':
			udp_client();
			break;
		case 'x':
			unix_client();
			break;
		}
	}

	return 0;
}
