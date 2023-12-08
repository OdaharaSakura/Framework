#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "resultcamera.h"
#include "resultplayer.h"
#include "resultsky.h"
#include "titlelogo.h"
#include "titlebg.h"
#include "titleenter.h"
#include "titleselect.h"
#include "titlecursor.h"
#include "loading.h"

#include "audio.h"


void Title::Init()
{
	ResultCamera* camera = AddGameObject<ResultCamera>(0);
	camera->Setoffset(D3DXVECTOR3(2.0f, 1.0f, 0.0f));
	AddGameObject<ResultSky>(1);
	ResultPlayer* player = AddGameObject<ResultPlayer>(1);
	player->SetPosition(D3DXVECTOR3(1.0f, 0.0f, 0.0f));
	//AddGameObject<TitleBG>(2);
	AddGameObject<TitleLogo>(2);
	
	m_TitleSelect = AddGameObject<TitleSelect>(2);
	m_TitleSelect->SetAlpha(0.0f);
	m_TitleCursor = AddGameObject<TitleCursor>(2);
	m_TitleCursor->SetAlpha(0.0f);
	m_TitleEnter = AddGameObject<TitleEnter>(2);



	////BGMçƒê∂
	//Audio* bgm;
	//bgm = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	//bgm->Load("asset\\audio\\035_long_BPM60.wav");
	//bgm->Play(true);

	//m_ShotSE1 = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	//m_ShotSE1->Load("asset\\audio\\VSQSE_0665_heavy_metal_hit_03.wav");
}
void Title::Uninit()
{
	Scene::Uninit();
}

void Title::Update()
{
	Scene::Update();

	//if (m_TitleEnter->GetIsPressEnter() && m_Phase == 0)
	//{
	//	m_Phase++;
	//	m_ShotSE1->Play(false);
	//	m_TitleEnter->SetAlpha(0.0f);
	//	m_TitleSelect->SetAlpha(1.0f);
	//}



	if (Input::GetKeyTrigger(VK_RETURN))
	{
		Manager::SetScene<Loading>();
	}


}
