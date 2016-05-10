#include <cstring>

#include "defs.h"
#include "Player.h"

Player :: Player()
{
	score = 0;
}

void Player :: BeforeTheSubGame()
{
	num_cards = 0;
	co_criminal = 0;
}

void Player :: GetCard(int card)
{
	cards[++num_cards] = card;
}

void Player :: SendCard(int pos)
{
	for (int i = pos; i < num_cards; ++i)
		cards[i] = cards[i + 1];
	--num_cards;
}

int Player :: GetNumOfCards()
{
	return num_cards;
}

int Player :: GetScore()
{
	return score;
}

void Player :: CardList() 
{
	printf("Cards :");
	if (!num_cards)
		puts(" no cards.");
	else {
		for (int i = 1; i <= num_cards; ++i)
			printf(" %s", DAG_TO_NAME_IN_ENGLISH[cards[i]]);
		puts("");
	}
}

void Player :: SetName(char *_name)
{
	strcpy(name, _name);
}

char *Player :: GetName()
{
	return name;
}

void Player :: GainScore(int add) {
	score += add;
}
