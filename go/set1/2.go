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
    "bytes"
    "fmt"
    mcc "github.com/dpl0/mcclib"
)

const first = "1c0111001f010100061a024b53535009181c"
const second = "686974207468652062756c6c277320657965"
const result = "746865206b696420646f6e277420706c6179"

func main() {
    stringFirst := mcc.String2Hex(first)
    stringSecond := mcc.String2Hex(second)
    stringResult := mcc.String2Hex(result)
    fmt.Printf("First byte stream: %q (%q)\n", first, stringFirst)
    fmt.Printf("Second byte stream: %q (%q)\n", second, stringSecond)
    fmt.Printf("Correct result: %q (%q)\n", result, stringResult)

    xor, err := mcc.ArrayXor(mcc.String2Hex(first), mcc.String2Hex(second))
    if (err != nil) {
        mcc.HandleError(err)
    }

    stringXOR := mcc.Hex2String(xor)
    fmt.Printf("\nOur result: %q (%q)\n", stringXOR, xor)

    if cmp := bytes.Compare(xor, mcc.String2Hex(result)); cmp != 0 {
        mcc.CorrectResult()
    } else {
        mcc.WrongResult()
    }
    return
}
