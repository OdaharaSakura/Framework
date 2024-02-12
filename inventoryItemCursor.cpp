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

void InventoryItemCursor::Init()
{
	AddComponent<UnlitTexture>();

	m_Scale.x = m_SelectItemTextureWidth;
	m_Scale.y = m_SelectItemTextureHeight;
	m_WorldPosition.x = 225.0f + (m_Index % 7) * 125.0f;
	m_WorldPosition.y = 170.0f + (m_Index / 7) * 100.0f;
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
		UpdateSelectItem();
		break;

		case SelectHowToUse:
		UpdateSelectHowToUse(GetSelectItem());
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

void InventoryItemCursor::UpdateSelectItem()
{
	Scene* scene = Manager::GetScene();
	m_Inventory = scene->GetGameObject<Inventory>();
	m_InventoryView = scene->GetGameObject<InventoryView>();

	if (Input::GetKeyTrigger('W'))
	{
		m_Index -= 7;
		if (m_Index < 0)
		{
			m_Index += m_Inventory->GetMaxCapacity();
		}
	}

	if (Input::GetKeyTrigger('S'))
	{
		m_Index += 7;
		if (m_Index >= m_Inventory->GetMaxCapacity())
		{
			m_Index -= m_Inventory->GetMaxCapacity();
		}
	}

	if (Input::GetKeyTrigger('A'))
	{
		m_Index--;
		if (m_Index < 0)
		{
			m_Index += m_Inventory->GetMaxCapacity();
		}
	}

	if (Input::GetKeyTrigger('D'))
	{
		m_Index++;
		if (m_Index >= m_Inventory->GetMaxCapacity())
		{
			m_Index -= m_Inventory->GetMaxCapacity();
		}
	}

	m_WorldPosition.x = 227.5f + (m_Index % 7) * 120.0f;
	m_WorldPosition.y = 170.0f + (m_Index / 7) * 107.5f;
	m_StaticSprite->SetPosition(D3DXVECTOR2(m_WorldPosition.x, m_WorldPosition.y));

	if (Input::GetKeyTrigger(VK_SPACE))
	{
		Scene* scene = Manager::GetScene();
		m_InventoryView = scene->GetGameObject<InventoryView>();
		m_InventoryView->ShowSelectPanel();
		SetSelectHowToUse();
		m_SelectStage = SelectHowToUse;
	}
}

void InventoryItemCursor::UpdateSelectHowToUse(Item* item)
{
	if (Input::GetKeyTrigger(VK_SPACE))
	{
		Scene* scene = Manager::GetScene();
		m_InventoryView = scene->GetGameObject<InventoryView>();
		m_InventoryView->HideSelectPanel();
		SetSelectItem();
		m_SelectStage = SelectItem;
	}
}

void InventoryItemCursor::SetSelectHowToUse()
{
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
	m_Scale.x = m_SelectItemTextureWidth;
	m_Scale.y = m_SelectItemTextureHeight;
	m_StaticSprite->SetTexture(m_SelectItemTextureKey, m_SelectItemTexturePass);
	m_StaticSprite->SetScale(D3DXVECTOR2(m_Scale.x, m_Scale.y));
}

Item* InventoryItemCursor::GetSelectItem()
{
	Item* item = m_Inventory->GetItem(m_Index);
	return item;
}