#include "main.h"
#include "renderer.h"
#include "titlelogo.h"
#include "sprite.h"

#include <cmath>

void TitleLogo::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");
	//Sprite* sprite = AddComponent<Sprite>();
	//sprite->Init(0.0f, 0.0f, 200.0f, 200.0f, "asset/texture/field004.jpg");

	//AddComponent<Sprite>()->Init(0.0f, m_Position.y, SCREEN_WIDTH, SCREEN_HEIGHT, "asset/texture/title.jpg");//��̂Ƃǂ����ł��悢

	m_Scale.x = SCREEN_WIDTH/3 * 2;
	m_Scale.y = SCREEN_HEIGHT/3 * 2;

	m_Position.x = (SCREEN_WIDTH / 2) - (m_Scale.x / 2);
	m_Position.y = (SCREEN_HEIGHT / 3) - (m_Scale.y / 2) + 15.0f;


	m_Sprite = AddComponent<Sprite>();
	m_Sprite->Init(m_Position.x, m_Position.y, m_Scale.x, m_Scale.y, "asset/texture/TitleLogo.png");//��̂Ƃǂ����ł��悢

	
}

void TitleLogo::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Uninit();
}

void TitleLogo::Update()
{
	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Update();


	//�㉺�ړ�
	m_Sprite->SetPositionY(m_Position.y + (std::sinf(m_Rot) * 15));;

	m_Rot += 0.05f;
	if (m_Rot >= 360.0f)
		m_Rot = 0.0f;

}

void TitleLogo::Draw()
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