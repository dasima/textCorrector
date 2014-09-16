#include "tcp_server.h"
#include "non_copyable.h"
#include <iostream>
#include <string>
using namespace std;
using namespace std::placeholders;

 class EchoServer :NonCopyable
{   
    public:
        EchoServer(const InetAddress &addr)
            :server_(addr)
        {
            server_.setConnection(bind(&EchoServer::onConnection, this, _1));
            server_.setMessage(bind(&EchoServer::onMessage, this, _1));
        }

        void start()
        { server_.start(); }
    private:
        TcpServer server_;

        void onConnection(const TcpConnectionPtr &conn)
        { conn->sendString("hello\n"); }
        void onMessage(const TcpConnectionPtr &conn)
        {
            cout << "recv data " << conn->receiveString();
            conn->sendString("ACK\n");
        }
};

/*
 *类EchoServer案例
 *
 */


int main(int argc, const char *argv[])
{
    InetAddress addr(8080);
    EchoServer server(addr);
    server.start();
    
    return 0;
}
