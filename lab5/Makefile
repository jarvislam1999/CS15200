.PHONY: clean cleanppm

hsqueeze: hsqueeze.c
	clang -Wall -o hsqueeze hsqueeze.c -lm

vsqueeze: vsqueeze.c
	clang -Wall -o vsqueeze vsqueeze.c -lm

hstretch: hstretch.c
	clang -Wall -o hstretch hstretch.c -lm

vstretch: vstretch.c
	clang -Wall -o vstretch vstretch.c -lm

brighten: brighten.c
	clang -Wall -o brighten brighten.c -lm

gray: gray.c
	clang -Wall -o gray gray.c -lm

clean:
	rm -f hsqueeze vsqueeze hstretch vstretch brighten gray a.out

cleanppm:
	rm -f *ppm