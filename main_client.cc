#include <cstdio>
#include <cstring>
#include <iostream>

#include "UserInterface.h"

int main()
{
	UserInterface *view_controller = new UserInterface();

	view_controller->Welcome();

	return EXIT_SUCCESS;
}

