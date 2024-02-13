#pragma once
#include "component.h"

//静的画像表示コンポーネント
class StaticSprite : public Component
{
private:
	class Image* m_Image = nullptr;
	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11ShaderResourceView* m_Texture{};

	D3DXCOLOR m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR2 m_WorldPosition = D3DXVECTOR2(0.0f, 0.0f);
	D3DXVECTOR2 m_Scale = D3DXVECTOR2(0.0f, 0.0f);

	int m_Index = 0;

	bool m_IsSendToPixelShader = true;

	bool m_IsActive = true;

public:
	void Init();
	void Init(float x, float y, float Width, float Height, std::string TextureKey, std::string TexturePath);
	void Uninit();
	void Update();
	void Draw();
	void SetColor(D3DXCOLOR Color) { m_Color = Color; }
	void SetPosition(D3DXVECTOR2 position) { m_WorldPosition = position; }
	void SetScale(D3DXVECTOR2 scale) { m_Scale = scale; }
	void SetIsNotSendToPixelShader() { m_IsSendToPixelShader = false; }
	void SetIndex(int num) { m_Index = num; }
	void SetTexture(std::string TextureKey, std::string TexturePath);

	ID3D11ShaderResourceView* GetTexture() { return m_Texture; }
};
