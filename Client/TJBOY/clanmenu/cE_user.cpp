#include "StdAfx.h"
#define CE_USER_CPP

#include "tjclanDEF.h"

#ifdef USE_PROSTONTALE		//=========== 프리스턴소스인경우
#include "..\\..\\HoBaram\\HoTextFile.h"
#endif


#include "tjclan.h"
#include "cE_user.h"
#include "tjscroll.h"
#include "cE_report.h"
#include "cE_CViewClanInfo.h"
#include "..\\isaocheck\\auth.h"
#include "..\\isaocheck\\isaocheck.h"
#include "..\\ygy\\ygyheader.h"

//void CheckMsgPos(CLANMSG* clanmsg,int width, int height);
//*****************************************************************************
CLANEntity_user::CLANEntity_user()
{
	ZeroMemory(szTemp, sizeof(szTemp));

}

CLANEntity_user::~CLANEntity_user()
{

}


//*****************************************************************************
int CLANEntity_user::Init(int Life)
{
	life = Life;
	bSubChip = FALSE;
	ZeroMemory(szClanUserMsg, sizeof(szClanUserMsg));
	return 1;
}

int CLANEntity_user::Clear()
{
	return 1;
}


//*****************************************************************************
void CLANEntity_user::Main()
{
	int i;
	int PFlag = 0;
	if (life == 0) return;

	switch (C_menuN)
	{
		//부칩관련 메세지 처리 ============
	case CLANUSER_SUBCHIP_READMSG_FLAG:
		switch (C_menuN2) {
		case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();		//웹db를 재개한다.

			//WebDB.isKPFlag(cldata.szID,cldata.name,cldata.ChaName,cldata.gserver,"201","1");
			if (cldata.nKFlag == 4) //부칩임명만 들어 왔을때
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "8", "1");
			}
			else if (cldata.nKFlag == 16) //부칩해임만 들어 왔을때
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "32", "1");
			}
			else if (cldata.nKFlag == 5) //칩위임 부칩임명만 들어 왔을때(칩위임 확인 부칩임명확인플래그 세팅)
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "8", "1");
			}
			else if ((cldata.nKFlag == 7) && (cldata.nKFlag_Count)) //칩위임만 확인했고 부침임명확인 안했어 추가로 플래그 세팅
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "8", "1");
			}
			else if ((cldata.nKFlag == 17) && (cldata.nKFlag_Count == 1)) //칩위임 부치해임
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "32", "1");
			}
			else if ((cldata.nKFlag == 19) && (cldata.nKFlag_Count == 1)) //칩위임 부칩해임에서 칩위임만 확인했을 경우
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "32", "1");
			}
			else if ((cldata.nKFlag == 20) && (cldata.nKFlag_Count == 1) && (bSubChip == TRUE)) //부칩임명 부칩해임만 들어 왔을때(부칩해임만 확인)
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "32", "1");
			}
			else if ((cldata.nKFlag == 20) && (cldata.nKFlag_Count == 2) && (bSubChip == TRUE)) //부칩임명확인  플래그 세팅
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "8", "1");
			}
			else if ((cldata.nKFlag == 20) && (cldata.nKFlag_Count == 1) && (bSubChip == FALSE))
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "8", "1");
			}
			else if ((cldata.nKFlag == 20) && (cldata.nKFlag_Count == 2) && (bSubChip == FALSE)) //부칩임명확인  플래그 세팅
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "32", "1");
			}
			else if (cldata.nKFlag == 52) //부칩해임만 확인하여 추가로 부침임명확인 플래그 세팅
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "8", "1");
			}
			else if ((cldata.nKFlag == 21) && (cldata.nKFlag_Count == 1) && (bSubChip == TRUE)) //클랜칩 위임 부칩해임 부칩임명 들어 왔을때(칩이임확인,부칩해임 확인)
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "32", "1");
			}
			else if ((cldata.nKFlag == 21) && (cldata.nKFlag_Count == 2) && (bSubChip == TRUE)) //클랜칩 위임 부칩해임 부칩임명 들어 왔을때(칩이임확인,부칩해임 확인,부칩임명 확인)
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "8", "1");
			}
			else if ((cldata.nKFlag == 21) && (cldata.nKFlag_Count == 1) && (bSubChip == FALSE))
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "8", "1");
			}
			else if ((cldata.nKFlag == 21) && (cldata.nKFlag_Count == 2) && (bSubChip == FALSE)) //클랜칩 위임 부칩해임 부칩임명 들어 왔을때(칩이임확인,부칩해임 확인,부칩임명 확인)
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "32", "1");
			}
			else if ((cldata.nKFlag == 23) && (cldata.nKFlag_Count == 1)) //클랜칩 위임 부칩해임 부칩임명 에서 클랜칩 확인만 했을 경우
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "32", "1");
			}
			else if ((cldata.nKFlag == 23) && (cldata.nKFlag_Count == 2))//클랜칩위임 부칩해임 부칩임명에서 마지막 부칩임명 확인
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "8", "1");
			}
			else if (cldata.nKFlag == 55) //클랜칩위임 부칩해임 부칩임명에서 클랜칩위임 부침해임만 확인하였을 경우
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "8", "1");
			}
			else if (cldata.nKFlag == 28) //부칩해임 확인 플래그세팅
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "32", "1");
			}
			C_menuN2 = 1;
			break;
		case 1:
			switch (ANSdata.ret_val)
			{
			case 0:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (84)", clanszError_Msg.szMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				cClanReport.InitMsg(szErrorMsg);
				C_menuN2 = -1;
				break;
			case 1:
				WebDB.Suspend();
				C_menuN2 = -1;

				if ((cldata.nKFlag == 20) && (cldata.nKFlag_Count == 1))
				{
					cldata.nKFlag_Count = 2;
					if (bSubChip == TRUE)	C_menuN = CLANUSER_SUBCHIP_APPOINTMSG;
					else C_menuN = CLANUSER_SUBCHIP_RELEASEMSG;
					menuInit(C_menuN);
					break;
				}
				else if ((cldata.nKFlag == 21) && (cldata.nKFlag_Count == 1))
				{
					cldata.nKFlag_Count = 2;
					if (bSubChip == TRUE)	C_menuN = CLANUSER_SUBCHIP_APPOINTMSG;
					else C_menuN = CLANUSER_SUBCHIP_RELEASEMSG;
					menuInit(C_menuN);
					break;
				}
				else if ((cldata.nKFlag == 23) && (cldata.nKFlag_Count == 1))
				{
					cldata.nKFlag_Count = 2;
					C_menuN = CLANUSER_SUBCHIP_APPOINTMSG;
					menuInit(C_menuN);
					break;
				}
				if ((cldata.nKFlag == 4) ||
					(cldata.nKFlag == 16) ||
					(cldata.nKFlag == 17) ||
					(cldata.nKFlag == 19) ||
					(cldata.nKFlag == 5) ||
					(cldata.nKFlag == 7) ||
					(cldata.nKFlag == 52) ||
					((cldata.nKFlag == 23) && (cldata.nKFlag_Count == 2)) ||
					((cldata.nKFlag == 21) && (cldata.nKFlag_Count == 2)) ||
					(cldata.nKFlag == 55))
				{
					cldata.nKFlag_Count = 0;
				}
				if ((strcmp(cldata.stats, "0") == 0) && (strcmp(cldata.PFlag, "0") == 0))
				{
					C_menuN = CLAN_USER_NOMAKE;
					menuInit(C_menuN);
					C_menuN2 = -1;
				}
				else if ((strcmp(cldata.stats, "1") == 0) && (strcmp(cldata.PFlag, "0") == 0))
				{
					lstrcpy(cldata.PFlag, "2");
					wsprintf(string, clanMakeFinishClanWon.szMsg, cldata.name);
					lstrcpy(clanMakeFinishClanWon.szMsg, string);
					CheckMsgPos(&clanMakeFinishClanWon, BOX_MAX_WIDTH, 0);
					C_menuN = CLANUSER_MAKE_FIRSTMESSAGE;

					menuInit(C_menuN);
					C_menuN2 = -1;
				}
				else if ((strcmp(cldata.stats, "1") == 0) && (strcmp(cldata.PFlag, "2") == 0) && (nClanWon_Num < 5))
				{
					C_menuN = CLANUSER_DOWN6_CLANWON_MESSAGE;
					menuInit(C_menuN);
					C_menuN2 = -1;
				}
				else
				{
					C_menuN = CLAN_USER;
					menuInit(C_menuN);
					C_menuN2 = -1;
				}

				break;
			default:
				if (ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (85)", clanszError_Msg.szMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					cClanReport.InitMsg(szErrorMsg);
					C_menuN2 = -1;
				}
				break;
			}
		}
		break;
	case CLANUSER_SUBCHIP_APPOINTMSG:
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
			i = i;
			switch (i)
			{
			case 0:
				C_menuN = CLANUSER_SUBCHIP_READMSG_FLAG;
				menuInit(C_menuN);
				C_menuN2 = 0;
				break;

			default:
				i = i;
				break;
			}
		}
		break;

	case CLANUSER_SUBCHIP_RELEASEMSG:
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
			i = i;
			switch (i)
			{
			case 0:
				C_menuN = CLANUSER_SUBCHIP_READMSG_FLAG;
				menuInit(C_menuN);
				C_menuN2 = 0;
				break;

			default:
				i = i;
				break;

			}
		}
		break;
	case CLANUSER_LEAVECLAN_MESSAGEEND:
		switch (C_menuN2)
		{
		case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();

			if ((cldata.nKFlag == 1) && (cldata.nKFlag_Count == 1))
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "2", "1");
			else if ((cldata.nKFlag == 5) && (cldata.nKFlag_Count == 1))
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "2", "1");
			else if ((cldata.nKFlag == 17) && (cldata.nKFlag_Count == 1))
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "2", "1");
			else if ((cldata.nKFlag == 21) && (cldata.nKFlag_Count == 1))
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "2", "1");

			C_menuN2 = 1;
			break;
		case 1:
			switch (ANSdata.ret_val)
			{
			case 0:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (84)", clanszError_Msg.szMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				cClanReport.InitMsg(szErrorMsg);
				C_menuN2 = -1;
				break;
			case 1:
				WebDB.Suspend();
				C_menuN2 = -1;


				if ((cldata.nKFlag == 1) && (cldata.nKFlag_Count == 1))
				{
					cldata.nKFlag_Count = 0;

				}
				else if (cldata.nKFlag == 17)
				{
					cldata.nKFlag_Count = 1;

					C_menuN = CLANUSER_SUBCHIP_RELEASEMSG;
					menuInit(C_menuN);
					break;
				}
				else if (cldata.nKFlag == 5) //부클랜칩 임명
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANUSER_SUBCHIP_APPOINTMSG;
					menuInit(C_menuN);
					break;
				}
				else if (cldata.nKFlag == 21) //부클랜칩 해임,임명
				{
					cldata.nKFlag_Count = 1;
					if (cldata.SubChip[0] == 0)
					{
						bSubChip = FALSE;
						C_menuN = CLANUSER_SUBCHIP_APPOINTMSG;
					}
					else {
						bSubChip = TRUE;
						C_menuN = CLANUSER_SUBCHIP_RELEASEMSG;
					}
					menuInit(C_menuN);
					break;
				}
				if ((strcmp(cldata.stats, "0") == 0) && (strcmp(cldata.PFlag, "0") == 0))
				{
					C_menuN = CLAN_USER_NOMAKE;
					menuInit(C_menuN);
					C_menuN2 = -1;
				}
				else if ((strcmp(cldata.stats, "1") == 0) && (strcmp(cldata.PFlag, "0") == 0))
				{
					lstrcpy(cldata.PFlag, "2");
					wsprintf(string, clanMakeFinishClanWon.szMsg, cldata.name);
					lstrcpy(clanMakeFinishClanWon.szMsg, string);
					CheckMsgPos(&clanMakeFinishClanWon, BOX_MAX_WIDTH, 0);
					C_menuN = CLANUSER_MAKE_FIRSTMESSAGE;

					menuInit(C_menuN);
					C_menuN2 = -1;
				}
				else if ((strcmp(cldata.stats, "1") == 0) && (strcmp(cldata.PFlag, "2") == 0) && (nClanWon_Num < 5))
				{
					C_menuN = CLANUSER_DOWN6_CLANWON_MESSAGE;
					menuInit(C_menuN);
					C_menuN2 = -1;
				}
				else
				{
					C_menuN = CLAN_USER;
					menuInit(C_menuN);
					C_menuN2 = -1;
				}

				break;
			default:

				if (ANSdata.ret_val != -1) {		//전혀엉뚱한 답이 와서 에러가 났다.
					WebDB.Suspend();
					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (85)", clanszError_Msg.szMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					cClanReport.InitMsg(szErrorMsg);
					C_menuN2 = -1;
				}
				break;
			}
		}
		break;
	case CLANUSER_LEAVECLAN_MESSAGE:
		i = chkeckMenuN();
		switch (i) {
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
			i = i;
			switch (i)
			{
			case 0:
				C_menuN = CLANUSER_LEAVECLAN_MESSAGEEND;
				menuInit(C_menuN);
				C_menuN2 = 0;
				break;

			default:
				i = i;
				break;

			}
		}
		break;
	case CLANUSER_REMOVE://클랜원이 추방당했을경우
		i = chkeckMenuN();
		switch (i) {
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
			i = i;
			switch (i)
			{
			case 0:
				C_menuN = CLANUSER_RELEASE_FLAG;
				menuInit(C_menuN);
				C_menuN2 = 0;
				break;
			default:
				i = i;
				break;
			}
		}
		break;

	case	CLANUSER_AUTORELEASE:
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
			i = i;
			switch (i)
			{
			case 0:
				C_menuN = CLANUSER_RELEASE_FLAG;
				menuInit(C_menuN);
				C_menuN2 = 0;
				break;
			default:
				i = i;
				break;
			}
		}

		break;
	case CLANUSER_GO_RELEASEMESSAGE:
		C_menuN = CLANUSER_RELEASEMESSAGE;
		menuInit(C_menuN);
		C_menuN2 = -1;
		break;
	case CLANUSER_CHECKPFLAG:
		PFlag = atoi(cldata.PFlag);
		if (PFlag == 101)
		{
			lstrcpy(szTemp, clanClanUserReleaseMsg.szMsg);
			wsprintf(szClanUserMsg, clanClanUserReleaseMsg.szMsg, cldata.name);
			lstrcpy(clanClanUserReleaseMsg.szMsg, szClanUserMsg);
			CheckMsgPos(&clanClanUserReleaseMsg, BOX_MAX_WIDTH, 0);
			C_menuN = CLANUSER_AUTORELEASE;
			menuInit(C_menuN);
			lstrcpy(clanClanUserReleaseMsg.szMsg, szTemp);
		}
		else if (PFlag == 102)
		{
			lstrcpy(szTemp, clanClanUserReleaseMsg.szMsg);
			wsprintf(szClanUserMsg, clanClanUserReleaseMsg.szMsg, cldata.name);
			lstrcpy(clanClanUserReleaseMsg.szMsg, szClanUserMsg);

			CheckMsgPos(&clanClanUserReleaseMsg, BOX_MAX_WIDTH, 0);

			C_menuN = CLANUSER_AUTORELEASE;
			menuInit(C_menuN);
			lstrcpy(clanClanUserReleaseMsg.szMsg, szTemp);
		}
		else if (PFlag == 110)
		{
			C_menuN = CLANUSER_REMOVE;
			menuInit(C_menuN);
		}
		else
		{
			C_menuN = CLANUSER_RELEASEMESSAGE;
			menuInit(C_menuN);
		}

		break;
	case CLANUSER_RELEASEMESSAGE:
		i = chkeckMenuN();
		switch (i) {
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
			i = i;
			switch (i)
			{
			case 0:

				C_menuN = CLANUSER_RELEASE_FLAG;
				menuInit(C_menuN);
				C_menuN2 = 0;
				break;
			default:
				break;

			}
		}
		break;
	case CLAN_USER_NOMAKE_FLAG:
		C_menuN = CLAN_USER_NOMAKE;
		menuInit(C_menuN);
		C_menuN2 = 0;
		break;
	case CLAN_USER_FLAG:
		C_menuN = CLAN_USER_ReadDATA;
		C_menuN2 = 0;
		break;
	case CLAN_USER_DATA:
		switch (C_menuN2) {
		case 0:
			C_menuN = CLAN_USER;
			menuInit(C_menuN);
			break;
		}
		break;
	case CLAN_USER:
		i = chkeckMenuN();
		memset(menuMouseOver, -1, sizeof(int) * 30);
		switch (i)
		{
		case 2:
			menuMouseOver[2] = 1;
			break;
		case 3:
			menuMouseOver[3] = 1;
			break;
		case 4:
			menuMouseOver[4] = 1;
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
			case 2:
				C_menuN = CLAN_SECESSION;
				menuInit(CLAN_SECESSION);
				C_menuN2 = -1;
				break;
			case 3:
				LoadHelp(CLANUSER_HELP);
				C_menuN = CLAN_USER_HELP_CONTENT;

				menuInit(C_menuN);
				break;
			case 4:
				C_menuN = 255;
				menuInit(C_menuN);
				C_menuN2 = -1;
				break;
			default:
				break;
			}
		}
		break;
	case CLAN_USER_NOMAKE:
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
				C_menuN = CLAN_USER;
				menuInit(C_menuN);
				break;
			default:
				break;
			}
		}

		break;

	case CLAN_USER_WAREHOUSE:
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
				C_menuN = CLAN_USER;
				menuInit(CLAN_USER);
				break;
			default:
				break;
			}
		}
		break;

	case CLAN_SECESSION:

		i = chkeckMenuN();
		switch (i) {
		case 2:
			menuMouseOver[2] = 1;
			break;
		case 3:
			menuMouseOver[3] = 1;
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
			case 3:
				C_menuN = CLAN_USER;
				menuInit(C_menuN);

				break;
			case 2:
				C_menuN = CLAN_RECONF_SECESSION;
				menuInit(C_menuN);

			default:
				break;
			}
		}
		break;
	case CLAN_RECONF_SECESSION_LOADING:
		if (ANSdata.ret_val != -1) C_menuN = CLAN_RECONF_SECESSION;
		break;
	case CLAN_RECONF_SECESSION:
		switch (C_menuN2)
		{
		case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();

			WebDB.Secession(cldata.szID, cldata.gserver, cldata.ChaName, cldata.name);
			C_menuN2 = 1;
			break;
		case 1:

			switch (ANSdata.ret_val)
			{
			case -1:
				C_menuN = CLAN_RECONF_SECESSION_LOADING;
				menuInit(C_menuN);
				break;
			case 0:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (34)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_USER;
				C_menuN2 = -1;
				break;
			case 3:
			case 1:
				WebDB.Suspend();
				cldata.myPosition = CLANNO_REGESTER;
				wsprintf(szClanUserMsg, clanFinishSecessionMsg.szMsg, cldata.name, cldata.ChaName);
				lstrcpy(clanFinishSecessionMsg.szMsg, szClanUserMsg);
				C_menuN = CLAN_FINISH_SECESSION;
				menuInit(C_menuN);
				C_menuN2 = -1;

				void SetClanWon();
				SetClanWon();

#ifdef VOICE_CHAT
				if (bCheckClan)
					g_CtrlProcess.SetSelectCha(cldata.szID, cldata.ChaName, NULL, 0, cldata.myPosition);
#endif
				break;
			case 2:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (35)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				C_menuN2 = -1;
				break;
			case 4:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (36)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = 255;
				C_menuN2 = -1;
				break;
			case 100:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (37)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = 255;
				C_menuN2 = -1;
				break;
			case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (38)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				break;
			default:
				if (ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (39)", clanszError_Msg.szMsg);
					cClanReport.InitMsg(szErrorMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					CLAN_ERROR_ret = CLAN_USER;
					C_menuN2 = -1;
				}
				break;
			}
			break;
		}

		i = chkeckMenuN();
		switch (i) {
		case 2:
			menuMouseOver[2] = 1;
			break;
		case 3:
			menuMouseOver[3] = 1;
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
			case 3:
				C_menuN = CLAN_USER;
				menuInit(C_menuN);

				break;
			case 2:
				C_menuN2 = 0;

			default:
				break;
			}
		}
		break;
	case CLAN_FINISH_SECESSION:
		i = chkeckMenuN();
		switch (i)
		{
		case 3:
			menuMouseOver[3] = 1;
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
			case 3:
				cldata.myPosition = CLANNO_REGESTER;
				ZeroMemory(cldata.name, sizeof(cldata.name));
				ZeroMemory(cldata.explanation, sizeof(cldata.explanation));
				ZeroMemory(cldata.ClanZang_Name, sizeof(cldata.ClanZang_Name));
				ZeroMemory(cldata.ClanMark, sizeof(cldata.ClanMark));
				cldata.intClanMark = 0;
				ZeroMemory(cldata.PFlag, sizeof(cldata.PFlag));
				ZeroMemory(szChatClanWon, sizeof(szChatClanWon));
#ifdef USE_PROSTONTALE
				DELET(cldata.hClanMark);
				DELET(cldata.hClanMark16);
#endif
				C_menuN = CLAN_AllEnd;;
				menuInit(C_menuN);
				break;
			default:
				break;
			}
		}
	case CLAN_USER_HELP:
		i = chkeckMenuN();
		switch (i) {
		case 0:
			menuMouseOver[0] = 1;
			break;
		case 2:
			menuMouseOver[2] = 1;
			break;
		case 3:
			menuMouseOver[3] = 1;
			break;
		case 4:
			menuMouseOver[4] = 1;
			break;
		case 5:
			menuMouseOver[5] = 1;
			break;
		default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}
		if (MOUSE0())
		{
			switch (i)
			{
			case 0:
				DestroyClanHelpIcon();
				C_menuN = CLAN_USER;
				menuInit(C_menuN);
				MOUSE0() = 0;
				break;
			case 2:
			case 3:
			case 4:
			case 5:
				LoadHelp(ClanHelpIcon[i + nScl_Bar - 2].TextFilePath);
				C_menuN = CLAN_USER_HELP_CONTENT;
				menuInit(C_menuN);
				MOUSE0() = 0;
				break;
			case 6:
				nScl_Bar = tscr.topScrollLineNum(pCursorPos.y);
				scrIconPos.top = pCursorPos.y - 8;
				break;
			default:
				MOUSE0() = 0;
				break;
			}
		}
		break;
	case CLAN_USER_HELP_CONTENT:
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
		if (TJwheel != 0)
		{
			scrIconPos.top = tscr.ret_WHEELpoint(TJwheel, scrIconPos.top);
			nScl_Bar = tscr.topScrollLineNum(scrIconPos.top);
			TJwheel = 0;
		}
		if (MOUSE0())
		{
			switch (i)
			{
			case 0:
				C_menuN = CLAN_USER;
				menuInit(C_menuN);
				MOUSE0() = 0;
				tscr.Init(0);

				break;
			case 5:
				nScl_Bar = tscr.topScrollLineNum(pCursorPos.y);
				scrIconPos.top = pCursorPos.y - 8;
				break;
			default:
				MOUSE0() = 0;
				break;
			}
		}
		break;

	case CLANUSER_RELEASE_FLAG:
		switch (C_menuN2) {
		case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();
			WebDB.isPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "100", "1");
			C_menuN2 = 1;
			break;
		case 1:
			switch (ANSdata.ret_val)
			{
			case 0:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (40)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);

				C_menuN2 = -1;
				break;
			case 1:

				WebDB.Suspend();
				C_menuN2 = -1;
				C_menuN = CLAN_AllEnd;

				break;
			default:
				if (ANSdata.ret_val != -1) {		//전혀엉뚱한 답이 와서 에러가 났다.
					WebDB.Suspend();
					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (41)", clanszError_Msg.szMsg);
					cClanReport.InitMsg(szErrorMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					C_menuN2 = -1;
				}
				break;
			}
		}
		break;
	case ISPFLAG_USER:
		switch (C_menuN2)
		{
		case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();
			WebDB.isPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, cldata.PFlag, "1");
			C_menuN2 = 1;
			break;
		case 1:
			switch (ANSdata.ret_val)
			{
			case 0:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (42)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				C_menuN2 = -1;
				break;
			case 1:
				WebDB.Suspend();
				C_menuN2 = -1;
				C_menuN = CLAN_USER;
				menuInit(C_menuN);
				break;
			default:
				if (ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					C_menuN2 = -1;
					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (43)", clanszError_Msg.szMsg);
					cClanReport.InitMsg(szErrorMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				}
				break;
			}
		}
		break;
	case CLANUSER_MAKE_FIRSTMESSAGE:
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
				C_menuN = ISPFLAG_USER;
				menuInit(C_menuN);
				C_menuN2 = 0;
				break;
			default:
				break;
			}
		}
		break;
	case CLANUSER_DOWN6_CLANWON_MESSAGE:
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
				C_menuN = CLAN_USER;
				menuInit(C_menuN);
				C_menuN2 = 0;
				break;
			default:
				break;
			}
		}
		break;

	case CLANUSER_DOWN6_CLANWON:
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
				C_menuN = ISPFLAG_USER;
				menuInit(C_menuN);
				C_menuN2 = 0;
				break;
			default:
				break;
			}
		}
		break;

	case CLAN_USER_ReadDATA:

		switch (C_menuN2)
		{
		case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();
			WebDB.ReadClan(cldata.szID, cldata.gserver, cldata.ClanZang_Name);
			C_menuN2 = 1;
			break;
		case 1:

			if (ANSdata.ret_val != -1)
				ANSdata.ret_val = ANSdata.ret_val;

			switch (ANSdata.ret_val)
			{
			case 0:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (44)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);

				CLAN_ERROR_ret = 255;		//에러메뉴보여준후그냥끝낸다.
				C_menuN2 = -1;
				break;
			case 1:
				WebDB.Suspend();
				ParsigClanWon(ANSdata.ret_Buf);
				if (cldata.nKFlag == 1)
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANUSER_LEAVECLAN_MESSAGE;
					menuInit(C_menuN);
					break;
				}
				else if (cldata.nKFlag == 16)
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANUSER_SUBCHIP_RELEASEMSG;

					menuInit(C_menuN);
					break;
				}
				else if (cldata.nKFlag == 4)
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANUSER_SUBCHIP_APPOINTMSG;
					menuInit(C_menuN);
					break;
				}
				else if (cldata.nKFlag == 17)
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANUSER_LEAVECLAN_MESSAGE;
					menuInit(C_menuN);
					break;
				}
				else if (cldata.nKFlag == 19)
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANUSER_SUBCHIP_RELEASEMSG;
					menuInit(C_menuN);
					break;
				}
				else if (cldata.nKFlag == 5)
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANUSER_LEAVECLAN_MESSAGE;
					menuInit(C_menuN);
					break;
				}
				else if (cldata.nKFlag == 7)
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANUSER_SUBCHIP_APPOINTMSG;
					menuInit(C_menuN);
					break;
				}
				else if (cldata.nKFlag == 20)
				{
					if (cldata.SubChip[0] == 0)
					{
						bSubChip = FALSE;
						cldata.nKFlag_Count = 1;
						C_menuN = CLANUSER_SUBCHIP_APPOINTMSG;
						menuInit(C_menuN);
					}
					else
					{
						bSubChip = TRUE;
						cldata.nKFlag_Count = 1;
						C_menuN = CLANUSER_SUBCHIP_RELEASEMSG;
						menuInit(C_menuN);
					}
					break;
				}
				else if (cldata.nKFlag == 28)
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANUSER_SUBCHIP_RELEASEMSG;
					menuInit(C_menuN);
					break;
				}
				else if (cldata.nKFlag == 52)
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANUSER_SUBCHIP_APPOINTMSG;
					menuInit(C_menuN);
					break;
				}
				else if (cldata.nKFlag == 21)
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANUSER_LEAVECLAN_MESSAGE;
					menuInit(C_menuN);
					break;
				}
				else if (cldata.nKFlag == 23)
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANUSER_SUBCHIP_RELEASEMSG;
					menuInit(C_menuN);
					break;
				}
				else if (cldata.nKFlag == 55)
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANUSER_SUBCHIP_APPOINTMSG;
					menuInit(C_menuN);
					break;
				}

				if ((lstrcmp(cldata.stats, "0") == 0) && (lstrcmp(cldata.PFlag, "0") == 0))
				{
					C_menuN = CLAN_USER_NOMAKE;
					menuInit(C_menuN);
					C_menuN2 = -1;
				}
				else if ((lstrcmp(cldata.stats, "1") == 0) && (lstrcmp(cldata.PFlag, "0") == 0))
				{
					lstrcpy(cldata.PFlag, "2");
					wsprintf(string, clanMakeFinishClanWon.szMsg, cldata.name);
					lstrcpy(clanMakeFinishClanWon.szMsg, string);
					CheckMsgPos(&clanMakeFinishClanWon, BOX_MAX_WIDTH, 0);
					C_menuN = CLANUSER_MAKE_FIRSTMESSAGE;

					menuInit(C_menuN);
					C_menuN2 = -1;
				}
				else if ((strcmp(cldata.stats, "1") == 0) && (strcmp(cldata.PFlag, "2") == 0) && (nClanWon_Num < 5))
				{
					C_menuN = CLANUSER_DOWN6_CLANWON_MESSAGE;
					menuInit(C_menuN);
					C_menuN2 = -1;
				}
				else
				{
					C_menuN = CLAN_USER;
					menuInit(C_menuN);
					C_menuN2 = -1;
				}
				break;
			case 100:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (45)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;
				C_menuN2 = -1;
				break;
			case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (46)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				break;

			default:
				if (ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					C_menuN = CLAN_AllEnd;
					menuInit(C_menuN);

					C_menuN2 = -1;
				}
				break;
			}
			break;
		}
	}
}
void CLANEntity_user::RenderMain()
{
	if (life == 0) return;

}
void CLANEntity_user::menuInit(int num)
{
	int bx = 0, by = 0;
	int      nNext = 0, i, nIconCount = 0, nIconPos = 0, nAdd = 0, nWidth = 0;
	int      nFirstIconSave = 0;

	switch (num)
	{
	case CLANUSER_SUBCHIP_APPOINTMSG:
		menuSu = 3;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		menuPos[1].left = BackStartPos.x + SubChipAppointEnd.pos.x;
		menuPos[1].top = BackStartPos.y + SubChipAppointEnd.pos.y;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		break;

	case CLANUSER_SUBCHIP_RELEASEMSG:
		menuSu = 3;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		menuPos[1].left = BackStartPos.x + SubChipReleaseEnd.pos.x;
		menuPos[1].top = BackStartPos.y + SubChipReleaseEnd.pos.y;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		break;

	case CLANUSER_LEAVECLAN_MESSAGE:
		menuSu = 3;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		menuPos[1].left = BackStartPos.x + LeaveClanMessage.pos.x;
		menuPos[1].top = BackStartPos.y + LeaveClanMessage.pos.y;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		break;

	case	CLANUSER_AUTORELEASE:
		menuSu = 3;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;


		menuPos[1].left = BackStartPos.x + 55;
		menuPos[1].top = BackStartPos.y + 70;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;
		break;
	case CLANUSER_REMOVE:
		menuSu = 3;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		menuPos[1].left = BackStartPos.x + clanClanUserRemove.pos.x;
		menuPos[1].top = BackStartPos.y + clanClanUserRemove.pos.y;

		bx = 48;
		by = 23;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;
		break;
	case CLAN_USER:
		menuSu = 13;

		if (hMark == NULL)
			hMark = GetClanMark();

		bx = 208;
		by = 29;

		menuPos[0].left = BackStartPos.x + CLANNAME_X;		//클랜 이름
		menuPos[0].top = BackStartPos.y + CLANNAME_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		bx = 69;
		by = 59;

		menuPos[1].left = BackStartPos.x + CLANMARKBOX_X;		//마크
		menuPos[1].top = BackStartPos.y + CLANMARKBOX_Y;
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;

		bx = 32;
		by = 32;

		menuPos[6].left = BackStartPos.x + CLANMARK_X;		//마크
		menuPos[6].top = BackStartPos.y + CLANMARK_Y;
		menuPos[6].right = menuPos[6].left + bx;
		menuPos[6].bottom = menuPos[6].top + by;

		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;

		menuPos[2].left = BackStartPos.x + CLANUSER_SECESSION_X;		//탈퇴
		menuPos[2].top = BackStartPos.y + CLANUSER_SECESSION_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;

		menuPos[3].left = BackStartPos.x + CLANUSER_HELP_X;		//도움말
		menuPos[3].top = BackStartPos.y + CLANUSER_HELP_Y;//180;
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;

		bx = 32;
		by = 16;

		menuPos[4].left = BackStartPos.x + BUTTON1_X;		//나가기
		menuPos[4].top = BackStartPos.y + BUTTON1_Y;
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;

		bx = 64;
		by = 16;

		menuPos[5].left = BackStartPos.x + BUTTON1_BOX_X;		//나가기 테드리 박스
		menuPos[5].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[5].right = menuPos[5].left + bx;
		menuPos[5].bottom = menuPos[5].top + by;

		bx = 64;
		by = 16;

		menuPos[7].left = BackStartPos.x + CLANNAMETEXT_X;		//클랜이름
		menuPos[7].top = BackStartPos.y + CLANNAMETEXT_Y;
		menuPos[7].right = 0;
		menuPos[7].bottom = 0;

		bx = 30;
		by = 30;

		menuPos[8].left = BackStartPos.x + 75;		//탈퇴 왼쪽
		menuPos[8].top = BackStartPos.y + 105;
		menuPos[8].right = menuPos[8].left + bx;
		menuPos[8].bottom = menuPos[8].top + by;

		bx = 30;
		by = 30;

		menuPos[9].left = BackStartPos.x + 216;		//탈퇴 오른쪽
		menuPos[9].top = BackStartPos.y + 105;
		menuPos[9].right = menuPos[9].left + bx;
		menuPos[9].bottom = menuPos[9].top + by;

		bx = 30;
		by = 30;

		menuPos[10].left = BackStartPos.x + 75;		//탈퇴 오른쪽
		menuPos[10].top = BackStartPos.y + 155;
		menuPos[10].right = menuPos[10].left + bx;
		menuPos[10].bottom = menuPos[10].top + by;

		bx = 30;
		by = 30;

		menuPos[11].left = BackStartPos.x + 216;		//탈퇴 오른쪽
		menuPos[11].top = BackStartPos.y + 155;
		menuPos[11].right = menuPos[11].left + bx;
		menuPos[11].bottom = menuPos[11].top + by;

		bx = 30;
		by = 30;


		menuPos[12].left = BackStartPos.x + 9;		//탈퇴 오른쪽
		menuPos[12].top = BackStartPos.y + 109;
		menuPos[12].right = menuPos[11].left + bx;
		menuPos[12].bottom = menuPos[11].top + by;

		break;
	case CLANUSER_MAKE_FIRSTMESSAGE:
		menuSu = 3;

		bx = 64;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		menuPos[1].left = BackStartPos.x + clanMakeFinishClanWon.pos.x;
		menuPos[1].top = BackStartPos.y + clanMakeFinishClanWon.pos.y;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인 테두리
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		break;
	case CLANUSER_DOWN6_CLANWON_MESSAGE:
	case CLANUSER_DOWN6_CLANWON:
		menuSu = 3;

		bx = 64;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		menuPos[1].left = BackStartPos.x + CLANUSERTEXT_X;
		menuPos[1].top = BackStartPos.y + CLANUSERTEXT_Y;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인 테두리
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;
		break;
	case CLAN_USER_NOMAKE:
		menuSu = 3;

		bx = 64;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		menuPos[1].left = BackStartPos.x + clanClanUserNoMakeMsg.pos.x;
		menuPos[1].top = BackStartPos.y + clanClanUserNoMakeMsg.pos.y;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인 테두리
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;
		break;

	case CLAN_SECESSION:
		menuSu = 4;

		if (hMark == NULL)
			hMark = GetClanMark();

		bx = 64;
		by = 16;

		menuPos[0].left = BackStartPos.x + CLANNAME_X;		//클랜 이름
		menuPos[0].top = BackStartPos.y + CLANNAME_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		bx = 16;
		by = 16;

		menuPos[1].left = BackStartPos.x + CLANMARKBOX_X;		//마크
		menuPos[1].top = BackStartPos.y + CLANMARKBOX_Y;
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;

		bx = 16;
		by = 16;

		menuPos[7].left = BackStartPos.x + CLANMARK_X;		//마크
		menuPos[7].top = BackStartPos.y + CLANMARK_Y;
		menuPos[7].right = menuPos[7].left + bx;
		menuPos[7].bottom = menuPos[7].top + by;

		bx = 32;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON2_X;		//취소
		menuPos[2].top = BackStartPos.y + BUTTON2_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		bx = 32;
		by = 16;

		menuPos[3].left = BackStartPos.x + BUTTON3_X;		//확인 
		menuPos[3].top = BackStartPos.y + BUTTON3_Y;
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;

		bx = 64;
		by = 16;

		menuPos[4].left = BackStartPos.x + BUTTON2_BOX_X;		//취소 테드리 박스
		menuPos[4].top = BackStartPos.y + BUTTON2_BOX_Y;
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;

		bx = 64;
		by = 16;

		menuPos[5].left = BackStartPos.x + BUTTON3_BOX_X;		//확인 테드리 박스
		menuPos[5].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[5].right = menuPos[6].left + bx;
		menuPos[5].bottom = menuPos[6].top + by;

		menuPos[6].left = BackStartPos.x + clanSecession.pos.x;		//지문
		menuPos[6].top = BackStartPos.y + 130;
		menuPos[6].right = menuPos[2].left + 200;
		menuPos[6].bottom = menuPos[2].top + 40;

		menuPos[8].left = BackStartPos.x + CLANNAMETEXT_X;		//클랜이름
		menuPos[8].top = BackStartPos.y + CLANNAMETEXT_Y;
		menuPos[8].right = 0;//menuPos[2].left + 200;
		menuPos[8].bottom = 0;//menuPos[2].top + 40;
		break;
	case CLAN_RECONF_SECESSION:
		menuSu = 4;

		bx = 64;
		by = 16;

		menuPos[0].left = BackStartPos.x + CLANNAME_X;		//클랜 이름
		menuPos[0].top = BackStartPos.y + CLANNAME_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		bx = 16;
		by = 16;

		menuPos[1].left = BackStartPos.x + CLANMARKBOX_X;		//마크
		menuPos[1].top = BackStartPos.y + CLANMARKBOX_Y;
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;

		bx = 16;
		by = 16;

		menuPos[7].left = BackStartPos.x + CLANMARK_X;		//마크
		menuPos[7].top = BackStartPos.y + CLANMARK_Y;
		menuPos[7].right = menuPos[7].left + bx;
		menuPos[7].bottom = menuPos[7].top + by;

		bx = 32;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON2_X;		//취소
		menuPos[2].top = BackStartPos.y + BUTTON2_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		bx = 32;
		by = 16;

		menuPos[3].left = BackStartPos.x + BUTTON3_X;		//확인 
		menuPos[3].top = BackStartPos.y + BUTTON3_Y;
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;

		bx = 64;
		by = 16;

		menuPos[4].left = BackStartPos.x + BUTTON2_BOX_X;		//취소 테드리 박스
		menuPos[4].top = BackStartPos.y + BUTTON2_BOX_Y;
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;

		bx = 64;
		by = 16;


		menuPos[5].left = BackStartPos.x + BUTTON3_BOX_X;		//확인 테드리 박스
		menuPos[5].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[5].right = menuPos[6].left + bx;
		menuPos[5].bottom = menuPos[6].top + by;

		menuPos[6].left = BackStartPos.x + clanSecessionMsg.pos.x;		//지문
		menuPos[6].top = BackStartPos.y + 130;
		menuPos[6].right = menuPos[2].left + 200;
		menuPos[6].bottom = menuPos[2].top + 40;

		menuPos[8].left = BackStartPos.x + CLANNAMETEXT_X;		//클랜이름
		menuPos[8].top = BackStartPos.y + CLANNAMETEXT_Y;
		menuPos[8].right = 0;//menuPos[2].left + 200;
		menuPos[8].bottom = 0;//menuPos[2].top + 40;

		break;
	case CLAN_FINISH_SECESSION:
		menuSu = 6;

		bx = 64;
		by = 16;

		menuPos[0].left = BackStartPos.x + CLANNAME_X;		//클랜 이름
		menuPos[0].top = BackStartPos.y + CLANNAME_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		bx = 16;
		by = 16;

		menuPos[1].left = BackStartPos.x + CLANMARKBOX_X;		//마크
		menuPos[1].top = BackStartPos.y + CLANMARKBOX_Y;
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;

		bx = 16;
		by = 16;

		menuPos[2].left = BackStartPos.x + CLANMARK_X;		//마크
		menuPos[2].top = BackStartPos.y + CLANMARK_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		bx = 32;
		by = 16;


		menuPos[3].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[3].top = BackStartPos.y + BUTTON1_Y;
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;

		bx = 64;
		by = 16;

		menuPos[4].left = BackStartPos.x + BUTTON1_BOX_X;		//확인 테드리 박스
		menuPos[4].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;

		menuPos[5].left = BackStartPos.x + clanFinishSecessionMsg.pos.x;
		menuPos[5].top = BackStartPos.y + 130;
		menuPos[5].right = 0;
		menuPos[5].bottom = 0;

		menuPos[6].left = BackStartPos.x + CLANNAMETEXT_X;		//클랜이름
		menuPos[6].top = BackStartPos.y + CLANNAMETEXT_Y;
		menuPos[6].right = 0;//menuPos[2].left + 200;
		menuPos[6].bottom = 0;//menuPos[2].top + 40;

		break;


		//클랜 유저 창고
	case CLAN_USER_WAREHOUSE:
		menuSu = 3;

		bx = 64;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON3_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON3_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		bx = 64;
		by = 16;

		menuPos[1].left = BackStartPos.x + BUTTON3_BOX_X;		//확인
		menuPos[1].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;


		menuPos[2].left = BackStartPos.x + 50;		//지문
		menuPos[2].top = BackStartPos.y + 70;
		menuPos[2].right = menuPos[2].left + 200;
		menuPos[2].bottom = menuPos[2].top + 40;
		break;
	case CLAN_USER_HELP:
		menuSu = 2 + CLANHELPICON_DISPLAY_MAX + 3;

		nScl_Bar = 0;

		bx = 64;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		bx = 64;
		by = 16;

		menuPos[1].left = BackStartPos.x + BUTTON1_BOX_X;		//확인 테두리
		menuPos[1].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;

		nIconPos = 2;
		nAdd = 0;
		for (i = 0; i < CLANHELPICON_DISPLAY_MAX; i++)
		{
			bx = CLANTEXT_IMAGE_WIDTH;
			by = CLANTEXT_IMAGE_HEIGHT;

			menuPos[nIconPos].left = BackStartPos.x + CLANHELPLIST_X;
			menuPos[nIconPos].top = BackStartPos.y + CLANHELPLIST_Y + nAdd;//BackStartPos.y +  CLANHELPICON_START_Y+nAdd+nWidth;
			menuPos[nIconPos].right = menuPos[nIconPos].left + CLANHELPICON_WIDTH;
			menuPos[nIconPos].bottom = menuPos[nIconPos].top + CLANHELPICON_HEIGHT;
			nIconPos += 1;
			nAdd += CLANHELPICON_CAP;

		}
		nIconPos = 6;

		tscr.Init(0);

		if (g_nClanIconNum > CLANHELPICON_DISPLAY_MAX)
		{
			bx = 16;
			by = 16;

			menuPos[nIconPos].left = BackStartPos.x + SCROLLBAR_LEFT;
			menuPos[nIconPos].top = BackStartPos.y + SCROOBAR_TOP;
			menuPos[nIconPos].right = menuPos[nIconPos].left + 8;
			menuPos[nIconPos].bottom = menuPos[nIconPos].top + 160;

			tscr.Init(1);
			tscr.Init(menuPos[nIconPos].top, menuPos[nIconPos].top + 160, g_nClanIconNum, CLANHELPICON_DISPLAY_MAX);


			scrIconPos.left = BackStartPos.x + SCROLLBAR_LEFT - 4;

			scrIconPos.top = menuPos[nIconPos].top - 8;
		}
		nIconPos += 1;

		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;

		menuPos[nIconPos].left = BackStartPos.x + CLANTEXT_IMAGE_X;
		menuPos[nIconPos].top = BackStartPos.y + CLANTEXT_IMAGE_Y;
		menuPos[nIconPos].right = menuPos[nIconPos].left + bx;
		menuPos[nIconPos].bottom = menuPos[nIconPos].top + by;
		break;
	case CLAN_USER_HELP_CONTENT:
		menuSu = 1 + HLEPDISPLAY_MAX + 4;

		nScl_Bar = 0;

		bx = 64;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		bx = 64;
		by = 16;

		menuPos[1].left = BackStartPos.x + BUTTON1_BOX_X;		//확인 테두리
		menuPos[1].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;

		bx = 120;
		by = 30;

		menuPos[2].left = BackStartPos.x + CLANTITLE_X;		//헬프 마크
		menuPos[2].top = BackStartPos.y + CLANTITLE_Y;//CLANHELPCONTENT_MARK_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		bx = 30;
		by = 30;


		menuPos[3].left = BackStartPos.x + 14;
		menuPos[3].top = BackStartPos.y + 12;
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;

		menuPos[4].left = BackStartPos.x + 9;
		menuPos[4].top = BackStartPos.y + 45;
		menuPos[4].right = menuPos[3].left + bx;
		menuPos[4].bottom = menuPos[3].top + by;

		nIconPos = 5;

		//================스크롤 바

		if (g_HelpDisPlay > HLEPDISPLAY_MAX)
		{
			bx = 16;
			by = 16;


			menuPos[nIconPos].left = BackStartPos.x + SCROLLBAR_LEFT;//SCROLLBAR_LEFT;
			menuPos[nIconPos].top = BackStartPos.y + SCROOBAR_TOP;//BackStartPos.y + SCROOBAR_TOP;
			menuPos[nIconPos].right = menuPos[nIconPos].left + 8;
			menuPos[nIconPos].bottom = menuPos[nIconPos].top + 160;

			tscr.Init(1);
			tscr.Init(menuPos[nIconPos].top, menuPos[nIconPos].top + 160, g_HelpDisPlay, HLEPDISPLAY_MAX);
			scrIconPos.left = BackStartPos.x + SCROLLBAR_LEFT - 5;//SCROLLBAR_LEFT-4;

			scrIconPos.top = menuPos[nIconPos].top - 8;//(BackStartPos.y + SCROOBAR_TOP)-8;
		}


		nIconPos = 7;
		nAdd = 0;
		for (i = 0; i < HLEPDISPLAY_MAX; i++)
		{
			bx = 64;
			by = 16;

			menuPos[nIconPos].left = BackStartPos.x + HELPCONTENT_X;
			menuPos[nIconPos].top = BackStartPos.y + HELPCONTENT_Y + nAdd;
			menuPos[nIconPos].right = 0;
			menuPos[nIconPos].bottom = 0;
			nIconPos += 1;
			nAdd += HELPCONTENT_CAP;
		}

		break;
	case CLANUSER_RELEASEMESSAGE:
		menuSu = 3;

		bx = 64;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		//텍스트 출력 위치
		menuPos[1].left = BackStartPos.x + 55;
		menuPos[1].top = BackStartPos.y + 70;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;
		break;
	case CLANUSER_SUBCHIP_READMSG_FLAG:
	case ISPFLAG_USER:
	case CLAN_USER_ReadDATA:
	case CLAN_RECONF_SECESSION_LOADING:

		menuPos[0].left = BackStartPos.x + clanLoading.pos.x;
		menuPos[0].top = BackStartPos.y + clanLoading.pos.y;
		menuPos[0].right = 0;
		menuPos[0].bottom = 0;
		break;
	}
}



void CLANEntity_user::Draw()
{
	int i = 0, nIconCount = 0;
	int nIconPos = 0;
	int nSaveTop = 0, nAdd = 0;
	int nStrLen = 0;
	char szDrawMenuMsg[2024];
	ZeroMemory(szDrawMenuMsg, sizeof(char) * 2024);

	char szHelpContent[HELPWIDTH];

	switch (C_menuN)
	{
	case CLANUSER_SUBCHIP_APPOINTMSG:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);

		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);


		if (cldata.SubChip[0] == 0)
			wsprintf(szClanUserMsg, SubChipAppointEnd.szMsg, cldata.OldSubChip);
		else
			wsprintf(szClanUserMsg, SubChipAppointEnd.szMsg, cldata.SubChip);

		Draw_C_Text(szClanUserMsg, menuPos[1].left, menuPos[1].top);
		break;
	case CLANUSER_SUBCHIP_RELEASEMSG:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);

		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		wsprintf(szClanUserMsg, SubChipReleaseEnd.szMsg, cldata.OldSubChip);
		Draw_C_Text(szClanUserMsg, menuPos[1].left, menuPos[1].top);
		break;
	case CLANUSER_LEAVECLAN_MESSAGE:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);

		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		wsprintf(szClanUserMsg, LeaveClanMessage.szMsg, cldata.OldChipChaName, cldata.ClanZang_Name);
		Draw_C_Text(szClanUserMsg, menuPos[1].left, menuPos[1].top);
		break;
	case CLANUSER_REMOVE:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		wsprintf(szClanUserMsg, clanClanUserRemove.szMsg, cldata.name, cldata.ChaName);
		Draw_C_Text(szClanUserMsg, menuPos[1].left, menuPos[1].top);
		break;
	case	CLANUSER_AUTORELEASE:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(szClanUserMsg, menuPos[1].left, menuPos[1].top);
		break;
	case CLAN_USER:
		DrawSprite(menuPos[0].left, menuPos[0].top, hClanName, 0, 0, CLANNAME_WIDTH, CLANNAME_HEIGHT, 1);

		if (menuMouseOver[2] > 0)
			DrawSprite(menuPos[2].left, menuPos[2].top, hTxt_Secession[1], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		else
			DrawSprite(menuPos[2].left, menuPos[2].top, hTxt_Secession[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);

		if (menuMouseOver[3] > 0)
			DrawSprite(menuPos[3].left, menuPos[3].top, hTxt_Help[1], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		else
			DrawSprite(menuPos[3].left, menuPos[3].top, hTxt_Help[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);

		DrawSprite(menuPos[5].left, menuPos[5].top, hButton_Box, 0, 0, 48, 23, 1);

		if (menuMouseOver[4] > 0)
			DrawSprite(menuPos[4].left, menuPos[4].top, hClose[1], 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[4].left, menuPos[4].top, hClose[0], 0, 0, 32, 16, 1);


		DrawSprite(menuPos[1].left, menuPos[1].top, hMark_box, 0, 0, 69, 59, 1);

		if (cldata.hClanMark)
			DrawSprite(menuPos[6].left, menuPos[6].top, cldata.hClanMark, 0, 0, 32, 32, 1);

		nStrLen = lstrlen(cldata.name) / 2;

		if (nStrLen % 2)
		{
			nStrLen = nStrLen / 2;
			nStrLen += 1;
			Draw_C_Text(cldata.name, menuPos[7].left - (nStrLen * 11), menuPos[7].top, 2);	//클랜이름그림자 2임
		}
		else
		{
			nStrLen = nStrLen / 2;
			Draw_C_Text(cldata.name, menuPos[7].left - (nStrLen * 11) - 3, menuPos[7].top, 2);	//클랜이름그림자 2임
		}

		sinDrawTexImage(hLine, (float)menuPos[12].left, (float)menuPos[12].top, (float)240, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 255);

		break;
	case CLANUSER_MAKE_FIRSTMESSAGE:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);
		wsprintf(szDrawMenuMsg, szMakeFinishClan, cldata.name);

		Draw_C_Text(string, menuPos[1].left, menuPos[1].top);
		break;
	case CLANUSER_DOWN6_CLANWON_MESSAGE:
	case CLANUSER_DOWN6_CLANWON:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);
		Draw_C_Text(szClanWon6Down, menuPos[1].left, menuPos[1].top);
		break;
	case CLAN_USER_NOMAKE:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);
		wsprintf(string, clanClanUserNoMakeMsg.szMsg, cldata.name);
		Draw_C_Text(string, menuPos[1].left, menuPos[1].top);
		break;

	case CLAN_USER_WAREHOUSE:
		DrawSprite(menuPos[1].left, menuPos[1].top, hButton_Box, 0, 0, 48, 23, 1);

		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);
		break;

	case CLAN_SECESSION:
		DrawSprite(menuPos[0].left, menuPos[0].top, hClanName, 0, 0, CLANNAME_WIDTH, CLANNAME_HEIGHT, 1);

		DrawSprite(menuPos[4].left, menuPos[4].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[5].left, menuPos[5].top, hButton_Box, 0, 0, 48, 23, 1);

		if (menuMouseOver[3] > 0)
			DrawSprite(menuPos[3].left, menuPos[3].top, hCancel_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[3].left, menuPos[3].top, hCancel_Gray, 0, 0, 32, 16, 1);
		if (menuMouseOver[2] > 0)
			DrawSprite(menuPos[2].left, menuPos[2].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[2].left, menuPos[2].top, hOk_Gray, 0, 0, 32, 16, 1);

		DrawSprite(menuPos[1].left, menuPos[1].top, hMark_box, 0, 0, 69, 59, 1);

		if (cldata.hClanMark)
			DrawSprite(menuPos[7].left, menuPos[7].top, cldata.hClanMark, 0, 0, 32, 32, 1);

		wsprintf(string, clanSecession.szMsg, cldata.name);
		Draw_C_Text(string, menuPos[6].left, menuPos[6].top);
		nStrLen = lstrlen(cldata.name) / 2;

		if (nStrLen % 2)
		{
			nStrLen = nStrLen / 2;
			nStrLen += 1;
			Draw_C_Text(cldata.name, menuPos[8].left - (nStrLen * 11), menuPos[8].top, 2);
		}
		else
		{
			nStrLen = nStrLen / 2;
			Draw_C_Text(cldata.name, menuPos[8].left - (nStrLen * 11) - 3, menuPos[8].top, 2);
		}


		break;
	case CLAN_RECONF_SECESSION:
		DrawSprite(menuPos[0].left, menuPos[0].top, hClanName, 0, 0, CLANNAME_WIDTH, CLANNAME_HEIGHT, 1);

		DrawSprite(menuPos[4].left, menuPos[4].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[5].left, menuPos[5].top, hButton_Box, 0, 0, 48, 23, 1);

		if (menuMouseOver[3] > 0)
			DrawSprite(menuPos[3].left, menuPos[3].top, hCancel_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[3].left, menuPos[3].top, hCancel_Gray, 0, 0, 32, 16, 1);

		if (menuMouseOver[2] > 0)
			DrawSprite(menuPos[2].left, menuPos[2].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[2].left, menuPos[2].top, hOk_Gray, 0, 0, 32, 16, 1);

		DrawSprite(menuPos[1].left, menuPos[1].top, hMark_box, 0, 0, 69, 59, 1);

		if (cldata.hClanMark)
			DrawSprite(menuPos[7].left, menuPos[7].top, cldata.hClanMark, 0, 0, 32, 32, 1);

		Draw_C_Text(clanSecessionMsg.szMsg, menuPos[6].left, menuPos[6].top);
		nStrLen = lstrlen(cldata.name) / 2;

		if (nStrLen % 2)
		{
			nStrLen = nStrLen / 2;
			nStrLen += 1;
			Draw_C_Text(cldata.name, menuPos[8].left - (nStrLen * 11), menuPos[8].top, 2);
		}
		else
		{
			nStrLen = nStrLen / 2;
			Draw_C_Text(cldata.name, menuPos[8].left - (nStrLen * 11) - 3, menuPos[8].top, 2);
		}
		break;
	case CLANUSER_SUBCHIP_READMSG_FLAG:
	case ISPFLAG_USER:
	case CLAN_USER_ReadDATA:
	case CLAN_RECONF_SECESSION_LOADING:
		Draw_C_Text(clanLoading.szMsg, menuPos[0].left, menuPos[0].top);
		break;
	case CLAN_FINISH_SECESSION:
		DrawSprite(menuPos[0].left, menuPos[0].top, hClanName, 0, 0, CLANNAME_WIDTH, CLANNAME_HEIGHT, 1);
		DrawSprite(menuPos[4].left, menuPos[4].top, hButton_Box, 0, 0, 48, 23, 1);

		if (menuMouseOver[3] > 0)
			DrawSprite(menuPos[3].left, menuPos[3].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[3].left, menuPos[3].top, hOk_Gray, 0, 0, 32, 16, 1);

		DrawSprite(menuPos[1].left, menuPos[1].top, hMark_box, 0, 0, 69, 59, 1);

		if (cldata.hClanMark)
			DrawSprite(menuPos[2].left, menuPos[2].top, cldata.hClanMark, 0, 0, 32, 32, 1);

		Draw_C_Text(szClanUserMsg, menuPos[5].left, menuPos[5].top);
		nStrLen = lstrlen(cldata.name) / 2;

		if (nStrLen % 2)
		{
			nStrLen = nStrLen / 2;
			nStrLen += 1;
			Draw_C_Text(cldata.name, menuPos[6].left - (nStrLen * 11), menuPos[6].top, 2);
		}
		else
		{
			nStrLen = nStrLen / 2;
			Draw_C_Text(cldata.name, menuPos[6].left - (nStrLen * 11) - 3, menuPos[6].top, 2);
		}

		break;


	case CLAN_USER_HELP:
		DrawSprite(menuPos[1].left, menuPos[1].top, hButton_Box, 0, 0, 48, 23, 1);

		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		nIconPos = 2;

		for (i = 0; i < CLANHELPICON_DISPLAY_MAX; i++)
		{
			if (i == g_nClanIconNum)
				break;
			if (menuMouseOver[nIconPos] > 0)
				DrawSprite(menuPos[nIconPos].left, menuPos[nIconPos].top, hClanHelpIcon[i + nScl_Bar][0], 0, 0, 109, 30, 1);
			else
				DrawSprite(menuPos[nIconPos].left, menuPos[nIconPos].top, hClanHelpIcon[i + nScl_Bar][1], 0, 0, 109, 30, 1);

			nIconPos += 1;
		}
		nIconPos = 6;

		if (g_nClanIconNum > CLANHELPICON_DISPLAY_MAX)
		{
			DrawSprite(menuPos[nIconPos].left, menuPos[nIconPos].top, hScl_Bar, 0, 0, 8, 160, 1);
			sinDrawTexImage(hScl_icon_tj, (float)scrIconPos.left, (float)scrIconPos.top, 16, 16);
		}
		nIconPos += 1;

		DrawSprite(menuPos[nIconPos].left, menuPos[nIconPos].top, hTxt_Help[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);

		break;
	case CLAN_USER_HELP_CONTENT:
		DrawSprite(menuPos[1].left, menuPos[1].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		DrawSprite(menuPos[2].left, menuPos[2].top, hTxt_Help[0], 0, 0, 109, 30, 1);
		DrawSprite(menuPos[3].left, menuPos[3].top, hBt_Help, 0, 0, 30, 30, 1);

		sinDrawTexImage(hLine, (float)menuPos[4].left, (float)menuPos[4].top, (float)240, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 255);

		nIconPos = 5;
		if (g_HelpDisPlay > HLEPDISPLAY_MAX)
		{
			DrawSprite(menuPos[nIconPos].left, menuPos[nIconPos].top, hScl_Bar, 0, 0, 8, 160, 1);
			sinDrawTexImage(hScl_icon_tj, (float)scrIconPos.left, (float)scrIconPos.top, 16, 16);
		}
		nIconPos = 7;

		for (i = 0; i < HLEPDISPLAY_MAX; i++)
		{
			if (i == g_HelpDisPlay)
				break;

			ZeroMemory(szHelpContent, sizeof(char)*HELPWIDTH); ;

			STRINGCOPY(szHelpContent, HelpContents[i + nScl_Bar].szHelpContent);
			Draw_C_Text(szHelpContent, menuPos[nIconPos].left, menuPos[nIconPos].top);
			nIconPos += 1;
		}

		break;
	case CLANUSER_RELEASEMESSAGE:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(clanClanUserRelease.szMsg, menuPos[1].left, menuPos[1].top);
		break;

	}
}


