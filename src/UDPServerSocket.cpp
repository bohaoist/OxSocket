#include <UDPServerSocket.h>

UDPServerSocket::UDPServerSocket(const unsigned port) {

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE; // use my IP

	const unsigned int digits = (0 < port ? (int) log10((double) port) + 1 : 1);
	char cport[digits + 1]; // add one
	int n = (sprintf(cport, "%d", port));
	if (0 > n) {
		throw std::runtime_error("UDPServerSocket::sprintf() failed");
	}

	if ((rv = getaddrinfo(NULL, cport, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		throw std::runtime_error("UDPServerSocket::getaddrinfo() failed");
	}

	// loop through all the results and bind to the first we can
	for (p = servinfo; p != NULL; p = p->ai_next) {
		if ((ufds.fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol))
				== -1) {
			perror("UDPServerSocket::socket() failed");
			continue;
		}

		if (bind(ufds.fd, p->ai_addr, p->ai_addrlen) == -1) {
			close(ufds.fd);
			perror("UDPServerSocket::bind() failed");
			continue;
		}

		break;
	}

	if (p == NULL) {
		throw std::runtime_error("UDPServerSocket::bind() failed");
	}

}

UDPServerSocket::~UDPServerSocket() {
}
