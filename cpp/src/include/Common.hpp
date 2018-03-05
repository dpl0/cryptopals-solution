#ifndef CRYPTOBREAKER_COMMON_H
#define CRYPTOBREAKER_COMMON_H

#include <vector>
#include <cstdint>

// Common types through the library.
using Byte = uint8_t;
using ByteStream = std::vector<Byte>;

enum class coding : Byte {
    ascii,
    hex,
    base64,
};

#endif //CRYPTOBREAKER_COMMON_H
