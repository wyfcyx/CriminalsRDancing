#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "defs.h"

class Player {
public:
	int score;
	char name[110];
	bool co_criminal;
	Player();

	void BeforeTheSubGame();
	void GetCard(int card);
	void SendCard(int pos);
	int PopCard();
	int GetNumOfCards();
	int GetScore();
	void CardList();
	void SetName(char *_name);
	char *GetName();
	void GainScore(int add);
	bool IsBeginPlayer();
	void ReceiveNotice(char *notice);
	void SetPos(int _pos);

private:
	int cards[MAX_CARD], num_cards, pos;
};

#endif // _PLAYER_H_
