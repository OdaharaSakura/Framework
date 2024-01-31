
#include "main.h"
#include "manager.h"
#include "scene.h"
#include "iEquipment.h"
#include "equipment.h"
#include "equipmentView.h"

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
