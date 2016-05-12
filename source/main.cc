#include <cstdio>
#include <cstdlib>

#include "Game.h"

int main()
{
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

	return EXIT_SUCCESS;
}