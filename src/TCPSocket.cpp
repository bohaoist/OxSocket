#include "TCPSocket.h"

TCPSocket::~TCPSocket() {
}

char* TCPSocket::getServerAddr() {
	return (::inet_ntoa(serv_addr.sin_addr));
}

//bool TCPSocket::isValidIpAddress(const char *ipAddress) {
//	struct sockaddr_in sa;
//	int result = inet_pton(AF_INET, ipAddress, &(sa.sin_addr));
//	return result != 0;
//}

TCPSocket::TCPSocket(const unsigned portno, const char *hostaddr) :
		SocketFd(::socket(AF_INET, SOCK_STREAM, 0)) {

	this->serv_addrlen = 0;

	hostent * record = NULL;
	if (NULL != hostaddr) {
		record = gethostbyname(hostaddr);
		if (NULL == record) {
			throw std::runtime_error(
					"Failed to construct TCPSocket :: gethostbyname() failed");
		}
	}

	::memset((char *) &(serv_addr), '\0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr = (
			(NULL == hostaddr) ? INADDR_ANY : *(in_addr_t*) record->h_addr);
		}

