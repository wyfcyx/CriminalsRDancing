#include <cstdio>

#include "Card.h"

Card :: Card(int _)
{
	card_id = _;
	status = 0;
}

Card :: Card(int _, int __)
{
	card_id = _;
	status = __;
}

void Card :: PlayCard()
{
	return ;
}
