#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "networkTest.h"
#include "CNetwork.h"
#include "playerNetwork.h"
#include "player.h"
#include "meshfield.h"
#include "camera.h"
#include "text.h"
#include "tree_billboard.h"
#include "sky.h"
#include "cylinder.h"
#include "earth.h"

#include <winuser.h>

#define STAGE_CONNECTING 1
#define STAGE_PLAYING 2

CNETWORK Net;
BOOL g_boConnected = FALSE;
INT g_Stage = STAGE_CONNECTING;

void NetWorkTest::Load()
{
	Earth::Load();
	TreeBillboard::Load();
}


void NetWorkTest::Init()
{
	Load();

	// �ʐM�p�N���X�̏�����
	if (FAILED(Net.Init(GetWindow())))
	{
		MessageBox(0, "�ʐM�N���X�̏��������o���܂���", "", MB_OK);
	}

	AddGameObject<Camera>(LAYER_CAMERA);//�o�^����List�̎�ނ�ς���
	AddGameObject<Sky>(LAYER_OBJECT_3D);
	MeshField* meshField = AddGameObject<MeshField>(LAYER_OBJECT_3D);


	AddGameObject<Cylinder>(LAYER_OBJECT_3D)->SetGameObject(D3DXVECTOR3(6.0f, 0.0f, 6.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(3.0f, 3.0f, 3.0f));



	m_player = AddGameObject<Player>(LAYER_OBJECT_3D);
	m_player->SetPosition(D3DXVECTOR3(-1.0f, 0.0f, -4.0f));
	m_playerNetwork = AddGameObject<PlayerNetWork>(LAYER_OBJECT_3D);
	m_playerNetwork->SetPosition(D3DXVECTOR3(2.0f, 0.0f, -4.0f));

	
	srand(0);

	for (int i = 0; i < 20; i++)
	{
		TreeBillboard* treeBillboard = AddGameObject<TreeBillboard>(LAYER_OBJECT_3D);

		D3DXVECTOR3 pos;
		pos.x = (float)rand() / RAND_MAX * 100.0f - 50.0f;
		pos.z = (float)rand() / RAND_MAX * 100.0f - 50.0f;
		pos.y = meshField->GetHeight(pos);

		treeBillboard->SetPosition(pos);
	}


}

void NetWorkTest::Uninit()
{
	Scene::Uninit();

	Earth::Unload();

	TreeBillboard::Unload();
}


void NetWorkTest::Update()
{
	switch (g_Stage)
	{
	case STAGE_CONNECTING:
		Connect();
		break;
	case STAGE_PLAYING:
		Scene::Update();

		D3DXVECTOR3 playerNetworkPosition = m_playerNetwork->GetPosition();
		D3DXVECTOR3 playerPosition = m_player->GetPosition();
		Net.DoAction(RECIEVE_BINARYDATA, &playerNetworkPosition, sizeof(D3DXVECTOR3));
		Net.DoAction(SEND_BINARYDATA, &playerPosition, sizeof(D3DXVECTOR3));
		m_playerNetwork->SetPosition(playerNetworkPosition);

	/*	if (Net.m_boHosting)
		{
			Net.DoAction(RECIEVE_BINARYDATA, &Thing[MELON].vecPosition, sizeof(D3DXVECTOR3));
			Net.DoAction(SEND_BINARYDATA, &Thing[TOMATO].vecPosition, sizeof(D3DXVECTOR3));
		}
		else
		{
			Net.DoAction(RECIEVE_BINARYDATA, &Thing[TOMATO].vecPosition, sizeof(D3DXVECTOR3));
			Net.DoAction(SEND_BINARYDATA, &Thing[MELON].vecPosition, sizeof(D3DXVECTOR3));
		}*/

		//if (Input::GetKeyPress(VK_F2))
		//{
		//	m_Fade->SetIsFadeOut();

		//}
		//if (m_Fade->GetFadeOutFinish())
		//{
		//	Manager::SetScene<Result>();//�G���^�[�L�[����������Q�[���V�[���Ɉڍs
		//}
		break;
	}

}

HRESULT NetWorkTest::Connect()
{
	if (!g_boConnected)
	{
		g_boConnected = TRUE;
		// �z�X�g		 
		if (Net.m_boHosting)
		{
			if (FAILED(Net.DoAction(HOST_SESSION, (PVOID)"�V���v���Q�[��_DP", NULL)))
			{
				MessageBox(0, "�z�X�g�Ƃ��Ă̑ҋ@���s", "", MB_OK);
				return E_FAIL;
			}
		}
		// �Q�X�g
		else
		{
			if (FAILED(Net.DoAction(CONNECT_SESSION, (PVOID)L"�V���v���Q�[��_DP", NULL)))
			{
				MessageBox(0, "�z�X�g�ւ̐ڑ����s", "", MB_OK);
				return E_FAIL;
			}
		}
	}
	BYTE bPlayer = 0;
	//CHAR szStr[MAX_PATH + 1];
	//�z�X�g	
	Net.QueryNetPlayerAmt(&bPlayer);
	if (Net.m_boHosting)
	{

		if (bPlayer < 2)
		{
			//m_Write->SetText("�v���C���[��: 1 \n�v���C���[��2�l�ɂȂ�܂őҋ@���܂�");
		}
		else
		{
			//m_Write->SetText("");
			g_Stage = STAGE_PLAYING;
		}
	}
	//�Q�X�g		 
	else
	{
		if (bPlayer < 2)
		{
			//m_Write->SetText("�v���C���[��: 1 \n�v���C���[��2�l�ɂȂ�܂őҋ@���܂�");
		}
		else
		{
			//m_Write->SetText("");
			D3DXVECTOR3 networkpos = m_playerNetwork->GetPosition();
			D3DXVECTOR3 pos = m_player->GetPosition();
			m_player->SetPosition(networkpos);
			m_playerNetwork->SetPosition(pos);
			g_Stage = STAGE_PLAYING;
		}
	}
	return S_OK;
}


