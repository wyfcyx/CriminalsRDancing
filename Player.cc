#include <cstring>

#include "defs.h"
#include "Player.h"

Player :: Player()
{
	score = 0;
}

void Player :: ClearCard()
{
	num_cards = 0;
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