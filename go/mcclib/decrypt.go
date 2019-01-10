package mcclib

// import "fmt"
import "math"

type DecryptResult struct {
	Data             []byte
	Key              []byte
	Count            LetterCount
	ChiSquaredResult float64
}

type ChiSquareResults map[float64][]byte
type BCCResults map[byte]float64

// Given a set of ChiSquareResults, find the one with the best score
func GetBestChiSquareDist(distributions ChiSquareResults) []byte {
	var key []byte
	var smaller = math.Inf(1)
	for testRes, k := range distributions {
		if testRes < smaller {
			smaller = testRes
			key = k
		}
	}
	return key
}

// Given a set of DecryptResults, find the one with best score from Chi Squared
func GetBestDecryptResult(results []DecryptResult) (ret DecryptResult) {
	ret = DecryptResult{nil, nil, nil, math.Inf(1)}
	for _, result := range results {
		if result.ChiSquaredResult < ret.ChiSquaredResult {
			ret = result
		}
	}
	return
}

// By default, decrypt assuming english text
func DecryptOneByteXor(hexCrypt []byte) DecryptResult {
	return DecryptOneByteXorDist(hexCrypt, EnglishDist)
}

// Decrypt XOR with one byte key
func DecryptOneByteXorDist(hexCrypt []byte, dist LetterDist) DecryptResult {
	// Store all possible results of decripting with any key, and evaluate and
	// return the best one.
	chiSquareTestResults := make(ChiSquareResults)
	for i := 0; i <= 255; i++ {
		key := []byte{byte(i)}
		decrypted := ArrayXor(key, hexCrypt)
		// test := ChiSquaredTestDist(string(decrypted), dist)
		test := BhattacharyyaCoefficientDist(string(decrypted), dist)
		chiSquareTestResults[test] = key
	}

	key := GetBestDist(chiSquareTestResults)
	decrypted := ArrayXor(key, hexCrypt)
	freq := SymbolCount(decrypted)
	chiTest := ChiSquaredTestDist(string(decrypted), dist)
	return DecryptResult{decrypted, key, freq, chiTest}
}
