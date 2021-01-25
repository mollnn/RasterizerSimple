bin/main.exe:						lib/main.o
	g++ -o bin/main.exe lib/main.o

lib/main.o:							src/main.cpp
	g++ -o lib/main.o -c src/main.cpp

makedir:
	mkdir bin
	mkdir lib

clean:
	rm bin/*.exe
	rm lib/*.o

run:
	bin/main.exe

cmr:
	make clean
	make
	make run

mr:
	make
	make run