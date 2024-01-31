#pragma once
#include "GameObject.h"

class EquipmentView :public GameObject
{
private:
	class IEquipment* m_EquipmentInterface;
	class EquipmentPanel* m_EquipmentPanel;
	class EquipmentIcon* m_EquipmentIcon;
public:
	void Init();
	void Uninit();
	void Update();

	void SetEquipmentInterface(class IEquipment* equipment) { m_EquipmentInterface = equipment; }
};