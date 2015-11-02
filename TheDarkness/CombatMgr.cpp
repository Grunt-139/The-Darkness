#include "CombatMgr.h"


CombatMgr::CombatMgr(void)
{
	m_inCombat = new bool(false);
}


CombatMgr::~CombatMgr(void)
{
	delete m_inCombat;
}

void CombatMgr::Combat(Player *pPlayer, Enemy * pEnemy,Cell*Room[20][20],vector<Enemy*> Enemies)
{
	*m_inCombat = true; //This bool says whether combat is going on or not, it is only made false IF the player flees
	int armour=0;
	do
	{
		Display(pPlayer,pEnemy,Room);
		if(!pEnemy->isDead())
		{
			m_Damage=EnemyTurn(pEnemy);
			cout << pEnemy->GetName() << " attacks and does " << m_Damage << " points of damage." <<endl;
			if(pPlayer->GetArmourStatus())
			{
				armour = ARMOUR_BLOCK+(rand()%ARMOUR_MOD);	//If the player has armour
				m_Damage -= armour;
				cout << "Your armour blocked " << armour << " points of damage" <<endl;
			}
			if(m_Damage <0)
			{
				m_Damage =0;	//Funny bug happens, if the armour blocks the damage the damage can go into the negative adding health (negative minus a negative makes a positive)
			}
			pPlayer->DamageHealth(m_Damage,Room);
			Sleep(500);
		}
		if(!pPlayer->isDead())
		{
			m_Damage =PlayerTurn(pPlayer,pEnemy,Room);
			cout << pPlayer->GetName() << " attacks and does " << m_Damage << " points of damage." <<endl;
			pEnemy->DamageHealth(m_Damage,Room);
			Sleep(500);
		}
		
	}while(!pPlayer->isDead() && !pEnemy->isDead() && *m_inCombat);
	*m_inCombat = false;
}

int CombatMgr::EnemyTurn(Enemy*pEnemy)
{
	vector<int> whichAttack;
	vector<int> hitMiss;
	for(int i=0; i <10; i++)
	{
		hitMiss.push_back(i);
	}
	for(int i=0; i <10; i++)
	{
		whichAttack.push_back(i);
	}
	random_shuffle(hitMiss.begin(),hitMiss.end());
	random_shuffle(whichAttack.begin(),whichAttack.end());

	if(whichAttack.front() < 3)
	{
		whichAttack.clear();
		hitMiss.clear();
		pEnemy->Heal();
		return 0;
	}
	if(hitMiss.front() > 4)
	{
		if(whichAttack.front() >= 12)
		{
			whichAttack.clear();
			hitMiss.clear();
			return pEnemy->BiteAttack();
		}
		else if(whichAttack.front() >= 5)
		{
			whichAttack.clear();
			hitMiss.clear();
			return pEnemy->Attack();
		}
	}
	else
	{
		whichAttack.clear();
		hitMiss.clear();
		return 0;	//Miss
	}

	whichAttack.clear();
	hitMiss.clear();
	return 0;

}

int CombatMgr::PlayerTurn(Player*pPlayer, Enemy* pEnemy,Cell * Room[20][20])
{
	string choice;
	int fleeDirection;
	int escapeChance;
	int armour;
	vector<int> hitMiss;
	
	for(int i=0; i <10; i++)
	{
		hitMiss.push_back(i);
	}
	random_shuffle(hitMiss.begin(),hitMiss.end());
	do
	{
	cout <<"What would you like to do?" <<endl;
	cout <<"\t1 - Attack" <<endl;
	cout <<"\t2 - Inventory"<<endl;
	cout <<"\t3 - Flee"<<endl;
	cout <<"Choice (number):";
	cin >>choice;

	switch(choice[0])
	{
	case '1':
		if(hitMiss.front() > 3)
		{
			if(pPlayer->GetEquippedItem() != NULL)
			{
				//YOU HIT
				
				switch(hitMiss.front())
				{
					//Just some code to give you a seemingly random comment about your attack
				case 6:
					cout <<"You swing and hear a satisfying crunch"<<endl;
					break;
				case 7:
					cout <<"You jab at your enemy with your"<<pPlayer->GetEquippedItem()->GetName()<<endl;
					break;
				case 8:
					cout <<"You bring your "<<pPlayer->GetEquippedItem()->GetName() <<" over your head for a powerful downward hit"<<endl;
					break;
				case 9:
					cout <<"Swing left, swing right and SMACK!!!"<<endl;
					break;
				case 10:
					cout << "KERPOW!!!!!!" <<endl;
					break;
				}
				hitMiss.clear();
				return (pPlayer->GetEquippedItem())->UseItem();
				
			}
			else
			{
				//Default attack if you have nothing equipped, so you're attacking with your bare hands
				//YOU HIT
				
				switch(hitMiss.front())
				{
					//Just some code to give you a seemingly random comment about your attack
				case 6:
					cout <<"You deliver the ol' One Two punch"<<endl;
					break;
				case 7:
					cout <<"You deliver a powerful jab followed by a right across"<<endl;
					break;
				case 8:
					cout <<"Jab, jab, punch you hit your enemy"<<endl;
					break;
				case 9:
					cout <<"You elbow your foe in the jaw"<<endl;
					break;
				case 10:
					cout << "You throw a left hook at your enemy. You hear a satisfying thud" <<endl;
					break;
				}
				hitMiss.clear();
				return (pPlayer->Attack());
			}
		}
		else
		{
			//YOU MISSED
			switch(hitMiss.front())
				{
					//Just some code to give you a seemingly random comment about your attack
				case 1:
					cout << "You miss your foe and strike thin air" <<endl;
					break;
				case 2:
					cout <<"Swing and a miss"<<endl;
					break;
				case 3:
					cout <<"You lose track of your foe in the darkness and miss"<<endl;
					break;
				case 4:
					cout <<"Your opponent dodges your attack"<<endl;
					break;
				case 5:
					cout <<"You swing blindly into the dark and connect with nothing"<<endl;
					break;
				}
			hitMiss.clear();
			return 0;
		}
		break;
	case '2':
		pPlayer->Inventory();		//Pulls up your inventory so you can use a health pack or equip something
		PlayerTurn(pPlayer,pEnemy,Room);
		break;
	case '3':
		escapeChance = 1+(rand()%10);	//Attempt to flee
		if(escapeChance > 5)
		{
			Flee(pPlayer,fleeDirection,Room);	//Flee unscathed
			cout << "You escape unscathed" <<endl;
		}
		else
		{
			m_Damage = EnemyTurn(pEnemy);		//Enemy gets a free attack in
			if(pPlayer->GetArmourStatus())
			{
				armour = ARMOUR_BLOCK+(rand()%ARMOUR_MOD);	//If the player has armour
			}
			Flee(pPlayer,fleeDirection,Room);
			cout << "Turning your back on your enemy he takes a swipe at you dealing "<< m_Damage <<" points of damage to you."<<endl;
		}
		hitMiss.clear();
		return 0;
	default:
		cout << "That is not a valid choice, please pick again" <<endl;
		break;
	}
	}while(choice != "1" || choice != "2" || choice != "3");
	hitMiss.clear();
	return 0;
}

void CombatMgr::Display(Player* pPlayer, Enemy* pEnemy, Cell* Room[20][20])
{

	//Prints out a small version of the map
	int startRow = pPlayer->GetRow() -1;
	int endRow = pPlayer->GetRow() +1;
	int startColumn = pPlayer->GetColumn() -1;
	int endColumn = pPlayer->GetColumn() +1;
	cout<<"*****Combat Map*****"<<endl;
	
	for(int i=startRow; i <=endRow; i++)
	{
		
		for(int j=startColumn; j <=endColumn;j++)
		{
			cout<<"*";
			if(Room[i][j]->GetType() == 4)//If the player is there
			{
				Room[i][j]->SetSymbol(pPlayer->GetSymbol());
			}
			else if(Room[i][j]->GetType()==5) //If an Enemy is there
			{
				Room[i][j]->SetSymbol(pEnemy->GetSymbol());

			}	
			cout << Room[i][j]->GetSymbol();
		}
		cout <<"*"<<endl;
	}
	cout<<"********************"<<endl;

	//Prints out the health and such
	cout <<"*****************************"<<endl;
	cout <<pPlayer->GetName() <<" 's hitpoints: "<< pPlayer->GetHealth() <<endl;
	cout<<pEnemy->GetName() << " 's hitpoints: "<< pEnemy->GetHealth() <<endl;
	cout <<"*****************************"<<endl;
}

bool CombatMgr::isCombat(Cell* Room[20][20], Player * pPlayer,vector<Enemy*> Enemies)
{
	int fleeDirection=0;
	vector<Enemy*>::iterator EnemyIter;
	for(EnemyIter = Enemies.begin(); EnemyIter <Enemies.end();EnemyIter++)
	{
		if(*EnemyIter !=NULL)
		{
			//UP
			if(pPlayer->GetRow()-1 == (*EnemyIter)->GetRow() && pPlayer->GetColumn() == (*EnemyIter)->GetColumn())	//Up
			{
				if((*EnemyIter)->isLightSensitive() && Room[(*EnemyIter)->GetRow()][(*EnemyIter)->GetColumn()]->GetVisible())
				{
					return Ambush(pPlayer,EnemyIter,fleeDirection,Room,Enemies);	//Handles the code for the player fleeing/Fighting
				}
				else
				{
					Combat(pPlayer,*EnemyIter,Room,Enemies);		//If the player CANNOT see the enemy then the enemy just attacks
					return true;
				}
			}
			//DOWN
			else if(pPlayer->GetRow()+1 == (*EnemyIter)->GetRow() && pPlayer->GetColumn() == (*EnemyIter)->GetColumn())	//Down
			{
				if((*EnemyIter)->isLightSensitive()&&Room[(*EnemyIter)->GetRow()][(*EnemyIter)->GetColumn()]->GetVisible())
				{
					return Ambush(pPlayer,EnemyIter,fleeDirection,Room,Enemies);
				}
				else
				{
					Combat(pPlayer,*EnemyIter,Room,Enemies);
					return true;
				}
			}
			//LEFT
			else if(pPlayer->GetRow() == (*EnemyIter)->GetRow() && pPlayer->GetColumn()-1 == (*EnemyIter)->GetColumn())	//Left
			{
				if((*EnemyIter)->isLightSensitive()&&Room[(*EnemyIter)->GetRow()][(*EnemyIter)->GetColumn()]->GetVisible())
				{
					return Ambush(pPlayer,EnemyIter,fleeDirection,Room,Enemies);
				}
				else
				{
					Combat(pPlayer,*EnemyIter,Room,Enemies);
					return true;
				}
			}
			//RIGHT
			else if(pPlayer->GetRow() == (*EnemyIter)->GetRow() && pPlayer->GetColumn()+1 == (*EnemyIter)->GetColumn())	//Right
			{
				if((*EnemyIter)->isLightSensitive()&&Room[(*EnemyIter)->GetRow()][(*EnemyIter)->GetColumn()]->GetVisible())
				{
					return Ambush(pPlayer,EnemyIter,fleeDirection,Room,Enemies);
				}
				else
				{
					Combat(pPlayer,*EnemyIter,Room,Enemies);
					return true;
				}
			}
		}
	}
	return false;
}
bool CombatMgr::Ambush(Player * pPlayer, vector<Enemy*>::iterator EnemyIter, int&fleeDirection, Cell*Room[20][20], vector<Enemy*>Enemies)
{
	Enemy * pEnemy= *EnemyIter;
	//If the Enemy is lightsensitive and is currently in the light the player can either attack them or flee
	string choice;
	cout <<"You have the drop on him. Would you like to:" <<endl;
	cout<<"\t1 - Flee"<<endl;
	cout<<"\t2 - Attack while its weak" <<endl;
	do
	{
		cin >> choice;
	}while(choice != "1" && choice !="2");
	switch(choice[0])
	{
	case '1':
		Flee(pPlayer,fleeDirection,Room);	//Player is given the choice of what direction they run in
		pPlayer->Move(pPlayer,Room);	//They Run
		return false;
		break;
	case '2':
		(*EnemyIter)->SetHealth((*EnemyIter)->GetMaxHealth() *0.5);
		m_Damage = PlayerTurn(pPlayer,pEnemy,Room);	//Player gets a free attack
		cout << pPlayer->GetName() << " attacks and does " << m_Damage << " points of damage." <<endl;
		pEnemy->DamageHealth(m_Damage,Room);
		Combat(pPlayer,pEnemy,Room,Enemies);	//Combat carries on
		return true;
		break;
	default:
		cout << "That is an invalid choice" <<endl;
		break;
	}
}
void CombatMgr::OnEdge(Cell* Room[20][20], Player * pPlayer,vector<Enemy*> Enemies)
{
	int distance=0;
	vector<Enemy*>::iterator EnemyIter;
	//Checks the players Row and Column for an enemy
	for(EnemyIter = Enemies.begin(); EnemyIter < Enemies.end(); EnemyIter++)	//Rows
	{
		if(*EnemyIter != NULL)
		{
			if(pPlayer->GetRow()==(*EnemyIter)->GetRow())	//In the same row
			{
				if(pPlayer->GetColumn() > (*EnemyIter)->GetColumn())
				{
					distance = pPlayer->GetColumn() - (*EnemyIter)->GetColumn();	//Finds difference between the column locations
				}
				else if(pPlayer->GetColumn() < (*EnemyIter)->GetColumn())
				{
					distance = (*EnemyIter)->GetColumn() - pPlayer->GetColumn();	//Finds difference between the column locations
				}
			}
		}
	}
	
	for(EnemyIter = Enemies.begin(); EnemyIter < Enemies.end(); EnemyIter++)		//Columns
	{
		if(*EnemyIter != NULL)
		{
			if(pPlayer->GetColumn()==(*EnemyIter)->GetColumn())	//In the same column
			{
				if(pPlayer->GetRow() > (*EnemyIter)->GetRow())		
				{
					distance = pPlayer->GetRow() - (*EnemyIter)->GetRow();	//Finds difference between the Row locations
				}
				else if(pPlayer->GetRow() < (*EnemyIter)->GetRow())
				{
					distance = (*EnemyIter)->GetRow() - pPlayer->GetRow();	//Finds difference between the Row locations
				}
			}
		}
	}
	if(distance==0)
	{
		return;
	}
	else if(distance >5 && distance <8)
	{
		cout << "You hear shuttering in the distance." <<endl;
	}

	else if(distance < 5 && distance > 2)
	{
		cout <<"You feel the hair on the back of your neck stand up."<<endl;
	}
	else if(distance <=2 && distance >0)
	{
		cout <<"A breeze passes by."<<endl;
	}
}

void CombatMgr::Flee(Player*pPlayer, int& direction, Cell*Room[20][20])
{
	*m_inCombat = false;
	string directionString;
	cout << "What direction?" <<endl;
	cout << "0 - Forward" <<endl;
	cout << "1 - Left" <<endl;
	cout << "2 - Right" <<endl;
	cout << "3 - Behind" <<endl;
	do
	{
		cin >> directionString;
	}while(directionString!="0" && directionString != "1" && directionString !="2" && directionString !="3");
	if(directionString != "0")
	{
		switch(directionString[0])
		{
		case '1':
			direction = 1;
			pPlayer->SetDirection(direction,Room);
			break;
		case '2':
			direction = 2;
			pPlayer->SetDirection(direction,Room);
			break;
		case '3':
			direction = 3;
			pPlayer->SetDirection(direction,Room);
			break;
		}
		//After getting their direction they move and run off
		pPlayer->Move(pPlayer, Room);
	}
	else
	{
		pPlayer->Move(pPlayer,Room);
	}
}