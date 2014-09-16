#ifndef _RIO_H_
#define _RIO_H_
#include "non_copyable.h"
#include <stdlib.h>
#define ERR_EXIT(m)\
    do\
    {\
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)

#define MAXLINE 1024
#define RIO_BUFFER 8192
class Rio : NonCopyable
{
    public:
        explicit Rio(int);

        ssize_t rio_readn(char*, size_t);
        ssize_t rio_readline(char*, size_t);
        ssize_t rio_writen(const char*, size_t);
    private:
        ssize_t rio_read(char*, size_t);

        int fd_;
        int left_;
        char *bufPtr_;
        char buffer_[RIO_BUFFER];
};

#endif  /*_RIO_H_*/
