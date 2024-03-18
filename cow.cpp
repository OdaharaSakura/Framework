#include "main.h"
#include "renderer.h"
#include "cow.h"
#include "manager.h"
#include "player.h"
#include "scene.h"
#include "gauge.h"
#include "earth.h"
#include "shader.h"
#include "animationModel.h"
#include "animationModelContainer.h"
#include "camera.h"

void COW::Load()
{
	
}

void COW::Unload()
{
	
}

void COW::Init()
{
	Scene* scene = Manager::GetScene();
	m_Model = new AnimationModel();
	m_Model = AnimationModelContainer::GetAnimationModel_Key(FBXModel::FBXModel_Cow);

	AddComponent<VertexLighting>();

}

void COW::Uninit()
{
	GameObject::Uninit();
	if (m_Model) m_Model = nullptr;
}

void COW::Update()
{
	GameObject::Update();

	m_Time++;
	m_BlendRate += 0.1f;
}

void COW::Draw()
{
	GameObject::Draw();
	Scene* scene = Manager::GetScene();

	//������J�����O
	Camera* camera = scene->GetGameObject<Camera>();
	D3DXVECTOR3 length = D3DXVECTOR3(m_Scale.x, 0.0f, m_Scale.z);
	float objectSize = D3DXVec3Length(&length);

	if (!camera->CheckViewWithBoundingSphere(m_WorldPosition, objectSize))
	{
		return;
	}

	Player* player = scene->GetGameObject<Player>();

	// �}�g���N�X�ݒ�
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXVECTOR3 target = player->GetPosition();

	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	//CalcLookAtMatrixAxisFix(&rot, &m_WorldPosition, &target, &up);
	D3DXMatrixTranslation(&trans, m_WorldPosition.x, m_WorldPosition.y, m_WorldPosition.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	m_Model->Update(CowAnimation::Cow_Walk, m_Time, CowAnimation::Cow_Walk, m_Time, m_BlendRate);


	if (m_BlendRate > 1.0f) m_BlendRate = 1.0f;
	m_Model->Draw();
}

//�L�����N�^�[����������֐�
D3DXMATRIX* COW::CalcLookAtMatrixAxisFix(D3DXMATRIX* pout, D3DXVECTOR3* pPos, D3DXVECTOR3* pLook, D3DXVECTOR3* pUp)
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

