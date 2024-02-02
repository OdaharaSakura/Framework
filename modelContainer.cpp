#include "main.h"
#include "renderer.h"
#include "modelContainer.h"
#include "scene.h"
#include <algorithm>

std::unordered_map<std::string, Model*> ModelContainer::m_ModelDictionary{};

std::string ModelContainer::m_ModelsFrontPath = "asset\\model\\obj\\";


void ModelContainer::Load(int sceneIndex)
{
    // シーンに基づいて特定のテクスチャをロード
    switch (sceneIndex) {
    case SCENE_TITLE:
        // タイトルシーンのテクスチャをロード
        //AddImage("titleBackground", "path/to/title_background.png");
        break;
    case SCENE_GAME:
        AddModel("Desk", "desk.obj");//机
        AddModel("House1", "house1.obj");//家
        AddModel("House2", "house2.obj");//家2
        AddModel("Shop1", "shop1.obj");//赤色の店
        AddModel("Shop2", "shop2.obj");//臙脂色の店
        AddModel("Shop3", "shop3.obj");//茶色の店
        AddModel("Fence", "fence.obj");//柵
        AddModel("FenceWood", "woodfence.obj");//木製の柵
        AddModel("MiddleTree", "treemiddle.obj");//並木道用の樹木
        AddModel("SymbolTree", "TAIZYU.obj");//中央の大樹
        AddModel("WindMill", "windmill.obj");//風車
        AddModel("Gate", "gate.obj");//門
        AddModel("Gate2", "gate2.obj");//門2
        /*AddModel("Bridge", "bridge.obj");//橋
        AddModel("Pool", "pool.obj");//水汲み場
        AddModel("WateringCan", "wateringcan.obj");//空のじょうろ
        AddModel("WateringCan2", "wateringcan2.obj");//水いっぱいのじょうろ*/
        AddModel("Carriage", "carriage.obj");//馬車
        AddModel("Mountain", "mountain.obj");//山
        AddModel("Flower", "flower.obj");//花
        AddModel("Flower2", "flower2.obj");//花2
        AddModel("Flower3", "flower3.obj");//花3
        AddModel("Flower4", "flower4.obj");//花4
        AddModel("Flower5", "flower5.obj");//花5
        AddModel("Flower6", "flower6.obj");//花6
        //AddModel("Barrel", "barrel.obj");//たる*/

        break;
    case SCENE_RESULT:
        break;
    default:
        break;
    }
}

void ModelContainer::Unload(int sceneIndex)
{
    for (auto& it : m_ModelDictionary) {
        delete it.second; // メモリ解放
        it.second = nullptr;
    }
    m_ModelDictionary.clear();
}

Model* ModelContainer::GetModel_Key(std::string key)
{
    auto it = m_ModelDictionary.find(key);
    if (it != m_ModelDictionary.end()) {
        return it->second;
    }
    else {
        return nullptr;
    }
}



void ModelContainer::AddModel(std::string key, std::string path)
{

    std::string fullPath = m_ModelsFrontPath + path;

    auto it = m_ModelDictionary.find(key);
    if (it == m_ModelDictionary.end()) {
        Model* newModel = new Model;
        newModel->Load(fullPath.c_str());

        if (newModel != nullptr)
        {
            m_ModelDictionary[key] = newModel;
        }
        else
        {
            //ロードに失敗した
            //TODO:エラーメッセージ出す
            delete newModel;
        }
    }
    else 
    {
        // 既に存在するキーの場合、新しい Image オブジェクトを作成しない
        //TODO:エラーメッセージ出す
    }
}


