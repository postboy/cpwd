//cpwd - command-line password manager for your various accounts
//this is a port of npwd utility by Nadim Kobeissi (https://github.com/kaepora/npwd) to C

//Author: Zuboff Ivan, licence: GPL v3

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
//#include <string.h> - someone may need this header for re-using cpwd code somewhere else

#include "scrypt/readpass.h"
#include "scrypt/crypto_scrypt.h"
#include "poison.h"

extern int main (int argc, char **argv)
{
	char* key;
	unsigned char hash[16];
	char account[1016], salt[1024] = {0}, n[4] = "npwd", command[100] = {0}, password_letters[3];
	int i;
	
	char command_begin[6] = "echo \0";
	
	//--PLATFORM-SPECIFIC CODE BEGIN---------------------------------------------------------------
	//comment all code in this section that is unuseful for your system (that's easy)
	
	char command_end[28] = "|xclip -selection clipboard\0";	//Linux/OpenBSD with xclip package installed
	//char command_end[26] = "|xsel --clipboard --input\0";	//Linux/OpenBSD with xsel package installed
	//char command_end[6] = "|clip\0";						//Windows
	//char command_end[8] = "|pbcopy\0";					//Mac OS X
	
	//--PLATFORM-SPECIFIC CODE END-----------------------------------------------------------------
	
	
	//getting account name and lowercasing it for usability
	printf("account: ");
	if (fflush(stdin)) {
		printf("fflush() error\n");
		return 1;
		}
	if (fgets((char *)account, 1016, stdin) == NULL) {
		printf("fgets() error\n");
		return 1;
		};
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
		//output format is 2 lowercase hex symbols and null-byte for strncat, totally 3 bytes
		snprintf(password_letters, 3, "%02x", hash[i]);
		strncat(command, password_letters, 3);
		}
	strncat(command, command_end, strlen(command_end));
	if (system(command)) {
	    printf("system(fill_clipboard) error\n");
		return 1;
    	};
	
	//notify user and pause for 15 seconds
	printf("\nPaste it!\n");
	sleep(15);
	
	//clear a clipboard
	//to do that, compose and execute a command "command_begin"+"command_end"
	bzero(command, 1);	//clear first byte of "command" for owerwriting it
	strncat(command, command_begin, strlen(command_begin));
	strncat(command, command_end, strlen(command_end));
	if (system(command)) {
	    printf("system(clear_clipboard) error\n");
		return 1;
    	};
	
	return 0;
}
