/*
 * UNIXClientSocket.h
 *
 *  Created on: Sep 29, 2014
 *      Author: inbre001
 */

#ifndef UNIXCLIENTSOCKET_H_
#define UNIXCLIENTSOCKET_H_

#include <UNIXSocket.h>
#include <Connection.h>

class UNIXClientSocket: public UNIXSocket {
public:
	UNIXClientSocket(const char* path);
	virtual ~UNIXClientSocket();
	Connection* connect();
};

#endif /* UNIXCLIENTSOCKET_H_ */
