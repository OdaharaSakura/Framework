#pragma once
#include "main.h"

class Image
{
private:
	int							m_WidthSplit = 1;	// 横分割数
	int							m_HeightSplit = 1;	// 縦分割数

	const char*						m_Path;
	ID3D11ShaderResourceView* m_Texture = NULL;		// テクスチャ


public:
	Image(const char* Path);
	~Image();

	void Load();
	void Unload();

	const char* GetPath() { return m_Path; }

	ID3D11ShaderResourceView* GetShaderResourceView() { return m_Texture; }

	void SetWidthSplit(int WidthSplit) { m_WidthSplit = WidthSplit; }
	void SetHeightSplit(int HeightSplit) { m_HeightSplit = HeightSplit; }

	int GetWidthSplit() { return m_WidthSplit; }
	int GetHeightSplit() { return m_HeightSplit; }

};
