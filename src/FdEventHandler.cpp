#include <FdEventHandler.h>

namespace OxSocket {

FdEventHandler::FdEventHandler(const unsigned int _maxevents) :
		efd(epoll_create1(0)), maxevents(_maxevents), i(0), n(0) {
	if (-1 == efd) {
		const char *msg = "epoll_create";
		perror(msg);
		throw std::runtime_error(msg);
	}
	/* Buffer where events are returned */
//	events = (epoll_event*) calloc(maxevents, sizeof(event));
	events = new epoll_event[maxevents]();

}

int FdEventHandler::check() {
	n = epoll_wait(efd, events, maxevents, -1);
	if (n == -1) {
		perror("epoll_wait");
	}
	return n;
}

FdEventHandler::~FdEventHandler() {
	//free(events);
	delete[] events;

}

int FdEventHandler::addFd(int infd) {
	event.data.fd = infd;
	event.events = EPOLLIN | EPOLLET;
	int s = epoll_ctl(efd, EPOLL_CTL_ADD, infd, &event);
	if (-1 == s) {
		perror("epoll_ctl ADD");
	}
	return s;
}

int FdEventHandler::delFd(int infd) {
	int s = epoll_ctl(efd, EPOLL_CTL_DEL, infd, &event);
	if (-1 == s) {
		perror("epoll_ctl DEL");
	}
	return s;
}

} /* namespace OxSocket */
