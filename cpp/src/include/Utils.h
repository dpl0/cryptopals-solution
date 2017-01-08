#ifndef CRYPTOBREAKER_BYTE_H
#define CRYPTOBREAKER_BYTE_H

#include <string>
#include <vector>
#include <map>

#include <stdint.h>

using namespace std;

using Byte = uint8_t;
using ByteStream = vector<Byte>;


class Utils {
private: // data
    static const string hexSymbols;
    static const string base64Symbols;
    static const map<char, Byte> hexValues;
    static const vector<uint64_t> b64ByteSel;

public:
    static ByteStream encodeAsAscii(string&);
    static ByteStream encodeAsHex(string&);
    static ByteStream encodeAsBase64(string&);

    static string decodeAsAscii(ByteStream&);
    static string decodeAsHex(ByteStream&);
    static string decodeAsBase64(ByteStream&);

    static string hexToBase64(string&);
    static string base64ToHex(string&);

private:
    // Auxiliary
    static Byte buildByteFromHex(char a, char b);
    static std::string buildHexFromByte(Byte b);
};

#endif //CRYPTOBREAKER_BYTE_H
