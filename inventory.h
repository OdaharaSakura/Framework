#pragma once
#include "gameObject.h"
#include "item.h"
#include "savedata.h"
#include <vector>

class Inventory : public GameObject
{
private:
    std::vector<Item> m_PossessionItems;
    int maxCapacity = 21;
	class InventoryView* m_InventoryView;
    int m_Money = 200;

public:
    void Init();
    void Show();
    void Hide();

    void AddItem(Item* itemptr);
    void AddItem(Item* itemptr, int quantity);

    void RemoveItem(Item* itemptr);
    void RemoveItem(std::string& itemKey);
    void RemoveItem(int index);

    void DecreaseItem(Item* itemptr);
    void DecreaseItem(Item* itemptr, int quantity);
    void DecreaseItem(std::string itemkey);
    void DecreaseItem(int index);
    void DecreaseItem(int index, int quantity);

    void SetMoney(int money) { m_Money = money; }
    void AddMoney(int money) { m_Money += money; }
    void DecreaseMoney(int money) { m_Money -= money; }


    std::vector<Item>& GetItems() { return m_PossessionItems; }
    std::vector<std::string>GetPossessionItemKeys();

    Item* GetItem(std::string itemkey);
    Item* GetItem(int index);

    int GetMaxCapacity() { return maxCapacity; }
    int GetMoney() { return m_Money; }

    void Load(PlayerData playerData);
};