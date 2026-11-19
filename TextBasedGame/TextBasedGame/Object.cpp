#include "Object.h"

Object::Object()
{
}

Object::Object(ObjectType type, Item item)
{
	switch (type)
	{
	case Chest:
		m_objectName = "Chest";
		m_searchText = "You look in ";
		break;
	}

	m_hiddenItem = item;
}

Object::~Object()
{
}

Item* Object::Search()
{
	std::cout << m_searchText << m_objectName << ((m_hiddenItem.GetName() == "Empty") ? (" and find nothing.\n") : (" and find " + m_hiddenItem.GetName())) << std::endl;
	return &m_hiddenItem;
}

std::string Object::GetName()
{
	return m_objectName;
}
