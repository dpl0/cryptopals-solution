#include <vector>
#include <cstdint>
#include <cassert>

#include "ByteStream.hpp"
#include "Utils.hpp"
#include "Common.hpp"

const std::string hexSymbols = "0123456789abcdef";
const std::string base64Symbols = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" \
                          "abcdefghijklmnopqrstuvwxyz0123456789+/";

namespace CB {
    ByteStream::ByteStream() {}
    ByteStream::~ByteStream() {} // TODO Memory management?!

    ByteStream::ByteStream(const int size): data(std::vector<Byte>(size)) {}
    ByteStream::ByteStream(std::string &s, const coding as)
    {
        if (as == coding::ascii) {
            asciiDecoded = s;
            data = std::vector<Byte>{s.begin(), s.end()};
        } else if (as == coding::hex) {
            assert(s.length() % 2 == 0);
            data = std::vector<Byte>{};

            // TODO This can be improved with std algorithms.
            for (int i = 0; i < s.size(); i+=2) {
                data.push_back(buildByteFromHex(s[i], s[i+1]));
            }
        } else if (as == coding::base64) {
            auto quartets = Utils::splitInChunks(s, 4);
            data = std::vector<Byte>{};

            for (auto c : quartets) {
                // TODO Doesn't work properly
                for (auto b: encodeBase64Block(c))
                    data.push_back(b);
            }
        }
    }

    ByteStream::ByteStream(std::vector<Byte> &d) : data(d) {}

    size_t ByteStream::size() {
        return data.size();
    }

    std::string ByteStream::decodeAs(const coding as) {
        std::string retval;
        if (as == coding::ascii) {
            retval = std::string{begin(data), end(data)};
        } else if (as == coding::hex) {
            for (auto b: data) {
                retval += buildHexFromByte(b);
            }
        } else if (as == coding::base64) {
            for (auto b: Utils::splitInChunks(data, 3)) {
                 retval.append(decodeBase64Block(b));
            }
        }
        return retval;
    }

    ByteStream operator^(const ByteStream& lhs, const ByteStream& rhs) {
        const size_t smallest = lhs.data.size() < rhs.data.size() ?
                                    lhs.data.size() : rhs.data.size();
        ByteStream retval(smallest);
        for (size_t i = 0; i < smallest; i++) {
            retval.data[i] = lhs.data[i] ^ rhs.data[i];
        }
        return retval;
    }

    ByteStream ByteStream::xorWith(const ByteStream &other) {
        size_t smallest = data.size() < other.data.size() ?
                                    this->data.size() : other.data.size();
        ByteStream retval(smallest);
        for (size_t i = 0; i < smallest; i++) {
            retval.data[i] = this->data[i] ^ other.data[i];
        }
        return retval;
    }

    ByteStream ByteStream::xorWith(const ByteStream &other, const size_t &size) {
        if (size > this->data.size() or size > other.data.size())
            return ByteStream();
        ByteStream retval(size);
        for (size_t i = 0; i < size; i++) {
            retval.data[i] = this->data[i] ^ other.data[i];
        }
        return retval;
    }

    // Auxiliary functions
    Byte ByteStream::buildByteFromHex(char &a, char &b) {
        size_t aLocation = hexSymbols.find(tolower(a));
        size_t bLocation = hexSymbols.find(tolower(b));
        return (uint16_t) aLocation << 4 | bLocation;
    }

    std::string ByteStream::buildHexFromByte(Byte& b) {
        char topChar{hexSymbols[(b & 0xf0) >> 4]};
        char bottomChar{hexSymbols[b & 0x0f]};
        return std::string{topChar, bottomChar};
    }

    std::string ByteStream::decodeBase64Block(std::vector<Byte> &byte) {
        // Indicates if this is the last round, we'll have to add '='*lackingChars.
        const bool isLastRound = (byte.size() < 3);
        const int lackingChars = (isLastRound ? 3 - byte.size() : 0);

        const Byte firstByte = byte[0];
        const Byte secondByte = (isLastRound && lackingChars == 2) ?
                    Byte{0} : byte[1];
        const Byte thirdByte = (isLastRound && lackingChars >= 1) ?
                    Byte{0} : byte[2];

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

    std::vector<Byte> ByteStream::encodeBase64Block(std::string &s) {
        return std::vector<Byte>{};
    }

} // end of namespace CB

