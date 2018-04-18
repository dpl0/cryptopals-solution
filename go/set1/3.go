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

const crypt = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736"

func main() {
    hexCrypt := mcc.String2Hex(crypt)
    // Key has to be of type []byte, even if just one byte.
    key := []byte{0}

    for i := 0; i <= 255; i++ {
        key[0] = byte(i)
        decrypted := mcc.KeyXOR(key, []byte(hexCrypt))
        freq := mcc.SymbolFrequency(decrypted)
        if mcc.IsDistSimilarTo(freq, mcc.EnglishDist, 0.1, 16) {
            fmt.Printf("Key: %s\nCryptogram: %s\n", key, decrypted)
            fmt.Println(mcc.CorrectResult)
            return
        }
    }
    fmt.Println(mcc.WrongResult)
    return
}
