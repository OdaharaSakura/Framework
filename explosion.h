#pragma once

#include "gameObject.h"
class Explosion : public GameObject
{
private:


	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11ShaderResourceView* m_Texture{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	int m_Count{};
	int width{};
	int height{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};


