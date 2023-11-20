#include "main.h"
#include "renderer.h"
#include "player.h"
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
#include "gameover.h"
#include "earth.h"
#include "meshField.h"
#include "camera.h"
#include "collider.h"


void Player::Init()
{
	Scene* scene = Manager::GetScene();
	m_Model = new AnimationModel();
	m_Model->Load("asset\\model\\Player.fbx");
	m_Model->LoadAnimation("asset\\model\\Player_Idle.fbx", "Idol");
	m_Model->LoadAnimation("asset\\model\\Player_Run.fbx", "Run");
	m_Model->LoadAnimation("asset\\model\\Player_LeftRun.fbx", "LeftRun");
	m_Model->LoadAnimation("asset\\model\\Player_RightRun.fbx", "RightRun");
	m_Model->LoadAnimation("asset\\model\\Player_BackRun.fbx", "BackRun");
	m_Model->LoadAnimation("asset\\model\\Player_Attack.fbx", "Attack");
	m_Model->LoadAnimation("asset\\model\\Player_Death.fbx", "Death");
	m_Model->LoadAnimation("asset\\model\\Player_InPlaceJump.fbx", "InPlaceJump");

	m_AnimationName = "Idol";
	m_NextAnimationName = "Idol";

	m_IsDisplayShadow = true;

	m_Scale = D3DXVECTOR3(0.015f, 0.015f, 0.015f);

	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout, "shader\\PercentageCloserFilteringVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\PercentageCloserFilteringPS.cso");


	 m_ShotSE = AddComponent<Audio>();
	 m_ShotSE->Load("asset\\audio\\���Ŏa��3.wav");

	 //AddComponent<SphireCollider>()->SetSphireCollider(this, 1.0f);
	 

	 m_AttackDelaynum = 0;
	 m_IsAttackflg = false;
	 m_Attackflg = false;
	 m_Hp = m_HpMax;
}

void Player::Uninit()
{
	GameObject::Uninit();
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Player::Update()
{
	GameObject::Update();
	Scene* scene = Manager::GetScene();
	D3DXVECTOR3 oldPosition = m_Position;

	m_IsAttackflg = false;
	

	//�����F�����蔻��R���|�[�l���g�ɂ���i����̎d�����ƂɊ֐��ς���j
	//ImGUI�̃J�����ɉf����悤�ɕύX������

	//�G�����蔻��
	std::vector<Enemy*> enemies = scene->GetGameObjects<Enemy>();
	for (Enemy* enemy : enemies)
	{
		D3DXVECTOR3 position = enemy->GetPosition();
		D3DXVECTOR3 scale = enemy->GetScale();
		D3DXVECTOR3 scalexz = enemy->GetScale();

		D3DXVECTOR3 direction = m_Position - position;
		direction.y = 0.0f;
		float length = D3DXVec3Length(&direction);
		scalexz.y = 0.0f;
		float lengthxz = D3DXVec3Length(&scalexz);
		if (length < lengthxz)
		{
			if (m_Position.y + m_Scale.y < position.y + scale.y - 0.5f)
			{
				m_Position.x = oldPosition.x;
				m_Position.z = oldPosition.z;
				m_Hp -= 3;
			}
		}
		if (length < lengthxz * lengthxz)
		{
			m_IsAttackflg  = true;
		}
	}

	switch (m_PlayerState)
	{
	case PLAYER_STATE_GROUND:
		UpdateGround();
		break;
	case PLAYER_STATE_JUMP:
		UpdateJump();
		break;
	case PLAYER_STATE_ATTACK:
		UpdateAttack();
		break;
	}

	//�ړ�
	m_Position += m_Velocity;//�I�C���[�@

	//��Q���Ƃ̏Փ˔��聫��=====================================
	float groundHeight;

	MeshField* meshfield = scene->GetGameObject<MeshField>();
	groundHeight = meshfield->GetHeight(m_Position);

	//�~��
	std::vector<Cylinder*> cylinders = scene->GetGameObjects<Cylinder>();
	for (Cylinder* cylinder : cylinders)
	{
		D3DXVECTOR3 position = cylinder->GetPosition();
		D3DXVECTOR3 scale = cylinder->GetScale();
		D3DXVECTOR3 scalexz = cylinder->GetScale();

		D3DXVECTOR3 direction = m_Position - position;
		direction.y = 0.0f;
		float length = D3DXVec3Length(&direction);
		scalexz.y = 0.0f;
		float lengthxz = D3DXVec3Length(&scalexz);
		if (length < lengthxz)
		{
			if (m_Position.y < position.y + scale.y - 0.5f)
			{
				m_Position.x = oldPosition.x;
				m_Position.z = oldPosition.z;
			}

			else
			{
				groundHeight = position.y + scale.y;
			}

			break;
		}
	}



	//������
	std::vector<Box*> boxes = scene->GetGameObjects<Box>();
	for (Box* box : boxes)
	{
		D3DXVECTOR3 position = box->GetPosition();
		D3DXVECTOR3 scale = box->GetScale();



		if (position.x - scale.x - 0.5f < m_Position.x &&
			m_Position.x < position.x + scale.x + 0.5f &&
			position.z - scale.z - 0.5f < m_Position.z &&
			m_Position.z < position.z + scale.z + 0.5f)
		{
			if (m_Position.y < position.y + scale.y * 2.0f - 0.5f)//2.0f�̓��f���̑傫������1����Ȃ���2���Ƃ����Ȃ�
			{
				m_Position.x = oldPosition.x;
				m_Position.z = oldPosition.z;
			}

			else
			{
				groundHeight = position.y + scale.y * 2.0f;
			}

			break;
		}
	}

	//�y
	std::vector<Earth*> Earths = scene->GetGameObjects<Earth>();
	for (Earth* Earth : Earths)
	{
		D3DXVECTOR3 position = Earth->GetPosition();
		D3DXVECTOR3 scale = Earth->GetScale();



		if (position.x - scale.x - 0.5f < m_Position.x &&
			m_Position.x < position.x + scale.x + 0.5f &&
			position.z - scale.z - 0.5f < m_Position.z &&
			m_Position.z < position.z + scale.z + 0.5f)
		{
			if (m_Position.y < position.y + scale.y * 2.0f - 0.5f)//2.0f�̓��f���̑傫������1����Ȃ���2���Ƃ����Ȃ�
			{
				m_Position.x = oldPosition.x;
				m_Position.z = oldPosition.z;
			}

			else
			{
				groundHeight = position.y + scale.y * 2.0f;
			}

			break;
		}
	}
	//��Q���Ƃ̏Փ˔��聪��=====================================

		//�d��
	m_Velocity.y -= 0.015f;



	//�ڒn
	if (m_Position.y < groundHeight && m_Velocity.y < 0.0f)
	{
		m_Position.y = groundHeight;
		m_Velocity.y = 0.0f;
		m_IsGround = true;
	}
	else
	{
		m_IsGround = false;
	}


	////�e�̈ړ�
	//D3DXVECTOR3 shadowPosition = m_Position;
	//shadowPosition.y = groundHeight;
	//m_Shadow->SetPosition(shadowPosition);

	if (m_Hp <= 0)
	{
		//Manager::SetScene<GameOver>();
	}
}

void Player::Draw()
{
	GameObject::Draw();

	//������J�����O
	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>();

	if (!camera->CheckView(m_Position)) return;

	// ���̓��C�A�E�g�ݒ�g�iDirectX�֒��_�̍\����������j
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	// �g�p����V�F�[�_��ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);//�o�[�e�b�N�X�V�F�[�_�[�I�u�W�F�N�g�̃Z�b�g
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);//�s�N�Z���V�F�[�_�[�I�u�W�F�N�g�̃Z�b�g

	// �}�g���N�X�ݒ�
	D3DXMATRIX matrix, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);//���f���ɂ�邪�A�������Ă���+ D3DX_PI��180�x��]������
	D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	matrix = scale * rot * trans;
	m_Matrix = matrix;

	Renderer::SetWorldMatrix(&matrix);

	//�V���h�E�o�b�t�@�e�N�X�`�����P�ԂփZ�b�g
	ID3D11ShaderResourceView* depthShadowTexture =
	Renderer::GetDepthShadowTexture();
	Renderer::GetDeviceContext()->PSSetShaderResources(1, 1,
		&depthShadowTexture);
	
	m_Model->Update(m_AnimationName.c_str(), m_Time, m_NextAnimationName.c_str(), m_Time, m_BlendRate);

	m_Time++;
	m_BlendRate += 0.1f;
	if (m_BlendRate > 1.0f) m_BlendRate = 1.0f;
	m_Model->Draw();
}

void Player::UpdateGround()
{
	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>();
	D3DXVECTOR3 cameraForward = camera->GetForward();
	cameraForward.y = 0.0f;
	D3DXVec3Normalize(&cameraForward, &cameraForward);
	bool move = false;

	////�g�b�v�r���[
	//if (Input::GetKeyPress('A'))
	//{
	//	m_Position.x -= 0.1f;
	// 		m_Rotation.y = -D3DX_PI * 0.5f;
	//}
	//if (Input::GetKeyPress('D'))
	//{
	//	m_Position.x += 0.1f;
	// 		m_Rotation.y = D3DX_PI * 0.5f;
	//}
	//if (Input::GetKeyPress('W'))
	//{
	//	m_Position.z += 0.1f;
	//	m_Rotation.y = D3DX_PI * 0.0f;
	//}
	//if (Input::GetKeyPress('S'))
	//{
	//	m_Position.z -= 0.1f;
	//	m_Rotation.y = D3DX_PI * 1.0f;
	//}


	D3DXVECTOR3 moveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�T�[�h�p�[�\���r���[
	if (Input::GetKeyPress('A'))
	{
		if (m_NextAnimationName != "LeftRun")
		{
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "LeftRun";
			m_BlendRate = 0.0f;
		}
		//moveVec -= GetRight();
		m_Position.x -= 0.1f;

		D3DXQUATERNION quat;
		D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXQuaternionRotationAxis(&quat, &axis, -D3DX_PI / 2.0f);//(��������90�x)
		//m_Quaternion = quat;
		D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.1f);//���ʕό`���

		move = true;

	}
	if (Input::GetKeyPress('D'))
	{
		if (m_NextAnimationName != "RightRun")
		{
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "RightRun";
			m_BlendRate = 0.0f;
		}
		
		//moveVec += GetRight();

		D3DXQUATERNION quat;
		D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXQuaternionRotationAxis(&quat, &axis, D3DX_PI / 2.0f);//(��������90�x)
		//m_Quaternion = quat;
		D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.1f);
		move = true;

	}
	if (Input::GetKeyPress('W'))
	{

		if (m_NextAnimationName != "Run")
		{
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "Run";
			m_BlendRate = 0.0f;
		}

		//moveVec += GetForward();
		m_Position += cameraForward * 0.1f;

		D3DXQUATERNION quat;
		D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		float angle = atan2f(cameraForward.x, cameraForward.z);
		D3DXQuaternionRotationAxis(&quat, &axis, angle);//(��������90�x)
		//m_Quaternion = quat;
		D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.1f);
		move = true;
	}

	if (Input::GetKeyPress('S'))
	{
		if (m_NextAnimationName != "BackRun")
		{
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "BackRun";
			m_BlendRate = 0.0f;
		}

		//moveVec -= GetForward();
		m_Position.z -= 0.1f;

		D3DXQUATERNION quat;
		D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXQuaternionRotationAxis(&quat, &axis, D3DX_PI);//(��������90�x)
		//m_Quaternion = quat;
		D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.1f);
		move = true;
	}

	//D3DXVec3Normalize(&moveVec, &moveVec);
	//m_Position += moveVec * 0.1f;



	if (Input::GetKeyPress('Q'))
	{
		m_Rotation.y -= 0.1f;
	}
	if (Input::GetKeyPress('E'))
	{
		m_Rotation.y += 0.1f;
	}
	if (m_AnimeFrame < 17 && m_AnimeState == ATTACK)
	{
		m_AnimeState = ATTACK;
	}

	//�U��
	if (Input::GetKeyPress('I'))
	{

		m_ShotSE->Play(false);
		if (m_NextAnimationName != "Attack")
		{
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "Attack";
			m_BlendRate = 0.0f;
		}
		move = true;
		m_PlayerState = PLAYER_STATE_ATTACK;
		if (m_IsAttackflg)
		{
			m_Attackflg = true;
		}

	}

	//�y���@
	if (Input::GetKeyPress('L'))
	{
		D3DXVECTOR3 earthPosition;
		earthPosition = m_Position + this->GetForward() * 2.0f;
		scene->AddGameObject<Earth>(1)->SetPosition(earthPosition);//�v���C���[�̈ʒu���甭�˂�����

	}

	//�W�����v
	if (Input::GetKeyPress('J') && m_Velocity.y == 0.0f)
	{
		m_Velocity.y = 0.35f;
		m_PlayerState = PLAYER_STATE_JUMP;

		if (m_NextAnimationName != "InPlaceJump")
		{
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "InPlaceJump";
			m_BlendRate = 0.0f;
		}
		move = true;
	}





	if (move == false)
	{
		if (m_NextAnimationName != "Idol")
		{
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "Idol";
			m_BlendRate = 0.0f;
		}
	}
}

void Player::UpdateJump()
{
	if (m_IsGround == true)
	{
		m_PlayerState = PLAYER_STATE_GROUND;
	}
}

void Player::UpdateAttack()
{
	m_AttackDelaynum++;
	if (m_AttackDelaynum > 25)
	{
		m_PlayerState = PLAYER_STATE_GROUND;
		m_AttackDelaynum = 0;
	}
}

