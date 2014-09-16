#ifndef _CACHE_MANAGER_H_
#define _CACHE_MANAGER_H_

#include <string>
#include <ctype.h>
#include <vector>
#include <queue>
#include "../include/cache.h"
//#include "../include/packaging/queue.h"
#include "../include/lib/mutex_lock.h"
#include "../include/lib/condition.h"
#include "./lib/timer_thread.h"
#include "./lib/mutex_lock.h"

class CacheManager
{
    public:
        CacheManager(const std::string &, size_t , int);
        ~CacheManager();

        void start();
        void stop();
        Cache *getCache();
        void returnCache(size_t);
        void writeToCacheFile();
        void updateCache();

    private:
        std::string Cache_file_;//缓存文件
        size_t Cache_num_;//缓存数
        std::vector<Cache> Caches_;//存放多个缓存
        Cache Cache_total_;//总缓存
        std::vector<size_t> Flags_;//
        bool Is_started_;
        std::queue<size_t> Queue_;//队列
        MutexLock Mutex_;//锁
        Condition Empty_;//信号量
        Condition Full_;
        TimerThread Timer_;//计时器

};

#endif  /*_CACHE_MANAGER_H_*/
