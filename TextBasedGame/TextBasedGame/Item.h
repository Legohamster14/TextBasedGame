#pragma once
#include <string>


class Item
{
private:
	std::string m_itemName;
public:
	Item();
	Item(std::string name);
	Item(Item* input);
	std::string GetName();
};

class Potions : public Item
{

};

class MagicSrolls : public Item
{

};

class Keys : public Item
{

};

class Weapons : public Item
{

};