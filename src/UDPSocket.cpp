#include <UDPSocket.h>
namespace OxSocket {
UDPSocket::UDPSocket() {
	p = 0;
	servinfo = 0;
	rv = 0;
	numbytes = 0;
	addr_len = 0;
}

UDPSocket::~UDPSocket() {
}

//int UDPSocket::send(const char* buf, const unsigned int size) {
////	sum = (sendto(sfd, (void*) buf, size, 0, p->ai_addr, p->ai_addrlen
//////			(sockaddr *) &their_addr, sizeof(their_addr)
////			));
////	char s[INET6_ADDRSTRLEN];
////	inet_ntop(p->ai_family, get_in_addr((sockaddr *) p->ai_addr), s, sizeof(s));
////	targetaddr = s;
////
////	printf("from IP address %s\n",
////			inet_ntop(their_addr.ss_family,
////					get_in_addr((sockaddr *) &their_addr), s, sizeof s));
////	return sum;
//	numbytes = sendto(sfd, (void*) buf, size, 0, p->ai_addr, p->ai_addrlen);
//	targetaddr = inet_ntop(their_addr.ss_family,
//			get_in_addr((struct sockaddr *) p->ai_addr), s, sizeof s);
//	return numbytes;
//}

//int UDPSocket::recv(char* buf, const unsigned int size) {
//
////	socklen_t fromlen = sizeof(their_addr);
//
////	sum = (recvfrom(sfd, (void*) buf, size, 0, p->ai_addr, &p->ai_addrlen));
//
////	sum = recvfrom(sfd, (void*) buf, size, 0, (sockaddr*) &their_addr,
////			&fromlen);
//
////	printf("recv()'d %d bytes of data in buf\n", byte_count);
////	char s[INET_ADDRSTRLEN];
////	inet_ntop(AF_INET, get_in_addr((sockaddr *) &p->ai_addr), s, sizeof(s));
////	targetaddr = s;
//
////	printf("from IP address %s\n",
////			inet_ntop(p->ai_addr->sa_family,
////					get_in_addr((sockaddr *) &p->ai_addr), s, sizeof s));
//	numbytes = recvfrom(sfd, (void*) buf, size, 0,
//			(struct sockaddr *) &their_addr, &addr_len);
//	targetaddr = inet_ntop(their_addr.ss_family,
//			get_in_addr((struct sockaddr *) &their_addr), s, sizeof s);
//	return numbytes;
//}

}
