#pragma once
//インクルード
#include <stdio.h>
#include <Winsock2.h>
#include "resource.h"
//ライブラリのロード
#pragma comment (lib,"Ws2_32.lib")
//定数定義
#define WSM_GETHOST WM_USER+1
#define WSM_ASYNC WM_USER+2

//データ型

enum NETACTION//通信メソッドをクラス外から汎用的に操作するために識別子を使う
{
	HOST_SESSION,
	CONNECT_SESSION,
	SEND_STRING,
	SEND_BINARYDATA,
	RECIEVE_BINARYDATA,
};
//
class CNETWORK
{
public:
	BOOL m_boHosting;
	HWND m_hDlg;
	BOOL m_boSetting;

	CNETWORK();
	~CNETWORK();
	HRESULT Init(HWND);
	INT DlgProc(HWND ,UINT ,WPARAM ,LPARAM );
	HRESULT DoAction(NETACTION,PVOID ,DWORD );
	HRESULT QueryNetPlayerAmt(BYTE*);
private:
	SOCKET m_socMine;
	SOCKET m_socClient;
	SOCKADDR_IN m_saServer;
	SOCKADDR_IN m_saClient;
	TCHAR m_szHostName[MAX_PATH+1];
	TCHAR m_szHostAddr[MAX_PATH+1];
	TCHAR m_szHostEntry[MAXGETHOSTSTRUCT+1];
	WORD m_wPort;	
	BYTE m_bNetPlayerAmt;
	BYTE m_bBinaryData[1000];
	BOOL m_bConnected; 
	
	HRESULT HostSession();
	HRESULT ConnectSession();
	VOID GetHostHandler(WPARAM ,LPARAM );
	VOID HostAsyncHandler(WPARAM ,LPARAM );
	VOID ClientAsyncHandler(WPARAM ,LPARAM );
	HRESULT Send(VOID* , DWORD);
};