#ifndef ACCEPTSOCKET_H_
#define ACCEPTSOCKET_H_

#include <Connection.h>
#include <SocketFd.h>

/**
 * \brief Virtual Base
 */
class AcceptSocket: public SocketFd {
protected:
	AcceptSocket();
public:
	virtual ~AcceptSocket();
	virtual Connection* accept() = 0;
};

#endif
