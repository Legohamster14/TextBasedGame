#include "Item.h"
#include <iostream>

//Item
Item::~Item()
{
}

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
	m_itemType = input->m_itemType;
}

std::string Item::GetName()
{
	return m_itemName;
}

ItemType Item::GetItemType()
{
	return m_itemType;
}

//HealthPotion
HealthPotion::~HealthPotion()
{
}

HealthPotion::HealthPotion() : Item()
{
	m_itemName = "Empty";
	m_itemType = ItemType::PotionType;
}

HealthPotion::HealthPotion(HealthPotion* input) : Item(input)
{
	m_healthAmount = input->m_healthAmount;
	m_itemType = ItemType::PotionType;
}

HealthPotion::HealthPotion(std::string name, int health) : Item(name)
{
	m_itemName = name;
	m_healthAmount = health;
	m_itemType = ItemType::PotionType;
}

int HealthPotion::GetHealthAmount()
{
	return m_healthAmount;
}

//Magic Scroll
MagicScroll::~MagicScroll()
{
}

MagicScroll::MagicScroll()
{
	m_itemName = "Empty";
	m_itemType = ItemType::MagicScrollType;
}

MagicScroll::MagicScroll(ScrollType type)
{
	m_itemType = ItemType::MagicScrollType;
	switch (type)
	{
	case Fireball:
		m_itemName = "Fireball_Scroll";
		m_scrollType = ScrollType::Fireball;
		m_scrollTypeText = "Fireball";
		break;
	case Lightning:
		m_itemName = "Lightning_Scroll";
		m_scrollType = ScrollType::Lightning;
		m_scrollTypeText = "Lightning Bolt";
		break;
	case IceSpike:
		m_itemName = "IceSpike_Scroll";
		m_scrollType = ScrollType::IceSpike;
		m_scrollTypeText = "Ice Spike";
		break;
	case Earthquake:
		m_itemName = "Earthquake_Scroll";
		m_scrollType = ScrollType::Earthquake;
		m_scrollTypeText = "Earthquake";
		break;
	}
}

MagicScroll::MagicScroll(MagicScroll* input)
{
	m_itemType = ItemType::MagicScrollType;
	m_itemName = input->m_itemName;
	m_scrollType = input->m_scrollType;
	m_scrollTypeText = input->m_scrollTypeText;
}

ScrollType MagicScroll::GetScrollType()
{
	return m_scrollType;
}

std::string MagicScroll::GetScrollTypeText()
{
	return m_scrollTypeText;
}

//Key
Key::~Key()
{
}

Key::Key()
{
	m_itemName = "Empty";
	m_itemType = ItemType::KeyType;
}

Key::Key(KeyColour colour)
{
	m_itemType = ItemType::KeyType;
	switch (colour)
	{
	case KeyColour::Red:
		m_itemName = "Red_Key";
		m_keyColour = KeyColour::Red;
		break;
	case KeyColour::Blue:
		m_itemName = "Blue_Key";
		m_keyColour = KeyColour::Blue;
		break;
	case KeyColour::Purple:
		m_itemName = "Purple_Key";
		m_keyColour = KeyColour::Purple;
		break;
	}
}

Key::Key(Key* input)
{
	m_itemType = ItemType::KeyType;
	m_itemName = input->m_itemName;
	m_keyColour = input->m_keyColour;
}

KeyColour Key::GetKeyColour()
{
	return m_keyColour;
}

//Weapon
Weapon::~Weapon()
{
}

Weapon::Weapon()
{
	m_itemName = "Empty";
	m_itemType = ItemType::WeaponType;
}

Weapon::Weapon(std::string name, int damage)
{
	m_itemType = ItemType::WeaponType;
	m_itemName = name;
	m_damage = damage;
}

Weapon::Weapon(Weapon* input)
{
	m_itemType = ItemType::WeaponType;
	m_itemName = input->m_itemName;
	m_damage = input->m_damage;
}

int Weapon::GetWeaponDamage()
{
	return m_damage;
}
