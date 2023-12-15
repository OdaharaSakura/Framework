#pragma once

#include "Component.h"
#include "DirectWriteCustomFont.h"
#include <string>

class Text : public Component
{
private:
	FontData m_Data;
	DirectWriteCustomFont* m_Write;

	std::string m_String{};
	D3DXVECTOR2 m_Position = D3DXVECTOR2(0.0f, 0.0f);
	int			m_FontSize = 60;

	//color, weightÇ‡ê›íËÇ≈Ç´ÇÈÇÊÇ§Ç…ïœÇ¶ÇÈ

public:
	void Init(std::string text, D3DXVECTOR2 position);
	void Uninit();
	void Update();
	void Draw();

	std::string GetText() { return m_String; }
	void SetText(std::string c);
	void SetFontSize(int size);
	void SetPosition(D3DXVECTOR2 position);
};
