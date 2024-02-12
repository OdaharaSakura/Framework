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
	int m_buyingPrice{};
	int m_sellingPrice{};
};


struct EquipmentData
{
	std::string m_Type{};
	std::string m_Key{};
	std::string m_TexturePass{};
	std::string m_Name{};
	std::string m_Description{};
	int m_buyingPrice{};
	int m_sellingPrice{};
};

class ItemDataContainer
{
private:
	static std::vector<ItemData> m_ItemData; // \‘¢‘Ì‚ÌƒŠƒXƒg‚ğ•Û
public:
	//scene‚É‚æ‚Á‚Ä‚Ç‚ê‚ğ“Ç‚İ‚Ş‚©‚ğŒˆ‚ß‚é
	static void Load();

	static ItemData GetItemData_Key(std::string key);
};