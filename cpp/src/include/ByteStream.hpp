#ifndef CRYPTOBREAKER_BYTESTREAM_H
#define CRYPTOBREAKER_BYTESTREAM_H

#include <string>
#include <vector>

#include <cstdint>

#include "Common.hpp"

namespace CB {
    class ByteStream {
        public:
            std::vector<Byte> data;
            std::string asciiDecoded, hexDecoded, Base64Decoded;
        public:
            ByteStream();
            ByteStream(const int size);
            ByteStream(std::string&, const coding);
            ByteStream(std::vector<Byte>&);
            ~ByteStream();

            size_t size();

            // encode as as an alternative to constructor
            // std::string encodeAs(const coding);
            std::string decodeAs(const coding);

            ByteStream operator^(const ByteStream&);
            ByteStream xorWith(const ByteStream&);
            ByteStream xorWith(const ByteStream&, const size_t&);

        private:
            Byte buildByteFromHex(char &a, char &b);
            std::string decodeBase64Block(std::vector<Byte>&);
            std::string buildHexFromByte(Byte &b);
            std::vector<Byte> encodeBase64Block(std::string &s);
    };
} // end of namespace CB

#endif //CRYPTOBREAKER_BYTESTREAM_H
