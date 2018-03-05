// Copyright 2016 dpl

/*
 * Fixed XOR
 *
 * Write a function that takes two equal-length buffers and produces their XOR combination.
 *
 * If your function works properly, then when you feed it the string:
 * "1c0111001f010100061a024b53535009181c"
 *
 * ... after hex decoding, and when XOR'd against:
 * "686974207468652062756c6c277320657965"
 *
 * ... should produce:
 * "746865206b696420646f6e277420706c6179"
 *
 */

#include <string>
#include <iostream>
#include <assert.h>

#include "Utils.hpp"
#include "ByteStream.hpp"

int main() {
    std::string intputStr{"1c0111001f010100061a024b53535009181c"};
    std::string xorToStr{"686974207468652062756c6c277320657965"};
    std::string outputStr{"746865206b696420646f6e277420706c6179"};
    CB::ByteStream input  = CB::ByteStream(intputStr, coding::hex);
    CB::ByteStream xorTo  = CB::ByteStream(xorToStr,  coding::hex);
    CB::ByteStream output = CB::ByteStream(outputStr, coding::hex);

    // ByteStream inputBS =  CB::Utils::encodeAsHex(input);
    // ByteStream xorToBS =  CB::Utils::encodeAsHex(xorTo);
    // ByteStream outputBS = CB::Utils::encodeAsHex(output);

    // ByteStream xoredBS = CB::Utils::XorByteStreams(inputBS, xorToBS);
    CB::ByteStream xoredBS = input.xorWith(xorTo);
    // ByteStream xoredBS = input ^ xorTo;

    // assert(CB::Utils::decodeAsHex(xoredBS) == output);
    assert(input.xorWith(xorTo).decodeAs(coding::ascii) == output.asciiDecoded);
}



