package mcclib

// Applies the XOR cipher with key k to s.
func ArrayXor(k []byte, s []byte) []byte {
	ret := make([]byte, len(s))
	for i := range ret {
		ret[i] = s[i] ^ k[i%len(k)]
	}
	return ret
}
