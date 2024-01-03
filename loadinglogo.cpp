#include "main.h"
#include "renderer.h"
#include "loadinglogo.h"
#include "sprite.h"

#include <cmath>

void LoadingLogo::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");

	m_Scale.x = SCREEN_WIDTH / 3 * 2;
	m_Scale.y = SCREEN_HEIGHT / 3 * 2;

	m_WorldPosition.x = (SCREEN_WIDTH / 2) - (m_Scale.x / 2);
	m_WorldPosition.y = (SCREEN_HEIGHT / 3) - (m_Scale.y / 2) + 15.0f;


	m_Sprite = AddComponent<Sprite>();
	m_Sprite->Init(m_WorldPosition.x, m_WorldPosition.y, m_Scale.x, m_Scale.y, "asset/texture/Loading.png");//上のとどっちでもよい


}

void LoadingLogo::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	//基底クラスのメソッド呼び出し
	GameObject::Uninit();
}

void LoadingLogo::Update()
{
	//基底クラスのメソッド呼び出し
	GameObject::Update();


	//上下移動
	m_Sprite->SetPositionY(m_WorldPosition.y + (std::sinf(m_Rot) * 15));;

	m_Rot += 0.05f;
	if (m_Rot >= 360.0f)
		m_Rot = 0.0f;

}

void LoadingLogo::Draw()
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