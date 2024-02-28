#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "gameover.h"
#include "title.h"
#include "gameoverlogo.h"
#include "titleenter.h"
#include "fade.h"
#include "audio.h"


void GameOver::Init()
{

	AddGameObject<GameOverLogo>(2);
	AddGameObject<TitleEnter>(2);
	m_Fade = AddGameObject<Fade>(2);

	////BGM再生
	//Audio* bgm;
	//bgm = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	//bgm->Load("asset\\audio\\VSQ_MUSIC_0052_chill.wav");
	//bgm->Play(true);
}

void GameOver::Uninit()
{
	Scene::Uninit();
}

void GameOver::Update()
{
	Scene::Update();

	if (Input::GetKeyPress(VK_SPACE))
	{
		m_Fade->SetIsFadeOut();

	}
	if (m_Fade->GetFadeOutFinish())
	{
		Manager::SetScene<Title>();//エンターキーを押したらゲームシーンに移行	
	}

}
