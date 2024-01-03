
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "sphere.h"
#include "model.h"
#include "shader.h"
#include "input.h"


void Sphere::Init()
{
	m_Model = new Model();
	m_Model->Load("asset\\model\\obj\\Sphere.obj");

	// 環境マッピング用テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/envmap4.dds",
		NULL,
		NULL,
		&m_TextureEnvCube,
		NULL);
	assert(m_TextureEnvCube);

	AddComponent<EnvMapping>();//shader
}


void Sphere::Uninit()
{

	m_Model->Unload();
	delete m_Model;

	m_TextureEnvCube->Release();


}


void Sphere::Update()
{
	if (Input::GetKeyPress('R'))
		m_Rotation.x -= 0.1f;
	if (Input::GetKeyPress('F'))
		m_Rotation.x += 0.1f;

	if (Input::GetKeyPress('Q'))
		m_Rotation.y -= 0.1f;
	if (Input::GetKeyPress('E'))
		m_Rotation.y += 0.1f;
}


void Sphere::Draw()
{


	// マトリクス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_WorldPosition.x, m_WorldPosition.y, m_WorldPosition.z);
	world = scale * rot * trans;

	Renderer::SetWorldMatrix(&world);

	// テクスチャ設定
	//Renderer::GetDeviceContext()->PSSetShaderResources(2, 1, &m_TextureEnvCube);
	m_Model->Draw();

}	