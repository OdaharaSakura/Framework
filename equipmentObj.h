#pragma once
#include "gameObject.h"

class Model;
class EquipmentObj : public GameObject//åpè≥
{
private:
	D3DXVECTOR3 m_worldPosition;

public:

	Model* m_Model{};
	D3DXMATRIX m_pMatrix;

	void Init() override;

	void Uninit() override {}
	void Update() override;
	void Draw() override;
};
