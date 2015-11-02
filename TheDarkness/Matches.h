#pragma once
#include "item.h"
#include <ctime>
#include <cstdlib>
class Matches :
	public Item
{
public:
	Matches(string name="Matches", string description="A box of Matches", bool use= true);
	~Matches(void);
	int UseItem();
};

