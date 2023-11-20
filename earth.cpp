
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "earth.h"

Model* Earth::m_Model{};

void Earth::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\box.obj");
}

void Earth::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void Earth::Init()
{
	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout, "shader\\vertexLightingVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader,
		"shader\\vertexLightingPS.cso");
}

void Earth::Uninit()
{



	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}

void Earth::Update()
{
	//�o��


	if (m_Position.y >= m_Scale.y / 2)
	{
		m_CountUpNum++;
		m_Position.y = m_Scale.y / 2;
	}
	else 	m_Position.y += 0.1f;

	//
	if (m_CountUpNum != 0)
	{
		if (m_CountUpNum >= 180) SetDestroy();
	}
}

void Earth::Draw()
{


	// ���̓��C�A�E�g�ݒ�g�iDirectX�֒��_�̍\����������j
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	// �g�p����V�F�[�_��ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);//�o�[�e�b�N�X�V�F�[�_�[�I�u�W�F�N�g�̃Z�b�g
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);//�s�N�Z���V�F�[�_�[�I�u�W�F�N�g�̃Z�b�g

	// �}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;

	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();
}
