
#include "main.h"
#include "renderer.h"
#include "farmfield.h"
#include "manager.h"
#include "scene.h"
#include "input.h"
#include "farmTile.h"
#include "image.h"
#include "textureContainer.h"
#include "player.h"


void FarmField::Init()
{
	VERTEX_3D vertex[4];



	vertex[0].Position = D3DXVECTOR3(-1.0f, 0.0f, 1.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(5.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(1.0f, 0.0f, 1.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(-1.0f, 0.0f, -1.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(5.0f, 5.0f);

	vertex[3].Position = D3DXVECTOR3(1.0f, 0.0f, -1.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(0.0f, 5.0f);


	// 頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);


	// テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/sand2.jpg",
		NULL,
		NULL,
		&m_Texture,
		NULL);
	assert(m_Texture);

	m_WorldPosition = D3DXVECTOR3(-15.0f, 0.01f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(7.5f, 1.0f, 10.0f);


	Scene* scene = Manager::GetScene();

	

	for (int z = 0; z < m_Maxfieldz; z++)
	{
		for (int x = 0; x < m_Maxfieldx; x++)
		{
			auto farmtile = scene->AddGameObject<FarmTile>(LAYER_OBJECT_3D);
			farmtile->SetPosition(D3DXVECTOR3(-9.0f - (x * 1.7f), 0.0f, -8.5f + (z * 1.7f)));
			m_FarmTiles.push_back(farmtile);
			
		}
	}	
}


void FarmField::Uninit()
{

	m_VertexBuffer->Release();
	m_Texture->Release();

}


void FarmField::Update()
{

}


void FarmField::Draw()
{

	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_WorldPosition.x, m_WorldPosition.y, m_WorldPosition.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	// 頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::SetMaterial(material);

	// テクスチャ設定
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	// プリミティブトポロジ設定
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// ポリゴン描画
	Renderer::GetDeviceContext()->Draw(4, 0);

}

FarmTile* FarmField::GetFarmTileClosestToPlayer(int state)
{
	Scene* scene = Manager::GetScene();
	m_Player = scene->GetGameObject<Player>();

	D3DXVECTOR3 playerPosition = m_Player->GetPosition();
	D3DXVECTOR3 playerScale = m_Player->GetScale();

	if (m_WorldPosition.x - m_Scale.x - (m_Scale.x / 2) < playerPosition.x &&
		playerPosition.x < m_WorldPosition.x + m_Scale.x + (m_Scale.x / 2) &&
		m_WorldPosition.z - m_Scale.z - (m_Scale.z / 2) < playerPosition.z &&
		playerPosition.z < m_WorldPosition.z + m_Scale.z + (m_Scale.z / 2))
	{
		std::vector<FarmTile*> emptyFarmTiles;

		for (int i = 0; i < m_FarmTiles.size(); i++)
		{
			if (m_FarmTiles[i]->GetFarmTileState() == state)
			{
				emptyFarmTiles.push_back(m_FarmTiles[i]);
			}
		}

		// プレイヤーと一番近いstateのFarmTileを取得（距離の二乗を利用）
		FarmTile* nearestFarmTile = nullptr;
		float nearestDistanceSq = FLT_MAX; // 初期値は非常に大きな値

		for (FarmTile* tile : emptyFarmTiles)
		{
			D3DXVECTOR3 tilePosition = tile->GetPosition();
			// プレイヤーとこのFarmTileとの距離の二乗を計算
			const D3DXVECTOR3 d = tilePosition - playerPosition;
			float distanceSq = D3DXVec3LengthSq(&d);

			// これまでの最小距離の二乗よりも短い場合は、このFarmTileを記録
			if (distanceSq < nearestDistanceSq)
			{
				nearestDistanceSq = distanceSq;
				nearestFarmTile = tile;
			}
		}
		return nearestFarmTile;
	}
	else
	{
		return nullptr;
	}
}

FarmTile* FarmField::GetFarmTileClosestToPlayer(int state1, int state2)
{
	//TODO:プレイヤーとの距離をここで取得する必要なし、farmfieldの中にプレイヤーがいるかどうかの判定を行う
	Scene* scene = Manager::GetScene();
	m_Player = scene->GetGameObject<Player>();

	D3DXVECTOR3 playerPosition = m_Player->GetPosition();
	D3DXVECTOR3 playerScale = m_Player->GetScale();

	if (m_WorldPosition.x - m_Scale.x - (m_Scale.x / 2) < playerPosition.x &&
		playerPosition.x < m_WorldPosition.x + m_Scale.x + (m_Scale.x / 2) &&
		m_WorldPosition.z - m_Scale.z - (m_Scale.z / 2) < playerPosition.z &&
		playerPosition.z < m_WorldPosition.z + m_Scale.z + (m_Scale.z / 2))
	{
		std::vector<FarmTile*> emptyFarmTiles;

		for (int i = 0; i < m_FarmTiles.size(); i++)
		{
			if (m_FarmTiles[i]->GetFarmTileState() == state1 || m_FarmTiles[i]->GetFarmTileState() == state2)
			{
				emptyFarmTiles.push_back(m_FarmTiles[i]);
			}
		}

		// プレイヤーと一番近いstateのFarmTileを取得（距離の二乗を利用）
		FarmTile* nearestFarmTile = nullptr;
		float nearestDistanceSq = FLT_MAX; // 初期値は非常に大きな値

		for (FarmTile* tile : emptyFarmTiles)
		{
			D3DXVECTOR3 tilePosition = tile->GetPosition();
			// プレイヤーとこのFarmTileとの距離の二乗を計算
			const D3DXVECTOR3 d = tilePosition - playerPosition;
			float distanceSq = D3DXVec3LengthSq(&d);

			// これまでの最小距離の二乗よりも短い場合は、このFarmTileを記録
			if (distanceSq < nearestDistanceSq)
			{
				nearestDistanceSq = distanceSq;
				nearestFarmTile = tile;
			}
		}
		return nearestFarmTile;
	}
	else
	{
		return nullptr;
	}
}

void FarmField::LoadFarmTileData(std::vector<FarmTileData> farmTileData)
{
	if (m_FarmTiles.size() <= 0) return;
	for (int i = 0; i < m_FarmTiles.size(); i++)
	{
		FarmTileState farmTileState = (FarmTileState)farmTileData[i].tileStage;
		CropState cropState = (CropState)farmTileData[i].cropStage;
		
		m_FarmTiles[i]->LoadData(farmTileState, cropState, farmTileData[i].cropKey, farmTileData[i].growthMinute);
	}
}
