#include "StdAfx.h"
#define PROCESS_CPP
#include "..\\YgyHeader.h"

extern HWND hwnd;


extern char UserAccount[256];		//id가 들어있는 버퍼
extern char	szConnServerName[16];	//접속한 서버이름이 들어있는 버퍼

int vrunRuning = 0;					//vrun.dat의 실행여부

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



extern HWND hwnd; //프리스턴 핸들 
int CProcess::InitRemoteProcess()
{
	m_hRemoteWnd = FindWindow(REMOTEPROCESS_NAME, NULL);

	if(m_hRemoteWnd)  //프리스턴 클라이언트를 보낸다.
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
현재는 메모리 맵과 원격프로세스 핸들을 가지고 오기위해서 초기화 하는 역할
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
현재는 메모리 맵을 삭제하는 함수
============================================================================================*/
VOID CProcess::Clear()
{
	if(!m_IsStart) return;

	UserOut();	//유저가 나가도록..


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
1. 메모리 맵에서 데이타를 가지고 옴 m_cMemMap->ReadMemoryMap
2. 메모리 맵에 있는 데이타를 옮겨옴 m_Packet.GetData()
3. 가지고 온 데이타를 파싱			m_Packet.Parsing()
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




// 박철호 (마이크 온오프)
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

	//데이타가 맨 처음 셋팅될때 =========================
	if(firstFlag==0) {
		firstFlag = 1;	
	
		//ktj : 여기서 데이타만 저장한후 보내야 될경우에만 보내는 처리를 해야할듯.
		ZeroMemory(&m_userInfo,sizeof(m_userInfo));
		m_userInfo.sIndex.dwIndex = INSIDE_USERINFO;
		//if(id != NULL)
		//	strncpy(m_userInfo.szID,id,strlen(id));

		extern char UserAccount[256];		//id가 들어있는 버퍼
		STRINGCOPY(m_userInfo.szID,UserAccount);


		if(chaname != NULL)
			STRINGCOPY(m_userInfo.szCharName, chaname);
		if(clanname !=NULL)
			STRINGCOPY(m_userInfo.szClanName,clanname);
		m_userInfo.dwClanNum = clannum;
		m_userInfo.utype = utype;

		//서버이름셋팅

		

		if(strlen(szConnServerName)<15) {
			STRINGCOPY(m_userInfo.szConnServerName,szConnServerName);
		
		
			
		}
		else {
			//짤라야될듯
			szConnServerName[15] = 0;
			
		}
		//보낼경우에는 이렇게
		m_nStep = INSIDE_USERINFO;
		return;
	}


	//이전에 설정되 있던 클랜 번호와 방금새로 들어온 클랜번호가 같으면
	//새로운 데이타를 보낼 필요가 없다.
	if(m_userInfo.dwClanNum == clannum) {
		return;
	}



	//ktj : 여기서 데이타만 저장한후 보내야 될경우에만 보내는 처리를 해야할듯.
	m_userInfo.sIndex.dwIndex = INSIDE_USERINFOCHG;
	if(clanname !=NULL)
		STRINGCOPY(m_userInfo.szClanName,clanname);
	else {
		memset(&m_userInfo.szClanName, 0, sizeof(m_userInfo.szClanName));
	}
	m_userInfo.dwClanNum = clannum;
	m_userInfo.utype = utype;

	//클랜이없어지거나 바뀐경우 db를 바꾸기위함.
	m_nStep = INSIDE_USERINFOCHG;	
}



VOID CProcess::UserOut()
{
	if(!m_IsStart) return;

	P_Out pout;
	pout.sIndex.dwIndex = INSIDE_GAME_OUT;

	m_cMemMap->WriteMemoryMap((char*)&pout, sizeof(pout));
	SendMessage(m_hRemoteWnd,WM_CALLMEMMAP,(WPARAM)0,0);
	Sleep(1000*2);	//프로세스삭제전에 시간을 주기위함.
}

//"mapedit.INI" 파일안의 "INITGAME"의 각종 옵션을 읽는다.
int read_GameOption(char *optStr, char *rStr)
{
	std::string strFileName = ".\\luncher.INI";

    if(rStr==NULL) { //int형
        return GetPrivateProfileInt("INITGAME", optStr, 0, strFileName.c_str());
    }
    //string형
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
    else {                      //디버깅버전의 첵크(mapedit.ini사용시)
        fclose(fp);             //일단 닫고 셋팅 데이타를 mapedit.ini에서 꺼낸다.

		//게임 서버 ip,port
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
	
	if(InitGAMEopt() == 0)	//luncher.ini가 없으면 겜클라이언트로부터 ip,port를 받아온다.
	{
		if((ip != NULL ) &&(port != 0))
		{
			gameServerPORT = port;
			STRINGCOPY(gameServerIP,ip);

			if(InitRemoteProcess() == 1) {
				vrunRuning = 1;					//vrun.dat의 실행여부
				m_IsStart = TRUE;
			}
		}
		else	//ini파일이 없고 서버에서도 ip,port셋팅이 없으면 그냥이걸로 한다.
		{
			gameServerPORT = 7000;
			STRINGCOPY(gameServerIP,"211.44.231.13");

			if(InitRemoteProcess() == 1) {
				vrunRuning = 1;					//vrun.dat의 실행여부
				m_IsStart = TRUE;
			}

		}
	}
	else //luncher.ini가 있으면 거기서 받아온다.
	{
		if(gameServerPORT != 0 && gameServerIP[0] != 0)
		{
			if(InitRemoteProcess() == 1) {
				vrunRuning = 1;					//vrun.dat의 실행여부
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