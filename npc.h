#pragma once

#include "gameObject.h"

#include <string>
class NPC : public GameObject//åpè≥
{
private:
	class AnimationModel* m_Model;

	D3DXVECTOR3 m_StartPosition{};

	std::string m_Conversation;
	bool m_IsHitPlayer = false;

	int m_Time{};
	int m_AnimeState{};
	int m_AnimeFrame{};

	std::string m_AnimationIndex;
	std::string m_NextAnimationIndex;
	float m_BlendRate{};

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

	std::string GetConversation() { return m_Conversation; }
	bool GetIsHitPlayer() { return m_IsHitPlayer; }


	D3DXMATRIX* CalcLookAtMatrixAxisFix(
		D3DXMATRIX* pout,
		D3DXVECTOR3* pPos,
		D3DXVECTOR3* pLook,
		D3DXVECTOR3* pUp
	);
};
