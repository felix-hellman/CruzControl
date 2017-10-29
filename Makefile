all:
	clang++ -std=c++14 obfuscator.cpp -o obf
	./obf
	rm -rf obf
	clang++ -std=c++14 web.cpp  -c
	clang++ -std=c++14 utility.cpp -c
	clang++ -std=c++14 deobfuscate.cpp -c
	clang++ -std=c++14 strings.obf.cpp -c
	clang++ -std=c++14 CruzControl.cpp -o Cruz web.o utility.o deobfuscate.o strings.obf.o -lcurl
	rm *.o
	rm strings.obf.cpp strings.obf.h
clean:
	rm *.o
	rm strings.obf.cpp strings.obf.h
