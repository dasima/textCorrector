#ifndef _STRING_UTILS_H_
#define _STRING_UTILS_H_ 

#include <string>
#include <vector>
#include <stdint.h>

namespace string_utils
{
    int getLenOfUTF8(unsigned char);
    void parseUTF8String(const std::string &, std::vector<uint32_t> &);
    int MIN(int, int, int);
    int editDistanceUint32(const std::vector<uint32_t> &, const std::vector<uint32_t> &);
    int editDistance(const std::string &, const std::string &);
}

#endif  /*_STRING_UTILS_H_*/
