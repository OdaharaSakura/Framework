#pragma once
#include "item.h"

class ItemFactory
{
public:
	ItemFactory() {};
	~ItemFactory() {};



	Item* CreateItem(std::string key);
};