#pragma once
#include "gameObject.h"

class Model;

class StaticObject : public GameObject//�p��
{
private:
	Model* m_Model;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetModel_Key(std::string model_Key);
};
