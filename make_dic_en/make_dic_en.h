#ifndef _MAKE_DIC_EN_H_
#define _MAKE_DIC_EN_H_

#include <iostream>
#include <string>
#include <vector>
#include <map>

class MakeDicEn
{
    public:
        MakeDicEn(const std::string &);
        void makeDicEn(const std::string &);
        
        void readFromFile(const std::string &);
        void writeToFile(const std::string &);
    private:
        std::vector<std::string> Lines_;
        std::map<std::string, int> Dic_en_;
};

#endif  /*_MAKE_DIC_EN_H_*/
