#pragma once
#include "gameObject.h"
class Camera : public GameObject
{

private:

	D3DXVECTOR3	m_Target{};
	float	m_Rotation{};
	D3DXMATRIX m_ViewMatrix{};
	D3DXMATRIX m_ProjectionMatrix{};

	float	m_ShakeAmplitude{};
	int		m_ShakeTime{};
	float	m_ShakeOffset{};


public:
	void Init() override;
	void Update() override;
	void Draw() override;

	D3DXVECTOR3 GetForward()//前方向ベクトル取得
	{
		D3DXMATRIX rot;
		/*D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);*/
		D3DXMatrixInverse(&rot, nullptr, &m_ViewMatrix);
		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}

	D3DXVECTOR3 GetRight()//前方向ベクトル取得
	{
		D3DXMATRIX rot;
		/*D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);*/
		D3DXMatrixInverse(&rot, nullptr, &m_ViewMatrix);
		D3DXVECTOR3 right;
		right.x = rot._11;
		right.y = rot._12;
		right.z = rot._13;

		return right;
	}

	D3DXMATRIX GetViewMatrix() { return m_ViewMatrix; }

	void Shake(float Amplitude)
	{
		m_ShakeAmplitude = Amplitude;
	}

	bool CheckView(D3DXVECTOR3 Position);

};