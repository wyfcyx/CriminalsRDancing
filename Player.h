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
	Player(char *_name, Game *_game, int _pos);

	void BeforeTheSubGame();
	void GetCard(int card);
	void DeleteCard(int pos);
	int PopCard();
	int GetNumOfCards();
	int GetScore();
	void CardList();
	void GainScore(int add);
	bool IsBeginPlayer();
	void ReceiveNotice(char *notice);
	void TellSystemEmpty();
	bool HaveAbsent();
	bool ShowAbsent();
	bool IsCriminal();
	int Fold();
	int RandowFold();
	std::vector<int> GetAvaliablePlayers();
	void PrintPlayerList(std::vector<int> player_list);

private:
	int cards[MAX_CARD], num_cards, pos;
};

#endif // _PLAYER_H_
