#ifndef CRYPTOBREAKER_ENCODING_H
#define CRYPTOBREAKER_ENCODING_H

#include "Common.h"

namespace Encoding {
    const std::string hexSymbols = "0123456789abcdef";
    const std::string base64Symbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" \
                              "abcdefghijklmnopqrstuvwxyz0123456789+/";


    ByteStream encodeAsAscii(std::string&);
    ByteStream encodeAsHex(std::string&);
    ByteStream encodeAsBase64(std::string&);

    std::string decodeAsAscii(ByteStream&);
    std::string decodeAsHex(ByteStream&);
    std::string decodeAsBase64(ByteStream&);

    // Perform complex operations in an easy way.
    std::string hexToBase64(std::string&);
    std::string base64ToHex(std::string&);

    Byte buildByteFromHex(char&, char&);
    std::string buildHexFromByte(Byte&);

    ByteStream encodeBase64Block(std::string&);
    std::string decodeBase64Block(ByteStream&);
} // end namespace Encoding

#endif //CRYPTOBREAKER_BYTE_H
