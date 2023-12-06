#include "CNetwork.h"

CNETWORK* g_pThis = NULL;
//
//INT CALLBACK DialogProc(HWND hwndDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
//ダイアログボックスのメッセージプロシージャー（ダイアログの作成段階に必要）
INT CALLBACK DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)

{
	return g_pThis->DlgProc(hDlg, uMsg, wParam, lParam);
}
//
//CNETWORK::CNETWORK()
//コンストラクタ
CNETWORK::CNETWORK()
{

	ZeroMemory(this, sizeof(CNETWORK));

}
//
//CNETWORK::~CNETWORK()
//デストラクタ
CNETWORK::~CNETWORK()
{

	EndDialog(m_hDlg, TRUE);

}
//
//HRESULT CNETWORK::Init(HWND hWnd)
//通信クラスの初期化
HRESULT CNETWORK::Init(HWND hWnd)
{

	g_pThis = this;
	//WinSock2.0の初期化
	WORD wVersionRequired = MAKEWORD(2, 0);
	WSADATA wsaData;
	WSAStartup(wVersionRequired, &wsaData);
	if (wsaData.wVersion != wVersionRequired)
	{
		MessageBox(0, "WinSockバージョン2.0以上がインストールされていません", "", MB_OK);
		return E_FAIL;
	}
	//接続ダイアログ  このダイアログのプロシージャーは通信イベントハンドラーとして使用するので、モードレスとして作成
	CreateDialog((HINSTANCE)GetWindowLong(hWnd, GWLP_HINSTANCE),
		MAKEINTRESOURCE(IDD_DIALOG1), hWnd, (DLGPROC)DialogProc);
	//セッティング（ユーザーによるポート等の入力）が終了するまでメッセージをポーリング
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (!m_boSetting)
	{
		if (PeekMessage(&msg, m_hDlg, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return S_OK;
}
//
//INT CNETWORK::DlgProc(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
//ダイアログボックスのメッセージプロシージャー（クラスメソッド）

INT CNETWORK::DlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	TCHAR szPort[30];
	switch (uMsg)
	{
		//
		//Win32イベントメッセージ
	case WM_INITDIALOG:
		m_hDlg = hDlg;
		return FALSE;
	case WM_CLOSE:
		ShowWindow(hDlg, SW_HIDE);
		m_boSetting = TRUE;
		return FALSE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
			//ホストボタン
		case IDC_BUTTON1:
			m_boHosting = TRUE;
			if (!GetDlgItemText(hDlg, IDC_EDIT1, szPort, sizeof(szPort)))
			{
				MessageBox(0, "ポート番号を入力してください", "", MB_OK);
				return TRUE;
			}
			m_boSetting = TRUE;
			m_wPort = atoi(szPort);
			ShowWindow(hDlg, SW_HIDE);
			return TRUE;
			//ゲストボタン
		case IDC_BUTTON2:
			m_boHosting = FALSE;
			if (!GetDlgItemText(hDlg, IDC_EDIT1, szPort, sizeof(szPort)))
			{
				MessageBox(0, "ポート番号を入力してください", "", MB_OK);
				return TRUE;
			}
			if (!GetDlgItemText(hDlg, IDC_EDIT2, m_szHostName, sizeof(m_szHostName)) &&
				!GetDlgItemText(hDlg, IDC_EDIT3, m_szHostAddr, sizeof(m_szHostAddr)))
			{
				MessageBox(0, "ホスト名かIPアドレスを入力してください", "", MB_OK);
				return TRUE;
			}
			m_wPort = atoi(szPort);
			ShowWindow(m_hDlg, SW_HIDE);
			m_boSetting = TRUE;
			return TRUE;
		}
		return TRUE;
		//
		//WinSockからのメッセージ(非同期APIは、ユーザー定義メッセージを発行する)

	case WSM_GETHOST://WSAAsyncGetHostByName関数から戻った時の処理
		GetHostHandler(wParam, lParam);
		return TRUE;
	case WSM_ASYNC://WSAAsyncSelectにより、非同期に設定されたイベントは、このメッセージをトリガー（発行）する
		if (m_boHosting)
		{
			HostAsyncHandler(wParam, lParam);
		}
		else
		{
			ClientAsyncHandler(wParam, lParam);
		}
		return TRUE;


	}
	return FALSE;
}
//
//HRESULT CNETWORK::DoAction(NETACTION Act,PVOID pData,DWORD dwSize)
//クラス外から、汎用的な引数で操作可能にするためのアクセス関数

HRESULT CNETWORK::DoAction(NETACTION Act, PVOID pData, DWORD dwSize)
{
	switch (Act)
	{
	case HOST_SESSION:
		if (SUCCEEDED(HostSession()))
		{

			return S_OK;
		}
		else
		{
			return E_FAIL;
		}
		break;

	case CONNECT_SESSION:
		if (SUCCEEDED(ConnectSession()))
		{

			return S_OK;
		}
		else
		{
			return E_FAIL;
		}
		break;

	case SEND_BINARYDATA:

		return Send(pData, dwSize);
		break;

	case RECIEVE_BINARYDATA:
		memcpy((BYTE*)pData, m_bBinaryData, dwSize);

		break;
	}
	return S_OK;
}
//
//HRESULT CNETWORK::QueryNetPlayerAmt(BYTE* pbPlayerAmt)
//外部にセッションの人数を返す
HRESULT CNETWORK::QueryNetPlayerAmt(BYTE* pbPlayerAmt)
{
	*pbPlayerAmt = m_bNetPlayerAmt;
	return S_OK;
}
//
//HRESULT CNETWORK::HostSession()
//ホストとなる（セッションを作成する）
HRESULT CNETWORK::HostSession()

{
	//ソケットを作成
	m_socMine = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socMine == INVALID_SOCKET)
	{
		MessageBox(0, "ソケット作成失敗", "", MB_OK);
		return E_FAIL;
	}
	//ソケットを非同期モードにする
	if (WSAAsyncSelect(m_socMine, m_hDlg, WSM_ASYNC, FD_CONNECT | FD_ACCEPT | FD_READ | FD_WRITE | FD_CLOSE))
	{
		MessageBox(0, "非同期モード設定失敗", "", MB_OK);
		return E_FAIL;
	}
	//バインド
	m_saServer.sin_family = AF_INET;
	m_saServer.sin_addr.s_addr = INADDR_ANY;
	m_saServer.sin_port = htons(m_wPort);

	if (bind(m_socMine, (LPSOCKADDR)&m_saServer, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		MessageBox(0, "バインド失敗", "", MB_OK);
		return E_FAIL;
	}
	//リスン
	if (listen(m_socMine, 1) == SOCKET_ERROR)
	{
		MessageBox(0, "リスン失敗", "", MB_OK);

		return E_FAIL;
	}
	m_bNetPlayerAmt++;

	return S_OK;
}
//
//HRESULT CNETWORK::ConnectSession()
//ゲストとなる（セッションに参加）
HRESULT CNETWORK::ConnectSession()
{
	in_addr iaHost;
	//ホスト名からホストサーバーを探す
	if (m_szHostName[0] != 0 && WSAAsyncGetHostByName(m_hDlg, WSM_GETHOST, m_szHostName,
		m_szHostEntry, MAXGETHOSTSTRUCT) == 0)
	{
		MessageBox(0, "WSAAsyncGetHostByNameに失敗しました", "", MB_OK);
		return E_FAIL;
	}
	//ホストアドレス（IPアドレス）からホストサーバーを探す
	iaHost.s_addr = inet_addr(m_szHostAddr);
	if (m_szHostAddr[0] != 0 && WSAAsyncGetHostByAddr(m_hDlg, WSM_GETHOST,
		(const CHAR*)&iaHost, sizeof(in_addr), AF_INET, m_szHostEntry, MAXGETHOSTSTRUCT) == 0)
	{
		MessageBox(0, "WSAAsyncGetHostByAddrに失敗しました", "", MB_OK);

		return E_FAIL;
	}
	m_bNetPlayerAmt++;
	return S_OK;
}
//
//VOID CNETWORK::GetHostHandler(WPARAM wParam,LPARAM lParam)
//WSAAsyncGetHostByName関数にたいする応答メッセージをハンドル（処理）する

VOID CNETWORK::GetHostHandler(WPARAM wParam, LPARAM lParam)
{
	//なんらかのエラーが無いかチェック
	if (WSAGETASYNCERROR(lParam))
	{
		MessageBox(0, "接続エラー", "", MB_OK);
		return;
	}
	//ソケットを作成
	m_socMine = socket(AF_INET, SOCK_STREAM, 0);
	if (m_socMine == INVALID_SOCKET)
	{
		MessageBox(0, "ソケット作成失敗", "", MB_OK);
		return;
	}
	//非同期モードの設定
	if (WSAAsyncSelect(m_socMine, m_hDlg, WSM_ASYNC, FD_CONNECT | FD_READ | FD_WRITE | FD_CLOSE))
	{
		MessageBox(0, "非同期モード設定失敗", "", MB_OK);
		return;
	}
	//ホストアドレスを初期化
	LPHOSTENT pHostEntry = (LPHOSTENT)m_szHostEntry;
	m_saServer.sin_family = AF_INET;
	m_saServer.sin_port = htons(m_wPort);
	m_saServer.sin_addr = *((LPIN_ADDR)*pHostEntry->h_addr_list);
	//接続
	if (connect(m_socMine, (LPSOCKADDR)&m_saServer, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)

	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{

			MessageBox(0, "接続失敗", "", MB_OK);
			return;
		}
	}

}
//
//VOID CNETWORK::HostAsyncHandler(WPARAM wParam,LPARAM lParam)
//非同期送受信メッセージをハンドル（処理）する　ホスト用

VOID CNETWORK::HostAsyncHandler(WPARAM wParam, LPARAM lParam)
{
	INT iAddLen = sizeof(SOCKADDR_IN);;
	switch (LOWORD(lParam))
	{
		//FD_ACCEPT
	case FD_ACCEPT:
		m_socClient = accept(m_socMine, (LPSOCKADDR)&m_saClient, &iAddLen);
		if (m_socClient == SOCKET_ERROR)
		{
			MessageBox(0, "クライアントをアクセプト出来ませんでした", "", MB_OK);

		}
		m_bNetPlayerAmt++;
		return;
		//FD_READ
	case FD_READ:

		recv(m_socClient, (CHAR*)m_bBinaryData, sizeof(m_bBinaryData), 0);

		return;
	}
}
//
//VOID CNETWORK::ClientAsyncHandler(WPARAM wParam,LPARAM lParam)
//非同期送受信メッセージをハンドル（処理）する　ゲスト用

VOID CNETWORK::ClientAsyncHandler(WPARAM wParam, LPARAM lParam)
{
	switch (LOWORD(lParam))
	{
		//FD_WRITE
	case FD_WRITE:
		m_boSetting = TRUE;
		m_bNetPlayerAmt++;
		return;
		//FD_READ
	case FD_READ:
		recv(m_socMine, (CHAR*)m_bBinaryData, sizeof(m_bBinaryData), 0);
		return;

	}
}

//
//HRESULT CNETWORK::Send(VOID* pvData,DWORD dwSize)
//データの送信

HRESULT CNETWORK::Send(VOID* pvData, DWORD dwSize)
{
	//ホスト
	if (m_boHosting)
	{
		if (send(m_socClient, (CHAR*)pvData, dwSize, 0) == SOCKET_ERROR)
		{
			MessageBox(0, "送信失敗", "", MB_OK);

			return E_FAIL;
		}
	}
	//ゲスト
	else
	{

		if (send(m_socMine, (CHAR*)pvData, dwSize, 0) == SOCKET_ERROR)
		{
			MessageBox(0, "送信失敗", "", MB_OK);
			return E_FAIL;
		}
	}

	return S_OK;
}