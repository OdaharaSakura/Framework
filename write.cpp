#include "main.h"
#include "renderer.h"
#include "write.h"
#include "sprite.h"
#include "DirectWrite.h"

void Write::Init()
{
	FontData* data = new FontData();

	data->fontSize = 40;

	write = new DirectWrite(data);

	write->Init();

	testtext = {};

	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");
}

void Write::Uninit()
{
	if(m_VertexLayout != NULL)m_VertexLayout->Release();
	if (m_VertexShader != NULL)m_VertexShader->Release();
	if (m_PixelShader != NULL)m_PixelShader->Release();

	GameObject;;Uninit();
}

void Write::Update()
{
	//基底クラスのメソッド呼び出し
	GameObject::Update();
}

void Write::Draw()
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);



	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//write->DrawString(testtext, D2D1::RectF(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT), D2D1_DRAW_TEXT_OPTIONS_NONE);

	D3DXVECTOR2 pos = D3DXVECTOR2(m_WorldPosition.x, m_WorldPosition.y);
	write->DrawString(testtext, pos, D2D1_DRAW_TEXT_OPTIONS_NONE);

	//基底クラスのメソッド呼び出し
	GameObject::Draw();
}