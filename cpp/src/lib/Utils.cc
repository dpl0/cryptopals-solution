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


ByteStream Utils::hexToByteStream(std::string &s) {
    assert(s.length() % 2 == 0);
    ByteStream bytes = ByteStream();

    for (int i = 0; i < s.size(); i+=2) {
        bytes.push_back(buildHexDatum(s[i], s[i+1]));
    }
    return bytes;
}

ByteStream Utils::base64ToByteStream(std::string &s) {
    return ByteStream();
}

std::string Utils::byteStreamToHex(ByteStream &raw) {
    return "";
}

std::string Utils::byteStreamToBase64(ByteStream &raw) {
    // size_t ntriplets = (size_t)ceil(intput.length( )/ 3);
    // uint16_t lackingchars = input.length() % 3;

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


std::string Utils::hexToBase64(std::string &s) {
    ByteStream raw = hexToByteStream(s);
    std::string ret = byteStreamToBase64(raw);
    return ret;
}

std::string Utils::base64ToHex(std::string &s) {
    ByteStream raw = base64ToByteStream(s);
    std::string ret = byteStreamToHex(raw);
    return ret;
}


Byte Utils::buildHexDatum(char a, char b) {
    size_t aLocation = Utils::hexSymbols.find(tolower(a));
    size_t bLocation = Utils::hexSymbols.find(tolower(b));
    return (uint16_t) aLocation << 4 | bLocation;
}
