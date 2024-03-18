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
#include "item.h"
#include "subPanel.h"
#include "subPanelOptions.h"
#include "subPanelSellingItem.h"
#include "sceneDescription.h"


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
	m_SelectPanelOptions = scene->AddGameObject<SubPanelOptions>(LAYER_OBJECT_2D);
	m_InventoryItemCursor = scene->AddGameObject<InventoryItemCursor>(LAYER_OBJECT_2D);




	m_InventoryPanel->SetIsActive(false);
	m_SelectPanel->SetIsActive(false);
	m_InventoryItemCursor->SetIsActive(false);

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
	auto & items = m_InventoryInterface->GetItems();

	for (int i = 0; i < items.size(); i++)
	{
		if (m_InventoryItemIcons[i] == nullptr) return;
		m_InventoryItemIcons[i]->SetIndex(i);
	}
}

void InventoryView::ShowInventory()
{
	Scene* scene = Manager::GetScene();
	m_InventoryInterface = scene->GetGameObject<Inventory>();
	auto& items = m_InventoryInterface->GetItems();
	for (int i = 0; i < items.size(); i++)
	{
		if (m_InventoryItemIcons[i] == nullptr) return;
		m_InventoryItemIcons[i]->SetIndex(i);
		m_InventoryItemIcons[i]->SetIsActive(true);
		m_InventoryItemIcons[i]->SetTextureEnable(true);
	}
	m_InventoryPanel->SetIsActive(true);
	m_InventoryItemCursor->SetIsActive(true);
	m_InventoryItemDescription = scene->AddGameObject<InventoryItemDescription>(LAYER_OBJECT_2D);

	scene->GetGameObject<SceneDescription>()->SetDescriptionText("Lキー：決定・Kキー：戻る・Tabキー：閉じる");

	m_IsInventoryActive = true;
	
}

void InventoryView::HideInventory()
{
	Scene* scene = Manager::GetScene();
	for (int i = 0; i < m_InventoryInterface->GetItems().size(); i++)
	{
		m_InventoryItemIcons[i]->SetIsActive(false);
		m_InventoryItemIcons[i]->SetTextureEnable(false);
	}
	
	m_InventoryPanel->SetIsActive(false);
	m_InventoryItemCursor->SetSelectItem();
	m_InventoryItemCursor->SetIsActive(false);
	m_InventoryItemDescription->SetDestroy();

	HideSelectPanel();
	scene->GetGameObject<SceneDescription>()->SetDescriptionText("");

	m_IsInventoryActive = false;
}

void InventoryView::ShowSelectPanel(Item* itemPtr)
{
	if (!itemPtr) return;

	SubPanelOptionTypes type{};

	if (itemPtr->GetType() == "そうび")
	{
		type = Inventory_Equipment;
	}
	else if (itemPtr->GetIsEat())
	{
		type = Inventory_Eat;
	}
	else
	{
		type = Inventory_NoUse;
	}


	m_SelectPanel->SetIsActive(true);
	m_SelectPanelOptions->SetIsActive(true);
	m_SelectPanelOptions->SetTypes(type);
}


void InventoryView::HideSelectPanel()
{
	m_SelectPanel->SetIsActive(false);
	m_SelectPanelOptions->SetIsActive(false);
}

void InventoryView::ShowSellingItemSubPanel()
{
	Scene* scene = Manager::GetScene();
	m_SubPanelSellingItem = scene->AddGameObject<SubPanelSellingItem>(LAYER_OBJECT_2D);
}

void InventoryView::HideSellingItemSubPanel()
{
	m_SubPanelSellingItem->SetDestroy();
}
