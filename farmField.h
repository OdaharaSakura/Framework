#pragma once

#include "gameObject.h"

class FarmTile;

class FarmField : public GameObject 
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11Buffer* m_IndexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};

	const int m_Maxfieldx = 8;
	const int m_Maxfieldz = 11;

	std::vector<FarmTile*> m_FarmTiles;
	

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	std::vector<FarmTile*> GetFarmTiles() { return m_FarmTiles; }
};


