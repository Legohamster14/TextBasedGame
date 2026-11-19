#pragma once
#include <string>

enum ItemType
{
	DefaultItem, Potion, MagicScroll, Key, Weapon
};

class Item
{
private:
	ItemType m_itemType = ItemType::DefaultItem;
protected:
	std::string m_itemName;
public:
	~Item();
	Item();
	Item(std::string name);
	Item(Item* input);
	std::string GetName();
};

class HealthPotion : public Item
{
private:
	ItemType m_itemType = ItemType::Potion;
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
	ItemType m_itemType = ItemType::MagicScroll;
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
	None, Red, Blue, Purple, Green
};

class Key : public Item
{
private:
	ItemType m_itemType = ItemType::Key;
	KeyColour m_keyColour = KeyColour::None;
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
	ItemType m_itemType = ItemType::Weapon;
	int m_damage = 0;
public:
	~Weapon();
	Weapon();
	Weapon(std::string name, int damage);
	Weapon(Weapon* input);
	int GetWeaponDamage();
};