#pragma once
#include "GameObject.h"

class InventoryView :public GameObject
{
private:
	class Inventory* m_InventoryInterface;
	class InventoryPanel* m_InventoryPanel;
	class InventoryItemIcon* m_InventoryItemIcon;
	class InventoryItemCursor* m_InventoryItemCursor;
public:
	void Init();
	void Uninit();
	void Update();

	void SetInventoryInterface(class Inventory* inventory) { m_InventoryInterface = inventory; }
	void ShowInventory();
	void HideInventory();
};