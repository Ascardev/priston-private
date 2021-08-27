#include "StdAfx.h"
#include "..\\YgyHeader.h"



CPacket::CPacket()
{
}
CPacket::~CPacket()
{
}


void CPacket::Init()
{	
	ZeroMemory(memMapReadData,sizeof(memMapReadData));
}
void CPacket::Clear()
{	

}

void CPacket::SetSelectCha(char *id,char *chaname, char *clanname,DWORD clannum)
{
	ZeroMemory(&m_userInfo,sizeof(m_userInfo));
	m_userInfo.sIndex.dwIndex = INSIDE_USERINFO;
	if(id != NULL)
		STRINGCOPY(m_userInfo.szID,id);
	if(chaname != NULL)
		STRINGCOPY(m_userInfo.szCharName,chaname);
	if(clanname !=NULL)
		STRINGCOPY(m_userInfo.szClanName,clanname);
	m_userInfo.dwClanNum = clannum;
}


VOICTALKUSERDATA voiceUser;
char voiceInfoStr[256]={0,};

BOOL talk_check(VOICTALKUSERDATA *vUser)
{
	static int tCnt=0;
	static char  talk[15][32];
	static DWORD ttime[15];

	int i, j;

	DWORD t = timeGetTime();
	for(i=0; i<15; i++)
	{
		if(ttime[i] != 0 && (t - ttime[i])  >= 1000*15)
			ttime[i] = 0;
	}

	for(i=0; i<8; i++)
	{
		if(vUser->uID[i][0]==0) 
			continue;
		for(j=0; j<15; j++) 
		{
			if(ttime[j]==0) 
				continue;

			if(strcmp(vUser->uID[i], talk[j]) ==0 ) 
			{
				goto jmp1;
			}
		}

		for(j=0; j<15; j++) 
		{
			if(ttime[j]==0) 
			{
				ZeroMemory(&talk[j], sizeof(talk[j]));
				lstrcpy(talk[j],vUser->uID[i]);

				ttime[j] = t;
				break;
			}
		}
jmp1:
		continue;
	}
	return TRUE;
}

void CPacket::Parsing()
{
	DWORD dwIndex = 0;
	m_Index = (INDEX*)memMapReadData;
	dwIndex = m_Index->dwIndex;
	switch(dwIndex)
	{

	case GOPRIS_VUSERIDs:
		{
			VOICTALKUSERDATA *vU = (VOICTALKUSERDATA*)memMapReadData;
			memcpy(&voiceUser, vU, sizeof( VOICTALKUSERDATA ));
			voiceUser.time = timeGetTime();
			talk_check(vU);
		}

		break;

	case GOPRIS_VCLIENTINFO:
		{
			VCLIENTINFO *vci = (VCLIENTINFO *)memMapReadData;

			if(vci->vcl_state==VC_STATE_NOSERVER)
				wsprintf(voiceInfoStr, "%s", VC_STATE_NOSERVER_STR);
			if(vci->vcl_state==VC_STATE_NOTCONNECT)
				wsprintf(voiceInfoStr, "%s", VC_STATE_NOTCONNECT_STR);
			if(vci->vcl_state==VC_STATE_CONNECT)
				wsprintf(voiceInfoStr, "%s", VC_STATE_CONNECT_STR);
			if(vci->vcl_state==VC_STATE_DISCONNECT)
				wsprintf(voiceInfoStr, "%s", VC_STATE_DISCONNECT_STR);
		}
		break;
	}	
}

void CPacket::SetClanChat(char *msg)
{
	m_sClanChat.sIndex.dwIndex = INSIDE_CLANCHAT;
	STRINGCOPY(m_sClanChat.szMsg,msg);
}

