#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "defs.h"

class Player {
public:
	int score;
	char name[110];
	Player();

	void BeforeTheSubGame();
	void GetCard(int card);
	void SendCard(int pos);
	void PopCard();
	int GetNumOfCards();
	int GetScore();
	void CardList();
	void SetName(char *_name);
	char *GetName();
	void GainScore(int add);

private:
	int cards[MAX_CARD], num_cards, pos;
	bool co_criminal;
	bool IsBeginPlayer();
	void ReceiveNotice(char *notice);
	void SetPos(int _pos);
};

#endif // _PLAYER_H_
