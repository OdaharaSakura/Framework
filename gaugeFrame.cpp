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
	m_GaugeFrame->Init(SCREEN_WIDTH - 200.0f, 20.0f, 180.0f, 24.0f, "asset/texture/GaugeFrame.dds");

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