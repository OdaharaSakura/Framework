#include "main.h"
#include "manager.h"
#include "scene.h"
#include "renderer.h"
#include "resultsky.h"
#include "resultcamera.h"
#include "camera.h"
#include "model.h"



void ResultSky::Init()
{
	m_Scale = D3DXVECTOR3(100.0f, 100.0f, 100.0f);

	m_Model = new Model();
	m_Model->Load("asset\\model\\obj\\sky.obj");



	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout, "shader\\unlitTextureVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");
}

void ResultSky::Uninit()
{

	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void ResultSky::Update()
{
	Scene* scene = Manager::GetScene();
	ResultCamera* resultcamera = scene->GetGameObject<ResultCamera>();

	m_WorldPosition = resultcamera->GetPosition();
}

void ResultSky::Draw()
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
	D3DXMatrixTranslation(&trans, m_WorldPosition.x, m_WorldPosition.y, m_WorldPosition.z);
	world = scale * rot * trans;

	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}
