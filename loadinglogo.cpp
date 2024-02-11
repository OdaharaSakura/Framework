#include "main.h"
#include "renderer.h"
#include "loadinglogo.h"
#include "sprite.h"

#include <cmath>

void LoadingLogo::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");


	m_WorldPosition.x = 0.0f;
	m_WorldPosition.y = 0.0f;

	m_Sprite = AddComponent<Sprite>();
	m_Sprite->Init(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, "asset/texture/Waitwindow.dds");//��̂Ƃǂ����ł��悢

	m_Sprite = AddComponent<Sprite>();
	m_Sprite->Init(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, "asset/texture/Loading.dds");//��̂Ƃǂ����ł��悢


}

void LoadingLogo::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Uninit();
}

void LoadingLogo::Update()
{
	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Update();


	//�㉺�ړ�
	m_Sprite->SetPositionY(m_WorldPosition.y + (std::sinf(m_Rot) * 15));;

	m_Rot += 0.05f;
	if (m_Rot >= 360.0f)
		m_Rot = 0.0f;

}

void LoadingLogo::Draw()
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