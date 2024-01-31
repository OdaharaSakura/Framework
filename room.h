#pragma once

#include "model.h"
#include "gameObject.h"
class Room : public GameObject//åpè≥
{
private:
	Model* m_Model{};


public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};
