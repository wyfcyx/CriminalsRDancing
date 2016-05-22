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

	void GetScore(int add);

	void CardList();
	int GetNumOfCards();
	void GetCard(int card);
	void DeleteCard(int pos);
	void TryTellSystemEmpty();
	void MaintainCards();

	bool CannotPopCard();
	int PopCard(int &extra_message);
	int Fold();
	int RandomFold();
	int GOD_DOG_Fold(int dogplayer);
	int TRANSACTION_Fold(int another_player);
	int RUMOR_Fold();
	int INTELLIGENCE_Fold();

	bool IsBeginPlayer();
	bool HaveAbsent();
	bool ShowAbsent();
	bool IsCriminal();
	void BeWatchedPlayer(Player player);

	void ReceiveNotice(char *notice);
private:
	int cards[MAX_CARD], num_cards, pos;
	std::vector<int> GetAvaliablePlayers();
	void PrintPlayerList(std::vector<int> player_list);
	int ReadAnotherPlayerFromTerminal(bool avaliable[]);
};

#endif // _PLAYER_H_
