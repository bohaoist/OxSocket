#include <iostream> /* cout */
#include <Socket.h> /* TCP/UNIXClientSocket, Connection */
#include <string>   /* string */

const static char EOM = '\n';

void stream_server(ServerSocket &sock) {

	Connection *con = sock.accept();

	if (NULL != con) {
		char buf = '-';
		int n = 0, sum = 0;
		std::string msg = "";
		con->setTimeout(5, 0); // we will wait 3 seconds untill we timeout ...
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
			std::cout << "Got Message from Client: " << msg << std::endl;

			if (0 > (n = con->send(msg.data(), msg.size()))) {
				std::cerr << "send failed " << std::endl;
			}
		} else {
			std::cerr << "error on recv" << std::endl;
		}
		delete con;
	} else {
		std::cerr << "invalid Connection on accept" << std::endl;
	}
}

void tcp_server() {
	unsigned int port = 0;
	do {
		std::cout << "Enter Server Port (1024 - 9999) : ";
		std::cin >> port;
		if (port > 1024 and port < 9999) {
			break;
		}
		std::cerr << "invalid port" << std::endl;
	} while (true);

	TCPServerSocket sock(port);

	stream_server(sock);
}

void unix_server() {
	std::string file = "tmp_socket";

	std::cout << "Enter UNIX Socket Filename: ";
	std::cin >> file;

	UNIXServerSocket sock(file.c_str());

	stream_server(sock);
}


void stream_client(ClientSocket &sock) {

	std::string msg = "";
	std::cout << "Enter Message: ";
	std::cin >> msg;

	Connection *con = sock.connect();
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
			std::cerr << "send failed " << std::endl;
		}
		// remove Connection
		delete con;
	} else {
		std::cerr << "invalid Connection on connect" << std::endl;
	}

}

void unix_client() {
	std::string file = "tmp_socket";

	std::cout << "Enter UNIX Socket Filename: ";
	std::cin >> file;

	UNIXClientSocket sock(file.c_str());

	stream_client(sock);
}

void tcp_client() {
	unsigned int port = 0;
	std::string serveraddr = "";

	do {
		std::cout << "Enter Server Port (1024 - 9999) : ";
		std::cin >> port;
		if (port > 1024 and port < 9999) {
			break;
		}
		std::cerr << "invalid port" << std::endl;
	} while (true);

	std::cout << "Enter Server IP/Addr (127.0.0.1): ";
	std::cin >> serveraddr;

	TCPClientSocket sock(serveraddr.c_str(), port);

	stream_client(sock);
}

void udp_server() {
	unsigned int port = 1234;
	do {
		std::cout << "Enter Server Port (1024 - 9999) : ";
		std::cin >> port;
		if (port > 1024 and port < 9999) {
			break;
		}
		std::cerr << "invalid port" << std::endl;
	} while (true);

	char buf[255];
	std::string msg = "";

	UDPSocket udpsock(port);

	int n = udpsock.recv(buf, sizeof(buf));
	msg = std::string(buf, n);
	std::cout << "Got Message from Client: " << msg << " (" << n << ")"
			<< std::endl;

	udpsock.send(buf, n);

}

void udp_client() {

	unsigned int port = 1234;
	std::string serveraddr = "127.0.0.1";
	std::string msg = "hello";
	do {
		std::cout << "Enter Server Port (1024 - 9999) : ";
		std::cin >> port;
		if (port > 1024 and port < 9999) {
			break;
		}
		std::cerr << "invalid port" << std::endl;
	} while (true);

	std::cout << "Enter Server IP/Addr (127.0.0.1): ";
	std::cin >> serveraddr;

	std::cout << "Enter Message: ";
	std::cin >> msg;
	UDPSocket udpsock(port, serveraddr.c_str());

	char buf[255];
	udpsock.send(msg.c_str(), msg.size());

	int n = udpsock.recv(buf, sizeof(buf));
	msg = std::string(buf, n);
	std::cout << "Got Message from Server: '" << msg << "'" << std::endl;

}

int main(int, char*[]) {

	char re1 = '\0';
	do {
		std::cout << "Start (s)erver or (c)lient (s/c): " << std::endl;
		std::cin >> re1;
		if (std::string::npos != std::string("sc").find(re1)) {
			break;
		}
		std::cerr << "invalid choice" << std::endl;
	} while (true);

	char re2 = '\0';
	do {
		std::cout << "which type? (t)cp, (u)dp, uni(x)? (t/u/x)" << std::endl;
		std::cin >> re2;
		if (std::string::npos != std::string("tux").find(re2)) {
			break;
		}
		std::cerr << "invalid choice" << std::endl;
	} while (true);

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
