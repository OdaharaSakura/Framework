#pragma once

#include "component.h"
class Sprite : public Component
{
private:

	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11ShaderResourceView* m_Texture{};

	D3DXCOLOR m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 m_WorldPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_Scale = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	int m_Index = 0;

	bool m_IsSendToPixelShader = true;

public:
	void Init(float x, float y, float Width, float Height, const char* TextureName);
	void Uninit();
	void Update();
	void Draw();
	void SetColor(D3DXCOLOR Color) { m_Color = Color; }
	void SetPositionY(float y) { m_WorldPosition.y = y; }
	void SetTexture(const char* TextureName);
	void SetIsNotSendToPixelShader() { m_IsSendToPixelShader = false; }

	void SetIndex(int num) { m_Index = num; }
	ID3D11ShaderResourceView* GetTexture() { return m_Texture; }
};
