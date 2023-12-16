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

	SetScene<Title>();
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

	if (m_Scene != nullptr)
	{
		D3DXVECTOR3 testposition = m_Scene->GetPlayerPosition();

		LightInitialize(&light, testposition);
	}
	else
	{
		LightInitialize(&light, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}


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

	//DebugManager::Draw();

	m_Renderer->End();

}

//void Manager::DrawEnv()
//{
//	//���C�g�J�����\���̂̏�����
//	LIGHT light;
//	light.Enable = true;
//
//	if (m_Scene != nullptr)
//	{
//		D3DXVECTOR3 testposition = m_Scene->GetPlayerPosition();
//
//		LightInitialize(&light, testposition);
//	}
//	else
//	{
//		LightInitialize(&light, D3DXVECTOR3(0.0f, 0.0f, 0.0f));
//	}
//
//
//	//1�p�X��    �V���h�[�o�b�t�@�̍쐬
//	Renderer::BeginDepth();
//	Renderer::SetDepthViewPort();
//
//	//���C�g�J�����̍s����Z�b�g
//	Renderer::SetViewMatrix(&light.ViewMatrix);
//	Renderer::SetProjectionMatrix(&light.ProjectionMatrix);
//
//	//�e�𗎂Ƃ������I�u�W�F�N�g��`��(�ꉞ�n�ʂ�)	
//	if (m_Scene != nullptr)m_Scene->DepthPath();
//
//	//�r���[�ϊ��s����쐬����
////�����_�I�t�Z�b�g�e�[�u��
//	D3DXVECTOR3 lookatOffset[6] = {
//	{ 1.0f, 0.0f, 0.0f },//+X D3D11_TEXTURECUBE_FACE_POSITIVE_X
//	{ -1.0f, 0.0f, 0.0f },//-X D3D11_TEXTURECUBE_FACE_NEGATIVE_X
//	{ 0.0f, 1.0f, 0.0f },//+Y D3D11_TEXTURECUBE_FACE_POSITIVE_Y
//	{ 0.0f, -1.0f, 0.0f },//-Y D3D11_TEXTURECUBE_FACE_NEGATIVE_Y
//	{ 0.0f, 0.0f, 1.0f },//+Z D3D11_TEXTURECUBE_FACE_POSITIVE_Z
//	{ 0.0f, 0.0f, -1.0f },//-Z D3D11_TEXTURECUBE_FACE_NEGATIVE_Z
//	};
//
//	//up�x�N�g���e�[�u��
//	D3DXVECTOR3 upOffset[6] = {
//	{ 0.0f, 1.0f, 0.0f },
//	{ 0.0f, 1.0f, 0.0f },
//	{ 0.0f, 0.0f, -1.0f },
//	{ 0.0f, 0.0f, 1.0f },
//	{ 0.0f, 1.0f, 0.0f },
//	{ 0.0f, 1.0f, 0.0f },
//	};
//
//	D3DXVECTOR3 eye;
//	D3DXVECTOR3 lookat;
//	D3DXVECTOR3 up;
//
//	D3DXMATRIX viewMatrixArray[6];
//	D3DXVECTOR3 vPlayerPos;
//	if (m_Scene != nullptr)
//	{
//		vPlayerPos = m_Scene->GetEnvObjectPosition();
//	}
//	else
//	{
//		vPlayerPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
//	}
//	for (int i = 0; i < 6; i++)
//	{
//		eye = vPlayerPos;
//		lookat = vPlayerPos + lookatOffset[i];
//		up = upOffset[i];
//		D3DXMatrixLookAtLH(&viewMatrixArray[i], &eye, &lookat, &up);
//	}
//
//	//�v���W�F�N�V�����}�g���N�X�ݒ�
//	D3DXMATRIX projectionMatrix;
//	D3DXMatrixPerspectiveFovLH(&projectionMatrix, D3DX_PI / 2, 1.0f, 0.01f, 10000.0f);
//	Renderer::SetProjectionMatrix(&projectionMatrix);
//	//�r���[�|�[�g�ύX
//	Renderer::SetReflectViewport();
//	//6�ʕ��`�悷��
//	for (int i = 0; i < 6; i++)
//	{
//		Renderer::BeginCube();
//		//�r���[�ϊ��}�g���N�X�ݒ�
//		Renderer::SetViewMatrix(&viewMatrixArray[i]);
//		//�}�b�v�ɕ`�悷��I�u�W�F�N�g��`��	
//		if (m_Scene != nullptr)m_Scene->EnvPath();
//		//�`�悵���e�N�X�`�����L���[�u�}�b�v�p�e�N�X�`���ɃR�s�[���Ă���
//		Renderer::GetDeviceContext()->CopySubresourceRegion(
//			Renderer::GetCubeReflectTexture(),
//			D3D11CalcSubresource(0, i, 1),
//			0, 0, 0, Renderer::GetReflectTexture(), 0, nullptr);
//	}
//
//
//
//
//
//	m_Renderer->Begin();
//	Renderer::SetDefaultViewPort();
//
//	if (m_Scene != nullptr)m_Scene->Draw();
//
//	//DebugManager::Draw();
//
//	m_Renderer->End();
//}


void Manager::LightInitialize(LIGHT * light, D3DXVECTOR3 position)
{
	light->Direction = D3DXVECTOR4(1.0f, -1.0f, 0.0f, 0.0f);
	D3DXVec4Normalize(&light->Direction, &light->Direction);
	light->Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	light->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���C�g�J�����̃r���[�s����쐬
	D3DXVECTOR3 lightPos = position + D3DXVECTOR3(0.0f, 10.0f, 15.0f);//0.0f, 20.0f, -5.0f
	D3DXVECTOR3 lightTarget = position;
	D3DXVECTOR3 lightUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&light->ViewMatrix, &lightPos, &lightTarget, &lightUp);

	//���C�g�J�����̃v���W�F�N�V�����s����쐬
	D3DXMatrixPerspectiveFovLH(&light->ProjectionMatrix, 1.0f, (float)(SCREEN_WIDTH) / (float)(SCREEN_HEIGHT), 1.0f, 100.0f);

	Renderer::SetLight(*light);
}
