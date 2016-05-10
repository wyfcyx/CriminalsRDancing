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
	void ChangePlayer(int pos);
private:
	Player players[MAX_PLAYER];
	int num_players, win_score, now_operate_player;

	CardManager *manager;	
};
#endif // _GAME_H_
