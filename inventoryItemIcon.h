#pragma once
#include "GameObject.h"

class InventoryItemIcon :public GameObject
{
private:
	class StaticSprite* m_StaticSprite{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};