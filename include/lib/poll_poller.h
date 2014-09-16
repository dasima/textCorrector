#ifndef _POLL_POLLER_H_
#define _POLL_POLLER_H_ 

#include "non_copyable.h"
#include "tcp_connection.h"
#include <functional>
#include <poll.h>
#include <stdio.h>
#include <map>

class PollPoller : private NonCopyable
{
    public :
        typedef TcpConnection::TcpConnectionCallback PollerCallback;

        explicit PollPoller(int);
        ~PollPoller();

        void pollWait();
        void handleAccept();
        void handleData();

        void handleConnectionEvent(int);
        void handleMessageEvent(int);
        void handleCloseEvent(int);

        void processConnect(const TcpConnectionPtr &conn)
        { conn->handleConnection(); }
        void processMessage(const TcpConnectionPtr &conn)
        { conn->handleMessage(); }
        void processClose(const TcpConnectionPtr &conn)
        { conn->handleClose(); }

        void setConnectionCallback(const PollerCallback &ppc)
        { onConnectionCallback_ = ppc; }
        void setMessageCallback(const PollerCallback &ppc)
        { onMessageCallback_ = ppc; }
        void setCloseCallback(const PollerCallback &ppc)
        { onCloseCallback_ = ppc; }

    private:
        struct pollfd event_[2048];
        int listenfd_;
        int maxi_;
        int nready_;
        std::map<int, TcpConnectionPtr> lists_;//从fd到TcpConnection的映射

        PollerCallback onConnectionCallback_;
        PollerCallback onMessageCallback_;
        PollerCallback onCloseCallback_;

        typedef std::map<int, TcpConnectionPtr>::iterator TcpConnectionIterator;

        static size_t kPoolQueueSize_;
        static size_t kPoolThreadSize_;
};

#endif  /*_POLL_POLLER_H_*/
