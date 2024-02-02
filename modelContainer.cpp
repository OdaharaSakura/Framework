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
        AddModel("Desk", "desk.obj");//��
        AddModel("House1", "house1.obj");//��
        AddModel("House2", "house2.obj");//��2
        AddModel("Shop1", "shop1.obj");//�ԐF�̓X
        AddModel("Shop2", "shop2.obj");//�b���F�̓X
        AddModel("Shop3", "shop3.obj");//���F�̓X
        AddModel("Fence", "fence.obj");//��
        AddModel("FenceWood", "woodfence.obj");//�ؐ��̍�
        AddModel("MiddleTree", "treemiddle.obj");//���ؓ��p�̎���
        AddModel("SymbolTree", "TAIZYU.obj");//�����̑��
        AddModel("WindMill", "windmill.obj");//����
        AddModel("Gate", "gate.obj");//��
        AddModel("Gate2", "gate2.obj");//��2
        /*AddModel("Bridge", "bridge.obj");//��
        AddModel("Pool", "pool.obj");//�����ݏ�
        AddModel("WateringCan", "wateringcan.obj");//��̂��傤��
        AddModel("WateringCan2", "wateringcan2.obj");//�������ς��̂��傤��*/
        AddModel("Carriage", "carriage.obj");//�n��
        AddModel("Mountain", "mountain.obj");//�R
        AddModel("Flower", "flower.obj");//��
        AddModel("Flower2", "flower2.obj");//��2
        AddModel("Flower3", "flower3.obj");//��3
        AddModel("Flower4", "flower4.obj");//��4
        AddModel("Flower5", "flower5.obj");//��5
        AddModel("Flower6", "flower6.obj");//��6
        //AddModel("Barrel", "barrel.obj");//����*/

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


