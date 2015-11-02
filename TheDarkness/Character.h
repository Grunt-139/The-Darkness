#pragma once
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Weapon.h"
#include "Cell.h"
#include "GameObject.h"
#include "Item.h"
using namespace std;

class Character:public GameObject
{
public:
	Character(string name, string left, string right, string up, string down, int startDirection, int health, int row, int column);
	~Character();
	void virtual Move(Character* playerMove, Cell * Room[20][20]);
	//Get Name
	string GetName() const;
	//Set Name
	void SetName(string& name);
	//Get Row
	int GetRow() const;
	//Get Column
	int GetColumn() const;
	//Set Position
	void SetPosition(int row, int column);
	//Attack
	int virtual Attack(Weapon* pWeapon);
	//Get Symbol(based off direction)
	string GetSymbol() const;
	//Get the Direction
	int GetDirection()const;
	//Change Direction
	void ChangeDirection(int newDirection);
	//Get Health
	int GetHealth() const;
	//Set Health
	void SetHealth(int newHealth);
	//Take Damage
	void DamageHealth(int& damage, Cell*Room[20][20]);
	//Death
	void Death(Cell*Room[20][20]);
	//Check to see if dead or alive
	bool isDead();
private:
	string m_Left;
	string m_Right;
	string m_Up;
	string m_Down;
	string* m_Name;
	int *m_Direction;
	int *m_Health;
	int *m_playerRow;
	int *m_playerColumn;
	bool m_isDead;
};

