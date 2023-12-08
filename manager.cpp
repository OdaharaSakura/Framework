#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "input.h"
#include "game.h"
#include "test.h"
#include "networkTest.h"
#include "audio.h"
#include "debugmanager.h"

Scene* Manager::m_Scene{};//�ÓI�����o�ϐ��͍Đ錾���K�v
Scene* Manager::m_NextScene{};//�ÓI�����o�ϐ��͍Đ錾���K�v
Renderer* Manager::m_Renderer{};

bool Manager::m_IsGameFinish{};

void Manager::Init()
{
	m_Renderer = new Renderer();
	m_Renderer->Init();

	DebugManager::Init();

	Input::Init();
	Audio::InitMaster();
	m_IsGameFinish = false;

	SetScene<Test>();
}

void Manager::Uninit()
{
	if (m_Scene != nullptr)m_Scene->Uninit();
	delete m_Scene;

	Audio::UninitMaster();
	Input::Uninit();
	DebugManager::Uninit();
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
	DebugManager::Update();
	if(m_Scene != nullptr) m_Scene->Update();
}

void Manager::Draw()
{
	//���C�g�J�����\���̂̏�����
	LIGHT light;
	light.Enable = true;

	LightInitialize(&light, D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//1�p�X��    �V���h�[�o�b�t�@�̍쐬
	Renderer::BeginDepth();
	Renderer::SetDepthViewPort();

	//���C�g�J�����̍s����Z�b�g
	Renderer::SetViewMatrix(&light.ViewMatrix);
	Renderer::SetProjectionMatrix(&light.ProjectionMatrix);

	//�e�𗎂Ƃ������I�u�W�F�N�g��`��(�ꉞ�n�ʂ�)	
	if (m_Scene != nullptr)m_Scene->DepthPath();

	m_Renderer->Begin();
	Renderer::SetDefaultViewPort();

	if (m_Scene != nullptr)m_Scene->Draw();

	DebugManager::Draw();

	m_Renderer->End();

}

void Manager::LightInitialize(LIGHT * light, D3DXVECTOR3 position)
{
	light->Direction = D3DXVECTOR4(1.0f, -1.0f, 0.0f, 0.0f);
	D3DXVec4Normalize(&light->Direction, &light->Direction);
	light->Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	light->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���C�g�J�����̃r���[�s����쐬
	D3DXVECTOR3 lightPos = position + D3DXVECTOR3(0.0f, 20.0f, -5.0f);
	D3DXVECTOR3 lightTarget = position;
	D3DXVECTOR3 lightUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&light->ViewMatrix, &lightPos, &lightTarget, &lightUp);

	//���C�g�J�����̃v���W�F�N�V�����s����쐬
	D3DXMatrixPerspectiveFovLH(&light->ProjectionMatrix, 1.0f, (float)(SCREEN_WIDTH) / (float)(SCREEN_HEIGHT), 5.0f, 50.0f);

	Renderer::SetLight(*light);
}
