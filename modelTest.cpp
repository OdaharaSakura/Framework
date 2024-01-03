#include "main.h"
#include "renderer.h"
#include "modelTest.h"
#include "shader.h"

void ModelTest::Init()
{
    m_Models.push_back(new Model());
    m_Models[0]->Load("asset\\model\\obj\\tree1.obj");
    m_ModelPositions.push_back(D3DXVECTOR3(15.0f, 0.0f, 20.0f)); // 最初のモデルの位置

    m_Models.push_back(new Model());
    m_Models[1]->Load("asset\\model\\obj\\calot.obj");
    m_ModelPositions.push_back(D3DXVECTOR3(20.0f, 0.0f, 18.0f)); // 最初のモデルの位置

    m_Models.push_back(new Model());
    m_Models[2]->Load("asset\\model\\obj\\carrot_1.obj");
    m_ModelPositions.push_back(D3DXVECTOR3(15.0f, 0.0f, 18.0f)); // 2番目のモデルの位置

    m_Models.push_back(new Model());
    m_Models[3]->Load("asset\\model\\obj\\carrot_2.obj");
    m_ModelPositions.push_back(D3DXVECTOR3(20.0f, 0.0f, 16.0f)); // 最初のモデルの位置

    m_Models.push_back(new Model());
    m_Models[4]->Load("asset\\model\\obj\\chair.obj");
    m_ModelPositions.push_back(D3DXVECTOR3(15.0f, 0.0f, 16.0f)); // 2番目のモデルの位置

    m_Models.push_back(new Model());
    m_Models[5]->Load("asset\\model\\obj\\desk.obj");
    m_ModelPositions.push_back(D3DXVECTOR3(20.0f, 0.0f, 14.0f)); // 最初のモデルの位置

    m_Models.push_back(new Model());
    m_Models[6]->Load("asset\\model\\obj\\eggplant.obj");
    m_ModelPositions.push_back(D3DXVECTOR3(15.0f, 0.0f, 14.0f)); // 2番目のモデルの位置

    m_Models.push_back(new Model());
    m_Models[7]->Load("asset\\model\\obj\\Kuwa.obj");
    m_ModelPositions.push_back(D3DXVECTOR3(15.0f, 0.0f, 12.0f)); // 2番目のモデルの位置

    m_Models.push_back(new Model());
    m_Models[8]->Load("asset\\model\\obj\\mizuyarihatake.obj");
    m_ModelPositions.push_back(D3DXVECTOR3(20.0f, 0.0f, 12.0f)); // 2番目のモデルの位置

    m_Models.push_back(new Model());
    m_Models[9]->Load("asset\\model\\obj\\niwatori.obj");
    m_ModelPositions.push_back(D3DXVECTOR3(15.0f, 0.0f, 10.0f)); // 2番目のモデルの位置

    m_Models.push_back(new Model());
    m_Models[10]->Load("asset\\model\\obj\\note.obj");
    m_ModelPositions.push_back(D3DXVECTOR3(20.0f, 0.0f, 10.0f)); // 2番目のモデルの位置

    m_Models.push_back(new Model());
    m_Models[11]->Load("asset\\model\\obj\\onion.obj");
    m_ModelPositions.push_back(D3DXVECTOR3(15.0f, 0.0f, 8.0f)); // 2番目のモデルの位置

    m_Models.push_back(new Model());
    m_Models[12]->Load("asset\\model\\obj\\piano.obj");
    m_ModelPositions.push_back(D3DXVECTOR3(20.0f, 0.0f, 8.0f)); // 2番目のモデルの位置s


    m_Models.push_back(new Model());
    m_Models[13]->Load("asset\\model\\obj\\sofa.obj");
    m_ModelPositions.push_back(D3DXVECTOR3(15.0f, 0.0f, 6.0f)); // 2番目のモデルの位置s


    m_Rotation = D3DXVECTOR3(0.0f, 3.14f / 2 * 3, 0.0f);

    AddComponent<VertexLighting>();
}

void ModelTest::Uninit()
{
    for (Model* model : m_Models)
    {
        model->Unload();
        delete model;
    }

    m_Models.clear();
    m_ModelPositions.clear();
}

void ModelTest::Update()
{

}

void ModelTest::Draw()
{
    for (size_t i = 0; i < m_Models.size(); i++)
    {
        // マトリクス設定
        D3DXMATRIX world, scale, rot, trans;
        D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
        D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
        D3DXMatrixTranslation(&trans, m_WorldPosition.x + m_ModelPositions[i].x, m_WorldPosition.y + m_ModelPositions[i].y, m_WorldPosition.z + m_ModelPositions[i].z);
        world = scale * rot * trans;

        Renderer::SetWorldMatrix(&world);

        m_Models[i]->Draw();
    }
}