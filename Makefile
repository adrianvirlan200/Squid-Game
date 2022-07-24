all: build run clean
	
build: main.cpp Implementation\ files/*.cpp
	g++ -I. -o out main.cpp Implementation\ files/*.cpp

run: 
	./out

clean: 
	rm -f out

.PHONY: all build run clean