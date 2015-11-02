#pragma once
#include <iostream>
#include <string>
#include "Cell.h"
#include "GameObject.h"
#include "PlayerCharacter.h"

#include <vector>
#include <algorithm>


class GameEventManager: public GameObject
{
public:
	GameEventManager(int Row,int Column);
	~GameEventManager(void);

	bool isRoomClear(int room);	//Checks to see if all objectives for that room are done
	void CreateNextEvent(Cell*Room[20][20]);	//Randomly places the next game event on the map
	void SetPosition(int Row, int Column);	//Sets the position of an event
	int GetRow() const;	//Gets the Row of the current Event
	int GetColumn() const;	//Gets the Column of the current Event
	int GetEvent() const;	//Returns the event number
	void PlayEvent(Player * pPlayer, Cell*Room[20][20]);	//Calls up the correct function for the event
	void Reset();
	bool GetGameOver() const;
	void SetEventPosition(int pos);

	//EVENTS
	//Floor One
	void GameStart(Player * pPlayer);
	void FirstRadioContact(Player * pPlayer);
	void FindTheKey(Player * pPlayer);
	void GoToElevator(Player * pPlayer);

	//Floor Two
	void YouFoundTheGenerator(Player * pPlayer);
	void FindGasoline(Player * pPlayer);
	void FindTools(Player * pPlayer);
	void FindKey(Player * pPlayer);
	void UnderAttack(Player * pPlayer);

	//Floor 2-3 Bridge
	void GetThroughTheDoor();

	//Floor Three
	void DarkRevelations(Player * pPlayer);
	void Choices(Player* pPlayer);

	//Endings
	void Hero();
	void Villain();
	void Survivor();

private:
	int * m_pEventPosition;
	int * m_pEventRow;
	int * m_pEventColumn;
	int * m_pStartRow;
	int * m_pStartColumn;
	string * m_pSymbol;
	bool * m_pRoom1Clear;
	bool * m_pRoom2Clear;
	bool * m_pRoom3Clear;
	bool * m_GameOver;
	
};

