#pragma once
#include "GameObject.h"

class InventoryPanel :public GameObject
{
private:
	class StaticSprite* m_StaticSprite{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};