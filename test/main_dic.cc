#include "../include/text_corrector.h"
//#include "../include/cache.h"
#include "../include/query_server.h"
#include "../include/log.h"


#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, const char *argv[])
{
    /*
    TextCorrector tc("../data/dic_en.txt", "../data/dic_cn.txt");
    string word;
    while(cin >> word)
    {
        tc.textQuery(word);
        tc.getCache().writeToCacheFile("../data/cache.txt");
    }
    */
    /*
    QueryServer server(InetAddress(8080), "../data/dic_en.txt", "../data/dic_cn.txt", "../data/cache.txt");
    server.start();
    */
    Log my_log("log.txt");
    my_log.addLog("hello");
    my_log.addLog("zhahaoya");
    sleep(1);
    my_log.stop();


    return 0;
}
