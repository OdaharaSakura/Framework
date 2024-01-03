#include "main.h"
#include "renderer.h"
#include "player.h"
#include "input.h"
#include "bullet.h"
#include "manager.h"
#include "scene.h"
#include "cylinder.h"
#include "enemy.h"
#include "gauge.h"
#include "bed.h"
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
#include "playerNetwork.h"
#include "shader.h"
#include "time.h"
#include "npc.h"
#include "conversation.h"

//AnimationModel* Player::m_Model{};

void Player::Load()
{

}

void Player::Unload()
{

}

void Player::Init()
{
	Scene* scene = Manager::GetScene();
	
	m_Model = new AnimationModel();
	m_Model->Load("asset\\model\\fbx\\Player.fbx");
	m_Model->LoadAnimation("asset\\model\\fbx\\Player_Idle.fbx", "Idle");
	m_Model->LoadAnimation("asset\\model\\fbx\\Player_Run.fbx", "Run");
	m_Model->LoadAnimation("asset\\model\\fbx\\Player_LeftRun.fbx", "LeftRun");
	m_Model->LoadAnimation("asset\\model\\fbx\\Player_RightRun.fbx", "RightRun");
	m_Model->LoadAnimation("asset\\model\\fbx\\Player_BackRun.fbx", "BackRun");
	m_Model->LoadAnimation("asset\\model\\fbx\\Player_Attack.fbx", "Attack");
	m_Model->LoadAnimation("asset\\model\\fbx\\Player_Death.fbx", "Death");
	m_Model->LoadAnimation("asset\\model\\fbx\\Player_InPlaceJump.fbx", "InPlaceJump");
	m_AnimationName = "Idle";
	m_NextAnimationName = "Idle";


	m_modelScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	SetPlayer();//Sceneにpositionを渡すための
	m_IsPlayer = true;

	m_Description = scene->AddGameObject<GameObject>(LAYER_OBJECT_2D)->AddComponent<Text>();
	m_Description->SetPosition(D3DXVECTOR2(SCREEN_WIDTH / 3, SCREEN_HEIGHT - 50.0f));

	

	AddComponent<PercentageCloserFiltering>();//影

	 //m_ShotSE = AddComponent<Audio>();
	 //m_ShotSE->Load("asset\\audio\\剣で斬る3.wav");

	 //AddComponent<SphireCollider>()->SetSphireCollider(this, 1.0f);
	 
	 m_AttackDelaynum = 0;
	 m_IsAttackflg = false;
	 m_Attackflg = false;
	 m_Hp = m_HpMax;
}

void Player::Uninit()
{
	GameObject::Uninit();
	if (m_Model != nullptr)m_Model->Unload();
	delete m_Model;
}

void Player::Update()
{
	//GameObject::Update();
	Scene* scene = Manager::GetScene();
	D3DXVECTOR3 oldPosition = m_WorldPosition;

	m_IsAttackflg = false;
	

	//メモ：当たり判定コンポーネントにする（判定の仕方ごとに関数変える）
	//ImGUIのカメラに映せるように変更したい

	//敵当たり判定
	std::vector<Enemy*> enemies = scene->GetGameObjects<Enemy>();
	for (Enemy* enemy : enemies)
	{
		D3DXVECTOR3 position = enemy->GetPosition();
		D3DXVECTOR3 scale = enemy->GetScale();
		D3DXVECTOR3 scalexz = enemy->GetScale();

		D3DXVECTOR3 direction = m_WorldPosition - position;
		direction.y = 0.0f;
		float length = D3DXVec3Length(&direction);
		scalexz.y = 0.0f;
		float lengthxz = D3DXVec3Length(&scalexz);
		if (length < lengthxz)
		{
			if (m_WorldPosition.y + m_Scale.y < position.y + scale.y - 0.5f)
			{
				m_WorldPosition.x = oldPosition.x;
				m_WorldPosition.z = oldPosition.z;
				m_Hp -= 3;
			}
		}
		if (length < lengthxz * lengthxz)
		{
			m_IsAttackflg  = true;
		}
	}

	//プレイヤー当たり判定
	std::vector<PlayerNetWork*> players = scene->GetGameObjects<PlayerNetWork>();
	for (PlayerNetWork* player : players)
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

	switch (m_PlayerState)
	{
	case PLAYER_STATE_TITLE:
		UpdateTitle();
		break;
	case PLAYER_STATE_GROUND:
		UpdateGround();
		break;
	case PLAYER_STATE_JUMP:
		UpdateJump();
		break;
	case PLAYER_STATE_ATTACK:
		UpdateAttack();
		break;
	case PLAYER_STATE_CONVERSATION:
		UpdateConversation();
		break;
	}

	//移動
	m_WorldPosition += m_Velocity;//オイラー法

	//障害物との衝突判定↓↓=====================================
	float groundHeight;

	MeshField* meshfield = scene->GetGameObject<MeshField>();
	if(meshfield != nullptr)groundHeight = meshfield->GetHeight(m_WorldPosition);
	else groundHeight = 0.0f;

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



	//ベッド
	auto bed = scene->GetGameObject<Bed>();
	if(bed !=nullptr)
	{
		D3DXVECTOR3 position = bed->GetPosition();
		D3DXVECTOR3 scale = bed->GetScale();



		if (position.x - (scale.x * 2.0f)- (scale.x / 2) < m_WorldPosition.x &&
			m_WorldPosition.x < position.x + (scale.x * 2.0f) + (scale.x / 2) &&
			position.z - (scale.z * 2.0f) - (scale.z / 2) < m_WorldPosition.z &&
			m_WorldPosition.z < position.z + (scale.z * 2.0f) + (scale.z / 2))
		{
			if (m_countnum >= 1)
			{
				m_Description->SetText("ベッドで眠りました");
				m_countnum += 1;
				if (60 <= m_countnum) m_countnum = 0;

			}
			else m_Description->SetText("U：ベッドで眠る");

			if (Input::GetKeyTrigger('U'))
			{
				Time* time = scene->GetGameObject<Time>();
				time->SetSleep();

				m_countnum += 1;
			}

			if (position.x - scale.x - (scale.x / 2) < m_WorldPosition.x &&
				m_WorldPosition.x < position.x + scale.x + (scale.x / 2) &&
				position.z - scale.z - (scale.z / 2) < m_WorldPosition.z &&
				m_WorldPosition.z < position.z + scale.z + (scale.z / 2))
			{
				if (m_WorldPosition.y < position.y + scale.y * 1.0f - 0.5f)//2.0fはモデルの大きさ高さ1じゃなくて2だとこうなる
				{//当たったら
					m_WorldPosition.x = oldPosition.x;
					m_WorldPosition.z = oldPosition.z;

				}
				else
				{
					groundHeight = position.y + scale.y * 2.0f;
				}
			}
			
		}
		else
		{
			m_Description->SetText("");
		}
	}

	//土
	
	std::vector<NPC*> NPCs = scene->GetGameObjects<NPC>();
	for (NPC* npc : NPCs)
	{
		if (npc->GetIsHitPlayer())
		{
			if (Input::GetKeyTrigger('U'))
			{
				m_Conversation = scene->AddGameObject<Conversation>(LAYER_OBJECT_2D);
				m_Message = npc->GetConversation();
				m_Conversation->SetText(m_Message);
				m_PlayerState = PLAYER_STATE_CONVERSATION;
			}
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

	m_Time++;
	m_BlendRate += 0.1f;
}

void Player::Draw()
{
	//GameObject::Draw();

	//視錘台カリング
	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>();

	if (!camera->CheckView(m_WorldPosition)) return;
	

	// マトリクス設定
	D3DXMATRIX matrix, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_modelScale.x, m_modelScale.y, m_modelScale.z);
	//D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);//モデルによるが、後ろ向いてたら+ D3DX_PIで180度回転させる
	D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);
	D3DXMatrixTranslation(&trans, m_WorldPosition.x, m_WorldPosition.y, m_WorldPosition.z);
	matrix = scale * rot * trans;
	m_Matrix = matrix;

	Renderer::SetWorldMatrix(&matrix);
	
	m_Model->Update(m_AnimationName.c_str(), m_Time, m_NextAnimationName.c_str(), m_Time, m_BlendRate);


	if (m_BlendRate > 1.0f) m_BlendRate = 1.0f;
	m_Model->Draw();
}

void Player::UpdateTitle()
{

	m_AnimationName = "Idle";

}

void Player::UpdateGround()
{
	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>();
	D3DXVECTOR3 cameraForward = camera->GetForward();
	D3DXVECTOR3 cameraRight = camera->GetRight();
	cameraForward.y = 0.0f;
	cameraRight.y = 0.0f;
	D3DXVec3Normalize(&cameraForward, &cameraForward);
	D3DXVec3Normalize(&cameraRight, &cameraRight);
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

	//サードパーソンビュー
	if (Input::GetKeyPress('A'))
	{
		if (m_NextAnimationName != "LeftRun")
		{
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "LeftRun";
			m_BlendRate = 0.0f;
		}
		//moveVec -= GetRight();
		//m_WorldPosition.x -= 0.1f;
		m_WorldPosition -= cameraRight * 0.1f;

		D3DXQUATERNION quat;
		D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		float angle = atan2f(cameraForward.x, cameraForward.z);
		D3DXQuaternionRotationAxis(&quat, &axis, angle);//(左方向に90度)
		//m_Quaternion = quat;
		D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.1f);

		move = true;
		if (m_IsConnectNetWork) m_InputData = 'A';

	}
	if (Input::GetKeyPress('D'))
	{
		if (m_NextAnimationName != "RightRun")
		{
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "RightRun";
			m_BlendRate = 0.0f;
		}
		
		//moveVec += GetRight();
		//m_WorldPosition.x += 0.1f;
		m_WorldPosition += cameraRight * 0.1f;
		

		D3DXQUATERNION quat;
		D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		float angle = atan2f(cameraForward.x, cameraForward.z);
		D3DXQuaternionRotationAxis(&quat, &axis, angle);//(左方向に90度)
		//m_Quaternion = quat;
		D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.1f);
		move = true;
		if (m_IsConnectNetWork) m_InputData = 'D';
	}
	if (Input::GetKeyPress('W'))
	{

		if (m_NextAnimationName != "Run")
		{
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "Run";
			m_BlendRate = 0.0f;
		}

		//moveVec += GetForward();
		m_WorldPosition += cameraForward * 0.1f;

		D3DXQUATERNION quat;
		D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		float angle = atan2f(cameraForward.x, cameraForward.z);
		D3DXQuaternionRotationAxis(&quat, &axis, angle);//(左方向に90度)
		//m_Quaternion = quat;
		D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.1f);
		move = true;
		if (m_IsConnectNetWork) m_InputData = 'W';
	}

	if (Input::GetKeyPress('S'))
	{
		if (m_NextAnimationName != "BackRun")
		{
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "BackRun";
			m_BlendRate = 0.0f;
		}

		//moveVec -= GetForward();
		m_WorldPosition -= cameraForward * 0.1f;
		//m_WorldPosition.z -= 0.1f;

		D3DXQUATERNION quat;
		D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		float angle = atan2f(cameraForward.x, cameraForward.z);
		D3DXQuaternionRotationAxis(&quat, &axis, angle);//(左方向に90度)
		//m_Quaternion = quat;
		D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.1f);
		move = true;
		if (m_IsConnectNetWork) m_InputData = 'S';
	}

	//D3DXVec3Normalize(&moveVec, &moveVec);
	//m_WorldPosition += moveVec * 0.1f;



	if (Input::GetKeyPress('Q'))
	{
		m_Rotation.y -= 0.1f;
	}
	if (Input::GetKeyPress('E'))
	{
		m_Rotation.y += 0.1f;
	}
	if (m_AnimeFrame < 17 && m_AnimeState == ATTACK)
	{
		m_AnimeState = ATTACK;
	}

	//攻撃
	if (Input::GetKeyPress('I'))
	{

		m_ShotSE->Play(false);
		if (m_NextAnimationName != "Attack")
		{
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "Attack";
			m_BlendRate = 0.0f;
		}
		move = true;
		m_PlayerState = PLAYER_STATE_ATTACK;
		if (m_IsAttackflg)
		{
			m_Attackflg = true;
		}

	}

	//土魔法
	if (Input::GetKeyPress('L'))
	{
		D3DXVECTOR3 earthPosition;
		earthPosition = m_WorldPosition + this->GetForward() * 2.0f;
		scene->AddGameObject<Earth>(LAYER_OBJECT_3D)->SetPosition(earthPosition);//プレイヤーの位置から発射させる

	}

	//ジャンプ
	if (Input::GetKeyPress('J') && m_Velocity.y == 0.0f)
	{
		m_Velocity.y = 0.35f;
		m_PlayerState = PLAYER_STATE_JUMP;

		if (m_NextAnimationName != "InPlaceJump")
		{
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "InPlaceJump";
			m_BlendRate = 0.0f;
		}
		move = true;
	}

	if (Input::GetKeyPress('C'))
	{
		camera->Shake(1.5f);
	}



	if (move == false)
	{
		if (m_NextAnimationName != "Idle")
		{
			m_AnimationName = m_NextAnimationName;
			m_NextAnimationName = "Idle";
			m_BlendRate = 0.0f;
		}
	}
}

void Player::UpdateJump()
{
	if (m_IsGround == true)
	{
		m_PlayerState = PLAYER_STATE_GROUND;

	}
}

void Player::UpdateAttack()
{
	m_AttackDelaynum++;
	if (m_AttackDelaynum > 25)
	{
		m_PlayerState = PLAYER_STATE_GROUND;
		m_AttackDelaynum = 0;
	}
}

void Player::UpdateConversation()
{
	if (Input::GetKeyTrigger('O'))
	{
		m_Conversation->SetDestroy();
		m_PlayerState = PLAYER_STATE_GROUND;
	}
}

