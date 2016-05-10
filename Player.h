#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "defs.h"

class Player {
public:
	Player();
	void ClearCard();
	void GetCard(int card);
	void SendCard(int pos);
	int GetNumOfCards();
	int GetScore();
	void CardList() {
		
	}
private:
	int cards[MAX_CARD], num_cards, score;
};

#endif // _PLAYER_H_