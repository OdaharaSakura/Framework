#include "main.h"
#include "equipment.h"

void IEquipment::AddEquipment(Equipment* equipment)
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
