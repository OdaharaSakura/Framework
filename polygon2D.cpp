#include "main.h"
#include "renderer.h"
#include "polygon2D.h"
#include "sprite.h"
#include "DirectWrite.h"

void Polygon2D::Init()
{
	FontData* data = new FontData();

	data->fontSize = 40;
	
	Write = new DirectWrite(data);
	
	Write->Init();

	testtext = "�����o�̓e�X�g";

	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");
	//Sprite* sprite = AddComponent<Sprite>();
	//sprite->Init(0.0f, 0.0f, 200.0f, 200.0f, "asset/texture/field004.jpg");

	AddComponent<Sprite>()->Init(SCREEN_WIDTH- 200.0f, SCREEN_HEIGHT- 200.0f, 200.0f, 200.0f, "asset/texture/setsumei.png");//��̂Ƃǂ����ł��悢
	//AddComponent<Sprite>()->Init(300.0f, 300.0f, 200.0f, 200.0f, "asset/texture/kizuna.jpg");
}

void Polygon2D::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Uninit();
}

void Polygon2D::Update()
{
	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Update();
}

void Polygon2D::Draw()
{
	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	// �V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);



	// �}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	Write->DrawString(testtext, D2D1::RectF(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT), D2D1_DRAW_TEXT_OPTIONS_NONE);

	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Draw();
}