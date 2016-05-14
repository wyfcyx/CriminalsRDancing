#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>

#include "defs.h"
#include "Enterance.h"
#include "Game.h"

#define VERSION "V0.01"

void Enterance()
{
	puts("Welcome to CriminalsRDancing.");
	puts("Commands:");
	puts("\'version\', \'v\': View the current version of the game.");
	puts("\'start\', \'s\': Start a new game.");
	puts("\'quit\', \'q\': Quit the game.");

	std::string s;
	while (true) {
		std::cin >> s;
		if (s == "version" || s == "v") {
			printf("%s\n", VERSION);
		}
		else if (s == "start" || s == "s") {
			break;
		}
		else if (s == "quit" || s == "q") {
			return ;
		}
		else {
			printf("unknown command.\n");
		}
	}

	int num = 0;
	puts("Enter the number of players: ");
	while (true) {
		scanf("%d", &num);
		if(num <= MAX_PLAYER && num >= MIN_PLAYER)
			break;
		puts("This number is invalid.\nPlease re-enter a valid number.");
	}
	int players = num;
	
	printf("Enter the minimum score to win: ");
	while (true) {
		scanf("%d", &num);
		if(num > 0)
			break;
		printf("You must input a positive number!\nPlease input the minimum score to win: ");
	}
	int min_score = num;

	Game *current_game = new Game(players, min_score);
	current_game->Start();

	return ;
}