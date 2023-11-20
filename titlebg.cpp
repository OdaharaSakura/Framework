#include "main.h"
#include "renderer.h"
#include "titlebg.h"
#include "sprite.h"

void TitleBG::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");
	//Sprite* sprite = AddComponent<Sprite>();
	//sprite->Init(0.0f, 0.0f, 200.0f, 200.0f, "asset/texture/field004.jpg");

	AddComponent<Sprite>()->Init(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, "asset/texture/white.jpg");//上のとどっちでもよい
	//AddComponent<Sprite>()->Init(300.0f, 300.0f, 200.0f, 200.0f, "asset/texture/kizuna.jpg");
}

void TitleBG::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	//基底クラスのメソッド呼び出し
	GameObject::Uninit();
}

void TitleBG::Update()
{
	//基底クラスのメソッド呼び出し
	GameObject::Update();
}

void TitleBG::Draw()
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);



	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//基底クラスのメソッド呼び出し
	GameObject::Draw();
}