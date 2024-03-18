#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "shader.h"
#include "inventoryItemCursor.h"
#include "inventory.h"
#include "inventoryView.h"
#include "staticSprite.h"
#include "shader.h"
#include "input.h"
#include "item.h"
#include "subPanelOptions.h"
#include "subPanelSellingItem.h"

void InventoryItemCursor::Init()
{
	AddComponent<UnlitTexture>();

	m_Scale.x = m_SelectItemTextureWidth;
	m_Scale.y = m_SelectItemTextureHeight;
	m_WorldPosition.x = 225.0f + (m_SelectItemIndex % 7) * 125.0f;
	m_WorldPosition.y = 170.0f + (m_SelectItemIndex / 7) * 100.0f;
	m_SelectItemTextureKey = "InventoryItemIconCursor";
	m_SelectItemTexturePass = "sentaku_frame.dds";

	m_SelectHowToUseTextureKey = "SubPanelCursor";
	m_SelectHowToUseTexturePass = "subpanelCursor.dds";

	m_StaticSprite = AddComponent<StaticSprite>();//上のとどっちでもよい
	m_StaticSprite->Init(m_WorldPosition.x, m_WorldPosition.y, m_Scale.x, m_Scale.y, m_SelectItemTextureKey, m_SelectItemTexturePass);

	m_SelectStage = SelectItem;
}

void InventoryItemCursor::Uninit()
{
	//基底クラスのメソッド呼び出し
	GameObject::Uninit();
}

void InventoryItemCursor::Update()
{
	//基底クラスのメソッド呼び出し
	GameObject::Update();

	switch (m_SelectStage)
	{
	case SelectItem:
	case SelectSellingItem:
		UpdateSelectItem();
		break;

	case SelectHowToUse:
		UpdateSelectHowToUse(GetSelectItem());
		break;

	case SelectSellingItemQuantity:
		UpdateSelectSellingItem(GetSelectItem());
		break;

	default:
		break;
	}
}

void InventoryItemCursor::Draw()
{
	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//基底クラスのメソッド呼び出し
	GameObject::Draw();
}

void InventoryItemCursor::UpdateInventoryItemCursor()
{
	Scene* scene = Manager::GetScene();
	m_Inventory = scene->GetGameObject<Inventory>();
	m_InventoryView = scene->GetGameObject<InventoryView>();

	if (Input::GetKeyTrigger('W'))
	{
		m_SelectItemIndex -= 7;
		if (m_SelectItemIndex < 0)
		{
			m_SelectItemIndex += m_Inventory->GetMaxCapacity();
		}
	}

	if (Input::GetKeyTrigger('S'))
	{
		m_SelectItemIndex += 7;
		if (m_SelectItemIndex >= m_Inventory->GetMaxCapacity())
		{
			m_SelectItemIndex -= m_Inventory->GetMaxCapacity();
		}
	}

	if (Input::GetKeyTrigger('A'))
	{
		m_SelectItemIndex--;
		if (m_SelectItemIndex < 0)
		{
			m_SelectItemIndex += m_Inventory->GetMaxCapacity();
		}
	}

	if (Input::GetKeyTrigger('D'))
	{
		m_SelectItemIndex++;
		if (m_SelectItemIndex >= m_Inventory->GetMaxCapacity())
		{
			m_SelectItemIndex -= m_Inventory->GetMaxCapacity();
		}
	}

	m_WorldPosition.x = 227.5f + (m_SelectItemIndex % 7) * 120.0f;
	m_WorldPosition.y = 170.0f + (m_SelectItemIndex / 7) * 107.5f;
	m_StaticSprite->SetPosition(D3DXVECTOR2(m_WorldPosition.x, m_WorldPosition.y));
}

void InventoryItemCursor::UpdateSelectItem()
{
	UpdateInventoryItemCursor();

	if (Input::GetKeyTrigger('L'))
	{
		if (!GetSelectItem()) return;

		if (m_SelectStage == SelectSellingItem)
		{
			m_InventoryView->ShowSellingItemSubPanel();
			m_SelectStage = SelectSellingItemQuantity;

		}
		else
		{
			m_InventoryView->ShowSelectPanel(GetSelectItem());
			SetSelectHowToUse();
			m_SelectStage = SelectHowToUse;
		}
	}
}

void InventoryItemCursor::UpdateSelectHowToUse(Item* item)
{
	Scene* scene = Manager::GetScene();
	auto subPanelOptions = scene->GetGameObject<SubPanelOptions>();

	if (Input::GetKeyTrigger('W'))
	{
		m_SelectHowToUseIndex--;
		if (m_SelectHowToUseIndex < 0)
		{
			m_SelectHowToUseIndex = subPanelOptions->GetOptionsCount() - 1;
		}
	}

	if (Input::GetKeyTrigger('S'))
	{
		m_SelectHowToUseIndex++;
		if (m_SelectHowToUseIndex >= subPanelOptions->GetOptionsCount())
		{
			m_SelectHowToUseIndex = 0;
		}
	}

	m_WorldPosition.x = (SCREEN_WIDTH - m_Scale.x) / 2;
	m_WorldPosition.y = (SCREEN_HEIGHT - m_Scale.y) / 2 + (m_SelectHowToUseIndex * 50.0f);
	m_StaticSprite->SetPosition(D3DXVECTOR2(m_WorldPosition.x, m_WorldPosition.y));

	if (Input::GetKeyTrigger('L'))
	{
		subPanelOptions->SetSelectOption(m_SelectHowToUseIndex, item);
		Scene* scene = Manager::GetScene();
		m_InventoryView = scene->GetGameObject<InventoryView>();
		SetSelectItem();
		m_InventoryView->HideSelectPanel();
	}


	if (Input::GetKeyTrigger('K'))
	{
		Scene* scene = Manager::GetScene();
		m_InventoryView = scene->GetGameObject<InventoryView>();
		SetSelectItem();
		m_InventoryView->HideSelectPanel();
		m_SelectStage = SelectItem;
	}
}

void InventoryItemCursor::UpdateSelectSellingItem(Item* item)
{
	Scene* scene = Manager::GetScene();
	auto subPanelSellingItem = scene->GetGameObject<SubPanelSellingItem>();
	auto inventory = scene->GetGameObject<Inventory>();
	m_SelectSellingItemQuantity = 0;

	if (Input::GetKeyTrigger('W'))
	{
		m_SelectSellingItemQuantity--;
		if (m_SelectSellingItemQuantity < 0)
		{
			m_SelectSellingItemQuantity = item->GetQuantity();
		}
	}

	if (Input::GetKeyTrigger('S'))
	{
		m_SelectSellingItemQuantity++;
		if (m_SelectSellingItemQuantity > item->GetQuantity())
		{
			m_SelectSellingItemQuantity = 0;
		}
	}

	subPanelSellingItem->SetSellingItemQuantity(m_SelectSellingItemQuantity);

	if (Input::GetKeyTrigger('L'))
	{
		subPanelSellingItem->SellingItem(m_SelectSellingItemQuantity, item);
		Scene* scene = Manager::GetScene();
		m_InventoryView = scene->GetGameObject<InventoryView>();
		SetSelectItem();
		m_SelectStage = SelectSellingItem;
		m_InventoryView->HideSellingItemSubPanel();
	}


	if (Input::GetKeyTrigger('K'))
	{
		Scene* scene = Manager::GetScene();
		m_InventoryView = scene->GetGameObject<InventoryView>();
		SetSelectItem();
		m_SelectStage = SelectSellingItem;
		m_InventoryView->HideSellingItemSubPanel();
	}
}

void InventoryItemCursor::SetSelectHowToUse()
{
	m_SelectStage = SelectStage::SelectHowToUse;
	m_SelectHowToUseIndex = 0;
	m_Scale.x = m_SelectHowToUseTextureWidth;
	m_Scale.y = m_SelectHowToUseTextureHeight;
	m_StaticSprite->SetTexture(m_SelectHowToUseTextureKey, m_SelectHowToUseTexturePass);
	m_WorldPosition.x = (SCREEN_WIDTH - m_Scale.x) / 2;
	m_WorldPosition.y = (SCREEN_HEIGHT - m_Scale.y) / 2;
	m_StaticSprite->SetPosition(D3DXVECTOR2(m_WorldPosition.x, m_WorldPosition.y));
	m_StaticSprite->SetScale(D3DXVECTOR2(m_Scale.x, m_Scale.y));
}

void InventoryItemCursor::SetSelectItem()
{
	m_SelectStage = SelectStage::SelectItem;
	m_Scale.x = m_SelectItemTextureWidth;
	m_Scale.y = m_SelectItemTextureHeight;
	m_StaticSprite->SetTexture(m_SelectItemTextureKey, m_SelectItemTexturePass);
	m_WorldPosition.x = 227.5f + (m_SelectItemIndex % 7) * 120.0f;
	m_WorldPosition.y = 170.0f + (m_SelectItemIndex / 7) * 107.5f;
	m_StaticSprite->SetPosition(D3DXVECTOR2(m_WorldPosition.x, m_WorldPosition.y));
	m_StaticSprite->SetScale(D3DXVECTOR2(m_Scale.x, m_Scale.y));
}

Item* InventoryItemCursor::GetSelectItem()
{
	Item* item = m_Inventory->GetItem(m_SelectItemIndex);
	return item;
}