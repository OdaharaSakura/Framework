#pragma once
#include "gameObject.h"
#include "item.h"
#include <vector>

class Inventory : public GameObject
{
private:
    std::vector<Item> m_PossessionItems;
    int maxCapacity = 21;
	class InventoryView* m_InventoryView;

public:
    void Init();
    void Show();
    void Hide();

    bool AddItem(const Item* itemptr);

    bool RemoveItem(std::string& itemName);

    std::vector<Item>& GetItems() { return m_PossessionItems; }

    Item* GetItem(std::string& itemName);

    Item* GetItem(int index);

    int GetMaxCapacity() { return maxCapacity; }
};