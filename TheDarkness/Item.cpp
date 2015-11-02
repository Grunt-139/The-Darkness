#include "Item.h"


Item::Item(string name, string description, bool use):m_Name(name), m_Description(description), m_canUse(use)
{
}


Item::~Item(void)
{
}

int Item::UseItem()
{
	return 0;
}

const string& Item::GetName() const
{
	return m_Name;
}

const string& Item::GetDescription() const
{
	return m_Description;
}

const bool Item::CanUse() const
{
	return m_canUse;
}


ostream& operator <<(ostream& os, const Item& aItem)
{
	os << aItem.m_Name;
	return os;
}
