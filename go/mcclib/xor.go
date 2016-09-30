package mcclib

// Returns the XOR of two arrays of same length.
func ArrayXOR(f []byte, s []byte) []byte {
	l := len(f)
	if l != len(s) {
		return nil
	}
	ret := make([]byte, l, l)
	for i := range ret {
		ret[i] = f[i] ^ s[i]
	}
	return ret
}

// Applies the XOR cipher to s.
func KeyXOR(k []byte, s []byte) []byte {
	l := len(s)
	lk := len(k)
	ret := make([]byte, l, l)
	for i := range ret {
		ret[i] = s[i] ^ k[i%lk]
	}
	return ret
}
