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
        LoadModelData("Desk", "desk.obj");//机
        LoadModelData("House1", "house1.obj");//家
        LoadModelData("House2", "house2.obj");//家2
        LoadModelData("Shop1", "shop1.obj");//赤色の店
        LoadModelData("Shop2", "shop2.obj");//臙脂色の店
        LoadModelData("Shop3", "shop3.obj");//茶色の店
        LoadModelData("Fence", "fence.obj");//柵
        LoadModelData("FenceWood", "woodfence.obj");//木製の柵
        LoadModelData("MiddleTree", "treemiddle.obj");//並木道用の樹木
        LoadModelData("SymbolTree", "TAIZYU.obj");//中央の大樹
        LoadModelData("WindMill", "windmill.obj");//風車
        LoadModelData("Gate", "gate.obj");//門
        LoadModelData("Gate2", "gate2.obj");//門2
        /*LoadModelData("Bridge", "bridge.obj");//橋
        LoadModelData("Pool", "pool.obj");//水汲み場
        LoadModelData("WateringCan", "wateringcan.obj");//空のじょうろ
        LoadModelData("WateringCan2", "wateringcan2.obj");//水いっぱいのじょうろ*/
        LoadModelData("Carriage", "carriage.obj");//馬車
        LoadModelData("Mountain", "mountain.obj");//山
        LoadModelData("Flower", "flower.obj");//花
        LoadModelData("Flower2", "flower2.obj");//花2
        LoadModelData("Flower3", "flower3.obj");//花3
        LoadModelData("Flower4", "flower4.obj");//花4
        LoadModelData("Flower5", "flower5.obj");//花5
        LoadModelData("Flower6", "flower6.obj");//花6
        //LoadModelData("Barrel", "barrel.obj");//たる
        LoadModelData("DryField", "dryfield.obj");//乾燥畑
        LoadModelData("WetField", "wetfield.obj");//水やり畑
        LoadModelData("Seed", "seed.obj");//種
        LoadModelData("Carrot_Seedling", "carrot_1.obj");//人参第一段階
        LoadModelData("Carrot_Seedling2", "carrot_2.obj");//人参第二段階

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

Model* ModelContainer::GetModelKey(std::string key)
{
    auto it = m_ModelDictionary.find(key);
    if (it != m_ModelDictionary.end()) {
        return it->second;
    }
    else {
        return nullptr;
    }
}



void ModelContainer::LoadModelData(std::string key, std::string path)
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


