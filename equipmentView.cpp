#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "shader.h"
#include "equipmentView.h"
#include "iEquipment.h"
#include "equipmentPanel.h"
#include "equipmentIcon.h"
#include "sprite.h"
#include "shader.h"

void EquipmentView::Init()
{
	Scene* scene = Manager::GetScene();

	m_EquipmentPanel = scene->AddGameObject<EquipmentPanel>(LAYER_OBJECT_2D);
	m_EquipmentIcon = scene->AddGameObject<EquipmentIcon>(LAYER_OBJECT_2D);
}

void EquipmentView::Uninit()
{
	//基底クラスのメソッド呼び出し
	GameObject::Uninit();
}

void EquipmentView::Update()
{
	//基底クラスのメソッド呼び出し
	GameObject::Update();
}
