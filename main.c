//cpwd - command-line password management for your various accounts
//a port of npwd utility by Nadim Kobeissi (https://github.com/kaepora/npwd) to C

//Author: Zuboff Ivan, licence: GPL v3

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "scrypt/readpass.h"
#include "scrypt/crypto_scrypt.h"
#include "xclip/xclib.h"

extern int main (int argc, char **argv)
{
	char* key;
	unsigned char password[16];
	char account[1016], salt[1024] = {0}, n[4] = "npwd", temp[4];
	int i, dec = 1;
	
	if (tarsnap_readpass(&key, "key", dec ? NULL : "repeat a key", 1)) {
		printf("tarsnap_readpass() error\n");
		return 1;
		}
	
	//getting account name and lowercasing it for usability
	printf("account: ");
	if (fflush(stdin)) {
		printf("fflush() error\n");
		return 1;
		}
	fgets((char *)account, 1016, stdin);
	for (i = 0; account[i]; i++)
 		account[i] = tolower(account[i]);

	//salt: "npwd"+lowercased account without newline+"npwd"
	strncat(salt, n, 4);
	strncat(salt, account, strlen(account)-1);
	strncat(salt, n, 4);

	if (crypto_scrypt((uint8_t *)key, (size_t)strlen(key), (uint8_t *)salt, (size_t)strlen(salt), 131072, 8, 1, password, 16)) {
    	printf("crypto_scrypt() error\n");
		return 1;
    	}

	for (i=0; i < 16; i++) {
		snprintf(temp, 4, "%02x", password[i]);	//output format of hash is HEX-code
		printf("%s", temp);
		}
	printf("\n");
	
	return 0;
}
