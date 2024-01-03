#include "main.h"
#include "renderer.h"
#include "text.h"
#include "DirectWriteCustomFont.h"

void Text::Init()
{
	m_String = 0.0f;
	m_Position = D3DXVECTOR2(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	// DirectWriteCustomFontクラスの生成
	m_Write = new DirectWriteCustomFont(&m_Data);

	// 初期化
	m_Write->Init(Renderer::GetSwapChain());

	// フォントデータを改変
	m_Data.fontSize = 40;
	m_Data.fontWeight = DWRITE_FONT_WEIGHT_LIGHT;
	m_Data.Color = D2D1::ColorF(D2D1::ColorF::White);
	m_Data.font = m_Write->GetFontName(Font_NicocaV2);

	// フォントをセット
	m_Write->SetFont(m_Data);
}

void Text::Uninit()
{
	Component::Uninit();
}

void Text::Update()
{
	//基底クラスのメソッド呼び出し
	Component::Update();
}

void Text::Draw()
{
	//基底クラスのメソッド呼び出し
	Component::Draw();
	m_Write->DrawString(m_String, m_Position, D2D1_DRAW_TEXT_OPTIONS_NONE);
}

void Text::SetText(std::string c)
{
	m_String = c; 
}

void Text::SetFontSize(int size)
{
	m_FontSize = size; 
	m_Data.fontSize = m_FontSize;
	// フォントをセット
	m_Write->SetFont(m_Data);
}

void Text::SetPosition(D3DXVECTOR2 position)
{
	m_Position = position;
}

void Text::SetFontWeight(DWRITE_FONT_WEIGHT fontWeight)
{
	m_Data.fontWeight = fontWeight;
	// フォントをセット
	m_Write->SetFont(m_Data);
}

void Text::SetFontColor(D2D1::ColorF color)
{
	m_Data.Color = color;
	// フォントをセット
	m_Write->SetFont(m_Data);
}

void Text::SetFontNameIndex(int fontNameIndex)
{
	m_Data.font = m_Write->GetFontName(fontNameIndex);
	// フォントをセット
	m_Write->SetFont(m_Data);
}


