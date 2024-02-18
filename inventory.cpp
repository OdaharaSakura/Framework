#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "player.h"
#include "inventory.h"
#include "inventoryView.h"

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
    for (auto it = m_PossessionItems.begin(); it != m_PossessionItems.end(); ++it)
    {
        if (it->GetName() == itemptr->GetName())
        {
            m_PossessionItems.erase(it);
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

Item* Inventory::GetItem(std::string& itemName)
{
    for (auto it = m_PossessionItems.begin(); it != m_PossessionItems.end(); ++it)
    {
        if (it->GetName() == itemName)
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
