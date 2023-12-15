#pragma once

#include "gameObject.h"
#include <string>
class Polygon2D : public GameObject
{
private:


public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};
