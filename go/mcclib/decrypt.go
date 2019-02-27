package mcclib

import (
    "fmt"
    "math"
)

type Decrypted struct {
    Key []byte
    Data []byte
    Score float64
}

func (d Decrypted) String() string {
    return fmt.Sprintf("\n\tKey: %v [%q]\n\tData: %q\n\tScore: %v\n", d.Key, d.Key, d.Data, d.Score)
}


// Given a set of ChiSquareResults, find the one with the best score
func GetBestChiSquareDist(distributions map[byte]float64) (bestKey byte) {
	var smaller = math.Inf(1)
	for k, score := range distributions {
		if score < smaller {
			smaller = score
			bestKey = k
		}
	}
	return
}

func GetBestDecrypted(set []Decrypted) (ret Decrypted) {
    smaller := math.Inf(1)
	for _, decripted := range set {
		if decripted.Score < smaller {
			smaller = decripted.Score
            ret = decripted
		}
	}
	return
}

// By default, decrypt assuming english text
func DecryptOneByteXor(hexCrypt []byte) Decrypted {
	return DecryptOneByteXorDist(hexCrypt, EnglishDist)
}

// Decrypt XOR with one byte key
func DecryptOneByteXorDist(hexCrypt []byte, dist LetterDist) Decrypted {
	// Store all possible results of decripting with any key, and evaluate and
	// return the best one.
	decriptedSet := make([]Decrypted, 256)
	for i := 0; i <= 255; i++ {
		key := byte(i)
		decrypted := ArrayXor([]byte{key}, hexCrypt)
		score := ChiSquaredTestDist(string(decrypted), dist)
		decriptedSet[i] = Decrypted{[]byte{key}, decrypted, score}
	}
	return GetBestDecrypted(decriptedSet)
}
