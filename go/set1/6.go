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
	"math"
	"os"
	"reflect"
)

const filename = "./6.txt"

func BlockData(data []byte, size int) (ret [][]byte) {
	for i := 0; i < len(data); i += size {
		if i+size < len(data) {
			ret = append(ret, data[i:i+size])
		} else {
			ret = append(ret, data[i:])
		}
	}
	return
}

func TransposeData(data [][]byte) (ret [][]byte) {
	x, y := len(data[0]), len(data)
	ret = make([][]byte, x)
	for i := 0; i < x; i++ {
		ret[i] = make([]byte, y)
	}

	for i := 0; i < x; i++ {
		for j := 0; j < y; j++ {
			// Last block from data may have missing bytes!
			if j < len(data)-1 {
				ret[i][j] = data[j][i]
			} else {
				if i < len(data[j]) {
					ret[i][j] = data[j][i]
				}
			}
		}
	}
	return
}

func testBlocking() {
	data := []byte{1, 2, 3, 4, 5, 6, 6, 7, 8, 9, 10}
	result := [][]byte{[]byte{1, 2}, []byte{3, 4}, []byte{5, 6}, []byte{7, 8}, []byte{9, 10}}
	var size = 2

	if reflect.DeepEqual(result, BlockData(data, size)) {
		mcc.PrintWrongly("Blocking")
		os.Exit(1)
	} else {
		mcc.PrintCorrectly("Blocking")
	}
}

func testTransposing() {
	data := [][]byte{[]byte{1, 2}, []byte{3, 4}, []byte{5, 6}, []byte{7, 8}, []byte{9, 10}}
	result := [][]byte{[]byte{1, 3, 5, 7, 9}, []byte{2, 4, 6, 8, 10}}

	transposed := TransposeData(data)

	if len(result) != len(transposed) {
		mcc.PrintWrongly("Transposing")
		os.Exit(1)
	}
	if cap(result) != cap(transposed) {
		mcc.PrintWrongly("Transposing")
		os.Exit(1)
	}

	for i := 0; i < len(result); i++ {
		if len(result[i]) != len(transposed[i]) {
			mcc.PrintWrongly("Transposing")
			os.Exit(1)
		}
		if cap(result[i]) != cap(transposed[i]) {
			mcc.PrintWrongly("Transposing")
			os.Exit(1)
		}
		for j := 0; j < len(result[i]); j++ {
			if result[i][j] != transposed[i][j] {
				mcc.PrintWrongly("Transposing")
				os.Exit(1)
			}
		}
	}
	mcc.PrintCorrectly("Transposing")
}

func testHammingDistance() {
	s := []byte("this is a test")
	t := []byte("wokka wokka!!!")
	if mcc.HammingDistance(s, t) != 37 {
		mcc.PrintWrongly("Hamming distance")
		os.Exit(1)
	} else {
		mcc.PrintCorrectly("Hamming distance")
	}
}

func testBase64Decoding() {
	testBase64Decoding := func(base64 string, str string) {
		decoded := string(mcc.Base642Bytes(base64))
		if decoded != str {
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

func averageScores(numbers []float64) (ret float64) {
	for _, v := range numbers {
		ret += v
	}
	ret /= float64(len(numbers))
	return
}

	// // Find best keysize
	// // TODO - Eventually, put this in some function
	// // 1. Let KEYSIZE be the guessed length of the key; try from 2 to 40
	// var probableKeySizes [3]int
	// {
	// 	minorThreeDistances := [3]float32{1000, 1000, 1000}
	// 	for keysize := 2; keysize <= 40; keysize++ {
	// 		// 3. Take the first and second KEYSIZE worth of bytes, and find
	// 		// the normalized (dividing by keysize) edit distance between them.
	// 		// 4. The KEYSIZE with the min edit dist is probably the key.  You
	// 		// could proceed perhaps with the smallest 2-3.  Or take 4 KEYSIZE
	// 		// blocks instead of 2 and average the distances.
	// 		firstBlock := fileTextDecoded[:keysize]
	// 		secondBlock := fileTextDecoded[keysize : keysize*2]
	// 		thirdBlock := fileTextDecoded[keysize*2 : keysize*3]
	// 		fourthBlock := fileTextDecoded[keysize*3 : keysize*4]
	// 		editDistance1 := float32(mcc.HammingDistance(firstBlock, secondBlock)) / float32(keysize)
	// 		editDistance2 := float32(mcc.HammingDistance(secondBlock, thirdBlock)) / float32(keysize)
	// 		editDistance3 := float32(mcc.HammingDistance(thirdBlock, fourthBlock)) / float32(keysize)
	// 		editDistance := (editDistance1 + editDistance2 + editDistance3) / 3

	// 		// We could either use this, or a map with all the values and
	// 		// search later, but this is a little bit more complex, but much
	// 		// simpler to implement (Maybe I just don't wan't to use
	// 		// storage/heap :P)
	// 		if editDistance < minorThreeDistances[0] {
	// 			minorThreeDistances[0] = editDistance
	// 			probableKeySizes[0] = keysize
	// 		} else if editDistance < minorThreeDistances[1] {
	// 			minorThreeDistances[1] = editDistance
	// 			probableKeySizes[1] = keysize
	// 		} else if editDistance < minorThreeDistances[2] {
	// 			minorThreeDistances[2] = editDistance
	// 			probableKeySizes[2] = keysize
	// 		}
	// 	}

	// 	fmt.Println("Probable key sizes: ", probableKeySizes)
	// 	fmt.Println("Minor three distances: ", minorThreeDistances)
	// }


// Returns the calculated score of each keysize from min to max for data.
func calcKeySize(min int, max int, data []byte) (ret map[int]float32) {
    ret = make(map[int]float32)

    for i := min; i <= max; i++ {
        fmt.Println("\ti:", i)
        blocked := BlockData(data, i)
        fmt.Println("\tAfter blocking:", i)
        scores := make([]float32, len(blocked))

        for j := 0; j <= len(blocked); j += 2 {
            if j+1 > len(blocked) { continue }
            scores[j] = float32(mcc.HammingDistance(blocked[j], blocked[j+1])) / float32(j)
        }

        fmt.Println("\tscores:", scores)

        // Average score
        for s := range(scores) {
            ret[i] += float32(s)
        }
        ret[i] /= float32(max-min)
    }

    fmt.Println(ret)
    os.Exit(1)

    return ret
}

func main() {
	var fileText string
	fmt.Println("First of all, execute some tests")
	testHammingDistance()
	testBase64Decoding()
	testBlocking()
	testTransposing()
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
	// 1. Let KEYSIZE be the guessed length of the key; try from 2 to 40
    fmt.Println("Before calcKeySize")
    keysizes := calcKeySize(2, 40, fileTextDecoded)


	transposedData := make(map[int][][]byte)
    decryptionResults := make(map[int][]mcc.Decrypted)
	{
		// 5. Break the ciphertext into blocks of KEYSIZE length.
		blocks := make(map[int][][]byte)
        scores := make(map[int][]float64)
		for k, _ := range keysizes {
			blocks[k] = BlockData(fileTextDecoded, k)
		}

		// 6. Transpose the blocks: make a block that is the 1st byte of
		// every block, and a block that is the 2nd byte of every block...
		for keysize, blocked := range blocks {
			data := TransposeData(blocked)
			transposedData[keysize] = data
			fmt.Println("Attemting with transposed blocks of keysize: ", keysize)
			// 7. Solve each block as if it was single-character XOR, get the
			// keysize that produces the best-looking histogram.
			for _, block := range data {
                decrypt := mcc.DecryptOneByteXor(block)
                decryptionResults[keysize] = append(decryptionResults[keysize], decrypt)
				scores[keysize] = append(scores[keysize], decrypt.Score)
				scores[keysize] = []float64{averageScores(scores[keysize])}
			}
		}

		// Choose best keysize
		var finalKeysize int
		{
			var keysize int = 0
			var lower float64 = math.Inf(1)
			for k, score := range scores {
				if score[0] < lower {
					keysize = k
					lower = score[0]
				}
			}
			finalKeysize = keysize

			if finalKeysize == 0 {
				fmt.Println("ERROR: Haven't found valid key!")
				os.Exit(1)
			}
		}
		fmt.Println("Best keysize: ", finalKeysize)

    var key []byte
    var decrypted string
    {
        for _, v := range decryptionResults[finalKeysize] {
            key = append(key, v.Key[0])
        }
        decrypted = string(mcc.ArrayXor(key, fileTextDecoded))
    }

    fmt.Printf("Key: \"%s\"\n", key)
    fmt.Println("Decrypted: \n", decrypted)


	// 8. For each block, the single-byte XOR key that produces the best
	// looking histogram is the repeating-key XOR key byte for that block.
	// Put them together and you have the key.

	}

	return
}
