#ifndef _ROOM_CONTROLLER_H_
#define _ROOM_CONTROLLER_H_

#include <vector>

#include "defs.h"
#include "CommClient.h"
#include "Game.h"

class RoomController {
public:
	RoomController();

	bool is_playing_;

	void GotMessage(const std::string &message);

private:
	std::vector<ClientPtr> seat_;
	std::vector<ClientPtr> player_list_;
	int score_[MAX_PLAYER], rank_[MAX_PLAYER];

	Game *current_game_;

	int min_score_;

	void NewPlayer(ClientPtr client);
	void ChangeMinScore(int new_score);

	void GameStart();
}

#endif // _ROOM_CONTROLLER_H_
