
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "resultcamera.h"
#include "input.h"
#include "player.h"
#include "scene.h"


void ResultCamera::Init()
{

	m_WorldPosition = D3DXVECTOR3(0.0f, 5.0f, -10.0f);


}



//memo:���b�N�I���@�\���
void ResultCamera::Update()
{
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();



	//�T�[�h�p�[�\���r���[�i�t�H�[�g�i�C�g�Ƃ��j
	m_Target = player->GetPosition() + offset;//�����������ɂ����
	m_WorldPosition = m_Target + player->GetForward() * 3.0f + D3DXVECTOR3(0.0f, 2.0f, 0.0f);
}


void ResultCamera::Draw()
{

	//�r���[�}�g���N�X�ݒ�
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&m_ViewMatrix, &m_WorldPosition, &m_Target, &up);

	Renderer::SetViewMatrix(&m_ViewMatrix);


	//�v���W�F�N�V�����}�g���N�X�ݒ�
	D3DXMATRIX projectionMatrix;
	D3DXMatrixPerspectiveFovLH(&projectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 1.0f, 1000.0f);

	Renderer::SetProjectionMatrix(&projectionMatrix);

}
