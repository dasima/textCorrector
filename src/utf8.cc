#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

//计算utf8编码所占的字节
int getLenOfUTF8(unsigned char c)
{
    int cnt = 0;
    while(c & (1 << (7 - cnt)))
        ++cnt;
    return cnt;
}

//把字符解析成uint32_t数组
void parseUTF8String(const string &s, vector<uint32_t> &vec)
{
    vec.clear();
    for(string::size_type ix = 0; ix !=s.size(); ++ix)
    {
        int len = getLenOfUTF8(s[ix]);
        cout << "len " << len << endl;
        uint32_t t = (unsigned char)s[ix];
        cout << "unint32_t " << t << endl;
        if(len > 1)
        {
            --len;
            //拼接剩余的字节
            while(len--)
            {
                t = (t << 8) + (unsigned char)s[++ix];
            }
        }
        vec.push_back(t);
    }
}

inline int MIN(int a, int b, int c)
{
    int ret = (a < b) ? a : b;
    ret = (ret < c) ? ret : c;
    return ret;
}

int editDistanceUint32(const vector<uint32_t> &w1, const vector<uint32_t> &w2)
{
    int len_a = w1.size();
    int len_b = w2.size();
    int memo[100][100];
    memset(memo, 0x00, 100*100*sizeof(int));
    for(int i = 1; i <= len_a; ++i)
    {
        memo[i][0] = i;
    }
    for(int j = 1; j <= len_b; ++j)
    {
        memo[0][j] = j;
    }
    for(int i = 1; i <= len_a; ++i)
    {
        for(int j = 1; j <= len_b; ++j)
        {
            if(w1[i-1] == w2[j-1])
            {
                memo[i][j] = memo[i-1][j-1];
            }
            else
            {
                memo[i][j] = MIN(memo[i-1][j-1], memo[i-1][j], memo[i][j-1]) + 1;
            }
        }   
    }
    return memo[len_a][len_b];
}

int editDistance(const string &a, const string &b)
{
    vector<uint32_t> w1, w2;
    parseUTF8String(a, w1);
    parseUTF8String(b, w2);
    return editDistanceUint32(w1, w2);
}

int main(int argc, const char *argv[])
{
    string s = argv[1];
    string s2 = argv[2];
    printf("%d\n", editDistance(s, s2));
 
    /*
    string ss = "帕克邓肯";
    vector<uint32_t> vec;
    parseUTF8String(ss, vec);
    for(size_t ix = 0; ix != vec.size(); ++ix)
    {
        printf("%x\n", vec[ix]);
    }
    */

    return 0;
}
