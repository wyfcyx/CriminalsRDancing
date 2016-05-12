#include <map>
#include <string>
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
		score.insert(std::make_pair(players[i].score, i));
	
	int current_rank = 0, last_rank = 0, last_score = 0;
	for (std::map<int, int>::reverse_iterator i = score.rbegin(); i != score.rend(); ++i, ++current_rank) {

		if (i == score.rbegin() || last_score != i->first)
			rank[i->second] = current_rank;
		else
			rank[i->second] = last_rank;
		
		last_score = i->first;
		last_rank = rank[i->second];
	}

	return score.rbegin()->first >= win_score;
}

void Game :: SubGameStart()
{
	manager->GenerateCardsSequence();

	for (int i = 0; i < num_players; ++i)
		players[i].BeforeTheSubGame();

	int p_card = 0;
	for (int i = 0; i < num_players; ++i)
		for (int j = 0; j < 4; ++j)
			players[i].GetCard(manager->card_seq[p_card++]);

	int start = 0;
	for (int i = 0; i < num_players; ++i)
		if (players[i].IsBeginPlayer()) {
			start = i;
			break;
		}


	memset(list, 0, sizeof(list));
	for (int i = 0; i < num_players; ++i) {
		list[i].pos = i;
		list[i]._next = (i + 2 == num_players) ? &list[0] : &list[i + 1];
		list[i].back = !i ? &list[num_players] : &list[i - 1];
	}
	Node *now = &list[start];

	bool terminated = false;
	while (true && !terminated) {							// Player loop
		now = now->_next;
		printf("Now is %s's tern.\n", players[now->pos].name);

		int x = 0;
		int card = players[now->pos].PopCard(x);

		switch (card) {
			case CRIMINAL:
			{
				printf("%s is cirminal.\n", players[now->pos].name);
				printf("Criminal wins!\n");
				for (int i = 0; i < num_players; ++i)
					if (players[i].co_criminal)
						players[i].GetScore(2);
				players[x].GetScore(2);
				
				terminated = true;
				break;
			}

			case DETECTIVE:
			{
				printf("%s detects %s.\n", players[now->pos].name, players[x].name);
				if(players[x].ShowAbsent())
					printf("%s is absent!\n", players[x].name);
				else if(!players[x].IsCriminal())
					printf("%s is not criminal.\n", players[x].name);
				else {
					printf("%s is cirminal!\n", players[x].name);
					printf("Detective wins!\n");
					for (int i = 0; i < num_players; ++i)
						if (!players[i].co_criminal)
							players[i].GetScore(1);
					players[now->pos].GetScore(2);

					terminated = true;
				}
				break;
			}

			case GOD_DOG:
			{
				printf("%s is biting %s, %s should fold a card.\n",
						players[now->pos].name,
						players[x].name,
						players[x].name);

				int folded_card = players[x].Fold();
				printf("%s folded %s",
					   players[x].name,
					   DIG_TO_NAME_IN_ENGLISH[folded_card]);
				if (!folded_card) {
					printf("%s is Criminal.", players[x].name);
					printf("Dog wins!\n");

					for (int i = 0; i < num_players; ++i)
						if (!players[x].co_criminal)
							players[x].GetScore(1);
					
					players[now->pos].GetScore(3);
					
					terminated = true;
				}
				break;
			}

			case WITNESS:
			{
				printf("%s will watch %s's cards.\n", players[now->pos].name, players[x].name);
				players[now->pos].BeWatchedPlayer(players[x]);
				printf("%s has watched %s's cards.\n", players[now->pos].name, players[x].name);
				break;
			}

			case ORDIARY:
			{
				printf("%s is an ordiary person.\n", players[now->pos].name);
				break;
			}

			case CO_CRIMINAL:
			{
				printf("%s is co_criminal.\n", players[now->pos].name);
				players[now->pos].co_criminal = true;
				break;
			}

			case TRANSACTION:
			{
				if (x != -1) {
					printf("%s wants to transaction with %s.\n", players[now->pos].name, players[x].name);
					printf("%s gives %s a card.\n", players[now->pos].name, players[x].name);
					int folded_card = players[now->pos].Fold();
					printf("%s gives %s a card.\n", players[x].name, players[now->pos].name);
					int _folded_card = players[x].Fold();

					players[now->pos].GetCard(folded_card);
					players[x].GetCard(_folded_card);
				}
				else {
					printf("%s give up the TRANSACTION card.\n", players[now->pos].name);
				}
				break;
			}

			case INTELLIGENCE:
			{
				GoRound(false, now);
				break;
			}

			case ABSENT:
			{
				printf("%s folded card \"absent\"\n", players[now->pos].name);
				break;
			}

			case RUMOR:
			{
				GoRound(true, now);
				break;
			}
		}
	}
}

void Game :: GoRound(bool is_rumor, Node *now)
{
	Node *p = now;
	int temp[MAX_PLAYER], tot = 0;
	memset(temp, 0, sizeof(temp));
	do {
		if(!is_rumor) {
			printf("%s needs to select a card and give it to next player.\n", players[p->pos].name);
			temp[tot++] = players[p->pos].Fold();
		}
		else
			temp[tot++] = players[p->pos].RandomFold();
		p = p->_next;
	}while (p != now);

	p = now;
	for (int i = 0; i < tot; ++i) {
		players[p->_next->pos].GetCard(temp[i]);
		p = p->_next;
	}
}

void Game :: Start()
{
	char temp_name[10] = "test name";
	for (int i = 0; i < num_players; ++i)
		players[i] = Player(temp_name, this, i);

	Player *winner = NULL;
	while (true) {
		SubGameStart();
		
		if (MaintainRanking())
			break;

		PrintRanking();
	}
	puts("Game over!");
	static bool is_winner[MAX_PLAYER];
	memset(is_winner, 0, sizeof(is_winner));
	int winners = 0;
	char *name = NULL;
	for (int i = 0; i < num_players; ++i)
		if (players[i].score >= win_score)
			is_winner[i] = true, ++winners, name = players[i].name;

	if (winners == 1)
		printf("Winner is %s.\n", name);
	else {
		printf("Winners are:");
		for (int i = 0; i < num_players; ++i)
			if (is_winner[i])
				printf(" %s,", players[i].name);
		puts(".");
	}
}

void Game :: PlayerIsEmpty(int pos) 
{
	for (int i = 0; i < num_players; ++i)
		if(list[i].pos == pos) {
			list[i].back->_next = list[i]._next;
			list[i]._next->back = list[i].back;
			break;
		}
}

void Game :: PrintRanking()
{
	puts("Now Ranking:");
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

Node :: Node(Node *_, Node *__, int ___)
{
	_next = _;
	back = __;
	pos = ___;
}

Node :: Node()
{

}
