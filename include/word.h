#ifndef _WORD_H_
#define _WORD_H_ 

#include <string>

struct Word
{
    bool operator < (const Word &other) const
    {
        if(Distance_ == other.Distance_)
            return Frequence_ < other.Frequence_;
        else
            return Distance_ > other.Distance_;
    }

    std::string Word_;
    int Distance_;
    int Frequence_;
};

#endif  /*_WORD_H_*/
