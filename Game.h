#ifndef _GAME_H_
#define _GAME_H_

#include "Player.h"
#include "defs.h"

class Game {
public:
	Game();
	void SetNumberOfPlayers();
	void SetWinScore();
	int FindWinner();
	void Start();
	void SubGameStart();
private:
	Player players[MAX_PLAYER];
	int num_players, win_score;
};
#endif // _GAME_H_
