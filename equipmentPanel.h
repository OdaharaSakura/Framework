#pragma once
#include "GameObject.h"

class EquipmentPanel :public GameObject
{
private:

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};