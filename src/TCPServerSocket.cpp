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
#ifdef DEBUG
		::perror(msg);
#endif
		throw std::runtime_error(msg);
	}

	if ((rv = ::getaddrinfo(NULL, port, &hints, &servinfo)) != 0) {
#ifdef DEBUG
		fprintf(stderr, "TCPServerSocket::getaddrinfo: %s\n", gai_strerror(rv));
#endif
		throw std::runtime_error("TCPServerSocket::getaddrinfo() failed");
	}

	// loop through all the results and bind to the first we can
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((ufds.fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))
				== -1) {
#ifdef DEBUG
			perror("TCPServerSocket::socket() failed");
#endif
			continue;
		}

		int yes = 1; // Addr allready in use message
		if (setsockopt(ufds.fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))
				== -1) {
			const char* msg = "TCPServerSocket::setsockopt() failed";
#ifdef DEBUG
			perror(msg);
#endif
			throw std::runtime_error(msg);
		}

		if (bind(ufds.fd, p->ai_addr, p->ai_addrlen) == -1) {
#ifdef DEBUG
			perror("TCPServerSocket::bind() failed");
#endif
			close(ufds.fd);
			continue;
		}

		break;
	}

	freeaddrinfo(servinfo); // all done with this structure
	if (p == NULL) {
		throw std::runtime_error("TCPServerSocket() failed");
	}

	if (::listen(ufds.fd, 10) == -1) {
		const char *msg = "TCPServerSocket::listen() failed";
#ifdef DEBUG
		perror(msg);
#endif
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

	char s[INET6_ADDRSTRLEN];
	inet_ntop(their_addr.ss_family, get_in_addr((sockaddr *) &their_addr), s,
			sizeof(s));

	return (new Connection(tmp, s));
}
