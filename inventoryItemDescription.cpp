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

	for (int i = 0; i < m_textObjNum; i++)
	{
		m_ItemText[i] = scene->AddGameObject<GameObject>(LAYER_OBJECT_2D);
	}
	
	m_ItemNameText = m_ItemText[0]->AddComponent<Text>();
	m_ItemTypeText = m_ItemText[1]->AddComponent<Text>();
	m_ItemDescriptionText = m_ItemText[2]->AddComponent<Text>();
	m_ItemQuantityText = m_ItemText[3]->AddComponent<Text>();


	m_ItemNameText->SetPosition(D3DXVECTOR2(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 5 * 3.5f));
	m_ItemNameText->SetFontColor(D2D1::ColorF::Brown);

	m_ItemTypeText->SetPosition(D3DXVECTOR2(SCREEN_WIDTH / 5 * 2, SCREEN_HEIGHT / 5 * 3.5f));
	m_ItemTypeText->SetFontColor(D2D1::ColorF::Gray);

	m_ItemQuantityText->SetPosition(D3DXVECTOR2(SCREEN_WIDTH / 3 * 2 - 20.0f, SCREEN_HEIGHT / 5 * 3.5f));
	m_ItemQuantityText->SetFontColor(D2D1::ColorF::Black);
	m_ItemQuantityText->SetFontSize(24);

	m_ItemDescriptionText->SetPosition(D3DXVECTOR2(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 5 * 3.75f));
	m_ItemDescriptionText->SetFontColor(D2D1::ColorF::Black);


}

void InventoryItemDescription::Uninit()
{
	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Uninit();
	for (int i = 0; i < m_textObjNum; i++)
	{
		m_ItemText[i]->SetDestroy();
	}
}

void InventoryItemDescription::Update()
{
	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Update();

	Scene* scene = Manager::GetScene();
	m_Inventory = scene->GetGameObject<Inventory>();
	m_InventoryItemCursor = scene->GetGameObject<InventoryItemCursor>();

	if (m_InventoryItemCursor == nullptr) return;

	Item * item = m_Inventory->GetItem(m_InventoryItemCursor->GetSelectItemIndex());

	if (item == nullptr)
	{
		SetText(m_ItemNameText, "");
		SetText(m_ItemTypeText, "");
		SetText(m_ItemQuantityText, "");
		SetText(m_ItemDescriptionText, "");
		return;
	}

	std::string itemQuantity = std::to_string(item->GetQuantity());
	
	SetText(m_ItemNameText, item->GetName());
	SetText(m_ItemTypeText, "��ށF" + item->GetType());
	SetText(m_ItemQuantityText, "�������F" + itemQuantity);
	SetText(m_ItemDescriptionText, item->GetDescription());
}

void InventoryItemDescription::Draw()
{

	// �}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Draw();
}

void InventoryItemDescription::SetText( Text* textptr, const std::string& text)
{
	textptr->SetText(text);
}
