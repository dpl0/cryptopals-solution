#ifndef CRYPTOBREAKER_BYTE_H
#define CRYPTOBREAKER_BYTE_H

#include <string>
#include <vector>
#include <map>

#include <stdint.h>

using Byte = uint8_t;
using ByteStream = std::vector<Byte>;

namespace Utils {
    std::vector<std::string> splitInChunks(std::string&, int);
    std::vector<ByteStream> splitInChunks(ByteStream&, int);
}

namespace Debug {
    std::string byteToBinaryString(Byte);
    std::string byteStreamToBinaryString(ByteStream&);
}

#endif //CRYPTOBREAKER_BYTE_H
