package mcclib

// Applies the XOR cipher with key k to s.
func ArrayXor(k []byte, s []byte) (ret []byte) {
    if len(k) == 0 || len(s) == 0 {
        return nil
    }

	ret = make([]byte, len(s))
	for i, _ := range ret {
		ret[i] = s[i] ^ k[i%len(k)]
	}
	return
}
