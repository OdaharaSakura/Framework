#include "main.h"
#include "renderer.h"
#include "gaugeframe.h"
#include "sprite.h"
#include "input.h"
#include "shader.h"

void GaugeFrame::Init()
{
	AddComponent<UnlitTexture>();
	m_GaugeFrame = AddComponent<Sprite>();
	m_GaugeFrame->Init(70.0f, SCREEN_HEIGHT - 90.0f, 320.0f, 70.0f, "asset/texture/gauge_frame.dds");

}

void GaugeFrame::Uninit()
{

	//基底クラスのメソッド呼び出し
	GameObject::Uninit();
}

void GaugeFrame::Update()
{
	//基底クラスのメソッド呼び出し
	GameObject::Update();

}

void GaugeFrame::Draw()
{

	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//基底クラスのメソッド呼び出し
	GameObject::Draw();
}