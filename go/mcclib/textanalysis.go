package mcclib

import (
    "math"
)

type LetterDist map[byte]float64

type DistSimilarity struct {
    maxDiff float64
    eqSymbols int
}

var DefaultSimilarity = DistSimilarity{ 0.1, 16 }

// Distribution of letters in English, from:
// http://www.data-compression.com/english.html
// No punctuation letters.
var EnglishDist = LetterDist {
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
func SymbolFrequency(s []byte) (ret LetterDist) {
    ret = make(LetterDist)
    var count float64 = 0
    // Calculate number of times a symbol appears.
    for _, val := range s {
        bval := byte(val)
        count++
        // Initialize if needed.
        if _, ok := ret[bval]; ok != true {
            ret[bval] = 0
        }
        ret[bval] += 1
    }
    // Calculate the frequency of time a symbol appears.
    for k, val := range ret {
        ret[k] = val / count
    }
    return
}

// Compares a given distribution with another.
// Returns true if there's a match within +-maxDiff, and the result shares at
// least eqSymbols symbols.
func IsDistSimilarTo(f LetterDist, s LetterDist, sim DistSimilarity) bool {
    var matchingSymbols LetterDist = make(LetterDist)
    for k, _ := range f {
        if _, ok := s[k]; ok {
            matchingSymbols[k] = math.Abs(f[k] - s[k])
        }
    }

    // We now have to search the other way. This could be much easier with the
    // python-like set ^ operation.
    for k, _ := range s {
        if _, ok := f[k]; ok {
            // We might have already this symbol!
            if _, match := matchingSymbols[k]; !match {
                matchingSymbols[k] = math.Abs(f[k] - s[k])
            }
        }
    }

    // We also have to ensure that at least a minimum of symbols are the same.
    // Otherwise we'd get false positives.
    if len(matchingSymbols) < sim.eqSymbols {
        return false
    }

    for _, val := range matchingSymbols {
        if val > sim.maxDiff {
            return false
        }
    }

    return true
}

func HammingDistance(s string, t string) (ret int) {
    var masks []byte = []byte{0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80}

    if len(s) != len(t) {
        return -1
    }

    for  i := 0; i < len(s);  i++ {
        if s[i] != t[i] {
            // Check every bit
            for _, mask := range(masks) {
                if ((s[i] & mask) != (t[i] & mask)) {
                    ret++
                }
            }
        }
    }

    return
}
