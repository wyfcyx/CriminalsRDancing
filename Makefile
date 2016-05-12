all: main

objects := main.o CardManager.o Player.o Game.o

main: $(objects)
	clang++ -omain $(objects) -g -Wall

main.o: main.cc defs.h
	clang++ -c -g main.cc

CardManager.o: CardManager.cc CardManager.h defs.h
	clang++ -c -g CardManager.cc

Player.o: Player.cc Player.h defs.h
	clang++ -c -g Player.cc

Game.o: Game.cc Game.h Player.h CardManager.h defs.h
	clang++ -c -g Game.cc

clean:
	rm main $(objects)

.PHONY: clean all
