#include "main.h"
#include "renderer.h"
#include "fade.h"
#include "sprite.h"

void Fade::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout, "Shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"Shader\\unlitTexturePS.cso");

	m_Sprite = AddComponent<Sprite>();
	m_Sprite->Init(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, "asset/texture/black.png");//��̂Ƃǂ����ł��悢

	
	if (!m_IsFadeOut)
	{
		m_Alpha = 1.0f;
	}
	else
	{
		m_Alpha = 0.0f;
	}
}

void Fade::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Uninit();
}

void Fade::Update()
{
	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Update();
	if (!m_IsFadeOut)
	{

		m_Alpha -= m_Fadespeed;
		if (0.0f >= m_Alpha)
			m_Alpha = 0.0f;
	}
	else
	{
		m_Alpha += m_Fadespeed;
		if (m_Alpha > 1.0f)
		{
			m_Alpha = 1.0f;
			m_IsFadeOutFinish = true;
		}
			
	}
	
	m_Sprite->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_Alpha));
}

void Fade::Draw()
{
	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	// �V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);
	


	// �}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Draw();
}