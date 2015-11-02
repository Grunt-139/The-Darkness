#pragma once
#include <string>
#include <iostream>
#include <Windows.h>
#include "GameObject.h"
#include <vector>
#include <algorithm>

using namespace std;


class Cell
{
friend ostream& operator <<(ostream& os, const Cell& aCell);
public:
	Cell(int type=0, string description="nothing.", GameObject* object = NULL);
	~Cell();
	void Reset();	//Does a Reset
	void SetSymbol(string& newSymbol);	//For New Symbol
	const string& GetSymbol() const;
	const int& GetType() const;
	void SetType(int newType);	//For changing the Type
	bool isEmpty() const;	//Check if empty
	void SetEmpty();	//Switches true to false, and false to true
	bool GetVisible() const;	//Is it visible
	void SetVisibility(bool visible);	//Change visibility
	string GetDescription() const;	//Get the cell's description
	void SetDescription(string newDescription);	//Set the Cell's description
	void SetObject(GameObject * newObject);	//Changes the Object
	GameObject* GetObject() const;	//Gets the Object
	void SetDiscovered(bool discovered);
	bool isDiscovered() const;

private:
	string m_Description;
	string m_Symbol;
	int m_Type;
	bool m_Empty;
	bool m_isVisible;
	bool m_Discovered;
	GameObject * m_MyObject;

};

