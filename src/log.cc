#include "../include/log.h"
#include "../include/lib/exception.h"
#include "../include/string_utils.h"
#include <iostream>
#include <fstream>
using namespace std;

Log::Log(const string &log_file)
    :Log_file_(log_file),
    Is_started_(false),
    Cond_(Mutex_),
    Thread_(bind(&Log::getLog, this))
{
    Thread_.start();
    Is_started_ = true;
}

void Log::stop()
{
    Is_started_ = false;
    Cond_.notifyAll();
    Thread_.join();
}

void Log::getLog()
{
    while(Is_started_)
    {
        MutexLockGuard lock(Mutex_);
        while(Is_started_ && Queue_.empty())
        {
            Cond_.wait();
        }
        string str;
        //vector<uint32_t> vec;
        //string_utils::parseUTF8String(str, vec);
        if(!Queue_.empty())
        {
            str = Queue_.front();
            Queue_.pop();
            //writeToLog("hi");
            writeToLog(str);
        }
        else
        {
            writeToLog("server has stop");
        }
    }
}

void Log::addLog(const string &str)
{
    MutexLockGuard lock(Mutex_);
    //vector<uint32_t> vec;
   // string_utils::parseUTF8String(str, vec);
    Queue_.push(str);
    if(Queue_.size() == 1)
        Cond_.notify();
}

void Log::writeToLog(const string &log_file)
{
    ofstream of;
    of.open(Log_file_, ofstream::app);
    if(!of)
        throw Exception("open file failed");
    of << log_file << endl;
    of.close();

}
