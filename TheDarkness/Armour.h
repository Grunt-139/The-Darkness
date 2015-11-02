#pragma once
#include "item.h"
#include "PlayerCharacter.h"
class Armour :
	public Item
{
public:
	Armour(string name="Armour", string description="A set of body Armour", bool use=true);
	~Armour(void);
};

