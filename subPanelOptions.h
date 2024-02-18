#pragma once
#include "GameObject.h"

#include <string>
#include <map>
enum SubPanelOptionTypes
{
	None,
	Inventory_Equipment,
	Inventory_Eat,
	Inventory_NoUse
};

class SubPanelOptions :public GameObject
{
private:
	class StaticSprite* m_StaticSprite{};

	SubPanelOptionTypes m_OptionType;


	std::map<SubPanelOptionTypes, std::string> m_TextureKeys{};
	std::map<SubPanelOptionTypes, std::string> m_TexturePasses{};
	std::map<SubPanelOptionTypes, int> m_OptionCounts{};//ëIëéàÇÃêî
public:


	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetTypes(SubPanelOptionTypes type);

	int GetOptionsCount();
};