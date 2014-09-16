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
     *1. Log构造函数
     *2. addLog函数
     *3. getLog函数
     *  3.1 getLog会调用writeToLog
     *   这里， while循环为假前，会一直调用writeToLog函数，
     *   这里会调用两次，然后停留在内部while函数的wait处
     * 
     *
     *4.stop函数
     *  stop函数中会调用一次writeToLog函数
     */
    cout << "a" << endl;
    Log my_log("log.txt");
    cout << "b" << endl;
    my_log.addLog("hello");
    my_log.addLog("zhahaoya");
    sleep(1);//这里需要留给线程时间进行处理
    my_log.stop();


    return 0;
}
