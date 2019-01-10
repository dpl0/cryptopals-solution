/*
 * Single-byte XOR cipher
 *
 * The hex encoded string:
 *
 * 1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736
 * ... has been XOR'd against a single character. Find the key, decrypt the
 * message.
 *
 * You can do this by hand. But don't: write code to do it for you.
 *
 * How? Devise some method for "scoring" a piece of English plaintext.
 * Character frequency is a good metric. Evaluate each output and choose the
 * one with the best score.
 *
 * Achievement Unlocked
 * You now have our permission to make "ETAOIN SHRDLU" jokes on Twitter.
 */

package main

import (
	"fmt"
	mcc "github.com/dpl0/mcclib"
)

const crypt = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a3" +
	"93b3736"
const value = "Cooking MC's like a pound of bacon"

func main() {
    fmt.Println("Executing exercice 3 in set 1")
	hexCrypt := mcc.String2Bytes(crypt)
	result := mcc.DecryptOneByteXor(hexCrypt)
    fmt.Println("Result: ",string(result.Data))
	if value == string(result.Data) {
		mcc.CorrectResult()
	} else {
		mcc.WrongResult()
	}
	return
}
