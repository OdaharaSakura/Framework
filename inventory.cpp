#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "inventory.h"
#include "inventoryView.h"
#include "itemFactory.h"

void Inventory::Init()
{
	m_InventoryView = Manager::GetScene()->AddGameObject<InventoryView>(LAYER_OBJECT_NOTDRAW);
}

void Inventory::Show()
{
    Scene* scene = Manager::GetScene();
    if (scene->GetGameObject<InventoryView>() == nullptr)
    {
        m_InventoryView = scene->AddGameObject<InventoryView>(LAYER_OBJECT_NOTDRAW);
        m_InventoryView->ShowInventory();
    }
    else
    {
        m_InventoryView->ShowInventory();
    }
    
}

void Inventory::Hide()
{
    if (m_InventoryView == nullptr) return;

    m_InventoryView->HideInventory();
}

void Inventory::AddItem(Item* itemptr)
{
    if (m_PossessionItems.size() < 0) return;
        if (m_PossessionItems.size() >= maxCapacity)//範囲外
    {
        //TODO：入りきらないことを表示する
        return;
    }

    for (auto it = m_PossessionItems.begin(); it != m_PossessionItems.end(); ++it)//すでにアイテムにあるか
    {
        if (it->GetName() == itemptr->GetName())
        {
            it->AddQuantity(1);
            return;
        }
    }

    Item item = *itemptr;
    if (m_PossessionItems.size() < maxCapacity)
    {
        m_PossessionItems.push_back(item);
    }
}


void Inventory::AddItem(Item* itemptr, int quantity)
{
    if (m_PossessionItems.size() >= maxCapacity)//範囲外
    {
        //TODO：入りきらないことを表示する
        return;
    }

    for (auto it = m_PossessionItems.begin(); it != m_PossessionItems.end(); ++it)//すでにアイテムにあるか
    {
        if (it->GetName() == itemptr->GetName())
        {
            it->AddQuantity(quantity);
            return;
        }
    }

    Item item = *itemptr;
    if (m_PossessionItems.size() < maxCapacity)
    {
        m_PossessionItems.push_back(item);
    }
}

void Inventory::RemoveItem(Item* itemptr)
{
    if (!itemptr) return;
    for (auto it = m_PossessionItems.begin(); it != m_PossessionItems.end(); ++it)
    {
        if (it->GetName() == itemptr->GetName())
        {
            m_PossessionItems.erase(it);
            break;
        }
    }
}

void Inventory::RemoveItem(std::string& itemName)
{
    for (auto it = m_PossessionItems.begin(); it != m_PossessionItems.end(); ++it)
    {
        if (it->GetName() == itemName)
        {
            m_PossessionItems.erase(it);
            break;
        }
    }
}

void Inventory::RemoveItem(int index)
{
    if (index < 0 || index >= m_PossessionItems.size())//範囲外
    {
        return;
    }

    m_PossessionItems.erase(m_PossessionItems.begin() + index);
}

void Inventory::DecreaseItem(Item* itemptr)
{
    if (m_PossessionItems.size() <= 0)//範囲外
    {
        //インベントリにアイテムが０
        return;
    }

    for (auto it = m_PossessionItems.begin(); it != m_PossessionItems.end(); ++it)//すでにアイテムにあるか
    {
        if (it->GetName() == itemptr->GetName())
        {
            it->SubQuantity(1);
        }
    }

    if (itemptr->GetQuantity() <= 0)
    {
        RemoveItem(itemptr);
    }
}

void Inventory::DecreaseItem(int index)
{
    if (m_PossessionItems.size() <= 0)//範囲外
    {
        //インベントリにアイテムが０
        return;
    }

    if (index < m_PossessionItems.size())
    {
        m_PossessionItems[index].SubQuantity(1);
    }

    if (m_PossessionItems[index].GetQuantity() <= 0)
    {
        RemoveItem(index);
    }
}

void Inventory::DecreaseItem(int index, int quantity)
{
    if (m_PossessionItems.size() <= 0)//範囲外
    {
        //インベントリにアイテムが０
        return;
    }

    if (index < m_PossessionItems.size())
    {
        m_PossessionItems[index].SubQuantity(quantity);
    }

    if (m_PossessionItems[index].GetQuantity() <= 0)
    {
        RemoveItem(index);
    }
}

std::vector<std::string> Inventory::GetPossessionItemKeys()
{
    std::vector<std::string> keys;
    for (auto it = m_PossessionItems.begin(); it != m_PossessionItems.end(); ++it)
    {
		keys.push_back(it->GetKey());
	}
	return keys;
}

Item* Inventory::GetItem(std::string itemkey)
{
    for (auto it = m_PossessionItems.begin(); it != m_PossessionItems.end(); ++it)
    {
        if (it->GetKey() == itemkey)
        {
            return &(*it);
        }
    }
    return nullptr;
}

Item* Inventory::GetItem(int index)
{
    if (index < m_PossessionItems.size())
    {
		return &m_PossessionItems[index];
	}
	return nullptr;
}

void Inventory::Load(PlayerData playerData)
{
    if (playerData.possessionItemKeys.size() <= 0)
    {
        return;
    }

    ItemFactory* itemFactory = new ItemFactory();
        
    for(auto it = playerData.possessionItemKeys.begin(); it != playerData.possessionItemKeys.end(); ++it)
	{//TODO:アイテムの数も保存する
        Item* item = itemFactory->CreateItem(*it);
        AddItem(item);
	}
}
