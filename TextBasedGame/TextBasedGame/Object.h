#pragma once
#include "Item.h"

enum ObjectType
{
	Chest, Table, Carpet, Cabinet
};

class Object
{
private:
	std::string m_objectName;
	std::string m_searchText;
	Item* m_hiddenItem = nullptr;
public:
	Object();
	Object(ObjectType type, Item* item = new Item());
	Object(Object* object);
	~Object();
	Item* Search();
	std::string GetName();
	void DeleteHiddenItem();
};

//Object table;
//Object chest = Object(Chest, Item("TestItem"));
//Object cupboard;