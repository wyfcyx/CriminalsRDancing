#include <map>
#include <cstdio>

#include "Game.h"
#include "Player.h"
#include "defs.h"
#include "CardManager.h"

Game :: Game(int _, int __)
{
	num_players = _;
	win_score = __;
	manager = new CardManager(num_players);

	for (int i = 0; i < num_players; ++i)
		rank[i] = 1;
}

bool Game :: MaintainRanking()
{
	static std::map<int, int> score;
	score.clear();
	for (int i = 0; i < num_players; ++i)
		score.insert(make_pair(players[i], i));
	
	int current_rank = 0, last_rank = 0, last_score = 0;
	for (std::map<int, int>::reverse_iterator i = score.rbegin(); i != score.rend(); ++i, ++current_rank) {

		if (i == score.rbegin() || last_score != i->first)
			rank[i->second] = current_rank;
		else
			rank[i->second] = last_rank;
		
		last_score = i->first;
		last_rank = rank[i->second];
	}

	return score.rbegin()->first >= min_score;
}

void Game :: SubGameStart()
{
	manager->GenerateCardsSequence();
	
}

void Game :: Start()
{
	for (int i = 0; i < num_players; ++i)
		players[i] = Player();

	while (true) {
		SubGameStart();
		
		if (MaintainRanking())
			break;

		PrintRanking();
	}
	puts("Game over!");
}

void Game :: PringRanking()
{
	for (int i = 1; i <= num_players; ++i)
		for (int j = 0; i < num_players; ++j) {
			if(rank[j] == i) {
				printf("Rank %d: %s", i, players[j].name);
				if(i == 1)
					printf("\t\tbeast player!");
				puts("");
			}
		}
}

void Game :: SubGameStart()
{
	/*
	CardManager cardmanager(num_players);
	cardmanager.GenerateCardSequence();
	for (int i = 0; i < num_players; ++i)
		players[i].BeforeTheSubGame();
	int now_card = 0;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < num_players; ++j) {
			players[i].GetCard(cardmanager.card_seq[now_card++]);
		}
	}

	int begin_player;
	for (int i = 0; i < num_players; ++i)
		if (players[i].IsBeginPlayer())
			begin_player = i;

	while (1) {

	}
	*/
}

void Game :: Start()
{
	SetNumberOfPlayers();
	SetWinScore();
}

void ChangePlayer(int pos)
{
	printf("It's player %d 's turn to operate!\n", pos + 1);
	now_operate_player = pos;
}
