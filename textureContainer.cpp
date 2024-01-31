#include "main.h"
#include "textureContainer.h"
#include "scene.h"
#include <algorithm>

std::unordered_map<std::string, Image*> TextureContainer::m_ImageDictionary{};
std::string TextureContainer::m_FrontPath = "asset/texture/";

void TextureContainer::Load(int sceneIndex)
{
    // �V�[���Ɋ�Â��ē���̃e�N�X�`�������[�h
    switch (sceneIndex) {
    case SCENE_TITLE:
        // �^�C�g���V�[���̃e�N�X�`�������[�h
        //AddImage("titleBackground", "path/to/title_background.png");
        break;
    case SCENE_GAME:
        AddImage("Hoe", "equipment_icon_kuwa.dds");//�L
        AddImage("WateringCan", "equipment_icon_WateringCan.png");//�����
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

void TextureContainer::AddImage(std::string key,  std::string path)
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
