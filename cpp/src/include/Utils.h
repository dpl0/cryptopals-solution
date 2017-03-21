#ifndef CRYPTOBREAKER_UTILS_H
#define CRYPTOBREAKER_UTILS_H

#include <string>
#include <vector>
#include "Common.h"

namespace Utils {
    std::vector<std::string> splitInChunks(std::string&, int);
    std::vector<ByteStream> splitInChunks(ByteStream&, int);
}

namespace Debug {
    std::string byteToBinaryString(Byte);
    std::string byteStreamToBinaryString(ByteStream&);
}

#endif //CRYPTOBREAKER_UTILS_H
