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
	int m_LostHP{}; //�g�p�������Ɍ���HP
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
	static std::vector<ItemData> m_ItemData; // �\���̂̃��X�g��ێ�
	static std::vector<EquipmentData> m_EquipmentData; // �\���̂̃��X�g��ێ�
	static std::vector<CropData> m_CropData; // �\���̂̃��X�g��ێ�
public:
	//scene�ɂ���Ăǂ��ǂݍ��ނ������߂�
	static void Load();

	static ItemData GetItemData_Key(std::string key);
	static EquipmentData GetEquipmentData_Key(std::string key);
	static CropData GetCropData_Key(std::string key);
};