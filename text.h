#pragma once

#include "Component.h"
#include "DirectWriteCustomFont.h"
#include <string>

class Text : public Component
{
private:
	FontData m_Data{};
	DirectWriteCustomFont* m_Write{};

	std::string m_String{};
	D3DXVECTOR2 m_Position = D3DXVECTOR2(0.0f, 0.0f);
	int			m_FontSize = 60;

public:
	void Init(
		std::string text,
		D3DXVECTOR2 position,
		DWRITE_FONT_WEIGHT fontWeight,
		D2D1::ColorF color,
		int fontNameIndex);

	void Uninit();
	void Update();
	void Draw();

	std::string GetText() { return m_String; }
	void SetText(std::string c);
	void SetFontSize(int size);
	void SetPosition(D3DXVECTOR2 position);
};
