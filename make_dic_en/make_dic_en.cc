#include "make_dic_en.h"
#include <echo/exception.h>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <ostream>
#include <algorithm>
#include <functional>
#include <cctype>

using namespace std;

MakeDicEn::MakeDicEn(const string &filename)
{
    makeDicEn(filename);
    readFromFile("en.txt");
    writeToFile("dic_en.txt");
}

void MakeDicEn::makeDicEn(const string &filename)
{
    ifstream in;
    in.open(filename.c_str());
    if(!in)
        throw Exception("open file failed!");
    string line;
    while(getline(in, line))
        Lines_.push_back(line);
    in.close();

    ofstream out("en.txt");
    for(vector<string>::size_type ix = 0; ix != Lines_.size(); ++ix)
    {
        istringstream iss(Lines_[ix]);
        string word;
        while(iss >> word)
        {
            for(string::iterator it = word.begin(); it != word.end(); ++it)
            {
                if(isupper(*it))
                    tolower(*it);
                if(ispunct(*it))
                    *it = ' ';
            }
            string::iterator it = remove_if(word.begin(), word.end(), bind2nd(equal_to<char>(), ' '));
            word.erase(it, word.end());
            if(isdigit(word[0]))
                continue;
            out << word << endl;
        }
    }
    out.close();
}

void MakeDicEn::readFromFile(const string &filename)
{
    ifstream in;
    in.open(filename.c_str());
    if(!in)
        throw Exception("open file failed");
    string line;
    string word;
    while(getline(in, line))
    {
        istringstream iss(line);
        iss >> word;
        ++Dic_en_[word];
    }
    in.close();
}

void MakeDicEn::writeToFile(const string &filename)
{
    ofstream of;
    of.open(filename.c_str());
    if(!of)
        throw Exception("open file failed");

    map<string, int>::iterator mit;
    for(mit = Dic_en_.begin(); mit != Dic_en_.end(); ++mit)
    {
        of << mit->first << " " << mit->second << endl;
    }
    of.close();
}
