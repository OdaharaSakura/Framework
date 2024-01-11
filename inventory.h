#pragma once
#include "item.h"
#include <vector>

class Inventory
{
private:
    std::vector<Item> items;
    int maxCapacity;

public:
    Inventory(int capacity) : maxCapacity(capacity) {}

    bool AddItem(const Item& item)
    {
        if (items.size() < maxCapacity)
        {
            items.push_back(item);
            return true;
        }
        return false;
    }

    bool RemoveItem(const std::string& itemName)
    {
        for (auto it = items.begin(); it != items.end(); ++it)
        {
            if (it->GetName() == itemName)
            {
                items.erase(it);
                return true;
            }
        }
        return false;
    }

    const std::vector<Item>& GetItems() const { return items; }
};
