#pragma once
#include "gameObject.h"
class ResultCamera : public GameObject
{

private:

	D3DXVECTOR3	m_Target{};
	D3DXMATRIX m_ViewMatrix{};
	D3DXVECTOR3 offset = D3DXVECTOR3(0.0f, 1.0f, 0.0f); 

public:
	void Init() override;
	void Update() override;
	void Draw() override;

	D3DXMATRIX GetViewMatrix() { return m_ViewMatrix; }

	void Setoffset(D3DXVECTOR3 position) { offset = position; }
};