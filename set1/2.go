/*
 * Fixed XOR
 * Write a function that takes two equal-length buffers and produces their XOR combination.
 *
 * If your function works properly, then when you feed it the string:
 *
 * 1c0111001f010100061a024b53535009181c
 * ... after hex decoding, and when XOR'd against:
 *
 * 686974207468652062756c6c277320657965
 * ... should produce:
 *
 * 746865206b696420646f6e277420706c6179
 */

package main

import (
	"fmt"
	"strings"
	"strconv"
)

var first = "1c0111001f010100061a024b53535009181c"
var second = "686974207468652062756c6c277320657965"
var result = "746865206b696420646f6e277420706c6179"

// Perform XOR for two arrays.
func arrayxor(f []byte, s []byte) []byte {
	fmt.Printf("f: %x\ns: %x\n", f, s)
	l := len(f)
	if l != len(s) {
		return nil
	}

	ret := make([]byte, l, l)
	for i := range ret {
		fmt.Printf("f[%d]: %x, s[%d]: %x, ^: %x\n", i, byte(f[i]), i, byte(s[i]), f[i] ^ s[i])
		ret[i] = byte(f[i]) ^ byte(s[i])
	}
	return ret
}

// Returns the hexadecimal values of a string with hexadecimal.
func String2hex(s *[]byte) (ret *[]byte) {
	ret := make([]byte, len(*s), cap(*s))
	start := 0
	if (*s)[0] == '0' && (*s[1] == 'x' || *s[1] == 'X') {
		start = 2
	}

	// Appends byte if needed.
	if len(*s) % 2 != 0 {
		last := *s[len(s)-1]
		*s = *s[:len(s)-1]
		*s = append(s, '0', last)
	}

	for i := 0 ; i <= len(s); i+=2 {
		strconv.ParseInt(*s[i:i+1], 16, 8)
	}
	return &ret
}

func main() {
	for i,val := range first {
		fmt.Printf("%x", first)
	}
	fmt.Printfln("")
	for i,val := range String2hex(first) {
		fmt.Printf("%x", val)
	}
	fmt.Printfln("")
	fmt.Printf("First byte stream: %q\n", first)
	fmt.Printf("Second byte stream: %q\n", second)
	fmt.Printf("Correct result: %q\n", result)
	xor := arrayxor([]byte(first), []byte(second))
	fmt.Printf("Our result: %s\n", xor)
	
	if cmp := strings.Compare(result, string(xor)); cmp != 0 {
		fmt.Printf("Your code is wrong!")
	} else {
		fmt.Printf("Your code is correct! :)")
	}
	return
}
