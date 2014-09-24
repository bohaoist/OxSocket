# netlib
##### What is it ?
A Object abstraction Layer for Networking Communications Calls in C++

##### What do i need to build it?
A C++ Compiler and stdlib and some magic.

##### How do i build it?
<pre><code>    git clone https://github.com/inbre001/netlib.git
    cd netlib/lib/
    make
</code></pre>
##### How do i use it? 
Just include the "Net.h" Header
<pre><code>    #include "Net.h"
</code></pre>
Now you can initialize TCP and UDP "Sockets"

#### Examples
##### TCP Echo Server
```C++   
    #include "Net.h"
    #include &lt;iostream&gt;
    #include &lt;string&gt;

    int main(int argc, char *argv[]) {
    
        int port = 1234;
        char buf[255];

        ServerSocket serversock(port);
        Connection *c = NULL;
    
        while(true){
            c = serversock.accept();
            int nbytes = c->recv(buf, sizeof(buf));
            if (nbytes >= 0) {
                std::cout << "Echo Server: recved message '" //
                << std::string(buf,nbytes) << "'" << std::endl;
            }
            c->send(buf,nbytes);
            delete c;
        }
        return 0;
    }
```
##### TCP Echo Client
<pre><code>    #include "Net.h"
    #include  &lt;iostream&gt;
    #include  &lt;string&gt;

    int main(int argc, char *argv[]) {
    
        int port = 1234;
        char buf[255];
        std::string msg = "Echo";

        ServerSocket sock(port);
        Connection *c = sock.connect();
        c->send(msg,msg.size());
        int nbytes = c->recv(buf,sizeof(buf));
        if (nbytes >= 0) {
                std::cout << "Echo Client: recved message '"  //
                << std::string(buf,nbytes) << "'" << std::endl;
        }
        delete c;

        return 0;
    }
</pre></code>
 
##### Creating a UDP Socket 
.. on the Server
<pre><code>    int port = 1234;
    UDPSocket udpsock(port);
</pre></code>
.. on the Client
<pre><code>    std::string serveraddr = "127.0.0.1";
    int port = 1234;
    UDPSocket udpsock(serveraddr.c_str(), port);
</pre></code>

###### Using a UDP Socket 
... sending
<pre><code>    std::string msg = "Hello";
    udpsock.send(msg.c_str(),msg.size());
</pre></code>
... recving
<pre><code>    char buf[255];
    udpsock.recv(buf,sizeof(buf));
</pre></code>

#### UDP Examples

##### Echo Server
    
##### Echo Client
    

