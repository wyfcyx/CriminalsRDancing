#ifndef _GAME_H_
#define _GAME_H_

#include "Player.h"
#include "CardManager.h"
#include "defs.h"

struct Node {
	Node *_next;
	Node *back;
	int pos;

	Node(Node* _, Node* __, int ___);
};

class Game {
public:
	int rank[MAX_PLAYER];
	Node list[MAX_PLAYER];

	Game(int _, int __);
	bool MaintainRanking();
	void Start();
	void SubGameStart();
	void PrintRanking();
	void PlayerIsEmpty(int pos);

private:
	Player players[MAX_PLAYER];
	int num_players, win_score, now_operate_player;

	CardManager *manager;	

	void GoRound(bool is_rumor);
};

#endif // _GAME_H_
