#pragma once
#include "item.h"
#include <vector>


class Equipment : public Item
{
public:
	virtual void Execute() {};
};

//ŒL
#pragma region Hoe 
class Hoe : public Equipment
{
public:
	void Execute() override{};
};
#pragma endregion

//‚¶‚å‚¤‚ë
#pragma region WateringCan 
class WateringCan : public Equipment
{
public:
	void Execute() override {};
};
#pragma endregion