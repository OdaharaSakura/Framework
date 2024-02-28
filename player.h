#pragma once

#include "gameObject.h"
#include "animationModel.h"
#include "savedata.h"

#include <string>

class Item;

enum PLAYER_STATE
{
	PLAYER_STATE_TITLE,
	PLAYER_STATE_GROUND,
	PLAYER_STATE_JUMP,
	PLAYER_STATE_ATTACK,
	PLAYER_STATE_CONVERSATION,//��b
	PLAYER_STATE_INVENTORY//�C���x���g��
};

class Player : public GameObject//�p��
{
private:
	int m_PlayerState = PLAYER_STATE_GROUND;
	bool m_IsGround{};
	bool m_IsConnectNetWork{};

	char m_InputData{};


	int m_countnum = 0;//test

	class IEquipment* m_EquipmentInterface;
	class Inventory* m_InventoryInterface;
	class ItemFactory* m_ItemFactory;
	class EquipmentFactory* m_EquipmentFactory;

	class Text* m_Description;//����
	class Conversation* m_Conversation;//��b
	std::string m_Message;//��b���̃��b�Z�[�W

	D3DXVECTOR3			m_MoveVec{};
	D3DXVECTOR3			m_Velocity{};
	D3DXVECTOR3			m_modelScale{};
	D3DXQUATERNION		m_Quaternion{};

	class Audio* m_ShotSE{};
	class MeshField* m_MeshField{};

	int m_Hp;
	int m_HpMax = 500;

	int m_Time{};
	int m_AnimationIndex;
	int m_NextAnimationIndex;
	float m_BlendRate{};

	int m_AnimeState{};
	int m_AnimeFrame{};
	int m_AttackDelaynum{};

	bool m_IsAttackflg{};//�A�^�b�N�ł��邩(�G�͈͓̔��ɓ�������)
	bool m_Attackflg{};//�U��������

public:
	static AnimationModel* m_Model;

	void Init();
	void Uninit();
	void Update();
	void Draw();
	void UpdateTitle();//TODO:�X�e�[�g�p�^�[���ŏ����Ă݂�
	void UpdateGround();
	void UpdateJump();
	void UpdateAttack();
	void UpdateConversation();
	void UpdateInventory();

	void UseEquipment();
	void EatItem(std::string key);
	void SetEquipment(std::string key);
	void SetInventoryItem(std::string key);

	void SetNonAttackflg() { m_Attackflg = false; }
	void SetConnectNetWork() { m_IsConnectNetWork = true; }
	void SetPlayerState(int state) { m_PlayerState = state; }
	void AddHp(int hp);
	void LoadPlayerData(PlayerData playerData);


	D3DXVECTOR3 GetForward()//�O�����x�N�g���擾
	{
		D3DXMATRIX rot;
		//D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);
		D3DXVECTOR3 forward;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		return forward;
	}

	D3DXVECTOR3 GetRight()//�E�����x�N�g���擾
	{
		D3DXMATRIX rot;
		//D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);
		D3DXVECTOR3 right;
		right.x = rot._11;
		right.y = rot._12;
		right.z = rot._13;

		return right;
	}


	D3DXVECTOR3 GetUp()//������x�N�g���擾
	{
		D3DXMATRIX rot;
		//D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		D3DXMatrixRotationQuaternion(&rot, &m_Quaternion);
		D3DXVECTOR3 top;
		top.x = rot._21;
		top.y = rot._22;
		top.z = rot._23;

		return top;
	}

	int GetHp() { return m_Hp;}
	int GetHpMax() {return m_HpMax;}
	bool GetAttackflg() { return m_Attackflg; }
	char GetInputData() { return m_InputData; }

	void GetDebugData();
};
