#pragma once
#include "gameObject.h"

class Post : public GameObject
{
private:

	ID3D11Buffer*				m_VertexBuffer = NULL;

	//ここに	シェーダー関連の変数を追加
	ID3D11VertexShader*	m_VertexShader;
	ID3D11PixelShader*	m_PixelShader;
	ID3D11InputLayout*	m_VertexLayout;

	float	m_Threshold;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();


};