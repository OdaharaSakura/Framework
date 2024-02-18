#pragma once
#include "GameObject.h"
#include <vector>

class InventoryItemIcon;
class InventoryView :public GameObject
{
private:
	class Inventory* m_InventoryInterface{};
	class InventoryPanel* m_InventoryPanel{};
	class InventoryItemCursor* m_InventoryItemCursor{};
	class InventoryItemDescription* m_InventoryItemDescription{};
	std::vector<InventoryItemIcon*> m_InventoryItemIcons{};

	class SubPanel* m_SelectPanel{};
	class SubPanelOptions* m_SelectPanelOptions{};

	bool m_IsInventoryActive{};
public:
	void Init();
	void Uninit();
	void Update();

	void SetInventoryInterface(class Inventory* inventory) { m_InventoryInterface = inventory; }
	void ShowInventory();
	void HideInventory();

	void ShowSelectPanel(class Item* itemPtr);
	void HideSelectPanel();

	InventoryItemIcon* GetInventoryItemIcon(int index) 
	{
		if (index < m_InventoryItemIcons.size())
		{
			return m_InventoryItemIcons[index];
		}
		else
		{
			return nullptr;
		}
	}

	bool IsInventoryActive() { return m_IsInventoryActive; }
};