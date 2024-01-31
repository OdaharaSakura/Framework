
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "input.h"
#include "player.h"
#include "scene.h"


void Camera::Init()
{

	m_WorldPosition = D3DXVECTOR3(0.0f, 5.0f, -10.0f);


}



//memo:ロックオン機能作る
void Camera::Update()
{
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();

	////トップビュー//マリオ3Dワールドとか
	//m_Target = player->GetPosition();
	//m_WorldPosition = m_Target + D3DXVECTOR3(0.0f, 10.0f, -10.0f);


	////ファーストパーソンビュー（ヴァロラント
	//m_WorldPosition = player->GetPosition() + D3DXVECTOR3(0.0f, 1.5f, 0.0f);
	//m_Target = m_WorldPosition + player->GetForward();

	////サードパーソンビュー（フォートナイトとか）
	//m_Target = player->GetPosition() + player->GetRight() * 0.5f + D3DXVECTOR3(0.0f, 3.0f, 0.0f);//少しだけ左にずれる
	//m_WorldPosition = m_Target - player->GetForward() * 6.0f + D3DXVECTOR3(0.0f, 2.0f, 0.0f);

	if (Input::GetKeyPress(VK_LEFT))
	{
		m_Rotation += 0.1f;

	}
	if (Input::GetKeyPress(VK_RIGHT))
	{
		m_Rotation -= 0.1f;

	}
	
	//トップビュー
	m_Target = player->GetPosition() + player->GetRight() * 0.5f + D3DXVECTOR3(0.0f, 2.0f, 0.0f);;
	m_WorldPosition = m_Target + D3DXVECTOR3(sinf(m_Rotation) * 5.0f, 2.0f, -cosf(m_Rotation)*6.0f);

	//カメラシェイク
	m_ShakeOffset = sinf(m_ShakeTime * 1.5f) * m_ShakeAmplitude;
	m_ShakeTime++;
	m_ShakeAmplitude *= 0.9f;
}


void Camera::Draw()
{
	//ビューマトリクス設定
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	D3DXVECTOR3 position = m_WorldPosition + D3DXVECTOR3(0.0f, m_ShakeOffset, 0.0f);
	D3DXVECTOR3 target = m_Target + D3DXVECTOR3(0.0f, m_ShakeOffset, 0.0f);
	D3DXMatrixLookAtLH(&m_ViewMatrix, &position, &target, &up);

	Renderer::SetViewMatrix(&m_ViewMatrix);


	//プロジェクションマトリクス設定
	D3DXMatrixPerspectiveFovLH(&m_ProjectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 3000.0f);

	Renderer::SetProjectionMatrix(&m_ProjectionMatrix);

}

bool Camera::CheckView(D3DXVECTOR3 Position)
{
	D3DXMATRIX vp,invvp;

	vp = m_ViewMatrix * m_ProjectionMatrix;
	D3DXMatrixInverse(&invvp, NULL, &vp);

	D3DXVECTOR3 vpos[4];
	D3DXVECTOR3 wpos[4];

	vpos[0] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f);
	vpos[1] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	vpos[2] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
	vpos[3] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	D3DXVec3TransformCoord(&wpos[0], &vpos[0], &invvp);
	D3DXVec3TransformCoord(&wpos[1], &vpos[1], &invvp);
	D3DXVec3TransformCoord(&wpos[2], &vpos[2], &invvp);
	D3DXVec3TransformCoord(&wpos[3], &vpos[3], &invvp);

	D3DXVECTOR3 v, v1, v2, n;

	v = Position - m_WorldPosition;

	//左、下、右、上の順で判定
	for (int i = 0; i < 4; i++)
	{
		v1 = wpos[i] - m_WorldPosition;
		v2 = wpos[(i + 1) % 4] - m_WorldPosition;

		// 外積計算
		D3DXVec3Cross(&n, &v1, &v2);
		D3DXVec3Normalize(&n, &n);

		if (D3DXVec3Dot(&n, &v) < -3.0f)
		{
			return false;
		}
	}
	
	return true;
}
