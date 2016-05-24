#include <ctime>
#include <random>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <sys/time.h>

#include "CardManager.h"

CardManager :: CardManager(int _)
{
	total_players = _;
	memset(card_seq, 0, sizeof(card_seq));
}

void CardManager :: GenerateCardsSequence()
{
	if (total_players == MAX_PLAYER)
		memcpy(card_seq, predealed_sequence, sizeof(int) * 32);
	else {
		memcpy(card_seq, predealed_sequence, sizeof(int) * start_point[total_players]);

		int need_to_be_shuffled[50];
		memset(need_to_be_shuffled, 0, sizeof(int) * 50);


		int remained_num = ALL_CARD - start_point[total_players];
		memcpy(need_to_be_shuffled,
				predealed_sequence + start_point[total_players],
				sizeof(int) * remained_num);

		Shuffle(need_to_be_shuffled, remained_num);

		memcpy(card_seq + start_point[total_players],
				need_to_be_shuffled,
				sizeof(int) * add_cards[total_players]);
	}

	Shuffle(card_seq, total_cards[total_players]);

	return ;
}

void Shuffle(int array[], int elements)
{
	srand((unsigned int)time(NULL));
	unsigned int seed = (unsigned int)rand();

	shuffle(array, array + elements, std::default_random_engine(seed));

	return ;
}

