#pragma once

#include "gameObject.h"
#include <string>
class InventoryItemDescription : public GameObject
{
private:
	GameObject* m_ItemText[3];//テキストの数のオブジェクト生成

	class Text* m_ItemNameText;
	class Text* m_ItemTypeText;
	class Text* m_ItemDescriptionText;

	class Inventory* m_Inventory;
	class InventoryItemCursor* m_InventoryItemCursor;

	int m_Index{};

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetText(Text* textptr, const std::string& text);
};
