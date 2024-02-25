#pragma once
#include "main.h"
#include <vector>

struct TimeData
{
	int Month;
	int Day;
	int Hours;
	int Minutes;
};

struct FarmData
{
	int Money;
	int Water;
	int Fertilizer;
};

// セーブデータ構造体
struct SaveData
{
	TargetBreakingMode TargetBreaking;
	KumiteMode KumiteNormal;
	KumiteMode KumiteHard;
};
