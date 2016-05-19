#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <vector>

#include "defs.h"
#include "Player.h"
#include "Game.h"

Player :: Player()
{

}

Player :: Player(char *_name, Game *_game, int _pos)
{
	strcpy(name, _name);
	current_game = _game;
	pos = _pos;

	score = 0;
	memset(cards, 0, sizeof(cards));
}

void Player :: BeforeTheSubGame()
{
	num_cards = 0;
	co_criminal = 0;
}

void Player :: GetCard(int card)
{
	cards[num_cards++] = card;
	MaintainCards();
	//printf("The card is %d, num_cards = %d\n", card, num_cards);
}

void Player :: DeleteCard(int pos)
{
	//printf("You played the card %s :", DIG_TO_NAME_IN_ENGLISH[cards[pos]]);
	for (int i = pos; i < num_cards - 1; ++i)
		cards[i] = cards[i + 1];
	--num_cards;
	if (num_cards > 0)
		MaintainCards();
}

bool Player :: CannotPopCard()
{
	if (num_cards <= 2)
		return false;
	for (int i = 0; i < num_cards; ++i) {
		if (cards[i] != CRIMINAL && cards[i] != DETECTIVE) {
			return false;
		}
	}
	return true;
}

int Player :: PopCard(int &extra_message)
{
	static int id, card, player_pos;
	static bool avaliable[10];
	puts("------------------------------------------------------");
	CardList();
	std::vector<int> player_list = GetAvaliablePlayers();
	PrintPlayerList(player_list);
	puts("------------------------------------------------------\n");
	memset(avaliable, 0, sizeof avaliable);
	for (int i = 0; i < player_list.size(); ++i)
		avaliable[player_list[i]] = 1;

	while (true) {
		while (true) {
			printf("Please input the index of the card that you want to play: ");
			scanf("%d", &id);
			if (id < 1 || id > num_cards) {
				puts("Please input a legal number!Re-try!");
				continue;
			}
			else
				break;
		}
		card = cards[id - 1];
		if (card == CRIMINAL) {
			if (num_cards > 1) {
				puts("The CRIMINAL card must be you last card.");
				continue;
			}
			else {
				DeleteCard(id - 1);
				TryTellSystemEmpty();
				return card;
			}
		}
		if (card == DETECTIVE) {
			if (CannotPopCard()) {
				DeleteCard(id - 1);
				TryTellSystemEmpty();
				extra_message = -1;
				return card;
			}
			else if (num_cards > 2) {
				puts("You have more than 2 cards!");
				continue;
			}
			else {
				DeleteCard(id - 1);
				TryTellSystemEmpty();
				extra_message = ReadAnotherPlayerFromTerminal(avaliable);
				return card;
			}
			
		}
		if (card == GOD_DOG || card == WITNESS) {
			DeleteCard(id - 1);
			extra_message = ReadAnotherPlayerFromTerminal(avaliable);
			TryTellSystemEmpty();
			return card;
		}
		if (card == ORDIARY || card == CO_CRIMINAL || card == INTELLIGENCE || card == ABSENT || card == RUMOR) {
			DeleteCard(id - 1);
			TryTellSystemEmpty();
			return card;
		}
		if (card == TRANSACTION) {
			if (num_cards == 1) {
				DeleteCard(id - 1);
				TryTellSystemEmpty();
				extra_message = -1;
				return card;
			}
			else {
				DeleteCard(id - 1);
				extra_message = ReadAnotherPlayerFromTerminal(avaliable);
				return card;
			}
		}
	}
}

int Player :: GetNumOfCards()
{
	return num_cards + 1;
}

void Player :: CardList()
{
	printf("Cards of player %d :", pos);
	if (!num_cards)
		puts(" no cards.");
	else {
		for (int i = 0; i < num_cards; ++i)
			printf(" %s", DIG_TO_NAME_IN_ENGLISH[cards[i]]);
		puts("");
	}
}

bool Player :: IsBeginPlayer()
{
	for (int i = 0; i < num_cards; ++i) {
		if (cards[i] == FIRST) {
			DeleteCard(i);
			return true;
		}
	}
	return false;
}

void Player :: ReceiveNotice(char *notice)
{
	printf("The system tell you: %s\n", notice);
}

void Player :: TryTellSystemEmpty()
{
	if (!num_cards)
		current_game->PlayerIsEmpty(pos);
}

bool Player :: HaveAbsent()
{
	for (int i = 0; i < num_cards; ++i) {
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
			if (_ != 1 && _ != 0) {
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
	for (int i = 0; i < num_cards; ++i) {
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
			puts("Please input a legal number!Re-try!");
			continue;
		}
		else
			break;
	}
	card = cards[id - 1];
	DeleteCard(id - 1);
	return card;
}

int Player :: GOD_DOG_Fold(int dogplayer) {
	return Fold();
}

int Player :: TRANSACTION_Fold(int another_player) {
	return Fold();
}

int Player :: RUMOR_Fold() {
	return RandomFold();
}

int Player :: INTELLIGENCE_Fold() {
	return Fold();
}

int Player :: RandomFold()
{
	static int id, card;
	id = rand() % num_cards;
	card = cards[id];
	DeleteCard(id);
	return card;
}

void Player :: GetScore(int add)
{
	score += add;
}

void Player :: BeWatchedPlayer(Player player)
{
	printf("Player %d's card list:\n", player.pos);
	player.CardList();
}
void Player :: MaintainCards()
{
	std::sort(cards, cards + num_cards);
}
std::vector<int> Player :: GetAvaliablePlayers()
{
	static Node *it;
	std::vector<int> player_list;
	it = &(current_game->list[0]);
	//printf("Avaliable Players List:\n");
	while (true) {
		//printf("Player %d has %d cards.\n", it->pos, current_game->players[it->pos].num_cards);
		player_list.push_back(it->pos);
		it = it->_next;
		if (it->pos == current_game->list[0].pos)
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

int Player :: ReadAnotherPlayerFromTerminal(bool avaliable[])
{
	static int player_pos;
	while (true) {
		printf("Please input a player id: ");
		scanf("%d", &player_pos);
		if (player_pos < 0 || player_pos > 7) {
			puts("Please input a legal number in range [0,7]!");
			continue;
		}
		else if (player_pos == pos) {
			puts("The player can't be yourself!");
			continue;
		}
		else if (!avaliable[player_pos]) {
			puts("The player isn't in the game now!");
			continue;
		}
		else
			return player_pos;
	}
}

