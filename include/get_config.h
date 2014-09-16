#ifndef _GET_CONFIG_H_
#define _GET_CONFIG_H_

#include <iostream>
#include <pthread.h>
#include <string>
#include <stdlib.h>
class GetConfig
{
    public:
        GetConfig(){}//这里,私有？？

        static GetConfig *getInstance()
        {
            pthread_once(&Once_, &initInstance);
            return pInstance_;
        }
        static void initInstance()
        {
            ::atexit(&destroyInstance);
            pInstance_ = new GetConfig;
        }
        static void destroyInstance()
        {
            std::cout << "destroy " << std::endl;
            delete pInstance_;
        }
        void readConfig(const std::string &filename);
        
        const int getPort() const 
        { return Port_; }
        const std::string &getLogFile() const 
        { return Log_file_; }
        const std::string &getCacheFile() const
        { return Cache_file_; }
        const std::string &getEnDicFile() const 
        { return En_dic_file_; }
        const std::string &getCnDicFile() const 
        { return Cn_dic_file_; }
        const int &getCacheNum() const 
        { return Cache_num_; }
        const int getUpdateFrequence() const
        { return Update_frequence_; }
    private:
        GetConfig(const GetConfig &);
        void operator=(const GetConfig &);

        static GetConfig *pInstance_;
        static pthread_once_t Once_;

        int Port_;
        std::string Log_file_;
        std::string Cache_file_;
        std::string En_dic_file_;
        std::string Cn_dic_file_;
        int Cache_num_;
        int Update_frequence_;

};

#endif  /*_GET_CONFIG_H_*/
