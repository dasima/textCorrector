#include "../include/cache_manager.h"
#include <map>
#include <iostream>
using namespace std;

CacheManager::CacheManager(const string &cache_file, 
                            size_t cache_num,
                            int update_frequence)
    :Cache_file_(cache_file),
    Cache_num_(cache_num),
    Caches_(cache_num),
    Flags_(cache_num),
    Is_started_(true),
    Empty_(Mutex_),
    Full_(Mutex_)
{
    Cache_total_.readFromCacheFile(Cache_file_);
    map<string, set<string> >::iterator beginit = Cache_total_.getCache().begin();
    map<string, set<string> >::iterator endit = Cache_total_.getCache().end();
    vector<Cache>::iterator vit = Caches_.begin(); 
    for(; vit != Caches_.end(); ++vit)
    {
        vit->getCache().insert(beginit, endit);
    }
    vector<Cache>::size_type ix = 0; 
    for(; ix != Caches_.size(); ++ix)
    {
        Caches_[ix].setOrder(ix);
        Flags_[ix] = 0;
        Queue_.push(ix);
    }
    Timer_.setTimer(10, update_frequence);
    Timer_.setTimerCallback(::bind(&CacheManager::writeToCacheFile, this));
}


CacheManager::~CacheManager()
{
    Timer_.cancelTimerThread();
    stop();
}

void CacheManager::start()
{
    Timer_.startTimerThread();
}

void CacheManager::stop()
{
    if(Is_started_)
    {
        Is_started_ = true;
        Full_.notifyAll();
    }
}

Cache *CacheManager::getCache()
{
    MutexLockGuard lock(Mutex_);
    size_t i;
    while(Is_started_  && Queue_.empty())
        Full_.wait();
    if(!Queue_.empty())
    {
        i = Queue_.front();
        Queue_.pop();
    }
    return &Caches_[i];
}


void CacheManager::returnCache(size_t i)
{
    MutexLockGuard lock(Mutex_);
    Queue_.push(i);
    if(Queue_.size() == 1)
        Full_.notify();
}

void CacheManager::writeToCacheFile()
{
    map<string, set<string> >::iterator begin, end;
    for(size_t i = 0; i != Cache_num_; ++i)
    {
        begin = Caches_[i].getCache().begin();
        end = Caches_[i].getCache().end();
        Cache_total_.getCache().insert(begin, end);
    }
    Cache_total_.writeToCacheFile(Cache_file_);
    updateCache();
}

void CacheManager::updateCache()
{
    map<string, set<string> >::iterator begin, end;
    begin = Cache_total_.getCache().begin();
    end = Cache_total_.getCache().end();
    size_t i = 0;
    while(i != Cache_num_)
    {
        Cache *Cache_ = getCache();
        size_t order = Cache_->getOrder();
        if(Flags_[order] == 0)
        {
            Cache_->getCache().insert(begin, end);
            Flags_[order] = 1;
        }
        returnCache(order);
        if(order == i)
            ++i;
    }
    for(vector<size_t>::iterator vit = Flags_.begin(); vit != Flags_.end(); ++vit)
    {
        *vit = 0;
    }
    cout << "update cache " << endl;
}
