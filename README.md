# netlib
##### What is it ?

A Object abstraction Layer for Networking Communications Calls in C++
##### Build:
<pre>  
    git clone https://github.com/inbre001/netlib.git
    cd netlib/lib/
    make
</pre>
#### Use: 
Just include the "Net.h" Header
<pre><code>
#include "Net.h"
</code></pre>
###### Creating a TCP Connection 
 ... on the Server
<pre><code>
    int port = 1234;
    ServerSocket serversock(port);    
    Connection *c = serversock.accept();    
</pre></code>
 ... on the Client
<pre><code>
    std::sting serveraddr = "127.0.0.1"; // either IP or Hostname
    int port = 1234; 
    Socket sock(serveraddr,port);
    Connection *c = sock.connect();
</pre></code>
##### Using TCP Connections
.. to send data
<pre><code>
    std::string msg = "Hello World\n";
    c->send(msg.c_str(),msg.size());
</pre></code>
.. to recv data
<pre><code>
    int bsize = 255;
    char buf[bsize];
    c->recv(buf,bsize);
</pre></code>
#### Examples
##### Echo Server
<pre><code>
    #include "Net.h"
    #include <iostream>
    #include <string>

    int main(int argc, char *argv[]) {
    
        int port = 1234;
        char buf[255];

        ServerSocket serversock(port);
        Connection *c = NULL;
    
        while(true){
            c = serversock.accept();
            int nbytes = c->recv(buf, sizeof(buf));
            if (nbytes >= 0) {
                std::cout << "Echo Server: recved message '" << std::string(buf,nbytes) << "'" << std::endl;
            }
            c->send(buf,nbytes);
            delete c;
        }

        return 0;
    }
</pre></code>
##### Echo Client
<pre><code>
    #include "Net.h"
    #include <iostream>
    #include <string>

    int main(int argc, char *argv[]) {
    
        int port = 1234;
        char buf[255];
        std::string msg = "Echo";

        ServerSocket sock(port);
        Connection *c = sock.connect();
        c->send(msg,msg.size());
        int nbytes = c->recv(buf,sizeof(buf));
        if (nbytes >= 0) {
                std::cout << "Echo Client: recved message '" << std::string(buf,nbytes) << "'" << std::endl;
        }
        delete c;

        return 0;
    }
</pre></code>
 
##### Creating a UDP Connection 

