#pragma once
#include "GameObject.h"

class Item;
class InventoryItemCursor :public GameObject
{
private:
	enum SelectStage
	{
		SelectItem,
		SelectHowToUse
	};

	class StaticSprite* m_StaticSprite{};
	class Inventory* m_Inventory{};
	class InventoryView* m_InventoryView{};

	int m_SelectItemIndex{};
	int m_SelectHowToUseIndex{};
	int m_SelectStage{};

	float m_SelectItemTextureWidth = 100.0f;
	float m_SelectItemTextureHeight = 100.0f;
	std::string m_SelectItemTextureKey{};
	std::string m_SelectItemTexturePass{};


	float m_SelectHowToUseTextureWidth = 240.0f;
	float m_SelectHowToUseTextureHeight = 240.0f;
	std::string m_SelectHowToUseTextureKey{};
	std::string m_SelectHowToUseTexturePass{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void UpdateSelectItem();
	void UpdateSelectHowToUse(Item* item);

	

	void SetSelectHowToUse();
	void SetSelectItem();

	int GetSelectItemIndex() { return m_SelectItemIndex; }
	Item* GetSelectItem();

};