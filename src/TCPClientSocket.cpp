#include <TCPClientSocket.h>

namespace OxSocket {

TCPClientSocket::TCPClientSocket(const std::string host, const unsigned iport) {

	std::string errmsg = "";

	targetaddr = host;

	const unsigned nb_digits = (
			0 < iport ? (int) ::log10((double) iport) + 1 : 1);
	char port[nb_digits + 1]; // add one
	int n = (::sprintf(port, "%d", iport));
	if (0 > n) {
		errmsg = "TCPClientSocket::sprintf() failed :: ";
		errmsg += ::strerror(errno);
		throw std::runtime_error(errmsg);
	}

	::memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if (0 != (rv = ::getaddrinfo(host.c_str(), port, &hints, &servinfo))) {
		errmsg = "TCPClientSocket::getaddrinfo(" + host + "," + port
				+ ") failed :: ";
		errmsg += ::gai_strerror(rv);
		throw std::runtime_error(errmsg);
	}

	// loop through all the results and connect to the first we can
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if (-1
				== (sfd = ::socket(p->ai_family, p->ai_socktype, p->ai_protocol))) {
#ifdef DEBUG
			::perror("TCPClientSocket::socket() failed");
#endif
			continue;
		}

		if (-1 == ::connect(sfd, p->ai_addr, p->ai_addrlen)) {
#ifdef DEBUG
			::perror("TCPClientSocket::connect() failed");
#endif
			::close(sfd);
			continue;
		}

		break;
	}

	if (p == NULL) {
		errmsg = "TCPClientSocket() failed";
		throw std::runtime_error(errmsg);
	}

}

TCPClientSocket::~TCPClientSocket() {

}

} // end namespace
