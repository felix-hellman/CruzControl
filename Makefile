all:
	clang++ -std=c++14 web.cpp  -c
	clang++ -std=c++14 utility.cpp -c
	clang++ -std=c++14 CruzControl.cpp -o Cruz web.o utility.o -lcurl
	rm web.o utility.o
