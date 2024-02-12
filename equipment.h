#pragma once
#include "item.h"
#include <vector>


class Equipment : public Item
{
	std::string m_Modelpass;
public:
	void Init() {};
	virtual void Execute() {};
};

//ŒL
#pragma region Hoe 
class Hoe : public Equipment
{
public:
	void Init() {};
	void Execute() override{};
};
#pragma endregion

