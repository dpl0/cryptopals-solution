#ifndef CRYPTOBREAKER_BYTE_H
#define CRYPTOBREAKER_BYTE_H

#include <string>
#include <vector>
#include <map>

#include <stdint.h>

using Byte = uint8_t;
using ByteStream = std::vector<Byte>;


class Utils {
private: // data
    static const std::string hexSymbols;
    static const std::string base64Symbols;
    static const std::map<char, Byte> hexValues;

public:
    static std::vector<std::string> splitInChunks(std::string&, int);
    static std::vector<ByteStream> splitInChunks(ByteStream&, int);

    static ByteStream encodeAsAscii(std::string&);
    static ByteStream encodeAsHex(std::string&);
    static ByteStream encodeAsBase64(std::string&);

    static std::string decodeAsAscii(ByteStream&);
    static std::string decodeAsHex(ByteStream&);
    static std::string decodeAsBase64(ByteStream&);

    // Perform complex operations in an easy way.
    static std::string asciiToHex(std::string&);
    static std::string asciiToByteStream(std::string&);
    static std::string hexToAscii(std::string&);
    static std::string hexToBase64(std::string&);
    static std::string base64ToAscii(std::string&);
    static std::string base64ToHex(std::string&);

private:
    static Byte buildByteFromHex(char&, char&);
    static std::string buildHexFromByte(Byte&);

    static ByteStream encodeBase64Block(std::string&);
    static std::string decodeBase64Block(ByteStream&);
};

namespace Debug {
    std::string byteToBinaryString(Byte);
    std::string byteStreamToBinaryString(ByteStream&);
}

#endif //CRYPTOBREAKER_BYTE_H
