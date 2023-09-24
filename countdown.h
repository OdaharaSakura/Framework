#pragma once

#include "gameObject.h"
class CountDown : public GameObject
{
private:
	ID3D11Buffer* m_VertexBuffer = nullptr;
	ID3D11ShaderResourceView* m_Texture{};

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	int m_Count = 20;
	int m_Digit = 2;//ÉXÉRÉAÇÃåÖêî
	int width = 5;
	int height = 5;
	int m_Frame{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void AddCount(int Count) { m_Count += Count; }
};
