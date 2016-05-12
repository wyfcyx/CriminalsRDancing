#ifndef _DEFS_H_
#define _DEFS_H_

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
const char DESCRIPTION[11][150] = {
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
const char DIG_TO_NAME_IN_ENGLISH[11][15] = {
	"CRIMINAL",
	"DETECTIVE",
	"GOD_DOG",
	"WITNESS",
	"ORDIARY",
	"FIRST",
	"CO_CRIMINAL",
	"TRANSACTION",
	"INTELLIGENCE",
	"ABSENT",
	"RUMOR"
};
const char DIG_TO_NAME_IN_CHINESE[11][100] = {
	"犯人",
	"侦探",
	"神犬",
	"目击者",
	"普通人",
	"第一发现者",
	"共犯",
	"交易",
	"情报交换",
	"不在场证明",
	"谣言"
};

#endif // _DEFS_H_