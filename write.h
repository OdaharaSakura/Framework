#pragma once

#include "gameObject.h"
#include <string>
class Write : public GameObject
{
private:

	ID3D11VertexShader* m_VertexShader{};
	ID3D11PixelShader* m_PixelShader{};
	ID3D11InputLayout* m_VertexLayout{};

	class DirectWrite* write;
	std::string testtext;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	const char GetText() { return (const char)testtext.c_str(); }
	void SetText(std::string c) { testtext = c; }
};
