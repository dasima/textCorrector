#ifndef _QUERY_SERVER_H_
#define _QUERY_SERVER_H_

#include <echo/tcp_server.h>
#include <echo/thread_pool.h>
#include <echo/timer_thread.h>
#include "text_corrector.h"
#include "log.h"
#include <string>
#include "cache.h"
#include "get_config.h"
class QueryServer : NonCopyable
{
    public:
        //QueryServer(const InetAddress &, const std::string &, const std::string &, const std::string & );
        ~QueryServer();
        QueryServer(GetConfig *);
        void start();
    private:
        void onConnection(const TcpConnectionPtr &);
        void onMessage(const TcpConnectionPtr &);
        void onClose(const TcpConnectionPtr &);

        void runQuery(const std::string &, const TcpConnectionPtr &);
        //void runQuery(const std::string &, const TcpConnectionPtr &, Cache *);

        //0814为了把缓存回写，使用计时器，计时器调用这个函数
        void writeCache();

        TcpServer server_;
        TextCorrector query_;
        ThreadPool pool_;
        Cache cache_;
        //CacheManeger caches_;
        TimerThread timer_;
        Log log_;
};

#endif  /*_QUERY_SERVER_H_*/
