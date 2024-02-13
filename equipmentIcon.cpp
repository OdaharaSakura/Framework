#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "shader.h"
#include "equipmentIcon.h"
#include "iEquipment.h"
#include "staticSprite.h"
#include "shader.h"
#include "equipment.h"


void EquipmentIcon::Init()
{
	AddComponent<UnlitTexture>();

	m_Scale.x = 100.0f;
	m_Scale.y = 100.0f;

	m_StaticSprite = AddComponent<StaticSprite>();//上のとどっちでもよい
	m_StaticSprite->SetPosition(D3DXVECTOR2(SCREEN_WIDTH - m_Scale.x - 15.0f, SCREEN_HEIGHT - m_Scale.y - 10.0f));
	m_StaticSprite->SetScale(D3DXVECTOR2(m_Scale.x, m_Scale.y));

}

void EquipmentIcon::Uninit()
{
	//基底クラスのメソッド呼び出し
	GameObject::Uninit();
}

void EquipmentIcon::Update()
{
	//基底クラスのメソッド呼び出し
	GameObject::Update();
	Scene *scene = Manager::GetScene();

	IEquipment* iEquipment = scene->GetGameObject<IEquipment>();
	if (iEquipment != nullptr)
	{
		Equipment* equipment = iEquipment->GetEquipment();
		if (equipment)
		{
			m_StaticSprite->SetIsEnable(true);
			m_StaticSprite->SetTexture(equipment->GetKey(), equipment->GetTexturePass());
		}
		else
		{
			m_StaticSprite->SetIsEnable(false);
		}
		
	}

}

void EquipmentIcon::Draw()
{
	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//基底クラスのメソッド呼び出し
	GameObject::Draw();
}
