#include "main.h"
#include "renderer.h"
#include "polygon2D.h"
#include "sprite.h"
#include "DirectWrite.h"

void Polygon2D::Init()
{
	FontData* data = new FontData();

	data->fontSize = 40;
	
	Write = new DirectWrite(data);
	
	Write->Init();

	testtext = "文字出力テスト";

	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");
	//Sprite* sprite = AddComponent<Sprite>();
	//sprite->Init(0.0f, 0.0f, 200.0f, 200.0f, "asset/texture/field004.jpg");

	AddComponent<Sprite>()->Init(SCREEN_WIDTH- 200.0f, SCREEN_HEIGHT- 200.0f, 200.0f, 200.0f, "asset/texture/setsumei.png");//上のとどっちでもよい
	//AddComponent<Sprite>()->Init(300.0f, 300.0f, 200.0f, 200.0f, "asset/texture/kizuna.jpg");
}

void Polygon2D::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

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
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);



	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	Write->DrawString(testtext, D2D1::RectF(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT), D2D1_DRAW_TEXT_OPTIONS_NONE);

	//基底クラスのメソッド呼び出し
	GameObject::Draw();
}