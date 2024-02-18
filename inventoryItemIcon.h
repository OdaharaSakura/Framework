#pragma once
#include "GameObject.h"

class Inventory;
class Item;

class InventoryItemIcon :public GameObject
{
private:
	class StaticSprite* m_StaticSprite{};
	Inventory* m_Inventory{};
	Item* m_Item{};
	int m_Index{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetIndex(int itemIndex);
	void SetTextureEnable(bool isEnable);

	Item* GetItem() { return m_Item; }
	int GetIndex() { return m_Index; }
};