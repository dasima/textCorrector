#ifndef _MAKE_DIC_CN_H_
#define _MAKE_DIC_CN_H_

#include <iostream>
#include <string>
#include "../include/cppjieba/src/MixSegment.hpp"
#define LOGGER_LEVEL LL_WARN

class MakeDicCn
{
    public:
        MakeDicCn();
        void cut(const CppJieba::ISegment&, const char* const);
        void makeDic();

        void readFromFile(const std::string &);
        void writeToFile(const std::string &);
    private:
        std::map<std::string, int> Dic_;

};

#endif  /*_MAKE_DIC_CN_H_*/
