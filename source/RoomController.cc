#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>

#include <boost/shared_ptr.hpp>

#include "defs.h"
#include "RoomController.h"
#include "CommClient.h"

RoomController :: RoomController(const std::vector<ClientPtr> *client_list, const int room)
{
	std::vector<ClientPtr>::iterator iter;
	int count = 0;
	for (iter = client_list.begin(); iter != client_list.end(); ++iter)
		if (*iter->status_ == room)
			++count;

	Game *current_game = Game(count, DEFAULT_SCORE_TO_WIN);
	for (iter = client_list.begin(); iter != client_list.end(); ++iter)
		if (*iter->status_ == room)
			current_game->list[*iter->pos_] = *iter;
}
