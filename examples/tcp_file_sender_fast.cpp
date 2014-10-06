#include <iostream>
#include <string>
#include <fstream>
#include <0xSocket.h>
#include <sys/sendfile.h>
#include <sys/stat.h>

using namespace std;
using namespace OxSocket;

int main(int argc, char* argv[]) {

	cout << argc << endl;
	if (argc != 4) {
		return 1;
	}
//	unsigned long size = 0;
	std::string receiver = argv[1];
	unsigned port = atoi(argv[2]);
	int fd = open(argv[3], O_RDONLY);
	if (fd < 0) {
		cout << "failed to open file" << endl;
		return 1;
	} else {
		cout << "opended file: " << argv[3] << endl;
	}

	struct stat buf;
	fstat(fd, &buf);

	cout << "Sending: " << buf.st_size << " Bytes" << endl;

	TCPClientSocket sock(receiver, port);

	sock.send((char*) &(buf.st_size), sizeof(buf.st_size));
	close(fd);
//	do_sendfile(sock.sfd,fd,0,buf.st_size);
	sock.sendfile_fast(argv[3]);

	return 0;
}

// EOF 
