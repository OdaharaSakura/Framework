#include "main.h"
#include "textureContainer.h"
#include "scene.h"
#include <algorithm>

std::unordered_map<std::string, Image*> TextureContainer::m_ImageDictionary{};
std::string TextureContainer::m_FrontPath = "asset\\texture\\";

void TextureContainer::Load(int sceneIndex)
{
    // シーンに基づいて特定のテクスチャをロード
    switch (sceneIndex) {
    case SCENE_TITLE:
        // タイトルシーンのテクスチャをロード
        //LoadImageData("LoadingLogo", "lightgreen.jpg");
        break;
    case SCENE_GAME:
        LoadImageData("Hoe", "equipment_icon_kuwa.dds");//鍬
        LoadImageData("Sickle", "equipment_icon_kama.dds");//鎌
        LoadImageData("WaterWand", "equipment_icon_wand.dds");//杖
        LoadImageData("EquipmentPanel", "equipment_Panel.png");//装備パネル
        LoadImageData("InventoryPanel", "Windows_item.dds");//インベントリパネル
        LoadImageData("InventoryItemIconCursor", "sentaku_frame.dds");//インベントリパネルフレーム
        LoadImageData("SubPanel", "subpanel.dds");//サブパネル
        LoadImageData("SubPanelCursor", "subpanelCursor.dds");//サブパネル
        LoadImageData("SubPanelOptions_Inventory_Equipment", "subpanel1-1.dds");//サブパネル
        LoadImageData("SubPanelOptions_Inventory_Eat", "subpanel2-1.dds");//サブパネル
        LoadImageData("SubPanelOptions_Inventory_NoUse", "subpanel3-1.dds");//サブパネル
        LoadImageData("SpecialTalk", "special_UI_L.dds");//特別キー
        LoadImageData("UsualTalk", "usual_UI_L.dds");//汎用キー
        LoadImageData("GaugeFrame", "gauge_frame.dds");//汎用キー
        LoadImageData("TIPS_E", "TIPS_E.dds");//Eキー
        LoadImageData("TIPS_TAB", "TIPS_TAB.dds");//タブキー
        LoadImageData("TIPS_Space", "TIPS_Space.dds");//スペースキー
        LoadImageData("TIPS_UO", "TIPS_UO.dds");//カメラ回転キー
        LoadImageData("TIPS_WASD", "TIPS_WASD.dds");//上下左右キー
        LoadImageData("TIPS_Space_DEC", "TIPS_Space_DEC.dds");//決定キー
        LoadImageData("Tomato_Seed", "tomatoseeds.dds");//カメラ回転キー
        LoadImageData("Eggplant_Seed", "eggplantseeds.dds");//上下左右キー
        LoadImageData("Onion_Seed", "onionseeds.dds");//決定キー
        LoadImageData("Carrot_Seed", "carrotseeds.dds");//決定キー
        break;
    case SCENE_RESULT:
        break;
    default:
        break;
    }
}

void TextureContainer::Unload(int sceneIndex)
{
    // シーンに基づいて不要なテクスチャをアンロードし、メモリを解放
    for (auto& it : m_ImageDictionary) {
        delete it.second; // メモリ解放
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
            //ロードに失敗した
            //TODO:エラーメッセージ出す
            delete newImage;
        }
    }
    else {
        // 既に存在するキーの場合、新しい Image オブジェクトを作成しない
        //TODO:エラーメッセージ出す
    }
}
