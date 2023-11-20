#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "test.h"
#include "result.h"
#include "gameover.h"
#include "input.h"

#include "camera.h"
#include "meshfield.h"
#include "polygon2D.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "explosion.h"
#include "cylinder.h"
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
#include "countdown.h"
#include "gamelogo.h"
#include "treasureBox.h"
#include "collider.h"
#include "testObj.h"


Player* player;

void Test::Load()
{
	Bullet::Load();
	Enemy::Load();
	Earth::Load();
	Gauge::Load();
	Tree::Load();
	TreasureBox::Load();
	TreeBillboard::Load();
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
	Load();

	AddGameObject<Camera>(CAMERA_LAYER);//登録するListの種類を変える
	AddGameObject<Sky>(OBJECT_3D_LAYER);
	MeshField* meshField = AddGameObject<MeshField>(OBJECT_3D_LAYER);


	AddGameObject<Cylinder>(OBJECT_3D_LAYER)->SetGameObject(D3DXVECTOR3(6.0f, 0.0f, 6.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));


	player = AddGameObject<Player>(OBJECT_3D_LAYER);
	m_SphereCollider = player->AddComponent<SphereCollider>();
	m_SphereCollider->m_testObj->SetParent(player);
	TestObj* test = (TestObj*)m_SphereCollider->m_testObj;
	test->m_pMatrix = MatrixConvert(player->m_Model->GetBone()["mixamorig:LeftHand"].WorldMatrix);

	player->SetPosition(D3DXVECTOR3(-1.0f, 0.0f, -4.0f));

	AddGameObject<Enemy>(OBJECT_3D_LAYER)->SetGameObject(D3DXVECTOR3(-5.0f, 0.0f, 15.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));

	//SetEnemy();
	//SetTree();



	PlayerGauge* playerGauge = AddGameObject<PlayerGauge>(OBJECT_2D_LAYER);
	playerGauge->SetGameObject(D3DXVECTOR3(80.0f, SCREEN_HEIGHT - 80.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(300.0f, 50.0f, 0.0f));
	playerGauge->SetPlayerParent(player);
	AddGameObject<TreasureBox>(OBJECT_3D_LAYER)->SetGameObject(D3DXVECTOR3(0.0, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));

	srand(0);

	for (int i = 0; i < 20; i++)
	{
		TreeBillboard* treeBillboard = AddGameObject<TreeBillboard>(OBJECT_3D_LAYER);

		D3DXVECTOR3 pos;
		pos.x = (float)rand() / RAND_MAX * 100.0f - 50.0f;
		pos.z = (float)rand() / RAND_MAX * 100.0f - 50.0f;
		pos.y = meshField->GetHeight(pos);

		treeBillboard->SetPosition(pos);
	}


	//AddGameObject<CountDown>(OBJECT_2D_LAYER);
	AddGameObject<Polygon2D>(OBJECT_2D_LAYER);
	AddGameObject<GameLogo>(OBJECT_2D_LAYER);

	m_Fade = AddGameObject<Fade>(OBJECT_2D_LAYER);
	////BGM再生
	//Audio* bgm;
	//bgm = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	//bgm->Load("asset\\audio\\戦い153_long_BPM165.wav");
	//bgm->Play(true);
}

void Test::Uninit()
{
	Scene::Uninit();

	Bullet::Unload();
	Enemy::Unload();
	Earth::Unload();
	Gauge::Unload();
	Tree::Unload();
	TreasureBox::Unload();

	TreeBillboard::Unload();
}

void Test::Update()
{
	Scene::Update();

	if (Input::GetKeyPress(VK_F2))
	{
		m_Fade->SetIsFadeOut();

	}
	if (m_Fade->GetFadeOutFinish())
	{
		Manager::SetScene<Result>();//エンターキーを押したらゲームシーンに移行	
	}

	TestObj* test = (TestObj*)m_SphereCollider->m_testObj;
	test->m_pMatrix = MatrixConvert(player->m_Model->GetBone()["mixamorig:LeftHand"].WorldMatrix);
}

//時間ないから直
//期限過ぎたらCSVファイルから読み込んでvectorのlist使えるようにしたい

//void Test::SetEnemy()
//{
//	
//	AddGameObject<Enemy>(1)->SetGameObject(D3DXVECTOR3(0.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
//	AddGameObject<Enemy>(1)->SetGameObject(D3DXVECTOR3(10.0f, 0.0f, 35.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
//
//	AddGameObject<Enemy>(1)->SetGameObject(D3DXVECTOR3(5.0f, 0.0f, -25.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
//	AddGameObject<Enemy>(1)->SetGameObject(D3DXVECTOR3(0.0f, 0.0f, -70.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
//	AddGameObject<Enemy>(1)->SetGameObject(D3DXVECTOR3(-10.0f, 0.0f, -55.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
//
//
//
//}
//
//void Test::SetTree()
//{
//	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(13.0f, 0.0f, 11.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
//	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(10.0f, 0.0f, 22.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
//	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(20.0f, 0.0f, 35.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
//	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(5.0f, 0.0f, 41.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
//	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(17.0f, 0.0f, -8.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
//	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(1.0f, 0.0f, -35.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
//	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(11.0f, 0.0f, -37.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
//	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(20.0f, 0.0f, -11.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
//	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(8.0f, 0.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
//	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(-13.0f, 0.0f, -11.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
//	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(-10.0f, 0.0f, -22.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
//	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(-20.0f, 0.0f, -35.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
//	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(-5.0f, 0.0f, -41.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
//	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(-17.0f, 0.0f, 8.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
//	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(-1.0f, 0.0f, 35.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
//	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(-11.0f, 0.0f, 37.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
//	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(-20.0f, 0.0f, 11.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
//	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(-8.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
//
//}
//
//void Test::SetWall()
//{
//	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(20.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
//	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(20.0f, 0.0f, 6.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
//	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(20.0f, 0.0f, 12.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
//	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(20.0f, 0.0f, 18.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
//	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(20.0f, 0.0f, 24.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
//	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(20.0f, 0.0f, -6.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
//	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(20.0f, 0.0f, -12.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
//	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(20.0f, 0.0f, -18.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
//	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(20.0f, 0.0f, -24.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
//	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(20.0f, 0.0f, -30.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
//
//	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(-20.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
//	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(-20.0f, 0.0f, 6.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
//	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(-20.0f, 0.0f, 12.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
//	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(-20.0f, 0.0f, 18.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
//	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(-20.0f, 0.0f, 24.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
//	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(-20.0f, 0.0f, -6.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
//	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(-20.0f, 0.0f, -12.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
//	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(-20.0f, 0.0f, -18.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
//	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(-20.0f, 0.0f, -24.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
//	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(-20.0f, 0.0f, -30.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
//}




