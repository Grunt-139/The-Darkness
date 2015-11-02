#pragma once
#include "item.h"
#include "PlayerCharacter.h"
class MedKit :
	public Item
{
public:
	MedKit(string name="Med Kit", string description = "A small bag of bandages, and painkillers", bool use= true);
	~MedKit(void);
	int UseItem();
private:
	static const int HEAL = 20;
};

