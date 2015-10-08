package krypt

// The Matasano Crypto Challenge Crypto library implements a set of
// cryptography primitives to be used with the
import(
	"strconv"
)

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

// Returns the hexadecimal values of a string with hexadecimal.
func String2hex(s []byte) (ret []byte) {
	start := 0
	if s[0] == '0' && (s[1] == 'x' || s[1] == 'X') {
		start = 2
	}

	// Appends byte if needed.
	if len(s) % 2 != 0 {
		last := s[len(s)-1]
		s := s[:len(s)-1]
		s = append(s, '0', last)
	}

	for i := 0 ; i <= len(s); i+=2 {
		strconv.ParseInt(s[i:i+1], 16, 8)
	}
	return
}

// Hexadecimal to base 64.
func Hex2base64(hex []byte) string {
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
	return string(ret)
}
