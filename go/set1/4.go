/*
 * Detect single-character XOR
 *
 * One of the 60-character strings in this file (4.txt) has been encrypted by
 * single-character XOR.
 *
 * Find it.
 *
 * (Your code from #3 should help.)
 */

package main

import (
	"bufio"
	"fmt"
	mcc "github.com/dpl0/mcclib"
	"os"
)

var filename string = "4.txt"
var result string = "Now that the party is jumping\n"

func main() {
	file, err := os.Open(filename)
	if err != nil {
		fmt.Println("Couldn't open file: './4.txt'")
		os.Exit(1)
	}

	scanner := bufio.NewScanner(file)
	if err := scanner.Err(); err != nil {
		fmt.Fprintln(os.Stderr, "reading standard input:", err)
	}

	var decryptedSet []mcc.Decrypted
	for scanner.Scan() {
		data := mcc.String2Bytes(scanner.Text())
        decrypted := mcc.DecryptOneByteXor(data)
		decryptedSet = append(decryptedSet, decrypted)
	}

	// Get best result
	best := mcc.GetBestDecrypted(decryptedSet)
    fmt.Printf("Best solution is: %q\n", string(best.Data))
    fmt.Println(best)

	if string(best.Data) == result {
		mcc.CorrectResult()
	} else {
		mcc.WrongResult()
	}
}
