package mcclib

import (
    "fmt"
    "os"
)

// Utils for solving cryptopals problems.

// * Define strings when working correctly, with colors
const CorrectResult = "\x1b[6;30;42m" + "Your code is correct! :)\n" + "\x1b[0m"
const WrongResult = "\x1b[6;30;41m" + "Your code is wrong! :(\n" + "\x1b[0m"

func PrintCorrectly(str string) {
    fmt.Printf("\x1b[6;30;42m"+str+"\x1b[0m\n");
}
func PrintWrongly(str string) {
    fmt.Printf("\x1b[6;30;41m"+str+"\x1b[0m\n");
}

// * Define error handling function from Go (as in 2.go)
func HandleError(err error) {
    fmt.Fprintf(os.Stderr, "\nmcclib error: %s\n", err)
    os.Exit(1)
}
