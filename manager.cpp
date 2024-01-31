#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "input.h"
#include "game.h"
#include "test.h"
#include "title.h"
#include "networkTest.h"
#include "audio.h"
#include "debugmanager.h"
#include "loading.h"

#include "bloomPolygon.h"
#include "luminance.h"
#include "post.h"

Scene* Manager::m_Scene{};//静的メンバ変数は再宣言が必要
Scene* Manager::m_NextScene{};//静的メンバ変数は再宣言が必要
Renderer* Manager::m_Renderer{};

bool Manager::m_IsGameFinish{};

void Manager::Init()
{
	m_Renderer = new Renderer();
	m_Renderer->Init();

	//DebugManager::Init();

	Input::Init();
	Audio::InitMaster();
	m_IsGameFinish = false;




	SetScene<Title>();//ゲーム開始時のシーンを設定



}

void Manager::Uninit()
{
	if (m_Scene != nullptr)m_Scene->Uninit();
	delete m_Scene;

	Audio::UninitMaster();
	Input::Uninit();
	//DebugManager::Uninit();
	m_Renderer->Uninit();
}

void Manager::Update()
{
	Input::Update();
	if (m_NextScene)
	{
		if (m_Scene)
		{
			m_Scene->Uninit();
			delete m_Scene;
		}


		m_Scene = m_NextScene;
		m_Scene->Init();

		

		m_NextScene = nullptr;
	}
	//DebugManager::Update();
	if(m_Scene != nullptr) m_Scene->Update();
}

void Manager::Draw()
{
	//ライトカメラ構造体の初期化
	LIGHT light;
	light.Enable = true;

	if (m_Scene == nullptr) return;

	D3DXVECTOR3 testposition = m_Scene->GetPlayerPosition();
	LightInitialize(&light, testposition);

	//1パス目    シャドーバッファの作成
	Renderer::BeginDepth();
	Renderer::SetDepthViewPort();

	//ライトカメラの行列をセット
	Renderer::SetViewMatrix(&light.ViewMatrix);
	Renderer::SetProjectionMatrix(&light.ProjectionMatrix);

	//影を落としたいオブジェクトを描画	
	m_Scene->DepthPath();


	if (m_Scene->GetIsBloom())
	{
		m_Renderer->BeginPP();
		Renderer::SetDefaultViewPort();


		m_Scene->Draw();

		//bloom
		//ライト無効
		light.Enable = false;
		Renderer::SetLight(light);
		//2パス目 輝度抽出用バッファにレンダリング
		Renderer::BeginLuminance();
		Renderer::SetLuminanceViewport();
		m_Scene->GetGameObject<Luminance>()->Draw();
		//3～6パス目 縮小バッファへレンダリング
		for (int i = 0; i < 4; i++)
		{
			Renderer::BeginBloom(i);
			Renderer::SetBloomViewport(i);
			m_Scene->GetGameObject<BloomPolygon>()->Draw(i);
		}
		//7パス目
		Renderer::Begin();
		Renderer::SetDefaultViewPort();
		m_Scene->GetGameObject<Post>()->Draw();
	}
	else
	{
		m_Renderer->Begin();
		Renderer::SetDefaultViewPort();

		m_Scene->Draw();
	}

	m_Scene->Draw2D();

	//DebugManager::Draw();

	m_Renderer->End();

}




void Manager::LightInitialize(LIGHT * light, D3DXVECTOR3 position)
{
	light->Direction = D3DXVECTOR4(1.0f, -1.0f, 0.0f, 0.0f);
	D3DXVec4Normalize(&light->Direction, &light->Direction);
	light->Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	light->Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//ライトカメラのビュー行列を作成
	D3DXVECTOR3 lightPos = position + D3DXVECTOR3(0.0f, 10.0f, -5.0f);//0.0f, 20.0f, -5.0f
	D3DXVECTOR3 lightTarget = position;
	D3DXVECTOR3 lightUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&light->ViewMatrix, &lightPos, &lightTarget, &lightUp);

	//ライトカメラのプロジェクション行列を作成
	D3DXMatrixPerspectiveFovLH(&light->ProjectionMatrix, 1.0f, (float)(SCREEN_WIDTH) / (float)(SCREEN_HEIGHT), 1.0f, 1000.0f);

	Renderer::SetLight(*light);
}
