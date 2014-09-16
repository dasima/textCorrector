#include "../include/index.h"
#include "../include/string_utils.h"
#include <iostream>
#include <vector>

using namespace std;

void Index::buildIndexEn(const map<string, int> &dic)
{
    map<string, int>::const_iterator mit;
    map<string, int> words[26];
    for(mit = dic.begin(); mit != dic.end(); ++mit)
    {
        string word = mit->first;
        char index_c = *(word.begin());
        int index = (index_c - 97);
        if(index >= 0 && index <= 25)
        {
            words[index][word] = (mit->second);
            Index_[index_c] = words[index];
        }
    }

}


void Index::buildIndexCn(const map<string, int> &dic)
{
    map<string, int>::const_iterator mit;
    for(mit = dic.begin(); mit != dic.end(); ++mit)
    {
        string word = mit->first;
        vector<uint32_t> vword;
        string_utils::parseUTF8String(word, vword);
        for(vector<uint32_t>::iterator it = vword.begin(); it != vword.end(); ++it){
            Index_[*it].insert(make_pair(word, mit->second)); 
        }
    }
}


