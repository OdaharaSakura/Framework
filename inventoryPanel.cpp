#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "shader.h"
#include "inventoryPanel.h"
#include "inventory.h"
#include "staticSprite.h"

void InventoryPanel::Init()
{
	AddComponent<UnlitTexture>();

	m_Scale.x = 1120.0f;
	m_Scale.y = 630.0f;

	m_WorldPosition.x = (SCREEN_WIDTH - m_Scale.x) / 2;
	m_WorldPosition.y = (SCREEN_HEIGHT - m_Scale.y) / 2;

	std::string key = "InventoryPanel";
	std::string path = "Windows_item.dds";

	m_StaticSprite = AddComponent<StaticSprite>();//��̂Ƃǂ����ł��悢
	m_StaticSprite->Init(m_WorldPosition.x, m_WorldPosition.y, m_Scale.x, m_Scale.y, key, path);
}

void InventoryPanel::Uninit()
{
	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Uninit();
}

void InventoryPanel::Update()
{
	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Update();

	m_StaticSprite->SetPosition(D3DXVECTOR2(m_WorldPosition.x, m_WorldPosition.y));
}

void InventoryPanel::Draw()
{
	// �}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Draw();
}
