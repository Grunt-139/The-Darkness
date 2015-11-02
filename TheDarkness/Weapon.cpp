#include "Weapon.h"


Weapon::Weapon(string name, string description, bool use):Item(name,description,use)
{
	srand(static_cast<unsigned int>(time(0)));
	vector<int>RandomNumber;
	for(int i =0; i < 4; i++)
	{
		RandomNumber.push_back(i);
	}
	random_shuffle(RandomNumber.begin(),RandomNumber.end());
	//Random Weapon Generator
	switch(RandomNumber.front())
	{
	case 0:
		m_Name = "Lead Pipe";
		m_Damage = 8;
		m_Description ="A solid, heavy lead pipe.";
		break;
	case 1:
		m_Name = "Beating stick";
		m_Damage = 5;
		m_Description ="A beating stick.";
		break;
	case 2:
		m_Name = "Combat Knife";
		m_Damage = 10;
		m_Description = "A good sturdy KaBar knife.";
		break;
	case 3:
		m_Name = "Axe";
		m_Damage = 15;
		m_Description = "An axe originally meant for emergencies, like a fire.";
		break;
	}
}


Weapon::~Weapon(void)
{
}

int Weapon::UseItem()
{
	int randomDamage = m_Damage + (rand()%MODIFIER);	//Takes the base damage, and adds part of the modifier
	return randomDamage;
}
