#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "shader.h"
#include "inventoryItemIcon.h"
#include "inventory.h"
#include "staticSprite.h"
#include "shader.h"


void InventoryItemIcon::Init()
{
	AddComponent<UnlitTexture>();

	

	m_Scale.x = 140.0f;
	m_Scale.y = 100.0f;
	std::string key = "Hoe";
	std::string path = "equipment_icon_kuwa.dds";
	m_StaticSprite = AddComponent<StaticSprite>();//��̂Ƃǂ����ł��悢
	m_StaticSprite->Init(0, 0, m_Scale.x, m_Scale.y, key, path);
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

	m_WorldPosition.x = 180.0f;
	m_WorldPosition.y = 170.0f;

	m_StaticSprite->SetPosition(D3DXVECTOR2(m_WorldPosition.x, m_WorldPosition.y));
}

void InventoryItemIcon::Draw()
{
	// �}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Draw();
}
