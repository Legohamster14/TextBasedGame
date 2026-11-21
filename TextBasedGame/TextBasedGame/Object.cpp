#include "Object.h"
#include <iostream>

Object::Object()
{
	m_hiddenItem = new Item();
}

Object::Object(ObjectType type, Item* item)
{
	switch (type)
	{
	case Chest:
		m_objectName = "Chest";
		m_searchText = "You look in the ";
		break;
	case ObjectType::Cabinet:
		m_objectName = "Cabinet";
		m_searchText = "You look in the ";
		break;
	case ObjectType::Carpet:
		m_objectName = "Carpet";
		m_searchText = "You look under the ";
		break;
	case ObjectType::Table:
		m_objectName = "Table";
		m_searchText = "You look on the ";
		break;
	}
	switch (item->GetItemType())
	{
	case ItemType::DefaultItemType:
	{
		m_hiddenItem = new Item(item);
	}
	break;
	case ItemType::PotionType:
	{
		HealthPotion* tempPotionPtr = (HealthPotion*)item;
		m_hiddenItem = new HealthPotion(tempPotionPtr);
	}
	break;
	case ItemType::MagicScrollType:
	{
		MagicScroll* tempMagicScrollPtr = (MagicScroll*)item;
		m_hiddenItem = new MagicScroll(tempMagicScrollPtr);
	}
	break;
	case ItemType::KeyType:
	{
		Key* tempKeyPtr = (Key*)item;
		m_hiddenItem = new Key(tempKeyPtr);
	}
	break;
	case ItemType::WeaponType:
	{
		Weapon* tempWeaponPtr = (Weapon*)item;
		m_hiddenItem = new Weapon(tempWeaponPtr);
	}
	break;
	}


	//m_hiddenItem = new Item(item);
}

Object::Object(Object* object)
{
	m_objectName = object->m_objectName;
	m_searchText = object->m_searchText;
	m_hiddenItem = object->m_hiddenItem;
}

Object::~Object()
{
}

Item* Object::Search()
{
	std::cout << '-' << m_searchText << m_objectName << ((m_hiddenItem->GetName() == "Empty") ? (" and find nothing.\n") : (" and find " + m_hiddenItem->GetName())) << std::endl;
	return m_hiddenItem;
}

std::string Object::GetName()
{
	return m_objectName;
}

void Object::DeleteHiddenItem()
{
	delete m_hiddenItem;
}
