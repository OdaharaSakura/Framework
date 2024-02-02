#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "shader.h"
#include "equipmentPanel.h"
#include "iEquipment.h"
#include "staticSprite.h"
#include "shader.h"

void EquipmentPanel::Init()
{
	AddComponent<UnlitTexture>();

	m_Scale.x = 150.0f;
	m_Scale.y = 100.0f;
	AddComponent<StaticSprite>()->Init(SCREEN_WIDTH - m_Scale.x - 10.0f, SCREEN_HEIGHT - m_Scale.y - 10.0f, m_Scale.x, m_Scale.y, "EquipmentPanel", "equipment_Panel.png");//��̂Ƃǂ����ł��悢
}

void EquipmentPanel::Uninit()
{
	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Uninit();
}

void EquipmentPanel::Update()
{
	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Update();
}

void EquipmentPanel::Draw()
{
	// �}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Draw();
}
