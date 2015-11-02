#include <iostream>
#include <Windows.h>
#include "Game.h"


using namespace std;


int main()
{
	Game aGame;
	char again;
	do
	{
		aGame.MainMenu();
		cout << "\t\tAre you sure you want to quit? (y/n): ";
		cin >> again;
	}while(again !='y' && again != 'Y');
	cout <<"\n\n"<<endl;
	cout <<"\t\t\t  Thank you for playing :)";
	
	Sleep(1000);
	
	return 0;
}

