//#include "main.h"
//#include "renderer.h"
//#include "manager.h"
//#include "scene.h"
//#include "grass.h"
//
//Model* Grass::m_Model{};
//
//void Grass::Load()
//{
//	m_Model = new Model();
//	m_Model->Load("asset\\model\\tree1.obj");
//}
//
//void Grass::Unload()
//{
//	m_Model->Unload();
//	delete m_Model;
//}
//
//void Grass::Init()
//{
//
//	Renderer::CreateVertexShader(&m_VertexShader,
//		&m_VertexLayout, "shader\\vertexLightingVS.cso");
//	Renderer::CreatePixelShader(&m_PixelShader,
//		"shader\\vertexLightingPS.cso");
//}
//
//void Grass::Uninit()
//{
//
//	m_VertexLayout->Release();
//	m_VertexShader->Release();
//	m_PixelShader->Release();
//}
//
//void Grass::Update()
//{
//
//}
//
//void Grass::Draw()
//{
//
//
//	// ���̓��C�A�E�g�ݒ�g�iDirectX�֒��_�̍\����������j
//	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
//	// �g�p����V�F�[�_��ݒ�
//	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);//�o�[�e�b�N�X�V�F�[�_�[�I�u�W�F�N�g�̃Z�b�g
//	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);//�s�N�Z���V�F�[�_�[�I�u�W�F�N�g�̃Z�b�g
//
//
//	// �}�g���N�X�ݒ�
//	D3DXMATRIX world, scale, rot, trans;
//	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
//	//D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
//	D3DXMatrixTranslation(&trans, m_WorldPosition.x, m_WorldPosition.y, m_WorldPosition.z);
//	world = scale * invView * trans;
//	Renderer::SetWorldMatrix(&world);
//
//	// ���_�o�b�t�@�ݒ�
//	UINT stride = sizeof(VERTEX_3D);
//	UINT offset = 0;
//	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
//
//	// �}�e���A���ݒ�
//	MATERIAL material;
//	ZeroMemory(&material, sizeof(material));
//	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
//	material.TextureEnable = true;
//	Renderer::SetMaterial(material);
//
//	// �e�N�X�`���ݒ�
//	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);
//
//	// �v���~�e�B�u�g�|���W�ݒ�
//	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
//
//	Renderer::SetATCEnable(true);
//
//	// �|���S���`��
//	Renderer::GetDeviceContext()->Draw(4, 0);
//
//	Renderer::GetDeviceContext()->DrawInstanced(4, 100, 0, 0);//�W�I���g���C���X�^���V���O�i���_��, ��, �j
//
//
//	Renderer::SetATCEnable(false);
//}
