#include "main.h"
#include "renderer.h"
#include "polygon2D.h"
#include "sprite.h"
#include "input.h"
#include "shader.h"
#include "textureContainer.h"
#include "staticSprite.h"

void Polygon2D::Init()
{
	m_WorldPosition = D3DXVECTOR3(750.0f, SCREEN_HEIGHT - 75.0f, 0.0f);
	m_Scale = D3DXVECTOR3(310.0f, 24.0f, 1.0f);

	AddComponent<UnlitTexture>();

	m_TIPS = AddComponent<StaticSprite>();

	key[UIType_TIPS_WASD] = "TIPS_WASD";
	path[UIType_TIPS_WASD] = "TIPS_WASD.dds";

	key[UIType_TIPS_UO] = "TIPS_UO";
	path[UIType_TIPS_UO] = "TIPS_UO.dds";

	key[UIType_TIPS_E] = "TIPS_E";
	path[UIType_TIPS_E] = "TIPS_E.dds";

	key[UIType_TIPS_SPACE] = "TIPS_Space";//ジャンプ
	path[UIType_TIPS_SPACE] = "TIPS_Space.dds";

	key[UIType_TIPS_TAB] = "TIPS_TAB";//インベントリ
	path[UIType_TIPS_TAB] = "TIPS_TAB.dds";

	m_TIPS->Init(m_WorldPosition.x, m_WorldPosition.y, m_Scale.x, m_Scale.y, key[0], path[0]);
 	
}

void Polygon2D::Uninit()
{

	//基底クラスのメソッド呼び出し
	GameObject::Uninit();
}

void Polygon2D::Update()
{
	//基底クラスのメソッド呼び出し
	GameObject::Update();

	if (m_IsChangeUI == true)
	{
		//ランダムな数
		int	uiType = rand() % (UIType_TIPS_MAX);

		m_TIPS->SetTexture(key[uiType], path[uiType]);
		m_IsChangeUI = false;
	}

}

void Polygon2D::Draw()
{

	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//基底クラスのメソッド呼び出し
	GameObject::Draw();
}