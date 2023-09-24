#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "tree.h"

Model* Tree::m_Model{};

void Tree::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\tree1.obj");
}

void Tree::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void Tree::Init()
{

	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout, "Shader\\vertexLightingVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader,
		"Shader\\vertexLightingPS.cso");
}

void Tree::Uninit()
{

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Tree::Update()
{

}

void Tree::Draw()
{


	// 入力レイアウト設定ト（DirectXへ頂点の構造を教える）
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	// 使用するシェーダを設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);//バーテックスシェーダーオブジェクトのセット
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);//ピクセルシェーダーオブジェクトのセット

	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}
