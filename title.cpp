#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "title.h"
#include "meshField.h"
#include "game.h"
#include "resultcamera.h"
#include "resultplayer.h"
#include "audio.h"
#include "resultsky.h"
#include "titlelogo.h"
#include "titleenter.h"
#include "titleselect.h"
#include "titlecursor.h"
#include "loading.h"
#include "alpha.h"
#include "sphere.h"




void Title::Init()
{
	

	ResultCamera* camera = AddGameObject<ResultCamera>(LAYER_CAMERA);
	camera->Setoffset(D3DXVECTOR3(2.0f, 1.0f, 1.0f));
	AddGameObject<ResultSky>(LAYER_OBJECT_3D);
	MeshField* meshField = AddGameObject<MeshField>(LAYER_OBJECT_3D);
	ResultPlayer* player = AddGameObject<ResultPlayer>(LAYER_OBJECT_3D);

	AddGameObject<Alpha>(LAYER_OBJECT_2D);
	AddGameObject<TitleLogo>(LAYER_OBJECT_2D);
	
	m_TitleSelect = AddGameObject<TitleSelect>(LAYER_OBJECT_2D);
	m_TitleSelect->SetAlpha(0.0f);
	m_TitleCursor = AddGameObject<TitleCursor>(LAYER_OBJECT_2D);
	m_TitleCursor->SetAlpha(0.0f);
	m_TitleEnter = AddGameObject<TitleEnter>(LAYER_OBJECT_2D);


	//BGMçƒê∂
	Audio* bgm;
	bgm = AddGameObject<GameObject>(0)->AddComponent<Audio>();
	bgm->Load("asset\\audio\\TitleBGM.wav");
	
	bgm->Play(true);
	
	//m_ShotSE1 = AddGameObject<GameObject>(LAYER_OBJECT_NOTDRAW)->AddComponent<Audio>();
	//m_ShotSE1->Load("asset\\audio\\VSQSE_0665_heavy_metal_hit_03.wav");
}
void Title::Uninit()
{
	Scene::Uninit();
}

void Title::Update()
{
	Scene::Update();


	if (m_TitleEnter->GetIsPressEnter() && m_Phase == 0)
	{
		m_Phase++;
		//m_ShotSE1->Play(false);
		m_TitleEnter->SetAlpha(0.0f);
		m_TitleSelect->SetAlpha(1.0f);
	}
}
