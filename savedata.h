#pragma once
#include "main.h"
#include <string>
#include <vector>

struct TimeData
{
	int month;
	int day;
	int hour;
	int minute;
};

struct FarmTileData
{
	std::string cropKey;
	int tileStage;
	int cropStage;
	int growthMinute;
};

struct PlayerData
{
	int money;
	float positionx;
	float positiony;
	float positionz;
	std::vector<std::string> possessionItemKeys;
	std::string equipmentItemKey;
};


struct SaveData
{
	TimeData timeData;
	PlayerData playerData;
	std::vector<FarmTileData> farmTileData;
};