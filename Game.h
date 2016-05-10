#ifndef _GAME_H_
#define _GAME_H_

#include "Player.h"
#include "CardManager.h"
#include "defs.h"

class Game {
public:
	int rank[MAX_PLAYER];

	Game(int _, int __);
	bool MaintainRanking();
	void Start();
	void SubGameStart();
	void PrintRanking();
private:
	Player players[MAX_PLAYER];
	int num_players, win_score;

	CardManager *manager;
};
#endif // _GAME_H_
