#pragma once

#include "gameObject.h"
#include <string>

class GaugeFrame : public GameObject
{
private:
	class Sprite* m_GaugeFrame{};


public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};
