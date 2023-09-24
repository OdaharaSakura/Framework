#pragma once

#include "gameObject.h"
class PlayerGauge : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = nullptr;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	//ヒットポイント関連
	int m_Hp;		//現在のヒットポイント
	int m_HpMax;	//最大ヒットポイント
	int m_HpOld;

	class Player* m_PlayerParent{};//gameobjectの型を使った方が良い

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetPlayerParent(Player* Parent) { m_PlayerParent = Parent; }
};
