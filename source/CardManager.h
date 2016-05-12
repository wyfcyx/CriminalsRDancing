#ifndef _CARD_MANAGER_H_
#define _CARD_MANAGER_H_

#include "defs.h"

const int predealed_sequence[32] = {
	FIRST, CRIMINAL, DETECTIVE, ABSENT, // 3 player
	CO_CRIMINAL, // 4 player
	ABSENT, // 5 player
	DETECTIVE, CO_CRIMINAL, // 6 player
	ABSENT, // 7 player
	DETECTIVE, DETECTIVE, 
	GOD_DOG,
	WITNESS, WITNESS, WITNESS,
	ORDIARY, ORDIARY,
	TRANSACTION, TRANSACTION, TRANSACTION, TRANSACTION,
	INTELLIGENCE, INTELLIGENCE, INTELLIGENCE, INTELLIGENCE,
	ABSENT, ABSENT,
	RUMOR, RUMOR, RUMOR, RUMOR, RUMOR // others
};
const int start_point[10] = {0, 0, 0, 4, 5, 6, 8, 9};
const int add_cards[10] = {0, 0, 0, 8, 11, 14, 16, 19};
const int total_cards[10] = {0, 0, 0, 12, 16, 20, 24, 28, 32};

class CardManager {
public:
	int card_seq[50];

	void GenerateCardsSequence();
	CardManager(int _);

private:
	int total_players;
};

void Shuffle(int *array, int elements);

#endif // _CARD_MANAGER_H_
