#include "main.h"
#include "manager.h"
#include "scene.h"
#include "iEquipment.h"
#include "equipmentView.h"
#include "equipmentFactory.h"

void IEquipment::Init()
	{
		Scene* scene = Manager::GetScene();
	
		m_IsStatic = true;
		EquipmentView* equipmentView = scene->AddGameObject<EquipmentView>(LAYER_OBJECT_NOTDRAW);
		equipmentView->SetEquipmentInterface(this);
	}

void IEquipment::SetEquipment(Equipment* equipment)
{
	if (m_Equipment != nullptr)
	{
		RemoveEquipment();
	}
	m_Equipment = equipment;
}

void IEquipment::SetEquipmentInName(Equipment* equipment)
{
	if (m_Equipment != nullptr)
	{
		RemoveEquipment();
	}
	m_Equipment = equipment;
}

void IEquipment::RemoveEquipment()
{
	delete m_Equipment;
	m_Equipment = nullptr;
}

void IEquipment::ExecuteEquipment()
{
	if (m_Equipment) {
		m_Equipment->Execute();
	}
}

void IEquipment::Load(PlayerData playerdata)
{
	auto equipmentFactory = new EquipmentFactory();
	auto equipment = equipmentFactory->CreateEquipment(playerdata.equipmentItemKey);
	if (equipment == nullptr) return;
    SetEquipment(equipment);
}
