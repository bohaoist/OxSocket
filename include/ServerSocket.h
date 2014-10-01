#ifndef SERVERSOCKET_H_
#define SERVERSOCKET_H_

#include <Connection.h>

class ServerSocket {
protected:
	ServerSocket();
public:
	virtual ~ServerSocket();
	virtual Connection* accept() = 0;
};

#endif
