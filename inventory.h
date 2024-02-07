#pragma once
#include "gameObject.h"
#include "item.h"
#include <vector>

class Inventory : public GameObject
{
private:
    std::vector<Item> m_PossessionItems;
    int maxCapacity;
	class InventoryView* m_InventoryView;//SOLIDŒ´‘¥‚Éˆá”½‚µ‚Ä‚¢‚é

public:
    void Init();
    void Show();
    void Hide();

    bool AddItem(Item& item);

    bool RemoveItem(const std::string& itemName);

    std::vector<Item>& GetItems() { return m_PossessionItems; }
};