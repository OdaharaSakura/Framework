#pragma once
#include "GameObject.h"

class Item;
class InventoryItemCursor :public GameObject
{
private:
	class StaticSprite* m_StaticSprite{};
	class Inventory* m_Inventory{};
	class InventoryView* m_InventoryView{};

	int m_Index{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	int GetIndex() { return m_Index; }
	Item* GetSelectItem();

};