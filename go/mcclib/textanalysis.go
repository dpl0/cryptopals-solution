package mcclib

import (
	"math"
	"strings"
	// "fmt"
)

type LetterDist map[byte]float64
type LetterCount map[byte]int

// Distribution of letters in English, from:
// http://www.data-compression.com/english.html
// No punctuation letters.
var EnglishDist = LetterDist{
	'a': 0.0651738, 'b': 0.0124248, 'c': 0.0217339,
	'd': 0.0349835, 'e': 0.1041442, 'f': 0.0197881,
	'g': 0.0158610, 'h': 0.0492888, 'i': 0.0558094,
	'j': 0.0009033, 'k': 0.0050529, 'l': 0.0331490,
	'm': 0.0202124, 'n': 0.0564513, 'o': 0.0596302,
	'p': 0.0137645, 'q': 0.0008606, 'r': 0.0497563,
	's': 0.0515760, 't': 0.0729357, 'u': 0.0225134,
	'v': 0.0082903, 'w': 0.0171272, 'x': 0.0013692,
	'y': 0.0145984, 'z': 0.0007836, ' ': 0.1918182,
}

// Returns the frequency of given byte in s
func SymbolCount(s []byte) (ret LetterCount) {
	ret = make(LetterCount)
	var count float64 = 0
	// Calculate number of times a symbol appears.
	str := strings.ToLower(string(s))
	for _, val := range str {
		bval := byte(val)
		count++
		// Initialize if needed.
		if _, ok := ret[bval]; ok != true {
			ret[bval] = 0
		}
		ret[bval] += 1
	}
	return
}

func GetLetterDist(s []byte) (ret LetterDist) {
	ret = make(LetterDist)
	count := SymbolCount(s)

	for letter, number := range count {
		ret[letter] = float64(number / len(s))
	}
	return
}

// Chi Squared test
//             i = 'z'
//             ------
//             \    (C_i - E_i)^2
// x^2(C, E) =  ·  ---------------
//             /        E_i
//             ------
//             i = 'a'
// E is the distribution that we check agains
func ChiSquaredTestDist(s string, e LetterDist) (ret float64) {
	var count LetterCount = SymbolCount([]byte(s))

	for symbol, freqE := range e {
		countE := freqE * float64(len(s))
		if countC, ok := count[symbol]; ok {
			contrib := math.Pow(float64(countC)-countE, 2) / countE
			ret += contrib
		} else {
			ret = math.Inf(1)
			break
			// ret += 10000
		}
	}
	return
}

// By default, use the English distribution
func ChiSquaredTest(s string) (ret float64) {
	return ChiSquaredTestDist(s, EnglishDist)
}

// Bhattacharyya Coefficient
//             i = 0xff
//             ------
//             \    __________
// BC(Q, p) =  ·  \/ p_i * q_i
//             /
//             ------
//             i = 0x00
//
func BhattacharyyaCoefficientDist(s string, p LetterDist) (ret float64) {
	var sDist LetterDist = GetLetterDist([]byte(s))

	for symbol, freqP := range p {
		if freqQ, ok := sDist[symbol]; ok {
			ret += math.Sqrt(freqP * freqQ)
		}
	}
	return
}

// By default, use the English distribution
func BhattacharyyaCoefficient(s string) (ret float64) {
	return BhattacharyyaCoefficientDist(s, EnglishDist)
}

// Hamming distance is calculated as the number of bits different in two data
// streams
func HammingDistance(s []byte, t []byte) (ret int) {
	var masks []byte = []byte{0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80}

	if len(s) != len(t) {
		return -1
	}

	for i := 0; i < len(s); i++ {
		if s[i] != t[i] {
			// Check every bit
			for _, mask := range masks {
				if (s[i] & mask) != (t[i] & mask) {
					ret++
				}
			}
		}
	}

	return
}
