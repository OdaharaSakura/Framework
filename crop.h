#pragma once
#include "item.h"
#include <vector>

enum CropState {
	None,//Ç»Çµ
	Seed,//éÌ
	Seedling1,//ê¨í∑
	Harvest,//é˚än
};

class Crop
{
protected:
	std::string m_Key{};
	std::string m_TexturePass{};
	int m_GrowthTime{};
	int m_GrowthTimeToFirstState{};
	int m_GrowthTimeToHarvest{};
	std::string m_FirstStateModelPass{};
	std::string m_HarvestModelPass{};

	CropState m_CropState{};

public:
	Crop(
		std::string key,
		std::string texturePass,
		int growthTime,
		int growthTimeToFirstState,
		int growthTimeToHarvest,
		std::string firstStateModelPass,
		std::string harvestModelPass
		): 
		m_Key(key),
		m_TexturePass(texturePass),
		m_GrowthTime(growthTime),
		m_GrowthTimeToFirstState(growthTimeToFirstState),
		m_GrowthTimeToHarvest(growthTimeToHarvest),
		m_FirstStateModelPass(firstStateModelPass),
		m_HarvestModelPass(harvestModelPass) {
		m_CropState = CropState::None;
	};
	~Crop() {};

	std::string GetKey() { return m_Key; }
	std::string GetTexturePass() { return m_TexturePass; }
	int GetGrowthTime() { return m_GrowthTime; }
	int GetGrowthTimeToFirstState() { return m_GrowthTimeToFirstState; }
	int GetGrowthTimeToHarvest() { return m_GrowthTimeToHarvest; }
	std::string GetFirstStateModelPass() { return m_FirstStateModelPass; }
	std::string GetHarvestModelPass() { return m_HarvestModelPass; }

	void SetCropState(CropState state) { m_CropState = state; }
	CropState GetCropState() { return m_CropState; }
};

