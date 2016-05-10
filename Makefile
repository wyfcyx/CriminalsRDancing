all: main

objects := main.o CardManager.o

main: $(objects)
	clang++ -omain $(objects)

main.o: main.cc defs.h
	clang++ -c main.cc

CardManager.o: CardManager.cc CardManager.h defs.h
	clang++ -c CardManager.cc

clean:
	rm main $(objects)
