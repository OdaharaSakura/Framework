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
	m_GaugeFrame->Init(SCREEN_WIDTH - 200.0f, 20.0f, 180.0f, 24.0f, "asset/texture/GaugeFrame.dds");

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