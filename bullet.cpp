#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "bullet.h"
#include "player.h"
#include "enemy.h"
#include "explosion.h"
#include "score.h"

Model* Bullet::m_Model{};

void Bullet::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\torus.obj");
}

void Bullet::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void Bullet::Init()
{
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();
	m_Scale = D3DXVECTOR3(0.3f, 0.3f, 0.3f);
	SetVelocity(player->GetForward() / 3.0f);


	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout, "shader\\vertexLightingVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\vertexLightingPS.cso");
}

void Bullet::Uninit()
{

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Bullet::Update()
{
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();
	Score* score = scene->GetGameObject<Score>();
	std::vector<Enemy*> enemies = scene->GetGameObjects<Enemy>();
	//auto enemys = scene->GetGameObjects<Enemy>();//型を判断してくれる//コードが見づらかったらauto使うことも

	m_Position += m_Velocity;

	//m_Rotation += m_Velocity;//プレイヤーの前方向に飛ぶようにしたい

	D3DXVECTOR3 playerPos = player->GetPosition();
	D3DXVECTOR3 directionPlayer = playerPos - m_Position;
	float lengthPlayer = D3DXVec3Length(&directionPlayer);

	if (lengthPlayer > 15.0f)//プレイヤーから15.0f離れたら
	{
		//弾を消す予約をする
		SetDestroy();
		return;
	}

	//敵との衝突判定
	for (Enemy* enemy : enemies)
	{
		D3DXVECTOR3 enemyPos = enemy->GetPosition();
		D3DXVECTOR3 enemyScale = enemy->GetScale();
		D3DXVECTOR3 directionEnemy = enemyPos - m_Position;
		float scaleEnemy = D3DXVec3Length(&enemyScale);
		float lengthEnemy = D3DXVec3Length(&directionEnemy);

		if (lengthEnemy < scaleEnemy)
		{
			scene->AddGameObject<Explosion>(1)->SetPosScale(enemyPos, enemyScale);
			SetDestroy();//弾を消す
			enemy->SetDestroy();//敵を消す
			score->AddCount(100);
			return;
		}
	}
}

void Bullet::Draw()
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



