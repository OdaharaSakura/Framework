#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "shader.h"
#include "subPanelSellingItem.h"
#include "staticSprite.h"
#include "text.h"
#include "item.h"
#include "inventory.h"


void SubPanelSellingItem::Init()
{
	AddComponent<UnlitTexture>();

	m_Scale.x = 240.0f;
	m_Scale.y = 240.0f;

	m_WorldPosition.x = (SCREEN_WIDTH - m_Scale.x) / 2;
	m_WorldPosition.y = (SCREEN_HEIGHT - m_Scale.y) / 2;

	std::string key = "SubPanelSellingItem";
	std::string path = "subpanel_selling.dds";

	m_StaticSprite = AddComponent<StaticSprite>();//��̂Ƃǂ����ł��悢
	m_StaticSprite->Init(m_WorldPosition.x, m_WorldPosition.y, m_Scale.x, m_Scale.y, key, path);

	m_SellingItemQuantity = 0;

	m_Text = AddComponent<Text>();
	m_Text->SetPosition(D3DXVECTOR2(m_WorldPosition.x + 20, m_WorldPosition.y - 10));
	m_Text->SetFontSize(20);
	m_Text->SetText(std::to_string(m_SellingItemQuantity));
}

void SubPanelSellingItem::Uninit()
{
	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Uninit();
}

void SubPanelSellingItem::Update()
{
	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Update();

	m_StaticSprite->SetPosition(D3DXVECTOR2(m_WorldPosition.x, m_WorldPosition.y));
	m_Text->SetText(std::to_string(m_SellingItemQuantity));
}

void SubPanelSellingItem::Draw()
{
	// �}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Draw();
}

void SubPanelSellingItem::SellingItem(int quantity, Item* itemPtr)
{
	Scene* scene = Manager::GetScene();
	Inventory* inventory = scene->GetGameObject<Inventory>();

	auto itemPtrKey = itemPtr->GetKey();

	int price = itemPtr->GetSellingPrice() * quantity;
	inventory->AddMoney(price);

	inventory->DecreaseItem(itemPtr, quantity);
}

