#ifndef _ROOM_CONTROLLER_H_
#define _ROOM_CONTROLLER_H_

#include <vector>

#include "CommClient.h"

class RoomController {
public:
	RoomController(const std::vector<ClientPtr> *client_list, const int room);

private:
	std::vector<ClientPtr> seat_;
	int score_[MAX_PLAYER], rank_[MAX_PLAYER];

	void MaintainRanking();
}

#endif // _ROOM_CONTROLLER_H_
