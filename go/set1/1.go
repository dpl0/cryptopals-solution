/*
 * Convert hex to base64
 *
 * The string:
 * 49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d
 *
 * Should produce:
 * SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t
 *
 * So go ahead and make that happen. You'll need to use this code for the rest
 * of the exercises.
 *
 * Cryptopals Rule Always operate on raw bytes, never on encoded strings. Only
 * use hex and base64 for pretty-printing.
 */

package main

import (
	"fmt"
	mcc "github.com/dpl0/mcclib"
)

// Symbols used in base64.
const test = "49276d206b696c6c696e6720796f757220627261696e206c696b6520612070" +
	"6f69736f6e6f7573206d757368726f6f6d"
const result = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hy" +
	"b29t"

func main() {
	fmt.Printf("Test string: %q len(test): %d\n", test, len(test))
	fmt.Printf("Correct result: %q len(result): %d\n", result, len(result))

	base64 := mcc.Hex2Base64(mcc.String2Hex(test))
	fmt.Printf("Our result: %s\n", base64)

	if mcc.AreEqualByteArrays(base64, []byte(result)) {
		mcc.CorrectResult()
	} else {
		mcc.WrongResult()
	}
	return
}
