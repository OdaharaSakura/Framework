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

	m_Scale.x = SCREEN_WIDTH / 3 * 2;
	m_Scale.y = SCREEN_HEIGHT / 3 * 2;

	m_WorldPosition.x = (SCREEN_WIDTH / 2) - (m_Scale.x / 2);
	m_WorldPosition.y = (SCREEN_HEIGHT / 3) - (m_Scale.y / 2) + 15.0f;


	m_Sprite = AddComponent<Sprite>();
	m_Sprite->Init(m_WorldPosition.x, m_WorldPosition.y, m_Scale.x, m_Scale.y, "asset/texture/Loading.png");//��̂Ƃǂ����ł��悢


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