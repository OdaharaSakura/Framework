#include "main.h"
#include "renderer.h"
#include "enemy.h"
#include "scene.h"
#include "manager.h"
#include "treasureBox.h"
#include "gameover.h"
#include "gauge.h"
#include "earth.h"


Model* TreasureBox::m_Model{};

void TreasureBox::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\obj\\TreasureBox.obj");

}

void TreasureBox::Unload()
{
	if(m_Model != nullptr)m_Model->Unload();
	delete m_Model;
}

void TreasureBox::Init()
{
	Scene* scene = Manager::GetScene();

	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout, "shader\\vertexLightingVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\vertexLightingPS.cso");

	m_ModelScale = D3DXVECTOR3(0.015f, 0.015f, 0.015f);

	Gauge* gauge = scene->AddGameObject<Gauge>(1);
	gauge->SetPosition(D3DXVECTOR3(m_WorldPosition.x, 3.0f, m_WorldPosition.z));
	gauge->SetBoxParent(this);

	m_Startflg = true;

	m_AttackDelaynum = 0;
	m_IsAttackflg = false;
	m_Attackflg = false;
	m_Hp = m_HpMax;

}

void TreasureBox::Uninit()
{
	GameObject::Uninit();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void TreasureBox::Update()
{
	GameObject::Update();
	if (m_Startflg)
	{
		m_Hp = m_HpMax;
		m_Startflg = false;
	}
	m_WorldPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (m_AnimeFrame >= 17 || m_AnimeFrame == 0)
	{
		m_AnimeState = RUN;
		m_AnimeFrame = 0;
	}

	D3DXVECTOR3 oldPosition = m_WorldPosition;
	Scene* scene = Manager::GetScene();

	//敵当たり判定
	std::vector<Enemy*> enemies = scene->GetGameObjects<Enemy>();
	for (Enemy* enemy : enemies)
	{
		if (enemy->GetAttackflg())
		{
			m_Hp -= 50;
			enemy->SetNonAttackflg();
		}

		D3DXVECTOR3 position = enemy->GetPosition();
		D3DXVECTOR3 scale = enemy->GetScale();
		D3DXVECTOR3 scalexz = enemy->GetScale();

		D3DXVECTOR3 direction = m_WorldPosition - position;
		direction.y = 0.0f;
		float length = D3DXVec3Length(&direction);
		scalexz.y = 0.0f;
		float lengthxz = D3DXVec3Length(&scalexz);
		if (length < lengthxz)
		{
			m_Hp -= 2;
		}
		if (length < scale.x * scale.x)
		{
			m_IsAttackflg = true;
		}
	}

	if (m_Hp == 0)
	{
		//Manager::SetScene<GameOver>();//ゲームオーバー
	}



	//土
	std::vector<Earth*> Earths = scene->GetGameObjects<Earth>();
	for (Earth* Earth : Earths)
	{
		D3DXVECTOR3 position = Earth->GetPosition();
		D3DXVECTOR3 scale = Earth->GetScale();



		if (position.x - scale.x - 0.5f < m_WorldPosition.x + m_Scale.x &&
			m_WorldPosition.x - m_Scale.x < position.x + scale.x + 0.5f &&
			position.z - scale.z - 0.5f < m_WorldPosition.z + m_Scale.z &&
			m_WorldPosition.z - m_Scale.z < position.z + scale.z + 0.5f)
		{

			if (m_WorldPosition.y < position.y + scale.y * 2.0f - 0.5f)//2.0fはモデルの大きさ高さ1じゃなくて2だとこうなる
			{
				m_WorldPosition.x = oldPosition.x;
				m_WorldPosition.z = oldPosition.z;
			}

			break;
		}
	}


	//test += 0.01f;
}

void TreasureBox::Draw()
{
	GameObject::Draw();


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


