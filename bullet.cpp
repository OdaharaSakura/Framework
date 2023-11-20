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
	//auto enemys = scene->GetGameObjects<Enemy>();//�^�𔻒f���Ă����//�R�[�h�����Â炩������auto�g�����Ƃ�

	m_Position += m_Velocity;

	//m_Rotation += m_Velocity;//�v���C���[�̑O�����ɔ�Ԃ悤�ɂ�����

	D3DXVECTOR3 playerPos = player->GetPosition();
	D3DXVECTOR3 directionPlayer = playerPos - m_Position;
	float lengthPlayer = D3DXVec3Length(&directionPlayer);

	if (lengthPlayer > 15.0f)//�v���C���[����15.0f���ꂽ��
	{
		//�e�������\�������
		SetDestroy();
		return;
	}

	//�G�Ƃ̏Փ˔���
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
			SetDestroy();//�e������
			enemy->SetDestroy();//�G������
			score->AddCount(100);
			return;
		}
	}
}

void Bullet::Draw()
{


	// ���̓��C�A�E�g�ݒ�g�iDirectX�֒��_�̍\����������j
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	// �g�p����V�F�[�_��ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);//�o�[�e�b�N�X�V�F�[�_�[�I�u�W�F�N�g�̃Z�b�g
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);//�s�N�Z���V�F�[�_�[�I�u�W�F�N�g�̃Z�b�g

	// �}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}



