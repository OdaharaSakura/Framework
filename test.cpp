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

Player* player;
bool Test::m_LoadFinish = false;

void Test::Load()
{

	Gauge::Load();
	TreasureBox::Load();
	TreeBillboard::Load();
	m_LoadFinish = true;
}
void Test::Unload()
{
	m_LoadFinish = false;

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
	AddGameObject<Camera>(LAYER_CAMERA);//�o�^����List�̎�ނ�ς���
	AddGameObject<Sky>(LAYER_OBJECT_3D);
	MeshField* meshField = AddGameObject<MeshField>(LAYER_OBJECT_3D);
	AddGameObject<FarmField>(LAYER_OBJECT_3D);
	AddGameObject<FarmTile>(LAYER_OBJECT_3D);


	AddGameObject<House>(LAYER_OBJECT_3D)->SetPosition(D3DXVECTOR3(6.0f, 3.0f, 6.0f));
	AddGameObject<ModelTest>(LAYER_OBJECT_3D)->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	player = AddGameObject<Player>(LAYER_OBJECT_3D);
	//m_SphereCollider = player->AddComponent<SphereCollider>();
	//m_SphereCollider->m_testObj->SetParent(player);
	//TestObj* test = (TestObj*)m_SphereCollider->m_testObj;
	//test->m_pMatrix = MatrixConvert(player->m_Model->GetBone()["mixamorig:LeftHand"].WorldMatrix);

	player->SetPosition(D3DXVECTOR3(-1.0f, 0.0f, -4.0f));

	AddGameObject<NPC>(LAYER_OBJECT_3D)->SetGameObject(D3DXVECTOR3(-5.0f, 0.0f, 15.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	AddGameObject<Enemy>(LAYER_OBJECT_3D)->SetGameObject(D3DXVECTOR3(-30.0f, 0.0f, 30.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));

	//SetEnemy();
	//SetTree();

	//AddGameObject<TreasureBox>(LAYER_OBJECT_3D)->SetGameObject(D3DXVECTOR3(0.0, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));


	

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

	
	PlayerGauge* playerGauge = AddGameObject<PlayerGauge>(LAYER_OBJECT_2D);
	playerGauge->SetGameObject(D3DXVECTOR3(80.0f, SCREEN_HEIGHT - 80.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(300.0f, 50.0f, 0.0f));
	playerGauge->SetPlayerParent(player);

	//AddGameObject<CountDown>(OBJECT_2D_LAYER);
	AddGameObject<Polygon2D>(LAYER_OBJECT_2D);
	AddGameObject<Time>(LAYER_OBJECT_2D);
	//AddGameObject<GameLogo>(OBJECT_2D_LAYER);

	m_Fade = AddGameObject<Fade>(LAYER_OBJECT_2D);
	////BGM�Đ�
	//Audio* bgm;
	//bgm = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	//bgm->Load("asset\\audio\\�킢153_long_BPM165.wav");
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
		Manager::SetScene<TestHouse>();//�G���^�[�L�[����������Q�[���V�[���Ɉڍs	
	}

	//TestObj* test = (TestObj*)m_SphereCollider->m_testObj;
	//test->m_pMatrix = MatrixConvert(player->m_Model->GetBone()["mixamorig:LeftHand"].WorldMatrix);
}


