#pragma once
#include "savedata.h"

class SaveDataManager
{
private:
	static SaveData m_SaveData;

public:
	static void Save(int sceneIndex);
	static void Load(
		class FarmField* farmField,
		class Inventory* inventory,
		class IEquipment* iEquipment,
		class Player* player,
		class Time* time);

	static void Load(
		class Inventory* inventory,
		class IEquipment* iEquipment,
		class Player* player,
		class Time* time
		);

	static void Delete();

};