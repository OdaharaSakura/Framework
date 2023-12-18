#include "main.h"
#include "renderer.h"
#include "polygon2D.h"
#include "sprite.h"
#include "input.h"
#include "shader.h"


void Polygon2D::Init()
{
	AddComponent<UnlitTexture>();
	AddComponent<Sprite>()->Init(SCREEN_WIDTH- 200.0f, SCREEN_HEIGHT- 200.0f, 200.0f, 200.0f, "asset/texture/setsumei.png");//上のとどっちでもよい

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