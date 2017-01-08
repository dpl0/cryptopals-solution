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


const std::string Utils::hexSymbols {"0123456789abcdef"};
const std::string Utils::base64Symbols {"ABCDEFGHIJKLMNOPQRSTUVWXYZ" \
                           "abcdefghijklmnopqrstuvwxyz0123456789+/"};

const std::vector<uint64_t> Utils::b64ByteSel {0xfc0000, 0x03f000,
                                                0x000fc0, 0x00003f};
// Encoding functions
ByteStream Utils::encodeAsAscii(std::string &s) {
    return ByteStream{s.begin(), s.end()};
}

ByteStream Utils::encodeAsHex(std::string &s) {
    assert(s.length() % 2 == 0);
    ByteStream retval{};

    // XXX This can be improved with std algorithms, surely.
    for (int i = 0; i < s.size(); i+=2) {
        retval.push_back(Utils::buildByteFromHex(s[i], s[i+1]));
    }
    return retval;
}

ByteStream Utils::encodeAsBase64(std::string &s) {
    return ByteStream();
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
    // size_t ntriplets = (size_t)ceil(stream.length( )/ 3);
    // uint16_t lackingchars = stream.length() % 3;

    // // Separate triplets into sets of four symbols.
    // for (size_t i = 0; i < ntriplets; i++)
    // {
    //     // Get the symbols.
    //     if (i == ntriplets - 1) {
    //         // We'll have to add "=" as required
    //         printf("Last iteration!\n");
    //     } else {
    //         uint64_t data = s[i*1]|s[i*2]|s[i*3];
    //         printf("Triplet: 0x%x, (int)%lu\n", data, data);
    //         // Get the 4 symbols, separating 64 bits in 4 6-bits ints
    //         Byte first = (Byte & byteSel[0]) >> 56);
    //         printf("%x\n", first);
    //         // Byte second = 
    //         // Byte third = 
    //         // Byte fourth = 
    //     }

    //     // cout << data << endl;
    //     // cout << "    " << (char)s[i*1] << " " << (char)s[i*2] << 
    //         // " " << (char)s[i*3] << " " << endl;
    // }
    return "";
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
Byte Utils::buildByteFromHex(char a, char b) {
    size_t aLocation = hexSymbols.find(tolower(a));
    size_t bLocation = hexSymbols.find(tolower(b));
    return (uint16_t) aLocation << 4 | bLocation;
}

std::string Utils::buildHexFromByte(Byte b) {
    char topChar{hexSymbols[(b & 0xf0) >> 4]};
    char bottomChar{hexSymbols[b & 0x0f]};
    return std::string{topChar, bottomChar};
}
