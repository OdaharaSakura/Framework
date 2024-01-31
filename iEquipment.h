#pragma once
#include "gameObject.h"

class Equipment;

class IEquipment : public GameObject
{
private:
	Equipment* m_Equipment;
public:
	void Init();
	void Uninit(){}
	void Update(){}


	void SetEquipment(Equipment* equipment);
	void SetEquipmentInName(Equipment* equipment);
	void RemoveEquipment();
	Equipment* GetEquipment() { return m_Equipment; };

	void ExecuteEquipment();
};