#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "shader.h"
#include "inventoryView.h"
#include "inventory.h"
#include "inventoryPanel.h"
#include "inventoryItemIcon.h"
#include "inventoryItemCursor.h"
#include "inventoryItemDescription.h"

void InventoryView::Init()
{
	Scene* scene = Manager::GetScene();
	//�A�C�e���̐��ɉ����đ��₷
	m_InventoryPanel = scene->AddGameObject<InventoryPanel>(LAYER_OBJECT_2D);
	m_InventoryItemIcon = scene->AddGameObject<InventoryItemIcon>(LAYER_OBJECT_2D);
	m_InventoryItemCursor = scene->AddGameObject<InventoryItemCursor>(LAYER_OBJECT_2D);
	

	m_InventoryPanel->SetIsActive(false);
	m_InventoryItemIcon->SetIsActive(false);
	m_InventoryItemCursor->SetIsActive(false);

}


void InventoryView::Uninit()
{
	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Uninit();
}

void InventoryView::Update()
{
	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Update();
}

void InventoryView::ShowInventory()
{
	Scene* scene = Manager::GetScene();
	m_InventoryItemIcon->SetIsActive(true);
	m_InventoryPanel->SetIsActive(true);
	m_InventoryItemCursor->SetIsActive(true);
	m_InventoryItemDescription = scene->AddGameObject<InventoryItemDescription>(LAYER_OBJECT_2D);
	
}

void InventoryView::HideInventory()
{
	m_InventoryItemIcon->SetIsActive(false);
	m_InventoryPanel->SetIsActive(false);
	m_InventoryItemCursor->SetIsActive(false);
	m_InventoryItemDescription->SetDestroy();
}
