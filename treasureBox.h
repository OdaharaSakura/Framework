#pragma once

#include "model.h"
#include "gameObject.h"
class TreasureBox : public GameObject//継承
{
private:
	static Model* m_Model;

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

	bool m_IsAttackflg{};//アタックできるか
	bool m_Attackflg{};//攻撃したか

	enum Animation {
		IDOL,
		RUN,
		ATTACK,
		DAMAGE
	};

public:
	static void Load();
	static void Unload();
	void Init();
	void Uninit();
	void Update();
	void Draw();

	int GetHp() { return m_Hp; }
	int GetHpMax() { return m_HpMax; }

	bool GetAttackflg() { return m_Attackflg; }
	void SetnonAttackflg() { m_Attackflg = false; }

};
