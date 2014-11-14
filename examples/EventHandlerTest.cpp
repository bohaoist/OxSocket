#include <iostream>
#include <string>
#include <cstdlib>
#include <OxSocket.h>
#include <FdEventHandler.h>

using namespace std;
using namespace OxSocket;

int main(int argc, char* argv[]) {

	FdEventHandler ehdl(5);

	TCPServerSocket sock(1234);

	ehdl.addFd(sock.sfd);
//	Connection *c1 = sock.accept();
//	ehdl.addFd(c1->sfd);
//	Connection *c2 = sock.accept();
//	ehdl.addFd(c2->sfd);

	while (true) {
		int n = ehdl.wait();
//	n = ehdl.wait();
		cout << "#Events: " << n << endl;

		for (int i = 0; i < n; i++) {

			if ((ehdl.getEvent(i).events & EPOLLERR) //
			|| (ehdl.getEvent(i).events & EPOLLHUP) //
					|| (!(ehdl.getEvent(i).events & EPOLLIN))) {
				/* An error has occured on this fd, or the socket is not
				 ready for reading (why were we notified then?) */
				fprintf(stderr, "epoll error\n");
//			close(events[i].data.fd);

				continue;
//		} else if (sfd == events[i].data.fd) {
//			cout << " We have a notification on the listening socket, which"
//			 "means one or more incoming connections. " << endl;

			} else {
				cout << " We have data on the fd waiting to be read. Read and"
						"display it. We must read whatever data is available"
						"completely, as we are running in edge-triggered mode "
						"and won't get a notification again for the same "
						"data." << endl;
				cout << ehdl.getEvent(i).data.fd << endl;

				char buf[255];

				if (ehdl.getEvent(i).data.fd == sock.sfd) {
					cout << "accepted" << endl;
					Connection *tmp = sock.accept();
					ehdl.addFd(tmp->sfd);
//			} else if (ehdl.getEvent(i).data.fd == c1->sfd) {
//				c1->recv(buf,sizeof(buf));
//				cout << buf << endl;
//			} else if (ehdl.getEvent(i).data.fd == c2->sfd) {
//				c2->recv(buf,sizeof(buf));
					cout << buf << endl;
				} else {
					Connection blub(ehdl.getEvent(i).data.fd,"");
					int n = blub.recv(buf,sizeof(buf));
					cout << std::string(buf,n) << endl;
				}

			}
		}

	}

	return 0;
}

// EOF 
