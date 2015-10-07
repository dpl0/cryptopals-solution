#!/usr/bin/env python3

test = "76d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"
result = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"

# Hexadecimal to base 64.
def hex2b64(b):
    n = ord(b)
    if ord('0') <= n <=  ord('9'):
        return chr(n - ord('0'))
    if ord('a') <= n <= ord('z'):
        return chr(n - ord('a') + 10)
    return chr(n - ord('A') + 10)

def string2b64 (s):
    return [ hex2b64(s[i]) for i in range(len(s)) ]

print "Test string: ", test
print "Correct result: ", result
print "Our result: ", string2b64(test)
