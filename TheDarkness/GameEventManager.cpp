#include "GameEventManager.h"


GameEventManager::GameEventManager(int Row, int Column)
{
	m_pEventRow = new int(Row);
	m_pEventColumn = new int(Column);
	m_pEventPosition = new int(0);
	m_pRoom1Clear = new bool(false);
	m_pRoom2Clear = new bool(false);
	m_pRoom3Clear = new bool(false);
	m_pSymbol = new string(" ! ");
	m_pStartRow = new int(Row);
	m_pStartColumn = new int(Column);
	m_GameOver = new bool(false);
}


GameEventManager::~GameEventManager(void)
{
	delete m_pEventRow;
	m_pEventRow = NULL;
	delete m_pEventColumn;
	m_pEventColumn = NULL;
	delete m_pEventPosition;
	m_pEventPosition = NULL;
	delete m_pSymbol;
	m_pSymbol = NULL;

	delete m_pStartRow;
	delete m_pStartColumn;
	m_pStartRow = NULL;
	m_pStartColumn = NULL;

	delete m_GameOver;
	m_GameOver = NULL;
}

void GameEventManager::SetEventPosition(int pos)
{
	*m_pEventPosition = pos;
}

bool GameEventManager::isRoomClear(int room)
{
	//Takes in the room number (0-2)
	switch(room)
	{
	case 0:
		//Room 1
		if(*m_pRoom1Clear != NULL && *m_pRoom1Clear == true)
		{
			return true;
		}
		break;
	case 1:
		//Room 2
		if(*m_pRoom2Clear != NULL && *m_pRoom2Clear == true)
		{
			return true;
		}
		break;
	case 2:
		//Room 3
		if(*m_pRoom3Clear != NULL && *m_pRoom3Clear == true)
		{
			return true;
		}
		break;
	}
	return false;

}


void GameEventManager::SetPosition(int Row,int Column)
{
	*m_pEventRow = Row;
	*m_pEventColumn = Column;
}

int GameEventManager::GetColumn() const
{
	return * m_pEventColumn;
}

int GameEventManager::GetRow() const
{
	return * m_pEventRow;
}

int GameEventManager::GetEvent() const
{
	return *m_pEventPosition;
}


bool GameEventManager::GetGameOver() const
{
	return *m_GameOver;
}

void GameEventManager::PlayEvent(Player * pPlayer,Cell*Room[20][20])
{
	if(*m_pEventPosition !=0 && Room[GetRow()][GetColumn()] !=NULL)
	{
		Room[GetRow()][GetColumn()]->Reset();	//Resets the Cell the event is in
	}
	switch(GetEvent())
	{
		//Floor 1
	case 0:
		GameStart(pPlayer);
		*m_pEventPosition=+1;
		break;
	case 1:
		FirstRadioContact(pPlayer);
		CreateNextEvent(Room);
		break;
	case 2:
		FindTheKey(pPlayer);
		CreateNextEvent(Room);
		break;
	case 3:
		GoToElevator(pPlayer);
		//There is no create here because this is the end of the room, the next room will deal with continuing it on
		*m_pEventPosition+=1;	//So the next event will be loaded
		*m_pRoom1Clear = true;
		break;
		//Floor 2
	case 4:
		YouFoundTheGenerator(pPlayer);
		CreateNextEvent(Room);
		break;
	case 5:
		FindGasoline(pPlayer);
		CreateNextEvent(Room);
		break;
	case 6:
		FindTools(pPlayer);
		CreateNextEvent(Room);
		break;
	case 7:
		FindKey(pPlayer);
		CreateNextEvent(Room);
		break;
	case 8:
		UnderAttack(pPlayer);
		*m_pEventPosition+=1;	//So the next event will be loaded (since the Create new isnt called)
		*m_pRoom2Clear = true;
		break;
	case 9:
		GetThroughTheDoor();
		*m_pEventPosition+=1;
		break;
		//Floor 3
	case 10:
		DarkRevelations(pPlayer);
		CreateNextEvent(Room);
		break;
	case 11:
		Choices(pPlayer);
		break;
	}
}

void GameEventManager::CreateNextEvent(Cell* Room[20][20])
{
	vector<int> randPos;
	int row =0;
	int column = 0;
	for(int i=0; i < 20; i++)
	{
		randPos.push_back(i);
	}
	do
	{
		random_shuffle(randPos.begin(),randPos.end());
		row = randPos.front();
		random_shuffle(randPos.begin(),randPos.end());
		column = randPos.front();
	}while(!Room[row][column]->isEmpty());

	//Builds a new game event cell elsewhere
	SetPosition(row,column);
	Room[row][column]->SetEmpty();
	Room[row][column]->SetObject(this);	//make it point to this class
	Room[row][column]->SetType(10);	//Make it the correct type
	Room[row][column]->SetSymbol(*m_pSymbol);
	Room[row][column]->SetVisibility(true);
	Room[row][column]->SetDiscovered(true);
	
	*m_pEventPosition+=1;	//Increments the event's position
}

void GameEventManager::Reset()
{
	*m_pEventPosition =0;
}

//The Events

//Floor One
void GameEventManager:: GameStart(Player * pPlayer)
{
	Sleep(2000);
	system("cls");
	cout << "My head";
	for(int i=0; i <4;i++)
	{
		Sleep(250);
		cout <<".";
	}
	char choice;
	cout <<"\nYou awaken in the dark. Your head spinning and in pain"<<endl;
	cout <<"What would you like to do?"<<endl;
	cout <<"\t1 - Attempt to stand" <<endl;
	cout <<"\t2 - Lay here in agony"<<endl;
	do
	{
		cin >> choice;
	}while(choice!='1' && choice != '2');

	//Choice
	switch(choice)
	{
	case '1':
		cout << "You attempt to stand, but the pain drives you down to your knees...and eventually the floor" <<endl;
		break;
	case '2':
		cout <<"No shame in accepting you are in pain"<<endl;
		break;
	}

	//Pause
	system("pause");
	system("cls");

	cout <<"Care to try again?"<<endl;
	cout <<"\t1 - Yes"<<endl;
	cout <<"\t2 - No"<<endl;
	cin>>choice;

	//Choice
	switch(choice)
	{
	case '1':
		cout <<"Thats the spirit!!"<<endl;
		break;
	case '2':
		cout <<"Wont get anywhere like that..."<<endl;
		Sleep(3000);
		system("pause");
		break;
	}

	cout <<"After a good pep talk you manage to get to your feet."<<endl;
	system("pause");
	system("cls");
	cout <<"Standing up you suddenly notice a beeping sound coming from your chest."<<endl;
	
	cout <<"What would you like to do?"<<endl;
	cout <<"\t1 - Investigate the sound"<<endl;
	cout <<"\t2 - Look Around"<<endl;
	do{
		cin >> choice;
	}while(choice !='1' && choice !='2');

	//Choice
	switch(choice)
	{
	case '1':
		//Investigating the sound
		cout <<"You turn and look in different directions and notice that the sound changes."<<endl;
		system("pause");
		cout <<"You hear two distinct beeps, the first one followed a few seconds later by another."<<endl;
		system("pause");
		cout <<"Sometimes, the pause between them is long, sometimes short."<<endl;
		system("pause");
		cout <<"There is also a strange device on your wrist. Would you like to investigate?"<<endl;
		cout <<"\t1 - Yes"<<endl;
		cout <<"\t2 - No"<<endl;
		do{
			cin >> choice;
		}while(choice!='1' && choice != '2');

		switch(choice)
		{
		case '1':
			cout <<"The device looks like a watch, but instead of the time it simply gives a number and then Meters"<<endl;
			cout <<"Perhaps its distance?"<<endl;
			cout <<"You look around until it says 1, and you take a step forward"<<endl;
			system("pause");
			cout <<"And run into a table"<<endl;
			break;
		case '2':
			cout <<"Alright fine, wander about and learn as you go." <<endl;
			break;
		}
		break;
	//looking around
	case '2':
		cout <<"You see blackness...howabout you investigate that device, eh"<<endl;
		cout <<"\t1 - Okay...fine"<<endl;
		cout <<"\t2 - No"<<endl;
		do{
			cin >> choice;
		}while(choice!='1' && choice != '2');
		switch(choice)
		{
		case '1':
			//Investigating the sound
			cout <<"You turn and look in different directions and notice that the sound changes."<<endl;
			system("pause");
			cout <<"You hear two distinct beeps, the first one followed a few seconds later by another."<<endl;
			system("pause");
			cout <<"Sometimes, the pause between them is long, sometimes short."<<endl;
			system("pause");
			cout <<"There is also a strange device on your wrist. Would you like to investigate?"<<endl;
			cout <<"\t1 - Yes"<<endl;
			cout <<"\t2 - No"<<endl;

			do{
				cin >> choice;
			}while(choice!='1' && choice != '2');

			switch(choice)
			{
			case '1':
				cout <<"The device looks like a watch, but instead of the time it simply gives a number and then Meters"<<endl;
				cout <<"Perhaps its distance?"<<endl;
				cout <<"You look around until it says 1, and you take a step forward"<<endl;
				system("pause");
				cout <<"And run into a table"<<endl;
				break;
			case '2':
				cout <<"Alright fine, wander about and learn as you go." <<endl;
				break;
			}
		}
		break;
	}
	
	system("cls");
	cout <<"\n\nYou should explore and learn more about where you are, what happened, and what this strange device is." <<endl;

	system("pause");
}
void GameEventManager::FirstRadioContact(Player * pPlayer)
{
	system("cls");
	char choice;
	cout <<"You hear a crackling radio, approaching it you hear a voice"<<endl;
	system("pause");
	cout <<"Hello. Hello. Is this thing on??"<<endl;
	cout <<"\t1 - Yes, who is this?"<<endl;
	cout <<"\t2 - Hello!! Hello!! Who is this?!!"<<endl;
	do{
		cin >> choice;
	}while(choice !='1' && choice !='2');

	cout <<"You hear silence on the other end of the radio";
	for(int i=0; i <4;i++)
	{
		Sleep(400);
		cout<<".";
	}
	cout<<"for a moment"<<endl;

	system("pause");

	cout <<"Who is this?"<<endl;
	cout <<"What do you say?"<<endl;
	cout <<"\t1 - My name is "<<pPlayer->GetName()<<endl;
	cout <<"\t2 - Uhh I don't remember, I think I hit my head <LIE>"<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='2');

	switch(choice)
	{
	case '1':
		cout<<"He pauses for a moment...again"<<endl;
		system("pause");
		cout <<"Well, "<<pPlayer->GetName()<<" you can call me The Caretaker, since I plan to take care of you."<<endl;
		break;
	case '2':
		cout <<"Hmm, alright. Well you can call me The Caretaker, since I am going to be taking care of you."<<endl;
		break;
	}
	cout <<"What do you want to ask him"<<endl;
	cout <<"\t1 - Why do I need help?"<<endl;
	cout <<"\t2 - What are you going to do to help?"<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='2');
	switch(choice)
	{
	case'1':
		cout <<"You barely remember your name, and you are wandering in the dark."<<endl;
		cout <<"I think you need some help."<<endl;
		break;
	case '2':
		cout <<"I am going to instruct you in how to escape."<<endl;
		break;
	}
	system("pause");
	system("cls");
	cout <<"\nUh oh, I can hear something pounding at the door."<<endl;
	cout <<"\nSearch side rooms for MED-KITS, WEAPONS, ARMOUR and MATCHES."<<endl;
	cout <<"These creatures are WEAK to LIGHT"<<endl;
	system("pause");
	cout <<"\n...what was he said about creatures?"<<endl;
	system("pause");
	system("cls");
}
void GameEventManager::FindTheKey(Player * pPlayer)
{
	system("cls");
	cout <<"Again you hear the crackling of a PA"<<endl;
	system("pause");
	cout <<"Sorry about that, I'm back"<<endl;
	cout <<"Now what you need to do is get the power back on."<<endl; 
	cout <<"There is a stairwell on this floor."<<endl;
	cout <<"The door is locked though, so you should go find the key."<<endl;
	cout <<"When you do find the key, head to the south-east corner of the floor"<<endl;
	cout <<"Good luck"<<endl;
	cout <<endl;
	

	cout<<"\nGo forth and find that key"<<endl;
	system("pause");
	system("cls");
}
void GameEventManager::GoToElevator(Player * pPlayer)
{
	system("cls");
	cout<<"You step forward and run into something hard and squishy"<<endl;
	cout<<"Investigating you realize that its a body"<<endl;
	cout<<"Remembering that you were looking for a key you start searching the body"<<endl;
	cout<<"You find a key in a pants pocket"<<endl;
	cout <<"\nNow go find that stairs, SOUTH-EAST corner he said"<<endl;
	system("pause");
	system("cls");
}




//Floor Two
void GameEventManager::YouFoundTheGenerator(Player * pPlayer)
{
	system("cls");
	char choice;
	cout<<"Over the P.A system you hear the Caretaker again"<<endl;
	cout<<"\nHave you found the generator?"<<endl;
	cout<<"\nWhat do you say?"<<endl;
	cout<<"\t1 - Yea, and its pretty banged up"<<endl;
	cout<<"\t2 - What do I need to fix it?"<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='2');

	cout <<"You need to go find some GASOLINE,TOOLS and then a KEY to start it"<<endl;
	cout <<"\nHow do you reply?"<<endl;
	cout<<"\t1 - Sounds a bit complicated"<<endl;
	cout <<"\t2 - Simple enough"<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='2');

	cout <<"Thats the spirit, now go find that stuff."<<endl;

	//Learn something about the device
	cout <<"Ask some questions?"<<endl;
	cout <<"\t1 - Yes"<<endl;
	cout <<"\t2 - No"<<endl;
	do{
		cin>>choice;
	}while(choice!='1' && choice !='2');
	switch(choice)
	{
	case '1':
		do{
			cout <<"Thats an experimental sonar device, that you were testing before...well before the power got cut."<<endl;
			cout <<"\nWhat would you like to do?"<<endl;
			cout <<"\t1 - Where are we?"<<endl;
			cout <<"\t2 - Who am I?"<<endl;
			cout <<"\t3 - What is it?"<<endl;
			cout <<"\t4 - Carry on your merry and don't ask"<<endl;
			do{
				cin>>choice;
			}while(choice!='1' && choice!='2'&&choice!='3'&&choice!='4');
			cout <<"We really don't have time for questions \n"<<endl;
			switch(choice)
			{
			case '1':
				cout <<"You must have hit your head pretty hard."<<endl;
				cout <<"We are in a top secret government lab"<<endl;
				cout <<"Think Area 51, crazy experiments, devices, no Aliens though"<<endl;
				system("pause");
				break;
			case '2':
				cout <<"You're a scientist, I've seen your name before"<<endl;
				cout <<"but we haven't spoken much, I'm a geneticist."<<endl;
				cout <<"You're an engineer."<<endl;
				system("pause");
				break;
			case '3':
				cout <<"If I remember correctly its a sonar device"<<endl;
				cout <<"A sound wave goes out from your chest and bounces back"<<endl;
				cout <<"A high pitched beep means whatever it hit is living" <<endl;
				cout <<"A lower one means its non-living"<<endl;
				cout <<"The distance from yourself to the object is displayed"<<endl;
				cout <<"on the watch like device on your wrist."<<endl;
				system("pause");
				break;
			case '4':
				break;
			}
		}while(choice != '4');
		break;
	case '2':
		break;
	}
	system("pause");
	system("cls");
}
void GameEventManager::FindGasoline(Player * pPlayer)
{
	system("cls");
	cout <<"You find a can of gasoline"<<endl;
	system("pause");
	system("cls");
}
void GameEventManager::FindTools(Player * pPlayer)
{
	system("cls");
	cout <<"You find a tool box"<<endl;
	system("pause");
	system("cls");
}
void GameEventManager:: FindKey(Player * pPlayer)
{
	system("cls");
	cout <<"You stumble across a key"<<endl;
	system("pause");
	system("cls");
}
void GameEventManager::UnderAttack(Player * pPlayer)
{
	char choice;
	cout <<"You make it back to the generator."<<endl;
	cout <<"The Caretaker comes back over the P.A"<<endl;
	cout <<"Are you done?"<<endl;

	do
	{
		cout <<"\t1 - Yes"<<endl;
		cout <<"\t2 - No"<<endl;
		do{
			cin>>choice;
		}while(choice!='1' && choice!='2');
		switch(choice)
		{
		case '1':
			cout <<"Alright, use the tools to fix it up"<<endl;
			system("pause");
			cout <<"\nInspecting the generator you notice that some hoses are pulled out"<<endl;
			cout <<"Along with wires cut"<<endl;
			cout <<"You put the hoses back, tape up the wires, and generally Macgyver it"<<endl;
			system("pause");
			cout<<"Next you have to put the gas in the tank"<<endl;
			cout<<"\n You put gasoline in the tank, simple enough"<<endl;
			system("pause");
			cout<<"Now just turn the key and power it up"<<endl;
			break;
		case '2':
			cout <<"You liar, you know you are..."<<endl;
			break;
		}
	}while(choice !='1');
	cout <<"The generator comes to life"<<endl;
	cout <<"You hear a rumbling coming from the air vents"<<endl;
	cout <<"You hear the Caretaker shout. RUN!!! Get through that door"<<endl;
}

void GameEventManager::GetThroughTheDoor()
{
	system("cls");
	char choice;
	cout <<"You get through the door and run and run"<<endl;
	cout <<"Luckily the lights are on now so you can see much easier"<<endl;
	cout <<"You round a corner and before you you see 5 grotesque creatures"<<endl;
	cout <<"Standing 6 feet tall, the body of a man"<<endl;
	cout <<"But a forward jutting neck and the head of a Hammerhead shark"<<endl;
	cout<<"Not to mention a long tail"<<endl;
	system("pause");
	cout <<"These must be the creatures you've been fighting"<<endl;
	cout <<"Do you?"<<endl;
	cout <<"\t1 - Run?"<<endl;
	cout <<"\t2 - Charge?"<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='2');
	switch(choice)
	{
	case'1':
		cout <<"You turn and run"<<endl;
		cout <<"They quickly catch up"<<endl;
		break;
	case'2':
		cout<<"You charge them"<<endl;
		break;
	}
	cout <<"You try to fight them but they're are too many and far too strong"<<endl;
	cout <<"Just when you think its too late, you see a man approaching from the side"<<endl;
	cout <<"He has a strange device, he holds it up and the creatures run off"<<endl;
	system("pause");
	cout <<"He smiles and walks over. Speaking to you he says:"<<endl;
	cout <<"Like a dog whistle, makes them as docile as a puppy. Luckily only I know the frequency"<<endl;
	cout <<"I am the Caretaker, and you are a loose end. Goodbye"<<endl;
	cout <<"He smiles, and smashes you over the head"<<endl;
	cout <<"You black out"<<endl;
}


//Floor Three
void GameEventManager::DarkRevelations(Player * pPlayer)
{
	char choice;
	system("cls");
	cout <<"Your head pounding from the Caretaker's hit you approach a bank of computers"<<endl;
	cout <<"As per usual, the P.A system comes to life"<<endl;
	cout <<"Hello, Mr.LoosEnd. How is the head?"<<endl;
	cout <<"\t1 - WHO THE HELL ARE YOU!!!"<<endl;
	cout <<"\t2 - Hurts a bit"<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='2');
	switch(choice)
	{
	case '1':
		cout <<"Well, sit right there and I shall elaborate"<<endl;
		break;
	case '2':
		cout <<"Hahaha, funny. Shame I didn't hit you harder"<<endl;
		break;
	}
	system("pause");
	cout <<"You and I are scientists at a research lab"<<endl;
	cout <<"I have been working on making some sort of replacement to a soldier"<<endl;
	cout <<"Take the best parts of many creatures, and create a super being."<<endl;
	cout <<"Cheap, easy, expendable. That was the hope anyway"<<endl;
	cout <<"Well we got something, the Nightstalkers. These creatures you have been fighting"<<endl;
	cout <<"They are my creations"<<endl;
	cout <<"\nAsk a question"<<endl;
	cout <<"\t1 - Why did you unleash them?"<<endl;
	cout <<"\t2 - Why are they loose"<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='2');
	switch(choice)
	{
	case '1':
		cout <<"Good good you remember all that, excellent"<<endl;
		break;
	case '2':
		cout <<"Well, that is a somethng else isnt it."<<endl;
		break;
	}
	cout <<"That's easy to explain."<<endl;
	cout <<"I did it because I can, I am the only one who can control them"<<endl;
	cout <<"And world domination seems like a fun idea"<<endl;

	cout <<"What do you say?"<<endl;
	cout <<"\t1 - You're insane!"<<endl;
	cout <<"\t2 - Why am I a loose end?"<<endl;
	do{
		cin>>choice;
	}while(choice!='1'&&choice!='2');
	switch(choice)
	{
	case '1':
		cout <<"That may be, and you almost stopped me."<<endl;
		break;
	case '2':
		cout <<"Because you are the only other living person on this base"<<endl;
		break;
	}

	cout <<"When I unleashed them, you caught me. We had a fight and I knocked you over the head"<<endl;
	cout <<"Funny how I keep doing that and you just won't die eh?"<<endl;
	cout <<"Luckily for me you survived."<<endl;
	cout <<"When they were unleashed, the base went into lockdown, and the power was cut"<<endl;
	cout <<"I needed you to get the power back on so I could tell the army not to nuke us"<<endl;
	cout <<"Anywho, I have a world to take over. Do try to die"<<endl;
	system("pause");
	system("cls");
}

void GameEventManager::Choices(Player*pPlayer)
{
	char choice;
	cout <<"You find a ladder leading up to a hatch."<<endl;
	cout <<"You climb it"<<endl;
	system("pause");
	cout <<"\nAt the top there are two doors"<<endl;
	cout <<"The one has exit above it"<<endl;
	cout <<"The other has COMMUNICATIONS above it"<<endl;
	cout <<"You have a choice." <<endl;
	cout <<"Use it to call the army."<<endl;
	cout <<"Do nothing, and use the P.A to call the Caretaker"<<endl;
	cout <<"Escape through the door, into armageddon"<<endl;
	system("pause");
	cout <<"\n\nWhat are you?"<<endl;
	cout <<"A Hero? Tell the army to burn the place to the ground?"<<endl;
	cout <<"A Villain? Call up the Caretaker and make a deal?"<<endl;
	cout <<"A Survivot? Escape through the door?"<<endl;
	cout <<"\t1 - Hero?"<<endl;
	cout <<"\t2 - Villain?"<<endl;
	cout <<"\t3 - Survivor?"<<endl;
	do{
		cin>>choice;
	}while(choice !='1' && choice!='2' && choice!='3');

	switch(choice)
	{
	case '1':
		Hero();
		break;
	case '2':
		Villain();
		break;
	case '3':
		Survivor();
		break;
	}
	*m_GameOver = true;
}

void GameEventManager::Hero()
{
	char choice;
	do{
		cout <<"Looking at the board of buttons you wonder which to press"<<endl;
		cout <<"\t1 - Big RED One"<<endl;
		cout <<"\t2 - Small Blue One"<<endl;
		cout <<"\t3 - The one labelled CONTAINMENT BREACH"<<endl;
		do{
			cin>>choice;
		}while(choice!='1' && choice !='2' && choice != '3');
		switch(choice)
		{
		case'1':
			cout <<"You hear a distant explosion"<<endl;
			cout <<"Maybe thats good?"<<endl;
			break;
		case'2':
			cout <<"Nothing happens"<<endl;
			break;
		case '3':
			cout <<"You see the device light up"<<endl;
			cout <<"A banner comes across saying "<<endl;
			cout <<"EMERGENCY CONTAINMENT BREACH"<<endl;
			cout <<"Now to wait and see if that worked..."<<endl;
			break;
		}
	}while(choice!='3');
	cout <<"Would you like to escape in the mean time?"<<endl;
	cout <<"\t1 - Yes"<<endl;
	cout <<"\t2 - No"<<endl;
	do{
		cin>>choice;
	}while(choice !='1' && choice !='2');
	switch(choice)
	{
	case '1':
		cout <<"You escape through the door and run"<<endl;
		cout <<"Reaching the surface you find yourself in the desert"<<endl;
		cout <<"You begin to run, a few minutes later an explosion rocks you to the ground"<<endl;
		cout <<"Turning you see a mushroom cloud climbing from what you assume was the base"<<endl;
		cout <<"You survived, good job!"<<endl;
		break;
	case'2':
		cout <<"Fine, your funeral"<<endl;
		cout <<"On the plus side you're a hero...a dead one though"<<endl;
	}

	system("pause");
	system("cls");
}

void GameEventManager::Villain()
{
	char choice;
	cout <<"You flip some switches and turn some knobs"<<endl;
	cout <<"Finding the channel the Caretaker has been using you say:"<<endl;
	cout <<"\t1 - I want Europe"<<endl;
	cout <<"\t2 - Howabout we deal?"<<endl;
	cout <<"\t3 - How do you feel about partners?"<<endl;
	do{
		cin>>choice;
	}while(choice !='1' && choice !='2' && choice !='3');
	cout <<"You hear the static cut out for a second" <<endl;
	system("pause");
	cout <<"Welcome aboard" <<endl;
	cout <<"\n\n As they say desperate times call for desperate meausures"<<endl;
	system("pause");
	system("cls");
}

void GameEventManager::Survivor()
{
	cout <<"You walk through the door"<<endl;
	cout <<"How long will you survive though??"<<endl;
	system("pause");
	system("cls");
}