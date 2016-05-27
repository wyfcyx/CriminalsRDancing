#ifndef _SERVER_CONTROLLER_H_
#define _SERVER_CONTROLLER_H_

#include <vector>
#include <map>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include "defs.h"
#include "CommClient.h"
#include "RoomController.h"

using namespace boost::asio;

class ServerController {
public:
	ServerController();

	void Accept(ClientPtr client, const error_code &err);

private:
	io_service service_;
	ip::tcp::acceptor acceptor_;

	int room_count_[MAX_ROOM];
	RoomController room_[MAX_ROOM];
	std::vector<ClientPtr> client_list_;

	std::map<ClientPtr, int> client_status_[MAX_PLAYER * MAX_ROOM];
	// 0 for square, 1 ~ inf for a certain room.

	void DisconnectServer(ClientPtr client);

	void GetInRoom(ClientPtr client, int room);
	void GetOutRoom(ClientPtr client);
};


#endif // _SERVER_CONTROLLER_H_

