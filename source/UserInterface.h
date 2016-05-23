#ifndef _USER_INTERFACE_H_
#define _USER_INTERFACE_H_

#include <boost/shared_ptr.hpp>

#include "defs.h"
#include "CommServer.h"

class UserInterface {
public:
	UserInterface();

	void Welcome();
	void Entrance();
	void FailedToConnect();
	void SuccessToConnect();

private:
	std::string username_, server_ip_;
	int port_;
	boost::shared_ptr<CommServer> pipe_;

	void SquareEntrance();
};

#endif // _USER_INTERFACE_H_
