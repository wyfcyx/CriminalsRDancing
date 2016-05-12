#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <vector>

#include "defs.h"

class Game;

class Player {
public:
	int score;
	char name[110];
	bool co_criminal;
	Game *current_game;
	Player();
	Player(char *_name, Game *_game, int _pos);

	void BeforeTheSubGame();
	void GetCard(int card);
	void DeleteCard(int pos);
	int PopCard(int &extra_message);
	int GetNumOfCards();
	void CardList();
	bool IsBeginPlayer();
	void ReceiveNotice(char *notice);
	void TryTellSystemEmpty();
	bool HaveAbsent();
	bool ShowAbsent();
	bool IsCriminal();
	int Fold();
	int RandomFold();
	void GetScore(int add);
	void BeWatchedPlayer(Player player);

private:
	int cards[MAX_CARD], num_cards, pos;
	std::vector<int> GetAvaliablePlayers();
	void PrintPlayerList(std::vector<int> player_list);
	int ReadAnotherPlayerFromTerminal(bool avaliable[]);
};

#endif // _PLAYER_H_