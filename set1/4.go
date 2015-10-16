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
	mcc "github.com/dplbsd/mcclib"
	"os"
)

// We have to cat the stuff to the program instead of just executing it.
// $ cat set1/4.txt | go run set1/4.go # This should be enough.
func main() {
	scanner := bufio.NewScanner(os.Stdin)
	for scanner.Scan() {
		if res := mcc.DecryptXOR1ByteKey(scanner.Text()); len(res) > 0 {
			fmt.Println("Found results:")
			for _, val := range res {
				fmt.Printf("\t%v", val)
			}
		}
	}
	if err := scanner.Err(); err != nil {
		fmt.Fprintln(os.Stderr, "reading standard input:", err)
	}
}
