#include "main.h"
#include "renderer.h"
#include "playerNetWork.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "manager.h"
#include "scene.h"
#include "cylinder.h"
#include "enemy.h"
#include "gauge.h"
#include "box.h"
#include "audio.h"
#include "shadow.h"
#include "animationModel.h"
#include "result.h"
#include "gameover.h"
#include "earth.h"
#include "meshField.h"
#include "camera.h"
#include "collider.h"
#include "text.h"
#include "animationModelContainer.h"


void PlayerNetWork::Init()
{
	Scene* scene = Manager::GetScene();
	m_Model = AnimationModelContainer::GetAnimationModel_Key(FBXModel::FBXModel_Player);

	m_AnimationIndex = PlayerAnimation::Player_Idle;
	m_NextAnimationIndex = PlayerAnimation::Player_Idle;

	m_IsDisplayShadow = true;

	m_modelScale = D3DXVECTOR3(0.015f, 0.015f, 0.015f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout, "shader\\PercentageCloserFilteringVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\PercentageCloserFilteringPS.cso");


	 //m_ShotSE = AddComponent<Audio>();
	 //m_ShotSE->Load("asset\\audio\\剣で斬る3.wav");

	 //AddComponent<SphireCollider>()->SetSphireCollider(this, 1.0f);
	 

	 m_AttackDelaynum = 0;
	 m_IsAttackflg = false;
	 m_Attackflg = false;
	 m_Hp = m_HpMax;
}

void PlayerNetWork::Uninit()
{
	GameObject::Uninit();
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void PlayerNetWork::Update()
{
	GameObject::Update();
	Scene* scene = Manager::GetScene();
	D3DXVECTOR3 oldPosition = m_WorldPosition;


	//メモ：当たり判定コンポーネントにする（判定の仕方ごとに関数変える）
	//ImGUIのカメラに映せるように変更したい

	switch (m_PlayerState)
	{
	case PLAYER_STATE_GROUND:
		UpdateGround();
		break;
	case PLAYER_STATE_JUMP:
		UpdateJump();
		break;
	case PLAYER_STATE_ATTACK:
		UpdateAttack();
		break;
	}

	//移動
	m_WorldPosition += m_Velocity;//オイラー法

		//プレイヤー当たり判定
	std::vector<Player*> players = scene->GetGameObjects<Player>();
	for (Player* player : players)
	{
		D3DXVECTOR3 position = player->GetPosition();
		D3DXVECTOR3 scale = player->GetScale();
		D3DXVECTOR3 scalexz = player->GetScale();


		D3DXVECTOR3 direction = m_WorldPosition - position;
		direction.y = 0.0f;
		float length = D3DXVec3Length(&direction);
		scalexz.y = 0.0f;
		float lengthxz = D3DXVec3Length(&scalexz);
		if ((length * length) < (lengthxz * lengthxz))
		{
			m_WorldPosition.x = oldPosition.x;
			m_WorldPosition.z = oldPosition.z;
		}
		else
		{
		}
		
		if (length < lengthxz * lengthxz)
		{
			m_IsAttackflg = true;
		}
	}

	//障害物との衝突判定↓↓=====================================
	float groundHeight;

	MeshField* meshfield = scene->GetGameObject<MeshField>();
	groundHeight = meshfield->GetHeight(m_WorldPosition);

	//円柱
	std::vector<Cylinder*> cylinders = scene->GetGameObjects<Cylinder>();
	for (Cylinder* cylinder : cylinders)
	{
		D3DXVECTOR3 position = cylinder->GetPosition();
		D3DXVECTOR3 scale = cylinder->GetScale();
		D3DXVECTOR3 scalexz = cylinder->GetScale();

		D3DXVECTOR3 direction = m_WorldPosition - position;
		direction.y = 0.0f;
		float length = D3DXVec3Length(&direction);
		scalexz.y = 0.0f;
		float lengthxz = D3DXVec3Length(&scalexz);
		if (length < lengthxz)
		{
			if (m_WorldPosition.y < position.y + scale.y - 0.5f)
			{
				m_WorldPosition.x = oldPosition.x;
				m_WorldPosition.z = oldPosition.z;
			}

			else
			{
				groundHeight = position.y + scale.y;
			}

			break;
		}
	}

	
	//障害物との衝突判定↑↑=====================================

		//重力
	m_Velocity.y -= 0.015f;


	//接地
	if (m_WorldPosition.y < groundHeight && m_Velocity.y < 0.0f)
	{
		m_WorldPosition.y = groundHeight;
		m_Velocity.y = 0.0f;
		m_IsGround = true;
	}
	else
	{
		m_IsGround = false;
	}

	if (m_Hp <= 0)
	{
		//Manager::SetScene<GameOver>();
	}
}

void PlayerNetWork::Draw()
{
	GameObject::Draw();

	//視錘台カリング
	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>();

	if (!camera->CheckView(m_WorldPosition)) return;

	// 入力レイアウト設定ト（DirectXへ頂点の構造を教える）
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	// 使用するシェーダを設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);//バーテックスシェーダーオブジェクトのセット
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);//ピクセルシェーダーオブジェクトのセット

	// マトリクス設定
	D3DXMATRIX matrix, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_modelScale.x, m_modelScale.y, m_modelScale.z);
	//D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);//モデルによるが、後ろ向いてたら+ D3DX_PIで180度回転させる
	D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);
	D3DXMatrixTranslation(&trans, m_WorldPosition.x, m_WorldPosition.y, m_WorldPosition.z);
	matrix = scale * rot * trans;
	m_Matrix = matrix;

	Renderer::SetWorldMatrix(&matrix);

	//シャドウバッファテクスチャを１番へセット
	ID3D11ShaderResourceView* depthShadowTexture =
	Renderer::GetDepthShadowTexture();
	Renderer::GetDeviceContext()->PSSetShaderResources(1, 1,
		&depthShadowTexture);
	
	m_Model->Update(m_AnimationIndex, m_Time, m_NextAnimationIndex, m_Time, m_BlendRate);

	m_Time++;
	m_BlendRate += 0.1f;
	if (m_BlendRate > 1.0f) m_BlendRate = 1.0f;
	m_Model->Draw();
}

void PlayerNetWork::UpdateGround()
{
	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>();
	D3DXVECTOR3 cameraForward = camera->GetForward();
	cameraForward.y = 0.0f;
	D3DXVec3Normalize(&cameraForward, &cameraForward);
	bool move = false;

	////トップビュー
	//if (Input::GetKeyPress('A'))
	//{
	//	m_WorldPosition.x -= 0.1f;
	// 		m_Rotation.y = -D3DX_PI * 0.5f;
	//}
	//if (Input::GetKeyPress('D'))
	//{
	//	m_WorldPosition.x += 0.1f;
	// 		m_Rotation.y = D3DX_PI * 0.5f;
	//}
	//if (Input::GetKeyPress('W'))
	//{
	//	m_WorldPosition.z += 0.1f;
	//	m_Rotation.y = D3DX_PI * 0.0f;
	//}
	//if (Input::GetKeyPress('S'))
	//{
	//	m_WorldPosition.z -= 0.1f;
	//	m_Rotation.y = D3DX_PI * 1.0f;
	//}


	D3DXVECTOR3 moveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	int key = 0;
	key = m_PositionList.size();
	if (key != 0)
	{
		if (m_PositionList[0] == m_WorldPosition)
		{
			m_PositionList.erase(m_PositionList.begin());
		}
		else
		{
			//サードパーソンビュー
			if (m_PositionList[0].x < m_WorldPosition.x)
			{
				if (m_NextAnimationIndex != PlayerAnimation::Player_LeftRun)
				{
					m_AnimationIndex = m_NextAnimationIndex;
					m_NextAnimationIndex = PlayerAnimation::Player_LeftRun;
					m_BlendRate = 0.0f;
				}
				moveVec -= GetRight();
				//m_WorldPosition.x -= 0.1f;

				D3DXQUATERNION quat;
				D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				D3DXQuaternionRotationAxis(&quat, &axis, -D3DX_PI / 2.0f);//(左方向に90度)
				//m_Quaternion = quat;
				D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.1f);//球面変形補間

				move = true;

			}
			if (m_PositionList[0].x > m_WorldPosition.x)
			{
				if (m_NextAnimationIndex != PlayerAnimation::Player_RightRun)
				{
					m_AnimationIndex = m_NextAnimationIndex;
					m_NextAnimationIndex = PlayerAnimation::Player_RightRun;
					m_BlendRate = 0.0f;
				}

				moveVec += GetRight();

				D3DXQUATERNION quat;
				D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				D3DXQuaternionRotationAxis(&quat, &axis, D3DX_PI / 2.0f);//(左方向に90度)
				//m_Quaternion = quat;
				D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.1f);
				move = true;
			}
			if (m_PositionList[0].z > m_WorldPosition.z)
			{

				if (m_NextAnimationIndex != PlayerAnimation::Player_Run)
				{
					m_AnimationIndex = m_NextAnimationIndex;
					m_NextAnimationIndex = PlayerAnimation::Player_Run;
					m_BlendRate = 0.0f;
				}

				moveVec += GetForward();
				//m_WorldPosition += m_WorldPosition.z * 0.1f;

				D3DXQUATERNION quat;
				D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

				float angle = atan2f(cameraForward.x, cameraForward.z);
				D3DXQuaternionRotationAxis(&quat, &axis, angle);//(左方向に90度)
				//m_Quaternion = quat;
				D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.1f);
				move = true;
			}

			if (m_PositionList[0].z < m_WorldPosition.z)
			{
				if (m_NextAnimationIndex != PlayerAnimation::Player_BackRun)
				{
					m_AnimationIndex = m_NextAnimationIndex;
					m_NextAnimationIndex = PlayerAnimation::Player_BackRun;
					m_BlendRate = 0.0f;
				}

				moveVec -= GetForward();

				D3DXQUATERNION quat;
				D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
				D3DXQuaternionRotationAxis(&quat, &axis, D3DX_PI);//(左方向に90度)
				//m_Quaternion = quat;
				D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.1f);
				move = true;
			}
		}
	}
	

	if (move == false)
	{
		if (m_NextAnimationIndex != PlayerAnimation::Player_Idle)
		{
			m_AnimationIndex = m_NextAnimationIndex;
			m_NextAnimationIndex = PlayerAnimation::Player_Idle;
			m_BlendRate = 0.0f;
		}
	}
}

void PlayerNetWork::UpdateJump()
{
	if (m_IsGround == true)
	{
		m_PlayerState = PLAYER_STATE_GROUND;

	}
}

void PlayerNetWork::UpdateAttack()
{
	m_AttackDelaynum++;
	if (m_AttackDelaynum > 25)
	{
		m_PlayerState = PLAYER_STATE_GROUND;
		m_AttackDelaynum = 0;
	}
}

