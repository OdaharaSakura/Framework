#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "sceneDescription.h"
#include "text.h"
#include "sprite.h"
#include "input.h"
#include "shader.h"


void SceneDescription::Init()
{
	Scene* scene = Manager::GetScene();
	AddComponent<UnlitTexture>();

	m_Description = AddComponent<Text>();
	m_Description->SetPosition(D3DXVECTOR2(SCREEN_WIDTH / 3, SCREEN_HEIGHT - 50.0f));
}

void SceneDescription::Uninit()
{
	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Uninit();
}

void SceneDescription::Update()
{
	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Update();

}

void SceneDescription::Draw()
{

	// �}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Draw();
}

void SceneDescription::SetDescriptionText(std::string text)
{
	m_Description->SetText(text);
}

void SceneDescription::SetDescriptionPosition(D3DXVECTOR2 position)
{
	m_Description->SetPosition(position);
}

void SceneDescription::SetDescriptionTextSize(float size)
{
	m_Description->SetFontSize(size);
}
