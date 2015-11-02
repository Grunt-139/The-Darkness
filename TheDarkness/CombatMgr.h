#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "PlayerCharacter.h"
#include "Enemy.h"
#include "Cell.h"


using namespace std;

class CombatMgr
{
public:
	CombatMgr();
	~CombatMgr();
	void Combat(Player* pPlayer, Enemy* pEnemy,Cell*Room[20][20],vector<Enemy*> Enemies);	//Lets get ready to RUMBLE!!!!
	int EnemyTurn(Enemy* pEnemy);//Gets Enemy's attack
	int PlayerTurn(Player* pPlayer,Enemy*pEnemy, Cell*Room[20][20]);//Gets Player's attack
	void Display(Player* pPlayer, Enemy * pEnemy, Cell*Room[20][20]);	//Displays the player and the enemies stats
	bool isCombat(Cell*Room[20][20], Player * pPlayer, vector<Enemy*> Enemies);	//Is there combat?
	void OnEdge(Cell* Room[20][20], Player * pPlayer, vector<Enemy*> Enemies);	//Sees where the enemies are and puts the player on edge
	void Flee(Player* pPlayer, int& direction, Cell*Room[20][20]);	//Handles code for the fleeing
	bool Ambush(Player * pPlayer, vector<Enemy*>::iterator EnemyIter, int&fleeDirection, Cell*Room[20][20],vector<Enemy*> Enemies);
private:
	int m_Damage;
	static const int ARMOUR_BLOCK = 5;
	static const int ARMOUR_MOD=3;
	bool * m_inCombat;
};

