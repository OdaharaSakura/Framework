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

bool Inventory::AddItem(const Item& item)
{
    if (m_PossessionItems.size() < maxCapacity)
    {
        m_PossessionItems.push_back(item);
        return true;
    }
    return false;
}

bool Inventory::RemoveItem(const std::string& itemName)
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
