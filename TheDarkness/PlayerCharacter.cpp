#include "PlayerCharacter.h"


Player::Player(string name, string left, string right, string up, string down,int startDirection, int health,int playerRow, int playerColumn):Character(name,left,right,up,down,startDirection,health,playerRow,playerColumn)
{
	Initialize(inventory, INVENTORY_CAPACITY);
	equippedItem = NULL;
	m_ArmourEquipped = false;
}


Player::~Player()
{
}

void Player::SetDirection(int& newDirection,Cell*Room[20][20])
{
	//Direction being passed in
	//1 - Left
	//2 - Right
	//3 - Behind
	//Direction's in general
	//1 - Up
	//2 - down
	//3 - Left
	//4 - Right

	switch(GetDirection())
	{
	case 1:	//Up
		switch(newDirection)
		{
		case 1:	//Left
			ChangeDirection(3);	//Left
			break;
		case 2:	//Right
			ChangeDirection(4);	//Right
			break;
		case 3:	//Behind
			ChangeDirection(2);	//Down
			break;
		}
		break;
	case 2:	//Down
		switch(newDirection)
		{
		case 1:	//Left
			ChangeDirection(4);	//Right
			break;
		case 2:	//Right
			ChangeDirection(3);	//Left
			break;
		case 3:	//Behind
			ChangeDirection(1);	//Up
			break;
		}
		break;
	case 3:	//Left
		switch(newDirection)
		{
		case 1:	//Left
			ChangeDirection(2); //Down
			break;
		case 2:	//Right
			ChangeDirection(1); //Up
			break;
		case 3:	//Behind
			ChangeDirection(4);	//Right
			break;
		}
		break;
	case 4:	//Right
		switch(newDirection)
		{
		case 1:	//Left
			ChangeDirection(1);	//Up
			break;
		case 2:	//Right
			ChangeDirection(2);	//Down
			break;
		case 3:	//Behind
			ChangeDirection(3);	//Left
			break;
		}
		break;

	}
	EyeSight(this,Room);
}

int Player::Attack()
{
	int randomDamage = DAMAGE + (rand()%MODIFIER);	//Takes the base damage, and adds part of the modifier
													//So you get 5-10 damage with just your fists
	return randomDamage;
}



void Player::Inventory()
{
	string choice;         //menu choice
	int itemN;


    do 
    { 
		cout << "Inventory:" << endl;
		Display(inventory, INVENTORY_CAPACITY);
        cout << "---------" << endl << endl;
        cout << "0 - Back" << endl;
        cout << "1 - Use";
        cout << endl;
		cout << "2 - Info";
		cout << endl;
        cout << "3 - Remove an item from the inventory";
        cout << endl;
        cout << endl << "Choice: ";
        cin >> choice;
        cout << endl;

        switch (choice[0])
        {
        case '0':	
			break;
        case '1':
			cout << "What Item would you like to use?(Enter Number): ";
			cin >> itemN;
			cout <<endl;
			if(Use(itemN, inventory, INVENTORY_CAPACITY))
			{
				//Special remove
				RemoveUse(itemN,inventory,INVENTORY_CAPACITY);		//If the Item is used then it is removed from the inventory
			}
			else
			{
				cout << "Item found but has cannot be used" <<endl;		//If it isnt used then the player is told and it remains in the inventory
			}
			break;
		case '2':
			cout << "What Item would you like to learn more about?(Enter Number): ";
			cin >> itemN;
			cout <<endl;
			Info(itemN,inventory, INVENTORY_CAPACITY);
			break;
        case '3':
			 Display(inventory,INVENTORY_CAPACITY);
             cout << "Enter the NUMBER of the item to remove: ";
             cin >> itemN;
			 Remove(itemN, inventory, INVENTORY_CAPACITY);
			break;	
        default:
            cout << "Sorry, " << choice;
            cout << " isn't a valid choice." << endl;
        }
    } while (choice != "0");
}
void Player::Initialize(Item* container[], int capacity)
{
    //set all elements to NULL
    for (int i=0; i<capacity; ++i)
    {
        container[i] = NULL;
    }
}

void Player::Display(Item* container[], int capacity)
{
	for(int i=0; i < capacity; i++)
	{
		if(container[i] == NULL)
		{
			cout << i << " - <EMPTY>" <<endl;
		}
		else
		{
			cout <<i<<" - "<< container[i]->GetName() <<endl;
		}
	}

}
void Player::Info(int& item, Item* container[], int capacity)
{
	
	if(container[item] != NULL)
	{
		cout << container[item]->GetDescription() <<endl;
		return;
	}
	
	cout << "Sorry that Item does not exist." <<endl;
}

bool Player::isFull(Item* container[], int capacity)
{
	bool full = true;
    int i = 0;
    
    while (full && i<capacity)
    {
        //if there's at least one empty slot...
        if (container[i] == NULL)
        {
            //then the container isn't full
            full = false;
        }
        
        ++i;
    }

    return full;
}

void Player::Add(Item * pItem)
{
	 if (pItem == NULL)                                           
    {
        return;             
    }    

    if (isFull(inventory, INVENTORY_CAPACITY))
    {
        cout << "Inventory full. Can't add." << endl;
        return;
    }
     
    //find first null pointer in container, point it to string pItem points to
    bool found = false;
    int i = 0;
    
    while (!found && i<INVENTORY_CAPACITY)
    {       
        if (inventory[i] == NULL)
        {
            inventory[i] = pItem;         //add pointer 
                                          //to an item
            found = true;
        }
        
        ++i;
	}
}
void Player::RemoveUse(int& item, Item* container[],int capacity)
{
	//Special Remove for when the player uses something
	if(container[item] != NULL)
	{
		container[item] = NULL;          //remove pointer 
												//to an item
	}
	//if item wasn't found, say so
	else
	{
		cout << "Item not found. Can't remove." << endl;
	}
}

void Player::Remove(int& item,Item* container[], int capacity)
{
	char choice;
	cout << "If you drop this item, it will be forever lost in the darkness. Are you sure?"<<endl;
	cout <<"\t1 - Yes"<<endl;
	cout <<"\t2 - No"<<endl;
	do
	{
		cin >>choice;
	}while(choice != '1' && choice !='2');
	if(choice == 1)
	{
		if(container[item] != NULL)
		{
			container[item] = NULL;          //remove pointer 
												//to an item
		}
		//if item wasn't found, say so
		else
		{
			cout << "Item not found. Can't remove." << endl;
		}
	}
	else
	{
		cout << "Good choice"<<endl;
		return;
	}

}

bool Player::Use(int& itemNum, Item* container[], int capacity)
{
	char choice;
	if(container[itemNum] != NULL)
	{
		if(container[itemNum]->CanUse())	//If it can be used it is Equipped
		{
			if(equippedItem!=NULL)
			{
				if(equippedItem->GetName()=="Matches")
				{
					//Matches are important, dont want to take them away from the player if they dont want to
					cout<<"If you equip something else, you'll lose the matches"<<endl;
					cout<<"Are you sure?"<<endl;
					cout<<"\t1 - Yes"<<endl;
					cout<<"\t2 - No"<<endl;
					do{
						cin>>choice;
					}while(choice!='1'&&choice!='2');

					switch(choice)
					{
					case '1':
						SetEquippedItem(container[itemNum]);
						return true;
						break;
					case '2':
						return false;
						break;
					}
				}
			}
			else if(equippedItem == NULL)
			{
				SetEquippedItem(container[itemNum]);
				return true;
			}
		}
		else if(!container[itemNum]->CanUse())	//Else nothing happens
		{
			return false;
		}
	}
		cout << "Item cannot be found" <<endl;
		return false;
}

bool Player::Contains(string name, Item* container[], int capacity)
{
	for(int i=0;i<capacity;i++)
	{
		if(container[i]->GetName() == name)
		{
			return true;
		}
	}
	return false;
}

string Player::ReachOut(Cell*Room[20][20])
{
	char choice;
	switch(GetDirection())
	{
	case 1:	//Up
		Room[GetRow()-1][GetColumn()]->SetVisibility(true);		//Displays the cell's description and makes it visible
		Room[GetRow()-1][GetColumn()]->SetDiscovered(true);		//Marks the Cell as discovered
		if(Room[GetRow()-1][GetColumn()]->GetType()==7||Room[GetRow()-1][GetColumn()]->GetType()==8||Room[GetRow()-1][GetColumn()]->GetType()==9||Room[GetRow()-1][GetColumn()]->GetType()==12)	//If it is an item you can pick up it runs this code
		{
			cout <<"You reach forward and find "+Room[GetRow()-1][GetColumn()]->GetDescription()<<endl;
			cout <<"Would you like to pick it up?" <<endl;
			cout <<"1 - Yes"<<endl;
			cout <<"2 - No"<<endl;
			do
			{
				cin >> choice;
			}while(choice != '1' && choice!='2');
			switch(choice)
			{
			case '1':
				Add(static_cast<Item*>(Room[GetRow()-1][GetColumn()]->GetObject()));
				Room[GetRow()-1][GetColumn()]->Reset();
				break;
			case '2':
				cout<<"Alright, move along now" <<endl;
				break;
			}
			return "Item successfully added";
		}
		else
		{
			return ("You reach forward and find "+Room[GetRow()-1][GetColumn()]->GetDescription());
		}
			
		break;
	case 2:	//Down
		Room[GetRow()+1][GetColumn()]->SetVisibility(true);
		if(Room[GetRow()+1][GetColumn()]->GetType()==7||Room[GetRow()+1][GetColumn()]->GetType()==8||Room[GetRow()+1][GetColumn()]->GetType()==9||Room[GetRow()+1][GetColumn()]->GetType()==12)
		{
			cout << "You reach forward and find "+Room[GetRow()+1][GetColumn()]->GetDescription()<<endl;
			cout <<"Would you like to pick it up?" <<endl;
			cout <<"1 - Yes"<<endl;
			cout <<"2 - No"<<endl;
			do
			{
				cin >> choice;
			}while(choice != '1' && choice!='2');
			switch(choice)
			{
			case '1':
				Add(static_cast<Item*>(Room[GetRow()+1][GetColumn()]->GetObject()));
				Room[GetRow()+1][GetColumn()]->Reset();
				break;
			case '2':
				cout<<"Alright, move along now" <<endl;
				break;
			}
			return "Item successfully added";
		}
		else
		{
			return ("You reach forward and find "+Room[GetRow()+1][GetColumn()]->GetDescription());
		}
		break;
	case 3:	//Left
		Room[GetRow()][GetColumn()-1]->SetVisibility(true);
		if(Room[GetRow()][GetColumn()-1]->GetType()==7||Room[GetRow()][GetColumn()-1]->GetType()==8||Room[GetRow()][GetColumn()-1]->GetType()==9||Room[GetRow()][GetColumn()-1]->GetType()==12)
		{
			cout << "You reach forward and find "+Room[GetRow()][GetColumn()-1]->GetDescription()<<endl;
			
			cout <<"Would you like to pick it up?" <<endl;
			cout <<"1 - Yes"<<endl;
			cout <<"2 - No"<<endl;
			do
			{
				cin >> choice;
			}while(choice != '1' && choice!='2');
			switch(choice)
			{
			case '1':
				Add(static_cast<Item*>(Room[GetRow()][GetColumn()-1]->GetObject()));
				Room[GetRow()][GetColumn()-1]->Reset();
				break;
			case '2':
				cout<<"Alright, move along now" <<endl;
				break;
			}
			return "Item successfully added";
		}
		else
		{
			return("You reach forward and find "+Room[GetRow()][GetColumn()-1]->GetDescription());
		}
		break;
	case 4:	//Right
		Room[GetRow()][GetColumn()+1]->SetVisibility(true);
		if(Room[GetRow()][GetColumn()+1]->GetType()==7||Room[GetRow()][GetColumn()+1]->GetType()==8||Room[GetRow()][GetColumn()+1]->GetType()==9||Room[GetRow()][GetColumn()+1]->GetType()==12)
		{
			cout << "You reach forward and find "+Room[GetRow()][GetColumn()+1]->GetDescription()<<endl;
			cout <<"Would you like to pick it up?" <<endl;
			cout <<"1 - Yes"<<endl;
			cout <<"2 - No"<<endl;
			do
			{
				cin >> choice;
			}while(choice != '1' && choice!='2');
			switch(choice)
			{
			case '1':
				Add(static_cast<Item*>(Room[GetRow()][GetColumn()+1]->GetObject()));
				Room[GetRow()][GetColumn()+1]->Reset();
				break;
			case '2':
				cout<<"Alright, move along now" <<endl;
				break;
			}
			return "Item successfully added";
		}
		else
		{
			return("You reach forward and find "+Room[GetRow()][GetColumn()+1]->GetDescription());
		}
		break;
	}
	return "If you are reading this, run!!!";
}

Item* Player::GetEquippedItem() const
{
	return equippedItem;
}

void Player::SetEquippedItem(Item* itemToEquip)
{
	if(equippedItem!=NULL && equippedItem->GetName() == itemToEquip->GetName())
	{
		cout << "That item is already equipped" <<endl;
	}
	else if(itemToEquip->GetName() == "Armour"&& !m_ArmourEquipped)
	{
		m_ArmourEquipped = true;		//Body Armour is equipped
		cout << "You have equipped Body Armour" <<endl;
	}
	else if(itemToEquip->GetName() == "Med Kit")
	{
		const int HEAL = 20;
		if(!isMaxHealth())
		{
			int temp = GetHealth();
			SetHealth(GetHealth()+HEAL);	//Restores Health
			if(GetHealth() > MAX_HEALTH)
			{
				SetHealth(MAX_HEALTH);
			}
			cout << "You use a med kit restoring " << GetHealth()-temp << " points of damage." <<endl;
		}
		else
		{
			cout << "You are at full health" <<endl;
			Add(itemToEquip);	//Adds it back to the inventory
		}
	}
	else 
	{
		if(equippedItem== NULL)
		{
			equippedItem = itemToEquip;
		}
		else if(equippedItem != NULL)
		{
			Add(equippedItem);
			equippedItem = itemToEquip;
		}
	}
}

void Player::SetArmour(bool equipped)
{
	m_ArmourEquipped = equipped;
}

bool Player::GetArmourStatus() const
{
	return m_ArmourEquipped;	//Returns whether or not the player is wearing armour
}

void Player::Move(Player* playerMove,Cell* Room[20][20])
{
	Character::Move(playerMove,Room);	//Calls up the default move function from character

	EyeSight(playerMove,Room);
}

void Player::EyeSight(Player * pPlayer, Cell* Room[20][20])
{
	//Reveals the Cell in front of the player
	//Unless its a blank space or an enemy
	switch(GetDirection())
	{
	case 1:
		//Up
		if(Room[(pPlayer->GetRow()-1)][pPlayer->GetColumn()]->GetType() != 0&&Room[(pPlayer->GetRow()-1)][pPlayer->GetColumn()]->GetType() !=5)	//Up
		{
			Room[(pPlayer->GetRow()-1)][pPlayer->GetColumn()]->SetVisibility(true);
			Room[(pPlayer->GetRow()-1)][pPlayer->GetColumn()]->SetDiscovered(true);
		}
		break;
	case 2:
		//DOWN
		if(Room[pPlayer->GetRow()+1][pPlayer->GetColumn()]->GetType()!=0&&Room[pPlayer->GetRow()+1][pPlayer->GetColumn()]->GetType()!=5)	//Down
		{
			Room[pPlayer->GetRow()+1][pPlayer->GetColumn()]->SetVisibility(true);
			Room[pPlayer->GetRow()+1][pPlayer->GetColumn()]->SetDiscovered(true);
		}
		break;
	case 3:
		//LEFT
		if(Room[pPlayer->GetRow()][pPlayer->GetColumn()-1]->GetType()!=0&&Room[pPlayer->GetRow()][pPlayer->GetColumn()-1]->GetType()!=5)	//Left
		{
			Room[pPlayer->GetRow()][pPlayer->GetColumn()-1]->SetVisibility(true);
			Room[pPlayer->GetRow()][pPlayer->GetColumn()-1]->SetDiscovered(true);
		}
		break;
	case 4:
		//RIGHT
		if(Room[pPlayer->GetRow()][pPlayer->GetColumn()+1]->GetType() != 0&&Room[pPlayer->GetRow()][pPlayer->GetColumn()+1]->GetType() !=5)	//Right
		{
			Room[pPlayer->GetRow()][pPlayer->GetColumn()+1]->SetVisibility(true);
			Room[pPlayer->GetRow()][pPlayer->GetColumn()+1]->SetDiscovered(true);
		}
		break;
	}
}

bool Player::isMaxHealth() const
{
	//Checks to see if the player is at max health
	cout << MAX_HEALTH;
	if(GetHealth() == MAX_HEALTH)
	{
		return true;
	}
	else
	{
		return false;
	}
}