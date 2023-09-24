#pragma once

#include "gameObject.h"
class Gauge : public GameObject
{
private:

	static ID3D11Buffer* m_VertexBuffer;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};


	//�q�b�g�|�C���g�֘A
	int m_Hp;		//���݂̃q�b�g�|�C���g
	int m_HpMax;	//�ő�q�b�g�|�C���g
	int m_HpOld;

	class Player* m_PlayerParent{};//gameobject�̌^���g���������ǂ�
	class Enemy* m_EnemyParent;//gameobject�̌^���g���������ǂ�
	class TreasureBox* m_BoxParent;//gameobject�̌^���g���������ǂ�

public:
	static void Load();
	static void Unload();
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetPlayerParent(Player* Parent) { m_PlayerParent = Parent; }
	void SetEnemyParent(Enemy* Parent) { m_EnemyParent = Parent; }
	void SetBoxParent(TreasureBox* Parent) { m_BoxParent = Parent; }
};