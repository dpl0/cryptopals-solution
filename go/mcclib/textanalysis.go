package mcclib

import (
	"math"
	"strings"
)

type LetterDist map[byte]float64
type LetterCount map[byte]int

// Distribution of letters in English, calculated from Alice in wonderland
// ebook
var EnglishDist = LetterDist{
	' ': 0.1695302, 'e': 0.0939372, 't': 0.0739241, 'a': 0.0604361,
	'o': 0.0596701, 'i': 0.0537195, 'n': 0.0498892, 'r': 0.0444721,
	's': 0.0440891, 'h': 0.044007, 'd': 0.0323794, 'l': 0.031627,
	'\n': 0.0233236, 'u': 0.0231184, 'c': 0.0210801, 'g': 0.0185494,
	'w': 0.0173456, 'f': 0.0157862, 'm': 0.015663, 'y': 0.0142677,
	'p': 0.0135427, ',': 0.0126809, 'b': 0.0109983, '"': 0.0097125,
	'.': 0.0085223, 'k': 0.0075374, 'v': 0.0056223, '-': 0.0038987,
	'\'': 0.0035567, '!': 0.0024076, '_': 0.0020519, 'j': 0.0019562,
	'q': 0.0013132, ';': 0.001067, 'x': 0.001026, '?': 0.0009576,
	'1': 0.0009028, ':': 0.0005882, '/': 0.0004925, 'z': 0.0004651,
	'*': 0.0004514, '(': 0.0004514, ')': 0.0004514, '[': 0.0003693,
	']': 0.0003693, '0': 0.0003557, '3': 0.000342, '9': 0.0002326,
	'5': 0.0001642, '2': 0.0001368, '6': 0.0001231, '8': 0.0001231,
	'4': 0.0001231, '7': 8.21e-05, '&': 2.74e-05, '@': 2.74e-05,
	'$': 2.74e-05, '#': 1.37e-05, '%': 1.37e-05,
}

func GetSymbolCount(s []byte) (ret LetterCount) {
	ret = make(LetterCount)
	// Calculate number of times a symbol appears.
	str := strings.ToLower(string(s))
	for _, val := range str {
		bval := byte(val)
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
	count := GetSymbolCount(s)

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
// C_i is the count of the character i
// E_i is the expected count of the character using a given distribution
func ChiSquaredTestDist(s string, e LetterDist) (ret float64) {
	var count LetterCount = GetSymbolCount([]byte(s))

	for symbol, freqE := range e {
		countE := freqE * float64(len(s))
		if countC, ok := count[symbol]; ok {
			contrib := math.Pow(float64(countC)-countE, 2) / countE
			ret += contrib
		} else {
			ret += 100
		}
	}
	return
}

// By default, use the English distribution
func ChiSquaredTest(s string) (ret float64) {
	return ChiSquaredTestDist(s, EnglishDist)
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
