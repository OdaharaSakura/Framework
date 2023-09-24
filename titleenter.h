#pragma once

#include "gameObject.h"
class TitleEnter : public GameObject
{
private:
	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	class Sprite* m_Sprite;

	D3DXCOLOR m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	bool m_IsAlphaReturn = false;

	bool m_IsPressEnter = false;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool GetIsPressEnter() { return m_IsPressEnter; }
	void SetAlpha(float a) { m_Color.a = a; }
};
