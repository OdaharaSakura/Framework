
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "input.h"
#include "player.h"
#include "scene.h"


void Camera::Init()
{

	m_Position = D3DXVECTOR3(0.0f, 5.0f, -10.0f);


}



//memo:���b�N�I���@�\���
void Camera::Update()
{
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();

	////�g�b�v�r���[//�}���I3D���[���h�Ƃ�
	//m_Target = player->GetPosition();
	//m_Position = m_Target + D3DXVECTOR3(0.0f, 10.0f, -10.0f);


	////�t�@�[�X�g�p�[�\���r���[�i���@�������g
	//m_Position = player->GetPosition() + D3DXVECTOR3(0.0f, 1.5f, 0.0f);
	//m_Target = m_Position + player->GetForward();

	//�T�[�h�p�[�\���r���[�i�t�H�[�g�i�C�g�Ƃ��j
	m_Target = player->GetPosition() + player->GetRight() * 0.5f + D3DXVECTOR3(0.0f, 3.0f, 0.0f);//�����������ɂ����
	m_Position = m_Target - player->GetForward() * 6.0f + D3DXVECTOR3(0.0f, 2.0f, 0.0f);
}


void Camera::Draw()
{

	//�r���[�}�g���N�X�ݒ�
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_ViewMatrix, &m_Position, &m_Target, &up);

	Renderer::SetViewMatrix(&m_ViewMatrix);


	//�v���W�F�N�V�����}�g���N�X�ݒ�
	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&projectionMatrix);

}
