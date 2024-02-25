#pragma once

#include "model.h"
#include "gameObject.h"

class ResultPlayer : public GameObject//åpè≥
{
private:
	//Model* m_Model{};
	class AnimationModel* m_Model{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	D3DXVECTOR3			m_Velocity{};

	class Audio* m_ShotSE{};
	class Shadow* m_Shadow{};


	int m_AnimeState{};
	int m_AnimeFrame{};
	float m_BlendRate{};

	bool m_IsClearflg{};//çUåÇÇµÇΩÇ©


public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetIsClearflg() { m_IsClearflg = true; }
};
