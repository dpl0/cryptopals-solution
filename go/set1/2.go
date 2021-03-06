/*
 * Fixed XOR
 * Write a function that takes two equal-length buffers and produces their XOR
 * combination.
 *
 * If your function works properly, then when you feed it the string:
 *
 * 1c0111001f010100061a024b53535009181c
 * ... after hex decoding, and when XOR'd against:
 *
 * 686974207468652062756c6c277320657965
 * ... should produce:
 *
 * 746865206b696420646f6e277420706c6179
 */

package main

import (
	"fmt"
	mcc "github.com/dpl0/mcclib"
)

const first = "1c0111001f010100061a024b53535009181c"
const second = "686974207468652062756c6c277320657965"
const result = "746865206b696420646f6e277420706c6179"

func main() {
	hexFirst := mcc.String2Bytes(first)
	hexSecond := mcc.String2Bytes(second)
	hexResult := mcc.String2Bytes(result)

	xor := mcc.ArrayXor(hexFirst, hexSecond)

	stringXOR := mcc.Bytes2String(xor)
	fmt.Printf("\nOur result: %s (%q)\n", stringXOR, xor)

	if mcc.AreEqualByteArrays(xor, hexResult) {
		mcc.CorrectResult()
	} else {
		mcc.WrongResult()
	}

	return
}
