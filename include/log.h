#ifndef _LOG_H_
#define _LOG_H_

#include <string>
#include "../include/lib/mutex_lock.h"
#include "../include/lib/condition.h"
#include "../include/lib/thread.h"
#include <queue>

class Log
{
    public:
        Log(const std::string &);
        void stop();
        void getLog();
        void addLog(const std::string &);
        void writeToLog(const std::string &);
    private:
        std::string Log_file_;
        bool Is_started_;
        std::queue<std::string> Queue_;
        MutexLock Mutex_;
        Condition Cond_;
        Thread Thread_;

};

#endif  /*_LOG_H_*/
