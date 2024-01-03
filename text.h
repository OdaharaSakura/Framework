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
	void Init();
	void Uninit();
	void Update();
	void Draw();

	std::string GetText() { return m_String; }
	void SetText(std::string c);
	void SetPosition(D3DXVECTOR2 position);
	void SetFontWeight(DWRITE_FONT_WEIGHT fontWeight);
	void SetFontColor(D2D1::ColorF color);
	void SetFontNameIndex(int fontNameIndex);
	void SetFontSize(int size);
};
