//#include "main.h"
//#include "renderer.h"
//#include "rock.h"
//#include "manager.h"
//#include "player.h"
//#include "scene.h"
//#include "gauge.h"
//#include "earth.h"
//
//
//Model* Rock::m_Model{};
//
//void Rock::Load()
//{
//
//	m_Model->Load("asset\\model\\Mutant.fbx");
//
//}
//
//void Rock::Unload()
//{
//	m_Model->Unload();
//	delete m_Model;
//}
//
//void Rock::Init()
//{
//	Scene* scene = Manager::GetScene();
//
//	Renderer::CreateVertexShader(&m_VertexShader,
//		&m_VertexLayout, "Shader\\vertexLightingVS.cso");
//	Renderer::CreatePixelShader(&m_PixelShader,
//		"Shader\\vertexLightingPS.cso");
//
//	m_ModelScale = D3DXVECTOR3(0.015f, 0.015f, 0.015f);
//
//	Gauge* gauge = scene->AddGameObject<Gauge>(1);
//	gauge->SetPosition(D3DXVECTOR3(m_Position.x, 3.0f, m_Position.z));
//	gauge->SetEnemyParent(this);
//
//	m_Startflg = true;
//
//	m_AttackDelaynum = 0;
//	m_IsAttackflg = false;
//	m_Attackflg = false;
//	m_Hp = m_HpMax;
//
//	m_Hp = m_HpMax;
//}
//
//void Rock::Uninit()
//{
//	GameObject::Uninit();
//
//	m_VertexLayout->Release();
//	m_VertexShader->Release();
//	m_PixelShader->Release();
//}
//
//void Rock::Update()
//{
//	GameObject::Update();
//
//	if (m_Startflg)
//	{
//		m_StartPosition = m_Position;
//		m_StartScale = m_Scale;
//		m_Startflg = false;
//	}
//
//	if (m_AnimeFrame >= 17 || m_AnimeFrame == 0)
//	{
//		m_AnimeState = RUN;
//		m_AnimeFrame = 0;
//	}
//
//	D3DXVECTOR3 oldPosition = m_Position;
//	Scene* scene = Manager::GetScene();
//	Player* player = scene->GetGameObject<Player>();
//
//	D3DXVECTOR3 position = player->GetPosition();
//
//	if (m_Hp == 0)
//	{
//
//		Enemy* enemy;
//		enemy = scene->AddGameObject<Enemy>(1);
//		enemy->SetGameObject(m_StartPosition, D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_StartScale);
//
//		SetDestroy();
//	}
//
//
//	if (player->GetAttackflg())
//	{
//		m_Hp -= 50;
//		player->SetnonAttackflg();
//	}
//
//
//
//	//移動処理（プレイヤーに向かってくる）
//	D3DXVec3Lerp(&m_Position, &m_Position, &position, test);
//
//	//土
//	std::vector<Earth*> Earths = scene->GetGameObjects<Earth>();
//	for (Earth* Earth : Earths)
//	{
//		D3DXVECTOR3 position = Earth->GetPosition();
//		D3DXVECTOR3 scale = Earth->GetScale();
//
//
//
//		if (position.x - scale.x - 0.5f < m_Position.x + m_Scale.x &&
//			m_Position.x - m_Scale.x < position.x + scale.x + 0.5f &&
//			position.z - scale.z - 0.5f < m_Position.z + m_Scale.z &&
//			m_Position.z - m_Scale.z < position.z + scale.z + 0.5f)
//		{
//
//			if (m_Position.y < position.y + scale.y * 2.0f - 0.5f)//2.0fはモデルの大きさ高さ1じゃなくて2だとこうなる
//			{
//				m_Position.x = oldPosition.x;
//				m_Position.z = oldPosition.z;
//			}
//
//			break;
//		}
//	}
//
//	//プレイヤー当たり判定
//	D3DXVECTOR3 playerposition = player->GetPosition();
//	D3DXVECTOR3 playerscale = player->GetScale();
//
//	D3DXVECTOR3 direction = m_Position - playerposition;
//	direction.y = 0.0f;
//	float length = D3DXVec3Length(&direction);
//	playerscale.y = 0.0f;
//	float scalexz = D3DXVec3Length(&playerscale) * 100.0f;//プレイヤーのスケールを100分の1にしているため
//	if (length < scalexz)
//	{
//		m_Position.x = oldPosition.x;
//		m_Position.z = oldPosition.z;
//	}
//	if (length < scalexz * scalexz + 3.0f)
//	{
//
//		//m_Hp -= 3;
//
//	}
//
//
//	//test += 0.01f;
//}
//
//void Enemy::Draw()
//{
//	GameObject::Draw();
//	Scene* scene = Manager::GetScene();
//	Player* player = scene->GetGameObject<Player>();
//
//	// 入力レイアウト設定ト（DirectXへ頂点の構造を教える）
//	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
//	// 使用するシェーダを設定
//	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);//バーテックスシェーダーオブジェクトのセット
//	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);//ピクセルシェーダーオブジェクトのセット
//
//	// マトリクス設定
//	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
//	D3DXVECTOR3 target = player->GetPosition();
//
//	D3DXMATRIX world, scale, rot, trans;
//	D3DXMatrixScaling(&scale, m_ModelScale.x, m_ModelScale.y, m_ModelScale.z);
//	//D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
//	CalcLookAtMatrixAxisFix(&rot, &m_Position, &target, &up);
//	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
//	world = scale * rot * trans;
//	Renderer::SetWorldMatrix(&world);
//
//	m_Model->Update("Run", m_Time, "Run", m_Time, m_BlendRate);
//
//
//	m_Time++;
//	m_Model->Draw();
//}
//
////キャラクターを向かせる関数
//D3DXMATRIX* Enemy::CalcLookAtMatrixAxisFix(D3DXMATRIX* pout, D3DXVECTOR3* pPos, D3DXVECTOR3* pLook, D3DXVECTOR3* pUp)
//{
//	D3DXVECTOR3 X, Y, Z, D;
//	D = *pLook - *pPos;
//	D3DXVec3Normalize(&D, &D);
//	D3DXVec3Cross(&X, D3DXVec3Normalize(&Y, pUp), &D);
//	D3DXVec3Normalize(&X, &X);
//	D3DXVec3Normalize(&Z, D3DXVec3Cross(&Z, &X, &Y));
//
//	pout->_11 = X.x; pout->_12 = X.y; pout->_13 = X.z; pout->_14 = 0;
//	pout->_21 = Y.x; pout->_22 = Y.y; pout->_23 = Y.z; pout->_24 = 0;
//	pout->_31 = Z.x; pout->_32 = Z.y; pout->_33 = Z.z; pout->_34 = 0;
//	pout->_41 = 0.0f; pout->_42 = 0.0f; pout->_43 = 0.0f; pout->_44 = 1.0f;
//
//	return pout;
//}
//
