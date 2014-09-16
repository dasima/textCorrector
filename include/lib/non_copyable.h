#ifndef _NON_COPYABLE_H_
#define _NON_COPYABLE_H_

/*
 *不可复制类
 *通过把复制构造函数和重载运算符设为私有，实现
 *继承该类的派生类都不具有 value/值 拷贝功能
 */
class NonCopyable
{
    protected:
        NonCopyable(){}
        ~NonCopyable(){}
    private:
        NonCopyable(const NonCopyable &);
        void operator=(const NonCopyable &);
};

#endif  /*_NON_COPYABLE_H_*/
