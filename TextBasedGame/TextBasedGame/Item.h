#pragma once
#include <string>

enum ItemType
{
	DefaultItemType, PotionType, MagicScrollType, KeyType, WeaponType
};

class Item
{
private:
	ItemType m_itemType = ItemType::DefaultItemType;
protected:
	std::string m_itemName;
public:
	~Item();
	Item();
	Item(std::string name);
	Item(Item* input);
	std::string GetName();
	ItemType GetItemType();
};

class HealthPotion : public Item
{
private:
	ItemType m_itemType = ItemType::PotionType;
	int m_healthAmount = 0;
public:
	~HealthPotion();
	HealthPotion();
	HealthPotion(HealthPotion* input);
	HealthPotion(std::string name, int health);
	int GetHealthAmount();
};

enum ScrollType
{
	None, Fireball, Lightning, IceSpike, Earthquake
};

class MagicScroll : public Item
{
private:
	ItemType m_itemType = ItemType::MagicScrollType;
	ScrollType m_scrollType = ScrollType::None;
	std::string m_scrollTypeText = "";
public:
	~MagicScroll();
	MagicScroll();
	MagicScroll(ScrollType type);
	MagicScroll(MagicScroll* input);
	ScrollType GetScrollType();
	std::string GetScrollTypeText();
};

enum KeyColour
{
	Blank, Red, Blue, Purple, Green
};

class Key : public Item
{
private:
	ItemType m_itemType = ItemType::KeyType;
	KeyColour m_keyColour = KeyColour::Blank;
public:
	~Key();
	Key();
	Key(KeyColour colour);
	Key(Key* input);
	KeyColour GetKeyColour();
};

class Weapon : public Item
{
private:
	ItemType m_itemType = ItemType::WeaponType;
	int m_damage = 0;
public:
	~Weapon();
	Weapon();
	Weapon(std::string name, int damage);
	Weapon(Weapon* input);
	int GetWeaponDamage();
};