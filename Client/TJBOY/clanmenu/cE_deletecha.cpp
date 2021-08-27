#include "StdAfx.h"
#define CE_DELETECHA_CPP

#include "tjclanDEF.h"
#include "..\\..\\HoBaram\\HoTextFile.h"


#include "tjclan.h"
#include "cE_deletecha.h"
#include "cE_report.h"
#include "cE_CViewClanInfo.h"
#include "..\\isaocheck\\auth.h"
#include "..\\isaocheck\\isaocheck.h"
#include "..\\ygy\\ygyheader.h"



CLANEntity_deletecha::CLANEntity_deletecha()
{
	nHowDeleteChaFlag = 0;
}

CLANEntity_deletecha::~CLANEntity_deletecha()
{

}

int CLANEntity_deletecha::Init(int Life)
{
	life = Life;
	return 1;
}
void CLANEntity_deletecha::SetDeleteChaInfo(char *id, char *gserver, char *chaname)
{
	lstrcpy(cldata.szID, id);
	lstrcpy(cldata.ChaName, chaname);
	lstrcpy(cldata.gserver, gserver);
}
int CLANEntity_deletecha::Clear()
{
	return 1;
}
void CLANEntity_deletecha::Main()
{
	int i;
	switch (C_menuN)
	{
	case CLAN_DELETECHA_START:
		switch (C_menuN2)
		{
		case 0:
			ANSdata.ret_val = -1;
			nHowDeleteChaFlag = 0;

			WebDB.Resume();
			WebDB.isClanMember(cldata.szID, cldata.gserver, cldata.ChaName);
			C_menuN2 = 1;
			break;
		case 1:
			if (ANSdata.ret_val != -1)
				ANSdata.ret_val = ANSdata.ret_val;
			switch (ANSdata.ret_val)
			{
			case 4:
			case 3:
			case 0:
				WebDB.Suspend();
				bIsLoading = FALSE;
				C_menuN2 = -1;
				C_menuN = CLAN_AllEnd;
				cldata.myPosition = CLANNO_REGESTER;
				nHowDeleteChaFlag = 0;
#ifdef VOICE_CHAT
				if (bCheckClan)
					g_CtrlProcess.SetSelectCha(cldata.szID, cldata.ChaName, NULL, 0, cldata.myPosition);
#endif
				break;
			case 1:
				WebDB.Suspend();
				ParsingIsClanMember(ANSdata.ret_Buf);
				if (bFlag)
				{
					C_menuN = CLAN_DELETECHA_SECESSION_BEFORE;
					menuInit(C_menuN);
					cldata.myPosition = CLANUSER;
					nHowDeleteChaFlag = 0;
					C_menuN2 = -1;
				}
				else
				{
					C_menuN = CLAN_DIRECT_DELETE;
					menuInit(C_menuN);
					cldata.myPosition = CLANUSER;
					nHowDeleteChaFlag = 0;
					C_menuN2 = 0;
				}

#ifdef VOICE_CHAT
				if (bCheckClan)
					g_CtrlProcess.SetSelectCha(cldata.szID, cldata.ChaName, cldata.name, (DWORD)atoi(cldata.ClanMark), cldata.myPosition);
#endif
				break;
			case 2:
				WebDB.Suspend();
				C_menuN = CLAN_AllEnd;
				C_menuN2 = -1;
				nHowDeleteChaFlag = 3;
				break;
			case 100:
				WebDB.Suspend();
				C_menuN = CLAN_AllEnd;
				C_menuN2 = -1;
				nHowDeleteChaFlag = 3;
				break;
			case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				C_menuN = CLAN_AllEnd;
				C_menuN2 = -1;
				nHowDeleteChaFlag = 3;
				break;
			default:
				if (ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					bIsLoading = FALSE;
					C_menuN2 = 0;
					C_menuN = CLAN_AllEnd;
					cldata.myPosition = CLAN_NOCONNECT;
					C_menuN2 = -1;
					nHowDeleteChaFlag = 3;
				}
				break;
			}
			break;
		}
		break;
	case CLAN_DELETECHA_RELEASECLAN_BEFORE:
		switch (C_menuN2)
		{
		case 0:
			ANSdata.ret_val = -1;
			nHowDeleteChaFlag = 1;

			WebDB.Resume();
			WebDB.BreakUP_Clan(cldata.szID, cldata.gserver, cldata.ClanZang_Name, cldata.name);
			C_menuN2 = 1;
			break;
		case 1:
			switch (ANSdata.ret_val)
			{
			case 0:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				cClanReport.InitMsg(clanDeleteChaError.szMsg);
				cClanReport.menuInit(C_menuN, clanDeleteChaError.pos.x, clanDeleteChaError.pos.y);
				CLAN_ERROR_ret = 255;
				nHowDeleteChaFlag = 3;
				break;
			case 1:
				WebDB.Suspend();
				C_menuN = CLAN_DELETECHA_RELEASECLAN;
				menuInit(C_menuN);
				C_menuN2 = -1;
				nHowDeleteChaFlag = 2;
				break;
			case 100:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				cClanReport.InitMsg(clanDeleteChaError.szMsg);
				cClanReport.menuInit(C_menuN, clanDeleteChaError.pos.x, clanDeleteChaError.pos.y);
				CLAN_ERROR_ret = 255;
				nHowDeleteChaFlag = 3;
				break;
			case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				cClanReport.InitMsg(clanServerConnectErrorMsg.szMsg);
				cClanReport.menuInit(C_menuN, clanServerConnectErrorMsg.pos.x, clanServerConnectErrorMsg.pos.y);
				nHowDeleteChaFlag = 3;
				break;

			default:
				if (ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					C_menuN = CLAN_ERROR;
					cClanReport.InitMsg(clanDeleteChaError.szMsg);
					cClanReport.menuInit(C_menuN, clanDeleteChaError.pos.x, clanDeleteChaError.pos.y);
					CLAN_ERROR_ret = 255;
					C_menuN2 = -1;
					nHowDeleteChaFlag = 3;
				}
				break;
			}
			break;
		}

		i = chkeckMenuN();
		switch (i)
		{
		case 0:
			menuMouseOver[0] = 1;
			break;
		case 1:
			menuMouseOver[1] = 1;
			break;
		default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}
		if (MOUSE0())
		{
			MOUSE0() = 0;
			switch (i)
			{
			case 0:
				C_menuN2 = 0;
				break;
			case 1:
				C_menuN = CLAN_AllEnd;
				break;
			default:
				break;
			}
		}
		break;
	case CLAN_DELETECHA_RELEASECLAN:
		i = chkeckMenuN();
		switch (i)
		{
		case 0:
			menuMouseOver[0] = 1;
			break;
		default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}
		if (MOUSE0())
		{
			MOUSE0() = 0;
			switch (i)
			{
			case 0:
				C_menuN = CLAN_AllEnd;
				break;
			default:
				break;
			}
		}
		break;
	case CLAN_DIRECT_DELETE:
		switch (C_menuN2)
		{
		case 0:
			ANSdata.ret_val = -1;
			nHowDeleteChaFlag = 1;

			WebDB.Resume();

			WebDB.Secession(cldata.szID, cldata.gserver, cldata.ChaName, cldata.name);
			C_menuN2 = 1;
			break;
		case 1:
			switch (ANSdata.ret_val)
			{
			case 0:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				cClanReport.InitMsg(clanDeleteChaError.szMsg);
				cClanReport.menuInit(C_menuN, clanDeleteChaError.pos.x, clanDeleteChaError.pos.y);
				CLAN_ERROR_ret = CLAN_USER;		//클랜유저메뉴로 간다.
				C_menuN2 = -1;
				nHowDeleteChaFlag = 3;
				break;
			case 1://클랜원 탈퇴 성공
				WebDB.Suspend(); //웹db 중지
				C_menuN2 = -1;
				C_menuN = CLAN_AllEnd;		//나가기 : 끝내는걸로간다.				
				nHowDeleteChaFlag = 2;
				break;
			case 3:
				WebDB.Suspend();
				C_menuN2 = -1;
				C_menuN = CLAN_AllEnd;		//나가기 : 끝내는걸로간다.									
				nHowDeleteChaFlag = 2;
				break;
			case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				cClanReport.InitMsg(clanServerConnectErrorMsg.szMsg);
				cClanReport.menuInit(C_menuN, clanServerConnectErrorMsg.pos.x, clanServerConnectErrorMsg.pos.y);
				nHowDeleteChaFlag = 3;
				break;
			case 2:
			case 4://탈퇴하려는 자가 현재 클랜의 클랜장일 경우(오류)					
			case 100: //엉뚱한 값					
			default:
				if (ANSdata.ret_val != -1) {		//전혀엉뚱한 답이 와서 에러가 났다.
					WebDB.Suspend();

					//ygy : 살릴것
					//wsprintf(szErrorMsg, szDefaultError);
					C_menuN = CLAN_ERROR;
					cClanReport.InitMsg(clanDeleteChaError.szMsg);
					cClanReport.menuInit(C_menuN, clanDeleteChaError.pos.x, clanDeleteChaError.pos.y);
					CLAN_ERROR_ret = CLAN_USER;		//클랜유저메뉴로 간다.
					C_menuN2 = -1;
					nHowDeleteChaFlag = 3;
				}
				break;
			}
			break;
		}
		break;
	case CLAN_DELETECHA_SECESSION_BEFORE:
		switch (C_menuN2) {
		case 0:
			ANSdata.ret_val = -1;
			nHowDeleteChaFlag = 1;

			WebDB.Resume();		//웹db를 재개한다.

			WebDB.Secession(cldata.szID, cldata.gserver, cldata.ChaName, cldata.name);
			C_menuN2 = 1;
			break;
		case 1:

			switch (ANSdata.ret_val)
			{
			case 0:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				cClanReport.InitMsg(clanDeleteChaError.szMsg);
				cClanReport.menuInit(C_menuN, clanDeleteChaError.pos.x, clanDeleteChaError.pos.y);
				CLAN_ERROR_ret = CLAN_USER;		//클랜유저메뉴로 간다.
				C_menuN2 = -1;
				nHowDeleteChaFlag = 3;
				break;
			case 1:
				WebDB.Suspend();
				C_menuN = CLAN_DELETECHA_SECESSION;
				menuInit(C_menuN);
				C_menuN2 = -1;
				nHowDeleteChaFlag = 2;
				break;
			case 3:
				WebDB.Suspend();
				C_menuN = CLAN_DELETECHA_SECESSION;
				menuInit(C_menuN);
				C_menuN2 = -1;
				nHowDeleteChaFlag = 2;
				break;
			case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				cClanReport.InitMsg(clanServerConnectErrorMsg.szMsg);
				cClanReport.menuInit(C_menuN, clanServerConnectErrorMsg.pos.x, clanServerConnectErrorMsg.pos.y);
				nHowDeleteChaFlag = 3;
				break;
			case 2:
			case 4://탈퇴하려는 자가 현재 클랜의 클랜장일 경우(오류)					
			case 100: //엉뚱한 값					
			default:
				if (ANSdata.ret_val != -1)
				{
					WebDB.Suspend();

					C_menuN = CLAN_ERROR;
					cClanReport.InitMsg(clanDeleteChaError.szMsg);
					cClanReport.menuInit(C_menuN, clanDeleteChaError.pos.x, clanDeleteChaError.pos.y);
					CLAN_ERROR_ret = CLAN_USER;		//클랜유저메뉴로 간다.
					C_menuN2 = -1;
					nHowDeleteChaFlag = 3;
				}
				break;
			}
			break;
		}

		i = chkeckMenuN();
		switch (i) {
		case 0:
			menuMouseOver[0] = 1;
			break;
		case 1:
			menuMouseOver[1] = 1;
			break;
		default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}
		if (MOUSE0())
		{
			MOUSE0() = 0;
			switch (i)
			{
			case 1:
				C_menuN = CLAN_AllEnd;
				break;
			case 0:
				C_menuN2 = 0;

			default:
				break;
			}
		}
		break;


	case CLAN_DELETECHA_SECESSION:
		i = chkeckMenuN();
		switch (i)
		{
		case 0:
			menuMouseOver[0] = 1;
			break;

		default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;

		}
		if (MOUSE0())
		{
			MOUSE0() = 0;
			switch (i)
			{
			case 0:
				C_menuN = CLAN_AllEnd;
				break;
			default:
				break;
			}
		}
		break;
	}
}

void CLANEntity_deletecha::Draw()
{
	switch (C_menuN)
	{
	case CLAN_DELETECHA_RELEASECLAN_BEFORE:
		DrawSprite(menuPos[3].left, menuPos[3].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[4].left, menuPos[4].top, hButton_Box, 0, 0, 48, 23, 1);

		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		if (menuMouseOver[1] > 0)
			DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(szDeleteChaReleaseBefore, menuPos[2].left, menuPos[2].top);

		break;

	case CLAN_DELETECHA_RELEASECLAN:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);

		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(szDeleteChaReleaseFinish, menuPos[1].left, menuPos[1].top);
		break;
	case CLAN_DELETECHA_SECESSION_BEFORE:
		DrawSprite(menuPos[3].left, menuPos[3].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[4].left, menuPos[4].top, hButton_Box, 0, 0, 48, 23, 1);

		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);
		if (menuMouseOver[1] > 0)
			DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(szDeleteChaSecessionBefore, menuPos[2].left, menuPos[2].top);
		break;
	case CLAN_DELETECHA_SECESSION:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 27, 1);

		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(szDeleteChaSecessionFinish, menuPos[1].left, menuPos[1].top);
		break;
	}
}

void CLANEntity_deletecha::menuInit(int num)
{
	int bx = 0, by = 0;
	switch (num)
	{
	case CLAN_DELETECHA_RELEASECLAN_BEFORE:
		menuSu = 5;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON2_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON2_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		bx = 32;
		by = 16;

		menuPos[1].left = BackStartPos.x + BUTTON3_X;		//취소
		menuPos[1].top = BackStartPos.y + BUTTON3_Y;
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;

		menuPos[2].left = BackStartPos.x + 20;
		menuPos[2].top = BackStartPos.y + 50;
		menuPos[2].right = menuPos[2].left + 190;
		menuPos[2].bottom = menuPos[2].top + 180;

		bx = 68;
		by = 27;

		menuPos[3].left = BackStartPos.x + BUTTON2_BOX_X;		//확인 테두리 박스
		menuPos[3].top = BackStartPos.y + BUTTON2_BOX_Y;
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;

		bx = 68;
		by = 27;

		menuPos[4].left = BackStartPos.x + BUTTON3_BOX_X;		//취소 테두리 박스
		menuPos[4].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;

		break;
	case CLAN_DELETECHA_RELEASECLAN:
		menuSu = 3;

		bx = 64;
		by = 64;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		menuPos[1].left = BackStartPos.x + 70;
		menuPos[1].top = BackStartPos.y + 70;
		menuPos[1].right = menuPos[1].left + 190;
		menuPos[1].bottom = menuPos[1].top + 180;

		bx = 68;
		by = 27;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인 테두리 박스
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;
		break;
	case CLAN_DELETECHA_SECESSION_BEFORE:
		menuSu = 5;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON2_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON2_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		bx = 32;
		by = 16;

		menuPos[1].left = BackStartPos.x + BUTTON3_X;		//취소
		menuPos[1].top = BackStartPos.y + BUTTON3_Y;
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;

		menuPos[2].left = BackStartPos.x + 30;
		menuPos[2].top = BackStartPos.y + 70;
		menuPos[2].right = menuPos[2].left + 190;
		menuPos[2].bottom = menuPos[2].top + 180;

		bx = 68;
		by = 27;

		menuPos[3].left = BackStartPos.x + BUTTON2_BOX_X;		//확인 테두리 박스
		menuPos[3].top = BackStartPos.y + BUTTON2_BOX_Y;
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;

		bx = 68;
		by = 27;

		menuPos[4].left = BackStartPos.x + BUTTON3_BOX_X;		//취소 테두리 박스
		menuPos[4].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;

		break;
	case CLAN_DELETECHA_SECESSION:
		menuSu = 3;

		bx = 64;
		by = 64;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		menuPos[1].left = BackStartPos.x + 70;
		menuPos[1].top = BackStartPos.y + 70;
		menuPos[1].right = menuPos[1].left + 190;
		menuPos[1].bottom = menuPos[1].top + 180;

		bx = 68;
		by = 27;


		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인 테두리 박스
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;
		break;
	}
}