#pragma once

#include "gameObject.h"
class Field : public GameObject
{
private:


	ID3D11Buffer*			m_VertexBuffer{};
	ID3D11Buffer*			m_IndexBuffer{};
	int						m_numVertex = 0;
	int						m_numIndex = 0;
	ID3D11ShaderResourceView* m_Texture{};
	ID3D11ShaderResourceView* m_TextureNormal{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};


