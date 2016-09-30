package mcclib

import (
	"encoding/hex"
	"fmt"
)

// Convert a string representing hexa to actual hexa. Thanks encoding/hex!
func String2Hex(s string) (ret []byte) {
	var err error
	if ret, err = hex.DecodeString(s); err != nil {
		fmt.Print("Error when converting to hex: ", err)
	}
	return
}

// Convert a hexa array to its string representation. Thanks encoding/hex!
func Hex2String(s []byte) string {
	return hex.EncodeToString(s)
}
