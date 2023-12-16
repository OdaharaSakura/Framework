#include "main.h"
#include "renderer.h"
#include "alpha.h"
#include "sprite.h"
#include "shader.h"

#include <cmath>

void Alpha::Init()
{

	m_Scale.x = SCREEN_WIDTH / 4;
	m_Scale.y = SCREEN_HEIGHT / 2;

	m_WorldPosition.x = (SCREEN_WIDTH / 3) - (m_Scale.x / 2);
	m_WorldPosition.y = (SCREEN_HEIGHT / 3) - (m_Scale.y / 2);

	
	AddComponent<AlphaBlending>();

	m_Sprite[0] = AddComponent<Sprite>();
	m_Sprite[0]->Init(m_WorldPosition.x+200, m_WorldPosition.y-150, m_Scale.x/2, m_Scale.y/2, "asset/texture/greenAlpha.png");//��̂Ƃǂ����ł��悢

	m_Sprite[1] = AddComponent<Sprite>();
	m_Sprite[1]->Init(m_WorldPosition.x+ 100, m_WorldPosition.y-50, m_Scale.x/2, m_Scale.y/2, "asset/texture/pinkAlpha.png");//��̂Ƃǂ����ł��悢
	m_Sprite[1]->SetIndex(1);

	

}

void Alpha::Uninit()
{


	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Uninit();
}

void Alpha::Update()
{
	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Update();


	//�㉺�ړ�
	m_Sprite[0]->SetPositionY(m_WorldPosition.y - 50 + (std::sinf(m_Rot) * 15));
	m_Sprite[1]->SetPositionY(m_WorldPosition.y+50 + (std::sinf(m_Rot) * 15));

	m_Rot += 0.05f;
	if (m_Rot >= 360.0f)
		m_Rot = 0.0f;

}

void Alpha::Draw()
{


	// �}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Draw();
}