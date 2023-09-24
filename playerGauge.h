#pragma once

#include "gameObject.h"
class PlayerGauge : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = nullptr;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	//�q�b�g�|�C���g�֘A
	int m_Hp;		//���݂̃q�b�g�|�C���g
	int m_HpMax;	//�ő�q�b�g�|�C���g
	int m_HpOld;

	class Player* m_PlayerParent{};//gameobject�̌^���g���������ǂ�

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetPlayerParent(Player* Parent) { m_PlayerParent = Parent; }
};
