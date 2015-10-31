//cpwd 1.4.1 — tiny and handy password manager
//this is a port of npwd utility by Nadim Kobeissi (https://github.com/kaepora/npwd) to C

//licence: GPL v3, author: Zuboff Ivan (anotherdiskmag on gooooooogle mail)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#include "scrypt/readpass.h"
#include "scrypt/crypto_scrypt.h"
#include "poison.h"

extern int main (int argc, char **argv)
{

	//OS-specific part
	#ifdef WIN32
		char command_end[7] = "\'|clip\0";						//Windows
	#elif __MACH__
		char command_end[9] = "\'|pbcopy\0";						//Mac OS X
	#else
		//if it's not Windows nor OS X then assume it's Linux or OpenBSD
	
		//choose only one string via commenting unnecessary line!
		char command_end[29] = "\'|xclip -selection clipboard\0";	//Linux/OpenBSD with xclip package installed
		//char command_end[27] = "\'|xsel --clipboard --input\0";	//Linux/OpenBSD with xsel package installed
		
	#endif
	
	char command_begin[7] = "echo \'\0", command[100] = {0}, account[1016], salt[1024] = {0},
			n[4] = "npwd", password_letters[3];
	char* key;
	unsigned char hash[16];
	int i;
	


	//if registration mode enabled and/or account name was defined as a command line argument
	if (argc > 1) {
	
		//registration mode
		if (strcmp("-r", argv[1]) == 0) {
			
			//registration mode, account name was defined as a command line argument---------------
			if (argc > 2) {
			
				//copy at most 1016 bytes of argv[2] (to avoid buffer overflow) to account
				//maximum length of arguments is too big: http://www.in-ulm.de/~mascheck/various/argmax
				memcpy(account, argv[2], strlen(argv[2]) < 1016 ? strlen(argv[2]) : 1016);
	
				//lowercasing account name for usability
				for (i = 0; account[i]; i++)
	 				account[i] = tolower(account[i]);
 		
	 			//salt: "npwd"+lowercased account+"npwd"
				strncat(salt, n, 4);
				strncat(salt, account, strlen(account));
				strncat(salt, n, 4);
			
				}
			
			//registration mode, ask a user to enter account name----------------------------------
			else {
			
				printf("account: ");
				if (fflush(stdin)) {
					fprintf(stderr, "fflush() error\n");
					return 1;
					}
				if (fgets((char *)account, 1016, stdin) == NULL) {
					fprintf(stderr, "fgets() error\n");
					return 1;
					};
		
				//lowercasing account name for usability
				for (i = 0; account[i]; i++)
 					account[i] = tolower(account[i]);
 		
 				//salt: "npwd"+lowercased account without newline+"npwd"
				strncat(salt, n, 4);
				strncat(salt, account, strlen(account)-1);
				strncat(salt, n, 4);
				
				}
			
			//get master key twice because it's registration mode
		 	if (tarsnap_readpass(&key, "key", "repeat", 1)) {
				fprintf(stderr, "tarsnap_readpass() error\n");
				return 1;
				}
			
			}
			
		
		//normal mode, account name was defined as a command line argument-------------------------
		else {
		
			//copy at most 1016 bytes of argv[1] (to avoid buffer overflow) to account
			//maximum length of arguments is too big: http://www.in-ulm.de/~mascheck/various/argmax
			memcpy(account, argv[1], strlen(argv[1]) < 1016 ? strlen(argv[1]) : 1016);
	
			//lowercasing account name for usability
			for (i = 0; account[i]; i++)
	 			account[i] = tolower(account[i]);
 		
	 		//salt: "npwd"+lowercased account+"npwd"
			strncat(salt, n, 4);
			strncat(salt, account, strlen(account));
			strncat(salt, n, 4);
		
			//get master key once
	 		if (tarsnap_readpass(&key, "key", NULL, 1)) {
				fprintf(stderr, "tarsnap_readpass() error\n");
				return 1;
				}
				
			}

		}

	//no additional parameters: normal mode, ask a user to enter account name----------------------
	else {
	
		printf("account: ");
		if (fflush(stdin)) {
			fprintf(stderr, "fflush() error\n");
			return 1;
			}
		if (fgets((char *)account, 1016, stdin) == NULL) {
			fprintf(stderr, "fgets() error\n");
			return 1;
			};
		
		//lowercasing account name for usability
		for (i = 0; account[i]; i++)
 			account[i] = tolower(account[i]);
 		
 		//salt: "npwd"+lowercased account without newline+"npwd"
		strncat(salt, n, 4);
		strncat(salt, account, strlen(account)-1);
		strncat(salt, n, 4);
		
		//get master key once
	 	if (tarsnap_readpass(&key, "key", NULL, 1)) {
			fprintf(stderr, "tarsnap_readpass() error\n");
			return 1;
			}
	
		}

	//launch key derivation function to get hash of master key and account name
	if (crypto_scrypt((uint8_t *)key, (size_t)strlen(key), (uint8_t *)salt, (size_t)strlen(salt), 131072, 8, 1, hash, 16)) {
    	fprintf(stderr, "crypto_scrypt() error\n");
		return 1;
    	}
   
	//clear a buffer for a master key and for salt as soon as we can
	free(key);
	bzero(salt, 1024);

	//first let's take an unencoded hash to clipboard!
	//to do that, compose and execute a command "command_begin"+unencoded hash+"command_end"
	strncat(command, command_begin, strlen(command_begin));
	for (i=0; i < 16; i++) {
		//output format is 2 lowercase hex symbols and null-byte for strncat, totally 3 bytes
		snprintf(password_letters, 3, "%02x", hash[i]);
		strncat(command, password_letters, 3);
		}
	bzero(hash, 16);	//clear a buffer for a hash as soon as we can
	strncat(command, command_end, strlen(command_end));
	
	if (system(command)) {
	    fprintf(stderr, "system(fill_clipboard) error\n");
		return 1;
   		};
    
    //clear a buffer with a password as soon as we can
	bzero(command, 100);
	
	//notify user and pause for 15 seconds
	printf("\nIn clipboard!\n");
	sleep(15);
	
	//clear a clipboard via composing and executing command "command_begin"+"command_end"
	strncat(command, command_begin, strlen(command_begin));
	strncat(command, command_end, strlen(command_end));
	if (system(command)) {
	    fprintf(stderr, "system(clear_clipboard) error\n");
		return 1;
    	}
	
	return 0;
}
