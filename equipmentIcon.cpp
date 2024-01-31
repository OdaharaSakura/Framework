#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "shader.h"
#include "equipmentIcon.h"
#include "iEquipment.h"
#include "staticSprite.h"
#include "shader.h"


void EquipmentIcon::Init()
{
	AddComponent<UnlitTexture>();

	m_Scale.x = 140.0f;
	m_Scale.y = 100.0f;
	std::string key = "Hoe";
	std::string path = "equipment_icon_kuwa.dds";
	m_StaticSprite = AddComponent<StaticSprite>();//��̂Ƃǂ����ł��悢
	m_StaticSprite->Init(SCREEN_WIDTH - m_Scale.x, SCREEN_HEIGHT - m_Scale.y - 10.0f, m_Scale.x, m_Scale.y, key, path);
}

void EquipmentIcon::Uninit()
{
	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Uninit();
}

void EquipmentIcon::Update()
{
	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Update();

}

void EquipmentIcon::Draw()
{
	// �}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Draw();
}
