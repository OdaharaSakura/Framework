#include "main.h"
#include "renderer.h"
#include "gaugeframe.h"
#include "sprite.h"
#include "input.h"
#include "shader.h"

void GaugeFrame::Init()
{
	AddComponent<UnlitTexture>();
	m_GaugeFrame = AddComponent<Sprite>();
	m_GaugeFrame->Init(70.0f, SCREEN_HEIGHT - 90.0f, 320.0f, 70.0f, "asset/texture/gauge_frame.dds");

}

void GaugeFrame::Uninit()
{

	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Uninit();
}

void GaugeFrame::Update()
{
	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Update();

}

void GaugeFrame::Draw()
{

	// �}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Draw();
}