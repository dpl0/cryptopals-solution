#ifndef CRYPTOBREAKER_BYTE_H
#define CRYPTOBREAKER_BYTE_H

#include <string>
#include <vector>
#include <map>

#include <stdint.h>

using namespace std;

typedef uint8_t Byte;
typedef vector<uint8_t> ByteStream;

class Utils {
private: // data
    static const string hexSymbols;
    static const string base64Symbols;
    static const map<char, uint8_t> hexValues;
    static const vector<uint64_t> b64ByteSel;

public:
    static ByteStream hexToByteStream(string&);
    static ByteStream base64ToByteStream(string&);

    static string byteStreamToHex(ByteStream&);
    static string byteStreamToBase64(ByteStream&);

    static string hexToBase64(string&);
    static string base64ToHex(string&);
private:
    // Auxiliary
    static uint8_t buildHexDatum(char a, char b);
};

#endif //CRYPTOBREAKER_BYTE_H
