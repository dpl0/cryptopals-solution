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


// Tables
const std::string Utils::hexSymbols{"0123456789abcdef"};
const std::string Utils::base64Symbols{"ABCDEFGHIJKLMNOPQRSTUVWXYZ" \
                                   "abcdefghijklmnopqrstuvwxyz0123456789+/"};
// Encoding functions
ByteStream Utils::encodeAsAscii(std::string &s) {
    return ByteStream{s.begin(), s.end()};
}

ByteStream Utils::encodeAsHex(std::string &s) {
    assert(s.length() % 2 == 0);
    ByteStream retval{};

    // XXX This can be improved with std algorithms.
    for (int i = 0; i < s.size(); i+=2) {
        retval.push_back(Utils::buildByteFromHex(s[i], s[i+1]));
    }
    return retval;
}

ByteStream Utils::encodeAsBase64(std::string &s) {
    ByteStream retval;

    std::cout << s << std::endl;
    auto quartets = splitInChunks(s, 4);

    for (auto c : quartets) {
        for (auto b: encodeBase64Block(c))
            retval.push_back(b);
    }
    return ByteStream();
}

ByteStream Utils::encodeBase64Block(std::string &s) {
    // ByteStream retval(3);

    // auto first = base64Symbols.find(s[0]);
    // auto second = base64Symbols.find(s[1]);
    // auto third = base64Symbols.find(s[2]);
    // auto fourth = base64Symbols.find(s[3]);

    // std::cout << "decodeBase64Block(" << s << ")" << std::endl;
    // std::cout << "Indexes: " << first << " " << second << " "<< third << " "<<
    //     fourth << std::endl;
    // std::cout << "Indexes (hex): 0x" << std::bits << first << " 0x" << second
    //     << " 0x"<< third << " 0x"<< fourth << std::endl;

    // Byte firstByte = (first | second) >> 4;
    // Byte secondByte = (second | third) << 2;
    // Byte thirdByte = (third | fourth) << 4;

    // return ByteStream{firstByte, secondByte, thirdByte};
    return ByteStream{};
}

// Decoding functions
std::string Utils::decodeAsAscii(ByteStream &stream) {
    return std::string{begin(stream), end(stream)};
}

std::string Utils::decodeAsHex(ByteStream &stream) {
    std::string retval;
    for (auto b: stream) {
        retval += buildHexFromByte(b);
    }
    return retval;
}

std::string Utils::decodeAsBase64(ByteStream &stream) {
    std::string retval;

    for (auto b: splitInChunks(stream, 3)) {
         retval.append(decodeBase64Block(b));
    }

    return retval;
}

std::string Utils::decodeBase64Block(ByteStream &block) {
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


// Complex operations
std::string Utils::hexToBase64(std::string &s) {
    ByteStream stream = encodeAsHex(s);
    std::string ret = decodeAsBase64(stream);
    return ret;
}

std::string Utils::base64ToHex(std::string &s) {
    ByteStream stream = encodeAsBase64(s);
    std::string ret = decodeAsHex(stream);
    return ret;
}


// Auxiliary functions
Byte Utils::buildByteFromHex(char &a, char &b) {
    size_t aLocation = hexSymbols.find(tolower(a));
    size_t bLocation = hexSymbols.find(tolower(b));
    return (uint16_t) aLocation << 4 | bLocation;
}

std::string Utils::buildHexFromByte(Byte& b) {
    char topChar{hexSymbols[(b & 0xf0) >> 4]};
    char bottomChar{hexSymbols[b & 0x0f]};
    return std::string{topChar, bottomChar};
}

std::vector<std::string> Utils::splitInChunks(std::string &s, int chunkSize) {
    std::vector<std::string> retval;

    for (int i = 0; i < s.size() ; i += chunkSize) {
        const std::string triplet = s.substr(i, chunkSize);
        retval.push_back(triplet);
    }
    return retval;
}

std::vector<ByteStream> Utils::splitInChunks(ByteStream &s, int chunkSize) {
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


