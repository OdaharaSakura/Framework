#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "shader.h"
#include "inventoryItemCursor.h"
#include "inventory.h"
#include "staticSprite.h"
#include "shader.h"


void InventoryItemCursor::Init()
{
	AddComponent<UnlitTexture>();

	m_Scale.x = 140.0f;
	m_Scale.y = 100.0f;
	std::string key = "Hoe";
	std::string path = "equipment_icon_kuwa.dds";
	m_StaticSprite = AddComponent<StaticSprite>();//上のとどっちでもよい
	m_StaticSprite->Init(SCREEN_WIDTH - m_Scale.x, SCREEN_HEIGHT - m_Scale.y - 10.0f, m_Scale.x, m_Scale.y, key, path);
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

}

void InventoryItemCursor::Draw()
{
	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//基底クラスのメソッド呼び出し
	GameObject::Draw();
}
