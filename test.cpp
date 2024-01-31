#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "test.h"
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
#include "house.h"
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
#include "treasureBox.h"
#include "collider.h"
#include "testObj.h"
#include "time.h"
#include "npc.h"
#include "modelTest.h"
#include "farmField.h"
#include "farmTile.h"
#include "iEquipment.h"
#include "equipmentView.h"	
#include "textureContainer.h"
#include "modelContainer.h"
#include "staticObject.h"
#include "road.h"

#include "bloomPolygon.h"
#include "luminance.h"
#include "post.h"

Player* player;
bool Test::m_LoadFinish = false;

void Test::Load()
{
	TextureContainer::Load(SCENE_GAME);
	ModelContainer::Load(SCENE_GAME);
	Gauge::Load();
	TreasureBox::Load();
	TreeBillboard::Load();
	m_LoadFinish = true;
}
void Test::Unload()
{
	m_LoadFinish = false;
	TextureContainer::Unload(SCENE_GAME);
	ModelContainer::Unload(SCENE_GAME);
	Gauge::Unload();
	TreasureBox::Unload();
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


void Test::Init()
{
	AddGameObject<IEquipment>(LAYER_OBJECT_NOTDRAW);
	AddGameObject<Camera>(LAYER_CAMERA);//登録するListの種類を変える
	AddGameObject<Sky>(LAYER_OBJECT_3D);
	MeshField* meshField = AddGameObject<MeshField>(LAYER_OBJECT_3D);
	MeshField* meshField2 = AddGameObject<MeshField>(LAYER_OBJECT_3D);
	meshField2->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 150.0f));
	AddGameObject<FarmField>(LAYER_OBJECT_3D);



	AddGameObject<House>(LAYER_OBJECT_3D)->SetPosition(D3DXVECTOR3(6.0f, 3.0f, 6.0f));
	AddGameObject<ModelTest>(LAYER_OBJECT_3D)->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	player = AddGameObject<Player>(LAYER_OBJECT_3D);
	m_SphereCollider = player->AddComponent<SphereCollider>();
	m_SphereCollider->m_testObj->SetParent(player);
	TestObj* test = (TestObj*)m_SphereCollider->m_testObj;
	test->m_pMatrix = MatrixConvert(player->m_Model->GetBone()["mixamorig:LeftHand"].WorldMatrix);

	player->SetPosition(D3DXVECTOR3(-1.0f, 0.0f, -4.0f));

	AddGameObject<NPC>(LAYER_OBJECT_3D)->SetGameObject(D3DXVECTOR3(-5.0f, 0.0f, 15.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	//AddGameObject<Enemy>(LAYER_OBJECT_3D)->SetGameObject(D3DXVECTOR3(-30.0f, 0.0f, 30.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));


	//AddGameObject<TreasureBox>(LAYER_OBJECT_3D)->SetGameObject(D3DXVECTOR3(0.0, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));

	SetStaticObject();
	

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
	playerGauge->SetPlayerParent(player);

	//AddGameObject<CountDown>(OBJECT_2D_LAYER);
	AddGameObject<Polygon2D>(LAYER_OBJECT_2D);
	AddGameObject<Time>(LAYER_OBJECT_2D);

	m_Fade = AddGameObject<Fade>(LAYER_OBJECT_2D);
	////BGM再生
	//Audio* bgm;
	//bgm = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	//bgm->Load("asset\\audio\\戦い153_long_BPM165.wav");
	//bgm->Play(true);
}

void Test::Uninit()
{
	Scene::Uninit();

	Unload();
}

void Test::Update()
{
	Scene::Update();

	//Collision::CheckSphereCollider();

	if (Input::GetKeyPress(VK_F2))
	{
		m_Fade->SetIsFadeOut();

	}
	if (m_Fade->GetFadeOutFinish())
	{
		Manager::SetScene<TestHouse>();//エンターキーを押したらゲームシーンに移行	
	}

	//TestObj* test = (TestObj*)m_SphereCollider->m_testObj;
	//test->m_pMatrix = MatrixConvert(player->m_Model->GetBone()["mixamorig:LeftHand"].WorldMatrix);
}

void Test::SetStaticObject()
{
	StaticObject*  desk = AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	desk->SetModel_Key("Desk");
	desk->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 10.0f));
	desk->SetScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
	desk->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* house1 = AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	house1->SetModel_Key("House1");
	house1->SetPosition(D3DXVECTOR3(40.0f, 0.0f, 80.0f));
	house1->SetScale(D3DXVECTOR3(4.0f, 4.0f, 4.0f));
	house1->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* house2 = AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	house2->SetModel_Key("House2");
	house2->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 80.0f));
	house2->SetScale(D3DXVECTOR3(4.0f, 4.0f, 4.0f));
	house2->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* shop1 = AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	shop1->SetModel_Key("Shop1");
	shop1->SetPosition(D3DXVECTOR3(10.0f, 0.0f, 150.0f));
	shop1->SetScale(D3DXVECTOR3(4.0f, 4.0f, 4.0f));
	shop1->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	/*StaticObject* shop2 = AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	shop2->SetModel_Key("Shop2");
	shop2->SetPosition(D3DXVECTOR3(80.0f, 0.0f, 40.0f));
	shop2->SetScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
	shop2->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* shop3 = AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	shop3->SetModel_Key("Shop3");
	shop3->SetPosition(D3DXVECTOR3(70.0f, 0.0f, 100.0f));
	shop3->SetScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
	shop3->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* fence = AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	fence->SetModel_Key("Fence");
	fence->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 20.0f));
	fence->SetScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
	fence->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* fencewood = AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	fencewood->SetModel_Key("FenceWood");
	fencewood->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 30.0f));
	fencewood->SetScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
	fencewood->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* treemiddle = AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	treemiddle->SetModel_Key("MiddleTree");
	treemiddle->SetPosition(D3DXVECTOR3(20.0f, 0.0f, 170.0f));
	treemiddle->SetScale(D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	treemiddle->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* symboltree = AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	symboltree->SetModel_Key("SymbolTree");
	symboltree->SetPosition(D3DXVECTOR3(20.0f, 0.0f, 170.0f));
	symboltree->SetScale(D3DXVECTOR3(0.1f, 0.1f, 0.1f));
	symboltree->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	/*StaticObject* windmill = AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	windmill->SetModel_Key("WindMill");
	windmill->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 30.0f));
	windmill->SetScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
	windmill->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* gate1 = AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	gate1->SetModel_Key("Gate");
	gate1->SetPosition(D3DXVECTOR3(150.0f, 0.0f, 150.0f));
	gate1->SetScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
	gate1->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* gate2 = AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	gate2->SetModel_Key("Gate2");
	gate2->SetPosition(D3DXVECTOR3(120.0f, 0.0f, 120.0f));
	gate2->SetScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
	gate2->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* bridge = AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	bridge->SetModel_Key("Bridge");
	bridge->SetPosition(D3DXVECTOR3(110.0f, 0.0f, 70.0f));
	bridge->SetScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
	bridge->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* pool = AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	pool->SetModel_Key("Pool");
	pool->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -10.0f));
	pool->SetScale(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	pool->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	/*StaticObject* wateringcan = AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	wateringcan->SetModel_Key("WateringCan");
	wateringcan->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	wateringcan->SetScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
	wateringcan->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* wateringcan2 = AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	wateringcan2->SetModel_Key("WateringCan2");
	wateringcan2->SetPosition(D3DXVECTOR3(10.0f, 0.0f, 10.0f));
	wateringcan2->SetScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
	wateringcan2->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* carriage = AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	carriage->SetModel_Key("Carriage");
	carriage->SetPosition(D3DXVECTOR3(70.0f, 0.0f, 80.0f));
	carriage->SetScale(D3DXVECTOR3(0.01f, 0.01f, 0.01f));
	carriage->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	StaticObject* carriage = AddGameObject<StaticObject>(LAYER_OBJECT_3D);
	carriage->SetModel_Key("Barrel");
	carriage->SetPosition(D3DXVECTOR3(45.0f, 0.0f, 80.0f));
	carriage->SetScale(D3DXVECTOR3(0.5f, 0.5f, 0.5f));
	carriage->SetRotation(D3DXVECTOR3(0.0f, 0.0f, 0.0f));*/
}




