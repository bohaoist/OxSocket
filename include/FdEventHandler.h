#ifndef FDEVENTHANDLER_H_
#define FDEVENTHANDLER_H_

#include <sys/epoll.h>
#include <cstdio>
#include <cstdlib>
#include <stdexcept>

namespace OxSocket {

class FdEventHandler {
private:
	int i,n;
	const unsigned int maxevents;
	const int efd;
	epoll_event event;
	epoll_event *events;
public:
	FdEventHandler(const unsigned int = 64);
	virtual ~FdEventHandler();
	int addFd(int);
	int delFd(int);
	int check();
};

}

#endif
