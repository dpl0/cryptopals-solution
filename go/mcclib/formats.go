package mcclib

import (
    "encoding/hex"
    "errors"
    "fmt"
)


// This file implements all the formatting functions

// Hexadecimal to base 64.
func Hex2Base64(hex []byte) []byte {
    // Creates a base64 block (4 symbols) from 3 bytes.
    hexblock2base64 := func(hex []byte) (ret []byte) {
        var s = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
        one := hex[0] & 0xfc >> 2
        two := hex[0]&0x03<<4 | hex[1]&0xf0>>4
        three := hex[1]&0x0f<<2 | hex[2]&0xc0>>6
        four := hex[2] & 0x3f

        ret = append(ret, s[one], s[two], s[three], s[four])
        return
    }

    var ret []byte
    // Add padding if needed.
    for len(hex)%3 != 0 {
        hex = append(hex, byte(0))
    }

    // Perform transformation.
    for i := 0; i < len(hex); i += 3 {
        ret = append(ret, hexblock2base64(hex[i:i+3])...)
    }

    // Modify padding if needed.
    l := len(ret)
    for i := l - 3; i < l; i++ {
        if ret[i] == 'A' {
            ret[i] = '='
        }
    }
    return ret
}


func hex2String(str []byte) (string, error) {
    // Handle the case for each block from hexa to string
    hexBlock2String := func(str []byte) string {
        const s = "0123456789abcdef"
        return s
    }

    var ret string

    if (len(str) % 2 != 0) {
        return "", errors.New("Hex2Strings: Wrong size\n")
    }

    for i := 0; i < len(str); i += 2 {
        ret += hexBlock2String(str[i:i+2])
    }

    return ret, nil
}

// Convert a hexa array to its string representation. Thanks encoding/hex!
func Hex2String(s []byte) string {
    return hex.EncodeToString(s)
}


// Convert a string representing hexa to actual hexa. Thanks encoding/hex!
func String2Hex(s string) (ret []byte) {
    var err error
    if ret, err = hex.DecodeString(s); err != nil {
        fmt.Print("Error when converting to hex: ", err)
    }
    return
}

