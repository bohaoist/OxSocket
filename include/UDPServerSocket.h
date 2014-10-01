#ifndef UDPSERVERSOCKET_H_
#define UDPSERVERSOCKET_H_

#include <UDPSocket.h>

class UDPServerSocket: public UDPSocket {
public:
	UDPServerSocket(const unsigned);
	virtual ~UDPServerSocket();
};

#endif
