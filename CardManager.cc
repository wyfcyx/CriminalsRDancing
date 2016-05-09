#include <cstdio>
#include <algorithm>

#include "CardManager.h"

CardManager :: CardManager(int _)
{
	total_players = _;
}

bool CardManager :: GenerateCardsSequence()
{
	if (total_players < MIN_PLAYER) {
		puts("Not enough players, cards will not shuffle.");
		return false;
	}
	if (total_players > MAX_PLAYER) {
		puts("Too many players, cards will not shuffle.");
		return false;
	}

	if (total_players == MAX_PLAYER)
		memcpy(card_seq, predealed_sequence, sizeof(int) * 32);
	else {
		memcpy(card_seq, predealed_sequence, start_point[total_players]);

		int need_to_be_shuffled[50];
		memset(need_to_be_shuffled, need_to_be_shuffled + sizeof(int) * 50, 0);
		

		int remained_num = ALL_CARD - start_point[total_players];
		memcpy(need_to_be_shuffled,
			   predealed_sequence + sizeof(int) * start_point[total_players], 
			   sizeof(int) * remained_num);
		
		Shuffle(need_to_be_shuffled, remained_num);

		memcpy(card_seq + sizeof(int) * start_point[total_players],
			   need_to_be_shuffled,
			   add_cards[total_cards]);
	}

	Shuffle(card_seq, total_cards[total_players]);
	
	return true;
}

void Shuffle(int *array, int elements)
{
	std::random_shuffle(array, array + sizeof(int) * elements);
	return ;
}
