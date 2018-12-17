#!/usr/bin/env python3

hexa_symbols = "0123456789abcdef"

for i in hexa_symbols:
    for j in hexa_symbols:
        print('"%s' % i+j + '",')
