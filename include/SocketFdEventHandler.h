#ifndef SOCKETFDEVENTHANDLER_H_
#define SOCKETFDEVENTHANDLER_H_

#include <sys/epoll.h>
#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <unistd.h>
#include <SocketFd.h>
#include <FdEventHandler.h>


namespace OxSocket {

using namespace std;

class SocketFdEventHandler: public FdEventHandler {
protected:
	int iter,last_wait_value;
public:
	std::map<int,SocketFd*> evtsocks;
	SocketFdEventHandler(const unsigned int maxevents = 512);
	virtual ~SocketFdEventHandler();
	int add(SocketFd*);
	int del(SocketFd*);
	void wait2();
	SocketFd* getNextEvent();

};

}

#endif
