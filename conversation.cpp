#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "conversation.h"
#include "text.h"
#include "sprite.h"
#include "input.h"
#include "shader.h"


void Conversation::Init()
{
	Scene* scene = Manager::GetScene();
	AddComponent<UnlitTexture>();
	AddComponent<Sprite>()->Init(30.0f, SCREEN_HEIGHT - 200.0f, 1200.0f, 192.0f, "asset/texture/window_03.png");//上のとどっちでもよい
	m_Text = scene->AddGameObject<GameObject>(LAYER_OBJECT_2D)->AddComponent<Text>();
	m_Text->SetPosition(D3DXVECTOR2(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 5 * 4));
	m_Text->SetFontColor(D2D1::ColorF::Gray);
}

void Conversation::Uninit()
{
	//基底クラスのメソッド呼び出し
	GameObject::Uninit();
	m_Text->SetText("");
}

void Conversation::Update()
{
	//基底クラスのメソッド呼び出し
	GameObject::Update();

}

void Conversation::Draw()
{

	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//基底クラスのメソッド呼び出し
	GameObject::Draw();
}

void Conversation::SetText(const std::string& text)
{
	m_Text->SetText(text);
}
