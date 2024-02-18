#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "scene.h"
#include "shader.h"
#include "subPanelOptions.h"
#include "staticSprite.h"
#include "item.h"
#include "inventory.h"
#include "player.h"


void SubPanelOptions::Init()
{
	AddComponent<UnlitTexture>();

	m_Scale.x = 240.0f;
	m_Scale.y = 240.0f;

	m_WorldPosition.x = (SCREEN_WIDTH - m_Scale.x) / 2;
	m_WorldPosition.y = (SCREEN_HEIGHT - m_Scale.y) / 2;

	m_TextureKeys.insert(std::make_pair(SubPanelOptionTypes::Inventory_Equipment, "SubPanelOptions_Inventory_Equipment"));
	m_TexturePasses.insert(std::make_pair(SubPanelOptionTypes::Inventory_Equipment, "subpanel1-1.dds"));
	m_OptionCounts.insert(std::make_pair(SubPanelOptionTypes::Inventory_Equipment, EquipmentOptionTypes_Max));

	m_TextureKeys.insert(std::make_pair(SubPanelOptionTypes::Inventory_Eat, "SubPanelOptions_Inventory_Eat"));
	m_TexturePasses.insert(std::make_pair(SubPanelOptionTypes::Inventory_Eat, "subpanel2-1.dds"));
	m_OptionCounts.insert(std::make_pair(SubPanelOptionTypes::Inventory_Eat, EatOptionTypes_Max));

	m_TextureKeys.insert(std::make_pair(SubPanelOptionTypes::Inventory_NoUse, "SubPanelOptions_Inventory_NoUse"));
	m_TexturePasses.insert(std::make_pair(SubPanelOptionTypes::Inventory_NoUse, "subpanel3-1.dds"));
	m_OptionCounts.insert(std::make_pair(SubPanelOptionTypes::Inventory_NoUse, NoUseOptionTypes_Max));

}

void SubPanelOptions::Uninit()
{
	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Uninit();
}

void SubPanelOptions::Update()
{
	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Update();
}

void SubPanelOptions::Draw()
{

	// �}�g���N�X�ݒ�
	Renderer::SetWorldViewProjection2D();

	//���N���X�̃��\�b�h�Ăяo��
	GameObject::Draw();
}

void SubPanelOptions::SetTypes(SubPanelOptionTypes type)
{
	m_OptionType = type;
	std::string key{};
	std::string path{};


	auto it = m_TextureKeys.find(type);
	if (it != m_TextureKeys.end()) {
		key = it->second;
	}

	it = m_TexturePasses.find(type);
	if (it != m_TexturePasses.end()) {
		path = it->second;
	}


	m_StaticSprite = AddComponent<StaticSprite>();//��̂Ƃǂ����ł��悢
	m_StaticSprite->Init(m_WorldPosition.x, m_WorldPosition.y, m_Scale.x, m_Scale.y, key, path);
}

int SubPanelOptions::GetOptionsCount()
{
	int typeOptionsCount = 0;

	auto it = m_OptionCounts.find(m_OptionType);
	if (it != m_OptionCounts.end()) {
		typeOptionsCount = it->second;
	}

	return typeOptionsCount;
}


void SubPanelOptions::SetSelectOption(int index, Item* itemPtr)
{
	Scene* scene = Manager::GetScene();
	Inventory* inventory = scene->GetGameObject<Inventory>();
	Player* player = scene->GetGameObject<Player>();

	auto itemPtrKey = itemPtr->GetKey();

	switch (index)
	{
	case SelectOptions::Special:
			if (m_OptionType == SubPanelOptionTypes::Inventory_Equipment)
			{
				player->SetEquipment(itemPtrKey);
			}
			else if (m_OptionType == SubPanelOptionTypes::Inventory_Eat)
			{
				player->EatItem(itemPtrKey);
			}

		break;

	case SelectOptions::LiftUp:
		//�����グ��
		break;

	case SelectOptions::ThrowAway:
		//�̂Ă�
			inventory->DecreaseItem(itemPtr);
		break;
	}


}