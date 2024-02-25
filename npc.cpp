#include "main.h"
#include "renderer.h"
#include "npc.h"
#include "manager.h"
#include "player.h"
#include "scene.h"
#include "gauge.h"
#include "earth.h"
#include "shader.h"
#include "animationModel.h"
#include "animationModelContainer.h"

void NPC::Load()
{
	
}

void NPC::Unload()
{
	
}

void NPC::Init()
{
	Scene* scene = Manager::GetScene();
	m_Model = new AnimationModel();
	m_Model = AnimationModelContainer::GetAnimationModel_Key(FBXModel::FBXModel_NPC1);

	AddComponent<VertexLighting>();

	m_Conversation = "こんにちは！\nいい天気ね！";

}

void NPC::Uninit()
{
	GameObject::Uninit();
	if (m_Model) m_Model = nullptr;
}

void NPC::Update()
{
	GameObject::Update();


	D3DXVECTOR3 oldPosition = m_WorldPosition;
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
	float scalexz = D3DXVec3Length(&playerscale);
	if (length < scalexz)
	{
		m_WorldPosition.x = oldPosition.x;
		m_WorldPosition.z = oldPosition.z;
	}
	if (length < scalexz * scalexz + 3.0f)
	{
		m_IsHitPlayer = true;
	}
	else
	{
		m_IsHitPlayer = false;
	}



	m_Time++;
	m_BlendRate += 0.1f;
}

void NPC::Draw()
{
	GameObject::Draw();
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();


	// マトリクス設定
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 target = player->GetPosition();

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	//CalcLookAtMatrixAxisFix(&rot, &m_WorldPosition, &target, &up);
	D3DXMatrixTranslation(&trans, m_WorldPosition.x, m_WorldPosition.y, m_WorldPosition.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	m_Model->Update(NPCAnimation::NPC_Idle, m_Time, NPCAnimation::NPC_Idle, m_Time, m_BlendRate);


	if (m_BlendRate > 1.0f) m_BlendRate = 1.0f;
	m_Model->Draw();
}

//キャラクターを向かせる関数
D3DXMATRIX* NPC::CalcLookAtMatrixAxisFix(D3DXMATRIX* pout, D3DXVECTOR3* pPos, D3DXVECTOR3* pLook, D3DXVECTOR3* pUp)
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

