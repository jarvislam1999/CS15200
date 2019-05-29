.PHONY: clean

ident : ident.c
	clang -Wall -o ident ident.c

ppm : ppm.h
	clang -Wall -o ppm ppm.h

hmirror : ppm.h hmirror.c
	clang -Wall -o hmirror hmirror.c -lm

clean :
	rm -f ident hmirror
