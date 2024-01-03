#include "main.h"
#include "renderer.h"
#include "rock.h"
#include "manager.h"
#include "player.h"
#include "scene.h"
#include "gauge.h"
#include "earth.h"


Model* Rock::m_Model{};

void Rock::Load()
{

	m_Model->Load("asset\\model\\fbx\\Mutant.fbx");

}

void Rock::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void Rock::Init()
{
	Scene* scene = Manager::GetScene();

	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout, "shader\\vertexLightingVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\vertexLightingPS.cso");


}

void Rock::Uninit()
{
	GameObject::Uninit();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Rock::Update()
{
	GameObject::Update();


	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();

	D3DXVECTOR3 position = player->GetPosition();


	//プレイヤー当たり判定
	D3DXVECTOR3 playerposition = player->GetPosition();
	D3DXVECTOR3 playerscale = player->GetScale();

	D3DXVECTOR3 direction = m_WorldPosition - playerposition;
	direction.y = 0.0f;
	float length = D3DXVec3Length(&direction);
	playerscale.y = 0.0f;
	float scalexz = D3DXVec3Length(&playerscale) * 100.0f;//プレイヤーのスケールを100分の1にしているため
}

void Rock::Draw()
{
	GameObject::Draw();
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();

	// 入力レイアウト設定ト（DirectXへ頂点の構造を教える）
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	// 使用するシェーダを設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);//バーテックスシェーダーオブジェクトのセット
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);//ピクセルシェーダーオブジェクトのセット

	// マトリクス設定
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 target = player->GetPosition();

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_WorldPosition.x, m_WorldPosition.y, m_WorldPosition.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);


	m_Model->Draw();
}



