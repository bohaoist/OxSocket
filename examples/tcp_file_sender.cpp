#include <iostream>
#include <string>
#include <fstream>
#include <OxSocket.h>
#include <sys/sendfile.h>
#include <sys/stat.h>

using namespace std;

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
	}

	struct stat sta;
	fstat(fd, &sta);

	char buf[sta.st_size];
	read(fd, buf, sta.st_size);

	OxSocket::TCPClientSocket sock(receiver, port);
	sock.send((char*) &(sta.st_size), sizeof(sta.st_size));
	sock.send(buf, sta.st_size);

	close(fd);
	return 0;
}

// EOF 
