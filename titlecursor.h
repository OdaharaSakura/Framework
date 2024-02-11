#pragma once

#include "gameObject.h"
class TitleCursor : public GameObject
{
private:

	enum Select {
		SELECT_NULL,
		HAJIME,
		CONTINUE,
		UNINIT
	};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	class Sprite* m_Sprite;
	class Audio* m_ShotSEEnter{};
	class Audio* m_ShotSE2Select{};
	class Fade* m_Fade{};

	D3DXCOLOR m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	D3DXVECTOR3 m_StartPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int m_NextPhase = SELECT_NULL;
	bool m_IsNextPhase = false;
	float m_MoveRange = 80.0f;
	bool m_IsPressEnter = false;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	int GetNextPhase() { return m_NextPhase; }
	bool GetIsPressEnter() { return m_IsPressEnter; }
	void SetAlpha(float a) { m_Color.a = a; }
};
