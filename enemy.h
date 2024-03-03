#pragma once

#include "animationModel.h"
#include "gameObject.h"

enum ENEMY_STATE
{
	EnemyState_Wait,
	EnemyState_Tracking,
	EnemyState_Attack,
	EnemyState_Damage,
	EnemyState_Death
};

class Enemy : public GameObject//継承
{
private:
	AnimationModel* m_Model;

	class Gauge* m_Gauge{};

	D3DXVECTOR3 m_StartPosition{};
	D3DXVECTOR3 m_ModelScale{};
	D3DXVECTOR3 m_StartScale{};

	int m_EnemyState = EnemyState_Wait;
	int m_Hp;
	int m_HpMax = 300;

	float test = 0.005f;


	int m_Time{};
	int m_AnimeFrame{};
	int m_AttackDelaynum{};

	int m_AnimationIndex;
	int m_NextAnimationIndex;
	float m_BlendRate{};

	bool m_IsDamageflg{};//プレイヤーがアタックできるか
	bool m_Startflg{};//初期化フラグ

public:
	void Load();
	void Unload();
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void UpdateAnimation(int enemyAnimation);

	void UpdateWait();
	void UpdateTracking();
	void UpdateAttack();
	void UpdateDamage();
	void UpdateDeath();

	bool CheckPlayerDistance(float distance);

	void AddHp(int hp);
	int GetHp() { return m_Hp; }
	int GetHpMax() { return m_HpMax; }

	bool GetDamageflg() { return m_IsDamageflg; }
	void SetDamageflg(bool isDamage) { m_IsDamageflg = isDamage; }

	D3DXMATRIX* CalcLookAtMatrixAxisFix(
		D3DXMATRIX* pout,
		D3DXVECTOR3* pPos,
		D3DXVECTOR3* pLook,
		D3DXVECTOR3* pUp
	);
};
