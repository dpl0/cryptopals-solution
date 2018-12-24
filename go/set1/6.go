/*
 *
 * Break repeating-key XOR
 *
 * There's a file here. It's been base64'd after being encrypted with
 * repeating-key XOR.  Decrypt it.
 *
 * Here's how:
 *
 *     1. Let KEYSIZE be the guessed length of the key; try values from 2 to
 *     (say) 40.
 *
 *     2. Write a function to compute the edit distance/Hamming distance
 *     between two strings. The Hamming distance is just the number of
 *     differing bits. The distance between:
 *
 *     "this is a test"
 *     and
 *     "wokka wokka!!!"
 *
 *     is 37. Make sure your code agrees before you proceed.
 *
 *     3. For each KEYSIZE, take the first KEYSIZE worth of bytes, and the
 *     second KEYSIZE worth of bytes, and find the edit distance between them.
 *     Normalize this result by dividing by KEYSIZE.
 *
 *     4. The KEYSIZE with the smallest normalized edit distance is probably
 *     the key.  You could proceed perhaps with the smallest 2-3 KEYSIZE
 *     values. Or take 4 KEYSIZE blocks instead of 2 and average the distances.
 *
 *     5. Now that you probably know the KEYSIZE: break the ciphertext into
 *     blocks of KEYSIZE length.
 *
 *     6. Now transpose the blocks: make a block that is the first byte of
 *     every block, and a block that is the second byte of every block, and so
 *     on.
 *
 *     7. Solve each block as if it was single-character XOR. You already have
 *     code to do this.
 *
 *     8. For each block, the single-byte XOR key that produces the best
 *     looking histogram is the repeating-key XOR key byte for that block. Put
 *     them together and you have the key.
 *
 * This code is going to turn out to be surprisingly useful later on. Breaking
 * repeating-key XOR ("Vigenere") statistically is obviously an academic
 * exercise, a "Crypto 101" thing. But more people "know how" to break it than
 * can actually break it, and a similar technique breaks something much more
 * important.  No, that's not a mistake.
 *
 * We get more tech support questions for this challenge than any of the other
 * ones. We promise, there aren't any blatant errors in this text. In
 * particular: the "wokka wokka!!!" edit distance really is 37.
 *
 */

package main

import (
	"bufio"
	"fmt"
	mcc "github.com/dpl0/mcclib"
	"os"
)

const filename = "./6.txt"

func checkHammingDistance() {
	s := []byte("this is a test")
	t := []byte("wokka wokka!!!")
	if mcc.HammingDistance(s, t) != 37 {
		mcc.PrintWrongly("Hamming distance")
		os.Exit(1)
	} else {
		mcc.PrintCorrectly("Hamming distance")
	}
}

func checkBase64Decoding() {
	testBase64Decoding := func(base64 string, str string) {
		decoded := string(mcc.Base642Bytes(base64))
		if !mcc.AreEqualStrings(decoded, str) {
			os.Exit(1)
		}
	}

	// Taken as exemples
	testBase64Decoding("aGkgdGhlcmUh", "hi there!")
	mcc.PrintCorrectly("Base64 decoding 1/3")
	testBase64Decoding("aGkgdGhlcmU=", "hi there")
	mcc.PrintCorrectly("Base64 decoding 2/3")
	testBase64Decoding("aGkgdGhlcg==", "hi ther")
	mcc.PrintCorrectly("Base64 decoding 3/3")
}

func main() {
	var fileText string
    fmt.Println("First of all, execute some tests")
	checkHammingDistance()
	checkBase64Decoding()
    fmt.Println("Ok, starting with the exercise!")

	file, err := os.Open(filename)
	if err != nil {
		fmt.Println("Couldn't open file: " + filename)
		os.Exit(1)
	}

	scanner := bufio.NewScanner(file)
	if err := scanner.Err(); err != nil {
		fmt.Fprintln(os.Stderr, "reading standard input:", err)
	}

	for scanner.Scan() {
		fileText += scanner.Text()
	}

	fileTextDecoded := mcc.Base642Bytes(fileText)

    // Find best keysize
    // TODO - Eventually, put this in some function
    // 1. Let KEYSIZE be the guessed length of the key; try from 2 to 40
    var probableKeySizes [3]int
    {
        minorThreeDistances := [3]float32{1000, 1000, 1000}
        for keysize := 2; keysize <= 40; keysize++ {
            // 3. Take the first and second KEYSIZE worth of bytes, and find
            // the normalized (dividing by keysize) edit distance between them.
            // 4. The KEYSIZE with the min edit dist is probably the key.  You
            // could proceed perhaps with the smallest 2-3.  Or take 4 KEYSIZE
            // blocks instead of 2 and average the distances.
            firstBlock  := fileTextDecoded[:keysize]
            secondBlock := fileTextDecoded[keysize:keysize*2]
            thirdBlock  := fileTextDecoded[keysize*2:keysize*3]
            fourthBlock := fileTextDecoded[keysize*3:keysize*4]
            editDistance1 := float32(mcc.HammingDistance(firstBlock, secondBlock))/float32(keysize)
            editDistance2 := float32(mcc.HammingDistance(secondBlock, thirdBlock))/float32(keysize)
            editDistance3 := float32(mcc.HammingDistance(thirdBlock, fourthBlock))/float32(keysize)
            editDistance := (editDistance1 + editDistance2 + editDistance3)/3

            // We could either use this, or a map with all the values and
            // search later, but this is a little bit more complex, but much
            // simpler to implement (Maybe I just don't wan't to use
            // storage/heap :P)
            if (editDistance < minorThreeDistances[0]) {
                minorThreeDistances[0] = editDistance
                probableKeySizes[0] = keysize
            } else if (editDistance < minorThreeDistances[1]) {
                minorThreeDistances[1] = editDistance
                probableKeySizes[1] = keysize
            } else if (editDistance < minorThreeDistances[2]) {
                minorThreeDistances[2] = editDistance
                probableKeySizes[2] = keysize
            }
        }

        fmt.Println("Probable key sizes: ", probableKeySizes)
        fmt.Println("Minor three distances: ", minorThreeDistances)
    }

    {
        // 5. Break the ciphertext into blocks of KEYSIZE length.
        blocks := make(map[int][][]byte)
        for _, keysize := range(probableKeySizes) {
            // Put into blocks by keysize
            for i := 0; i < len(fileTextDecoded); i += keysize {
                if i+keysize < len(fileTextDecoded) {
                     blocks[keysize] = append(blocks[keysize], fileTextDecoded[i:i+keysize])
                } else {
                     blocks[keysize] = append(blocks[keysize], fileTextDecoded[i:])
                }
            }
        }

        // 6. Transpose the blocks: make a block that is the 1st byte of
        // every block, and a block that is the 2nd byte of every block...
        transposedData := make(map[int][][]byte)
        for keysize, blockedData := range(blocks) {
            var transposed []byte
            for _, block := range(blockedData) {
                for j := 0; j < keysize; j++ {
                    if (j < len(block)) {
                        transposed = append(transposed, block[j])
                    }
                }
            }
            fmt.Printf("BEFORE APPEND transposedData[%d]: %s\n\n", keysize, transposedData[keysize])
            transposedData[keysize] = append(transposedData[keysize], transposed)
            fmt.Printf("AFTER APPEND transposedData[%d]: %s\n\n", keysize, transposedData[keysize])
        }

        fmt.Println("Data length: ",  len(fileTextDecoded))
        for keysize, trData := range(transposedData) {
            fmt.Println("Keysize: ", keysize, "has ", len(trData), "blocks")
        }

        fmt.Println(transposedData[2])


        // 7. Solve each block as if it was single-character XOR.

        // 8. For each block, the single-byte XOR key that produces the best
        // looking histogram is the repeating-key XOR key byte for that block.
        // Put them together and you have the key.
    }


	return
}
