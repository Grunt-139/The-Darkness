#include "Cell.h"
//An individual spot a player/enemy/box can stand in

Cell::Cell(int type, string description, GameObject * object):m_Type(type), m_Description(description),m_MyObject(object)
{
	vector<int>Rand;
	for(int i =0; i<5; i++)
	{
		Rand.push_back(i);
	}
	random_shuffle(Rand.begin(),Rand.end());
	switch(m_Type)
	{
	case 0:
		m_Symbol = "   "; //Blank
		m_Empty = true;
		m_isVisible = false;
		SetDiscovered(false);
		break;
	case 1:				//OUTSIDE
		m_Symbol = "|"; //Wall
		m_Empty = false;
		m_isVisible = true;
		SetDiscovered(true);
		SetDescription("a wall, don't think you'll do much here.");
		break;
	case 2:
		m_Symbol = "---"; //Top/Bottom
		m_Empty = false;
		m_isVisible = false;
		SetDiscovered(false);
		SetDescription("a wall, don't think you'll do much here.");
		break;
	case 3:
		m_Symbol = " | "; //Inside Wall
		m_Empty = false;
		m_isVisible = false;
		SetDiscovered(false);
		SetDescription("a wall, don't think you'll do much here.");
		break;
	case 4:	//Player the symbol is taken from the Player class
		m_Empty = false;
		m_isVisible = true;
		break;
	case 5:	//Enemy the symbol is taken from the Enemy class
		m_Empty = false;
		m_isVisible = false;
		SetDiscovered(false);
		break;
	case 6:
		m_Symbol = "---"; //Top/Bottom for the outside 
		m_Empty = false;
		m_isVisible = true;
		SetDiscovered(true);
		SetDescription("a wall, don't think you'll do much here.");
		break;
	case 7:		//Item for the player----Matches
		m_Symbol = " * ";
		m_Empty = false;
		m_isVisible = false;
		SetDiscovered(false);
		SetDescription(description);
		break;
	case 8:		//Item for the Player-----Armour
		m_Symbol = " * ";
		m_Empty = false;
		m_isVisible = false;
		SetDiscovered(false);
		SetDescription(description);
		break;
	case 9:		//Item for the Player-----MedKit
		m_Symbol = " * ";
		m_Empty = false;
		m_isVisible = false;
		SetDiscovered(false);
		SetDescription(description);
		break;
	case 10:	//Game Event
		m_Symbol = " ! ";
		m_Empty = false;
		m_isVisible = true;
		SetDiscovered(true);
		SetDescription(description);
		break;
	case 11:	//Eye Candy
		m_Symbol = " x ";
		m_Empty = false;
		m_isVisible = false;
		SetDiscovered(false);
		switch(Rand.front())
		{
		case 0:
			description ="A Table";
			break;
		case 1:
			description ="A Chair";
			break;
		case 2:
			description ="A Computer Parts";
			break;
		case 3:
			description ="Stack of boxes";
			break;
		case 4:
			description ="A Desk";
			break;
		}
		SetDescription(description);
		break;
	case 12:	//Weapon
		m_Symbol = " * ";
		m_Empty = false;
		m_isVisible = false;
		SetDiscovered(false);
		SetDescription(description);
		break;
	case 13:	//Exit
		m_Symbol = "{ }"; 
		m_Empty = false;
		m_isVisible = false;
		SetDiscovered(false);
		SetDescription("An exit. Were you planning on leaving?");
		break;
	};
}


Cell::~Cell(void)
{
}

string Cell::GetDescription() const
{
	return m_Description;
}

void Cell::SetDescription(string newDescription)
{
	m_Description = newDescription;
}

void Cell::Reset()
{
	m_Type = 0;
	m_Symbol = "   ";
	m_Empty = true;
	SetVisibility(false);
	SetDiscovered(false);
	SetDescription("An empty space");
	m_MyObject=NULL;
}

void Cell::SetSymbol(string& newSymbol)
{
	m_Symbol = newSymbol;
}

const string& Cell::GetSymbol() const
{	

	return m_Symbol;	//Returns the symbol that the Cell is currently storing
}

const int& Cell::GetType() const
{
	return m_Type;	//Returns the Cells type
}

void Cell::SetType(int newType)
{
	m_Type = newType;
}

bool Cell::isEmpty() const
{
	return m_Empty;	//Returns whether or not its empty
}

void Cell::SetEmpty()
{
	//Does a reversal, if empty it becomes full and vice versa
	if(m_Empty)
	{
		m_Empty = false;
	}
	else
	{
		m_Empty = true;
	}
}

bool Cell::GetVisible() const
{	
	return m_isVisible;
}

void Cell::SetVisibility(bool visible)
{
	m_isVisible = visible;

	if(isDiscovered())
	{
		m_isVisible = true;
	}
}

void Cell::SetDiscovered(bool discovered)
{
	//This is used for when the lights flicker on and off, so when the lights go off the stuff the player has seen stays seen
	m_Discovered = discovered;
}

bool Cell::isDiscovered() const
{
	return m_Discovered;
}

void Cell::SetObject(GameObject * newObject)
{
	m_MyObject = newObject;
}

GameObject* Cell::GetObject() const
{
	return m_MyObject;
}

ostream& operator <<(ostream& os, const Cell& aCell)
{
	if(aCell.m_isVisible==true)
	{
		os << aCell.m_Symbol;
	}
	else 
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0);
		os << aCell.m_Symbol;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	}
	return os;
}