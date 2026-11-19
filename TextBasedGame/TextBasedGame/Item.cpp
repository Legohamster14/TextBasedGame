#include "Item.h"

Item::Item()
{
	m_itemName = "Empty";
}

Item::Item(std::string name)
{
	m_itemName = name;
}

Item::Item(Item* input)
{
	m_itemName = input->m_itemName;
}

std::string Item::GetName()
{
	return m_itemName;
}
