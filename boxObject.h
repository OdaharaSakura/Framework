#pragma once
#include "gameObject.h"

class Model;
class BoxObject : public GameObject//åpè≥
{
private:
	float m_Radius = 1.0f;
public:

	Model* m_Model{};
	D3DXMATRIX m_pMatrix;

	void Init() override;

	void Uninit() override {}
	void Update() override;
	void Draw() override;

	float GetRadius() { return m_Radius; }
	void SetRadius(float radius) { m_Radius = radius; }
};