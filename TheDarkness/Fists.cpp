#include "Fists.h"


Fists::Fists(string name, string description,int damage, bool use=true):Weapon(name,description,damage,use), m_Damage(damage)
{
}


Fists::~Fists(void)
{
}


int Fists::UseItem() const
{
	int randomDamage = m_Damage + (rand()%MODIFIER);	//Takes the base damage, and adds part of the modifier
	return randomDamage;
}