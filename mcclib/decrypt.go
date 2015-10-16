package mcclib

// Decrypt XOR'ed text with only one character as key.
func DecryptXOR1ByteKey(stream string) (ret []string) {
	hexCrypt :=  String2Hex(stream)
	// Key has to be of type []byte, even if just one byte.
	key  := []byte{0}

	for i := 0; i <= 255; i++ {
		key[0] = byte(i)
		decrypted := KeyXOR(key, []byte(hexCrypt))
		freq := SymbolFrequency(decrypted)
		if IsDistSimilarTo(freq, EnglishDist, 0.1, 16) {
			ret = append(ret, string(decrypted))
		}
	}
	return
}

