#pragma once

#include "gameObject.h"
#include "savedata.h"
#include <vector>
class FarmTile;
class Player;
class FarmField : public GameObject 
{
private:
	ID3D11Buffer* m_VertexBuffer{};
	ID3D11Buffer* m_IndexBuffer{};
	ID3D11ShaderResourceView* m_Texture{};

	const int m_Maxfieldx = 8;
	const int m_Maxfieldz = 11;

	std::vector<FarmTile*> m_FarmTiles;
	Player* m_Player{};

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;

	std::vector<FarmTile*> GetFarmTiles() { return m_FarmTiles; }
	FarmTile* GetFarmTileClosestToPlayer(int state);
	FarmTile* GetFarmTileClosestToPlayer(int state1, int state2);

	void LoadFarmTileData(std::vector<FarmTileData> farmTileData);
};


