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
};


struct EquipmentData
{
	std::string m_Type{};
	std::string m_Key{};
	std::string m_TexturePass{};
	std::string m_Name{};
	std::string m_Description{};
	int m_BuyingPrice{};
	int m_SellingPrice{};
	std::string m_ModelPass{};
	int m_LostHP{}; //使用した時に減るHP
};

struct CropData
{
	std::string m_Type{};
	std::string m_Key{};
	std::string m_TexturePass{};
	std::string m_Name{};
	std::string m_Description{};
	int m_BuyingPrice{};
	int m_SellingPrice{};
	bool m_IsEat{};
	int m_GrowthTime{};
	std::string m_Season{};
	int m_GrowTheFirstStage{};
	int m_GrowTheSecondStage{};
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
	static EquipmentData GetEquipmentData_Key(std::string key);
	static CropData GetCropData_Key(std::string key);
};