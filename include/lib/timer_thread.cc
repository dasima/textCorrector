#include "timer_thread.h"

using namespace std;

void TimerThread::setTimer(int val, int interval)
{
    timer_.setTimer(val, interval);
}

void TimerThread::setTimerCallback(const TimerCallback &tc)
{
    timer_.setTimerCallback(tc);
    thread_.setCallback(bind(&Timer::runTimer, &timer_));
}

void TimerThread::startTimerThread()
{
    thread_.start();
}

void TimerThread::cancelTimerThread()
{
    timer_.cancelTimer();
    thread_.join();
}
