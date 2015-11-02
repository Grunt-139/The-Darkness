#pragma once

#include <string>
#include <iostream>
#include "GameObject.h"

using namespace std;
class Item:public GameObject
{
	friend ostream& operator <<(ostream& os, const Item& aItem);
public:
	Item(string name, string description, bool use= false);
	~Item(void);
	const string& GetName() const;
	const string& GetDescription() const;
	const bool CanUse() const;
	virtual int UseItem();
protected:
	string m_Name;
	string m_Description;
	bool m_canUse;
};

