#ifndef _TIMER_THREAD_H_
#define _TIMER_THREAD_H_ 

#include "non_copyable.h"
#include "thread.h"
#include "timer.h"
#include <functional>

class TimerThread : NonCopyable
{
    public:
        typedef std::function<void ()> TimerCallback;
        void setTimer(int, int);
        void setTimerCallback(const TimerCallback &);
        void startTimerThread();
        void cancelTimerThread();
    private:
        Timer timer_;
        Thread thread_;
};


#endif  /*_TIMER_THREAD_H_*/
