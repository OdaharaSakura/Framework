#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "shader.h"
#include "inventoryView.h"
#include "inventory.h"
#include "inventoryPanel.h"
#include "inventoryItemIcon.h"
#include "inventoryItemCursor.h"
#include "inventoryItemDescription.h"
#include "SubPanel.h"

void InventoryView::Init()
{
	Scene* scene = Manager::GetScene();
	m_InventoryInterface = scene->GetGameObject<Inventory>();
	m_InventoryPanel = scene->AddGameObject<InventoryPanel>(LAYER_OBJECT_2D);
	for (int i = 0; i < m_InventoryInterface->GetMaxCapacity(); i++)
	{
		m_InventoryItemIcons.push_back(scene->AddGameObject<InventoryItemIcon>(LAYER_OBJECT_2D));
		m_InventoryItemIcons[i]->SetIsActive(false);
	}
	m_SelectPanel = scene->AddGameObject<SubPanel>(LAYER_OBJECT_2D);
	m_InventoryItemCursor = scene->AddGameObject<InventoryItemCursor>(LAYER_OBJECT_2D);




	m_InventoryPanel->SetIsActive(false);
	m_InventoryItemCursor->SetIsActive(false);
	m_SelectPanel->SetIsActive(false);

}


void InventoryView::Uninit()
{
	//基底クラスのメソッド呼び出し
	GameObject::Uninit();
}

void InventoryView::Update()
{
	//基底クラスのメソッド呼び出し
	GameObject::Update();

	for (int i = 0; i < m_InventoryInterface->GetItems().size(); i++)
	{
		if (m_InventoryItemIcons[i] == nullptr) return;
		m_InventoryItemIcons[i]->SetIndex(i);
	}
}

void InventoryView::ShowInventory()
{
	Scene* scene = Manager::GetScene();
	m_InventoryInterface = scene->GetGameObject<Inventory>();
	for (int i = 0; i < m_InventoryInterface->GetItems().size(); i++)
	{
		if (m_InventoryItemIcons[i] == nullptr) return;
		m_InventoryItemIcons[i]->SetIndex(i);
		m_InventoryItemIcons[i]->SetIsActive(true);
	}
	m_InventoryPanel->SetIsActive(true);
	m_InventoryItemCursor->SetIsActive(true);
	m_InventoryItemDescription = scene->AddGameObject<InventoryItemDescription>(LAYER_OBJECT_2D);
	
}

void InventoryView::HideInventory()
{
	for (int i = 0; i < m_InventoryInterface->GetItems().size(); i++)
	{
		m_InventoryItemIcons[i]->SetIsActive(false);
	}
	
	m_InventoryPanel->SetIsActive(false);
	m_InventoryItemCursor->SetIsActive(false);
	m_InventoryItemDescription->SetDestroy();
}

void InventoryView::ShowSelectPanel()
{
	m_SelectPanel->SetIsActive(true);
}

void InventoryView::HideSelectPanel()
{
	m_SelectPanel->SetIsActive(false);
}
