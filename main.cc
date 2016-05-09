#include <cstdio>
#include <cstring>
#include <climits>
#include <iostream>
#include <algorithm>

#include "defs.h"
#include "CardManager.h"

//defs.h
#define CRIMINAL       0 // cirminal
#define DETECTIVE      1 // detective
#define GOD_DOG        2 // god dog
#define WITNESS        3 // witness
#define ORDIARY        4 // ordinary person
#define FIRST          5 // first witness
#define CO_CRIMINAL    6 // co-criminal
#define TRANSACTION    7 // transaction
#define INTELLIGENCE   8 // intelligence
#define ABSENT         9 // absent
#define RUMOR         10 // rumor

const int MAX_CARD = 4;
const int ALL_CARD = 32;
const int MAX_PLAYER = 8;
const int MIN_PLAYER = 3;
const int CARD_AMOUNT[11] = {1, 4, 1, 3, 2, 1, 2, 4, 4, 5, 5}; 
const char DESCRIPTION[11][100] = {
	"cirminal: You are the cirminal now!",
	"detective: You can detect whether a player is the criminal.",
	"god dog: You have a chance to ask a player to abandon a card and then he/she will pick this card up.",
	"witness: You have a chance to see all cards which a certain player are holding.",
	"ordinary person: This card has no effect...",
	"first witness: Put this card to start the game.",
	"co-criminal: You have a chance to announce that you are also cirminal.",
	"transaction: You have a chance to ask a player to swap a card from each other.",
	"swap intelligence: Every player give a card from his/her cards to his/her right player.",
	"absent: When one wants to detect you, you can show this card to avoid his detection.",
	"rumor: Every player will get a random card from his/her left player."
};
//

//CardManager.h
#ifndef _CARD_MANAGER_H_
#define _CARD_MANAGER_H_

#include "defs.h"

const int predealed_sequence[32] = {
	FIRST, CRIMINAL, DETECTIVE, ABSENT, // 3 player
	CO_CRIMINAL, // 4 player
	ABSENT, // 5 player
	DETECTIVE, CO_CRIMINAL, // 6 player
	ABSENT, // 7 player
	DETECTIVE, DETECTIVE, 
	GOD_DOG,
	WITNESS, WITNESS, WITNESS,
	ORDIARY, ORDIARY,
	TRANSACTION, TRANSACTION, TRANSACTION, TRANSACTION,
	INTELLIGENCE, INTELLIGENCE, INTELLIGENCE, INTELLIGENCE,
	ABSENT, ABSENT,
	RUMOR, RUMOR, RUMOR, RUMOR, RUMOR // others
};
const int start_point[10] = {0, 0, 0, 4, 5, 6, 8, 9};
const int add_cards[10] = {0, 0, 0, 8, 11, 14, 16, 19};
const int total_cards[10] = {0, 0, 0, 12, 16, 20, 24, 28, 32};

class CardManager {
	int total_players;
	int card_seq[50];

	CardManager(int _);
	bool GenerateCardsSequence();
};

void Shuffle(int *array, int elements);
//

class Player {
	int cards[MAX_CARD], num_cards, score;
	Player() {
		score = 0;
	}
	void init() {
		memset(cards, 0, sizeof cards);	
	}
};
bool IsSomePlayerWin(Player Players[], int players_number, int win_score) {
	static int mx, cnt;
	mx = cnt = 0;
	for (int i = 0; i < players_number; ++i) {
		if(Players[i].score > mx) {
			mx = Players[i].score;
			cnt = 1;
		}
		else if(mx == Players[i].score)
			++cnt;
	}
	if (mx >= win_score && cnt == 1)
		return 1;
	else
		return 0;
}

int main()
{
	printf("请输入玩家的人数： ");
	int players_number;
	while (1) {
		scanf("%d", &players_number);
		if(players_number < 3 || players_number > 8) {
			puts("游戏人数必须在3人和8人之间，请重新输入！");
			continue ;
		}
		else
			break ;
	}
	
	printf("请输入赢得游戏的最低得分： ");
	int win_score;
	while (1) {
		scanf("%d", &win_score);
		if(win_score <= 0) {
			puts("赢得游戏得分必须为正整数，请重新输入！");
			continue ;
		}
		else
			break ;
	}
	scanf("%d", &win_score);
	Player players[players_number];
	while (!is_some_player_win(players, players_number, win_score)) {
		for (int i = 0; i < players_number; ++i) {
			players[i].init();
		}
		//开始洗牌并分配

	}
}