#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "tutorial.h"
#include "game.h"
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
#include "fade.h"
#include "sky.h"
#include "audio.h"

void Tutorial::Init()
{
	AddGameObject<Camera>(0);//登録するListの種類を変える
	AddGameObject<Sky>(1);
	AddGameObject<Field>(1);
	AddGameObject<Player>(1)->SetPosition(D3DXVECTOR3(-10.0f, 1.0f, -4.0f));
	AddGameObject<Enemy>(1)->SetGameObject(D3DXVECTOR3(0.0f, 0.0f, 5.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3(-4.0f, 0.0f, 5.0f));
	AddGameObject<Enemy>(1)->SetPosition(D3DXVECTOR3(4.0f, 0.0f, 5.0f));
	AddGameObject<Cylinder>(1)->SetGameObject(D3DXVECTOR3(6.0f, 0.0f, 6.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Box>(1)->SetGameObject(D3DXVECTOR3(6.0f, 0.0f, 12.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));
	AddGameObject<Polygon2D>(2);
	m_Fade = AddGameObject<Fade>(2);

	//BGM再生
	Audio* bgm;
	bgm = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	bgm->Load("asset\\audio\\bgm.wav");
	bgm->Play(true);
}

void Tutorial::Update()
{
	Scene::Update();

	if (Input::GetKeyPress(VK_F1))
	{
		m_Fade->SetIsFadeOut();

	}
	if (m_Fade->GetFadeOutFinish())
	{
		Manager::SetScene<Game>();//エンターキーを押したらゲームシーンに移行	
	}

}
