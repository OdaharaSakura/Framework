#pragma once

#include "scene.h"

class Game : public Scene
{
private:
	class Fade* m_Fade = nullptr;
	class EquipmentObj* m_EquipmentObj = nullptr;
	class Player* m_Player = nullptr;
	class Time* m_Time = nullptr;
	class FarmField* m_FarmField = nullptr;
	class IEquipment* m_Equipment = nullptr;
	class Inventory* m_Inventory = nullptr;
	class SceneDescription* m_SceneDescription = nullptr;

	class EnemyObserver* m_EnemyObserver = nullptr;
	class UIObserver* m_UIObserver = nullptr;

	static bool m_LoadFinish;

public:
	static void Load();
	static void Unload();
	static bool GetLoadFinish() { return m_LoadFinish; }

	void Init() override;
	void Uninit() override;
	void Update() override;
};
