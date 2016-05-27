#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>

#include "RoomController.h"

RoomController :: RoomController()
{
	is_playing_ = false;
	min_score = DEFAULT_SCORE_TO_WIN;
}

void GotMessage(const std::string &message)
{

}

void MaintainRanking()
{
}

void NewPlayer(ClientPtr client)
{
	player_list_.push_back(client);
}

void GameStart()
{
	int total_player = player_list_.size();
	current_game_ = new Game(total_player , min_score_);
}

void ChangeMinScore(int new_score)
{
	min_score_ = new_score;
}

