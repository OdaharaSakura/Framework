#include "main.h"
#include "renderer.h"
#include "enemy.h"
#include "manager.h"
#include "player.h"
#include "scene.h"
#include "gauge.h"
#include "earth.h"
#include "animationModelContainer.h"
#include "shader.h"


void Enemy::Load()
{

}

void Enemy::Unload()
{
	
}

void Enemy::Init()
{
	Scene* scene = Manager::GetScene();
	m_Model = AnimationModelContainer::GetAnimationModel_Key(FBXModel::FBXModel_Enemy);


	m_ModelScale = D3DXVECTOR3(0.015f, 0.015f, 0.015f);

	Gauge* gauge = scene->AddGameObject<Gauge>(LAYER_OBJECT_3D);
	gauge->SetPosition(D3DXVECTOR3(m_WorldPosition.x, 3.0f, m_WorldPosition.z));
	gauge->SetEnemyParent(this);

	m_Startflg = true;

	m_AttackDelaynum = 0;
	m_IsAttackflg = false;
	m_Attackflg = false;


	m_Hp = m_HpMax;

}

void Enemy::Uninit()
{
	GameObject::Uninit();
	if (m_Model) m_Model = nullptr;
}

void Enemy::Update()
{
	GameObject::Update();

	if (m_Startflg)
	{
		m_StartPosition = m_WorldPosition;
		m_StartScale = m_Scale;
		m_Startflg = false;
	}


	D3DXVECTOR3 oldPosition = m_WorldPosition;
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();

	D3DXVECTOR3 position = player->GetPosition();

	if (m_Hp == 0)
	{

		Enemy* enemy;
		enemy = scene->AddGameObject<Enemy>(LAYER_OBJECT_3D);
		enemy->SetGameObject(m_StartPosition, D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_StartScale);

		SetDestroy();
	}
		

	if (player->GetAttackflg())
	{
		m_Hp -= 50;
		player->SetNonAttackflg();
	}



	//移動処理（プレイヤーに向かってくる）
	//D3DXVec3Lerp(&m_WorldPosition,&m_WorldPosition, &position,test);

	//プレイヤー当たり判定
		D3DXVECTOR3 playerposition = player->GetPosition();
		D3DXVECTOR3 playerscale = player->GetScale();

		D3DXVECTOR3 direction = m_WorldPosition - playerposition;
		direction.y = 0.0f;
		float length = D3DXVec3Length(&direction);
		playerscale.y = 0.0f;
		float scalexz = D3DXVec3Length(&playerscale);//プレイヤーのスケールを100分の1にしているため
		if (length < scalexz)
		{
			m_WorldPosition.x = oldPosition.x;
			m_WorldPosition.z = oldPosition.z;
		}
		if (length < scalexz * scalexz + 3.0f)
		{

			//m_Hp -= 3;

		}
		if (length < scalexz * scalexz + 10.0f)
		{

			//m_Hp -= 3;

		}

}

void Enemy::Draw()
{
	GameObject::Draw();
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();

	// マトリクス設定
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 target = player->GetPosition();

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_ModelScale.x, m_ModelScale.y, m_ModelScale.z);
	//D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	CalcLookAtMatrixAxisFix(&rot, &m_WorldPosition, &target, &up);
	D3DXMatrixTranslation(&trans, m_WorldPosition.x, m_WorldPosition.y, m_WorldPosition.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	m_Model->Update(EnemyAnimation::Enemy_Run, m_Time, EnemyAnimation::Enemy_Run, m_Time, m_BlendRate);


	m_Time++;
	m_Model->Draw();
}

void Enemy::AddHp(int hp)
{
		m_Hp += hp;
		if (m_Hp > m_HpMax)
		{
		m_Hp = m_HpMax;
	}
		else if (m_Hp < 0)
		{
		m_Hp = 0;
	}
}

//キャラクターを向かせる関数
D3DXMATRIX* Enemy::CalcLookAtMatrixAxisFix(D3DXMATRIX* pout, D3DXVECTOR3* pPos, D3DXVECTOR3* pLook, D3DXVECTOR3* pUp)
{
	D3DXVECTOR3 X, Y, Z, D;
	D = *pLook - *pPos;
	D3DXVec3Normalize(&D, &D);
	D3DXVec3Cross(&X, D3DXVec3Normalize(&Y, pUp), &D);
	D3DXVec3Normalize(&X, &X);
	D3DXVec3Normalize(&Z, D3DXVec3Cross(&Z, &X, &Y));

	pout->_11 = X.x; pout->_12 = X.y; pout->_13 = X.z; pout->_14 = 0;
	pout->_21 = Y.x; pout->_22 = Y.y; pout->_23 = Y.z; pout->_24 = 0;
	pout->_31 = Z.x; pout->_32 = Z.y; pout->_33 = Z.z; pout->_34 = 0;
	pout->_41 = 0.0f; pout->_42 = 0.0f; pout->_43 = 0.0f; pout->_44 = 1.0f;

	return pout;
}

