#include "Matches.h"


Matches::Matches(string name, string description, bool use):Item(name,description,use)
{
	srand(static_cast<unsigned int>(time(0)));
}


Matches::~Matches(void)
{
}

int Matches::UseItem()
{
	int randomDamage = 3+ (rand()%5);	//Returns damage 3-8
	return randomDamage;
}