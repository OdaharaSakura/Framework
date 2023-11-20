#include "main.h"
#include "renderer.h"
#include "resultplayer.h"
#include "input.h"
#include "bullet.h"
#include "manager.h"
#include "scene.h"
#include "cylinder.h"
#include "enemy.h"
#include "gauge.h"
#include "box.h"
#include "audio.h"
#include "shadow.h"
#include "animationModel.h"
#include "result.h"
#include "earth.h"



void ResultPlayer::Init()
{
	Scene* scene = Manager::GetScene();
	m_Model = new AnimationModel();
	m_Model->Load("asset\\model\\Player.fbx");
	m_Model->LoadAnimation("asset\\model\\Player_Idle.fbx", "Idol");


	m_Scale = D3DXVECTOR3(0.015f, 0.015f, 0.015f);

	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout, "shader\\vertexLightingVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\vertexLightingPS.cso");

}

void ResultPlayer::Uninit()
{
	GameObject::Uninit();
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void ResultPlayer::Update()
{
	GameObject::Update();
	Scene* scene = Manager::GetScene();


	m_AnimeState = IDOL;



}

void ResultPlayer::Draw()
{
	GameObject::Draw();

	// 入力レイアウト設定ト（DirectXへ頂点の構造を教える）
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	// 使用するシェーダを設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);//バーテックスシェーダーオブジェクトのセット
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);//ピクセルシェーダーオブジェクトのセット

	// マトリクス設定
	D3DXMATRIX matrix, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);//モデルによるが、後ろ向いてたら+ D3DX_PIで180度回転させる
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	matrix = scale * rot * trans;
	m_Matrix = matrix;

	Renderer::SetWorldMatrix(&matrix);

	m_Model->Update("Idol", m_AnimeFrame, "Idol", m_AnimeFrame, m_BlendRate);
	m_AnimeFrame++;
	m_BlendRate += 0.01f;

	m_Model->Draw();
}

