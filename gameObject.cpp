#include "main.h"
#include "renderer.h"
#include "gameObject.h"



void GameObject::Uninit()
{
    for (Component* component : m_ComponentList)//範囲forループ
    {
        component->Uninit();
        delete component;
    }
    m_ComponentList.clear();//リスト構造の削除
}

void GameObject::Update()
{
    for (Component* component : m_ComponentList)//範囲forループ
    {
        component->Update();
    }
}

void GameObject::Draw()
{
    for (Component* component : m_ComponentList)//範囲forループ
    {
        component->Draw();//ポリモフィズム
    }
}

void GameObject::SetPosScale(D3DXVECTOR3 position, D3DXVECTOR3 scale)
{
    m_WorldPosition = position;
    m_Scale = scale;
}

void GameObject::SetGameObject(D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 scale)
{
    m_WorldPosition = position;
    m_Rotation = rotation;
    m_Scale = scale;
}

D3DXVECTOR3 GameObject::GetForward()
{
    D3DXMATRIX rot;
    D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
    D3DXVECTOR3 forward;
    forward.x = rot._31;
    forward.y = rot._32;
    forward.z = rot._33;

    return forward;
}

D3DXVECTOR3 GameObject::GetRight()
{
    D3DXMATRIX rot;
    D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
    D3DXVECTOR3 right;
    right.x = rot._11;
    right.y = rot._12;
    right.z = rot._13;

    return right;
}

D3DXVECTOR3 GameObject::GetUp()
{
    D3DXMATRIX rot;
    D3DXQUATERNION q = GetWorldRotation();
    D3DXMatrixRotationQuaternion(&rot, &q);
    D3DXVECTOR3 up;
    up.x = rot._21;
    up.y = rot._22;
    up.z = rot._23;

    return up;
}



