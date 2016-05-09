#ifndef _CARD_H_
#define _CARD_H_

#include "defs.h"

class Card {
	int card_id; // [0, 10]
	int status; // 0->nobody 1~8(max)->player

	Card(int _, int __);

	void PlayCard();
};

#endif // _CARD_H_
