#include <map>
#include <string>
#include <cstdio>
#include <cstdlib>

#include "Game.h"
#include "Player.h"
#include "defs.h"
#include "CardManager.h"

Game :: Game(int _, int __)
{
	num_players_ = _;
	win_score_ = __;
	manager_ = new CardManager(num_players_);

	for (int i = 0; i < num_players_; ++i)
		rank[i] = 1;
}

void Game :: GameStart()
{
	manager_->GenerateCardsSequence();

	/*
	for (int i = 0; i < num_players_; ++i)
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
		list[i]._next = (i + 1 == num_players) ? &list[0] : &list[i + 1];
		list[i].back = !i ? &list[num_players] : &list[i - 1];
	}
	Node *now = &list[start];

	bool terminated = false;
	static char read;
	read = getchar();
	while (true && !terminated) {							// Player loop
		now = now->_next;
		system("clear");
		printf("\nSystem Message : Now is %s's turn.\n", players[now->pos].name);
		printf("Please press enter to begin your round...\n");
		//read = getchar();
		read = getchar();
		system("clear");

		int x = 0;
		int card = players[now->pos].PopCard(x);

		switch (card) {
			case CRIMINAL:
			{
				printf("System Message : %s is cirminal.\n", players[now->pos].name);
				printf("System Message : Criminal wins!\n");
				for (int i = 0; i < num_players; ++i)
					if (players[i].co_criminal)
						players[i].GetScore(2);
				players[x].GetScore(2);

				terminated = true;
				break;
			}

			case DETECTIVE:
			{
				if (x == -1) {
					printf("System Message : %s folded card \"DETECTIVE\"", players[now->pos].name);
				}
				else {
					printf("System Message : %s detects %s.\n", players[now->pos].name, players[x].name);
					if(players[x].ShowAbsent())
						printf("System Message : %s is absent!\n", players[x].name);
					else if(!players[x].IsCriminal())
						printf("System Message : %s is not criminal.\n", players[x].name);
					else {
						printf("System Message : %s is cirminal!\n", players[x].name);
						printf("System Message : Detective wins!\n");
						for (int i = 0; i < num_players; ++i)
							if (!players[i].co_criminal)
								players[i].GetScore(1);
						players[now->pos].GetScore(2);

						terminated = true;
					}
				}
				break;
			}

			case GOD_DOG:
			{
				printf("System Message : %s is biting %s, %s should fold a card.\n",
						players[now->pos].name,
						players[x].name,
						players[x].name);

				int folded_card = players[x].Fold();
				printf("System Message : %s folded %s.\n",
						players[x].name,
						DIG_TO_NAME_IN_ENGLISH[folded_card]);
				if (!folded_card) {
					printf("System Message : %s is Criminal.\n", players[x].name);
					printf("System Message : Dog wins!\n");

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
				printf("System Message : %s will watch %s's cards.\n", players[now->pos].name, players[x].name);
				players[now->pos].BeWatchedPlayer(players[x]);
				printf("System Message : %s has watched %s's cards.\n", players[now->pos].name, players[x].name);
				break;
			}

			case ORDIARY:
			{
				printf("System Message : %s is an ordiary person.\n", players[now->pos].name);
				break;
			}

			case CO_CRIMINAL:
			{
				printf("System Message : %s is co_criminal.\n", players[now->pos].name);
				players[now->pos].co_criminal = true;
				break;
			}

			case TRANSACTION:
			{
				if (x != -1) {
					printf("System Message : %s wants to transaction with %s.\n", players[now->pos].name, players[x].name);
					printf("System Message : %s gives %s a card.\n", players[now->pos].name, players[x].name);
					int folded_card = players[now->pos].Fold();
					printf("System Message : %s gives %s a card.\n", players[x].name, players[now->pos].name);
					int _folded_card = players[x].Fold();

					players[now->pos].GetCard(folded_card);
					players[x].GetCard(_folded_card);
				}
				else {
					printf("System Message : %s give up the TRANSACTION card.\n", players[now->pos].name);
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
				printf("System Message : %s folded card \"absent\"\n", players[now->pos].name);
				break;
			}

			case RUMOR:
			{
				GoRound(true, now);
				break;
			}
		}

		printf("Please press enter to end your round.\n");
		read = getchar();
		read = getchar();
	}
*/
}

void Game :: GoRound(bool is_rumor, Node *now)
{
	Node *p = now;
	static int temp[MAX_PLAYER];
	int tot = 0;
	memset(temp, 0, sizeof(temp));

	// is_rumor = true -> random
	// is_rumor = false -> certain


	// TODO
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


std::string Game :: GetMessage(const std::string &message)
{
	return message;
}

Node :: Node(Node *_, Node *__, boost::shared_ptr<CommClient> ___)
{
	_next = _;
	back = __;
	player = ___;
}

