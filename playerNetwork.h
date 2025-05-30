#pragma once

#include "model.h"
#include "gameObject.h"
#include "player.h"
#include <string>
#include <vector>

class PlayerNetWork : public GameObject//継承
{
private:
	int m_PlayerState = PLAYER_STATE_GROUND;
	bool m_IsGround{};


	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	D3DXVECTOR3			m_Velocity{};
	D3DXVECTOR3			m_ModelScale{};
	D3DXQUATERNION		m_Quaternion{};

	class Audio* m_ShotSE{};
	class MeshField* m_MeshField{};

	int m_Hp;
	int m_HpMax = 300;

	int m_Time{};
	int m_AnimationIndex;
	int m_NextAnimationIndex;
	float m_BlendRate{};

	int m_AnimeState{};
	int m_AnimeFrame{};
	int m_AttackDelaynum{};

	bool m_IsAttackflg{};//アタックできるか(敵の範囲内に入ったら)
	bool m_Attackflg{};//攻撃したか

	std::vector<D3DXVECTOR3> m_PositionList{};

	enum Animation {
		IDOL,
		RUN,
		LEFTRUN,
		RIGHTRUN,
		BACKRUN,
		ATTACK,
		DEATH
	};

public:
	class AnimationModel* m_Model{};

	void Init();
	void Uninit();
	void Update();
	void Draw();
	void UpdateGround();//ステートパターンで書いてみる
	void UpdateJump();
	void UpdateAttack();

	D3DXVECTOR3 GetForward()//前方向ベクトル取得
	{
		D3DXMATRIX rot;
		//D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);
		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}

	D3DXVECTOR3 GetRight()//右方向ベクトル取得
	{
		D3DXMATRIX rot;
		//D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);
		D3DXVECTOR3 right;
		right.x = rot._11;
		right.y = rot._12;
		right.z = rot._13;

		return right;
	}


	D3DXVECTOR3 GetTop()//上方向ベクトル取得
	{
		D3DXMATRIX rot;
		//D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);
		D3DXVECTOR3 top;
		top.x = rot._21;
		top.y = rot._22;
		top.z = rot._23;

		return top;
	}

	int GetHp() { return m_Hp;}
	int GetHpMax() {return m_HpMax;}
	bool GetAttackflg() { return m_Attackflg; }
	void SetNonAttackflg() { m_Attackflg = false; }

	void SetPositionList(D3DXVECTOR3 position) { m_PositionList.push_back(position); }
};
