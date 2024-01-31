#pragma once

#include "gameObject.h"

class Road : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11Buffer* m_IndexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

};


