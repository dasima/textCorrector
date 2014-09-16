#include "make_dic_cn.h"
#include <echo/exception.h>
#include <istream>
#include <fstream>
#include <vector>
#define LOGGER_LEVEL LL_WARN

using namespace CppJieba;
using namespace std;

//const char * const TEST_FILE = "../cppjieba/test/testdata/testlines.utf8";
const char * const TEST_FILE = "./a.txt";
const char * const JIEBA_DICT_FILE = "../include/cppjieba/dict/jieba.dict.utf8";
const char * const HMM_DICT_FILE = "../include/cppjieba/dict/hmm_model.utf8";

/*
 *实现中文切词功能
 *并建立中文词典
 */

MakeDicCn::MakeDicCn()
{
    makeDic();
}

//切分中文单词
void MakeDicCn::cut(const ISegment& seg, const char * const file_path)
{
    ifstream ifile(file_path);
    ofstream of("cn.txt");
    vector<string> words;
    string line;//存放从文本读取的一行数据
    string res;//
    string word;//从一行数据中读取一个单词
    set<string> exclude_words;
    exclude_words.insert(",");
    while(getline(ifile, line))
    {        
        if(!line.empty())
        {
            words.clear();
            seg.cut(line, words);
            //这里词库输出有问题，把vector容器中内容输出查看是否输出成功
            //for(vector<string>::iterator it = words.begin(); it != words.end(); ++it)
              //  cout << *it << endl;
            join(words.begin(), words.end(), res, " ");

            istringstream iss(res);
            while(iss >> word)
            {
                if(!exclude_words.count(word))
                    of << word << endl;
            }
        }
    }
}


void MakeDicCn::makeDic()
{
    //    printf("\e[32m%s\e[0m\n", "[demo] MixSegment"); // colorful
        MixSegment seg(JIEBA_DICT_FILE, HMM_DICT_FILE);
        cut(seg, TEST_FILE);

        readFromFile("cn.txt");
        writeToFile("dic_cn.txt");

        /*
        ofstream of("dic_cn.txt");
        if(!of)
            throw Exception("open file failed!");
        map<string, int>::iterator mit;
        for(mit = Dic_.begin(); mit != Dic_.end(); ++mit)
        {
            cout << mit->first << " " << mit->second << endl;
            of << mit->first << " " << mit->second << endl; 
        }
        */
}

//把文件内容建成词典
void MakeDicCn::readFromFile(const string &filename)
{
    ifstream in;
    in.open(filename.c_str());
    if(!in)
        throw Exception("open file failed");
    string line;
    string word;
    string wordi;
    string::iterator it;
    set<string> exclude_word;
    exclude_word.insert("。");
    exclude_word.insert("《");
    exclude_word.insert("》");
    exclude_word.insert(".");
    exclude_word.insert("...");
    exclude_word.insert("-");
    exclude_word.insert(" ");
    exclude_word.insert("\'");
    exclude_word.insert("、");
    exclude_word.insert("：");
    exclude_word.insert("，");
    exclude_word.insert("`");
    exclude_word.insert("β");
    exclude_word.insert("¨");
    exclude_word.insert("·");
    exclude_word.insert("‘");
    exclude_word.insert("’");
    exclude_word.insert("“");
    exclude_word.insert("”");
    exclude_word.insert("…");
    exclude_word.insert("●");
    exclude_word.insert("　");
    exclude_word.insert("！");
    exclude_word.insert("＆");
    exclude_word.insert("（");
    exclude_word.insert("）");
    exclude_word.insert("．");
    exclude_word.insert("／");
    exclude_word.insert("？");
    exclude_word.insert("；");
    exclude_word.insert("～");
    exclude_word.insert("１");
    exclude_word.insert("２");
    exclude_word.insert("３");
    exclude_word.insert("４");
    exclude_word.insert("ｃ");
    exclude_word.insert("ｍ");
    exclude_word.insert("<feff>");
    exclude_word.insert("—");
    while(in >> line)
    {
        istringstream iss(line);
        iss >> wordi;
        if(exclude_word.count(wordi))
            continue;
        
        it = line.begin();
        if(isalpha(*it))
            continue;
        if(ispunct(*it))
            continue;
        if(isspace(*it))
            continue;
        if(isdigit(*it))
            continue;
        word = line;
        //cout << word << endl;
        ++Dic_[word];
    }
    in.close();
}

//把字典内容写入词典文件中
void MakeDicCn::writeToFile(const string &filename)
{
    ofstream of;
    of.open(filename.c_str());
    if(!of)
        throw Exception("open file failed");

    map<string, int>::iterator mit;
    for(mit = Dic_.begin(); mit != Dic_.end(); ++mit)
    {
        //cout << mit->first << " " << mit->second << endl;
        of << mit->first << " " << mit->second << endl; 
    }
    of.close();
}


