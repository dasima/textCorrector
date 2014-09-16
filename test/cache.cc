#include "../include/cache.h"
#include <fstream>
#include <echo/exception.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>
using namespace std;

Cache::Cache(const string &filename)
{
    readFromCacheFile(filename);
}

void Cache::readFromCacheFile(const string &filename)
{
    ifstream in;
    in.open(filename.c_str());
    if(!in)
        throw Exception("open file failed");

    string line;
    string usr_word;
    string word_cache;
    while(getline(in, line))
    {
        istringstream iss(line);
        iss >> usr_word;
        //cout << usr_word << "--" << endl;
        while(iss >> word_cache)
        {
            Cache_[usr_word].insert(word_cache);
        }
    }
    in.close();
}

void Cache::buildCache(const string &word, const string &word_cache)
{
    Cache_[word].insert(word_cache);
}

//程序运行成功后，把cout全注释了
void Cache::writeToCacheFile(const string &filename)
{
    ofstream of;
    of.open(filename.c_str());
    if(!of)
        throw Exception("open file failed");
    map<string, set<string> >::iterator mit = Cache_.begin();
    for(; mit != Cache_.end(); ++mit)
    {
       // cout << mit->first << " " ;
        of << mit->first << " " ;
        set<string>::iterator sit = (mit->second).begin();
        for(; sit != (mit->second).end(); ++sit)
        {
          //  cout << *sit << " ";
            of << *sit << " ";
        }
       // cout << endl;
        of << endl;
    }
    of.close();
}

set<string> Cache::searchFromCache(const string &word)
{
    map<string, set<string> >::iterator mit = Cache_.find(word);
    set<string> candidates;
    if(mit != Cache_.end())
        candidates = mit->second;
    return candidates;
}
