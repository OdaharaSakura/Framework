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
#include "iEquipment.h"
#include "inventory.h"
#include "itemFactory.h"
#include "equipmentFactory.h"
#include "equipment.h"
#include "item.h"
#include "farmField.h"
#include "farmTile.h"
#include "animationModelContainer.h"
#include "collider.h"
#include "sphereObject.h"
#include "boxObject.h"
#include "house.h"
#include "fade.h"
#include "testHouse.h"

AnimationModel* Player::m_Model{};

void Player::Init()
{
	Scene* scene = Manager::GetScene();
	m_EquipmentInterface = scene->GetGameObject<IEquipment>();
	m_InventoryInterface = scene->GetGameObject<Inventory>();

	m_ItemFactory = new ItemFactory();
	m_EquipmentFactory= new EquipmentFactory();
	auto hoe = m_ItemFactory->CreateItem("Hoe");
	m_InventoryInterface->AddItem(hoe);


	auto kama = m_ItemFactory->CreateItem("Sickle");
	m_InventoryInterface->AddItem(kama);

	auto wand = m_ItemFactory->CreateItem("WaterWand");
	m_InventoryInterface->AddItem(wand);

	auto sword = m_ItemFactory->CreateItem("Sword");
	m_InventoryInterface->AddItem(sword);

	auto tomatoSeed = m_ItemFactory->CreateItem("TomatoSeed");
	m_InventoryInterface->AddItem(tomatoSeed);

	auto carrotSeed = m_ItemFactory->CreateItem("CarrotSeed");
	m_InventoryInterface->AddItem(carrotSeed);
	
	m_Model = AnimationModelContainer::GetAnimationModel_Key(FBXModel::FBXModel_Player);
	
	m_AnimationIndex = PlayerAnimation::Player_Idle;
	m_NextAnimationIndex = PlayerAnimation::Player_Idle;


	m_ModelScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	SetPlayer();//Sceneにpositionを渡すための
	m_IsPlayer = true;

	m_Description = scene->AddGameObject<GameObject>(LAYER_OBJECT_2D)->AddComponent<Text>();
	m_Description->SetPosition(D3DXVECTOR2(SCREEN_WIDTH / 3, SCREEN_HEIGHT - 50.0f));

	

	AddComponent<PercentageCloserFiltering>();//影

	 //m_ShotSE = AddComponent<Audio>();
	 //m_ShotSE->Load("asset\\audio\\剣で斬る3.wav");

	 //AddComponent<SphereCollider>()->SetSphereCollider(1.0f, m_WorldPosition);
	 
	 m_AttackDelaynum = 0;
	 m_IsAttackflg = false;
	 m_Attackflg = false;
	 m_Hp = m_HpMax;
}

void Player::Uninit()
{
	GameObject::Uninit();
	if(m_Model) m_Model = nullptr;
}

void Player::Update()
{
	//GameObject::Update();
	Scene* scene = Manager::GetScene();
	m_OldPosition = m_WorldPosition;
	m_Description->SetText("");
	m_IsAttackflg = false;
	

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
	case PLAYER_STATE_INVENTORY:
		UpdateInventory();
		break;
	case PLAYER_STATE_PLOW:
		UpdatePlow();
		break;
	}

	//移動
	m_WorldPosition += m_Velocity;//オイラー法

	//障害物との衝突判定↓↓=====================================
	float groundHeight{};

	auto meshFields = scene->GetGameObjects<MeshField>();

	for (auto meshField : meshFields)
	{
		if (meshField != nullptr) groundHeight = meshField->GetHeight(m_WorldPosition);
		else groundHeight = 0.0f;
	}
	

	//SphereCollider
	std::vector<SphereObject*> sphereObjects = scene->GetSphereColliderObjects<SphereObject>();
	for (SphereObject* sphereObject : sphereObjects)
	{
		D3DXVECTOR3 position = sphereObject->GetPosition();
		D3DXVECTOR3 scalexz = sphereObject->GetScale();

		D3DXVECTOR3 direction = m_WorldPosition - position;
		direction.y = 0.0f;
		float length = D3DXVec3Length(&direction);
		scalexz.y = 0.0f;
		float lengthxz = D3DXVec3Length(&scalexz);
		if ((length * length) <= lengthxz)
		{
			m_WorldPosition.x = m_OldPosition.x;
			m_WorldPosition.z = m_OldPosition.z;
		}
	}

	//BoxCollider
	std::vector<BoxObject*> boxObjects = scene->GetBoxColliderObjects<BoxObject>();
	for (BoxObject* boxObject : boxObjects)
	{
		D3DXVECTOR3 position = boxObject->GetPosition();
		D3DXVECTOR3 scale = boxObject->GetScale();

		if (position.x - scale.x - (scale.x / 2) < m_WorldPosition.x &&
			m_WorldPosition.x < position.x + scale.x + (scale.x / 2) &&
			position.z - scale.z - (scale.z / 2) < m_WorldPosition.z &&
			m_WorldPosition.z < position.z + scale.z + (scale.z / 2))
		{

			m_WorldPosition.x = m_OldPosition.x;
			m_WorldPosition.z = m_OldPosition.z;

		}
	}

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
				m_WorldPosition.x = m_OldPosition.x;
				m_WorldPosition.z = m_OldPosition.z;
				m_Hp -= 3;
			}
		}
		if (length < lengthxz * lengthxz)
		{
			enemy->SetDamageflg(true);
		}
		else
		{
			enemy->SetDamageflg(false);
		}
	}

	
	//障害物との衝突判定↑↑=====================================

	if (Input::GetKeyTrigger('E'))
	{
		m_EquipmentInterface->RemoveEquipment();
	}

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
		Manager::SetScene<GameOver>();
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
	D3DXMatrixScaling(&scale, m_ModelScale.x, m_ModelScale.y, m_ModelScale.z);
	//D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);//モデルによるが、後ろ向いてたら+ D3DX_PIで180度回転させる
	D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);
	D3DXMatrixTranslation(&trans, m_WorldPosition.x, m_WorldPosition.y, m_WorldPosition.z);
	matrix = scale * rot * trans;
	m_Matrix = matrix;

	Renderer::SetWorldMatrix(&matrix);
	
	m_Model->Update(m_AnimationIndex, m_Time, m_NextAnimationIndex, m_Time, m_BlendRate);


	if (m_BlendRate > 1.0f) m_BlendRate = 1.0f;
	m_Model->Draw();


}

void Player::UpdateTitle()
{

	m_AnimationIndex = PlayerAnimation::Player_Idle;

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

	m_MoveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//サードパーソンビュー
	if (Input::GetKeyPress('A'))
	{
		UpdateAnimation(PlayerAnimation::Player_LeftRun);

		m_MoveVec -= cameraRight;

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
		UpdateAnimation(PlayerAnimation::Player_RightRun);
		
		m_MoveVec += cameraRight;
		

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
		UpdateAnimation(PlayerAnimation::Player_Run);

		m_MoveVec += cameraForward;
		//m_WorldPosition += cameraRight * 0.1f;

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
		UpdateAnimation(PlayerAnimation::Player_BackRun);

		m_MoveVec -= cameraForward;

		D3DXQUATERNION quat;
		D3DXVECTOR3 axis = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		float angle = atan2f(cameraForward.x, cameraForward.z);
		D3DXQuaternionRotationAxis(&quat, &axis, angle);//(左方向に90度)
		//m_Quaternion = quat;
		D3DXQuaternionSlerp(&m_Quaternion, &m_Quaternion, &quat, 0.1f);
		move = true;
		if (m_IsConnectNetWork) m_InputData = 'S';
	}

	D3DXVec3Normalize(&m_MoveVec, &m_MoveVec);
	m_WorldPosition += m_MoveVec * 0.1f;



	if (Input::GetKeyPress('Q'))
	{
		m_Rotation.y -= 0.1f;
	}
	if (Input::GetKeyPress('E'))
	{
		m_Rotation.y += 0.1f;
	}

	//装備品を使う
	if (Input::GetKeyTrigger('I'))
	{
		UseEquipment();
	}

	//ベッド
	auto bed = scene->GetGameObject<Bed>();
	if (bed != nullptr)
	{
		D3DXVECTOR3 position = bed->GetPosition();
		D3DXVECTOR3 scale = bed->GetScale();

		if (position.x - (scale.x * 2.0f) - (scale.x / 2) < m_WorldPosition.x &&
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
			else m_Description->SetText("L：ベッドで眠る");

			if (Input::GetKeyTrigger('L'))
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
				m_WorldPosition.x = m_OldPosition.x;
				m_WorldPosition.z = m_OldPosition.z;
			}

		}
	}

	//NPC

	std::vector<NPC*> NPCs = scene->GetGameObjects<NPC>();
	for (NPC* npc : NPCs)
	{
		if (npc->GetIsHitPlayer())
		{
			m_Description->SetText("L：話す");
			if (Input::GetKeyTrigger('L'))
			{
				m_Conversation = scene->AddGameObject<Conversation>(LAYER_OBJECT_2D);
				m_Message = npc->GetConversation();
				m_Conversation->SetText(m_Message);
				m_PlayerState = PLAYER_STATE_CONVERSATION;
			}
		}
	}

	auto farmField = scene->GetGameObject<FarmField>();
	if (farmField != nullptr)
	{
		auto farmTile = farmField->GetFarmTileClosestToPlayer(FarmTileState::PLANTED, FarmTileState::PLANTED_WATERED);
		if (farmTile)
		{
			if (farmTile->GetCropState() == CropState::Harvest)
			{
				m_Description->SetText("L：収穫する");
				if (Input::GetKeyTrigger('L'))
				{
					farmTile->Harvest();
				}
			}
		}
	}

	auto house = scene->GetGameObject<House>();
	auto fade = scene->GetGameObject<Fade>();
	if (house != nullptr)
	{
		D3DXVECTOR3 position = house->GetPosition();
		D3DXVECTOR3 scale = house->GetScale();

		if (position.x - (scale.x * 6.0f) - (scale.x / 2) < m_WorldPosition.x &&
			m_WorldPosition.x < position.x + (scale.x * 6.0f) + (scale.x / 2) &&
			position.z - (scale.z * 6.0f) - (scale.z / 2) < m_WorldPosition.z &&
			m_WorldPosition.z < position.z + (scale.z * 6.0f) + (scale.z / 2))
		{
			m_Description->SetText("L：家に入る");
			if (Input::GetKeyPress('L'))
			{
				fade->SetIsFadeOut();

			}

		}
	}
	if (fade->GetFadeOutFinish())
	{
		Manager::SetIsLoad(true);
		Manager::SetScene<TestHouse>();//エンターキーを押したらゲームシーンに移行	
	}

	//インベントリを開く
	if (Input::GetKeyTrigger(VK_TAB))
	{
		m_InventoryInterface->Show();
		m_PlayerState = PLAYER_STATE_INVENTORY;
	}

	//ジャンプ
	if (Input::GetKeyTrigger(VK_SPACE) && m_Velocity.y == 0.0f)
	{
		m_Velocity.y = 0.35f;
		m_PlayerState = PLAYER_STATE_JUMP;
		move = true;

		UpdateAnimation(PlayerAnimation::Player_InPlaceJump);		
	}

	if (Input::GetKeyTrigger('C'))
	{
		camera->Shake(1.0f);
	}



	if (move == false)
	{
		UpdateAnimation(PlayerAnimation::Player_Idle);
	}
}

void Player::UpdateJump()
{
	if (m_IsGround == true)
	{
		m_PlayerState = PLAYER_STATE_GROUND;

	}
	m_WorldPosition += m_MoveVec * 0.1f;
}

void Player::UpdatePlow()
{
	UpdateAnimation(PlayerAnimation::Player_Plowing);
	m_AttackDelaynum++;

	if (m_AttackDelaynum > 16)
	{
		m_PlayerState = PLAYER_STATE_GROUND;
		m_AttackDelaynum = 0;
	}
}

void Player::UpdateAttack()
{
	UpdateAnimation(PlayerAnimation::Player_Attack);
	m_AttackDelaynum++;

	if (m_AttackDelaynum > 17)
	{
		m_PlayerState = PLAYER_STATE_GROUND;
		m_AttackDelaynum = 0;
	}
}

void Player::UpdateConversation()
{
	if (Input::GetKeyTrigger('L'))
	{
		m_Conversation->SetDestroy();
		m_PlayerState = PLAYER_STATE_GROUND;
	}
}

void Player::UpdateInventory()
{
	if (Input::GetKeyTrigger(VK_TAB))
	{
		m_InventoryInterface->Hide();
		m_PlayerState = PLAYER_STATE_GROUND;
	}
}

void Player::SetDescriptionText(std::string text)
{
		m_Description->SetText(text);
}


void Player::UpdateAnimation(int playerAnimation)
{
	if (m_NextAnimationIndex != playerAnimation)
	{
		m_AnimationIndex = m_NextAnimationIndex;
		m_NextAnimationIndex = playerAnimation;
		m_BlendRate = 0.0f;
	}
}

void Player::AddHp(int hp)
{
	m_Hp += hp;
	if (m_Hp > m_HpMax) m_Hp = m_HpMax;
	if (m_Hp < 0) m_Hp = 0;
}

void Player::LoadPlayerData(PlayerData playerData)
{
	m_WorldPosition = D3DXVECTOR3(playerData.positionx, playerData.positiony, playerData.positionz);
}

void Player::GetDebugData()
{
	ImGui::Begin("Player");
	ImGui::Text("Position:%.2f,%.2f,%.2f", m_WorldPosition.x, m_WorldPosition.y, m_WorldPosition.z);
	ImGui::End();
}

void Player::UseEquipment()
{
	if(m_EquipmentInterface == nullptr) return;

	if (m_EquipmentInterface->GetEquipment()) {
		m_EquipmentInterface->ExecuteEquipment();
	}
}

void Player::EatItem(std::string key)
{
	auto itemPtr = m_InventoryInterface->GetItem(key);
	int healing = itemPtr->GetHealing();
	AddHp(healing);
	m_InventoryInterface->DecreaseItem(itemPtr);
}


void Player::SetEquipment(std::string key)
{
	auto equipment = m_EquipmentFactory->CreateEquipment(key);
	m_EquipmentInterface->SetEquipment(equipment);
}

void Player::SetInventoryItem(std::string key)
{
	auto item = m_ItemFactory->CreateItem(key);
	m_InventoryInterface->AddItem(item);
}

