#ifndef _GAME_H_
#define _GAME_H_

#include <string>

#include <boost/shared_ptr.hpp>

#include "defs.h"
#include "Player.h"
#include "CardManager.h"

#include "CommClient.h"

class RoomController;

struct Node {
	Node *_next;
	Node *back;
	ClientPtr player;

	Node();
	Node(Node* _, Node* __, ClientPtr  ___);
};

class Game {
public:
	Game(int _, int __, RoomController *creator);

	void GameStart();
	void PlayerIsEmpty(ClientPtr player);
	std::string GetMessage(const std::string &message);

private:
	int num_players_, win_score_;
	int rank_[MAX_PLAYER];
	Node list_[MAX_PLAYER];
	RoomController *current_room_;

	CardManager *manager_;

	void GoRound(bool is_rumor, Node *now);

	void SendMessage(ClientPtr the_one, const std::string &message);
	void SendMessage(const std::string &message); // send to all players.
};

#endif // _GAME_H_

