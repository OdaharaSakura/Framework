#pragma once

#include "animationModel.h"
#include "gameObject.h"
class Enemy : public GameObject//継承
{
private:
	AnimationModel* m_Model;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	class Gauge* m_Gauge{};

	D3DXVECTOR3 m_StartPosition{};
	D3DXVECTOR3 m_ModelScale{};
	D3DXVECTOR3 m_StartScale{};


	int m_Hp;
	int m_HpMax = 300;

	float test = 0.005f;
	bool m_Startflg;

	int m_Time{};
	int m_AnimeState{};
	int m_AnimeFrame{};
	int m_AttackDelaynum{};

	std::string m_AnimationName;
	std::string m_NextAnimationName;
	float m_BlendRate{};

	bool m_IsAttackflg{};//アタックできるか
	bool m_Attackflg{};//攻撃したか

	enum Animation {
		IDOL,
		RUN,
		ATTACK,
		DAMAGE
	};

public:
	void Load();
	void Unload();
	void Init();
	void Uninit();
	void Update();
	void Draw();

	int GetHp() { return m_Hp; }
	int GetHpMax() { return m_HpMax; }

	bool GetAttackflg() { return m_Attackflg; }
	void SetNonAttackflg() { m_Attackflg = false; }

	D3DXMATRIX* CalcLookAtMatrixAxisFix(
		D3DXMATRIX* pout,
		D3DXVECTOR3* pPos,
		D3DXVECTOR3* pLook,
		D3DXVECTOR3* pUp
	);
};
