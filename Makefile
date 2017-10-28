all:
	clang++ -std=c++14 web.cpp  -c
	clang++ -std=c++14 executer.cpp -c
	clang++ -std=c++14 main.cpp -o main web.o executer.o -lcurl
	rm web.o executer.o
