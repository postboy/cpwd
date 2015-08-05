#!/bin/sh
#just a compilation

gcc -Wall main.c scrypt/readpass.c scrypt/crypto_scrypt-ref.c scrypt/sha256.c -o cpwd
