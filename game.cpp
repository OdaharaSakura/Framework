#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "result.h"
#include "gameover.h"
#include "input.h"
#include "camera.h"
#include "field.h"
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
#include "gamelogo.h"
#include "treasureBox.h"



void Game::Load()
{
	Bullet::Load();
	//Enemy::Load();
	Earth::Load();
	Gauge::Load();
	Tree::Load();
	TreasureBox::Load();
}

void Game::Init()
{
	Load();

	AddGameObject<Camera>(0);//登録するListの種類を変える
	AddGameObject<Sky>(1);
	AddGameObject<Field>(1);

	AddGameObject<Cylinder>(1)->SetGameObject(D3DXVECTOR3(6.0f, 0.0f, 6.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	

	Player* player = AddGameObject<Player>(1);
	player->SetPosition(D3DXVECTOR3(-1.0f, 0.0f, -4.0f));


	SetEnemy();
	SetTree();



	PlayerGauge* playerGauge = AddGameObject<PlayerGauge>(2);
	playerGauge->SetGameObject(D3DXVECTOR3(80.0f, SCREEN_HEIGHT- 80.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(300.0f, 50.0f, 0.0f));
	playerGauge->SetPlayerParent(player);
	AddGameObject<TreasureBox>(1)->SetGameObject(D3DXVECTOR3(0.0, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));

	AddGameObject<Polygon2D>(2);
	AddGameObject<GameLogo>(2);

	m_Fade = AddGameObject<Fade>(2);
	////BGM再生
	//Audio* bgm;
	//bgm = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	//bgm->Load("asset\\audio\\戦い153_long_BPM165.wav");
	//bgm->Play(true);
}

void Game::Uninit()
{
	Scene::Uninit();

	Bullet::Unload();
	//Enemy::Unload();
	Earth::Unload();
	Gauge::Unload();
	Tree::Unload();
	TreasureBox::Unload();
}

void Game::Update()
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
}

//時間ないから直
//期限過ぎたらCSVファイルから読み込んでvectorのlist使えるようにしたい

void Game::SetEnemy()
{
	AddGameObject<Enemy>(1)->SetGameObject(D3DXVECTOR3(-5.0f, 0.0f, 15.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	AddGameObject<Enemy>(1)->SetGameObject(D3DXVECTOR3(0.0f, 0.0f, 50.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	AddGameObject<Enemy>(1)->SetGameObject(D3DXVECTOR3(10.0f, 0.0f, 35.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));

	AddGameObject<Enemy>(1)->SetGameObject(D3DXVECTOR3(5.0f, 0.0f, -25.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	AddGameObject<Enemy>(1)->SetGameObject(D3DXVECTOR3(0.0f, 0.0f, -70.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	AddGameObject<Enemy>(1)->SetGameObject(D3DXVECTOR3(-10.0f, 0.0f, -55.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));



}

void Game::SetTree()
{
	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(13.0f, 0.0f, 11.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(10.0f, 0.0f, 22.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(20.0f, 0.0f, 35.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(5.0f, 0.0f, 41.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(17.0f, 0.0f, -8.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(1.0f, 0.0f, -35.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(11.0f, 0.0f, -37.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(20.0f, 0.0f, -11.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(8.0f, 0.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(-13.0f, 0.0f, -11.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(-10.0f, 0.0f, -22.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(-20.0f, 0.0f, -35.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(-5.0f, 0.0f, -41.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(-17.0f, 0.0f, 8.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(-1.0f, 0.0f, 35.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(-11.0f, 0.0f, 37.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(-20.0f, 0.0f, 11.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));
	AddGameObject<Tree>(1)->SetGameObject(D3DXVECTOR3(-8.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(2.0f, 2.0f, 2.0f));

}

void Game::SetWall()
{
	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(20.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(20.0f, 0.0f, 6.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(20.0f, 0.0f, 12.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(20.0f, 0.0f, 18.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(20.0f, 0.0f, 24.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(20.0f, 0.0f, -6.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(20.0f, 0.0f, -12.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(20.0f, 0.0f, -18.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(20.0f, 0.0f, -24.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(20.0f, 0.0f, -30.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));

	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(-20.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(-20.0f, 0.0f, 6.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(-20.0f, 0.0f, 12.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(-20.0f, 0.0f, 18.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(-20.0f, 0.0f, 24.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(-20.0f, 0.0f, -6.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(-20.0f, 0.0f, -12.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(-20.0f, 0.0f, -18.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(-20.0f, 0.0f, -24.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(-20.0f, 0.0f, -30.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
}




