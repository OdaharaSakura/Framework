#pragma once
#include "GameObject.h"

class EquipmentIcon :public GameObject
{
private:
	class StaticSprite* m_StaticSprite{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};