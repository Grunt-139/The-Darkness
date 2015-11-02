#include "Game.h"

Game::Game(void)
{
	m_CombatMgr = new CombatMgr;
	m_lightsOn = new bool(false);
	m_GameMessage = new string("");
	m_GameEventHandler = new GameEventManager(0,0);
}

Game::~Game()
{
	Clear();
}
void Game::Clear()
{
	//Delete Room 1
	for(int i=0; i < ROWS; ++i)
	{
		for(int j=0; j<COLUMNS; ++j)
		{
			delete m_Room[i][j];
			m_Room[i][j] = NULL;
		}
	}

	for(m_EnemyIter=Enemies.begin(); m_EnemyIter < Enemies.end(); m_EnemyIter++)
	{
		delete *m_EnemyIter;
	}
	
	for(m_ItemIter=Items.begin(); m_ItemIter < Items.end(); m_ItemIter++)
	{
		delete *m_ItemIter;
	}

	delete m_pPlayer;
	m_pPlayer = NULL;

	delete m_CombatMgr;
	m_CombatMgr = NULL;

	delete m_lightsOn;
	m_lightsOn = NULL;

	delete m_GameEventHandler;
	m_GameEventHandler = NULL;
}


void Game::Reset()
{
	//First things first, wipe out the current room, enemies, and items
	for(int i=0; i < ROWS; ++i)
	{
		for(int j=0; j<COLUMNS; ++j)
		{
			m_Room[i][j] = NULL;
			delete m_Room[i][j];
		}
	}
	
	

	for(m_EnemyIter=Enemies.begin(); m_EnemyIter < Enemies.end(); m_EnemyIter++)
	{
		delete *m_EnemyIter;
	}
	
	for(m_ItemIter=Items.begin(); m_ItemIter < Items.end(); m_ItemIter++)
	{
		delete *m_ItemIter;
	}

	Enemies.clear();//Clears Enemy Vector
	Items.clear();//Clears Item Vector

	delete m_pPlayer;
	m_pPlayer = NULL;

	m_GameEventHandler->Reset();
}


void Game::RoomLoad(int load)
{

	m_currentRoom = load;		//The current room that you are in

	//Legend							Directions
	//0 - Blank "   "					1 - Up
	//1 - Wall	|						2 - Down
	//2 - Bottom ---					3 - Left
	//3 - Inside Wall " | "				4 - Right
	//4 - Player
	//5 - Enemy
	//6 - Outside bottom ---
	//7 - Item * Matches
	//8 - Item * Armour
	//9 - Item * Med Kit
	//10 - ! Game Event
	//11 - Eye Candy
	//12 - Weapon
	//13 - Exit
	/*BLANK TEMPLATE			{{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
							    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
								{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}};*/
	
	unsigned int type[ROWS][COLUMNS];
	///FLOOR NUMBER 1
	unsigned int floor1[ROWS][COLUMNS] =  {{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
										{1,0,0,0,12,0,0,0,0,0,3,11,0,3,11,0,3,9,0,1},
										{1,0,0,0,0,0,0,0,0,0,3,0,5,3,0,0,3,5,0,1},
										{1,0,0,0,0,0,0,0,0,0,3,0,2,2,2,0,2,0,2,1},
										{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
										{1,2,2,2,2,2,2,2,0,0,0,5,0,2,2,2,2,2,2,1},
										{1,7,3,0,11,10,11,3,0,0,0,0,0,3,0,0,0,0,0,1},
										{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,1},
										{1,2,3,0,0,0,0,3,0,0,0,0,0,3,0,0,0,0,0,1},
										{1,0,0,0,0,0,0,3,0,0,0,0,0,3,0,0,0,0,0,1},
										{1,11,0,0,0,0,0,3,0,0,11,0,0,3,0,0,0,0,0,1},
										{1,11,0,0,0,0,0,3,0,11,11,11,0,3,0,0,0,0,0,1},
										{1,11,0,0,0,0,0,3,0,12,11,0,0,0,0,0,0,0,0,1},
										{1,0,0,0,0,0,0,3,0,0,5,0,0,3,2,2,2,2,2,1},
										{1,2,2,2,2,0,2,2,0,0,0,0,0,0,0,0,0,0,0,1},
										{1,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,1},
										{1,9,0,3,0,0,11,3,0,5,0,0,0,0,0,0,0,0,0,1},
										{1,2,2,2,0,0,11,3,0,3,2,0,2,0,0,0,3,0,2,1},
										{1,0,0,0,4,0,11,3,0,3,0,0,3,0,0,0,3,0,13,1},
										{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6}};
	//FLOOR NUMBER 2
	unsigned int floor2[ROWS][COLUMNS] ={{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
										{1,0,0,0,0,0,0,0,11,10,11,0,0,0,0,0,0,0,0,1},
										{1,0,0,5,0,0,0,0,11,0,11,0,0,0,0,0,0,0,0,1},
										{1,13,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,1},
										{1,0,0,0,0,0,0,3,0,2,2,3,0,0,0,0,0,0,0,1},
										{1,0,0,0,0,0,0,3,0,0,0,3,0,0,0,0,0,0,0,1},
										{1,2,2,2,0,0,0,3,2,2,0,2,0,0,0,0,2,2,2,1},
										{1,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,9,1},
										{1,8,0,3,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,1},
										{1,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,1},
										{1,0,0,0,0,0,0,0,0,0,11,0,0,0,0,3,0,0,0,1},
										{1,5,0,0,0,0,0,0,0,11,11,11,0,0,0,0,0,0,0,1},
										{1,0,0,3,11,9,0,0,0,0,11,0,0,0,0,3,7,0,0,1},
										{1,0,0,3,11,11,0,0,3,0,0,0,3,0,0,3,2,2,2,1},
										{1,0,0,3,2,2,2,0,3,0,11,0,3,0,0,0,0,0,0,1},
										{1,0,0,0,0,0,0,0,3,7,0,0,3,0,0,0,2,2,2,1},
										{1,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,3,8,0,1},
										{1,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,1},
										{1,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,3,0,0,1},
										{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6}};
	//FLOOR NUMBER 3
	unsigned int floor3[ROWS][COLUMNS] ={{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6},
										{1,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,1},
										{1,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
										{1,0,0,0,0,0,0,0,0,0,5,0,0,0,3,9,0,0,0,1},
										{1,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,0,2,2,1},
										{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,8,1},
										{1,0,0,0,0,0,0,3,2,2,2,2,2,2,0,3,2,2,2,1},
										{1,0,0,5,0,0,0,3,0,0,4,0,0,3,0,0,0,0,0,1},
										{1,2,2,3,0,0,0,3,11,0,0,0,0,3,0,0,11,0,0,1},
										{1,12,0,0,0,0,0,3,11,0,0,0,0,0,0,0,11,0,1},
										{1,0,0,3,0,0,0,3,0,11,10,11,0,3,0,0,0,0,0,1},
										{1,0,0,3,0,0,0,2,2,2,2,2,2,2,0,0,0,0,0,1},
										{1,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
										{1,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,5,0,1},
										{1,2,2,2,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,1},
										{1,8,0,3,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,1},
										{1,0,0,3,0,0,5,0,0,3,0,0,0,0,3,0,0,5,0,1},
										{1,7,0,0,0,0,0,0,0,3,0,0,0,0,3,0,0,0,0,1},
										{1,2,2,3,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,1},
										{6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6}};


	switch(load)
	{
	case 0:
		//FLOOR 1 LOAD
		for(int i=0; i < ROWS;i++)
		{
			for(int j=0; j < COLUMNS;j++)
			{
				type[i][j]=floor1[i][j];
			}
		}
		m_nextRoom = 1;
		break;
	case 1:
		for(int i=0; i < ROWS;i++)
		{
			for(int j=0; j < COLUMNS;j++)
			{
				type[i][j]=floor2[i][j];
			}
		}
		m_nextRoom = 2;
		break;
	case 2:
		for(int i=0; i < ROWS;i++)
		{
			for(int j=0; j < COLUMNS;j++)
			{
				type[i][j]=floor3[i][j];
			}
		}
		break;
	}
	PopulateRoom(type);
}

void Game::PopulateRoom(unsigned int type[ROWS][COLUMNS])
{
	//Legend							Directions
	//0 - Blank "   "					1 - Up
	//1 - Wall	|						2 - Down
	//2 - Bottom ---					3 - Left
	//3 - Inside Wall " | "				4 - Right
	//4 - Player
	//5 - Enemy
	//6 - Outside bottom ---
	//7 - Item * Matches
	//8 - Item * Armour
	//9 - Item * Med Kit
	//10 - ! Game Event
	//11 - Eye Candy
	//12 - Weapon
	for(int i=0; i < ROWS; ++i)
	{
		for(int j=0; j<COLUMNS; ++j)
		{
			if(type[i][j] == 4)			//Player Spawn
			{
				m_pPlayer->SetPosition(i,j);
				m_Room[i][j] = new Cell(4,"A player is here...are you touching yourself?",m_pPlayer);
				m_Room[i][j]->SetSymbol(m_pPlayer->GetSymbol());
			}
			else if (type[i][j] ==5)			//Enemy Spawn
			{
				Enemies.push_back(new Enemy("Nightstalker"," N "," N "," N "," N ",1,50,i,j));
				m_Room[i][j] = new Cell(5,"An enemy",Enemies.back());
				m_Room[i][j]->SetSymbol(Enemies.back()->GetSymbol());
			}
			else if (type[i][j] ==7)			//Matches Spawn
			{
				Items.push_back(new Matches());
				m_Room[i][j] = new Cell(7,Items.back()->GetDescription(),Items.back());
			}
			else if (type[i][j] ==8)			//Armour Spawn
			{
				Items.push_back(new Armour());
				m_Room[i][j] = new Cell(8,Items.back()->GetDescription(),Items.back());
			}
			else if (type[i][j] ==9)			//MedKit Spawn
			{
				Items.push_back(new MedKit());
				m_Room[i][j] = new Cell(9,Items.back()->GetDescription(),Items.back());
			}
			else if (type[i][j] ==10)			//Game Event Spawn
			{
				m_GameEventHandler->SetPosition(i,j);
				m_Room[i][j] = new Cell(10,"Game Event",m_GameEventHandler);
			}
			else if (type[i][j] ==11)			//EyeCandy Spawn
			{
				m_Room[i][j] = new Cell(11,"Eye Candy",NULL);
			}	
			else if(type[i][j] == 12)		//Weapon Spawn
			{
				Items.push_back(new Weapon());
				m_Room[i][j] = new Cell(12,Items.back()->GetDescription(),Items.back());
			}
			else
			{
				m_Room[i][j] = new Cell(type[i][j]);	//If it is not a enemy or player then it just builds a new one and its awesome
			}
		}
	}
}


void Game::MainMenu()
{
	string choice;
do
{
	system("CLS");
	cout<<"\t\t______  ___  ______ _   __ _   _  _____ _____ _____ "<<endl;
	cout<<"\t\t|  _  \\/ _ \\ | ___ \\ | / /| \\ | ||  ___/  ___/  ___|"<<endl;
	cout<<"\t\t| | | / /_\\ \\| |_/ / |/ / |  \\| || |__ \\ `--.\\ `--. "<<endl;
	cout<<"\t\t| | | |  _  ||    /|    \\ | . ` ||  __| `--. \\`--. \\"<<endl;
	cout<<"\t\t| |/ /| | | || |\\ \\| |\\  \\| |\\  || |___/\\__/ /\\__/ /"<<endl;
	cout<<"\t\t|___/ \\_| |_/\\_| \\_\\_| \\_/\\_| \\_/\\____/\\____/\\____/ "<<endl;
	
	
		cout <<"\n\n\n\t\t\t\t 1 - Play"<<endl;
		cout <<"\t\t\t\t 2 - Instructions" <<endl;
		cout <<"\t\t\t\t 3 - Quit"<<endl;
		cout <<"\t\t\t\t Choice: ";
		cin>> choice;

		switch(choice[0])
		{
		case '1':
			Play();
			break;
		case '2':
			Instructions();
			break;
		case '3':
			return;
		default:
			cout <<"\nSorry that is not a valid choice. Only 1,2, and 3 are valid inputs." <<endl;
			break;
		}
}while(choice != "1" || choice !="2" || choice !="3");
}


void Game::Play()
{

	m_pPlayer = new Player("???????"," < "," > "," ^ "," v ", 1,40,0,0);	//Load Player
	SetPlayerName();	//Sets the players name
	*m_lightsOn = false;

	RoomLoad(0);		//Loads first room

	m_GameEventHandler->PlayEvent(m_pPlayer,m_Room);	//Plays the first event to kick the game off
	vector<int>LightsOnLightsOff;
	for(int i=0; i < 4;i++)
	{
		LightsOnLightsOff.push_back(i);		//Load up a vector to get a random number
	}

	string choice;
	string direction;
	int directionInt;
	int iHealth;	//Integer to store the players health
	string health;	//string to put it all together
	char buffer[10];//Buffer to change the health from an int to a string
	do
	{

		do
		{
			random_shuffle(LightsOnLightsOff.begin(),LightsOnLightsOff.end());
			//Randomly will turn on the lights later in the game
			if(m_currentRoom ==2 && LightsOnLightsOff.front() > 2)
			{
				SetLightsOn(true);
			}
			else if(m_currentRoom==2 && LightsOnLightsOff.front() < 2)
			{
				SetLightsOn(false);
			}

			if(IsThereAnEvent())		//Checks to see if there is an event near the player and plays that event
			{
				m_GameEventHandler->PlayEvent(m_pPlayer,m_Room);
			}

			//Special Event at the end of ROOM 2
			if(m_GameEventHandler->isRoomClear(1))
			{
				SetLightsOn(true);
			}

			if(*m_lightsOn)
			{
				SetLightsOn(true);
			}

			DisplayRoom();
			PlayBeep();
			m_CombatMgr->OnEdge(m_Room,m_pPlayer,Enemies);
			Door();	//Is there a door by the player
			cout <<GetGameMessage()<<endl;
			SetGameMessage("");
			cout << "Commands:" <<endl;
			cout << "\t 0 - Main Menu" <<endl;
			cout << "\t 1 - Wait" <<endl;
			cout << "\t 2 - Change Direction" <<endl;
			cout << "\t 3 - Move" <<endl;
			cout << "\t 4 - Inventory" <<endl;
			cout << "\t 5 - Reach Out" <<endl;
			cout << "\t 6 - Show Health" <<endl;
			cin >> choice;
			switch(choice[0])
			{
			case '0':
				Reset();
				return;
			case '1':
				EnemyTurn(Enemies);	//Enemies Turn
				DisplayRoom();
				break;
			case '2':
				cout << "What direction?" <<endl;
				cout << "1 - Left" <<endl;
				cout << "2 - Right" <<endl;
				cout << "3 - Behind" <<endl;
				do
				{
					cin >> direction;
				}while(direction != "1" && direction !="2" && direction !="3");
				switch(direction[0])
				{
				case '1':
					directionInt = 1;
					m_pPlayer->SetDirection(directionInt,m_Room);
					break;
				case '2':
					directionInt = 2;
					m_pPlayer->SetDirection(directionInt,m_Room);
					break;
				case '3':
					directionInt = 3;
					m_pPlayer->SetDirection(directionInt,m_Room);
					break;
				}
				break;
			case '3':
				m_pPlayer->Move(m_pPlayer, m_Room);
				EnemyTurn(Enemies);	//Enemies Turn
				break;
			case '4':
				m_pPlayer->Inventory();
				break;
			case '5':
				SetGameMessage(m_pPlayer->ReachOut(m_Room));
				break;
			case '6':
				iHealth = m_pPlayer->GetHealth();
				itoa(iHealth,buffer,10);
				health = "Health: ";
				health+=buffer;
				SetGameMessage(health);
				break;
			case '1337':
				*m_lightsOn = true;
				SetGameMessage("And lights on!!");
				break;
			default:
				SetGameMessage("Sorry not a valid choice");
				break;
			}
		}while(!m_CombatMgr->isCombat(m_Room,m_pPlayer,Enemies)&&!m_GameEventHandler->GetGameOver());

	}while(choice!="0" && !m_pPlayer->isDead() &&!m_GameEventHandler->GetGameOver());
	
	if(m_pPlayer->isDead())
	{
		cout << "You have died" <<endl;
		Sleep(5000);
	}
	else
	{
		m_GameEventHandler->Reset();
		Reset();
		cout <<"Thanks for playing, do play again"<<endl;
	}

}

void Game::SetPlayerName()
{
	string name;
	cout << "Welcome, what is your name? ";
	cin >> name;
	m_pPlayer->SetName(name);
	cout <<"\nWelcome " << m_pPlayer->GetName() <<endl;
}

void Game::SetGameMessage(string message)
{
	*m_GameMessage = message;
}

string Game::GetGameMessage() const
{
	return *m_GameMessage;
}

void Game::Instructions()
{
	//Display Instructions
	char done;
	
		system("CLS");
		cout <<"***************"<<endl;
		cout << "How to Play" <<endl;
		cout <<"***************"<<endl;

		cout << "\nNavigation" <<endl;
		cout << "*************" <<endl;
		cout <<"\tYou are trapped in a building, in complete darkness." <<endl;
		cout << "\tTo navigate you must use the strange sonar device on your chest, "<<endl; 
		cout << "\tand by waving your hands in front of you."<<endl;
		cout <<	"\tThe more you discover, the more of the map will be visible."<<endl;
		cout <<"\tCertain items may enlighten your path as well."<<endl;
		cout<<endl;

		cout << "\nDisplay" <<endl;
		cout <<"***************"<<endl;
		cout <<"Here is your Hud"<<endl;
		cout <<"Distance: X m	(Distance in meters from the player to some object)" <<endl;
		cout << "Commands:" <<endl;
		cout << "\t0 - Main Menu	(Takes you back to main menu)" <<endl;
		cout << "\t1 - Wait			(You do nothing)" <<endl;
		cout << "\t2 - Change Direction	(Changes your direction, Left, Right, Behind" <<endl;
		cout << "\t3 - Move		(Moves in your current direction 1 square)" <<endl;
		cout << "\t4 - Inventory	(Shows your inventory)" <<endl;
		cout << "\t5 - Reach Out	(Reveals what is in front of you)" <<endl;
		cout << "\t6 - Get Health		(Your name and your current health)" <<endl;
		cout <<	"To make a choice you enter the number you want." <<endl;
		cout << endl;
		
		cout << "\nMap Legend" <<endl;
		cout <<"***************"<<endl;
		cout << "^,v,>,< - Player(You)" <<endl;
		cout << "N - NightStalker"<<endl;
		cout << "|,__,---  - Walls"<<endl;
		cout << "x -Objects" <<endl;
		cout << "! - Game Event" <<endl;
		cout << "* - Item" <<endl;
		cout <<endl;
		
		cout << endl;
	do
	{
		cout << "Would you like to return to the main menu? (y/n): ";
		cin >> done;
	}while(done != 'y' && done!= 'Y');



}

void Game::PlayBeep()
{
	int a = m_pPlayer->GetRow();
	int b =m_pPlayer->GetColumn();
	int count = 0;
	count =GetCount(a,b,count);	//Count(which is 0) and the Room are both passed in.

	Beep(640,500);		//This is the default beep
	Sleep(count*150);	//Waits for the count, which is the distance between the player and the object measured in Cells

	if(m_Room[a][b]->GetType() == 5)
	{
		Beep(ALIVE,500);	//If it is an enemy(therefore alive) plays this sound a High pitched one
	}
	else
	{
		Beep(N_ALIVE, 500);	//If it is not living, it plays this lower sound
	}
	cout <<"Distance: "<< count << " m"<<endl;
}

int Game::GetCount(int& a,int& b, int counter)
{
	switch(m_pPlayer->GetDirection())	//Gets the players direction
	{
		//Moves through the Room array along the column or row the player is in.
	case 1:	//Up
		a--;
		while(a > 0 && m_Room[a][b]->isEmpty() )
		{
			a--;
			counter ++;
		};
		break;
	case 2:	//Down
		a++;
		while(a<ROWS && m_Room[a][b]->isEmpty())
		{
			a++;
			counter ++;
		};
		break;
	case 3:	//Left
		b--;
		while( b >0 && m_Room[a][b]->isEmpty())
		{
			b--;
			counter ++;
		};
		break;
	case 4:	//Right
		b++;
		while(b < COLUMNS && m_Room[a][b]->isEmpty())
		{
			b++;
			counter ++;
		};
		break;
	}
	//A little error checking so 'a' and 'b' wont be returned as a number outside of the array's bounds
	if(b == COLUMNS)
	{
		b = COLUMNS-1;
	}
	else if(b < 0)
	{
		b =0;
	}
	else if(a ==ROWS)
	{
		a = ROWS-1;
	}
	else if(a <0)
	{
		a =0;
	}
	return counter;
}

void Game::DisplayRoom()
{
	cout<<"*****************************************************************************"<<endl;
	cout<<"\t\t\tThe Floor As You Know it"<<endl;
	cout<<"*****************************************************************************"<<endl;
	int startRow = m_pPlayer->GetRow() -1;	//Row above player
	int endRow = m_pPlayer->GetRow() +1;	//Row below player
	int startColumn = m_pPlayer->GetColumn() -1;	//Column to players left
	int endColumn = m_pPlayer->GetColumn() +1;	//Column to players right

	if(AreLightsOn())
	{
		TurnOnLights();		//Checks to see if the lights should be on
	}
	else if(!AreLightsOn())
	{
		TurnOffLights();	//Checks to see if the lights should be off
	}

	m_EnemyIter= Enemies.begin();
	//Prints out the Room
	for(int i=0; i < ROWS; ++i)
	{
		for(int j=0; j <COLUMNS; ++j)
		{
			if(m_Room[i][j]->GetType() == 4)//If the player is there
			{
				m_Room[i][j]->SetSymbol(m_pPlayer->GetSymbol());
			}
			else if(m_Room[i][j]->GetType()==5) //If an Enemy is there
			{
				if(m_EnemyIter != Enemies.end())
				{
					m_Room[i][j]->SetSymbol((*m_EnemyIter)->GetSymbol());
					m_EnemyIter++;
				}
			}	

			if(m_pPlayer->GetEquippedItem()!=NULL && (m_pPlayer->GetEquippedItem())->GetName()=="Matches")	//If the player has Matches Equipped
			{
				
				//If the player is using matches
				for(int i=startRow; i <=endRow; i++)
				{
					for(int j=startColumn; j <=endColumn;j++)
					{	
						if(m_Room[i][j]->GetType()==5)//Enemy there
						{
							m_Room[i][j]->SetVisibility(true);
						}
						else if(m_Room[i][j]->GetType()!=0) //If not a blank spot
						{
							m_Room[i][j]->SetVisibility(true);
							m_Room[i][j]->SetDiscovered(true);
						}	
					}
				}

			}
			cout << *m_Room[i][j];
		}
			cout << endl;
	}
	cout<<"*****************************************************************************"<<endl;
}

void Game::Door()
{
	//Detects if there is a door near the player
	string choice;
	string direction;
	int directionInt;
	if(m_GameEventHandler->isRoomClear(m_currentRoom))
	{
		//Up
		if(m_Room[(m_pPlayer->GetRow()-1)][m_pPlayer->GetColumn()]->GetType() == 13)	//Up
		{
			cout << "You found a door!!" <<endl;
			cout <<"Would you like to go through it?"<<endl;
			cout <<"\t1 - Yes" <<endl;
			cout <<"\t2 - No"<<endl;
			cin >> choice;
			do
			{
				switch(choice[0])
				{
				case '1':
					RoomSwap(m_nextRoom);
					break;
				case '2':
					cout <<"Okay, move along"<<endl;
					cout << "What direction?" <<endl;
					cout << "0 - Forward" <<endl;
					cout << "1 - Left" <<endl;
					cout << "2 - Right" <<endl;
					cout << "3 - Behind" <<endl;
					do
					{
						cin >> direction;
					}while(direction!="0" && direction != "1" && direction !="2" && direction !="3");
					switch(direction[0])
					{
					case '1':
						directionInt = 1;
						m_pPlayer->SetDirection(directionInt,m_Room);
						break;
					case '2':
						directionInt = 2;
						m_pPlayer->SetDirection(directionInt,m_Room);
						break;
					case '3':
						directionInt = 3;
						m_pPlayer->SetDirection(directionInt,m_Room);
						break;
					}
					if(direction[0] != '0')
					{
						m_pPlayer->SetDirection(directionInt,m_Room);			//After getting their direction they move and run off
						m_pPlayer->Move(m_pPlayer, m_Room);
					}
					else
					{
						m_pPlayer->Move(m_pPlayer,m_Room);
					}
					break;
				default:
					cout << "Invalid choice, try again" <<endl;
					break;
				}
			}while(choice != "1" && choice!="2");
		}
		//DOWN
		else if(m_Room[m_pPlayer->GetRow()+1][m_pPlayer->GetColumn()]->GetType()==13)	//Down
		{
			cout << "You found a door!!" <<endl;
			cout <<"Would you like to go through it?"<<endl;
			cout <<"\t1 - Yes" <<endl;
			cout <<"\t2 - No"<<endl;
			cin >> choice;
			do
			{
				switch(choice[0])
				{
				case '1':
					RoomSwap(m_nextRoom);
					break;
				case '2':
					cout <<"Okay, move along"<<endl;
					cout << "What direction?" <<endl;
					cout << "0 - Forward" <<endl;
					cout << "1 - Left" <<endl;
					cout << "2 - Right" <<endl;
					cout << "3 - Behind" <<endl;
					do
					{
						cin >> direction;
					}while(direction!="0" && direction != "1" && direction !="2" && direction !="3");
					switch(direction[0])
					{
					case '1':
						directionInt = 1;
						m_pPlayer->SetDirection(directionInt,m_Room);
						break;
					case '2':
						directionInt = 2;
						m_pPlayer->SetDirection(directionInt,m_Room);
						break;
					case '3':
						directionInt = 3;
						m_pPlayer->SetDirection(directionInt,m_Room);
						break;
					}
					if(direction[0] != '0')
					{
						m_pPlayer->SetDirection(directionInt,m_Room);			//After getting their direction they move and run off
						m_pPlayer->Move(m_pPlayer, m_Room);
					}
					else
					{
						m_pPlayer->Move(m_pPlayer,m_Room);
					}
					break;
				default:
					cout << "Invalid choice, try again" <<endl;
					break;
				}
			}while(choice != "1" && choice!="2");
		}
		//LEFT
		else if(m_Room[m_pPlayer->GetRow()][m_pPlayer->GetColumn()-1]->GetType()==13)	//Left
		{
		cout << "You found a door!!" <<endl;
			cout <<"Would you like to go through it?"<<endl;
			cout <<"\t1 - Yes" <<endl;
			cout <<"\t2 - No"<<endl;
			cin >> choice;
			do
			{
				switch(choice[0])
				{
				case '1':
					RoomSwap(m_nextRoom);
					break;
				case '2':
					cout <<"Okay, move along"<<endl;
					cout << "What direction?" <<endl;
					cout << "0 - Forward" <<endl;
					cout << "1 - Left" <<endl;
					cout << "2 - Right" <<endl;
					cout << "3 - Behind" <<endl;
					do
					{
						cin >> direction;
					}while(direction!="0" && direction != "1" && direction !="2" && direction !="3");
					switch(direction[0])
					{
					case '1':
						directionInt = 1;
						m_pPlayer->SetDirection(directionInt,m_Room);
						break;
					case '2':
						directionInt = 2;
						m_pPlayer->SetDirection(directionInt,m_Room);
						break;
					case '3':
						directionInt = 3;
						m_pPlayer->SetDirection(directionInt,m_Room);
						break;
					}
					if(direction[0] != '0')
					{
						m_pPlayer->SetDirection(directionInt,m_Room);			//After getting their direction they move and run off
						m_pPlayer->Move(m_pPlayer, m_Room);
					}
					else
					{
						m_pPlayer->Move(m_pPlayer,m_Room);
					}
					break;
				default:
					cout << "Invalid choice, try again" <<endl;
					break;
				}
			}while(choice != "1" && choice!="2");
		}
		//RIGHT
		else if(m_Room[m_pPlayer->GetRow()][m_pPlayer->GetColumn()+1]->GetType() == 13)	//Right
		{
			cout << "You found a door!!" <<endl;
			cout <<"Would you like to go through it?"<<endl;
			cout <<"\t1 - Yes" <<endl;
			cout <<"\t2 - No"<<endl;
			cin >> choice;
			do
			{
				switch(choice[0])
				{
				case '1':
					RoomSwap(m_nextRoom);
					break;
				case '2':
					cout <<"Okay, move along"<<endl;
					cout << "What direction?" <<endl;
					cout << "0 - Forward" <<endl;
					cout << "1 - Left" <<endl;
					cout << "2 - Right" <<endl;
					cout << "3 - Behind" <<endl;
					do
					{
						cin >> direction;
					}while(direction!="0" && direction != "1" && direction !="2" && direction !="3");
					switch(direction[0])
					{
					case '1':
						directionInt = 1;
						m_pPlayer->SetDirection(directionInt,m_Room);
						break;
					case '2':
						directionInt = 2;
						m_pPlayer->SetDirection(directionInt,m_Room);
						break;
					case '3':
						directionInt = 3;
						m_pPlayer->SetDirection(directionInt,m_Room);
						break;
					}
					if(direction[0] != '0')
					{
						m_pPlayer->SetDirection(directionInt,m_Room);			//After getting their direction they move and run off
						m_pPlayer->Move(m_pPlayer, m_Room);
					}
					else
					{
						m_pPlayer->Move(m_pPlayer,m_Room);
					}
					break;
				default:
					cout << "Invalid choice, try again" <<endl;
					break;
				}
			}while(choice != "1" && choice!="2");
		}
	}
}

bool Game::IsThereAnEvent()
{
	//Up
	if(m_Room[(m_pPlayer->GetRow()-1)][m_pPlayer->GetColumn()]->GetObject() == m_GameEventHandler)	//Up
	{
		return true;
	}
	//DOWN
	else if(m_Room[m_pPlayer->GetRow()+1][m_pPlayer->GetColumn()]->GetObject() == m_GameEventHandler)	//Down
	{
		return true;
	}
	//LEFT
	else if(m_Room[m_pPlayer->GetRow()][m_pPlayer->GetColumn()-1]->GetObject() == m_GameEventHandler)	//Left
	{
		return true;
	}
	//RIGHT
	else if(m_Room[m_pPlayer->GetRow()][m_pPlayer->GetColumn()+1]->GetObject() == m_GameEventHandler)	//Right
	{
		return true;
	}

	return false;
}

void Game::SetLightsOn(bool lightsOn)
{
	*m_lightsOn = lightsOn;		//Sets whether the lights should be on or off
}

bool Game::AreLightsOn() const
{
	return *m_lightsOn;		//Returns whether or not the lights are on
}

void Game::TurnOnLights()
{
	for(int i=0; i<ROWS; i++)
	{
		for(int j=0; j <COLUMNS; j++)
		{
			m_Room[i][j]->SetVisibility(true);	//Make everything visible
		}
	}
}

void Game::TurnOffLights()
{
	for(int i=0; i<ROWS; i++)
	{
		for(int j=0; j <COLUMNS; j++)	//Make everything invisible
		{
			m_Room[i][j]->SetVisibility(false);

			if(m_Room[i][j]->GetType() == 4)//If the player is there
			{
				m_Room[i][j]->SetVisibility(true);
			}
		}
	}
}

void Game::EnemyTurn(vector<Enemy*> Enemies)
{
	int enemyMoveCount = 0; //Used so the enemy doesn't get stuck in a loop and kill the game
	for(m_EnemyIter=Enemies.begin(); m_EnemyIter < Enemies.end(); m_EnemyIter++)
	{
		if(*m_EnemyIter !=NULL)
		{
			if(!(*m_EnemyIter)->isDead())	//If enemy is not dead
			{
				(*m_EnemyIter)->whereIsPlayer(m_Room, m_pPlayer);	//Change Direction to face player
				(*m_EnemyIter)->Move(*m_EnemyIter,m_Room,enemyMoveCount);	//Move in direction currently facing
			}
		}
	}
}

void Game::RoomSwap(int newRoom)
{
	//First things first, wipe out the current room, enemies, and items
	for(int i=0; i < ROWS; ++i)
	{
		for(int j=0; j<COLUMNS; ++j)
		{
			delete m_Room[i][j];
			m_Room[i][j] = NULL;
		}
	}
	Enemies.clear();
	Items.clear();

	//Now call the RoomLoad Function

	RoomLoad(newRoom);
}
