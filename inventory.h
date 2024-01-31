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
    void Uninit();
    void Update();
    void Draw();


    bool AddItem(const Item& item)
    {
        if (m_PossessionItems.size() < maxCapacity)
        {
            m_PossessionItems.push_back(item);
            return true;
        }
        return false;
    }

    bool RemoveItem(const std::string& itemName)
    {
        for (auto it = m_PossessionItems.begin(); it != m_PossessionItems.end(); ++it)
        {
            if (it->GetName() == itemName)
            {
                m_PossessionItems.erase(it);
                return true;
            }
        }
        return false;
    }

    const std::vector<Item>& GetItems() const { return m_PossessionItems; }
};
