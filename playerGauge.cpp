#include "main.h"
#include "renderer.h"
#include "playerGauge.h"
#include "player.h"
#include "sprite.h"

void PlayerGauge::Init()
{
	VERTEX_3D vertex[4];


	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;//D3D11_USAGE_DYNAMICにすると書き換えられる//テクスチャアニメーションができる
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;//0からD3D11_CPU_ACCESS_WRITEにすると書き換えられる//テクスチャアニメーションができる

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout, "Shader\\gaugeVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"Shader\\gaugePS.cso");
	m_Scale.x = SCREEN_WIDTH / 3;
	m_Scale.y = SCREEN_HEIGHT / 3 * 2;

}

void PlayerGauge::Uninit()
{
	if (m_VertexBuffer != NULL)m_VertexBuffer->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	//基底クラスのメソッド呼び出し
	GameObject::Uninit();
}

void PlayerGauge::Update()
{
	//基底クラスのメソッド呼び出し
	GameObject::Update();
	if (m_Hp == m_HpMax)m_HpOld = m_HpMax;
	if (m_PlayerParent != NULL)
	{
		m_Hp = m_PlayerParent->GetHp();
		m_HpMax = m_PlayerParent->GetHpMax();
	}

	if (m_HpOld > m_Hp)
	{
		m_HpOld -= 1;
		if (m_HpOld < m_Hp) m_HpOld = m_Hp;
	}
}

void PlayerGauge::Draw()
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);






	//頂点データ書き換え
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
		D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;


	vertex[0].Position = D3DXVECTOR3(m_Position.x, m_Position.y, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(m_Position.x + m_Scale.x, m_Position.y, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(m_Position.x, m_Position.y + m_Scale.y, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(m_Position.x + m_Scale.x, m_Position.y + m_Scale.y, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);


	Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);


	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//HPパラメータ設定
	PARAMETER param;
	param.hitpoint.x = m_Hp;
	param.hitpoint.y = m_HpMax;
	param.hitpoint.z = m_HpOld;
	param.baseColor = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	param.lostColor = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	param.diffColor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	Renderer::SetParameter(param);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	Renderer::GetDeviceContext()->Draw(4, 0);

	//基底クラスのメソッド呼び出し
	GameObject::Draw();
}