#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "result.h"
#include "gameover.h"
#include "input.h"
#include "collision.h"
#include "camera.h"
#include "meshfield.h"
#include "polygon2D.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "explosion.h"
#include "box.h"
#include "score.h"
#include "audio.h"
#include "sky.h"
#include "fade.h"
#include "gauge.h"
#include "polygon2D.h"
#include "playerGauge.h"
#include "earth.h"
#include "child.h"
#include "tree.h"
#include "tree_billboard.h"
#include "testHouse.h"
#include "gamelogo.h"
#include "collider.h"
#include "equipmentObj.h"
#include "time.h"
#include "npc.h"
#include "modelTest.h"
#include "farmField.h"
#include "farmTile.h"
#include "iEquipment.h"
#include "inventory.h"
#include "equipmentView.h"	
#include "textureContainer.h"
#include "modelContainer.h"
#include "animationModelContainer.h"
#include "staticObject.h"
#include "road.h"
#include "townFactory.h"
#include "itemDataContainer.h"
#include "player.h"
#include "bloomPolygon.h"
#include "luminance.h"
#include "post.h"
#include "savedataManager.h"
#include "sphereObject.h"
#include "enemyObserver.h"
#include "uiObserver.h"
#include "gaugeFrame.h"
#include "sceneDescription.h"
#include "conversation.h"

bool Game::m_LoadFinish = false;

void Game::Load()
{
	ItemDataContainer::Load();
	TextureContainer::Load(SCENE_GAME);
	ModelContainer::Load(SCENE_GAME);
	AnimationModelContainer::Load(SCENE_GAME);
	Gauge::Load();
	TreeBillboard::Load();
	m_LoadFinish = true;
}
void Game::Unload()
{
	m_LoadFinish = false;
	TextureContainer::Unload(SCENE_GAME);
	ModelContainer::Unload(SCENE_GAME);
	AnimationModelContainer::Unload(SCENE_GAME);
	Gauge::Unload();
	TreeBillboard::Unload();
}
D3DXMATRIX MatrixConvert(aiMatrix4x4 aiMatrix);
static D3DXMATRIX MatrixConvert(aiMatrix4x4 aiMatrix)
{
	D3DXMATRIX fuse;

	fuse._11 = aiMatrix.a1;
	fuse._12 = aiMatrix.b1;
	fuse._13 = aiMatrix.c1;
	fuse._14 = aiMatrix.d1;

	fuse._21 = aiMatrix.a2;
	fuse._22 = aiMatrix.b2;
	fuse._23 = aiMatrix.c2;
	fuse._24 = aiMatrix.d2;

	fuse._31 = aiMatrix.a3;
	fuse._32 = aiMatrix.b3;
	fuse._33 = aiMatrix.c3;
	fuse._34 = aiMatrix.d3;

	fuse._41 = aiMatrix.a4;
	fuse._42 = aiMatrix.b4;
	fuse._43 = aiMatrix.c4;
	fuse._44 = aiMatrix.d4;


	return fuse;
}


void Game::Init()
{
	//インターフェース
	m_Equipment = AddGameObject<IEquipment>(LAYER_OBJECT_NOTDRAW);
	m_Inventory = AddGameObject<Inventory>(LAYER_OBJECT_NOTDRAW);


	AddGameObject<Camera>(LAYER_CAMERA);
	AddGameObject<Sky>(LAYER_OBJECT_3D);
	MeshField* meshField = AddGameObject<MeshField>(LAYER_OBJECT_3D);
	meshField->SetPosition(D3DXVECTOR3(0.0f, 0.0f , 0.0f));
	MeshField* meshField2 = AddGameObject<MeshField>(LAYER_OBJECT_3D);
	meshField2->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 200.0f));
	m_FarmField =  AddGameObject<FarmField>(LAYER_OBJECT_3D);

	TownFactory* townFactory = new TownFactory();
	townFactory->CreateTown();


	m_Player = AddGameObject<Player>(LAYER_OBJECT_3D);

	m_EquipmentObj = AddGameObject<EquipmentObj>(LAYER_OBJECT_3D);
	m_EquipmentObj->SetParent(m_Player);
	m_EquipmentObj->m_pMatrix = MatrixConvert(m_Player->m_Model->GetBone()["mixamorig:LeftHand"].WorldMatrix);

	m_Player->SetPosition(D3DXVECTOR3(-1.0f, 0.0f, -4.0f));

	NPC* npc1 = AddGameObject<NPC>(LAYER_OBJECT_3D);
	npc1->SetGameObject(D3DXVECTOR3(-5.0f, 0.0f, 15.0f), D3DXVECTOR3(0.0f, 3.14f/2, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	SphereObject* sphereroad = AddGameObject<SphereObject>(LAYER_SPHERECOLLIDER);
	sphereroad->SetPosition(npc1->GetPosition());
	sphereroad->SetScale(npc1->GetScale());

	AddGameObject<Enemy>(LAYER_OBJECT_3D)->SetGameObject(D3DXVECTOR3(0.0f, 1.0f, -40.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));


	

	srand(0);

	for (int i = 0; i < 20; i++)
	{
		TreeBillboard* treeBillboard = AddGameObject<TreeBillboard>(LAYER_OBJECT_3D);

		D3DXVECTOR3 pos;
		pos.x = (float)rand() / RAND_MAX * 100.0f - 50.0f;
		pos.z = (float)rand() / RAND_MAX * 100.0f - 50.0f;
		pos.y = meshField->GetHeight(pos);

		treeBillboard->SetPosition(pos);
	}

	//bloom
	SetIsBloom();
	AddGameObject<BloomPolygon>(LAYER_POSTEFFECT);
	AddGameObject<Luminance>(LAYER_POSTEFFECT);
	AddGameObject<Post>(LAYER_POSTEFFECT);


	
	PlayerGauge* playerGauge = AddGameObject<PlayerGauge>(LAYER_OBJECT_2D);
	playerGauge->SetGameObject(D3DXVECTOR3(80.0f, SCREEN_HEIGHT - 80.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(300.0f, 50.0f, 0.0f));
	playerGauge->SetPlayerParent(m_Player);

	AddGameObject<Polygon2D>(LAYER_OBJECT_2D);
	AddGameObject<GaugeFrame>(LAYER_OBJECT_2D);
	m_Time = AddGameObject<Time>(LAYER_OBJECT_2D);
	m_SceneDescription = AddGameObject<SceneDescription>(LAYER_OBJECT_2D);
	AddGameObject<Conversation>(LAYER_OBJECT_2D);

	m_EnemyObserver = new EnemyObserver();
	m_UIObserver = new UIObserver();

	m_Fade = AddGameObject<Fade>(LAYER_OBJECT_2D);

	//BGM再生
	Audio* bgm;
	bgm = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	bgm->Load("asset\\audio\\GameBGM.wav");
	bgm->Play(true);

	if (Manager::GetIsLoad())
	{
		SaveDataManager::Load(m_FarmField, m_Inventory, m_Equipment, m_Player, m_Time);
		m_Time->NotifyAllTimeObservers();
		Manager::SetIsLoad(false);
	}
}

void Game::Uninit()
{
	SaveDataManager::Save(SCENE_GAME);
	Scene::Uninit();
	Unload();
}

void Game::Update()
{
	Scene::Update();

	m_EquipmentObj->m_pMatrix = MatrixConvert(m_Player->m_Model->GetBone()["mixamorig:LeftHand"].WorldMatrix);
}




