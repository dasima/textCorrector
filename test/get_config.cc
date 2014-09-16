#include "../include/get_config.h"
#include <fstream>
#include <echo/exception.h>

using namespace std;

GetConfig *GetConfig::pInstance_ = NULL;
pthread_once_t GetConfig::Once_ = PTHREAD_ONCE_INIT;

void GetConfig::readConfig(const string &filename)
{
    ifstream in;
    in.open(filename.c_str());
    if(!in)
        throw Exception("open file failed!");
    string line;
    while(getline(in, line))
    {
        string type;//类型
        string param;//参数
        string::size_type pos;
        pos = line.find("=");
        type = line.substr(0, pos);
        param = line.substr(pos + 1);
 //       cout << "type " << type << " param " << param << endl;
        if(type == "port")
            Port_ = atoi(param.c_str());
        else if(type == "log")
            Log_file_ = param;
        else if(type == "cache_file")
            Cache_file_ = param;
        else if(type == "en_dic")
            En_dic_file_ = param;
        else if(type == "cn_dic")
            Cn_dic_file_ = param;
        else if(type == "cache_num")
            Cache_num_ = atoi(param.c_str());
        else if(type == "update_frequence")
            Update_frequence_ = atoi(param.c_str());
    }
}
