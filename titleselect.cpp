#include "main.h"
#include "renderer.h"
#include "titleselect.h"
#include "sprite.h"

void TitleSelect::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout, "Shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"Shader\\unlitTexturePS.cso");

	m_Scale.x = SCREEN_WIDTH / 3;
	m_Scale.y = SCREEN_HEIGHT / 3;

	m_Position.x = (SCREEN_WIDTH / 2) - (m_Scale.x / 2);
	m_Position.y = ((SCREEN_HEIGHT / 5) * 4) - (m_Scale.y / 2);

	m_Sprite = AddComponent<Sprite>();
	m_Sprite->Init(m_Position.x, m_Position.y, m_Scale.x, m_Scale.y, "asset/texture/titleselect.png");//上のとどっちでもよい
}

void TitleSelect::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	//基底クラスのメソッド呼び出し
	GameObject::Uninit();
}

void TitleSelect::Update()
{
	//基底クラスのメソッド呼び出し
	GameObject::Update();

	m_Sprite->SetColor(m_Color);
}

void TitleSelect::Draw()
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