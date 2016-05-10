#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>

#include "defs.h"
#include "Player.h"
#include "Game.h"

Player :: Player(char *_name, Game *_game)
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

void Player :: DeleteCard(int pos)
{
	//printf("You played the card %s :", DIG_TO_NAME_IN_ENGLISH[cards[pos]]);
	for (int i = pos; i < num_cards; ++i)
		cards[i] = cards[i + 1];
	--num_cards;
}

int Player :: PopCard(int &extra_message)
{
	static int id, card;
	static bool avaliable[10];
	CardList();
	std::vector<int> player_list = GetAvaliablePlayers();
	PrintPlayerList(player_list);
	memset(avaliable, 0, sizeof avaliable);
	for (int i = 0; i < player_list.size(); ++i)
		avaliable[player_list[i]] = 1;

	while (true) {
		while (true) {
			printf("Please input the index of the card that you want to play: ");
			scanf("%d", &id);
			if (id < 1 || id > num_cards) {
				puts("Please input a legal number!Retry!");
				continue;
			}
			else
				break;
		}
		card = cards[id];
		switch (card) {
			case CRIMINAL: 
		}

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
	printf("Cards: ");
	if (!num_cards)
		puts(" no cards.");
	else {
		for (int i = 1; i <= num_cards; ++i)
			printf(" %s", DIG_TO_NAME_IN_ENGLISH[cards[i]]);
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

void Player :: GainScore(int add)
{
	score += add;
}

bool Player :: IsBeginPlayer()
{
	for (int i = 1; i <= num_cards; ++i) {
		if (cards[i] == FIRST)
			return true;
	}
	return false;
}

void ReceiveNotice(char *notice)
{
	printf("The system tell you: %s\n", notice);
}

void TellSystemEmpty()
{
	current_game->PlayerIsEmpty(pos);
}

bool Player :: HaveAbsent()
{
	for (int i = 1; i <= num_cards; ++i) {
		if (cards[i] == ABSENT)
			return true;
	}
	return false;
}

bool Player :: ShowAbsent()
{
	static int _;
	if (!HaveAbsent())
		return false;
	else {
		while (true) {
			printf("Do you want to show your ABSENT card?If do then input number 1 else input 0: ");
			scanf("%d", &_);
			if (_ != 1 || _ != 0) {
				puts("Please input 0 or 1!Retry!");
				continue;
			}
			else
				break;
		}
		if (!_)
			return false;
		else
			return true;
	}
}

bool Player :: IsCriminal()
{
	for (int i = 1; i <= num_cards; ++i) {
		if (cards[i] == CRIMINAL)
			return true;
	}
	return false;
}

int Player :: Fold()
{
	CardList();
	static int id, card;
	static bool avaliable[10];
	while (true) {
		printf("Please input the index of the card that you want to play: ");
		scanf("%d", &id);
		if (id < 1 || id > num_cards) {
			puts("Please input a legal number!Retry!");
			continue;
		}
		else
			break;
	}
	card = cards[id];
	DeleteCard(id);
	return card;
}

int Player :: RandomFold()
{
	static int id, card;
	id = rand() % num_cards + 1;
	card = cards[id];
	DeleteCard(id);
	return card;
}

std::vector<int> Player :: GetAvaliablePlayers()
{
	static Node *it;
	vector<int> player_list;
	it = current_game->list[0];
	//printf("Avaliable Players List:\n");
	while (true) {
		//printf("Player %d has %d cards.\n", it->pos, current_game->players[it->pos].num_cards);
		player_list.push_back(it->pos);
		it = it->_next;
		if (it == current_game->list[0])
			break;
	}
	sort(player_list.begin(), player_list.end());
	return player_list;
}

void Player :: PrintPlayerList(std::vector<int> player_list)
{
	printf("Avaliable Players List:\n");
	for (int i = 0; i < player_list.size(); ++i)
		printf("Player %d has %d cards.\n", player_list[i], current_game->players[player_list[i]].num_cards);
}
