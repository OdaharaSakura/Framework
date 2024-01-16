#include "main.h"
#include "farmTile.h"
#include "renderer.h"
#include "model.h"
#include "shader.h"
#include "crop.h"

void FarmTile::Load()
{
	m_Model[FarmTileModelState::FARMTILE_MODEL_PLOWED] = new Model();
	m_Model[FarmTileModelState::FARMTILE_MODEL_PLOWED]->Load("asset\\model\\obj\\calot.obj");

	m_Model[FarmTileModelState::FARMTILE_MODEL_PLOWEDWATERED] = new Model();
	m_Model[FarmTileModelState::FARMTILE_MODEL_PLOWEDWATERED]->Load("asset\\model\\obj\\carrot_1.obj");
}

void FarmTile::Unload()
{
}

void FarmTile::Init()
{
	Load();

	m_WorldPosition = D3DXVECTOR3(-15.0f, 0.0f, 0.0f);

	AddComponent<VertexLighting>();

	m_FarmTileState == FarmTileState::EMPTY;
}

void FarmTile::Uninit()
{
	for (int i = 0; i < MAX_FARMTILE_MODEL_STAGE; i++)
	{
		if (m_Model[i] == nullptr) continue;

		m_Model[i]->Unload();
		delete m_Model[i];
	}
}

void FarmTile::Update()
{
	num++;

	if (num >= 200)
	{
		m_FarmTileState = FarmTileState::PLOWED;
	}
	if (num >= 500)
	{
		m_FarmTileState = FarmTileState::PLOWEDWATERED;
	}
}

void FarmTile::Draw()
{
	if (m_FarmTileState == EMPTY) return;
	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_WorldPosition.x, m_WorldPosition.y, m_WorldPosition.z);
	world = scale * rot * trans;

	Renderer::SetWorldMatrix(&world);

	switch (m_FarmTileState)
	{
	case FarmTileState::PLOWED:
		m_Model[FarmTileModelState::FARMTILE_MODEL_PLOWED]->Draw();
		break;
	case FarmTileState::PLOWEDWATERED:
		m_Model[FarmTileModelState::FARMTILE_MODEL_PLOWEDWATERED]->Draw();
		break;
	default:
		break;
	}
	
}


