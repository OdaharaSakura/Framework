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

// �Z�[�u�f�[�^�\����
struct SaveData
{
	TargetBreakingMode TargetBreaking;
	KumiteMode KumiteNormal;
	KumiteMode KumiteHard;
};
