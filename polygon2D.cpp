#include "main.h"
#include "renderer.h"
#include "polygon2D.h"
#include "sprite.h"
#include "input.h"
#include "shader.h"


void Polygon2D::Init()
{
	AddComponent<UnlitTexture>();
	AddComponent<Sprite>()->Init(SCREEN_WIDTH- 200.0f, SCREEN_HEIGHT- 200.0f, 200.0f, 200.0f, "asset/texture/setsumei.png");//��̂Ƃǂ����ł��悢

}

void Polygon2D::Uninit()
{

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

	// �}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Draw();
}