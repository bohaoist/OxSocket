/*
 * UNIXClientSocket.cpp
 *
 *  Created on: Sep 29, 2014
 *      Author: inbre001
 */

#include "UNIXClientSocket.h"

UNIXClientSocket::UNIXClientSocket(const char* path) :
		UNIXSocket(path) {

}

UNIXClientSocket::~UNIXClientSocket() {
}

Connection* UNIXClientSocket::connect() {

	if (0 != ::connect(sockfd, (struct sockaddr *) &local, this->cli_addrlen)) {
		perror("Socket::connect() failed");
		return NULL;
	}
	return (new Connection(sockfd));
}
