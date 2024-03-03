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
#include "gameover.h"
#include "inventory.h"
#include "itemFactory.h"

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


	m_ModelScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	Gauge* gauge = scene->AddGameObject<Gauge>(LAYER_OBJECT_3D);
	gauge->SetPosition(D3DXVECTOR3(m_WorldPosition.x, 8.0f, m_WorldPosition.z));
	gauge->SetEnemyParent(this);


	m_AttackDelaynum = 0;
	m_IsDamageflg = false;


	m_Hp = m_HpMax;

	m_EnemyState = EnemyState_Wait;
}

void Enemy::Uninit()
{
	GameObject::Uninit();
	if (m_Model) m_Model = nullptr;
}

void Enemy::Update()
{
	GameObject::Update();


	switch (m_EnemyState)
	{
	case EnemyState_Wait:
		UpdateWait();
		break;
	case EnemyState_Tracking:
		UpdateTracking();
		break;
	case EnemyState_Attack:
		UpdateAttack();
		break;
	case EnemyState_Damage:
		UpdateDamage();
		break;
	case EnemyState_Death:
		UpdateDeath();
		break;
	}


	D3DXVECTOR3 oldPosition = m_WorldPosition;
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();

	D3DXVECTOR3 position = player->GetPosition();

	if (m_Hp <= 0)
	{
		m_EnemyState = EnemyState_Death;
	}
		


	//プレイヤー当たり判定
	D3DXVECTOR3 playerscale = player->GetScale();
	playerscale.y = 0.0f;
	float scalexz = D3DXVec3Length(&playerscale);

	if (CheckPlayerDistance(scalexz))
	{
		m_WorldPosition.x = oldPosition.x;
		m_WorldPosition.z = oldPosition.z;
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
	if (m_EnemyState == EnemyState_Wait)
	{
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	}
	else
	{
		CalcLookAtMatrixAxisFix(&rot, &m_WorldPosition, &target, &up);
	}
	D3DXMatrixTranslation(&trans, m_WorldPosition.x, m_WorldPosition.y, m_WorldPosition.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	m_Model->Update(m_AnimationIndex, m_Time, m_NextAnimationIndex, m_Time, m_BlendRate);


	m_Time++;
	m_Model->Draw();
}

void Enemy::UpdateAnimation(int enemyAnimation)
{
	if (m_NextAnimationIndex != enemyAnimation)
	{
		m_AnimationIndex = m_NextAnimationIndex;
		m_NextAnimationIndex = enemyAnimation;
		m_BlendRate = 0.0f;
	}
}

void Enemy::UpdateWait()
{
	UpdateAnimation(EnemyAnimation::Enemy_Idle);

	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();

	D3DXVECTOR3 playerscale = player->GetScale();
	playerscale.y = 0.0f;
	float scalexz = D3DXVec3Length(&playerscale);
	if (CheckPlayerDistance(scalexz * scalexz + 10.0f))
	{
		m_EnemyState = EnemyState_Tracking;
	}
}

void Enemy::UpdateTracking()
{
	UpdateAnimation(EnemyAnimation::Enemy_Run);

	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();
	D3DXVECTOR3 position = player->GetPosition();

	D3DXVECTOR3 playerscale = player->GetScale();
	playerscale.y = 0.0f;
	float scalexz = D3DXVec3Length(&playerscale);

	if (!CheckPlayerDistance(scalexz * scalexz + 10.0f))
	{
		m_EnemyState = EnemyState_Wait;
	}
	if (CheckPlayerDistance(scalexz * scalexz + 3.0f))
	{
		m_EnemyState = EnemyState_Attack;
	}


	//移動処理（プレイヤーに向かってくる）
	D3DXVec3Lerp(&m_WorldPosition,&m_WorldPosition, &position,test);
}

void Enemy::UpdateAttack()
{
	Player* player = Manager::GetScene()->GetGameObject<Player>();
	UpdateAnimation(EnemyAnimation::Enemy_Attack);
	m_AnimeFrame++;

	if (m_AnimeFrame >= 15)
	{
		m_AnimeFrame = 0;
		player->AddHp(-10);
		m_EnemyState = EnemyState_Tracking;
	}
}

void Enemy::UpdateDamage()
{
}

void Enemy::UpdateDeath()
{
	Scene* scene = Manager::GetScene();
	Inventory* inventory = scene->GetGameObject<Inventory>();
	ItemFactory* itemFactory = scene->GetGameObject<ItemFactory>();
	inventory->AddItem(itemFactory->CreateItem("EnemyStone"));


	SetDestroy();
}

bool Enemy::CheckPlayerDistance(float distance)
{
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();

	D3DXVECTOR3 playerposition = player->GetPosition();

	D3DXVECTOR3 direction = m_WorldPosition - playerposition;
	direction.y = 0.0f;
	float length = D3DXVec3Length(&direction);

	if (length < distance)
	{
		return true;
	}
	else
	{
		return false;
	}
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

