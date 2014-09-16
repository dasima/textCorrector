#include "../include/text_corrector.h"
#include "../include/string_utils.h"
#include <echo/exception.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <queue>

using namespace std;
using namespace string_utils;

TextCorrector::TextCorrector(const string &filename1, const string &filename2)
    :Cache_("../data/cache.txt")
{
    readFileEn(filename1);    
    readFileCn(filename2);    
}

TextCorrector::~TextCorrector()
{
}

void TextCorrector::readFileEn(const string &filename)
{
    ifstream in;
    in.open(filename.c_str());
    if(!in)
        throw Exception("open file failed!");
    string line;
    string word;
    int frequence;
    while(getline(in, line))
    {
        istringstream iss(line);
        iss >> word >> frequence;
        Dic_en_.insert(make_pair(word, frequence));
    }
    /*
       while(getline(in, line))
       {
       istringstream iss(line);
       iss >> word >> frequence;
       Word new_word;
       new_word.Word_ = word;
       new_word.Distance_ = 5;
       new_word.Frequence_ = frequence;
       Dic_en_.insert(make_pair(word, new_word));
       }
       */
    in.close();
    Index_.buildIndexEn(Dic_en_);
}

void TextCorrector::readFileCn(const string &filename)
{
    ifstream in;
    in.open(filename.c_str());
    if(!in)
        throw Exception("open file failed!");
    string line;
    string word;
    int frequence;
    while(getline(in, line))
    {
        istringstream iss(line);
        iss >> word >> frequence;
        Dic_cn_.insert(make_pair(word, frequence));
    }
    in.close();
    Index_.buildIndexCn(Dic_cn_);
}

string TextCorrector::textQuery(const string &word)
{
    string tmp = word;
    while(*(tmp.rbegin()) == '\r' || *(tmp.rbegin()) == '\n')
        tmp.resize(tmp.size() - 1);

    string tmp2;
    string res;
    //先从缓存中查询---这里没有解决处理中文的问题
    map<string, set<string> >::iterator msit;
    msit = Cache_.getCache().find(tmp);
    if(msit != Cache_.getCache().end())
    {
        cout << "cache" << endl;
        set<string> candidate;
        candidate = Cache_.searchFromCache(word);
        set<string>::iterator index = candidate.begin();
        for(; index != candidate.end(); ++index)
        {
            tmp2 = *index;
            tmp2 += "\r\n";
            res += tmp2;
        }
    }
    //如果没查到，从文件中查询
    else
    {
        cout << "file" << endl;
        priority_queue<Word> queue;
        map<string, int>::iterator mit;
        int len = string_utils::getLenOfUTF8(tmp[0]);
        if(len >= 3)
        {
            mit = Dic_cn_.find(word);
            if(mit != Dic_cn_.end())
            {
                //cout << word << endl;
                Cache_.buildCache(word, word);
                return word;
            }
            res = cnQuery(tmp);
        }
        else
        {
            //这里查询输出用两种方式
            //1. 查询到词典中有这个单词，就返回并输出
            //2. 词典中没有这个单词，则从词典中查询相近的几个单词，并输出
            //这里英文采用第二种
            //中文采用第一种
            //如果要输出多个，可以查询正确也输出几个相近的
            /*
               mit = Dic_en_.find(word);
               if(mit != Dic_en_.end())
               {
               cout << word << endl;
               return word;
               }
               */
            res = enQuery(tmp);
        }
    }
    //cout << res << endl;
    return res; 
}

//从中文词典中查询---OK
string TextCorrector::cnQuery(const string &word)
{
    string tmp = word;
    priority_queue<Word> queue;
    map<string, int>::iterator mit = Dic_cn_.begin();
    for(; mit != Dic_cn_.end(); ++mit)
    {
        int distance = string_utils::editDistance((mit->first).c_str(), word.c_str());
        if(distance < 3)
        {
            Word mword;
            mword.Distance_ = distance;
            mword.Word_ = mit->first;
            mword.Frequence_ = mit->second;
            queue.push(mword);
        }
    }
    string res;
    string word_out;
    for(int i = 0; i < 3; ++i)
    {
        if(queue.empty())
            break;
        word_out = queue.top().Word_;
        //cout << word_out << endl;
        Cache_.buildCache(word, word_out);
        word_out += "\r\n";
        res += word_out;
        queue.pop();
    }
    return res;
}

//从英文词典中查询相近的单词---OK
string TextCorrector::enQuery(const string &word)
{
    string tmp = word;
    priority_queue<Word> queue;
    //map<string, int>::iterator mit = Dic_en_.begin();
    string::iterator c = tmp.begin();
    auto get_index = Index_.getIndex().find(*c)->second;
    for(auto mit = get_index.begin(); mit != get_index.end(); ++mit)
    {
        if(::abs(word.size() - (mit->first).size()) > 3)
            continue;
        int distance = string_utils::editDistance((mit->first).c_str(), word.c_str());
        if(distance < 2)
        {
            Word mword;
            mword.Distance_ = distance;
            mword.Word_ = mit->first;
            mword.Frequence_ = mit->second;
            queue.push(mword);
        }
    }
    string res;
    string word_out;
    for(int i = 0; i < 3; ++i)
    {
        if(queue.empty())
            break;
        //cout << "res" << endl;
        word_out = queue.top().Word_;
        Cache_.buildCache(word, word_out);
        //cout << word_out << endl;
        word_out += "\r\n";
        res += word_out;
        queue.pop();
    }
    return res;
}

