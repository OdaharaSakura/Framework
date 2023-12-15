#pragma once
#include "gameObject.h"

#include <iostream>
#include <string>

enum MonthType
{
	Spring,
	Summer,
	Autumn,
	Winter
};


class Time : public GameObject
{
private:
	std::string m_month{};
	std::string m_time{};

	int m_Month = MonthType::Spring;
	int m_Hours = 6;
	int m_Minutes{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};
