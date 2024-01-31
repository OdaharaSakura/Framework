#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "input.h"
#include "game.h"
#include "test.h"
#include "title.h"
#include "networkTest.h"
#include "audio.h"
#include "debugmanager.h"
#include "loading.h"

#include "bloomPolygon.h"
#include "luminance.h"
#include "post.h"

Scene* Manager::m_Scene{};//�ÓI�����o�ϐ��͍Đ錾���K�v
Scene* Manager::m_NextScene{};//�ÓI�����o�ϐ��͍Đ錾���K�v
Renderer* Manager::m_Renderer{};

bool Manager::m_IsGameFinish{};

void Manager::Init()
{
	m_Renderer = new Renderer();
	m_Renderer->Init();

	//DebugManager::Init();

	Input::Init();
	Audio::InitMaster();
	m_IsGameFinish = false;




	SetScene<Title>();//�Q�[���J�n���̃V�[����ݒ�



}

void Manager::Uninit()
{
	if (m_Scene != nullptr)m_Scene->Uninit();
	delete m_Scene;

	Audio::UninitMaster();
	Input::Uninit();
	//DebugManager::Uninit();
	m_Renderer->Uninit();
}

void Manager::Update()
{
	Input::Update();
	if (m_NextScene)
	{
		if (m_Scene)
		{
			m_Scene->Uninit();
			delete m_Scene;
		}


		m_Scene = m_NextScene;
		m_Scene->Init();

		

		m_NextScene = nullptr;
	}
	//DebugManager::Update();
	if(m_Scene != nullptr) m_Scene->Update();
}

void Manager::Draw()
{
	//���C�g�J�����\���̂̏�����
	LIGHT light;
	light.Enable = true;

	if (m_Scene == nullptr) return;

	D3DXVECTOR3 testposition = m_Scene->GetPlayerPosition();
	LightInitialize(&light, testposition);

	//1�p�X��    �V���h�[�o�b�t�@�̍쐬
	Renderer::BeginDepth();
	Renderer::SetDepthViewPort();

	//���C�g�J�����̍s����Z�b�g
	Renderer::SetViewMatrix(&light.ViewMatrix);
	Renderer::SetProjectionMatrix(&light.ProjectionMatrix);

	//�e�𗎂Ƃ������I�u�W�F�N�g��`��	
	m_Scene->DepthPath();


	if (m_Scene->GetIsBloom())
	{
		m_Renderer->BeginPP();
		Renderer::SetDefaultViewPort();


		m_Scene->Draw();

		//bloom
		//���C�g����
		light.Enable = false;
		Renderer::SetLight(light);
		//2�p�X�� �P�x���o�p�o�b�t�@�Ƀ����_�����O
		Renderer::BeginLuminance();
		Renderer::SetLuminanceViewport();
		m_Scene->GetGameObject<Luminance>()->Draw();
		//3�`6�p�X�� �k���o�b�t�@�փ����_�����O
		for (int i = 0; i < 4; i++)
		{
			Renderer::BeginBloom(i);
			Renderer::SetBloomViewport(i);
			m_Scene->GetGameObject<BloomPolygon>()->Draw(i);
		}
		//7�p�X��
		Renderer::Begin();
		Renderer::SetDefaultViewPort();
		m_Scene->GetGameObject<Post>()->Draw();
	}
	else
	{
		m_Renderer->Begin();
		Renderer::SetDefaultViewPort();

		m_Scene->Draw();
	}

	m_Scene->Draw2D();

	//DebugManager::Draw();

	m_Renderer->End();

}




void Manager::LightInitialize(LIGHT * light, D3DXVECTOR3 position)
{
	light->Direction = D3DXVECTOR4(1.0f, -1.0f, 0.0f, 0.0f);
	D3DXVec4Normalize(&light->Direction, &light->Direction);
	light->Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	light->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���C�g�J�����̃r���[�s����쐬
	D3DXVECTOR3 lightPos = position + D3DXVECTOR3(0.0f, 10.0f, -5.0f);//0.0f, 20.0f, -5.0f
	D3DXVECTOR3 lightTarget = position;
	D3DXVECTOR3 lightUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&light->ViewMatrix, &lightPos, &lightTarget, &lightUp);

	//���C�g�J�����̃v���W�F�N�V�����s����쐬
	D3DXMatrixPerspectiveFovLH(&light->ProjectionMatrix, 1.0f, (float)(SCREEN_WIDTH) / (float)(SCREEN_HEIGHT), 1.0f, 1000.0f);

	Renderer::SetLight(*light);
}
