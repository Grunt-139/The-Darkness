#pragma once
#include <iostream>

#include <Windows.h>
#include "Cell.h"
#include "Character.h"
#include "Enemy.h"
#include "PlayerCharacter.h"
#include "GameObject.h"
#include "Weapon.h"
#include "Item.h"
#include "Matches.h"
#include "MedKit.h"
#include "Armour.h"
#include "CombatMgr.h"
#include "GameEventManager.h"

#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <string>

#include <sstream>

using namespace std;

class Game
{
private:
	static const int ALIVE = 1046;
	static const int N_ALIVE = 400;
	static const int ROWS = 20;
	static const int COLUMNS = 20;
	Cell * m_Room[ROWS][COLUMNS];
	Player * m_pPlayer;
	vector<Enemy*>Enemies;		//Enemy Vector
	vector<Enemy*>::iterator m_EnemyIter;	
	vector<Item*>Items;		//Items Vector
	vector<Item*>::iterator m_ItemIter;
	CombatMgr * m_CombatMgr;
	string* m_GameMessage;	//Game Message
	bool *m_lightsOn;	//Are the Lights on or not

	GameEventManager * m_GameEventHandler;	//Event Manager for the game

	int m_currentRoom;	//Current Room
	int m_nextRoom; //Next Room

public:
	Game(void);
	~Game(void);


	//Display Messages
	void SetGameMessage(string message);
	string GetGameMessage() const;

	//Get Player Name
	void SetPlayerName();

	//Turn on the lights
	void SetLightsOn(bool lightsOn);
	bool AreLightsOn() const;
	void TurnOnLights();
	void TurnOffLights();

	//Door--Next Room
	void Door();

	//Game Event
	bool IsThereAnEvent();

	//Kill Everything
	void Clear();

	//Reset
	void Reset();

	//Main Menu
	void MainMenu();	
	//Display Instructions
	void Instructions();	

	//Play game
	void Play();
	//Load Rooms
	void RoomLoad(int load=0);	
	//Populate Room
	void PopulateRoom(unsigned int type[ROWS][COLUMNS]);
	//Room Swap
	void RoomSwap(int newRoom);
	//Play the Correct Beep for the sensor
	void PlayBeep();	
	//Get the count for the sensor
	int GetCount(int& a,int& b, int counter);	
	//Show Room
	void DisplayRoom();
	//Move a Character
	void EnemyTurn(vector<Enemy*> Enemies);
	//Move Player
	void PlayerMove(Player * playerMove);


};

