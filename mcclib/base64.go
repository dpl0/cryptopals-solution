package mcclib

import(
)

// This file implement all that you need to convert hexadecimal to base64.

// Creates a base64 block (4 symbols) from 3 bytes.
func hexblock2base64(hex []byte) (ret []byte) {
	var s = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
	one := hex[0] & 0xfc >> 2
	two := hex[0] & 0x03 << 4 | hex[1] & 0xf0 >> 4
	three := hex[1] & 0x0f << 2 | hex[2] & 0xc0 >> 6
	four := hex[2] & 0x3f

	ret = append(ret, s[one], s[two], s[three], s[four])
	return
}

// Hexadecimal to base 64.
func Hex2base64(hex []byte) []byte {
	var ret []byte;
	// Add padding if needed.
	for len(hex)%3 != 0 {
		hex = append(hex, byte(0))
	}

	// Perform transformation.
	for i := 0; i < len(hex); i += 3 {
		ret = append(ret, hexblock2base64(hex[i:i+3])...)
	}

	// Modify padding if needed.
	l := len(ret)
	for i := l - 3; i < l; i++ {
		if ret[i] == 'A' {
			ret[i] = '='
		}
	}
	return ret
}

