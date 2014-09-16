#ifndef _CACHE_H_
#define _CACHE_H_
#include <string>
#include <map>
#include <set>


class Cache
{
    public:
        typedef std::map<std::string, std::set<std::string> > MS_;

        Cache(const std::string &);
        Cache() {}

        MS_ &getCache()
        { return Cache_; }

        void buildCache(const std::string &, const std::string &);
        void readFromCacheFile(const std::string &);
        void writeToCacheFile(const std::string &);

        std::set<std::string> searchFromCache(const std::string &);

        void setOrder(size_t order)
        { Order_ = order; }
        size_t getOrder()
        { return Order_; }

    private:
        std::map<std::string, std::set<std::string> > Cache_;

        size_t Order_;

};


#endif  /*_CACHE_H_*/
