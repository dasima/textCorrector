#ifndef _INDEX_H_
#define _INDEX_H_

#include "word.h"
#include <string>
#include <map>
#include <stdint.h>

class Index
{
    public:
        typedef std::map<uint32_t, std::map<std::string, int> > M;
        Index()
        {}
        M const &getIndex() const
        { return Index_; }
        void buildIndexEn(const std::map<std::string, int> &);
        void buildIndexCn(const std::map<std::string, int> &);
        //void createIndexCn(const std::unordered_map<std::string, Word> &);

    private:
            std::map<uint32_t, std::map<std::string, int> > Index_;

};

#endif  /*_INDEX_H_*/
