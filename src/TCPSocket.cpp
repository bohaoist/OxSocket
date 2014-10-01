#include <TCPSocket.h>

TCPSocket::~TCPSocket() {
}

char* TCPSocket::getLocalAddr() {
	return (::inet_ntoa(si_me.sin_addr));
}

char* TCPSocket::getRemotAddr() {
	return (::inet_ntoa(si_other.sin_addr));
}

TCPSocket::TCPSocket(const unsigned portno, const char *addr) :
		Common_tcp_unix(ufds.fd, AF_INET) {

	hostent * rec = NULL;
	if (NULL != addr) {
		rec = gethostbyname(addr);
		if (NULL == rec) {
			throw std::runtime_error("TCPSocket::gethostbyname() failed");
		}
	}

	::memset((char *) &(si_me), '\0', sizeof(si_me));
	si_me.sin_family = AF_INET;
	si_me.sin_port = (::htons(portno));
	if (NULL == addr) {
		si_me.sin_addr.s_addr = INADDR_ANY;
	} else {
		si_me.sin_addr.s_addr = *(in_addr_t*) rec->h_addr;
	}
}

