all : context main
	g++ main.o context.o -o exe -std=c++11 -pthread -O3
context :
	g++ context.cpp -c
main :
	g++ main.cpp -c
