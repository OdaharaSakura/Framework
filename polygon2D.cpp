#include "main.h"
#include "renderer.h"
#include "polygon2D.h"
#include "sprite.h"
#include "input.h"
#include "shader.h"


void Polygon2D::Init()
{
	AddComponent<UnlitTexture>();
	AddComponent<Sprite>()->Init(70.0f, SCREEN_HEIGHT - 90.0f, 320.0f, 70.0f, "asset/texture/gauge_frame.dds");
	//AddComponent<Sprite>()->Init(480.0f, SCREEN_HEIGHT - 60.0f, 310.0f, 24.0f, "asset/texture/TIPS_UO.dds");
	AddComponent<Sprite>()->Init(480.0f, SCREEN_HEIGHT - 60.0f, 310.0f, 24.0f, "asset/texture/TIPS_Space_DEC.dds");
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

}

void Polygon2D::Draw()
{

	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//基底クラスのメソッド呼び出し
	GameObject::Draw();
}