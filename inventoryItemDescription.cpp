#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "inventoryItemDescription.h"
#include "text.h"
#include "sprite.h"
#include "input.h"
#include "shader.h"
#include "inventory.h"
#include "inventoryItemCursor.h"


void InventoryItemDescription::Init()
{
	Scene* scene = Manager::GetScene();
	AddComponent<UnlitTexture>();

	m_ItemText[0] = scene->AddGameObject<GameObject>(LAYER_OBJECT_2D);
	m_ItemNameText = m_ItemText[0]->AddComponent<Text>();
	m_ItemText[1] = scene->AddGameObject<GameObject>(LAYER_OBJECT_2D);
	m_ItemTypeText = m_ItemText[1]->AddComponent<Text>();
	m_ItemText[2] = scene->AddGameObject<GameObject>(LAYER_OBJECT_2D);
	m_ItemDescriptionText = m_ItemText[2]->AddComponent<Text>();

	m_ItemNameText->SetPosition(D3DXVECTOR2(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 5 * 3.5f));
	m_ItemNameText->SetFontColor(D2D1::ColorF::Brown);

	m_ItemTypeText->SetPosition(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5 * 3.5f));
	m_ItemTypeText->SetFontColor(D2D1::ColorF::Gray);

	m_ItemDescriptionText->SetPosition(D3DXVECTOR2(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 5 * 3.75f));
	m_ItemDescriptionText->SetFontColor(D2D1::ColorF::Black);
}

void InventoryItemDescription::Uninit()
{
	//基底クラスのメソッド呼び出し
	GameObject::Uninit();
	for (int i = 0; i < 3; i++)
	{
		m_ItemText[i]->SetDestroy();
	}
}

void InventoryItemDescription::Update()
{
	//基底クラスのメソッド呼び出し
	GameObject::Update();

	Scene* scene = Manager::GetScene();
	m_Inventory = scene->GetGameObject<Inventory>();
	m_InventoryItemCursor = scene->GetGameObject<InventoryItemCursor>();

	if (m_InventoryItemCursor == nullptr) return;

	Item * item = m_Inventory->GetItem(m_InventoryItemCursor->GetIndex());

	if (item == nullptr)
	{
		SetText(m_ItemNameText, "");
		SetText(m_ItemTypeText, "");
		SetText(m_ItemDescriptionText, "");
		return;
	}
	
	SetText(m_ItemNameText, item->GetName());
	SetText(m_ItemTypeText, "種類：" + item->GetType());
	SetText(m_ItemDescriptionText, item->GetDescription());
}

void InventoryItemDescription::Draw()
{

	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//基底クラスのメソッド呼び出し
	GameObject::Draw();
}

void InventoryItemDescription::SetText( Text* textptr, const std::string& text)
{
	textptr->SetText(text);
}
