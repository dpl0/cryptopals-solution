package mcclib

import "errors"

// Returns the XOR of two arrays of same length.
func ArrayXor(f []byte, s []byte) ([]byte, error) {
    l := len(f)
    if l != len(s) {
        return nil, errors.New("Different sizes!")
    }
    ret := make([]byte, l, l)
    for i := range ret {
        ret[i] = f[i] ^ s[i]
    }
    return ret, nil
}

// Applies the XOR cipher to s.
func KeyXor(k []byte, s []byte) []byte {
    l := len(s)
    lk := len(k)
    ret := make([]byte, l, l)
    for i := range ret {
        ret[i] = s[i] ^ k[i%lk]
    }
    return ret
}
