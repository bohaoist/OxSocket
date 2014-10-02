#include <TCPClientSocket.h>

TCPClientSocket::TCPClientSocket(const char* host, const unsigned iport) {

	const unsigned int nb_digits = (
			0 < iport ? (int) log10((double) iport) + 1 : 1);
	char port[nb_digits + 1]; // add one
	int n = (sprintf(port, "%d", iport));
	if (0 > n) {
		const char *msg = "TCPClientSocket::sprintf() failed";
#ifdef DEBUG
		perror(msg);
#endif
		throw std::runtime_error(msg);
	}

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((rv = getaddrinfo(host, port, &hints, &servinfo)) != 0) {
//		freeaddrinfo(servinfo); // all done with this structure
#ifdef DEBUG
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
#endif
		throw std::runtime_error("TCPClientSocket::getaddrinfo() failed");
	}

	// loop through all the results and connect to the first we can
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((ufds.fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))
				== -1) {
#ifdef DEBUG
			perror("TCPClientSocket::socket() failed");
#endif
			continue;
		}

		if (::connect(ufds.fd, p->ai_addr, p->ai_addrlen) == -1) {
#ifdef DEBUG
			perror("TCPClientSocket::connect() failed");
#endif
			close(ufds.fd);
			continue;
		}

		break;
	}

	if (p == NULL) {
//		freeaddrinfo(servinfo); // all done with this structure
		throw std::runtime_error("TCPClientSocket() failed");
	}

	char s[INET6_ADDRSTRLEN];
	inet_ntop(p->ai_family, get_in_addr((sockaddr *) p->ai_addr), s, sizeof s);
	targetaddr = s;

//	freeaddrinfo(servinfo); // all done with this structure
}

TCPClientSocket::~TCPClientSocket() {

}
