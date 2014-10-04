#include <iostream>
#include <string>
#include <fstream>
#include <0xSocket.h>
#include <sys/sendfile.h>
#include <sys/stat.h>

using namespace std;
using namespace OxSocket;

int main(int argc, char* argv[]) {

	if (argc != 4) {
		return 1;
	}
	unsigned long size = 0;
	std::string receiver = argv[1];
	unsigned port = atoi(argv[2]);
	int fd = open(argv[3], 'r');

	struct stat buf;
	fstat(fd, &buf);

	TCPClientSocket sock(receiver, port);
	sock.setTimeout(5, 0);

//	if (fs.is_open()) {
//		//
//		open()
//		fs.seekg(0, fs.end);
//		size = fs.tellg();
//		fs.seekg(0, fs.beg);
//

//		char buf[size];
//		fs.read(buf, size);
//		size = sock.send(buf, size);

	sendfile(sock.sfd, fd, 0, buf.st_size+1);

	sock.close();
//} else {
//	cout << "failed" << endl;
//}

	return 0;
}

// EOF 
