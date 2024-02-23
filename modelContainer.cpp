#include "main.h"
#include "renderer.h"
#include "modelContainer.h"
#include "scene.h"
#include <algorithm>

std::unordered_map<std::string, Model*> ModelContainer::m_ModelDictionary{};

std::string ModelContainer::m_ModelsFrontPath = "asset\\model\\obj\\";


void ModelContainer::Load(int sceneIndex)
{
    // �V�[���Ɋ�Â��ē���̃e�N�X�`�������[�h
    switch (sceneIndex) {
    case SCENE_TITLE:
        // �^�C�g���V�[���̃e�N�X�`�������[�h
        //AddImage("titleBackground", "path/to/title_background.png");
        break;
    case SCENE_GAME:
        LoadModelData("Desk", "desk.obj");//��
        LoadModelData("House1", "house1.obj");//��
        LoadModelData("House2", "house2.obj");//��2
        LoadModelData("House3", "house3.obj");//��3
        LoadModelData("House4", "house4.obj");//��3
        LoadModelData("House5", "house5.obj");//��3
        LoadModelData("Shop1", "shop.obj");//�ԐF�̓X
        LoadModelData("Shop2", "shop2.obj");//�b���F�̓X
        LoadModelData("Shop3", "shop3.obj");//���F�̓X
        LoadModelData("Shop4", "shop4.obj");//���F�̓X
        LoadModelData("Bench", "bench.obj");//�x���`
        LoadModelData("Fence", "fence.obj");//��
        LoadModelData("FenceWood", "woodfence.obj");//�ؐ��̍�
        LoadModelData("MiddleTree", "treemiddle.obj");//���ؓ��p�̎���
        LoadModelData("SymbolTree", "TAIZYU.obj");//�����̑��
        LoadModelData("WindMill", "windmill.obj");//����
        LoadModelData("Gate", "gate.obj");//��
        LoadModelData("Gate2", "gate2.obj");//��2
        LoadModelData("Carriage", "carriage.obj");//�n��
        LoadModelData("Mountain", "mountain.obj");//�R
        LoadModelData("Flower", "flower.obj");//��
        LoadModelData("Flower2", "flower2.obj");//��2
        LoadModelData("Flower3", "flower3.obj");//��3
        LoadModelData("Flower4", "flower4.obj");//��4
        LoadModelData("Flower5", "flower5.obj");//��5
        LoadModelData("Flower6", "flower6.obj");//��6
        LoadModelData("FlowerBed", "flowerbed.obj");//�Ԓd
        LoadModelData("DryField", "dryfield.obj");//������
        LoadModelData("WetField", "wetfield.obj");//����蔨
        LoadModelData("Seed", "seed.obj");//��
        LoadModelData("Carrot_Seedling", "carrot_1.obj");//�l�Q���i�K
        LoadModelData("Carrot_Seedling2", "carrot_2.obj");//�l�Q���i�K
        LoadModelData("Tomato_Seedling", "tomato_1.obj");//�g�}�g���i�K
        LoadModelData("Tomato_Seedling2", "tomato_2.obj");//�g�}�g���i�K
        LoadModelData("Carrot_Seedling", "onion_1.obj");//�ʂ˂����i�K
        LoadModelData("Carrot_Seedling2", "onion_2.obj");//�ʂ˂����i�K
        LoadModelData("Carrot_Seedling", "eggplant_1.obj");//�Ȃ����i�K
        LoadModelData("Carrot_Seedling2", "eggplant_2.obj");//�Ȃ����i�K
        LoadModelData("Carrot_Seedling", "kabu_1.obj");//���ԑ��i�K
        LoadModelData("Carrot_Seedling2", "kabu_2.obj");//���ԑ��i�K
        LoadModelData("Tile", "tile.obj");//�^�C��
        LoadModelData("Wooden", "woodbox.obj");//�ؔ�
        LoadModelData("Hoe", "Kuwa.obj");//����
        LoadModelData("Sickle", "kama.obj");//��
        LoadModelData("WaterWand", "waterwand.obj");//��
        LoadModelData("TomatoSeed", "bag1.obj");//�g�}�g�̎�
        LoadModelData("EggplantSeed", "bag3.obj");//�Ȃ��̎�
        LoadModelData("OnionSeed", "bag4.obj");//�ʂ˂��̎�
        LoadModelData("CarrotSeed", "bag5.obj");//�ɂ񂶂�̎�
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
        delete it.second; // ���������
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

Model* ModelContainer::GetModelPath(std::string path)
{
    std::string fullPath = m_ModelsFrontPath + path;

    auto itr = find_if(m_ModelDictionary.begin(), m_ModelDictionary.end(),
        [&](std::pair < std::string, Model* > pair) { return strcmp(pair.second->GetPath(), fullPath.c_str()) == 0; });

    if (itr != m_ModelDictionary.end())
    {
        return itr->second;
    }
    else
    {
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
            //���[�h�Ɏ��s����
            //TODO:�G���[���b�Z�[�W�o��
            delete newModel;
        }
    }
    else 
    {
        // ���ɑ��݂���L�[�̏ꍇ�A�V���� Image �I�u�W�F�N�g���쐬���Ȃ�
        //TODO:�G���[���b�Z�[�W�o��
    }
}


