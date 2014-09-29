#ifndef CLIENTSOCKET_H_
#define CLIENTSOCKET_H_

#include <Connection.h>

class ClientSocket {
protected:
	ClientSocket();
public:
	virtual ~ClientSocket();
	virtual Connection* connect() = 0;
};

#endif
