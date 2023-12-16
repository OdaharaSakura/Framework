#pragma once

#include "gameObject.h"
class Alpha : public GameObject
{
private:
	class Sprite* m_Sprite[2]{};
	float m_Rot = 180.0f;

	ID3D11ShaderResourceView* m_Texture[2]{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();


};
