#include <TCPSocket.h>

TCPSocket::~TCPSocket() {
}

char* TCPSocket::getServerAddr() {
	return (::inet_ntoa(serv_addr.sin_addr));
}

//bool TCPSocket::isValidIpAddress(const char *ipAddress) {
//	sockaddr_in sa;
//	int result = inet_pton(AF_INET, ipAddress, &(sa.sin_addr));
//	return result != 0;
//}

TCPSocket::TCPSocket(const unsigned portno, const char *addr):
		Common_tcp_unix(sfd,AF_INET)
		{
//	sfd = ::socket(AF_INET, SOCK_STREAM, 0);
//	if (sfd == -1) {
//		throw std::runtime_error("TCPSocket::socket() failed");
//	}

	this->saddrlen = 0;

	hostent * rec = NULL;
	if (NULL != addr) {
		rec = gethostbyname(addr);
		if (NULL == rec) {
			throw std::runtime_error("TCPSocket::gethostbyname() failed");
		}
	}

	::memset((char *) &(serv_addr), '\0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = (::htons(portno));
	serv_addr.sin_addr.s_addr = //
			((NULL == addr) ? INADDR_ANY : *(in_addr_t*) rec->h_addr);

		}

