#include "main.h"
#include "manager.h"
#include "scene.h"
#include "renderer.h"
#include "input.h"
#include "title.h"
#include "titlecursor.h"
#include "sprite.h"
#include "audio.h"
#include "fade.h"
#include "loading.h"

void TitleCursor::Init()
{
	Scene* scene = Manager::GetScene();
	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout, "shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\unlitTexturePS.cso");

	m_Fade = scene->AddGameObject<Fade>(LAYER_OBJECT_2D);

	m_Scale.x = SCREEN_WIDTH / 3;
	m_Scale.y = SCREEN_HEIGHT / 3;

	m_WorldPosition.x = (SCREEN_WIDTH / 2) - (m_Scale.x / 2);
	m_WorldPosition.y = ((SCREEN_HEIGHT / 5) * 4) - (m_Scale.y / 2);

	m_Sprite = AddComponent<Sprite>();
	m_Sprite->Init(m_WorldPosition.x, m_WorldPosition.y, m_Scale.x, m_Scale.y, "asset/texture/titlecursor.png");

	//初めの位置を保存
	m_StartPosition.x = (SCREEN_WIDTH / 2) - (m_Scale.x / 2);
	m_StartPosition.y = ((SCREEN_HEIGHT / 5) * 4) - (m_Scale.y / 2);

	m_ShotSEEnter = AddComponent<Audio>();
	m_ShotSEEnter->Load("asset\\audio\\VSQSE_0665_heavy_metal_hit_03.wav");

	m_ShotSE2Select = AddComponent<Audio>();
	m_ShotSE2Select->Load("asset\\audio\\RPG_erabu.wav");
}

void TitleCursor::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	//基底クラスのメソッド呼び出し
	GameObject::Uninit();
}

void TitleCursor::Update()
{
	//基底クラスのメソッド呼び出し
	GameObject::Update();

	
	//キー入力
	if (Input::GetKeyPress('W'))
	{
		m_Color.a = 1.0f;
		m_delaynum += 0.1f;
		if (m_delaynum >= 0.7f)
		{
			m_ShotSE2Select->Play(false);
			m_NextPhase -= 1;
			if (m_NextPhase < Select::HAJIME)
			{
				m_NextPhase = Select::UNINIT;
			}
			m_delaynum = 0.0f;
		}	
	}

	if (Input::GetKeyPress('S'))
	{
		m_Color.a = 1.0f;
		m_delaynum += 0.1f;
		if (m_delaynum >= 0.7f)
		{
			m_ShotSE2Select->Play(false);
			m_NextPhase += 1;
			if (m_NextPhase > Select::UNINIT)
			{
				m_NextPhase = Select::HAJIME;
			}
			m_delaynum = 0.0f;
		}
	}

	//カーソル移動
	switch (m_NextPhase)
	{
	case Select::HAJIME:
		m_WorldPosition.y = m_StartPosition.y;
		break;
	case Select::UNINIT:
		m_WorldPosition.y = (m_StartPosition.y + m_MoveRange);
		break;
	default:
		break;
	}



	if (Input::GetKeyPress(VK_SPACE) && !m_IsPressEnter && m_NextPhase != SELECT_NULL)
	{
		switch(m_NextPhase)
		{
		case 1 :
			m_Fade->SetFadeSpeed(0.05f);
			m_Fade->SetIsFadeOut();

			break;
		case 2 :
			Manager::SetIsGameFinish();
			break;
		default:
			break;
		}
		m_ShotSEEnter->Play(false);
	}
	if (m_Fade->GetFadeOutFinish())
	{
		Manager::SetScene<Loading>();//エンターキーを押したらゲームシーンに移行	
	}
	m_Sprite->SetPositionY(m_WorldPosition.y);
	
	m_Sprite->SetColor(m_Color);
}

void TitleCursor::Draw()
{
	// 入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	// シェーダ設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);



	// マトリクス設定
	Renderer::SetWorldViewProjection2D();

	//基底クラスのメソッド呼び出し
	GameObject::Draw();
}