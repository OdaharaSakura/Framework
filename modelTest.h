#pragma once

#include "model.h"
#include "gameObject.h"

#include<vector>

enum ModelType
{
	TYPE_1,
	TYPE_2,
	TYPE_3
};
class ModelTest : public GameObject//åpè≥
{
private:
	std::vector<Model*> m_Models{};
	std::vector<D3DXVECTOR3> m_ModelPositions{};
public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};
