#ifndef _CONDITION_H_
#define _CONDITION_H_

#include <pthread.h>
#include "non_copyable.h"

class MutexLock;
class Condition : NonCopyable
{
    public:
        Condition(MutexLock &);
        ~Condition();

        void wait();
        void notify();
        void notifyAll();

    private:
        pthread_cond_t cond_;
        MutexLock &mutex_;
        
};

#endif  /*_CONDITION_H_*/
