#pragma once

#include "scene.h"

class Sprite;//‘O•ûéŒ¾

class GameOver : public Scene
{
private:
	class Fade* m_Fade = nullptr;

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

public:
	void Init() override;
	void Uninit() override;
	void Update() override;
};
