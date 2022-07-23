all: build run clean
	
build: main.cpp Implementation\ files/Players.cpp 
	g++ -I. -o out main.cpp Implementation\ files/Players.cpp

run: 
	./out

clean:
	rm -f out