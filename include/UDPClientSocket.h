#ifndef UDPCLIENTSOCKET_H_
#define UDPCLIENTSOCKET_H_

#include <UDPSocket.h>

class UDPClientSocket: public UDPSocket {
public:
	UDPClientSocket(const unsigned int, const char*);
	virtual ~UDPClientSocket();
};

#endif
