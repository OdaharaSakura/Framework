#pragma once

#include "model.h"
#include "gameObject.h"
class House : public GameObject//�p��
{
private:
	Model* m_Model{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};
