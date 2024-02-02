#pragma once

#include "gameObject.h"
#include <string>
class InventoryItemDescription : public GameObject
{
private:
	GameObject* m_ItemText[3];//�e�L�X�g�̐��̃I�u�W�F�N�g����

	class Text* m_ItemNametext;
	class Text* m_ItemTypeText;
	class Text* m_ItemDescriptionText;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetText(Text* textptr, const std::string& text);
};
