#pragma once

#include "gameObject.h"
#include <string>

class Text;
class SceneDescription : public GameObject
{
private:
	Text* m_Description{};
	std::string m_DescriptionText{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetDescriptionText(std::string text);
	void SetDescriptionPosition(D3DXVECTOR2 position);
	void SetDescriptionTextSize(float size);
};
