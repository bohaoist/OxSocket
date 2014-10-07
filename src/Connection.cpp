#include <Connection.h>

namespace OxSocket {

Connection::Connection(const int fd, const std::string taddr) {
	targetaddr = taddr;
	sum = n = 0;
	sfd = fd;

#ifdef LINUXFAST
	if (pipe(pipefd) < 0) {
		perror("pipe");
		throw std::runtime_error("Connection::pipe() failed");
	}
#endif
}

Connection::~Connection() {
}

#define WEADMACRO(function) \
n = sum = 0; \
do { \
	n = function(sfd, buf + sum, size - sum); \
	if (n == 0) { \
		return (sum); /* End of File/Stream */\
	} else if (n < 0) { \
		/*::perror(#function);*/ \
		return (-1); /* Error */\
	} else { \
		sum += n; \
	} \
} while (sum < size); \
return (sum);

int Connection::send(const char *buf, const unsigned int size) {
//	_poll(msec);
	WEADMACRO(write)
}

int Connection::recv(char *buf, const unsigned int size) {
//	_poll(msec);
	WEADMACRO(read)
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

#ifdef LINUXFAST
ssize_t Connection::sendfile_fast(std::string file) {

	int in_fd = open(file.c_str(), O_RDONLY);
	if (in_fd < 0) {
		perror("open");
		return -1;
	}

	struct stat buf;
	if (0 > fstat(in_fd, &buf)) {
		perror("fstat");
		return -1;
	}

	size_t count = buf.st_size;

	ssize_t bytes_sent;
	size_t total_bytes_sent = 0;
	while (total_bytes_sent < count) {
		if ((bytes_sent = ::sendfile(this->sfd, in_fd, 0,
								count - total_bytes_sent)) <= 0) {
			if (errno == EINTR || errno == EAGAIN) {
				// Interrupted system call/try again
				// Just skip to the top of the loop and try again
				continue;
			}
			perror("sendfile");
			return -1;
		}
		total_bytes_sent += bytes_sent;
	}
	return total_bytes_sent;
}

ssize_t Connection::recvfile_fast(const std::string file, size_t count) {

	int out_fd = open(file.c_str(), O_CREAT | O_WRONLY);
	if (out_fd < 0) {
		perror("open");
		return -1;
	}

	ssize_t bytes, bytes_sent, bytes_in_pipe;
	size_t total_bytes_sent = 0;

	// Splice the data from in_fd into the pipe
	while (total_bytes_sent < count) {
		if ((bytes_sent = splice(sfd, NULL, pipefd[1], NULL,
								count - total_bytes_sent,
								SPLICE_F_MORE | SPLICE_F_MOVE)) <= 0) {
			if (errno == EINTR || errno == EAGAIN) {
				// Interrupted system call/try again
				// Just skip to the top of the loop and try again
				continue;
			}
			perror("splice1");
			return -1;
		}

		// Splice the data from the pipe into out_fd
		bytes_in_pipe = bytes_sent;
		while (bytes_in_pipe > 0) {
			if ((bytes = splice(pipefd[0], NULL, out_fd, 0, bytes_in_pipe,
									SPLICE_F_MORE | SPLICE_F_MOVE)) <= 0) {
				if (errno == EINTR || errno == EAGAIN) {
					// Interrupted system call/try again
					// Just skip to the top of the loop and try again
					continue;
				}
				perror("splice2");
				return -1;
			}
			bytes_in_pipe -= bytes;
		}
		total_bytes_sent += bytes_sent;
	}
	return total_bytes_sent;
}
#endif
}

