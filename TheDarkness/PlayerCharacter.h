#pragma once
#include "character.h"
#include <sstream>
class Player :
	public Character
{
public:
	Player(string name, string left, string right, string up, string down, int startDirection,int health,int playerColumn, int playerRow);
	~Player(void);

	void SetDirection(int& newDirection,Cell *Room[20][20]); //Based off current direction and such, used for making the player look left/right/behind based off current direction

	int Attack();	//Basic Attack, otherwise the computer uses whatever is equipped

	
	void EyeSight(Player* pPlayer, Cell * Room[20][20]);	//Reveals what is in front of the player except a blank cell or cell with an enemy in it

	//INVENTORY**************************************************
	//Inventory
	void Inventory();	//Displays inventory options
	//initializes a container
	void Initialize(Item* container[], int capacity); 
	//Displays the inventory's contents
	void Display(Item* container[], int capacity);
	//Gives the Info for a specific one
	void Info(int& item,Item* container[], int capacity);
	//Checks to see if the Inventory is full
	bool isFull(Item* container[], int capacity);
	//Add to the Inventory
	void Add(Item* pItem);
	//Remove from the Inventory
	void Remove(int& item, Item* container[], int capacity);
	void RemoveUse(int& item, Item* container[],int capacity);
	//Use an Item
	bool Use(int& item, Item* container[], int capacity);
	//Contains
	bool Contains(string, Item* container[], int capacity);
	


	//Equipped Item
	Item* GetEquippedItem() const;
	void SetEquippedItem(Item* ItemToEquip);
	void SetArmour(bool equipped);
	bool GetArmourStatus() const;

	//Reaching out
	string ReachOut(Cell*Room[20][20]);
	//Move
	void Move(Player* playerMove,Cell*Room[20][20]);
	//Checks to see if the player is at full health
	bool isMaxHealth() const;
private:
	//inventory
    static const int INVENTORY_CAPACITY = 5;  
    Item* inventory[INVENTORY_CAPACITY];
	static const int MAX_HEALTH =40;

	//Equipped Item
	Item* equippedItem;
	bool m_ArmourEquipped;

	//Default Combat-So your fists
	static const int  DAMAGE =5 ;
	static const int MODIFIER = 5;

};

