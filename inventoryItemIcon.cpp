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
	m_StaticSprite = AddComponent<StaticSprite>();//上のとどっちでもよい
	m_StaticSprite->Init(0, 0, m_Scale.x, m_Scale.y, key, path);
}

void InventoryItemIcon::Uninit()
{
	//基底クラスのメソッド呼び出し
	GameObject::Uninit();
}

void InventoryItemIcon::Update()
{
	//基底クラスのメソッド呼び出し
	GameObject::Update();

	m_WorldPosition.x = 180.0f;
	m_WorldPosition.y = 170.0f;

	m_StaticSprite->SetPosition(D3DXVECTOR2(m_WorldPosition.x, m_WorldPosition.y));
}

void InventoryItemIcon::Draw()
{
	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//基底クラスのメソッド呼び出し
	GameObject::Draw();
}
