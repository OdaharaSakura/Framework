#pragma once
#include "item.h"
#include <vector>


class Equipment : public Item
{
public:
	virtual void Execute() {};
};

//�L
#pragma region Hoe 
class Hoe : public Equipment
{
public:
	void Execute() override{};
};
#pragma endregion

//���傤��
#pragma region WateringCan 
class WateringCan : public Equipment
{
public:
	void Execute() override {};
};
#pragma endregion