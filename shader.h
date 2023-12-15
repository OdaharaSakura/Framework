#pragma once

#include "component.h"

class VertexLighting : public Component
{
private:

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

public:
	void Init()
	{
		Renderer::CreateVertexShader(&m_VertexShader,
			&m_VertexLayout, "shader\\vertexLightingVS.cso");
		Renderer::CreatePixelShader(&m_PixelShader,
			"shader\\vertexLightingPS.cso");
	}

	void Uninit()
	{
		if (m_VertexLayout != nullptr)m_VertexLayout->Release();
		if (m_VertexShader != nullptr)m_VertexShader->Release();
		if (m_PixelShader != nullptr)m_PixelShader->Release();
	}

	void Draw()
	{
		// ���̓��C�A�E�g�ݒ�g�iDirectX�֒��_�̍\����������j
		Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
		// �g�p����V�F�[�_��ݒ�
		Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);//�o�[�e�b�N�X�V�F�[�_�[�I�u�W�F�N�g�̃Z�b�g
		Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);//�s�N�Z���V�F�[�_�[�I�u�W�F�N�g�̃Z�b�g
	}
};

class UnlitTexture : public Component
{
private:

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

public:
	void Init()
	{
		Renderer::CreateVertexShader(&m_VertexShader,
			&m_VertexLayout, "shader\\unlitTextureVS.cso");
		Renderer::CreatePixelShader(&m_PixelShader,
			"shader\\unlitTexturePS.cso");
	}
	void Uninit()
	{
		if(m_VertexLayout != nullptr)m_VertexLayout->Release();
		if (m_VertexShader != nullptr)m_VertexShader->Release();
		if (m_PixelShader != nullptr)m_PixelShader->Release();
	}

	void Draw()
	{
		// ���̓��C�A�E�g�ݒ�g�iDirectX�֒��_�̍\����������j
		Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
		// �g�p����V�F�[�_��ݒ�
		Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);//�o�[�e�b�N�X�V�F�[�_�[�I�u�W�F�N�g�̃Z�b�g
		Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);//�s�N�Z���V�F�[�_�[�I�u�W�F�N�g�̃Z�b�g
	}
};

class PercentageCloserFiltering : public Component
{
private:

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

public:
	void Init()
	{
		Renderer::CreateVertexShader(&m_VertexShader,
			&m_VertexLayout, "shader\\PercentageCloserFilteringVS.cso");
		Renderer::CreatePixelShader(&m_PixelShader,
			"shader\\PercentageCloserFilteringPS.cso");

		m_AttachObject->SetDepthShadow();
	}
	void Uninit()
	{
		if (m_VertexLayout != nullptr)m_VertexLayout->Release();
		if (m_VertexShader != nullptr)m_VertexShader->Release();
		if (m_PixelShader != nullptr)m_PixelShader->Release();
	}

	void Draw()
	{
		// ���̓��C�A�E�g�ݒ�g�iDirectX�֒��_�̍\����������j
		Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
		// �g�p����V�F�[�_��ݒ�
		Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);//�o�[�e�b�N�X�V�F�[�_�[�I�u�W�F�N�g�̃Z�b�g
		Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);//�s�N�Z���V�F�[�_�[�I�u�W�F�N�g�̃Z�b�g

			//�V���h�E�o�b�t�@�e�N�X�`�����P�ԂփZ�b�g
		ID3D11ShaderResourceView* depthShadowTexture =
			Renderer::GetDepthShadowTexture();
		Renderer::GetDeviceContext()->PSSetShaderResources(1, 1,
			&depthShadowTexture);
	}
};