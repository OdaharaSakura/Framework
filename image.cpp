#include "image.h"
#include "renderer.h"

Image::Image(const char* Path)
{
	m_Path = Path;
	Load();
}

Image::~Image()
{
	Unload();
}

void Image::Load()
{
	// テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		m_Path,
		NULL,
		NULL,
		&m_Texture,
		NULL);
	assert(m_Texture);
}

void Image::Unload()
{
	m_Texture->Release();
}

