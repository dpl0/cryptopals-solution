#include "Xor.hpp"
#include "Utils.hpp"

namespace Xor {
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
} // end namespace Xor


