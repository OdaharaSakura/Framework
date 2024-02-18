
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



//memo:���b�N�I���@�\���
void Camera::Update()
{
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();

	////�g�b�v�r���[//�}���I3D���[���h�Ƃ�
	//m_Target = player->GetPosition();
	//m_WorldPosition = m_Target + D3DXVECTOR3(0.0f, 10.0f, -10.0f);


	////�t�@�[�X�g�p�[�\���r���[�i���@�������g
	//m_WorldPosition = player->GetPosition() + D3DXVECTOR3(0.0f, 1.5f, 0.0f);
	//m_Target = m_WorldPosition + player->GetForward();

	////�T�[�h�p�[�\���r���[�i�t�H�[�g�i�C�g�Ƃ��j
	//m_Target = player->GetPosition() + player->GetRight() * 0.5f + D3DXVECTOR3(0.0f, 3.0f, 0.0f);//�����������ɂ����
	//m_WorldPosition = m_Target - player->GetForward() * 6.0f + D3DXVECTOR3(0.0f, 2.0f, 0.0f);

	if (Input::GetKeyPress('U'))
	{
		m_Rotation += 0.1f;

	}
	if (Input::GetKeyPress('O'))
	{
		m_Rotation -= 0.1f;

	}
	
	//�g�b�v�r���[
	m_Target = player->GetPosition() + player->GetRight() * 0.5f + D3DXVECTOR3(0.0f, 1.0f, 0.0f);;
	m_WorldPosition = m_Target + D3DXVECTOR3(sinf(m_Rotation) * 4.0f, 1.0f, -cosf(m_Rotation) * 4.0f);

	//�J�����V�F�C�N
	m_ShakeOffset = sinf(m_ShakeTime * 1.5f) * m_ShakeAmplitude;
	m_ShakeTime++;
	m_ShakeAmplitude *= 0.9f;
}


void Camera::Draw()
{
	//�r���[�}�g���N�X�ݒ�
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);

	D3DXVECTOR3 position = m_WorldPosition + D3DXVECTOR3(0.0f, m_ShakeOffset, 0.0f);
	D3DXVECTOR3 target = m_Target + D3DXVECTOR3(0.0f, m_ShakeOffset, 0.0f);
	D3DXMatrixLookAtLH(&m_ViewMatrix, &position, &target, &up);

	Renderer::SetViewMatrix(&m_ViewMatrix);


	//�v���W�F�N�V�����}�g���N�X�ݒ�
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

	//���A���A�E�A��̏��Ŕ���
	for (int i = 0; i < 4; i++)
	{
		v1 = wpos[i] - m_WorldPosition;
		v2 = wpos[(i + 1) % 4] - m_WorldPosition;

		// �O�όv�Z
		D3DXVec3Cross(&n, &v1, &v2);
		D3DXVec3Normalize(&n, &n);

		if (D3DXVec3Dot(&n, &v) < -3.0f)
		{
			return false;
		}
	}
	
	return true;
}

bool Camera::CheckViewWithBoundingSphere(D3DXVECTOR3 position, float radius) 
{
	D3DXMATRIX vp, invvp;
	vp = m_ViewMatrix * m_ProjectionMatrix;
	D3DXMatrixInverse(&invvp, NULL, &vp);

	D3DXVECTOR3 vpos[8];
	D3DXVECTOR3 wpos[8];

	// �r���[�{�����[���̃R�[�i�[���`
	vpos[0] = D3DXVECTOR3(-1.0f, 1.0f, 0.0f); // �ߕ��ʂ̃R�[�i�[
	vpos[1] = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	vpos[2] = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
	vpos[3] = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	vpos[4] = D3DXVECTOR3(-1.0f, 1.0f, 1.0f); // �����ʂ̃R�[�i�[
	vpos[5] = D3DXVECTOR3(-1.0f, -1.0f, 1.0f);
	vpos[6] = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
	vpos[7] = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	// ���[���h��Ԃւ̕ϊ�
	for (int i = 0; i < 8; i++) {
		D3DXVec3TransformCoord(&wpos[i], &vpos[i], &invvp);
	}

	D3DXVECTOR3 v, v1, v2, n;

	v = position - m_WorldPosition;

	//�@���v�Z
	for (int i = 0; i < 4; i++) {
		v1 = wpos[i] - position;
		v2 = wpos[(i + 1) % 4] - position;

		// �O�όv�Z
		D3DXVec3Cross(&n, &v1, &v2);
		D3DXVec3Normalize(&n, &n);

		// �I�u�W�F�N�g�̒��S�ƃo�E���f�B���O�X�t�B�A���l��
		if (D3DXVec3Dot(&n, &v) < -radius) {
			return false;
		}
	}

	return true;
}
