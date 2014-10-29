#include <TCPServerSocket.h>
namespace OxSocket {
TCPServerSocket::TCPServerSocket(const unsigned port) {

	std::string errmsg = "";

	::memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; // use my IP

	const unsigned nb_digits = (0 < port ? (int) ::log10((double) port) + 1 : 1);
	char cport[nb_digits + 1]; // add one
	int n = (::sprintf(cport, "%d", port));
	if (0 > n) {
		errmsg = "TCPServerSocket::sprintf() failed :: ";
		errmsg += ::strerror(errno);
		throw std::runtime_error(errmsg);
	}

	if (0 != (rv = ::getaddrinfo(NULL, cport, &hints, &servinfo))) {
		errmsg = "TCPServerSocket::getaddrinfo() failed :: ";
		errmsg += ::gai_strerror(rv);
		throw std::runtime_error(errmsg);
	}

	// loop through all the results and bind to the first we can
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if (-1
				== (sfd = ::socket(p->ai_family, p->ai_socktype, p->ai_protocol))) {
#ifdef DEBUG
			::perror("TCPServerSocket::socket() failed");
#endif
			continue;
		}

		int yes = 1; // Addr allready in use message
		if (-1
				== ::setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &yes,
						sizeof(int))) {
			errmsg = "TCPServerSocket::setsockopt() failed :: ";
			errmsg += ::strerror(errno);
			throw std::runtime_error(errmsg);
		}

		if (-1 == ::bind(sfd, p->ai_addr, p->ai_addrlen)) {
#ifdef DEBUG
			::perror("TCPServerSocket::bind() failed");
#endif
			::close(sfd);
			continue;
		}

		break;
	}

	if (NULL == p) {
		errmsg = "TCPServerSocket() failed";
		throw std::runtime_error(errmsg);
	}

	if (-1 == ::listen(sfd, 10)) {
		errmsg = "TCPServerSocket::listen() failed :: ";
		errmsg += ::strerror(errno);
		throw std::runtime_error(errmsg);
	}

}

TCPServerSocket::~TCPServerSocket() {
}

Connection* TCPServerSocket::accept() {

	slen = sizeof their_addr;

	const int tmp = ::accept(sfd, (sockaddr*) &their_addr, &slen);

	if (-1 == tmp) {
#ifdef DEBUG
		::perror("TCPServerSocket::accept() failed");
#endif
		return (NULL);
	}

	char s[INET6_ADDRSTRLEN];
	::inet_ntop(their_addr.ss_family, get_in_addr((sockaddr *) &their_addr), s,
			sizeof(s));

	return (new Connection(tmp, s));
}
}
