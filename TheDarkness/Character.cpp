#include "Character.h"


Character::Character(string name, string left, string right, string up, string down, int startDirection, int health,int row, int column):m_Left(left),m_Right(right),m_Up(up),m_Down(down)
{
	m_Direction = new int(startDirection);
	m_Health = new int(health);
	m_playerRow = new int(row);
	m_playerColumn = new int(column);
	m_isDead = false;
	m_Name = new string(name);

	//Seed the Random Number Generator
	srand(static_cast<unsigned int>(time(0)));
}


Character::~Character(void)
{
	delete m_Direction;
	m_Direction = NULL;
	delete m_Health;
	m_Health = NULL;
	delete m_playerRow;
	m_playerRow = NULL;
	delete m_playerColumn;
	m_playerColumn = NULL;
}


int Character::Attack(Weapon * pWeapon)
{
	return 0;
}

void Character::DamageHealth(int& damage, Cell* Room[20][20])
{
	int newHealth = *m_Health - damage;
	if(newHealth > 0)
	{
		SetHealth(newHealth);
		m_isDead = false;
	}
	else	//Death
	{
		Death(Room);
	}
}

void Character::Death(Cell*Room[20][20])
{
	cout << GetName() << " is dead." <<endl;
	m_isDead = true;
	Room[GetRow()][GetColumn()]->Reset();
	SetPosition(NULL,NULL);
}

bool Character::isDead()
{
	return m_isDead;
}

string Character::GetSymbol() const
{
	switch(*m_Direction)
	{
	case 1:
		return m_Up;	//Up
		break;
	case 2:
		return m_Down;	//Down
		break;
	case 3:
		return m_Left;	//Left
		break;
	case 4:
		return m_Right;	//Right
		break;
	default:
		return("Fail");
	}
}

string Character::GetName() const
{
	return *m_Name;
}

void Character::SetName(string& name)
{
	*m_Name = name;
}

int Character::GetRow() const
{
	return *m_playerRow;
}

int Character::GetColumn() const
{
	return *m_playerColumn;
}

void Character::SetPosition(int row, int column)
{
	*m_playerRow = row;
	*m_playerColumn = column;
}

void Character::Move(Character* playerMove, Cell * Room[20][20])
{
	int tempType = Room[*m_playerRow][*m_playerColumn]->GetType();
	switch(playerMove->GetDirection())
	{
	case 1:	//Up
		if(Room[*m_playerRow-1][*m_playerColumn]->isEmpty())
		{
			Room[*m_playerRow][*m_playerColumn]->Reset();
			Room[*m_playerRow-1][*m_playerColumn]->SetType(tempType);
			Room[*m_playerRow-1][*m_playerColumn]->SetEmpty();
			Room[*m_playerRow-1][*m_playerColumn]->SetVisibility(true);
			Room[*m_playerRow-1][*m_playerColumn]->SetObject(playerMove);
			SetPosition(*m_playerRow-1,*m_playerColumn);
		}
		else
		{
			ChangeDirection(2);
			cout <<"You ran into "<<Room[*m_playerRow-1][*m_playerColumn]->GetDescription()<<endl;
			Room[*m_playerRow-1][*m_playerColumn]->SetVisibility(true);
			Room[*m_playerRow-1][*m_playerColumn]->SetDiscovered(true);
		}
		break;
	case 2:	//Down
		if(Room[*m_playerRow+1][*m_playerColumn]->isEmpty())
		{
			Room[*m_playerRow][*m_playerColumn]->Reset();
			Room[*m_playerRow+1][*m_playerColumn]->SetType(tempType);
			Room[*m_playerRow+1][*m_playerColumn]->SetEmpty();
			Room[*m_playerRow+1][*m_playerColumn]->SetVisibility(true);
			Room[*m_playerRow+1][*m_playerColumn]->SetObject(playerMove);	//Sets it so the Cell's Object is pointing to the character
			SetPosition(*m_playerRow+1, *m_playerColumn);
		}
		else
		{
			ChangeDirection(1);
			cout <<"You ran into "<<Room[*m_playerRow+1][*m_playerColumn]->GetDescription()<<endl;
			Room[*m_playerRow+1][*m_playerColumn]->SetVisibility(true);
			Room[*m_playerRow+1][*m_playerColumn]->SetDiscovered(true);
		}
		break;
		case 3:	//Left
		if(Room[*m_playerRow][*m_playerColumn-1]->isEmpty())
		{
			Room[*m_playerRow][*m_playerColumn]->Reset();
			Room[*m_playerRow][*m_playerColumn-1]->SetType(tempType);
			Room[*m_playerRow][*m_playerColumn-1]->SetEmpty();
			Room[*m_playerRow][*m_playerColumn-1]->SetVisibility(true);
			Room[*m_playerRow][*m_playerColumn-1]->SetObject(playerMove);	//Sets it so the Cell is pointing to the character
			SetPosition(*m_playerRow,*m_playerColumn-1);
		}
		else
		{
			ChangeDirection(4);
			cout <<"You ran into "<<Room[*m_playerRow][*m_playerColumn-1]->GetDescription()<<endl;
			Room[*m_playerRow][*m_playerColumn-1]->SetVisibility(true);
			Room[*m_playerRow][*m_playerColumn-1]->SetDiscovered(true);
		}
		break;
	case 4:	//Right
		if(Room[*m_playerRow][*m_playerColumn+1]->isEmpty())
		{
			Room[*m_playerRow][*m_playerColumn]->Reset();
			Room[*m_playerRow][*m_playerColumn+1]->SetType(tempType);
			Room[*m_playerRow][*m_playerColumn+1]->SetEmpty();
			Room[*m_playerRow][*m_playerColumn+1]->SetVisibility(true);
			Room[*m_playerRow][*m_playerColumn+1]->SetObject(playerMove);	//Sets it so the Cell is pointing to the character
			SetPosition(*m_playerRow,*m_playerColumn+1);
		}
		else
		{
			ChangeDirection(3);
			cout <<"You ran into "<<Room[*m_playerRow][*m_playerColumn+1]->GetDescription()<<endl;
			Room[*m_playerRow][*m_playerColumn+1]->SetVisibility(true);
			Room[*m_playerRow][*m_playerColumn+1]->SetDiscovered(true);
		}
		break;
	}
}


int Character::GetDirection() const
{
	switch(*m_Direction)
	{
	case 1:
		return 1;	//Up
		break;
	case 2:
		return 2;	//Down
		break;
	case 3:
		return 3;	//Left
		break;
	case 4:
		return 4;	//Right
		break;
	default:
		return(1337);
	}
}

void Character::ChangeDirection(int newDirection)
{
	*m_Direction = newDirection;
}

int Character::GetHealth() const
{
	return *m_Health;
}

void Character::SetHealth(int newHealth)
{
	*m_Health = newHealth;
}
