#include "thread_pool.h"

#include "thread.h"
using namespace std;

ThreadPool::ThreadPool(size_t queueSize, size_t poolSize)
    :empty_(mutex_),
    full_(mutex_),
    queueSize_(queueSize),
    poolSize_(poolSize),
    is_started_(false)
{
}

ThreadPool::~ThreadPool()
{
    if(is_started_)
        stop();
}

void ThreadPool::addTask(const Task &task)
{
    MutexLockGuard lock(mutex_);
    while(queue_.size() >= queueSize_)
        empty_.wait();

    queue_.push(task);
    full_.notify();//通知消费者取任务
}

ThreadPool::Task ThreadPool::getTask()
{
    MutexLockGuard lock(mutex_);
    while(queue_.empty() && is_started_)
        full_.wait();

    /*
     *这里的wait可以被stop函数的notifyAll所激活
     *激活后，is_started_不再为空
     *就退出循环
     *显然，此时队列仍然为空
     */
    Task task;
    //如果队列为空，返回的task为一个空函数
    if(!queue_.empty())
    {
        task = queue_.front();
        queue_.pop();
        empty_.notify();//通知生产者
    }
    return task;
}

void ThreadPool::runInThread()
{
    //当线程池关闭时，这个线程可以自动退出
    while(is_started_)
    {
        Task task(getTask());
        if(task)
            task();//这里才是真正执行任务
    }
}

void ThreadPool::start()
{
    if(is_started_)
        return;
    is_started_ = true;
    //开启线程
    for(size_t i = 0; i != poolSize_; ++i)
        threads_.push_back(std::unique_ptr<Thread>(new Thread(bind(&ThreadPool::runInThread, this))));
    for(size_t i = 0; i != poolSize_; ++i)
        threads_[i]->start();
}

void ThreadPool::stop()
{
    if(is_started_ == false)
        return;
    {
        MutexLockGuard lock(mutex_);
        is_started_ = false;
        full_.notifyAll();//激活所有正在等待任务的线程
    }
    for(size_t i = 0; i != poolSize_; ++i)
        threads_[i]->join();

    while(!queue_.empty())
        queue_.pop();

    threads_.clear();
}
