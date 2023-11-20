#pragma once

#include "gameObject.h"
#include "main.h"
#include "renderer.h"
#include "model.h"

class TestObj : public GameObject//継承
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
		m_Model->Load("asset\\model\\Sphere.obj");


		Renderer::CreateVertexShader(&m_VertexShader,
			&m_VertexLayout, "shader\\vertexLightingVS.cso");
		Renderer::CreatePixelShader(&m_PixelShader,
			"shader\\vertexLightingPS.cso");
	}
	void Uninit() override {
		m_VertexLayout->Release();
		m_VertexShader->Release();
		m_PixelShader->Release();
	}
	void Update() override {

	}
	void Draw() override {
		// 入力レイアウト設定ト（DirectXへ頂点の構造を教える）
		Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
		// 使用するシェーダを設定
		Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);//バーテックスシェーダーオブジェクトのセット
		Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);//ピクセルシェーダーオブジェクトのセット

		// マトリクス設定
		D3DXMATRIX world, scale, rot, trans;
		D3DXMatrixScaling(&scale, GetScale().x, GetScale().y, GetScale().z);
		D3DXMatrixRotationYawPitchRoll(&rot, GetRotation().y, GetRotation().x, GetRotation().z);
		D3DXMatrixTranslation(&trans, GetPosition().x, GetPosition().y, GetPosition().z);
		world = scale * rot * trans * m_pMatrix * GetParent()->GetMatrix();

		D3DXVec3TransformCoord(&m_worldPosition, &m_Position, &world);//ワールド座標

		Renderer::SetWorldMatrix(&world);

		//#ifdef _DEBUG
		m_Model->Draw();

		//#endif
	}
};
