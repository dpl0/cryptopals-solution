#include <iostream>
#include <string>
#include <vector>

#include <cctype>
#include <cstdint>
#include <cassert>

#include "Utils.h"

const std::string hexSymbols = "0123456789abcdef";
const std::string base64Symbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" \
                          "abcdefghijklmnopqrstuvwxyz0123456789+/";


namespace CB { namespace Utils {

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


ByteStream encodeAsAscii(std::string &s) {
    return ByteStream{s.begin(), s.end()};
}

ByteStream encodeAsHex(std::string &s) {
    assert(s.length() % 2 == 0);
    ByteStream retval{};

    // XXX This can be improved with std algorithms.
    for (int i = 0; i < s.size(); i+=2) {
        retval.push_back(buildByteFromHex(s[i], s[i+1]));
    }
    return retval;
}

ByteStream encodeAsBase64(std::string &s) {
    ByteStream retval;

    auto quartets = Utils::splitInChunks(s, 4);

    for (auto c : quartets) {
        for (auto b: encodeBase64Block(c))
            retval.push_back(b);
    }
    return ByteStream();
}

// Decoding functions
std::string decodeAsAscii(ByteStream &stream) {
    return std::string{begin(stream), end(stream)};
}

std::string decodeAsHex(ByteStream &stream) {
    std::string retval;
    for (auto b: stream) {
        retval += buildHexFromByte(b);
    }
    return retval;
}

std::string decodeAsBase64(ByteStream &stream) {
    std::string retval;

    for (auto b: Utils::splitInChunks(stream, 3)) {
         retval.append(decodeBase64Block(b));
    }

    return retval;
}

// Complex operations
std::string hexToBase64(std::string &s) {
    ByteStream stream = encodeAsHex(s);
    std::string ret = decodeAsBase64(stream);
    return ret;
}

std::string base64ToHex(std::string &s) {
    ByteStream stream = encodeAsBase64(s);
    std::string ret = decodeAsHex(stream);
    return ret;
}


// Auxiliary functions
Byte buildByteFromHex(char &a, char &b) {
    size_t aLocation = hexSymbols.find(tolower(a));
    size_t bLocation = hexSymbols.find(tolower(b));
    return (uint16_t) aLocation << 4 | bLocation;
}

std::string buildHexFromByte(Byte& b) {
    char topChar{hexSymbols[(b & 0xf0) >> 4]};
    char bottomChar{hexSymbols[b & 0x0f]};
    return std::string{topChar, bottomChar};
}

std::string decodeBase64Block(ByteStream &block) {
    // Indicates if this is the last round, we'll have to add '='*lackingChars.
    const bool isLastRound = (block.size() < 3);
    const int lackingChars = (isLastRound ? 3 - block.size() : 0);

    const Byte firstByte = block[0];
    const Byte secondByte = (isLastRound && lackingChars == 2) ?
                uint8_t{0} : block[1];
    const Byte thirdByte = (isLastRound && lackingChars >= 1) ?
                uint8_t{0} : block[2];

    const Byte firstCharIndex = (firstByte & 0xfc) >> 2;
    const Byte secondCharIndex = ((firstByte & 0x03) << 4)
                                | (secondByte >> 4) ;
    const Byte thirdCharIndex = ((secondByte & 0x0f) << 2)
                                | ((thirdByte & 0xc0) >> 6);
    const Byte fourthCharIndex = (thirdByte & 0x3f);

    const char firstChar = base64Symbols[firstCharIndex];
    const char secondChar = base64Symbols[secondCharIndex];
    const char thirdChar = (isLastRound && lackingChars == 2) ? '=' :
                    base64Symbols[thirdCharIndex];
    const char fourthChar = (isLastRound && lackingChars >= 1)? '=' :
                    base64Symbols[fourthCharIndex];

    return std::string{firstChar, secondChar, thirdChar, fourthChar};
}

// XXX
ByteStream encodeBase64Block(std::string &s) {
    return ByteStream{};
}

ByteStream
XorByteStreams(const ByteStream &a, const ByteStream &b, const size_t &size) {
    if (size > a.size() or size > b.size()) return ByteStream{0x00};
    ByteStream retval(size);
    for (size_t i = 0; i < size; i++) {
        retval[i] = a[i] ^ b[i];
    }
    return retval;
}

ByteStream
XorByteStreams(const ByteStream &a, const ByteStream &b) {
    size_t smallest = a.size() < b.size() ? a.size() : b.size();
    ByteStream retval(smallest);
    for (size_t i = 0; i < smallest; i++) {
        retval[i] = a[i] ^ b[i];
    }
    return retval;
}

} // end of namespace Utils
} // end of namespace CB

Byte buildByteFromHex(char &a, char &b) {
    size_t aLocation = hexSymbols.find(tolower(a));
    size_t bLocation = hexSymbols.find(tolower(b));
    return (uint16_t) aLocation << 4 | bLocation;
}

std::string buildHexFromByte(Byte& b) {
    char topChar{hexSymbols[(b & 0xf0) >> 4]};
    char bottomChar{hexSymbols[b & 0x0f]};
    return std::string{topChar, bottomChar};
}

std::string decodeBase64Block(ByteStream &block) {
    // Indicates if this is the last round, we'll have to add '='*lackingChars.
    const bool isLastRound = (block.size() < 3);
    const int lackingChars = (isLastRound ? 3 - block.size() : 0);

    const Byte firstByte = block[0];
    const Byte secondByte = (isLastRound && lackingChars == 2) ?
                uint8_t{0} : block[1];
    const Byte thirdByte = (isLastRound && lackingChars >= 1) ?
                uint8_t{0} : block[2];

    const Byte firstCharIndex = (firstByte & 0xfc) >> 2;
    const Byte secondCharIndex = ((firstByte & 0x03) << 4)
                                | (secondByte >> 4) ;
    const Byte thirdCharIndex = ((secondByte & 0x0f) << 2)
                                | ((thirdByte & 0xc0) >> 6);
    const Byte fourthCharIndex = (thirdByte & 0x3f);

    const char firstChar = base64Symbols[firstCharIndex];
    const char secondChar = base64Symbols[secondCharIndex];
    const char thirdChar = (isLastRound && lackingChars == 2) ? '=' :
                    base64Symbols[thirdCharIndex];
    const char fourthChar = (isLastRound && lackingChars >= 1)? '=' :
                    base64Symbols[fourthCharIndex];

    return std::string{firstChar, secondChar, thirdChar, fourthChar};
}

// XXX
ByteStream encodeBase64Block(std::string &s) {
    return ByteStream{};
}


namespace CB { namespace Debug {
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

} // end of namespace Debug
} // end of namespace CB

