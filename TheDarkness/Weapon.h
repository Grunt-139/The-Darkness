#pragma once
#include "Item.h"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
class Weapon:public Item
{
public:
	Weapon(string name="A Weapon", string description="Use to defend yourself with", bool use=true);
	~Weapon(void);
	int UseItem();
private:
	int m_Damage;
	static const int MODIFIER = 5;
};

