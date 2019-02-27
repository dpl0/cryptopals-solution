package mcclib

import (
	"errors"
	"strings"
)

// This file implements all the formatting functions

var hexSymbols = []string{
	"00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "0a", "0b",
	"0c", "0d", "0e", "0f", "10", "11", "12", "13", "14", "15", "16", "17",
	"18", "19", "1a", "1b", "1c", "1d", "1e", "1f", "20", "21", "22", "23",
	"24", "25", "26", "27", "28", "29", "2a", "2b", "2c", "2d", "2e", "2f",
	"30", "31", "32", "33", "34", "35", "36", "37", "38", "39", "3a", "3b",
	"3c", "3d", "3e", "3f", "40", "41", "42", "43", "44", "45", "46", "47",
	"48", "49", "4a", "4b", "4c", "4d", "4e", "4f", "50", "51", "52", "53",
	"54", "55", "56", "57", "58", "59", "5a", "5b", "5c", "5d", "5e", "5f",
	"60", "61", "62", "63", "64", "65", "66", "67", "68", "69", "6a", "6b",
	"6c", "6d", "6e", "6f", "70", "71", "72", "73", "74", "75", "76", "77",
	"78", "79", "7a", "7b", "7c", "7d", "7e", "7f", "80", "81", "82", "83",
	"84", "85", "86", "87", "88", "89", "8a", "8b", "8c", "8d", "8e", "8f",
	"90", "91", "92", "93", "94", "95", "96", "97", "98", "99", "9a", "9b",
	"9c", "9d", "9e", "9f", "a0", "a1", "a2", "a3", "a4", "a5", "a6", "a7",
	"a8", "a9", "aa", "ab", "ac", "ad", "ae", "af", "b0", "b1", "b2", "b3",
	"b4", "b5", "b6", "b7", "b8", "b9", "ba", "bb", "bc", "bd", "be", "bf",
	"c0", "c1", "c2", "c3", "c4", "c5", "c6", "c7", "c8", "c9", "ca", "cb",
	"cc", "cd", "ce", "cf", "d0", "d1", "d2", "d3", "d4", "d5", "d6", "d7",
	"d8", "d9", "da", "db", "dc", "dd", "de", "df", "e0", "e1", "e2", "e3",
	"e4", "e5", "e6", "e7", "e8", "e9", "ea", "eb", "ec", "ed", "ee", "ef",
	"f0", "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8", "f9", "fa", "fb",
	"fc", "fd", "fe", "ff"}

// Octet corresponds to byte characters, sextets to base64 symbols
// +--first octet--+-second octet--+--third octet--+
// |7 6 5 4 3 2 1 0|7 6 5 4 3 2 1 0|7 6 5 4 3 2 1 0|
// +-----------+---+-------+-------+---+-----------+
// |5 4 3 2 1 0|5 4 3 2 1 0|5 4 3 2 1 0|5 4 3 2 1 0|
// +--1.index--+--2.index--+--3.index--+--4.index--+

var base64Symbols string = "ABCDEFGHIJKLMNOPQRSTUVWXYZ" +
	"abcdefghijklmnopqrstuvwxyz0123456789+/"

const base64Pad = '='

// Bytes to base 64.
func Bytes2Base64(hex []byte) (base64 []byte) {
	// Creates a base64 block (4 symbols) from 3 bytes.
	hexBlock2Base64 := func(hex []byte) (ret []byte) {
		ret = append(ret, base64Symbols[hex[0]&0xfc>>2])
		ret = append(ret, base64Symbols[hex[0]&0x03<<4|hex[1]&0xf0>>4])
		ret = append(ret, base64Symbols[hex[1]&0x0f<<2|hex[2]&0xc0>>6])
		ret = append(ret, base64Symbols[hex[2]&0x3f])
		return
	}

	// Add padding if needed.
	for len(hex)%3 != 0 {
		hex = append(hex, byte(0))
	}

	// Perform transformation.
	for i := 0; i < len(hex); i += 3 {
		base64 = append(base64, hexBlock2Base64(hex[i:i+3])...)
	}

	// Modify last byte if needed, to set padding
	l := len(base64)
	for i := l - 3; i < l; i++ {
		if base64[i] == 'A' {
			base64[i] = base64Pad
		}
	}
	return base64
}

func Base642Bytes(base64 string) (data []byte) {
	base64Block2Bytes := func(hex string) (ret [3]byte) {
		symbolIndexes := func(hex string) [4]byte {
			first := byte(strings.Index(base64Symbols, string(hex[0])))
			second := byte(strings.Index(base64Symbols, string(hex[1])))
			third := byte(strings.Index(base64Symbols, string(hex[2])))
			fourth := byte(strings.Index(base64Symbols, string(hex[3])))
			return [4]byte{first, second, third, fourth}
		}

		indexes := symbolIndexes(hex)

		// |7 6 5 4 3 2 1 0|7 6 5 4 3 2 1 0|7 6 5 4 3 2 1 0|
		// |5 4 3 2 1 0|5 4 3 2 1 0|5 4 3 2 1 0|5 4 3 2 1 0|
		// Remember that we also have 2 bits for every index at the beginning
		// since ints are 8 bits long
		ret[0] = indexes[0]<<2 | ((indexes[1] & 0x30) >> 4)
		ret[1] = ((indexes[1] & 0x0f) << 4) | ((indexes[2] & 0x3c) >> 2)
		ret[2] = indexes[2]<<6 | (indexes[3] & 0x3f)
		return
	}

	// 4 base64 symbols (6 bits each) = 3 bytes
	for i := 0; i < len(base64); i += 4 {
		block := base64[i : i+4]
		translated := base64Block2Bytes(block)

		if base64[i+2] == base64Pad {
			data = append(data, translated[0])
		} else if base64[i+3] == base64Pad {
			data = append(data, translated[0], translated[1])
		} else {
			data = append(data, translated[0], translated[1], translated[2])
		}
	}

	return data
}

// Easy function to just handle strings
func Base642String(base64 string) string {
    return string(Base642Bytes(base64))
}

// Convert a binary array to its string representation in hexadecimal
func Bytes2String(data []byte) (ret string) {
	if len(data)%2 != 0 {
		HandleError(errors.New("Hex2Strings: Size is not multiple of 2\n"))
		return ""
	}

	for _, byt := range data {
		ret += hexSymbols[byt]
	}

	return ret
}

// Convert a string representing bytes to actual bytes.
func String2Bytes(s string) (ret []byte) {
	if len(s)%2 != 0 {
		return nil
		HandleError(errors.New("String has no appropiate size"))
	}
	if s[0:2] == "0x" {
		s = s[2:]
	} // Remove leading "0x"
	s = strings.ToLower(s)

	for i := 0; i < len(s); i += 2 {
		symbolInTable := false
		for j, symbol := range hexSymbols {
			if symbol == s[i:i+2] {
				ret = append(ret, byte(j))
				symbolInTable = true
			}
		}
		if symbolInTable == false {
			HandleError(errors.New("String has strange symbols"))
			return nil
		}
	}

	return ret
}

