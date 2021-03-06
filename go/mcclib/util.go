package mcclib

import (
	"fmt"
	"os"
)

// Compare bytes to not depend on the bytes lib
func AreEqualByteArrays(f []byte, s []byte) bool {
	if len(f) != len(s) {
		return false
	}

	for i, _ := range f {
		if f[i] != s[i] {
			return false
		}
	}
	return true
}

func CorrectResult() {
	fmt.Printf("\x1b[6;30;42m" + "Your code is correct! :)" + "\x1b[0m" + "\n")
}

func WrongResult() {
	fmt.Printf("\x1b[6;30;41m" + "Your code is wrong! :(" + "\x1b[0m" + "\n")
}

func PrintCorrectly(s string) {
	fmt.Printf("\x1b[6;30;42m" + s + "\x1b[0m" + "\n")
}

func PrintWrongly(s string) {
	fmt.Printf("\x1b[6;30;41m" + s + "\x1b[0m" + "\n")
}

func HandleError(err error) {
	fmt.Fprintf(os.Stderr, "\nmcclib error: %s\n", err)
	os.Exit(1)
}
