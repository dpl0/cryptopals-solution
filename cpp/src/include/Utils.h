#ifndef CRYPTOBREAKER_BYTE_H
#define CRYPTOBREAKER_BYTE_H

#include <string>
#include <vector>
#include <map>

#include <stdint.h>

typedef uint8_t Byte;
typedef std::vector<uint8_t> ByteStream;

class Utils {
public:
    static std::string& hexToBase64(std::string&);
    static std::string& base64ToHex(std::string&);
private:
    // constexprt this when possible
    static char base64Symbols[64];
    static std::vector<char> hexSymbols;
    static std::map<char, uint8_t> hexValues;
    static uint64_t b64ByteSel[4];

    // static char base64Symbols[64] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

    // static std::vector<char> hexSymbols = {'0', '1', '2', '3', '4', '5', '6' ,'7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

    // static std::map<char, uint8_t> hexValues = {{'0', 0x0}, {'1', 0x1},
    // {'2', 0x2}, {'3', 0x3}, {'4', 0x4}, {'5', 0x5}, {'6', 0x6}, {'7', 0x7},
    // {'8', 0x8}, {'9', 0x9}, {'a', 0xa}, {'b', 0xb}, {'c', 0xc}, {'d', 0xd},
    // {'e', 0xe}, {'f', 0xf}};

    // static uint64_t b64ByteSel[4] = { 0xfc0000, 0x03f000, 0x000fc0, 0x00003f };


    static ByteStream* hexToByteStream(std::string&);
    static ByteStream* base64ToByteStream(std::string&);

    static std::string byteStreamToHex(ByteStream*);
    static std::string byteStreamToBase64(ByteStream*);
};


#endif //CRYPTOBREAKER_BYTE_H
