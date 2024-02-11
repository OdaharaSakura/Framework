#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "shader.h"
#include "inventoryItemIcon.h"
#include "inventory.h"
#include "item.h"
#include "staticSprite.h"
#include "shader.h"


void InventoryItemIcon::Init()
{
	AddComponent<UnlitTexture>();

	m_Scale.x = 100.0f;
	m_Scale.y = 100.0f;
	
}

void InventoryItemIcon::Uninit()
{
	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Uninit();
}

void InventoryItemIcon::Update()
{
	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Update();

	m_StaticSprite->SetPosition(D3DXVECTOR2(m_WorldPosition.x, m_WorldPosition.y));
}

void InventoryItemIcon::Draw()
{
	// �}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Draw();
}

void InventoryItemIcon::SetIndex(int itemIndex)
{
	Scene* scene = Manager::GetScene();
	m_Inventory = scene->GetGameObject<Inventory>();

	m_Index = itemIndex;

	m_Item = m_Inventory->GetItem(m_Index);

	//�A�C�e���̃C���f�b�N�X�ɉ����ăA�C�R���̈ʒu��ݒ�
	m_WorldPosition.x = 227.5f + (m_Index % 7) * 120.0f;
	m_WorldPosition.y = 170.0f + (m_Index / 7) * 107.5f;


	if (m_StaticSprite == nullptr)
	{
		m_StaticSprite = AddComponent<StaticSprite>();
		m_StaticSprite->Init(m_WorldPosition.x, m_WorldPosition.y, m_Scale.x, m_Scale.y, m_Item->GetKey(), m_Item->GetTexturePass());
	}
	else
	{
		m_StaticSprite->SetTexture(m_Item->GetKey(), m_Item->GetTexturePass());
		m_StaticSprite->SetPosition(D3DXVECTOR2(m_WorldPosition.x, m_WorldPosition.y));
	}
}

