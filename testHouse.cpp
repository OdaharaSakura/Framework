#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "loading.h"
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
#include "boxObject.h"
#include "sphereObject.h"
#include "inventory.h"
#include "iequipment.h"
#include "animationModelContainer.h"
#include "textureContainer.h"
#include "modelContainer.h"
#include "itemDataContainer.h"
#include "saveDataManager.h"

void TestHouse::Load()
{
	ItemDataContainer::Load();
	TextureContainer::Load(SCENE_GAME);
	ModelContainer::Load(SCENE_GAME);
	AnimationModelContainer::Load(SCENE_GAME);
}
void TestHouse::Unload()
{
	TextureContainer::Unload(SCENE_GAME);
	ModelContainer::Unload(SCENE_GAME);
	AnimationModelContainer::Unload(SCENE_GAME);
}


void TestHouse::Init()
{	
	Load();

	//インターフェース
	AddGameObject<IEquipment>(LAYER_OBJECT_NOTDRAW);
	AddGameObject<Inventory>(LAYER_OBJECT_NOTDRAW);

	AddGameObject<Camera>(LAYER_CAMERA);//登録するListの種類を変える
	AddGameObject<Sky>(LAYER_OBJECT_3D);

	MeshField* meshField = AddGameObject<MeshField>(LAYER_OBJECT_3D);

	Room* room = AddGameObject<Room>(LAYER_OBJECT_3D);
	room->SetPositionY(-0.1f);

	m_Player = AddGameObject<Player>(LAYER_OBJECT_3D);
	Bed* bed = AddGameObject<Bed>(LAYER_OBJECT_3D);

	BoxObject* boxCollider1 = AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
	boxCollider1->SetPosition(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
	boxCollider1->SetScale(D3DXVECTOR3(1.0f, 0.0f, 20.0f));

	BoxObject* boxCollider2 = AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
	boxCollider2->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 0.0f));
	boxCollider2->SetScale(D3DXVECTOR3(1.0f, 0.0f, 20.0f));

	BoxObject* boxCollider3 = AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
	boxCollider3->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 5.0f));
	boxCollider3->SetScale(D3DXVECTOR3(20.0f, 0.0f, 1.0f));


	BoxObject* boxCollider4 = AddGameObject<BoxObject>(LAYER_BOXCOLLIDER);
	boxCollider4->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -5.0f));
	boxCollider4->SetScale(D3DXVECTOR3(20.0f, 0.0f, 1.0f));

	m_Sphere = AddGameObject<SphereObject>(LAYER_SPHERECOLLIDER);
	boxCollider4->SetPosition(D3DXVECTOR3(-4.0f, 0.0f, 10.0f));
	boxCollider4->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));

	PlayerGauge* playerGauge = AddGameObject<PlayerGauge>(LAYER_OBJECT_2D);
	playerGauge->SetGameObject(D3DXVECTOR3(80.0f, SCREEN_HEIGHT - 80.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(300.0f, 50.0f, 0.0f));
	playerGauge->SetPlayerParent(m_Player);
	AddGameObject<Time>(LAYER_OBJECT_2D);

	m_Fade = AddGameObject<Fade>(LAYER_OBJECT_2D);

	if (Manager::GetIsLoad())
	{
		SaveDataManager::Load(m_FarmField, m_Inventory, m_Equipment, m_Player, m_Time);
		Manager::SetIsLoad(false);
	}
}

void TestHouse::Uninit()
{
	Scene::Uninit();

	Unload();
}

void TestHouse::Update()
{
	Scene::Update();

	m_Player = GetGameObject<Player>();
	m_Sphere = GetGameObject<SphereObject>();
	D3DXVECTOR3 position = m_Sphere->GetPosition();
	D3DXVECTOR3 scalexz = m_Sphere->GetScale();

	D3DXVECTOR3 direction = m_Player->GetPosition() - position;
	direction.y = 0.0f;
	float length = D3DXVec3Length(&direction);
	scalexz.y = 0.0f;
	float lengthxz = D3DXVec3Length(&scalexz);
	if ((length * length) <= lengthxz)
	{
		if (Input::GetKeyPress('L'))
		{
			m_Fade->SetIsFadeOut();
		}
	}


	if (m_Fade->GetFadeOutFinish())
	{
		Manager::SetScene<Loading>();//エンターキーを押したらゲームシーンに移行	
	}
}


