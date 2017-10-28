all:
	clang++ -std=c++14 web.cpp  -c
	clang++ -std=c++14 main.cpp -o main web.o -lcurl
	rm web.o
