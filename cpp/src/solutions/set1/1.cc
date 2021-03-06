// Copyright 2016 dpl

/*
 * Convert hex to base64
 *
 * The string:
 * "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e" \
 * "6f7573206d757368726f6f6d"
 *
 * Should produce:
 * SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t
 *
 * So go ahead and make that happen. You'll need to use this code for the rest
 * of the exercises.
 *
 * Cryptopals Rule: Always operate on raw bytes, never on encoded strings. Only
 * use hex and base64 for pretty-printing.
 */


#include <string>
#include <iostream>
#include <assert.h>

// #include "Utils.hpp"
#include "Common.hpp"
#include "ByteStream.hpp"

int main() {
    std::string input = "49276d206b696c6c696e6720796f757220627261696e206c696b" \
                        "65206120706f69736f6e6f7573206d757368726f6f6d";
    std::string output = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3V" \
                         "zIG11c2hyb29t";

    // std::string translated = CB::Utils::hexToBase64(input);
    CB::ByteStream stream = CB::ByteStream(input, coding::base64);
    std::string translated = stream.decodeAs(coding::ascii);

    // std::string translated = CB::ByteStream(input).decodeAs("ASCII");
    assert(translated == output);
}
