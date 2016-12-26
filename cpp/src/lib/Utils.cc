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

using namespace std;

const string Utils::hexSymbols {"0123456789abcdef"};
const string Utils::base64Symbols {"ABCDEFGHIJKLMNOPQRSTUVWXYZ" \
                           "abcdefghijklmnopqrstuvwxyz0123456789+/"};

const vector<uint64_t> Utils::b64ByteSel {0xfc0000, 0x03f000,
                                                0x000fc0, 0x00003f};

ByteStream Utils::hexToByteStream(string &s) {
    assert(s.length() % 2 == 0);
    ByteStream bytes = ByteStream();

    for (int i = 0; i < s.size(); i+=2) {
        bytes.push_back(buildHexDatum(s[i], s[i+1]));
    }
    return bytes;
}

ByteStream Utils::base64ToByteStream(string &s) {
    return ByteStream();
}

string Utils::byteStreamToHex(ByteStream &raw) {
    return "";
}

string Utils::byteStreamToBase64(ByteStream &raw) {
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
    //         uint8_t first = (uint8_t)((data & byteSel[0]) >> 56);
    //         printf("%x\n", first);
    //         // uint8_t second = 
    //         // uint8_t third = 
    //         // uint8_t fourth = 
    //     }

    //     // cout << data << endl;
    //     // cout << "    " << (char)s[i*1] << " " << (char)s[i*2] << 
    //         // " " << (char)s[i*3] << " " << endl;
    // }
    return "";
}


string Utils::hexToBase64(string &s) {
    ByteStream raw = hexToByteStream(s);
    string ret = byteStreamToBase64(raw);
    return ret;
}

string Utils::base64ToHex(string &s) {
    ByteStream raw = base64ToByteStream(s);
    string ret = byteStreamToHex(raw);
    return ret;
}


uint8_t Utils::buildHexDatum(char a, char b) {
    size_t aLocation = Utils::hexSymbols.find(tolower(a));
    size_t bLocation = Utils::hexSymbols.find(tolower(b));
    return (uint16_t) aLocation << 4 | bLocation;
}
