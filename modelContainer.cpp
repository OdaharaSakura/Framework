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
        LoadModelData("Shop1", "shop1.obj");//�ԐF�̓X
        LoadModelData("Shop2", "shop2.obj");//�b���F�̓X
        LoadModelData("Shop3", "shop3.obj");//���F�̓X
        LoadModelData("Fence", "fence.obj");//��
        LoadModelData("FenceWood", "woodfence.obj");//�ؐ��̍�
        LoadModelData("MiddleTree", "treemiddle.obj");//���ؓ��p�̎���
        LoadModelData("SymbolTree", "TAIZYU.obj");//�����̑��
        LoadModelData("WindMill", "windmill.obj");//����
        LoadModelData("Gate", "gate.obj");//��
        LoadModelData("Gate2", "gate2.obj");//��2
        /*LoadModelData("Bridge", "bridge.obj");//��
        LoadModelData("Pool", "pool.obj");//�����ݏ�
        LoadModelData("WateringCan", "wateringcan.obj");//��̂��傤��
        LoadModelData("WateringCan2", "wateringcan2.obj");//�������ς��̂��傤��*/
        LoadModelData("Carriage", "carriage.obj");//�n��
        LoadModelData("Mountain", "mountain.obj");//�R
        LoadModelData("Flower", "flower.obj");//��
        LoadModelData("Flower2", "flower2.obj");//��2
        LoadModelData("Flower3", "flower3.obj");//��3
        LoadModelData("Flower4", "flower4.obj");//��4
        LoadModelData("Flower5", "flower5.obj");//��5
        LoadModelData("Flower6", "flower6.obj");//��6
        //LoadModelData("Barrel", "barrel.obj");//����
        LoadModelData("DryField", "dryfield.obj");//������
        LoadModelData("WetField", "wetfield.obj");//����蔨
        LoadModelData("Seed", "seed.obj");//��
        LoadModelData("Carrot_Seedling", "carrot_1.obj");//�l�Q���i�K
        LoadModelData("Carrot_Seedling2", "carrot_2.obj");//�l�Q���i�K

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


