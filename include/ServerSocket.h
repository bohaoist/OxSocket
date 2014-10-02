#ifndef SERVERSOCKET_H_
#define SERVERSOCKET_H_

#include <Connection.h>

/**
 * \brief Not instanziable BaseClass for all ServerSocket Classes
 * \details Not instanziable BaseClass for all ServerSocket Classes.
 *          Must provides an accept() function that will return a Connection Object
 */
class ServerSocket {
protected:
	ServerSocket();
public:
	virtual ~ServerSocket();
	virtual Connection* accept() = 0;
};

#endif
