#ifndef _THREAD_POOL_H_
#define _THREAD_POOL_H_ 

#include "non_copyable.h"
#include "mutex_lock.h"
#include "condition.h"
#include <functional>
#include <memory>
#include <queue>

class Thread;
class ThreadPool : NonCopyable
{
    public:
        typedef std::function<void ()> Task;

        ThreadPool(size_t queueSize, size_t poolSize);
        ~ThreadPool();

        void start();//启动线程池
        void stop();//停止线程池

        void addTask(const Task &);

    private:
        Task getTask();
        void runInThread();//线程池内线程的回调函数
        //这里mutex_生命为mutable是为了在const函数中也可以改变该变量
        mutable MutexLock mutex_;
        Condition empty_;
        Condition full_;
        size_t queueSize_;//队列大小
        std::queue<Task> queue_;
        size_t poolSize_;//线程池大小
        std::vector<std::unique_ptr<Thread>> threads_;
        bool is_started_;//线程是否开启

};

#endif  /*_THREAD_POOL_H_*/
