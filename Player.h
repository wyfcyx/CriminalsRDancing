#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "defs.h"

class Player {
public:
	Player();
	void BeforeTheSubGame();
	void GetCard(int card);
	void SendCard(int pos);
	int GetNumOfCards();
	int GetScore();
	void CardList();
	void SetName(char *_name);
	char *GetName();
	void GainScore(int add);
private:
	int cards[MAX_CARD], num_cards, score;
	bool co_criminal;
	char name[110];
};

#endif // _PLAYER_H_