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
var found bool

func main() {
	file, err := os.Open(filename)
	if err != nil {
		fmt.Println("Couldn't open file: './4.txt'")
		os.Exit(1)
	}

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		if res := mcc.DecryptXor1ByteKey(scanner.Text()); len(res) > 0 {
			found = true
			fmt.Println("Found results:")
			for i, val := range res {
				fmt.Println(fmt.Sprintf("%d:\t%s", i, val))
			}
		}
	}

	if found {
		mcc.CorrectResult()
	} else {
		mcc.WrongResult()
	}

	if err := scanner.Err(); err != nil {
		fmt.Fprintln(os.Stderr, "reading standard input:", err)
	}
}
