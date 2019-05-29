# Makefile for CS152 Winter 2019 Lab 7

CFLAGS=-Wall -g -O0
CC=clang

all : leak blowpast bst

leak : leak.c
	$(CC) $(CFLAGS) -o $@ leak.c
	
blowpast : blowpast.c
	$(CC) $(CFLAGS) -o $@ blowpast.c
	
bst : bst.c bst.h
	$(CC) $(CFLAGS) -o $@ bst.c

.PHONY clean :
	rm -rf leak blowpast bst *.dSYM a.out
