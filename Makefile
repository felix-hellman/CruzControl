CC = clang++
CFLAGS = -std=c++14 -I .
LFLAGS = -lcurl

all: Cruz

clean:
	rm -rf *.o > /dev/null 2>&1

web: obfuscate
	$(CC) $(CFLAGS) src/web.cpp -c
utility: obfuscate
	$(CC) $(CFLAGS) src/utility.cpp -c
deobfuscate: obfuscate
	$(CC) $(CFLAGS) src/deobfuscate.cpp -c
strings: obfuscate
	$(CC) $(CFLAGS) strings.obf.cpp -c
obfuscate:
	$(CC) $(CFLAGS) src/obfuscator.cpp -o src/obf
	./src/obf
	rm -rf src/obf
Cruz: web utility deobfuscate strings obfuscate
	$(CC) $(CFLAGS) src/CruzControl.cpp -o Cruz web.o utility.o deobfuscate.o strings.obf.o $(LFLAGS)
	rm strings.obf.cpp strings.obf.h
	rm *.o
