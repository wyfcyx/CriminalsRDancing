all: main

objects := main.o CardManager.o Player.o Game.o

main: $(objects)
	clang++ -omain $(objects) -g -Wall

main.o: main.cc defs.h
	clang++ -c main.cc

CardManager.o: CardManager.cc CardManager.h defs.h
	clang++ -c CardManager.cc

Player.o: Player.cc Player.h defs.h
	clang++ -c Player.cc

Game.o: Game.cc Game.h Player.h CardManager.h defs.h
	clang++ -c Game.cc

clean:
	rm main $(objects)

.PHONY: clean all
