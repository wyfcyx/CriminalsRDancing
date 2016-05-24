#ifndef _SERVER_CONTROLLER_H_
#define _SERVER_CONTROLLER_H_

#include <vector>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>

#include "defs.h"
#include "CommClient.h"

using namespace boost::asio;

class ServerController {
public:
	ServerController();

	void Accept(ClientPtr client, const error_code &err);

private:
	io_service service_;
	ip::tcp::acceptor acceptor_;

	int room_count_[MAX_ROOM];
	std::vector<ClientPtr> client_list_;

	void DisconnectServer(ClientPtr client);

	void GetInRoom(ClientPtr client, int room);
	void GetOutRoom(ClientPtr client);
};


#endif // _SERVER_CONTROLLER_H_

