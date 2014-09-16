#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include "non_copyable.h"
#include "inet_address.h"
#include "socket.h"
#include "poll_poller.h"
#include "tcp_connection.h"
#include <memory>

class TcpServer : NonCopyable
{
    public:
        typedef TcpConnection::TcpConnectionCallback TcpCallback;
        explicit TcpServer(const InetAddress &);

        void setConnection(const TcpCallback &tc)
        { onConnection_ = tc; }
        void setMessage(const TcpCallback &tc)
        { onMessage_ = tc; }
        void setClose(const TcpCallback &tc) 
        { onClose_ = tc; }

        void start();
    private:
        std::unique_ptr<Socket> sock_;
        std::unique_ptr<PollPoller> poller_;

        TcpCallback onConnection_;
        TcpCallback onMessage_;
        TcpCallback onClose_;

};

#endif  /*_TCP_SERVER_H_*/
