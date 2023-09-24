#pragma once

#include "scene.h"

class Sprite;//‘O•ûéŒ¾

class Title : public Scene
{
private:
	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	class Fade* m_Fade{};
	class Audio* m_ShotSE1{};
	class TitleEnter* m_TitleEnter{};
	class TitleSelect* m_TitleSelect{};
	class TitleCursor* m_TitleCursor{};


	int m_Phase = 0;




public:
	void Init() override;
	void Uninit() override;
	void Update() override;
};
