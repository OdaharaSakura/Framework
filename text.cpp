#include "main.h"
#include "renderer.h"
#include "text.h"
#include "DirectWriteCustomFont.h"

void Text::Init(std::string text, D3DXVECTOR2 position)
{
	m_String = text;
	m_Position = position;

	// DirectWriteCustomFont�N���X�̐���
	m_Write = new DirectWriteCustomFont(&m_Data);

	// ������
	m_Write->Init(Renderer::GetSwapChain());

	// �t�H���g�f�[�^������
	m_Data.fontSize = m_FontSize;
	m_Data.fontWeight = DWRITE_FONT_WEIGHT_ULTRA_BLACK;
	m_Data.Color = D2D1::ColorF(D2D1::ColorF::DimGray);
	m_Data.font = m_Write->GetFontName(Font_MaruMinya);

	// �t�H���g���Z�b�g
	m_Write->SetFont(m_Data);
}

void Text::Uninit()
{
	Component::Uninit();
}

void Text::Update()
{
	//���N���X�̃��\�b�h�Ăяo��
	Component::Update();
}

void Text::Draw()
{
	//���N���X�̃��\�b�h�Ăяo��
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
	// �t�H���g���Z�b�g
	m_Write->SetFont(m_Data);
}

void Text::SetPosition(D3DXVECTOR2 position)
{
	m_Position = position;
}


