#include "main.h"
#include "textureContainer.h"
#include "scene.h"
#include <algorithm>

std::unordered_map<std::string, Image*> TextureContainer::m_ImageDictionary{};
std::string TextureContainer::m_FrontPath = "asset\\texture\\";

void TextureContainer::Load(int sceneIndex)
{
    // �V�[���Ɋ�Â��ē���̃e�N�X�`�������[�h
    switch (sceneIndex) {
    case SCENE_TITLE:
        // �^�C�g���V�[���̃e�N�X�`�������[�h
        //LoadImageData("LoadingLogo", "lightgreen.jpg");
        break;
    case SCENE_GAME:
        LoadImageData("Hoe", "equipment_icon_kuwa.dds");//�L
        LoadImageData("Sickle", "equipment_icon_kama.dds");//��
        LoadImageData("WaterWand", "equipment_icon_wand.dds");//��
        LoadImageData("EquipmentPanel", "equipment_Panel.png");//�����p�l��
        LoadImageData("InventoryPanel", "Windows_item.dds");//�C���x���g���p�l��
        LoadImageData("InventoryItemIconCursor", "sentaku_frame.dds");//�C���x���g���p�l���t���[��
        LoadImageData("SubPanel", "subpanel.dds");//�T�u�p�l��
        LoadImageData("SubPanelCursor", "subpanelCursor.dds");//�T�u�p�l��
        LoadImageData("SubPanelOptions_Inventory_Equipment", "subpanel1-1.dds");//�T�u�p�l��
        LoadImageData("SubPanelOptions_Inventory_Eat", "subpanel2-1.dds");//�T�u�p�l��
        LoadImageData("SubPanelOptions_Inventory_NoUse", "subpanel3-1.dds");//�T�u�p�l��
        LoadImageData("SpecialTalk", "special_UI_L.dds");//���ʃL�[
        LoadImageData("UsualTalk", "usual_UI_L.dds");//�ėp�L�[
        LoadImageData("GaugeFrame", "gauge_frame.dds");//�ėp�L�[
        LoadImageData("TIPS_E", "TIPS_E.dds");//E�L�[
        LoadImageData("TIPS_TAB", "TIPS_TAB.dds");//�^�u�L�[
        LoadImageData("TIPS_Space", "TIPS_Space.dds");//�X�y�[�X�L�[
        LoadImageData("TIPS_UO", "TIPS_UO.dds");//�J������]�L�[
        LoadImageData("TIPS_WASD", "TIPS_WASD.dds");//�㉺���E�L�[
        LoadImageData("TIPS_Space_DEC", "TIPS_Space_DEC.dds");//����L�[
        LoadImageData("Tomato_Seed", "tomatoseeds.dds");//�J������]�L�[
        LoadImageData("Eggplant_Seed", "eggplantseeds.dds");//�㉺���E�L�[
        LoadImageData("Onion_Seed", "onionseeds.dds");//����L�[
        LoadImageData("Carrot_Seed", "carrotseeds.dds");//����L�[
        break;
    case SCENE_RESULT:
        break;
    default:
        break;
    }
}

void TextureContainer::Unload(int sceneIndex)
{
    // �V�[���Ɋ�Â��ĕs�v�ȃe�N�X�`�����A�����[�h���A�����������
    for (auto& it : m_ImageDictionary) {
        delete it.second; // ���������
        it.second = nullptr;
    }
    m_ImageDictionary.clear();
}

Image* TextureContainer::GetImage_Path(std::string path)
{
    std::string fullPath = m_FrontPath + path;

    auto itr = find_if(m_ImageDictionary.begin(), m_ImageDictionary.end(),
        [&](std::pair < std::string, Image* > pair) { return strcmp(pair.second->GetPath(), fullPath.c_str()) == 0; });

    if (itr != m_ImageDictionary.end())
    {
        return itr->second;
    }
    else
    {
        return nullptr;
    }
}

Image* TextureContainer::GetImage_Key(std::string key)
{
    auto it = m_ImageDictionary.find(key);
    if (it != m_ImageDictionary.end()) {
        return it->second;
    }
    else {
        return nullptr;
    }
}

void TextureContainer::LoadImageData(std::string key,  std::string path)
{
    std::string fullPath = m_FrontPath + path;

    auto it = m_ImageDictionary.find(key);
    if (it == m_ImageDictionary.end()) {
        Image* newImage = new Image(fullPath.c_str());

        if (newImage && newImage->GetShaderResourceView() != nullptr) {
            m_ImageDictionary[key] = newImage;
        }
        else 
        {
            //���[�h�Ɏ��s����
            //TODO:�G���[���b�Z�[�W�o��
            delete newImage;
        }
    }
    else {
        // ���ɑ��݂���L�[�̏ꍇ�A�V���� Image �I�u�W�F�N�g���쐬���Ȃ�
        //TODO:�G���[���b�Z�[�W�o��
    }
}
