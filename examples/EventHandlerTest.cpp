#include <iostream>
#include <string>
#include <cstdlib>
#include <OxSocket.h>

using namespace std;
using namespace OxSocket;

int main(int argc, char* argv[]) {

	SocketFdEventHandler handler;
	TCPServerSocket sock(1234);
	handler.add(&sock);

	while (true) {
		handler.wait2();

		SocketFd* tmp = NULL;
		while (NULL != (tmp = handler.getNextEvent())) {

			if (tmp->isAcceptSocket) {
				cout << "Accepting" << endl;
				Connection *tmp = sock.accept();
				handler.add(tmp);
			} else {
				cout << "Recving" << endl;
				char buf[255];
				Connection *con = (Connection*) tmp;
				con->setTimeout(5);

				int n = con->recv(buf, sizeof(buf));
				if (n > 0) {
					cout << " >>" << std::string(buf, n) << endl;
				} else if (n < 0){
					cout << "recv::timeout" << endl;
				} else if (n == 0){
					cout << "recv::disconnect" << endl;
                }else{
                    cout << "WTF happened ?!" << endl;
                }

				handler.del(con);
				delete con;

			}
		}
	}

	return 0;
}

// EOF 
