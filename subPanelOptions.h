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

enum SelectOptions
{
	Special,
	LiftUp,
	ThrowAway
};

class SubPanelOptions :public GameObject
{
private:
	class StaticSprite* m_StaticSprite{};

	SubPanelOptionTypes m_OptionType;


	std::map<SubPanelOptionTypes, std::string> m_TextureKeys{};
	std::map<SubPanelOptionTypes, std::string> m_TexturePasses{};
	std::map<SubPanelOptionTypes, int> m_OptionCounts{};//ëIëéàÇÃêî

	//íËêîíl
	static const int EquipmentOptionTypes_Max = 3;
	static const int EatOptionTypes_Max = 3;
	static const int NoUseOptionTypes_Max = 2;
public:


	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetTypes(SubPanelOptionTypes type);

	int GetOptionsCount();

	void SetSelectOption(int index, class Item* itemPtr);
};