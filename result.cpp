#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "resultplayer.h"
#include "result.h"
#include "input.h"
#include "resultcamera.h"
#include "title.h"
#include "resultscreen.h"
#include "fade.h"
#include "audio.h"
#include "resultsky.h"
#include "titleenter.h"
#include "tree.h"
#include "treasureBox.h"
void Result::Init()
{
	TreasureBox::Load();
	AddGameObject<ResultCamera>(0);
	AddGameObject<ResultSky>(1);
	AddGameObject<Field>(1);
	ResultPlayer* player = AddGameObject<ResultPlayer>(1);
	player->SetPosition(D3DXVECTOR3(1.0f, 0.0f, 0.0f));

	AddGameObject<ResultScreen>(2);
	AddGameObject<TitleEnter>(2);
	m_Fade = AddGameObject<Fade>(2);

	//BGM再生
	Audio* bgm;
	bgm = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	bgm->Load("asset\\audio\\クリア349_BPM70.wav");
	bgm->Play(true);
}

void Result::Uninit()
{
	TreasureBox::Unload();
	Scene::Uninit();
}

void Result::Update()
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
