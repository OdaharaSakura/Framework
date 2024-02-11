#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "shader.h"
#include "subPanel.h"
#include "staticSprite.h"

//test
#include "input.h"

void SubPanel::Init()
{
	AddComponent<UnlitTexture>();

	m_Scale.x = 240.0f;
	m_Scale.y = 240.0f;

	m_WorldPosition.x = (SCREEN_WIDTH - m_Scale.x) / 2;
	m_WorldPosition.y = (SCREEN_HEIGHT - m_Scale.y) / 2;

	std::string key = "SubPanel";
	std::string path = "subpanel.dds";

	m_StaticSprite = AddComponent<StaticSprite>();//上のとどっちでもよい
	m_StaticSprite->Init(m_WorldPosition.x, m_WorldPosition.y, m_Scale.x, m_Scale.y, key, path);
}

void SubPanel::Uninit()
{
	//基底クラスのメソッド呼び出し
	GameObject::Uninit();
}

void SubPanel::Update()
{
	//基底クラスのメソッド呼び出し
	GameObject::Update();

	m_StaticSprite->SetPosition(D3DXVECTOR2(m_WorldPosition.x, m_WorldPosition.y));
}

void SubPanel::Draw()
{
	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//基底クラスのメソッド呼び出し
	GameObject::Draw();
}

