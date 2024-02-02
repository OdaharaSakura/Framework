#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "shader.h"
#include "equipmentPanel.h"
#include "iEquipment.h"
#include "staticSprite.h"
#include "shader.h"

void EquipmentPanel::Init()
{
	AddComponent<UnlitTexture>();

	m_Scale.x = 150.0f;
	m_Scale.y = 100.0f;
	AddComponent<StaticSprite>()->Init(SCREEN_WIDTH - m_Scale.x - 10.0f, SCREEN_HEIGHT - m_Scale.y - 10.0f, m_Scale.x, m_Scale.y, "EquipmentPanel", "equipment_Panel.png");//上のとどっちでもよい
}

void EquipmentPanel::Uninit()
{
	//基底クラスのメソッド呼び出し
	GameObject::Uninit();
}

void EquipmentPanel::Update()
{
	//基底クラスのメソッド呼び出し
	GameObject::Update();
}

void EquipmentPanel::Draw()
{
	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//基底クラスのメソッド呼び出し
	GameObject::Draw();
}
