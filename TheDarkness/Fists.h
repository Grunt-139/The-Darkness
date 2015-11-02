#pragma once
#include "weapon.h"
class Fists :
	public Weapon
{
public:
	Fists(string name="Your Fists", string description="Five finger mary, fisticuffs, etc",int damage = 5, bool use=true);
	~Fists();
	int UseItem() const;
private:
	int m_Damage;
	static const int MODIFIER = 5;
};

