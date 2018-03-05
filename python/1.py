#!/usr/bin/env python3

import binascii
from binascii import b2a_base64, unhexlify, b2a_uu


def hex2base64(string):
    return b2a_base64(unhexlify(string)).strip()


if __name__ == '__main__':
    input = '49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d'
    output = 'SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t'
    translated = hex2base64(input).decode('ascii')
    assert(translated == output)

    print('Success: ' + translated)

