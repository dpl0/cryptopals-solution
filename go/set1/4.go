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
    "os"
    mcc "github.com/dpl0/mcclib"
)

var filename string = "4.txt"

func main() {
    file, err := os.Open(filename)
    if err != nil {
        fmt.Println("Couldn't open file: './4.txt'")
        os.Exit(1)
    }

    scanner := bufio.NewScanner(file)
    for scanner.Scan() {
        if res := mcc.DecryptXor1ByteKey(scanner.Text()); len(res) > 0 {
            fmt.Println("Found results:")
            for _, val := range res {
                mcc.PrintCorrectly("\t"+val)
            }
        }
    }

    if err := scanner.Err(); err != nil {
        fmt.Fprintln(os.Stderr, "reading standard input:", err)
    }
}
