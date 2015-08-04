#!/bin/sh
#compilation & launch for testing

gcc -Wall main.c scrypt/readpass.c scrypt/crypto_scrypt-ref.c scrypt/sha256.c -o cpwd
./cpwd
