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

#include "Utils.h"

using namespace std;

int main() {
    string input = "49276d206b696c6c696e6720796f757220627261696e206c696b" \
                        "65206120706f69736f6e6f7573206d757368726f6f6d";
    string output = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3V" \
                         "zIG11c2hyb29t";
    string translated;

    // string translated = Utils::hexToBase64(input);
    assert(translated == output);
}
