#include "main.h"
#include "renderer.h"
#include "countdown.h"
#include "sprite.h"
#include "scene.h"
#include "manager.h"
#include "result.h"


void CountDown::Init()
{
	VERTEX_3D vertex[4];


	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;//D3D11_USAGE_DYNAMIC�ɂ���Ə�����������//�e�N�X�`���A�j���[�V�������ł���
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;//0����D3D11_CPU_ACCESS_WRITE�ɂ���Ə�����������//�e�N�X�`���A�j���[�V�������ł���

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);


	// �e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/num.png",
		NULL,
		NULL,
		&m_Texture,
		NULL);
	assert(m_Texture);

	Renderer::CreateVertexShader(&m_VertexShader,
		&m_VertexLayout, "Shader\\unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader,
		"Shader\\unlitTexturePS.cso");
	//Sprite* sprite = AddComponent<Sprite>();
	//sprite->Init(0.0f, 0.0f, 200.0f, 200.0f, "asset/texture/field004.jpg");

	//AddComponent<Sprite>()->Init(0.0f, 0.0f, 200.0f, 200.0f, "asset/texture/num.png");//��̂Ƃǂ����ł��悢
	//AddComponent<Sprite>()->Init(300.0f, 300.0f, 200.0f, 200.0f, "asset/texture/kizuna.jpg");



}

void CountDown::Uninit()
{
	m_VertexBuffer->Release();
	m_Texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Uninit();
}

void CountDown::Update()
{
	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Update();
	m_Frame++;
	if (m_Frame >=60)
	{
		m_Count--;
		m_Frame = 0;
	}



	if(m_Count <= 0) Manager::SetScene<Result>();
}

void CountDown::Draw()
{
	// ���̓��C�A�E�g�ݒ�
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	// �V�F�[�_�ݒ�
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);



	// �}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	// ���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	// �}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.TextureEnable = true;
	Renderer::SetMaterial(material);

	// �e�N�X�`���ݒ�
	Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	// �v���~�e�B�u�g�|���W�ݒ�
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	int count = m_Count;

	for (int i = 0; i < m_Digit; i++)
	{
		//���_���W�Z�o
		float vx = 100.0f - i * 30.0f;
		float vy = 30.0f;
		float w = 50.0f;
		float h = 50.0f;

		//�e�N�X�`�����W�Z�o
		int number = count % 10;
		count /= 10;
		float x = number % width * (1.0f / width);
		float y = number / width * (1.0f / height);

		//���_�f�[�^��������
		D3D11_MAPPED_SUBRESOURCE msr;
		Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
			D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		//����
		vertex[0].Position = D3DXVECTOR3(vx, vy, 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = D3DXVECTOR2(x, y);
		//�E��
		vertex[1].Position = D3DXVECTOR3(vx + w, vy, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(x + (1.0f / width), y);
		//����O
		vertex[2].Position = D3DXVECTOR3(vx, vy + h, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = D3DXVECTOR2(x, y + (1.0f / height));
		//�E��O
		vertex[3].Position = D3DXVECTOR3(vx + w, vy + h, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(x + (1.0f / width), y + (1.0f / height));

		Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);



		// �|���S���`��
		Renderer::GetDeviceContext()->Draw(4, 0);
	}


}