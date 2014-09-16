#ifndef _TEXT_CORRECTOR_H_
#define _TEXT_CORRECTOR_H_

#include <string>
#include <map>
#include "word.h"
#include "cache.h"
#include "index.h"

class TextCorrector
{
    public:
        TextCorrector(const std::string &, const std::string &);
        ~TextCorrector();

        void readFileEn(const std::string &);
        void readFileCn(const std::string &);

        std::string textQuery(const std::string &);
        std::string enQuery(const std::string &);
        std::string cnQuery(const std::string &);

        Cache &getCache()
        { return Cache_; }
    private:
        std::map<std::string, int> Dic_en_;
        std::map<std::string, int> Dic_cn_;

        Cache Cache_;
        Index Index_;
};

#endif  /*_TEXT_CORRECTOR_H_*/
