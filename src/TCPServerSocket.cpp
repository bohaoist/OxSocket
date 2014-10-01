#include <TCPServerSocket.h>

TCPServerSocket::TCPServerSocket(const unsigned iport) {

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; // use my IP

	const unsigned int nb_digits = (
			0 < iport ? (int) log10((double) iport) + 1 : 1);
	char port[nb_digits + 1]; // add one
	int n = (::sprintf(port, "%d", iport));
	if (0 > n) {
		const char* msg = "TCPServerSocket::sprintf() failed";
		::perror(msg);
		throw std::runtime_error(msg);
	}

	if ((rv = ::getaddrinfo(NULL, port, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		throw std::runtime_error("TCPServerSocket::getaddrinfo() failed");
	}

	// loop through all the results and bind to the first we can
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((ufds.fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))
				== -1) {
			perror("TCPServerSocket::socket() failed");
			continue;
		}

		int yes = 1; // Addr allready in use message
		if (setsockopt(ufds.fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))
				== -1) {
			const char* msg = "TCPServerSocket::setsockopt() failed";
			perror(msg);
			throw std::runtime_error(msg);
		}

		if (bind(ufds.fd, p->ai_addr, p->ai_addrlen) == -1) {
			close(ufds.fd);
			perror("TCPServerSocket::bind() failed");
			continue;
		}

		break;
	}

	if (p == NULL) {
		throw std::runtime_error("TCPServerSocket::bind() failed");
	}

	freeaddrinfo(servinfo); // all done with this structure

	if (::listen(ufds.fd, 10) == -1) {
		const char *msg = "TCPServerSocket::listen() failed";
		perror(msg);
		throw std::runtime_error(msg);
	}

}

TCPServerSocket::~TCPServerSocket() {
}

Connection* TCPServerSocket::accept() {

	slen = sizeof their_addr;

	const int tmp = ::accept(ufds.fd, (sockaddr*) &their_addr, &slen);

	if (-1 == tmp) {
		::perror("TCPServerSocket::accept() failed");
		return (NULL);
	}

	return (new Connection(tmp));
}
