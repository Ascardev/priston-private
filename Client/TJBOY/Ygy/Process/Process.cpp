#include "StdAfx.h"
#define PROCESS_CPP
#include "..\\YgyHeader.h"

extern HWND hwnd;


extern char UserAccount[256];		//id�� ����ִ� ����
extern char	szConnServerName[16];	//������ �����̸��� ����ִ� ����

int vrunRuning = 0;					//vrun.dat�� ���࿩��

int gameServerPORT=0;
char gameServerIP[16]={0,};
BOOL bMic = 0;

char g_AllClanWon[_CLANWON_MAX][STRING_MAX];

CProcess::CProcess()
{
	m_cMemMap			 = NULL;	
	m_hRemoteProcess	 = NULL;
	m_hRemoteWnd		 = NULL;	
	//m_nKeyDown			 = -1;
	m_bIsMemMap			 = FALSE;
	m_IsStart			 = FALSE;

}

CProcess::~CProcess()
{
}



extern HWND hwnd; //�������� �ڵ� 
int CProcess::InitRemoteProcess()
{
	m_hRemoteWnd = FindWindow(REMOTEPROCESS_NAME, NULL);

	if(m_hRemoteWnd)  //�������� Ŭ���̾�Ʈ�� ������.
	{
		SendMessage(m_hRemoteWnd,WM_CALLMEMMAP,0, (LPARAM)hwnd);
		return 1;
	}
	return 0;
}



int CProcess::InitRmoteProcessWnd()
{
	m_nStep	 = INSIDE_GAMELOGIN;
	return 1;
}


/*===========================================================================================
����� �޸� �ʰ� �������μ��� �ڵ��� ������ �������ؼ� �ʱ�ȭ �ϴ� ����
============================================================================================*/
BOOL CProcess::Init()
{	
	if(m_IsStart)
	{
		m_cMemMap = (CMemMap*) new CMemMap;
		if(m_cMemMap == NULL)
		{
			return FALSE;
			m_bIsMemMap = FALSE;
		}

		m_cMemMap->SetMemMapSize(MEMORYMAP_MAX);  //MEMORYMAP_MAX  256
		m_cMemMap->SetName(MEMORYMAP_NAME);
		m_cMemMap->InitMemoryMap();
		m_bIsMemMap = TRUE;

		InitRmoteProcessWnd();
	}
	

	return TRUE;
}


/*===========================================================================================
����� �޸� ���� �����ϴ� �Լ�
============================================================================================*/
VOID CProcess::Clear()
{
	if(!m_IsStart) return;

	UserOut();	//������ ��������..


	if(m_hRemoteProcess != NULL)
		TerminateProcess(m_hRemoteProcess,0);

	m_Packet.Clear();
	m_cMemMap->Clear();
	if((m_cMemMap != NULL) && m_bIsMemMap)
	{
		delete m_cMemMap;
	}
}

/*===========================================================================================
1. �޸� �ʿ��� ����Ÿ�� ������ �� m_cMemMap->ReadMemoryMap
2. �޸� �ʿ� �ִ� ����Ÿ�� �Űܿ� m_Packet.GetData()
3. ������ �� ����Ÿ�� �Ľ�			m_Packet.Parsing()
============================================================================================*/
void PacketParsing()	//winmain.cpp
{
	g_CtrlProcess.PacketParsing();
}
VOID CProcess::PacketParsing()
{
	m_cMemMap->ReadMemoryMap((char*)m_Packet.GetData());
	m_Packet.Parsing();
}

VOID CProcess::Main()
{
	if(!m_IsStart) return;

	switch(m_nStep)
	{
	case INSIDE_GAMELOGIN:

		IPPORT ipport;
		ZeroMemory(&ipport, sizeof(ipport));

		ipport.sIndex.dwIndex = INSIDE_IPPORT;
		STRINGCOPY(ipport.ip,gameServerIP);
		ipport.port = gameServerPORT;

		m_cMemMap->WriteMemoryMap((char*)&ipport, sizeof(ipport));
		SendMessage(m_hRemoteWnd,WM_CALLMEMMAP,0,0);

		m_nStep = -1;
		break;

	case INSIDE_USERINFO:
		m_userInfo.sIndex.dwIndex = INSIDE_USERINFO;
		m_cMemMap->WriteMemoryMap((char*)&m_userInfo, sizeof(m_userInfo));
		SendMessage(m_hRemoteWnd,WM_CALLMEMMAP,0,0);
		m_nStep = -1;
		break;

	case INSIDE_USERINFOCHG:
		m_userInfo.sIndex.dwIndex = INSIDE_USERINFOCHG;
		m_cMemMap->WriteMemoryMap((char*)&m_userInfo, sizeof(m_userInfo));
		SendMessage(m_hRemoteWnd,WM_CALLMEMMAP,0,0);
		m_nStep = -1;
		break;
	case INSIDE_MICONOFF:
		VOICEONOFF vm;
		ZeroMemory(&vm, sizeof(vm));

		vm.sIndex.dwIndex = INSIDE_MICONOFF;
		
		//bMic = !bMic;
		vm.bMicONOFF = bMic;

		m_cMemMap->WriteMemoryMap((char*)&vm, sizeof(vm));
		SendMessage(m_hRemoteWnd,WM_CALLMEMMAP,0,0);
		m_nStep = -1;
		break;

	}
}




// ��öȣ (����ũ �¿���)
VOID	ParkSetMicOnOFF();

VOID	ParkSetMicOnOFF()
{
	g_CtrlProcess.SetMicOnOFF();
}
VOID	CProcess::SetMicOnOFF()
{
	if(!m_IsStart) return;

	m_nStep = INSIDE_MICONOFF;
}

VOID CProcess::TestInputData(HWND hWnd,WPARAM wParam,LPARAM lParam,char *temp)
{

}

VOID CProcess::SetStep(int step)
{
	m_nStep = step;
}


int firstFlag = 0;
VOID CProcess::SetSelectCha(char *id,char *chaname, char *clanname,DWORD clannum, int utype)
{
	if(!m_IsStart) return;

	//����Ÿ�� �� ó�� ���õɶ� =========================
	if(firstFlag==0) {
		firstFlag = 1;	
	
		//ktj : ���⼭ ����Ÿ�� �������� ������ �ɰ�쿡�� ������ ó���� �ؾ��ҵ�.
		ZeroMemory(&m_userInfo,sizeof(m_userInfo));
		m_userInfo.sIndex.dwIndex = INSIDE_USERINFO;
		//if(id != NULL)
		//	strncpy(m_userInfo.szID,id,strlen(id));

		extern char UserAccount[256];		//id�� ����ִ� ����
		STRINGCOPY(m_userInfo.szID,UserAccount);


		if(chaname != NULL)
			STRINGCOPY(m_userInfo.szCharName, chaname);
		if(clanname !=NULL)
			STRINGCOPY(m_userInfo.szClanName,clanname);
		m_userInfo.dwClanNum = clannum;
		m_userInfo.utype = utype;

		//�����̸�����

		

		if(strlen(szConnServerName)<15) {
			STRINGCOPY(m_userInfo.szConnServerName,szConnServerName);
		
		
			
		}
		else {
			//©��ߵɵ�
			szConnServerName[15] = 0;
			
		}
		//������쿡�� �̷���
		m_nStep = INSIDE_USERINFO;
		return;
	}


	//������ ������ �ִ� Ŭ�� ��ȣ�� ��ݻ��� ���� Ŭ����ȣ�� ������
	//���ο� ����Ÿ�� ���� �ʿ䰡 ����.
	if(m_userInfo.dwClanNum == clannum) {
		return;
	}



	//ktj : ���⼭ ����Ÿ�� �������� ������ �ɰ�쿡�� ������ ó���� �ؾ��ҵ�.
	m_userInfo.sIndex.dwIndex = INSIDE_USERINFOCHG;
	if(clanname !=NULL)
		STRINGCOPY(m_userInfo.szClanName,clanname);
	else {
		memset(&m_userInfo.szClanName, 0, sizeof(m_userInfo.szClanName));
	}
	m_userInfo.dwClanNum = clannum;
	m_userInfo.utype = utype;

	//Ŭ���̾������ų� �ٲ��� db�� �ٲٱ�����.
	m_nStep = INSIDE_USERINFOCHG;	
}



VOID CProcess::UserOut()
{
	if(!m_IsStart) return;

	P_Out pout;
	pout.sIndex.dwIndex = INSIDE_GAME_OUT;

	m_cMemMap->WriteMemoryMap((char*)&pout, sizeof(pout));
	SendMessage(m_hRemoteWnd,WM_CALLMEMMAP,(WPARAM)0,0);
	Sleep(1000*2);	//���μ����������� �ð��� �ֱ�����.
}

//"mapedit.INI" ���Ͼ��� "INITGAME"�� ���� �ɼ��� �д´�.
int read_GameOption(char *optStr, char *rStr)
{
	std::string strFileName = ".\\luncher.INI";

    if(rStr==NULL) { //int��
        return GetPrivateProfileInt("INITGAME", optStr, 0, strFileName.c_str());
    }
    //string��
    GetPrivateProfileString("INITGAME", optStr, NULL, rStr, 128, strFileName.c_str());
    return 0;
}


int InitGAMEopt()
{
    FILE *fp;
    fopen_s(&fp,"luncher.ini", "rb");
    if(fp==NULL) {
        return 0;
    }
    else {                      //���������� ýũ(mapedit.ini����)
        fclose(fp);             //�ϴ� �ݰ� ���� ����Ÿ�� mapedit.ini���� ������.

		//���� ���� ip,port
		read_GameOption("gameServerIP", gameServerIP );
		gameServerPORT = read_GameOption("gameServerPORT", NULL );
    }
	return TRUE;
}


VOID CProcess::CheckIPandPort(char *ip, int port)
{
	extern BOOL bip_port_error;
	if(bip_port_error==TRUE) {
		m_IsStart = FALSE;
		return;

	}
	
	if(InitGAMEopt() == 0)	//luncher.ini�� ������ ��Ŭ���̾�Ʈ�κ��� ip,port�� �޾ƿ´�.
	{
		if((ip != NULL ) &&(port != 0))
		{
			gameServerPORT = port;
			STRINGCOPY(gameServerIP,ip);

			if(InitRemoteProcess() == 1) {
				vrunRuning = 1;					//vrun.dat�� ���࿩��
				m_IsStart = TRUE;
			}
		}
		else	//ini������ ���� ���������� ip,port������ ������ �׳��̰ɷ� �Ѵ�.
		{
			gameServerPORT = 7000;
			STRINGCOPY(gameServerIP,"211.44.231.13");

			if(InitRemoteProcess() == 1) {
				vrunRuning = 1;					//vrun.dat�� ���࿩��
				m_IsStart = TRUE;
			}

		}
	}
	else //luncher.ini�� ������ �ű⼭ �޾ƿ´�.
	{
		if(gameServerPORT != 0 && gameServerIP[0] != 0)
		{
			if(InitRemoteProcess() == 1) {
				vrunRuning = 1;					//vrun.dat�� ���࿩��
				m_IsStart = TRUE;
				
			}
		}
		else
		{
			m_IsStart = FALSE;
		}
	}
}

VOID CProcess::SetClanChat(char *msg)
{

}