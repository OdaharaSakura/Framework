#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "inventoryItemDescription.h"
#include "text.h"
#include "sprite.h"
#include "input.h"
#include "shader.h"


void InventoryItemDescription::Init()
{
	Scene* scene = Manager::GetScene();
	AddComponent<UnlitTexture>();

	m_ItemText[0] = scene->AddGameObject<GameObject>(LAYER_OBJECT_2D);
	m_ItemNametext = m_ItemText[0]->AddComponent<Text>();
	m_ItemText[1] = scene->AddGameObject<GameObject>(LAYER_OBJECT_2D);
	m_ItemTypeText = m_ItemText[1]->AddComponent<Text>();
	m_ItemText[2] = scene->AddGameObject<GameObject>(LAYER_OBJECT_2D);
	m_ItemDescriptionText = m_ItemText[2]->AddComponent<Text>();


	m_ItemNametext->SetPosition(D3DXVECTOR2(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 5 * 3.5f));
	m_ItemNametext->SetFontColor(D2D1::ColorF::Brown);
	SetText(m_ItemNametext, "����");

	m_ItemTypeText->SetPosition(D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 5 * 3.5f));
	m_ItemTypeText->SetFontColor(D2D1::ColorF::Gray);
	SetText(m_ItemTypeText, "��ށF����");

	m_ItemDescriptionText->SetPosition(D3DXVECTOR2(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 5 * 3.75f));
	m_ItemDescriptionText->SetFontColor(D2D1::ColorF::Black);
	SetText(m_ItemDescriptionText, "�����k���铹��B");
}

void InventoryItemDescription::Uninit()
{
	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Uninit();
	for (int i = 0; i < 3; i++)
	{
		m_ItemText[i]->SetDestroy();
	}
}

void InventoryItemDescription::Update()
{
	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Update();
}

void InventoryItemDescription::Draw()
{

	// �}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Draw();
}

void InventoryItemDescription::SetText( Text* textptr, const std::string& text)
{
	textptr->SetText(text);
}
