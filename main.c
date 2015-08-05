//cpwd - command-line password management for your various accounts
//a port of npwd utility by Nadim Kobeissi (https://github.com/kaepora/npwd) to C

//Author: Zuboff Ivan, licence: GPL v3

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#include "scrypt/readpass.h"
#include "scrypt/crypto_scrypt.h"
#include "xclip/xclib.h"

extern int main (int argc, char **argv)
{
	char* key;
	unsigned char hash[16];
	char account[1016], salt[1024] = {0}, n[4] = "npwd", command[100] = {0}, password[3];
	int i;
	
	char command_begin[6] = "echo \0";
	
	//PLATFORM-SPECIFIC CODE BEGIN
	
	//Linux with xclip package installed
	char command_end[28] = "|xclip -selection clipboard\0";
	
	//PLATFORM-SPECIFIC CODE END
	
	
	//getting account name and lowercasing it for usability
	printf("account: ");
	if (fflush(stdin)) {
		printf("fflush() error\n");
		return 1;
		}
	fgets((char *)account, 1016, stdin);
	for (i = 0; account[i]; i++)
 		account[i] = tolower(account[i]);
 		
 	//getting master key
 	if (tarsnap_readpass(&key, "key", NULL, 1)) {
		printf("tarsnap_readpass() error\n");
		return 1;
		}

	//salt: "npwd"+lowercased account without newline+"npwd"
	strncat(salt, n, 4);
	strncat(salt, account, strlen(account)-1);
	strncat(salt, n, 4);

	//hashing it
	if (crypto_scrypt((uint8_t *)key, (size_t)strlen(key), (uint8_t *)salt, (size_t)strlen(salt), 131072, 8, 1, hash, 16)) {
    	printf("crypto_scrypt() error\n");
		return 1;
    	}

	//now let's take a hash to clipboard!
	//to do that, compose and execute a command "command_begin"+hex-code of hash+"command_end"
	strncat(command, command_begin, strlen(command_begin));
	for (i=0; i < 16; i++) {
		//output format is 2 bytes of lowercase hex-code and null-byte for strncat
		snprintf(password, 3, "%02x", hash[i]);
		strncat(command, password, 3);
		}
	strncat(command, command_end, strlen(command_end));
	system(command);
	
	//notify user and pause for 15 seconds
	printf("\nPaste it!\n");
	sleep(15);
	
	//clear a clipboard
	//to do that, compose and execute a command "command_begin"+"command_end"
	bzero(command, 1);	//clear first byte of "command" for owerwriting it
	strncat(command, command_begin, strlen(command_begin));
	strncat(command, command_end, strlen(command_end));
	system(command);
	
	return 0;
}
