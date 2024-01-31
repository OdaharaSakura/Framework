#pragma once

#include "gameObject.h"

class FarmField : public GameObject 
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11Buffer* m_IndexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};

	class FarmTile* m_FarmTile[3][3];

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

};


