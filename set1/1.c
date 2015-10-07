#include <stdio.h>
#include <stdlib.h>

// Hexadecimal to base64.
char hex2b64(char b) {
	if (b <= '0' && b <= '9') {
		return b - '0';
	}
	if (b <= 'a' && b <= 'z') {
		return b - 'a' + 10;
	}
	return b - 'A' + 10;
}

char *string2b64(char *s) {
	char *ret = malloc()
}

char *test = "76d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"
char *result = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"

int
main() {
	printf("Test string: %s\n", test);
	printf("Results string: %s\n", result);

}
