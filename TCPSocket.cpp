#include "TCPSocket.h"

TCPSocket::~TCPSocket() {
}

//bool TCPSocket::isValidIpAddress(const char *ipAddress) {
//	struct sockaddr_in sa;
//	int result = inet_pton(AF_INET, ipAddress, &(sa.sin_addr));
//	return result != 0;
//}

TCPSocket::TCPSocket(const unsigned portno, const char *hostaddr) :
		/*create an endpoint for communication*/
		SocketFd(::socket(AF_INET, SOCK_STREAM, 0)) {

	//printf("TCPSocket()\n");

	hostent * record = NULL;
	if (NULL != hostaddr) {
		record = gethostbyname(hostaddr);
		if (NULL == record) {
			//printf("%s is unavailable\n", hostaddr);
			perror("TCPSocket::gethostbyname() failed");
			throw Exception(
					"Failed to construct TCPSocket :: gethostbyname() failed");
		}
		//address = (in_addr *) record->h_addr;
		//std::string ip_address = inet_ntoa(*address);
		//printf("%s\n", ip_address.c_str());
	}
	//printf("memset\n");
	::memset((char *) &(serv_addr), '\0', sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portno);
	serv_addr.sin_addr.s_addr =
			(NULL == hostaddr) ? INADDR_ANY : *(in_addr_t*) record->h_addr;
}

