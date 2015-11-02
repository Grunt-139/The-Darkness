#pragma once
#include "character.h"
#include "PlayerCharacter.h"
class Enemy :
	public Character
{
public:
	Enemy(string name, string left, string right, string up, string down, int startDirection, int health, int playerRow,int playerColumn, bool lightSensitive = true);
	~Enemy(void);
	//Set Direction based off players position
	void whereIsPlayer(Cell* Room[20][20], Player* pPlayer);
	//Reset Function
	void Reset();
	//Move
	void Move(Enemy* playerMove, Cell* Room[20][20], int timesAttempted);
	//Wall Detector
	void wallDetector(Enemy*playerMove, Cell * Room[20][20]);
	//Checks to see if it is sensitive to light
	bool isLightSensitive() const;
	//Claw Attack
	int Attack();
	//Bite Attack
	int BiteAttack();
	//Heal
	void Heal();
	//Get Max Health
	int GetMaxHealth()const;

private:
	bool m_LightSensitivity;
	//Base damages
	static const int CLAW_DAMAGE=5;
	static const int BITE_DAMAGE=10;
	static const int MODIFIER = 5;
	//Healing
	static const int HEAL=5;
	int m_MaxHealth;
};

