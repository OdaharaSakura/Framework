#include "main.h"
#include "renderer.h"
#include "input.h"
#include "titleenter.h"
#include "sprite.h"

#include <cmath>

void TitleEnter::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");
	//Sprite* sprite = AddComponent<Sprite>();
	//sprite->Init(0.0f, 0.0f, 200.0f, 200.0f, "asset/texture/field004.jpg");

	//AddComponent<Sprite>()->Init(0.0f, m_Position.y, SCREEN_WIDTH, SCREEN_HEIGHT, "asset/texture/title.jpg");//��̂Ƃǂ����ł��悢

	m_Scale.x = SCREEN_WIDTH;
	m_Scale.y = SCREEN_HEIGHT;

	m_Position.x = 0.0f;
	m_Position.y = 0.0f;


	m_Sprite = AddComponent<Sprite>();
	m_Sprite->Init(m_Position.x, m_Position.y, m_Scale.x, m_Scale.y, "asset/texture/pressSPACE.png");//��̂Ƃǂ����ł��悢

	
}

void TitleEnter::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Uninit();
}

void TitleEnter::Update()
{
	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Update();

	
	if (!m_IsPressEnter)
	{
		//���l�ύX
		if (m_Color.a >= 1.0f)
		{
			m_IsAlphaReturn = false;
		}
		else if (m_Color.a <= 0.0f)
		{
			m_IsAlphaReturn = true;

		}
		if (!m_IsAlphaReturn)
		{
			m_Color.a -= 0.05f;
		}
		else
		{
			m_Color.a += 0.05f;
		}
	}
	

	m_Sprite->SetColor(m_Color);

	if (Input::GetKeyPress(VK_SPACE))
	{
		m_IsPressEnter = true;
	}
}

void TitleEnter::Draw()
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