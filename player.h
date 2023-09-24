#pragma once

#include "model.h"
#include "gameObject.h"
#include <string>

enum PLAYER_STATE
{
	PLAYER_STATE_GROUND, 
	PLAYER_STATE_JUMP,
	PLAYER_STATE_ATTACK
};

class Player : public GameObject//�p��
{
private:
	int m_PlayerState = PLAYER_STATE_GROUND;
	bool m_IsGround{};

	class AnimationModel* m_Model{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	D3DXVECTOR3			m_Velocity{};

	class Audio* m_ShotSE{};
	class Shadow* m_Shadow{};
	class MeshField* m_MeshField{};

	int m_Hp;
	int m_HpMax = 300;

	int m_Time{};
	std::string m_AnimationName;
	std::string m_NextAnimationName;
	float m_BlendRate{};

	int m_AnimeState{};
	int m_AnimeFrame{};
	int m_AttackDelaynum{};

	bool m_IsAttackflg{};//�A�^�b�N�ł��邩(�G�͈͓̔��ɓ�������)
	bool m_Attackflg{};//�U��������

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
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void UpdateGround();//�X�e�[�g�p�^�[���ŏ����Ă݂�
	void UpdateJump();
	void UpdateAttack();

	int GetHp() { return m_Hp;}
	int GetHpMax() {return m_HpMax;}
	bool GetAttackflg() { return m_Attackflg; }
	void SetnonAttackflg() { m_Attackflg = false; }


};
