package mcclib

import (
    "fmt"
    "os"
)


// Compare bytes with these function? Worth it?
func TestEqual(f []byte, s []byte) bool {
    // TODO
    return false
}

func CorrectResult() {
    fmt.Printf("\x1b[6;30;42m" + "Your code is correct! :)" + "\x1b[0m" + "\n")
}

func WrongResult() {
    fmt.Printf("\x1b[6;30;42m" + "Your code is wrong! :(" + "\x1b[0m" + "\n")
}

func HandleError(err error) {
    fmt.Fprintf(os.Stderr, "\nmcclib error: %s\n", err)
    os.Exit(1)
}
