#include "../include/text_corrector.h"
#include "../include/cache.h"
//#include "../include/query_server.h"
#include "../include/query_server.h"
#include "../include/log.h"
#include <iostream>
#include <string>
#include <vector>
#include "../include/get_config.h"

using namespace std;

int main(int argc, const char *argv[])
{
    GetConfig *config = GetConfig::getInstance();
    config->readConfig("../conf/config.txt");
    //QueryServer server(InetAddress(8080), "../data/dic_en.txt", "../data/dic_cn.txt", "../data/cache.txt");
    QueryServer server(config);
    server.start();

    return 0;
}
