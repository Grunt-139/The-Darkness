#pragma once
#include "item.h"
class Flashlight :
	public Item
{
public:
	Flashlight(string name, string description, bool use=true);
	~Flashlight(void);
};

