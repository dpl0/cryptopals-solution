#ifndef CRYPTOBREAKER_XOR_H
#define CRYPTOBREAKER_XOR_H

#include "Common.h"

namespace Xor {
    ByteStream XorByteStreams(const ByteStream&, const ByteStream&,
                                  const std::size_t&);
    ByteStream XorByteStreams(const ByteStream&, const ByteStream&);

} // end namespace Xor

#endif //CRYPTOBREAKER_XOR_H
