#include "CNetwork.h"

CNETWORK* g_pThis=NULL;
//
//INT CALLBACK DialogProc(HWND hwndDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
//�_�C�A���O�{�b�N�X�̃��b�Z�[�W�v���V�[�W���[�i�_�C�A���O�̍쐬�i�K�ɕK�v�j
INT CALLBACK DialogProc(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	return g_pThis->DlgProc(hDlg, uMsg, wParam, lParam);
}
//
//CNETWORK::CNETWORK()
//�R���X�g���N�^
CNETWORK::CNETWORK()
{
	ZeroMemory(this,sizeof(CNETWORK));
}
//
//CNETWORK::~CNETWORK()
//�f�X�g���N�^
CNETWORK::~CNETWORK()
{
	EndDialog(m_hDlg,TRUE);
}
//
//HRESULT CNETWORK::Init(HWND hWnd)
//�ʐM�N���X�̏�����
HRESULT CNETWORK::Init(HWND hWnd)
{
	g_pThis=this;
	//WinSock2.0�̏�����
	WORD wVersionRequired=MAKEWORD(2,0);
	WSADATA wsaData;
	WSAStartup(wVersionRequired,&wsaData);
	if (wsaData.wVersion != wVersionRequired)
	{
		MessageBox(0,"WinSock�o�[�W����2.0�ȏオ�C���X�g�[������Ă��܂���","",MB_OK);
		return E_FAIL;	
	}
	//�ڑ��_�C�A���O  ���̃_�C�A���O�̃v���V�[�W���[�͒ʐM�C�x���g�n���h���[�Ƃ��Ďg�p����̂ŁA���[�h���X�Ƃ��č쐬
	CreateDialog((HINSTANCE)GetWindowLong(hWnd,GWL_HINSTANCE),
		MAKEINTRESOURCE(IDD_DIALOG1),hWnd,(DLGPROC)DialogProc);
	//�Z�b�e�B���O�i���[�U�[�ɂ��|�[�g���̓��́j���I������܂Ń��b�Z�[�W���|�[�����O
	MSG msg;
	ZeroMemory( &msg, sizeof(msg) );
	while( !m_boSetting)
     {
		 if( PeekMessage( &msg, m_hDlg, 0U, 0U, PM_REMOVE ) )
         {	
			 TranslateMessage( &msg );
             DispatchMessage( &msg );	
         }
	 }
	return S_OK;
}
//
//INT CNETWORK::DlgProc(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
//�_�C�A���O�{�b�N�X�̃��b�Z�[�W�v���V�[�W���[�i�N���X���\�b�h�j
INT CNETWORK::DlgProc(HWND hDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	TCHAR szPort[30];
	switch(uMsg)
	{
		//
		//Win32�C�x���g���b�Z�[�W
		case WM_INITDIALOG:
			m_hDlg=hDlg;
			return FALSE;
		case WM_CLOSE:
			ShowWindow(hDlg,SW_HIDE);
			m_boSetting=TRUE;
			return FALSE;
		case WM_COMMAND:			    
			switch (LOWORD(wParam)) 
			{
				//�z�X�g�{�^��
			case IDC_BUTTON1:
				m_boHosting=TRUE;				
				if(!GetDlgItemText(hDlg,IDC_EDIT1,szPort,sizeof(szPort)))
				{
					MessageBox(0,"�|�[�g�ԍ�����͂��Ă�������","",MB_OK);
					return TRUE;
				}
				m_boSetting=TRUE;
				m_wPort = atoi(szPort);
				ShowWindow(hDlg,SW_HIDE);
				return TRUE;
				//�Q�X�g�{�^��
			case IDC_BUTTON2:
				m_boHosting=FALSE;
				if(!GetDlgItemText(hDlg,IDC_EDIT1,szPort,sizeof(szPort)))
				{
					MessageBox(0,"�|�[�g�ԍ�����͂��Ă�������","",MB_OK);
					return TRUE;
				}
				if(!GetDlgItemText(hDlg,IDC_EDIT2,m_szHostName,sizeof(m_szHostName)) && 
						!GetDlgItemText(hDlg,IDC_EDIT3,m_szHostAddr,sizeof(m_szHostAddr)) )					
				{				
					MessageBox(0,"�z�X�g����IP�A�h���X����͂��Ă�������","",MB_OK);
					return TRUE;
				}			
				m_wPort = atoi(szPort);	
				ShowWindow(m_hDlg,SW_HIDE);
				m_boSetting=TRUE;
				return TRUE;
			}
			return TRUE;
		//
		//WinSock����̃��b�Z�[�W(�񓯊�API�́A���[�U�[��`���b�Z�[�W�𔭍s����)

		case WSM_GETHOST://WSAAsyncGetHostByName�֐�����߂������̏���
			GetHostHandler(wParam,lParam);
			return TRUE;
		case WSM_ASYNC://WSAAsyncSelect�ɂ��A�񓯊��ɐݒ肳�ꂽ�C�x���g�́A���̃��b�Z�[�W���g���K�[�i���s�j����
			if(m_boHosting)
			{
				HostAsyncHandler(wParam,lParam);
			}
			else
			{
				ClientAsyncHandler(wParam,lParam);
			}
			return TRUE;

	}
	return FALSE;
}
//
//HRESULT CNETWORK::DoAction(NETACTION Act,PVOID pData,DWORD dwSize)
//�N���X�O����A�ėp�I�Ȉ����ő���\�ɂ��邽�߂̃A�N�Z�X�֐�
HRESULT CNETWORK::DoAction(NETACTION Act,PVOID pData,DWORD dwSize)
{
	switch(Act)
	{	
	case HOST_SESSION:	
		if(SUCCEEDED(HostSession()))
		{	
			return S_OK;
		}
		else
		{
			return E_FAIL;
		}
		break;
	case CONNECT_SESSION:		
		if(SUCCEEDED(ConnectSession()))
		{			
			return S_OK;
		}
		else
		{
			return E_FAIL;
		}
		break;

	case SEND_BINARYDATA:
		return Send(pData,dwSize);
		break;

	case RECIEVE_BINARYDATA:
		memcpy((BYTE*)pData,m_bBinaryData,dwSize);
		break;
	}
	return S_OK;
}
//
//HRESULT CNETWORK::QueryNetPlayerAmt(BYTE* pbPlayerAmt)
//�O���ɃZ�b�V�����̐l����Ԃ�
HRESULT CNETWORK::QueryNetPlayerAmt(BYTE* pbPlayerAmt)
{
	*pbPlayerAmt = m_bNetPlayerAmt;
	return S_OK;
}
//
//HRESULT CNETWORK::HostSession()
//�z�X�g�ƂȂ�i�Z�b�V�������쐬����j
HRESULT CNETWORK::HostSession()
{	
	//�\�P�b�g���쐬
	m_socMine=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socMine == INVALID_SOCKET)
	{
		MessageBox(0,"�\�P�b�g�쐬���s","",MB_OK);
		return E_FAIL;
	}
	//�\�P�b�g��񓯊����[�h�ɂ���
	if (WSAAsyncSelect(m_socMine, m_hDlg, WSM_ASYNC,FD_CONNECT | FD_ACCEPT | FD_READ | FD_WRITE | FD_CLOSE))	
	{ 	
		MessageBox(0,"�񓯊����[�h�ݒ莸�s","",MB_OK);
		return E_FAIL;	
	}
	//�o�C���h
	m_saServer.sin_family=AF_INET;
	m_saServer.sin_addr.s_addr=INADDR_ANY;
	m_saServer.sin_port=htons(m_wPort);

	if( bind(m_socMine,	(LPSOCKADDR)&m_saServer,	sizeof(SOCKADDR_IN))==SOCKET_ERROR)
	{
		MessageBox(0,"�o�C���h���s","",MB_OK);
		return E_FAIL;
	}
	//���X��
	if( listen(m_socMine,1)==SOCKET_ERROR)
	{
		MessageBox(0,"���X�����s","",MB_OK);
		return E_FAIL;
	}
	m_bNetPlayerAmt++;

	return S_OK;
}
//
//HRESULT CNETWORK::ConnectSession()
//�Q�X�g�ƂȂ�i�Z�b�V�����ɎQ���j
HRESULT CNETWORK::ConnectSession()
{		
	in_addr iaHost;
	//�z�X�g������z�X�g�T�[�o�[��T��
	if(m_szHostName[0] != 0 && WSAAsyncGetHostByName(m_hDlg, WSM_GETHOST,m_szHostName,	
		m_szHostEntry,MAXGETHOSTSTRUCT) ==0)        
	{
		MessageBox(0,"WSAAsyncGetHostByName�Ɏ��s���܂���","",MB_OK);
		return E_FAIL;
	}
	//�z�X�g�A�h���X�iIP�A�h���X�j����z�X�g�T�[�o�[��T��
	iaHost.s_addr=inet_addr(m_szHostAddr);
	if(m_szHostAddr[0] != 0 && WSAAsyncGetHostByAddr(m_hDlg, WSM_GETHOST,
		(const CHAR*)&iaHost,sizeof(in_addr),AF_INET,m_szHostEntry,MAXGETHOSTSTRUCT)==0 )
	{
		MessageBox(0,"WSAAsyncGetHostByAddr�Ɏ��s���܂���","",MB_OK);	
		return E_FAIL;
	}
	m_bNetPlayerAmt++;
	return S_OK;
}
//
//VOID CNETWORK::GetHostHandler(WPARAM wParam,LPARAM lParam)
//WSAAsyncGetHostByName�֐��ɂ������鉞�����b�Z�[�W���n���h���i�����j����
VOID CNETWORK::GetHostHandler(WPARAM wParam,LPARAM lParam)
{
	//�Ȃ�炩�̃G���[���������`�F�b�N
	if( WSAGETASYNCERROR(lParam) )
	{
		MessageBox(0,"�ڑ��G���[","",MB_OK);
		return;
	}
	//�\�P�b�g���쐬
	m_socMine=socket(AF_INET, SOCK_STREAM, 0);
	if (m_socMine == INVALID_SOCKET)
	{
		MessageBox(0,"�\�P�b�g�쐬���s","",MB_OK);
		return;
	}
	//�񓯊����[�h�̐ݒ�
	if (WSAAsyncSelect(m_socMine, m_hDlg, WSM_ASYNC,FD_CONNECT | FD_READ | FD_WRITE | FD_CLOSE))	
	{ 	
		MessageBox(0,"�񓯊����[�h�ݒ莸�s","",MB_OK);
		return;	
	}
	//�z�X�g�A�h���X��������
	LPHOSTENT pHostEntry=(LPHOSTENT)m_szHostEntry;
	m_saServer.sin_family = AF_INET;	
	m_saServer.sin_port = htons(m_wPort);
	m_saServer.sin_addr = *((LPIN_ADDR)*pHostEntry->h_addr_list);
	//�ڑ�
	if( connect(m_socMine,(LPSOCKADDR)&m_saServer,sizeof(SOCKADDR_IN))==SOCKET_ERROR)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{

			MessageBox(0,"�ڑ����s","",MB_OK);
			return;
		}		
	}	
}
//
//VOID CNETWORK::HostAsyncHandler(WPARAM wParam,LPARAM lParam)
//�񓯊�����M���b�Z�[�W���n���h���i�����j����@�z�X�g�p
VOID CNETWORK::HostAsyncHandler(WPARAM wParam,LPARAM lParam)
{
	INT iAddLen=sizeof(SOCKADDR_IN);;
	switch(LOWORD(lParam))
	{
		//FD_ACCEPT
	case FD_ACCEPT:
		m_socClient=accept(m_socMine,(LPSOCKADDR)&m_saClient,&iAddLen);
		if(m_socClient==SOCKET_ERROR)
		{
			MessageBox(0,"�N���C�A���g���A�N�Z�v�g�o���܂���ł���","",MB_OK);
		}
		m_bNetPlayerAmt++;
		return;
		//FD_READ
	case FD_READ:
		recv(m_socClient,(CHAR*)m_bBinaryData,sizeof(m_bBinaryData),0);	
		return;
	}
}
//
//VOID CNETWORK::ClientAsyncHandler(WPARAM wParam,LPARAM lParam)
//�񓯊�����M���b�Z�[�W���n���h���i�����j����@�Q�X�g�p
VOID CNETWORK::ClientAsyncHandler(WPARAM wParam,LPARAM lParam)
{
	switch(LOWORD(lParam))
	{
		//FD_WRITE
	case FD_WRITE:
		m_boSetting=TRUE;
		m_bNetPlayerAmt++;
		return;
		//FD_READ
	case FD_READ:	
		recv(m_socMine,(CHAR*)m_bBinaryData,sizeof(m_bBinaryData),0);	
		return;	
	}
}

//
//HRESULT CNETWORK::Send(VOID* pvData,DWORD dwSize)
//�f�[�^�̑��M
HRESULT CNETWORK::Send(VOID* pvData,DWORD dwSize)
{
	//�z�X�g
	if(m_boHosting)
	{
		if(send(m_socClient,(CHAR*)pvData,dwSize,0) ==SOCKET_ERROR)
		{
			MessageBox(0,"���M���s","",MB_OK);
			return E_FAIL;
		}
	}
	//�Q�X�g
	else
	{
		if(send(m_socMine,(CHAR*)pvData,dwSize,0) ==SOCKET_ERROR)
		{
			MessageBox(0,"���M���s","",MB_OK);
			return E_FAIL;
		}
	}	
	return S_OK;
}