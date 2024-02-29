#pragma once
#include "gameObject.h"
#include "savedata.h"
#include "equipment.h"
#include <string>

class IEquipment : public GameObject
{
private:
	Equipment* m_Equipment{};
public:
	void Init();
	void Uninit(){}
	void Update(){}


	void SetEquipment(Equipment* equipment);
	void SetEquipmentInName(Equipment* equipment);
	void RemoveEquipment();
	Equipment* GetEquipment() { return m_Equipment; };
	std::string GetEquipmentKey() 
	{
		std::string key{};
		if(m_Equipment == nullptr) return key;
		key = m_Equipment->GetKey();
		return key;
	};

	void ExecuteEquipment();
	void Load(PlayerData playerdata);
};