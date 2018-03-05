#ifndef CRYPTOBREAKER_UTILS_H
#define CRYPTOBREAKER_UTILS_H

#include <string>
#include <vector>
#include "Common.hpp"

namespace CB {
    namespace Utils {
        std::vector<std::string> splitInChunks(std::string&, int);
        std::vector<std::vector<Byte> > splitInChunks(std::vector<Byte>&t, int);

        ByteStream encodeAsAscii(std::string&);
        ByteStream encodeAsHex(std::string&);
        ByteStream encodeAsBase64(std::string&);

        std::string decodeAsAscii(ByteStream&);
        std::string decodeAsHex(ByteStream&);
        std::string decodeAsBase64(ByteStream&);

        // Perform complex operations in an easy way.
        std::string hexToBase64(std::string&);
        std::string base64ToHex(std::string&);

        // Auxiliary
        Byte buildByteFromHex(char&, char&);
        std::string buildHexFromByte(Byte&);

        ByteStream encodeBase64Block(std::string&);
        std::string decodeBase64Block(ByteStream&);

        // Xor
        ByteStream XorByteStreams(const ByteStream&, const ByteStream&,
                                      const std::size_t&);
        ByteStream XorByteStreams(const ByteStream&, const ByteStream&);
    }

    namespace Debug {
        std::string byteToBinaryString(Byte);
        std::string byteStreamToBinaryString(ByteStream&);
    }
}

#endif //CRYPTOBREAKER_UTILS_H
