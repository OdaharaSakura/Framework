#pragma once
#include "item.h"

class ItemFactory
{
public:
	ItemFactory() {};
	~ItemFactory() {};



	const Item* CreateItem(std::string key);
};