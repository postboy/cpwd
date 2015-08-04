#!/bin/sh
#just a compilation

gcc -Wall -march=native main.c scrypt/readpass.c scrypt/crypto_scrypt-ref.c scrypt/sha256.c -o cpwd
#grep sse /proc/cpuinfo
#gcc -Wall -march=native main.c scrypt/readpass.c scrypt/crypto_scrypt-sse.c scrypt/sha256.c -o cpwd
