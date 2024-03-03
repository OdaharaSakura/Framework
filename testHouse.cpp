#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "testHouse.h"
#include "input.h"
#include "camera.h"
#include "meshfield.h"
#include "sky.h"
#include "player.h"
#include "playerGauge.h"
#include "room.h"
#include "time.h"
#include "fade.h"
#include "bed.h"


void TestHouse::Load()
{

}
void TestHouse::Unload()
{

}


void TestHouse::Init()
{
	AddGameObject<Camera>(LAYER_CAMERA);//登録するListの種類を変える
	AddGameObject<Sky>(LAYER_OBJECT_3D);

	MeshField* meshField = AddGameObject<MeshField>(LAYER_OBJECT_3D);

	Room* room = AddGameObject<Room>(LAYER_OBJECT_3D);
	room->SetPositionY(-0.1f);

	Player* player = AddGameObject<Player>(LAYER_OBJECT_3D);
	Bed* bed = AddGameObject<Bed>(LAYER_OBJECT_3D);

	PlayerGauge* playerGauge = AddGameObject<PlayerGauge>(LAYER_OBJECT_2D);
	playerGauge->SetGameObject(D3DXVECTOR3(80.0f, SCREEN_HEIGHT - 80.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(300.0f, 50.0f, 0.0f));
	playerGauge->SetPlayerParent(player);
	AddGameObject<Time>(LAYER_OBJECT_2D);

	m_Fade = AddGameObject<Fade>(LAYER_OBJECT_2D);
}

void TestHouse::Uninit()
{
	Scene::Uninit();

	Unload();
}

void TestHouse::Update()
{
	Scene::Update();

	if (Input::GetKeyPress(VK_F2))
	{
		m_Fade->SetIsFadeOut();

	}
	if (m_Fade->GetFadeOutFinish())
	{
		Manager::SetScene<Game>();//エンターキーを押したらゲームシーンに移行	
	}
}


