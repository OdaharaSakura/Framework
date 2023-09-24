
#include "main.h"
#include "renderer.h"
#include "gauge.h"
#include "manager.h"
#include "scene.h"
#include "camera.h"
#include "player.h"
#include "enemy.h"
#include "treasureBox.h"
#include <iostream>
#include <cmath>

ID3D11Buffer* Gauge::m_VertexBuffer{};

void Gauge::Load()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(250.0f, 50.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(50.0f, 60.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(250.0f, 60.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);


	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;
	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);
}

void Gauge::Unload()
{
	//Release��NULL�`�F�b�N������
	if (m_VertexBuffer != NULL)
	{
		m_VertexBuffer->Release();
		m_VertexBuffer = NULL;
	}
}

void Gauge::Init()
{
	

	//�����ɃV�F�[�_�[�t�@�C���̃��[�h��ǉ�
	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "gaugeVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "gaugePS.cso");


}



void Gauge::Uninit()
{
	GameObject::Uninit();


	//m_Texture->Release();



	//�����ɃV�F�[�_�[�I�u�W�F�N�g�̉����ǉ�
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();
}




void Gauge::Update()
{
	GameObject::Update();
	if (m_Hp == m_HpMax)m_HpOld = m_HpMax;
	if (m_PlayerParent != NULL)
	{
		m_Hp = m_PlayerParent->GetHp();
		m_HpMax = m_PlayerParent->GetHpMax();
		m_Position = D3DXVECTOR3 (
			m_PlayerParent->GetPosition().x,
			m_PlayerParent->GetPosition().y + 3.0f,
			m_PlayerParent->GetPosition().z);//�ق�Ƃ̓}�g���b�N�X�Őڑ��������A�����߂�������
	}

	if (m_EnemyParent != NULL)
	{
		m_Hp = m_EnemyParent->GetHp();
		m_HpMax = m_EnemyParent->GetHpMax();
		m_Position = D3DXVECTOR3(
			m_EnemyParent->GetPosition().x,
			m_EnemyParent->GetPosition().y + m_EnemyParent->GetScale().y,
			m_EnemyParent->GetPosition().z
		);
	}

	if (m_BoxParent != NULL)
	{
		m_Hp = m_BoxParent->GetHp();
		m_HpMax = m_BoxParent->GetHpMax();
		m_Position = D3DXVECTOR3(
			m_BoxParent->GetPosition().x,
			m_BoxParent->GetPosition().y + m_BoxParent->GetScale().y,
			m_BoxParent->GetPosition().z
		);
	}

	if (m_HpOld > m_Hp)
	{
		m_HpOld -= 1;
		if (m_HpOld < m_Hp) m_HpOld = m_Hp;
	}
}


void Gauge::Draw()
{
	GameObject::Draw();
	//���_�f�[�^��������
	D3D11_MAPPED_SUBRESOURCE msr;
	Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
		D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	//����
	vertex[0].Position = D3DXVECTOR3(-1.0f, 0.15f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	//�E��
	vertex[1].Position = D3DXVECTOR3(1.0f, 0.15f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);
	//����O
	vertex[2].Position = D3DXVECTOR3(-1.0f, -0.15f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);
	//�E��O
	vertex[3].Position = D3DXVECTOR3(1.0f, -0.15f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);


	//�����ɃV�F�[�_�[�֘A�̕`�揀����ǉ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);



	// �}�g���N�X�ݒ�
	//CRenderer::SetWorldViewProjection2D();
	Scene* scene = Manager::GetScene();
	Camera* camera = scene->GetGameObject<Camera>();
	D3DXMATRIX view = camera->GetViewMatrix();

	//�r���[�̋t�s��
	D3DXMATRIX invView;
	D3DXMatrixInverse(&invView, NULL, &view);//�t�s��
	invView._41 = 0.0f;
	invView._42 = 0.0f;
	invView._43 = 0.0f;

	// �}�g���N�X�ݒ�
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	//D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * invView * trans;

	Renderer::SetWorldMatrix(&world);


	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	Renderer::SetMaterial(material);

	// �e�N�X�`���ݒ�
	//Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//HP�p�����[�^�ݒ�
	PARAMETER param;
	param.hitpoint.x = m_Hp;
	param.hitpoint.y = m_HpMax;
	param.hitpoint.z = m_HpOld;
	param.baseColor = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	param.lostColor = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
	param.diffColor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	Renderer::SetParameter(param);

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �|���S���`��
	Renderer::GetDeviceContext()->Draw(4, 0);

}
