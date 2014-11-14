#ifndef FDEVENTHANDLER_H_
#define FDEVENTHANDLER_H_

#include <sys/epoll.h>
#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <unistd.h>



namespace OxSocket {

using namespace std;

class FdEventHandler {
private:
	int efd;
	int i,n;
	unsigned int maxevents;
	epoll_event event;
	epoll_event *events;
public:
	FdEventHandler(const unsigned int = 64);
	virtual ~FdEventHandler();
	int addFd(int);
	int delFd(int);
	int wait();
	epoll_event getEvent(int n);

};

}

#endif
