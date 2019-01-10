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

	var decrypted []mcc.DecryptResult
	for scanner.Scan() {
		data := mcc.String2Bytes(scanner.Text())
		decrypted = append(decrypted, mcc.DecryptOneByteXor(data))
	}

	for _, d := range decrypted {
		fmt.Println(d.ChiSquaredResult, "-", string(d.Data))
		fmt.Println()
	}

	// Get best result
	result := mcc.GetBestDecryptResult(decrypted)
	fmt.Println(string(result.Data))

	// if found {
	// 	mcc.CorrectResult()
	// } else {
	// 	mcc.WrongResult()
	// }
}
