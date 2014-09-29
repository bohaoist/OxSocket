/*
 * UNIXServerSocket.cpp
 *
 *  Created on: Sep 29, 2014
 *      Author: inbre001
 */

#include "UNIXServerSocket.h"

UNIXServerSocket::UNIXServerSocket(const char* path) :
		UNIXSocket(path) {

	unlink(local.sun_path);

	if (::bind(sockfd, (struct sockaddr *) &local, this->cli_addrlen) == -1) {
		perror("bind");
//		exit(1);
	}

	cli_addrlen = sizeof(local);

	if (::listen(sockfd, 5) == -1) {
		perror("listen");
//		exit(1);
	}

}

UNIXServerSocket::~UNIXServerSocket() {
}

Connection* UNIXServerSocket::accept() {
	const int newsfd = ::accept(sockfd, (struct sockaddr *) &local,
			&cli_addrlen);

	if (0 > newsfd) {
//		::perror("ServerSocket::accept() failed");
		return (NULL);
	}

	return (new Connection(newsfd));
}
