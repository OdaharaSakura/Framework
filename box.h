#pragma once

#include "model.h"
#include "gameObject.h"
class Box : public GameObject//�p��
{
private:
	Model* m_Model{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11ShaderResourceView* m_Texture{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};
