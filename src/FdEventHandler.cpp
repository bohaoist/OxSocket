#include <FdEventHandler.h>

namespace OxSocket {

FdEventHandler::FdEventHandler(const unsigned int _maxevents) {

	efd = epoll_create1(0);
	maxevents = _maxevents;
	rv = 0;
	if (-1 == efd) {
		const char *msg = "epoll_create";
		perror(msg);
		throw std::runtime_error(msg);
	}
	/* Buffer where events are returned */
	events = new epoll_event[maxevents]();

}

bool FdEventHandler::isError(int i) {
	if ((this->getEvent(i).events & EPOLLERR) //
	|| (this->getEvent(i).events & EPOLLHUP) //
			|| (!(this->getEvent(i).events & EPOLLIN))) {
		return true;
	}
	return false;
}

int FdEventHandler::wait() {
	rv = epoll_wait(efd, events, maxevents, -1);
	if (-1 == rv) {
		perror("epoll_wait");
	}
	return rv;
}

FdEventHandler::~FdEventHandler() {
	//free(events);
	delete[] events;
}

int FdEventHandler::addFd(const int infd) {

	event.data.fd = infd;
	event.events = EPOLLIN | EPOLLET;
	rv = epoll_ctl(efd, EPOLL_CTL_ADD, infd, &event);
	if (-1 == rv) {
		perror("epoll_ctl ADD");
	}
	return rv;
}

int FdEventHandler::delFd(int infd) {
	rv = epoll_ctl(efd, EPOLL_CTL_DEL, infd, &event);
	if (-1 == rv) {
		perror("epoll_ctl DEL");
	}
	return rv;
}

epoll_event FdEventHandler::getEvent(int i) {
	return events[i];
}

} /* namespace OxSocket */
