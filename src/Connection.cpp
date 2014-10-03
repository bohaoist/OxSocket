#include <Connection.h>

Connection::Connection(const int fd, const std::string taddr) {
	targetaddr = taddr;
	sum = n = 0;
	ufds.fd = fd;
	ufds.events = POLLIN | POLLOUT | POLLPRI;
}

Connection::~Connection() {
}

#define WEADMACRO(function) \
n = sum = 0; \
do { \
	n = ::function(ufds.fd, buf + sum, size - sum); \
	if (n == 0) { \
		return (sum); /* End of File/Stream */\
	} else if (n < 0) { \
		::perror(#function); \
		return (-1); /* Error */\
	} else { \
		sum += n; \
	} \
} while (sum < size); \
return (sum);

int Connection::send(const char *buf, const unsigned size, const int) {
//	_poll(msec);
	WEADMACRO(write)
}

int Connection::recv(char *buf, const unsigned size, const int) {
//	_poll(msec);
	WEADMACRO(read)
}

int Connection::send(const std::string in) {
	return this->send(in.c_str(), in.size());
}

int Connection::recv(std::string& out, int size) {
	char buf[size];
	int n = this->recv(buf, size);
	if (n > 0) {
		out = std::string(buf, n);
	}
	return n;
}

#undef WEADMACRO

//int Connection::_poll(const int msec) {
//	int rv = ::poll(&ufds, 1, msec);
//#ifdef DEBUG
//	if (0 > rv) {
//		::perror("poll error");
//	} else if (0 == rv) {
//		::perror("poll timeout");
//	} //else 0 < rv
//#endif
//	return (rv);
//}

