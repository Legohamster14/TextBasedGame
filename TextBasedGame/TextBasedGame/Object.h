#pragma once
#include "Item.h"
#include <iostream>

enum ObjectType
{
	Chest, Table, Carpet, Cupboad
};

class Object
{
private:
	std::string m_objectName;
	std::string m_searchText;
	Item m_hiddenItem;
	bool m_bIsSearched = false;
public:
	Object();
	Object(ObjectType type, Item item = Item());
	~Object();
	Item* Search();
	std::string GetName();
};

//Object table;
//Object chest = Object(Chest, Item("TestItem"));
//Object cupboard;