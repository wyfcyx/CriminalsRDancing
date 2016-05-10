#include "Game.h"
#include "Player.h"
#include "defs.h"
#include "CardManager.h"

Game :: Game()
{

}

void Game :: SetNumberOfPlayers()
{
	printf("Please input the number of players : ");
	int _;
	while (1) {
		scanf("%d", &_);
		if (_ < 3 || _ > 8) {
			printf("The number must be in range [3,8]!\nPlease input the number of players : ");
			continue;
		}
		else
			break;
	}
	num_players = _;
}

void Game :: SetWinScore()
{
	printf("Please input the minimum score to win : ");
	int _;
	while (1) {
		scanf("%d", &_);
		if (_ <= 0) {
			printf("You must input a positive number!\nPlease input the minimum score to win : ");
			continue;
		}
		else 
			break;
	}
	win_score = _;
}

int Game :: FindWinner()
{
	static int mx, cnt, best_player;
	mx = cnt = 0;
	for (int i = 0; i < num_players; ++i) {
		if (mx < players[i].score) {
			mx = players[i].score;
			cnt = 1;
			best_player = i;
		}
		else if (mx == players[i].score)
			++cnt;
	}
	if (mx >= win_score && cnt == 1)
		return best_player;
	else
		return -1;
}

void Game :: SubGameStart()
{

}

void Game :: Start()
{
	SetNumberOfPlayers();
	SetWinScore();
}