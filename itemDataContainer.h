#pragma once
#include <string>
#include <vector>

struct ItemData
{
	std::string m_Type{};
	std::string m_Key{};
	std::string m_TexturePass{};
	std::string m_Name{};
	std::string m_Description{};
	int m_BuyingPrice{};
	int m_SellingPrice{};
	bool m_IsEat{};
	int m_Healing{};
};


struct EquipmentData
{
	std::string m_Key{};
	std::string m_TexturePass{};
	std::string m_ModelPass{};
	int m_LostHP{}; //使用した時に減るHP
};

struct CropData
{
	std::string m_Key{};
	std::string m_TexturePass{};
	int m_GrowthTime{};
	int m_GrowthTimeToFirstState{};
	int m_GrowthTimeToHarvest{};
	std::string m_FirstStateModelPass{};
	std::string m_HarvestModelPass{};
};
class ItemDataContainer
{
private:
	static std::vector<ItemData> m_ItemData; // 構造体のリストを保持
	static std::vector<EquipmentData> m_EquipmentData; // 構造体のリストを保持
	static std::vector<CropData> m_CropData; // 構造体のリストを保持
public:
	//sceneによってどれを読み込むかを決める
	static void Load();

	static ItemData GetItemData_Key(std::string key);
	static std::vector<ItemData> GetAllItemData() { return m_ItemData; }

	static EquipmentData GetEquipmentData_Key(std::string key);
	static std::vector<EquipmentData> GetAllEquipmentData() { return m_EquipmentData; }

	static CropData GetCropData_Key(std::string key);
	static std::vector<CropData> GetAllCropData() { return m_CropData; }
};