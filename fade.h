#pragma once

#include "gameObject.h"
class Fade : public GameObject
{
private:

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	class Sprite* m_Sprite{};

	float m_Alpha = 1.0f;
	bool m_IsFadeOut = false;//true:Å®çï
	bool m_IsFadeOutFinish = false;
	float m_Fadespeed = 0.025f;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetIsFadeOut() { m_IsFadeOut = true; }
	float GetAlpha() { return m_Alpha; }
	bool GetFadeOutFinish() { return m_IsFadeOutFinish; }
	void SetFadeSpeed(float speed) { m_Fadespeed = speed; }
};
