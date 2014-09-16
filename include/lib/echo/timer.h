#ifndef _TIMER_H_
#define _TIMER_H_

#include "non_copyable.h"
#include <functional>
#include <sys/timerfd.h>

class Timer : NonCopyable
{
    public:
        typedef std::function<void ()> TimerCallback;
        Timer();
        ~Timer();

        void setTimer(int, int);
        void setTimerCallback(const TimerCallback &);
        void runTimer();
        void cancelTimer();
    private:
        int timerfd_;
        struct itimerspec howlong_;
        TimerCallback timerCallback_;//用户逻辑
        bool is_started_;//是否开始
};

#endif  /*_TIMER_H_*/
