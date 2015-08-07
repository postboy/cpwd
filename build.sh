#!/bin/sh
#just a compilation

gcc -Wall main.c scrypt/readpass.c scrypt/crypto_scrypt-nosse.c scrypt/sha256.c -o cpwd
