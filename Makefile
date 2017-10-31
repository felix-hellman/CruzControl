CC = clang++
CFLAGS = -std=c++14
LFLAGS = -lcurl

all: Cruz

clean:
	rm -rf *.o > /dev/null 2>&1

web: obfuscate
	$(CC) $(CFLAGS) web.cpp -c
utility: obfuscate
	$(CC) $(CFLAGS) utility.cpp -c
deobfuscate: obfuscate
	$(CC) $(CFLAGS) deobfuscate.cpp -c
strings: obfuscate
	$(CC) $(CFLAGS) strings.obf.cpp -c
obfuscate:
	$(CC) $(CFLAGS) obfuscator.cpp -o obf
	./obf
	rm -rf obf
Cruz: web utility deobfuscate strings obfuscate
	$(CC) $(CFLAGS) CruzControl.cpp -o Cruz web.o utility.o deobfuscate.o strings.obf.o $(LFLAGS)
	rm strings.obf.cpp strings.obf.h
