#pragma once

#include "gameObject.h"
#include "main.h"
#include "renderer.h"
#include "model.h"
#include "debugmanager.h"

class TestObj : public GameObject//�p��
{
private:

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};
	D3DXVECTOR3 m_worldPosition;

public:

	Model* m_Model{};
	D3DXMATRIX m_pMatrix;

	void Init() override
	{

		m_Model = new Model();
		m_Model->Load("asset\\model\\obj\\Kuwa.obj");


		Renderer::CreateVertexShader(&m_VertexShader,
			&m_VertexLayout, "shader\\vertexLightingVS.cso");
		Renderer::CreatePixelShader(&m_PixelShader,
			"shader\\vertexLightingPS.cso");

		//�L�������Ă���Ƃ�
		m_Rotation = D3DXVECTOR3(-3.14f / 4, 0.0f, -3.14f / 2);
		m_WorldPosition = D3DXVECTOR3(0.0f, 0.5f, 0.0f);
	}
	void Uninit() override {
		m_VertexLayout->Release();
		m_VertexShader->Release();
		m_PixelShader->Release();
	}
	void Update() override {

	}
	void Draw() override {
		// ���̓��C�A�E�g�ݒ�g�iDirectX�֒��_�̍\����������j
		Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
		// �g�p����V�F�[�_��ݒ�
		Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);//�o�[�e�b�N�X�V�F�[�_�[�I�u�W�F�N�g�̃Z�b�g
		Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);//�s�N�Z���V�F�[�_�[�I�u�W�F�N�g�̃Z�b�g

		// �}�g���N�X�ݒ�
		D3DXMATRIX world, scale, rot, trans;
		D3DXMatrixScaling(&scale, GetScale().x, GetScale().y, GetScale().z);
		D3DXMatrixRotationYawPitchRoll(&rot, GetRotation().y + m_Rotation.y, GetRotation().x + m_Rotation.x, GetRotation().z + m_Rotation.z);
		D3DXMatrixTranslation(&trans, GetPosition().x + m_WorldPosition.x, GetPosition().y + m_WorldPosition.y, GetPosition().z + m_WorldPosition.z);
		world = scale * rot * trans * m_pMatrix * GetParent()->GetMatrix();

		//D3DXVec3TransformCoord(&m_WorldPosition, &m_WorldPosition, &world);//���[���h���W

		Renderer::SetWorldMatrix(&world);

		//#ifdef _DEBUG
		m_Model->Draw();

		//#endif
	}
};
