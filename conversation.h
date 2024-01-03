#pragma once

#include "gameObject.h"
#include <string>
class Conversation : public GameObject
{
private:
	class Text* m_Text = nullptr;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetText(const std::string& text);
};
