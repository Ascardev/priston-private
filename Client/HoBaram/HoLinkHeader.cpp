#include "StdAfx.h"

HoLogin		*lpLogin = NULL;
HoOpening	*lpOpening = NULL;

char CharacterName1[256];
char CharacterName2[256];

char Server_Name[64] = { 0 };

int GameStartField = -1;

int WorkMode = OPENING_MODE;

void HoReLoad()
{
	if (lpLogin != NULL && WorkMode == LOGIN_MODE)
		lpLogin->ReLoad();
}

int InitOpening()
{
	memset(CharacterName1, 0, sizeof(CharacterName1));
	memset(CharacterName2, 0, sizeof(CharacterName2));

	lpLogin = new HoLogin();
	lpOpening = new HoOpening();

	if (WorkMode == OPENING_MODE)
		lpOpening->Init();
	else if (WorkMode == LOGIN_MODE)
		lpLogin->Init();

	return TRUE;
}

int DrawOpening()
{
	if (lpOpening == NULL || lpLogin == NULL)
		return FALSE;

	if (WorkMode == OPENING_MODE)
		lpOpening->Draw();
	else if (WorkMode == LOGIN_MODE)
		lpLogin->Draw();

	return TRUE;
}

static int GameErrorTimeCount = 0;
int MainOpening()
{
	if (lpOpening == NULL || lpLogin == NULL)
		return FALSE;

	if (WorkMode == OPENING_MODE)
	{
		if (lpOpening->Main() == 2)
		{
			lpLogin->Init();
			WorkMode = LOGIN_MODE;
		}
	}
	else if (WorkMode = LOGIN_MODE)
	{
		int num;
		num = lpLogin->Main();
		if (num == 2)
		{
			lpOpening->Init();
			WorkMode = OPENING_MODE;
		}
		else if (num == 3)
			CURSORHANDLE->Hide();

		if (!CURSORHANDLE->IsOpen())
		{
			WorkMode = MODE_NONE;

			return TRUE;
		}

	}
	return FALSE;
}

int CloseOpening()
{
	lpOpening->Close();
	DELET(lpOpening);

	lpLogin->Close();
	DELET(lpLogin);

	return TRUE;
}
int RestoreSetSize()
{
	if (lpOpening)
		lpOpening->SetSize();

	return TRUE;
}
TRANS_USERCHAR_INFO		 *ServerUserCharacterInfo = NULL;
smTRANS_CHAR_COMMAND2	 *ServerReturn = NULL;
smTRANS_COMMAND			 *ServerLoginError = NULL;
PacketServerList		 *DownServerListInfo = NULL;

hoServerListInfo		UserServerListInfo[MAX_DOWN_SERVER_LIST_INFO];
int						UserServerListInfoCount;

HoUserCharacterInfo		DownUserCharacterInfo[MAX_DOWN_USER_LIST_INFO];
int						DownUserCharacterCount;

int HoRecvMessage(DWORD dwCode, void *RecvBuff)
{
	if (dwCode == smTRANSCODE_ID_SETUSERINFO)
	{
		ServerUserCharacterInfo = (TRANS_USERCHAR_INFO *)RecvBuff;
		if (strcmp(UserAccount, ServerUserCharacterInfo->szID) != 0)
			return FALSE;

		memset(DownUserCharacterInfo, 0, sizeof(DownUserCharacterInfo));
		DownUserCharacterCount = 0;

		for (int index = 0; index < ServerUserCharacterInfo->PlayUserCount; index++)
		{
			wsprintf(DownUserCharacterInfo[index].Name, "%s", ServerUserCharacterInfo->CharInfo[index].szName);
			DownUserCharacterInfo[index].Level = ServerUserCharacterInfo->CharInfo[index].Level;

			wsprintf(DownUserCharacterInfo[index].BodyName, "%s", ServerUserCharacterInfo->CharInfo[index].szModelName);
			wsprintf(DownUserCharacterInfo[index].FaceName, "%s", ServerUserCharacterInfo->CharInfo[index].szModelName2);

			DownUserCharacterInfo[index].Job = ServerUserCharacterInfo->CharInfo[index].JOB_CODE;
			DownUserCharacterInfo[index].StartField = ServerUserCharacterInfo->CharInfo[index].StartField;

			DownUserCharacterInfo[index].PosX = ServerUserCharacterInfo->CharInfo[index].PosX;
			DownUserCharacterInfo[index].PosZ = ServerUserCharacterInfo->CharInfo[index].PosZ;


		}
		DownUserCharacterCount = ServerUserCharacterInfo->PlayUserCount;
	}
	else if (dwCode == smTRANSCODE_SERVER_INFO)
	{
		DownServerListInfo = (PacketServerList *)RecvBuff;

		memset(UserServerListInfo, 0, sizeof(UserServerListInfo));
		UserServerListInfoCount = 0;

		lstrcpy(szConnServerName, DownServerListInfo->sHeader.szServerName);

		for (int index = 0; index < DownServerListInfo->sHeader.iGameServers; index++)
		{
			STRINGCOPY(UserServerListInfo[index].szServerName, DownServerListInfo->sServers[index].szName);
			STRINGCOPY(UserServerListInfo[index].szServerIp1, DownServerListInfo->sServers[index].szaIP[0]);
			STRINGCOPY(UserServerListInfo[index].szServerIp2, DownServerListInfo->sServers[index].szaIP[1]);
			STRINGCOPY(UserServerListInfo[index].szServerIp3, DownServerListInfo->sServers[index].szaIP[2]);

			UserServerListInfo[index].dwServerPort1 = DownServerListInfo->sServers[index].iaPort[0];
			UserServerListInfo[index].dwServerPort2 = DownServerListInfo->sServers[index].iaPort[1];
			UserServerListInfo[index].dwServerPort3 = DownServerListInfo->sServers[index].iaPort[2];

			UserServerListInfoCount++;
		}
	}
	else if (dwCode == smTRANSCODE_FAILCONNECT)
		ServerLoginError = (smTRANS_COMMAND *)RecvBuff;
	else
		ServerReturn = (smTRANS_CHAR_COMMAND2 *)RecvBuff;

	return TRUE;
}
// НиЭМ
void Capture()
{
	struct tm Tm;
	DWORD st = GetPlayTime_T();
	gmtime_s(&Tm, (time_t*)&st);

	int x = 0;

	const char *pszBuffer = nullptr;

	pszBuffer = FormatString("[Server Time]:%d-%d-%d %02d:%02d:%02d", Tm.tm_year + 1900, Tm.tm_mon + 1, Tm.tm_mday, (Tm.tm_hour + dwTime_ServerGMT) % 24, Tm.tm_min, Tm.tm_sec);

	x = ((int)RESOLUTION_WIDTH >> 1) - lstrlen(pszBuffer) * 3;

	dsTextLineOut(0, x, 35, pszBuffer, lstrlen(pszBuffer), D3DCOLOR_XRGB(255, 255, 255));

	time((time_t*)&st);

	localtime_s(&Tm, (time_t*)&st);

	pszBuffer = FormatString("[Local Time]:%d-%d-%d %02d:%02d:%02d", Tm.tm_year + 1900, Tm.tm_mon + 1, Tm.tm_mday, Tm.tm_hour, Tm.tm_min, Tm.tm_sec);

	if (x == 0)
		x = ((int)RESOLUTION_WIDTH >> 1) - lstrlen(pszBuffer) * 3;

	dsTextLineOut(0, x, 20, pszBuffer, lstrlen(pszBuffer), D3DCOLOR_XRGB(255, 255, 255));

	if (lpCurPlayer)
	{
		pszBuffer = FormatString("[%d] - %s - %s", GAME_VERSION, lpCurPlayer->sCharacterData.szName, Server_Name);

		if (x == 0)
			x = ((int)RESOLUTION_WIDTH >> 1) - lstrlen(pszBuffer) * 3;

		dsTextLineOut(0, x, 5, pszBuffer, lstrlen(pszBuffer), D3DCOLOR_XRGB(255, 255, 255));
	}

	LPDIRECT3DSURFACE9 pBackBuffer;

	pszBuffer = FormatString("Capture\\%d-%d-%d-%d-%d-%d.png", Tm.tm_year + 1900, Tm.tm_mon + 1, Tm.tm_mday, Tm.tm_hour, Tm.tm_min, Tm.tm_sec);

	if (SUCCEEDED(GRAPHICENGINE->GetDevice()->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer)))
	{
		D3DXSaveSurfaceToFile(pszBuffer, D3DXIFF_PNG, pBackBuffer, NULL, NULL);

		CHATGAMEHANDLE->AddChatBoxTextEx(CHATCOLOR_Error, "> Saved screenshot to %s", pszBuffer);
		pBackBuffer->Release();
	}
}

int GameErrorValue = -1;
int SetGameError(int num)
{
	GameErrorValue = num;
	return TRUE;
}
int DrawInterfaceParty()
{
	InterfaceParty.Draw();

	EffectHitBoard.Draw();

	return TRUE;
}

int MainInterfaceParty()
{
	InterfaceParty.Main();
	EffectHitBoard.Main();
	return TRUE;
}
int CloseInterfaceParty()
{
	InterfaceParty.Close();
	return TRUE;
}

int MainInterfaceParty(int x, int y)
{
	InterfaceParty.MainPartyMessage(x, y);
	return TRUE;
}

int DrawInterfaceParty(int x, int y)
{
	InterfaceParty.DrawPartyMessage(x, y);
	return TRUE;
}

extern int QuestnotCharMove;
extern int ClanCharMove;
extern int ClanCLCharMove;
BOOL HoStopCharMotion()
{
	if (InterfaceParty.MessageBoxOpenFlag)
	{
		if (pCursorPos.x >= 653 && pCursorPos.x <= 653 + 23 && pCursorPos.y >= 14 && pCursorPos.y <= 14 + 23)
			return TRUE;

		if (pCursorPos.x >= 653 && pCursorPos.x <= 653 + 23 && pCursorPos.y >= 41 && pCursorPos.y <= 41 + 23)
			return TRUE;
	}

	if (InterfaceParty.PartyPosState == PARTY_PROCESS)
	{
		if (600 <= pCursorPos.x  && pCursorPos.x <= 800 && pCursorPos.y >= 125 + 33 && pCursorPos.y <= 371 + 33)
			return TRUE;
	}
	if (QuestnotCharMove)
	{
		if (600 <= pCursorPos.x && pCursorPos.x <= 800 && pCursorPos.y >= 125 + 33 && pCursorPos.y <= 371 + 33)
			return TRUE;
	}
	if (ClanCharMove)
	{
		extern POINT clanBoxPos;
		if (clanBoxPos.x <= pCursorPos.x && pCursorPos.x <= (clanBoxPos.x + 64 * 5) && clanBoxPos.y <= pCursorPos.y && pCursorPos.y <= (clanBoxPos.y + 64 * 5))
			return TRUE;
	}
	if (ClanCLCharMove)
	{
		extern POINT clanCLBoxPos;
		if (clanCLBoxPos.x <= pCursorPos.x && pCursorPos.x <= (clanCLBoxPos.x + 256) && clanCLBoxPos.y <= pCursorPos.y && pCursorPos.y <= (clanCLBoxPos.y + 256))
			return TRUE;
	}
	return FALSE;
}


int hoDrawTexImageFloat(int Mat, float putX, float putY, float putSizeX, float putSizeY, float getTexX, float getTexY, float getTexSizeX, float getTexSizeY, float texSizeX, float texSizeY, int alpha)
{
	D3DTLVERTEX9 tlVertex[4];
	int cnt;

	for (cnt = 0; cnt < 4; cnt++)
	{
		tlVertex[cnt].rhw = 1;
		tlVertex[cnt].color = D3DCOLOR_RGBA(255, 255, 255, alpha);
		tlVertex[cnt].specular = D3DCOLOR_RGBA(0, 0, 0, 0);
		tlVertex[cnt].sz = 0;
	}

	float surWidth;
	float surHeight;

	surWidth = (float)texSizeX;
	surHeight = (float)texSizeY;

	tlVertex[0].sx = putX;
	tlVertex[0].sy = putY;
	tlVertex[0].tu = (1.f / surWidth)*getTexX;
	tlVertex[0].tv = (1.f / surHeight)*getTexY;

	tlVertex[1].sx = putX;
	tlVertex[1].sy = putY + putSizeY;
	tlVertex[1].tu = (1.f / surWidth)*getTexX;
	tlVertex[1].tv = (1.f / surHeight)*(getTexY + getTexSizeY);

	tlVertex[2].sx = putX + putSizeX;
	tlVertex[2].sy = putY;
	tlVertex[2].tu = (1.f / surWidth)*(getTexX + getTexSizeX);
	tlVertex[2].tv = (1.f / surHeight)*getTexY;

	tlVertex[3].sx = putX + putSizeX;
	tlVertex[3].sy = putY + putSizeY;
	tlVertex[3].tu = (1.f / surWidth)*(getTexX + getTexSizeX);
	tlVertex[3].tv = (1.f / surHeight)*(getTexY + getTexSizeY);

	psSetRenderState(0);

	if (smMaterial[Mat].smTexture[0] != NULL && smMaterial[Mat].smTexture[0]->m_pTexture != NULL)
		psDraw2DImage(smMaterial[Mat].smTexture[0]->m_pTexture, tlVertex);

	return TRUE;
}
static int CompString(char *src1, char *src2)
{
	int cnt;
	int len1, len2;
	int len;

	len1 = lstrlen(src1);
	len2 = lstrlen(src2);

	if (len1 < len2)
		len = len1;
	else
		len = len2;

	if (!len)
		return NULL;

	for (cnt = 0; cnt < len; cnt++)
	{
		if (src1[cnt] == 0 || src2[cnt] == 0)
			break;
		if (src1[cnt] != src2[cnt])
			return NULL;
	}

	return cnt;
}

int szSpaceSorting(char *lpString)
{
	int cnt, len;
	len = lstrlen(lpString);

	for (cnt = len - 1; cnt >= 0; cnt--)
	{
		if (lpString[cnt] != ' ')
		{
			lpString[cnt + 1] = 0;
			break;
		}
	}
	if (cnt < 0)
		lpString[0] = 0;

	return cnt;
}

char *CpFindString(char *lpData, char *lpFindWord, char *lpSaveBuff, int buffSize)
{
	int cnt;
	int len;
	int ep;
	int cnt2;
	char *lpsp;

	len = lstrlen(lpData);

	for (cnt = 0; cnt < len; cnt++)
	{
		ep = CompString(lpData + cnt, lpFindWord);

		if (ep)
		{
			lpsp = lpData + cnt + ep;
			for (cnt2 = 0; cnt2 < buffSize - 1; cnt2++)
			{
				if (lpsp[cnt2] == 0x0D || lpsp[cnt2] == 0x0A || lpsp[cnt2] == 0 || lpsp[cnt2] == ' ')
					break;
			}
			if (lpSaveBuff)
			{
				memcpy(lpSaveBuff, lpsp, cnt2);
				lpSaveBuff[cnt2] = 0;
				szSpaceSorting(lpSaveBuff);
			}
			return lpsp;
		}
	}
	return NULL;
}

hoCommandInfo	HoCommandInfo;
int				HoCommunity = COMMUNITY_TRIGLOW;

BOOL		HoEffectResLoadingFlag = TRUE;
void		HoSetEffectResLoading(BOOL flag)
{
	HoEffectResLoadingFlag = flag;
}

extern POINT3D	WaveCameraPosi;
extern int		WaveCameraFactor;
extern BOOL		WaveCameraFlag;
extern int		WaveCameraDelay;

extern void		EffectWaveCamera(int factor, int delay)
{
	WaveCameraFlag = TRUE;
	WaveCameraFactor = factor;
	WaveCameraDelay = delay;
}

