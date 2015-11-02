#include "Enemy.h"


Enemy::Enemy(string name, string left, string right, string up, string down, int startDirection, int health, int playerRow,int playerColumn, bool lightSensitive):Character(name,left,right,up,down,startDirection, health, playerRow, playerColumn),m_LightSensitivity(lightSensitive),m_MaxHealth(health)
{}


Enemy::~Enemy(void)
{}


void Enemy::Reset()
{
	SetPosition(0,0);
	SetHealth(m_MaxHealth);
}

int Enemy::GetMaxHealth() const
{
	return m_MaxHealth;
}


int Enemy::Attack()
{
	cout << GetName() << " claws at you!!" <<endl;
	return (CLAW_DAMAGE+(rand()%MODIFIER));
}

int Enemy::BiteAttack()
{
	cout << GetName() << " sinks its teeth into you!!" <<endl;
	return(CLAW_DAMAGE+(rand()%MODIFIER));
}

void Enemy::Heal()
{
	cout << GetName() << " heals itself!!";
	int temp = GetHealth();
	if(GetHealth()+HEAL > GetMaxHealth())
	{
		SetHealth(GetMaxHealth());
	}
	else
	{
		SetHealth(GetHealth()+HEAL);
	}
	cout <<"Restoring " <<GetHealth()-temp << " points of health" <<endl;
}

void Enemy::whereIsPlayer(Cell*Room[20][20], Player* pPlayer)
{
	//Directions
	//1 - Up
	//2 - Down
	//3 - Left
	//4 - Right
	
	if(pPlayer->GetColumn() == GetColumn())
	{
		if(GetRow() > pPlayer->GetRow()&&(GetRow()-pPlayer->GetRow() < 4))	//If the player is 3 or less squares away they will move to intercept
		{
			ChangeDirection(1);	//Face Up towards player
		}
		else if(GetRow() < pPlayer->GetRow() && (pPlayer->GetRow() - GetRow() <4))
		{
			ChangeDirection(2);	//Face Down towards player
		}
	}	

	if(pPlayer->GetRow() == GetRow())
	{
		if(GetColumn() > pPlayer->GetColumn()&&(GetColumn()-pPlayer->GetColumn() < 4))	//If the player is 3 or less squares away they will move to intercept
		{
			ChangeDirection(3);	//Face Left towards player
		}
		else if(GetColumn() < pPlayer->GetColumn() && (pPlayer->GetColumn() - GetColumn() <4))
		{
			ChangeDirection(4);	//Face Right towars player
		}
	} 


}
void Enemy::wallDetector(Enemy*playerMove, Cell*Room[20][20])
{
	//Up
	if(Room[(playerMove->GetRow()-1)][playerMove->GetColumn()]->GetType() == 0)	//Up
	{
			
	}
	//DOWN
	else if(Room[playerMove->GetRow()+1][playerMove->GetColumn()]->GetType()==0)	//Down
	{
			
	}
	//LEFT
	else if(Room[playerMove->GetRow()][playerMove->GetColumn()-1]->GetType()==0)	//Left
	{
		
	}
	//RIGHT
	else if(Room[playerMove->GetRow()][playerMove->GetColumn()+1]->GetType() == 0)	//Right
	{
			
	}
}
void Enemy::Move(Enemy* playerMove, Cell * Room[20][20], int timesAttempted)
{
	int tempType = Room[GetRow()][GetColumn()]->GetType();
	if(!playerMove->isDead())
	{
		switch(playerMove->GetDirection())
		{
		case 1:	//Up
			if(Room[GetRow()-1][GetColumn()]->isEmpty())
			{
				Room[GetRow()][GetColumn()]->Reset();
				Room[GetRow()-1][GetColumn()]->SetType(tempType);
				Room[GetRow()-1][GetColumn()]->SetEmpty();
				Room[GetRow()-1][GetColumn()]->SetObject(playerMove);	//Sets it so the Cell is now pointing to the enemy
				SetPosition(GetRow()-1,GetColumn());
			}
			else
			{
				//changes direction to Right
				ChangeDirection(4);//Direction goes to relative right and it attempts to move
				if(timesAttempted <4)
				{
					Move(playerMove,Room,++timesAttempted);
				}
			}
			break;
		case 2:	//Down
			if(Room[GetRow()+1][GetColumn()]->isEmpty())
			{
				Room[GetRow()][GetColumn()]->Reset();
				Room[GetRow()+1][GetColumn()]->SetType(tempType);
				Room[GetRow()+1][GetColumn()]->SetEmpty();
				Room[GetRow()+1][GetColumn()]->SetObject(playerMove);	//Sets it so the Cell is now pointing to the enemy
				SetPosition(GetRow()+1, GetColumn());
			}
			else
			{
				//changes direction to left
				ChangeDirection(3);//Changes direction to the relative right and attempts to move
				if(timesAttempted <4)
				{
					Move(playerMove,Room,++timesAttempted);
				}
			}
			break;
			case 3:	//Left
			if(Room[GetRow()][GetColumn()-1]->isEmpty())
			{
				Room[GetRow()][GetColumn()]->Reset();
				Room[GetRow()][GetColumn()-1]->SetType(tempType);
				Room[GetRow()][GetColumn()-1]->SetEmpty();
				Room[GetRow()][GetColumn()-1]->SetObject(playerMove);	//Sets it so the Cell is now pointing to the enemy
				SetPosition(GetRow(),GetColumn()-1);
			}
			else
			{
				//Changes direction to Up
				ChangeDirection(1);//Changes direction to the relative right and attempts to move
				if(timesAttempted <4)
				{
					Move(playerMove,Room,++timesAttempted);
				}
			}
			break;
		case 4:	//Right
			if(Room[GetRow()][GetColumn()+1]->isEmpty())
			{
				Room[GetRow()][GetColumn()]->Reset();
				Room[GetRow()][GetColumn()+1]->SetType(tempType);
				Room[GetRow()][GetColumn()+1]->SetEmpty();
				Room[GetRow()][GetColumn()+1]->SetObject(playerMove);	//Sets it so the Cell is now pointing to the enemy
				SetPosition(GetRow(),GetColumn()+1);
			}
			else
			{
				//Changed direction to Down
				ChangeDirection(2);//Changes direction to the relative right and attempts to move
				if(timesAttempted <4)
				{
					Move(playerMove,Room,++timesAttempted);
				}
			}
			break;
		}
	}
}

bool Enemy::isLightSensitive() const
{
	return m_LightSensitivity;
}