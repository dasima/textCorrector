#ifndef _INET_ADDRESS_H_
#define _INET_ADDRESS_H_

#include"copyable.h"
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
/*
 *InetAddress类 对sockaddr_in做了一些简单的包装
 *
 */
typedef struct sockaddr SA;
class InetAddress : private Copyable
{
    public:
        explicit InetAddress(uint16_t);
        InetAddress(const struct sockaddr_in &);

        const struct sockaddr_in *getSockAddrInet() const
        { return &addr_; }
        void setSockAddrInet(const struct sockaddr_in &addr)
        { addr_ = addr; }

        uint32_t ipNetEndian() const
        { return addr_.sin_addr.s_addr; }
        uint16_t portNetEndian() const
        { return addr_.sin_port; }

        std::string toIp() const
        { return std::string(inet_ntoa(addr_.sin_addr)); }
        uint16_t toPort() const
        { return ntohs(addr_.sin_port); }

        static InetAddress getLocalAddress(int);
        static InetAddress getPeerAddress(int);
    private:
        struct sockaddr_in addr_;
};

inline InetAddress::InetAddress(uint16_t port)
{
    ::memset(&addr_, 0, sizeof addr_);
    addr_.sin_family = AF_INET;
    addr_.sin_addr.s_addr = INADDR_ANY;
    addr_.sin_port = ::htons(port);
}

inline InetAddress::InetAddress(const struct sockaddr_in &addr)
    :addr_(addr)
{
}

inline InetAddress InetAddress::getLocalAddress(int sockfd)
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    if(::getsockname(sockfd, (SA*)&addr, &len) == -1)
        ERR_EXIT("getsockname");
    return InetAddress(addr);
}

inline InetAddress InetAddress::getPeerAddress(int sockfd)
{
    struct sockaddr_in addr;
    socklen_t len = sizeof(addr);
    if(::getpeername(sockfd, (SA*)&addr, &len) == -1)
        ERR_EXIT("getpeername");
    return InetAddress(addr);
}

#endif  /*_INET_ADDRESS_H_*/
