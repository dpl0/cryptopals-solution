#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <cmath>
#include <cctype>
#include <stdint.h>

#include <stdio.h>
#include <assert.h>

#include "Utils.h"

namespace Utils {

std::vector<std::string> splitInChunks(std::string &s, int chunkSize) {
    std::vector<std::string> retval;

    for (int i = 0; i < s.size() ; i += chunkSize) {
        const std::string triplet = s.substr(i, chunkSize);
        retval.push_back(triplet);
    }
    return retval;
}

std::vector<ByteStream> splitInChunks(ByteStream &s, int chunkSize) {
    std::vector<ByteStream> retval;
    const auto sSize = s.size();

    for (int i = 0; i < s.size() ; i += chunkSize) {
        ByteStream block;
        for (int j = 0 ; j <= chunkSize-1; j++) {
            if (i+j < sSize) {
                block.push_back(s[i+j]);
            }
        }
        retval.push_back(block);
    }
    return retval;
}

} // end of namespace Utils


namespace Debug {
std::string byteToBinaryString(Byte b) {
    std::string retval;
    for (int i = 1; i <= 8; i++) {
        if (b % 2 == 0) retval.insert(0, "0");
        else retval.insert(0, "1");
        b /= 2;
    }
    return retval;
}

std::string byteStreamToBinaryString(ByteStream &bs) {
    std::string retval;

    std::vector<std::string> parts;
    for (auto b: bs)
        parts.push_back(byteToBinaryString(b));

    for (int i = 0; i < parts.size(); i++) {
        retval += parts[i];
        if (i != (parts.size()-1))
                retval += '|';
    }
    return retval;
}

} // namespace Debug end


