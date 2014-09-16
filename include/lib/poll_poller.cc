#include "poll_poller.h"
#include <iostream>
#include <assert.h>
using namespace std;

#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

size_t PollPoller::kPoolQueueSize_ = 1000;
size_t PollPoller::kPoolThreadSize_ = 4;

PollPoller::PollPoller(int listenfd)
    :listenfd_(listenfd),
    maxi_(0),
    nready_(0)
{
    int i;
    for(i = 0; i < 2048; ++i)
        event_[i].fd = -1;
    event_[0].fd = listenfd;
    event_[0].events = POLLIN;
}

PollPoller::~PollPoller()
{
}

void PollPoller::pollWait()
{
    int nready;
    do
    {
        nready = ::poll(event_, maxi_ + 1, 10000);
    }while(nready == -1 && errno == EINTR);
    if(nready == -1)
        ERR_EXIT("poll");
    nready_ = nready;
}

void PollPoller::handleAccept()
{
    if(event_[0].revents && POLLIN)
    {
        int peerfd = ::accept(listenfd_, NULL, NULL);;
        if(peerfd == -1)
            ERR_EXIT("accept");
        handleConnectionEvent(peerfd);
    }
}

void PollPoller::handleData()
{
    int i;
    for(i = 1; i <= maxi_; ++i)
    {
        int peerfd = event_[i].fd;
        if(peerfd == -1)
            continue;
        if(event_[i].revents & POLLIN)
        {
            char buf[1024];
            int nread = ::recv(peerfd, buf, sizeof buf, MSG_PEEK);
            if(nread == -1)
                ERR_EXIT("recv");
            else if(nread == 0)
            {
                handleCloseEvent(i);
            }
            else
                handleMessageEvent(peerfd);
        }
    }
}

void PollPoller::handleConnectionEvent(int peerfd)
{
    //添加至event
    //map中新增一条
    //调用函数
    int i;
    for(i = 1; i < 2048; ++i)
    {
        if(event_[i].fd == -1)
        {
            event_[i].fd = peerfd;
            event_[i].events = POLLIN;
            if(i > maxi_)
                maxi_ = i;
            break;
        }
    }
    if(i == 2048)
    {
        fprintf(stderr, "too many clients\n");
        exit(EXIT_FAILURE);
    }

    TcpConnectionPtr conn(new TcpConnection(peerfd,
                InetAddress::getLocalAddress(peerfd),
                InetAddress::getPeerAddress(peerfd)));
    conn->setConnectionCallback(onConnectionCallback_);
    conn->setMessageCallback(onMessageCallback_);
    conn->setCloseCallback(onCloseCallback_);

    //
    pair<TcpConnectionIterator, bool> ret = lists_.insert(make_pair(peerfd, conn));
    //
    assert(ret.second == true);
    //onConnectionCallback_(conn);
    conn->handleConnection();
}

void PollPoller::handleMessageEvent(int peerfd)
{
    TcpConnectionIterator it = lists_.find(peerfd);
    assert(it != lists_.end());
    //onMessageCallback_(it->second);
    it->second->handleMessage();
}

void PollPoller::handleCloseEvent(int i)
{
    assert(i >= 0 && i <= 2048);
    int peerfd = event_[i].fd;
    //
    assert(peerfd != -1);
    event_[i].fd = -1;
    //
    TcpConnectionIterator it = lists_.find(peerfd);
    assert(it != lists_.end());
    it->second->handleClose();
    //onCloseCallback_(it->second);
    lists_.erase(it);

   // event_[i].fd = -1;
}
