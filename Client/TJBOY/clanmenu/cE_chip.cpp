#include "StdAfx.h"
#define CE_CHIP_CPP
#include "tjclanDEF.h"
#include "..\\..\\HoBaram\\HoTextFile.h"

#include "tjclan.h"
#include "cE_chip.h"
#include "tjscroll.h"
#include "cE_Report.h"
#include "cE_CViewClanInfo.h"
#include "..\\isaocheck\\auth.h"
#include "..\\isaocheck\\isaocheck.h"
#include "..\\ygy\\ygyheader.h"

CLANEntity_chip::CLANEntity_chip()
{
	Money = 0;
	bClan6Down = FALSE;
	ZeroMemory(szTemp, sizeof(szTemp));
	bRemoveSecondCheck = FALSE;
}

CLANEntity_chip::~CLANEntity_chip()
{

}
int CLANEntity_chip::Init(int Life)
{
	life = Life;
	bPFlag = FALSE;
	bRelease = FALSE;
	bSubChip = FALSE;
	bisSubChip = FALSE;
	return 1;
}

int CLANEntity_chip::Clear()
{
	return 1;
}
void CLANEntity_chip::Main()
{
	int i;
	char szClanMark[32];
	if (life == 0) return;

	switch (C_menuN)
	{
	case CLANCHIP_NOSUBCHIP:
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
				C_menuN = CLAN_CHIP;
				menuInit(C_menuN);

				C_menuN2 = -1;
				CLAN_ERROR_ret = -1;
				break;
			default:
				i = i;
				break;

			}
		}

		break;
	case CLANCHIP_SUBCHIP_LOAD_DATA:
		switch (C_menuN2)
		{
		case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();		//웹db를 재개한다.
			//클랜의 멤버데이타를 읽는다.
			WebDB.ReadClan(cldata.szID, cldata.gserver, cldata.ClanZang_Name);
			C_menuN2 = 1;
			break;
		case 1:
			switch (ANSdata.ret_val)
			{
			case 0:
				WebDB.Suspend();
				//wsprintf(szErrorMsg, "가입한 클랜이 없음");
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (101)", clanszError_Msg.szMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				cClanReport.InitMsg(szErrorMsg);
				CLAN_ERROR_ret = 255;		//에러메뉴보여준후그냥끝낸다.
				C_menuN2 = -1;
				break;
			case 1:
				WebDB.Suspend();
				ParsigClanWon(ANSdata.ret_Buf);
				C_menuN = CLANCHIP_SUBCHIP_LIST;
				menuInit(C_menuN);
				break;
			case 100:
				WebDB.Suspend();
				//ygy : 살려야함
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (102)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;		//에러메뉴보여준후그냥끝낸다.			
				C_menuN2 = -1;
				break;
			case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				//ygy : 살려야함
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (103)", clanszError_Msg.szMsg);
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
		break;
	case CLANCHIP_SUBCHIP_READMSG_FLAG:
		switch (C_menuN2)
		{
		case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();
			if (cldata.nKFlag == 4)
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "8", "0");
			}
			else if (cldata.nKFlag == 16) //부칩해임만 들어 왔을때
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "32", "0");
			}
			else if (cldata.nKFlag == 5) //칩위임 부칩임명만 들어 왔을때(칩위임 확인 부칩임명확인플래그 세팅)
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "8", "0");
			}
			else if ((cldata.nKFlag == 7) && (cldata.nKFlag_Count)) //칩위임만 확인했고 부침임명확인 안했어 추가로 플래그 세팅
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "8", "0");
			}
			else if ((cldata.nKFlag == 17) && (cldata.nKFlag_Count == 1)) //칩위임 부치해임
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "32", "0");
			}
			else if ((cldata.nKFlag == 19) && (cldata.nKFlag_Count == 1)) //칩위임 부칩해임에서 칩위임만 확인했을 경우
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "32", "0");
			}
			else if ((cldata.nKFlag == 20) && (cldata.nKFlag_Count == 1) && (bSubChip == TRUE)) //부칩임명 부칩해임만 들어 왔을때(부칩해임만 확인)
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "32", "0");
			}
			else if ((cldata.nKFlag == 20) && (cldata.nKFlag_Count == 2) && (bSubChip == TRUE)) //부칩임명확인  플래그 세팅
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "8", "0");
			}
			else if ((cldata.nKFlag == 20) && (cldata.nKFlag_Count == 1) && (bSubChip == FALSE))
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "8", "0");
			}
			else if ((cldata.nKFlag == 20) && (cldata.nKFlag_Count == 2) && (bSubChip == FALSE)) //부칩임명확인  플래그 세팅
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "32", "0");
			}
			else if (cldata.nKFlag == 52) //부칩해임만 확인하여 추가로 부침임명확인 플래그 세팅
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "8", "0");
			}
			else if ((cldata.nKFlag == 21) && (cldata.nKFlag_Count == 1) && (bSubChip == TRUE))
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "32", "0");
			}
			else if ((cldata.nKFlag == 21) && (cldata.nKFlag_Count == 2) && (bSubChip == TRUE))
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "8", "0");
			}
			else if ((cldata.nKFlag == 21) && (cldata.nKFlag_Count == 1) && (bSubChip == FALSE))
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "8", "0");
			}
			else if ((cldata.nKFlag == 21) && (cldata.nKFlag_Count == 2) && (bSubChip == FALSE))
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "32", "0");
			}
			else if ((cldata.nKFlag == 23) && (cldata.nKFlag_Count == 1))
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "32", "0");
			}
			else if ((cldata.nKFlag == 23) && (cldata.nKFlag_Count == 2))
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "8", "0");
			}
			else if (cldata.nKFlag == 28)
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "32", "0");
			}
			else if (cldata.nKFlag == 55)
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "8", "0");
			}
			else {}

			C_menuN2 = 1;
			break;
		case 1:
			switch (ANSdata.ret_val)
			{
			case 0:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (86)", clanszError_Msg.szMsg);
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
					if (bSubChip)
						C_menuN = CLANCHIP_SUBCHIP_APPOINTMSG;
					else
						C_menuN = CLANCHIP_SUBCHIP_RELEASEMSG;
					menuInit(C_menuN);
					break;
				}
				else if ((cldata.nKFlag == 21) && (cldata.nKFlag_Count == 1))
				{
					cldata.nKFlag_Count = 2;
					if (bSubChip == TRUE)
						C_menuN = CLANCHIP_SUBCHIP_APPOINTMSG;
					else
						C_menuN = CLANCHIP_SUBCHIP_RELEASEMSG;
					menuInit(C_menuN);
					break;
				}
				else if ((cldata.nKFlag == 23) && (cldata.nKFlag_Count == 1))
				{
					cldata.nKFlag_Count = 2;
					C_menuN = CLANCHIP_SUBCHIP_APPOINTMSG;
					menuInit(C_menuN);
					break;
				}
				else {}
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


				if ((lstrcmp(cldata.stats, "0") == 0) && (lstrcmp(cldata.PFlag, "0") == 0))
				{
					wsprintf(szDrawMenuMsg, clanMsg6.szMsg, cldata.nLastDay);
					lstrcpy(szTemp, clanMsg6.szMsg);
					lstrcpy(clanMsg6.szMsg, szDrawMenuMsg);
					CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);
					lstrcpy(clanMsg6.szMsg, szTemp);

					if (cldata.bIsOneDay)
					{
						wsprintf(szDrawMenuMsg, clanMsg7.szMsg, cldata.nHour, cldata.nMinute);
						lstrcpy(szTemp, clanMsg6.szMsg);
						lstrcpy(clanMsg6.szMsg, szDrawMenuMsg);
						CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);
						lstrcpy(clanMsg6.szMsg, szTemp);
					}
					else
					{
						wsprintf(szDrawMenuMsg, clanMsg6.szMsg, cldata.nLastDay);
						lstrcpy(szTemp, clanMsg6.szMsg);
						lstrcpy(clanMsg6.szMsg, szDrawMenuMsg);
						CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);

						lstrcpy(clanMsg6.szMsg, szTemp);
					}

					C_menuN = CLAN_NOMAKE;
					menuInit(C_menuN);
					bPFlag = FALSE;
					C_menuN2 = -1;
					break;
				}
				else if ((lstrcmp(cldata.stats, "1") == 0) && (lstrcmp(cldata.PFlag, "0") == 0))
				{
					lstrcpy(cldata.PFlag, "2");
					lstrcpy(szTemp, clanMakeFinishClan.szMsg);
					wsprintf(szDrawMenuMsg, clanMakeFinishClan.szMsg, cldata.name);
					lstrcpy(clanMakeFinishClan.szMsg, szDrawMenuMsg);
					CheckMsgPos(&clanMakeFinishClan, BOX_MAX_WIDTH, 0);
					C_menuN = CLANCHIP_MAKE_FIRSTMESSAGE;
					menuInit(C_menuN);
					lstrcpy(clanMakeFinishClan.szMsg, szTemp);
					C_menuN2 = -1;
					bPFlag = TRUE;
					break;
				}
				else if ((lstrcmp(cldata.stats, "1") == 0) && (lstrcmp(cldata.PFlag, "2") == 0) && (nClanWon_Num < 5))
				{

					wsprintf(szDrawMenuMsg, clanMsg6.szMsg, cldata.nLastDay);
					lstrcpy(szTemp, clanMsg6.szMsg);
					lstrcpy(clanMsg6.szMsg, szDrawMenuMsg);
					CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);
					lstrcpy(clanMsg6.szMsg, szTemp);

					if (cldata.bIsOneDay)
					{
						wsprintf(szDrawMenuMsg, clanMsg7.szMsg, cldata.nHour, cldata.nMinute);
						lstrcpy(szTemp, clanMsg6.szMsg);
						lstrcpy(clanMsg6.szMsg, szDrawMenuMsg);
						CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);
						lstrcpy(clanMsg6.szMsg, szTemp);
					}
					else
					{
						wsprintf(szDrawMenuMsg, clanMsg6.szMsg, cldata.nLastDay);
						lstrcpy(szTemp, clanMsg6.szMsg);
						lstrcpy(clanMsg6.szMsg, szDrawMenuMsg);
						CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);
						lstrcpy(clanMsg6.szMsg, szTemp);
					}

					C_menuN = CLAN_NOMAKE;
					menuInit(C_menuN);
					C_menuN2 = -1;
					bPFlag = FALSE;
				}
				else
				{
					C_menuN = CLAN_CHIP;
					menuInit(C_menuN);
					C_menuN2 = -1;
					bPFlag = TRUE;
				}
				C_menuN2 = -1;
				break;
			default:

				if (ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (87)", clanszError_Msg.szMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					cClanReport.InitMsg(szErrorMsg);
					C_menuN2 = -1;
				}
				break;
			}
		}
		break;
	case CLANCHIP_SUBCHIP_APPOINT_FLAG:
		switch (C_menuN2)
		{
		case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();

			WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "200", "1");

			C_menuN2 = 1;
			break;
		case 1:
			switch (ANSdata.ret_val)
			{
			case 0://플래그 삽입 실패
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (88)", clanszError_Msg.szMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				cClanReport.InitMsg(szErrorMsg);
				C_menuN2 = -1;
				break;
			case 1: //플래그 삽입 성공							
				WebDB.Suspend();
				C_menuN2 = -1;
				//C_menuN = CLAN_CHIP;						
				C_menuN = CLANCHIP_LEAVECLAN_SUCESS;
				menuInit(C_menuN);

				C_menuN2 = -1;
				break;
			default:

				if (ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (89)", clanszError_Msg.szMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					cClanReport.InitMsg(szErrorMsg);
					C_menuN2 = -1;
				}
				break;
			}
		}
		break;
	case CLANCHIP_SUBCHIP_APPOINTMSG:		//클랜부침이 임명되다고 한번 보여줌
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

				C_menuN = CLANCHIP_SUBCHIP_READMSG_FLAG;
				//C_menuN = CLAN_ERROR_ret;		//나가기 : 끝내는걸로간다.
				menuInit(C_menuN);

				C_menuN2 = 0;
				CLAN_ERROR_ret = -1;
				break;
			default:
				i = i;
				break;

			}
		}
		break;
	case CLANCHIP_SUBCHIP_RELEASEMSG:		//클랜부침이 해임되다고 한번 보여줌	
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
				C_menuN = CLANCHIP_SUBCHIP_READMSG_FLAG;
				menuInit(C_menuN);

				C_menuN2 = 0;
				CLAN_ERROR_ret = -1;
				break;
			default:
				i = i;
				break;

			}
		}
		break;
	case CLANCHIP_SUBCHIP_LIST:			//클랜원들 리스트 보여줌 부 클랜칩이 있으면 따로 보여줌
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
			case 12:
				nScl_Bar = tscr.topScrollLineNum(pCursorPos.y);
				//ktj : 스크롤 아이콘 위치재설정
				scrIconPos.top = pCursorPos.y - 8;//BackStartPos.y + SCROOBAR_TOP;
				break;

			case 4:
			case 5:
			case 6:
			case 7:
			case 8:		//추방할사람을 설정한다.
			case 9:
			case 10:
			case 11:
				if (banisF[i - 4 + nScl_Bar] > 0)
				{
					banisF[i - 4 + nScl_Bar] = !banisF[i - 4 + nScl_Bar];
					nSavePos = i - 4 + nScl_Bar;
				}
				else
				{
					ZeroMemory(banisF, sizeof(banisF));
					banisF[i - 4 + nScl_Bar] = !banisF[i - 4 + nScl_Bar];
					nSavePos = i - 4 + nScl_Bar;
				}
				MOUSE0() = 0;
				break;
			case 15:
			case 16:
			case 17:
			case 18:
			case 19:
			case 20:
			case 21:
			case 22:
				if (banisF[i - 15 + nScl_Bar] > 0)
				{
					banisF[i - 15 + nScl_Bar] = !banisF[i - 15 + nScl_Bar];
					nSavePos = i - 14 + nScl_Bar;

				}
				else
				{
					ZeroMemory(banisF, sizeof(banisF));
					banisF[i - 15 + nScl_Bar] = !banisF[i - 15 + nScl_Bar];
					nSavePos = i - 15 + nScl_Bar;
				}
				MOUSE0() = 0;
				break;

			case 0:
				C_menuN2 = 0;
				if (nSavePos < 0)
				{
					C_menuN = CLAN_CHIP;
				}
				else
				{
					if (strcmp(cldata.clanWon[nSavePos], cldata.SubChip) == 0)
					{
						C_menuN = CLANCHIP_RELEASESUBCHIP;
						bisSubChip = FALSE;
					}
					else if ((cldata.clanWon[nSavePos][0] != 0) && (cldata.SubChip[0] != 0) && (strcmp(cldata.clanWon[nSavePos], cldata.SubChip) != 0))
					{
						C_menuN = CLANCHIP_RELEASESUBCHIP;
						bisSubChip = TRUE;
					}
					else
					{
						C_menuN = CLANCHIP_RESUBCHIP_APPOINT;
					}

				}

				menuInit(C_menuN);
				//ygy : 살려야함
				MOUSE0() = 0;
				break;
			case 1:
				C_menuN = CLAN_CHIP;				//닫기 : 그냥 돌아감.
				menuInit(C_menuN);
				//ygy : 살려야함
				MOUSE0() = 0;
				break;
			default:
				//ygy : 살려야함
				MOUSE0() = 0;
				break;
			}
		}
		break;
	case CLANCHIP_RESUBCHIP_APPOINT:		//부 클랜칩 임명 재확인
		i = chkeckMenuN();				//================================================
		switch (i)
		{
		case 0:		//yes
			menuMouseOver[0] = 1;
			break;
		case 1:		//no
			menuMouseOver[1] = 1;
			break;
		default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
		}
		if (MOUSE0())
		{
			MOUSE0() = 0;
			switch (i)
			{
			case 0:
				//ktj : 이부분 다시 열것:

				C_menuN2 = 1;
				C_menuN = CLANCHIP_APPOINTSUBCHIP_DO;			//Y : 클랜결성하겟다.  대금지불의사로간다.
				menuInit(C_menuN);

				break;

			case 1: //클랜 만들기를 취소
				//ygy : 꼭 살릴것

				C_menuN = CLAN_CHIP;			//취소				
				menuInit(C_menuN);
				break;

			default:
				break;
			}
		}
		break;
	case CLANCHIP_RESUBCHIP_APPOINT_END:	//부 클랜칩임명 마지막 메세지
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
				C_menuN = CLAN_CHIP;
				//C_menuN = CLAN_ERROR_ret;		//나가기 : 끝내는걸로간다.
				menuInit(C_menuN);
				C_menuN2 = -1;
				//CLAN_ERROR_ret=-1;
				break;
			default:
				i = i;
				break;

			}
		}
		break;
	case CLANCHIP_RELEASESUBCHIP:			//부 클랜칩해임 재확인
		i = chkeckMenuN();				//================================================
		switch (i)
		{
		case 0:		//yes
			menuMouseOver[0] = 1;
			break;
		case 1:		//no
			menuMouseOver[1] = 1;
			break;
		default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
		}
		if (MOUSE0())
		{
			MOUSE0() = 0;
			switch (i)
			{
			case 0:
				//ktj : 이부분 다시 열것:

				C_menuN2 = 1;
				C_menuN = CLANCHIP_RELEASESUBCHIP_DO;			//Y : 클랜결성하겟다.  대금지불의사로간다.
				menuInit(C_menuN);

				break;

			case 1: //클랜 만들기를 취소
				//ygy : 꼭 살릴것

				C_menuN = CLAN_CHIP;			//취소				
				menuInit(C_menuN);
				break;

			default:
				break;
			}
		}
		break;
	case CLANCHIP_RELEASESUBCHIP_END:		//클랜칩 해임 마지막 메세지
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
				ZeroMemory(cldata.SubChip, sizeof(cldata.SubChip));
				C_menuN = CLAN_CHIP;
				//C_menuN = CLAN_ERROR_ret;		//나가기 : 끝내는걸로간다.
				menuInit(C_menuN);

				C_menuN2 = -1;
				CLAN_ERROR_ret = -1;
				break;
			default:
				i = i;
				break;

			}
		}
		break;
	case CLANCHIP_APPOINTSUBCHIP_DO:		//클랜부칩 임명 ASP호출
		switch (C_menuN2)
		{
		case 1:
			ANSdata.ret_val = -1;
			WebDB.Resume();		//웹db를 재개한다.
			WebDB.AppointSubChip(cldata.szID, cldata.ChaName, cldata.name, cldata.gserver, cldata.clanWon[nSavePos]);
			C_menuN2 = 2;

			break;
		case 2:
			switch (ANSdata.ret_val)
			{
			case 0:
				WebDB.Suspend();
				C_menuN2 = 0;

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (90)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;
				break;
			case 3:
				WebDB.Suspend();
				C_menuN2 = 0;

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (100)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;
				break;
			case 2:
				WebDB.Suspend();
				C_menuN2 = 0;

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (91)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;
				break;
			case 1:
				WebDB.Suspend();
				C_menuN2 = 0;
				lstrcpy(cldata.SubChip, cldata.clanWon[nSavePos]);
				C_menuN = CLANCHIP_RESUBCHIP_APPOINT_END;
				menuInit(C_menuN);

				void SetClanWon();
				SetClanWon();
				break;
			case 100:
				WebDB.Suspend();
				C_menuN2 = 0;

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (92)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;
				break;
			case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (93)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);

				break;
			default:
				if (ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					C_menuN2 = 0;
					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (94)", clanszError_Msg.szMsg);
					cClanReport.InitMsg(szErrorMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					CLAN_ERROR_ret = CLAN_AllEnd;
				}
				break;
			}
		}
		break;
	case CLANCHIP_SUBCHIP_LOAD:
		break;
	case CLANCHIP_RELEASESUBCHIP_DO:
		switch (C_menuN2)
		{
		case 1:
			ANSdata.ret_val = -1;
			WebDB.Resume();

			WebDB.ReleaseSubChip(cldata.szID, cldata.ChaName, cldata.name, cldata.gserver, cldata.SubChip);//cldata.clanWon[nSavePos]);
			C_menuN2 = 2;

			break;
		case 2:
			switch (ANSdata.ret_val)
			{
			case 0:
				WebDB.Suspend();
				C_menuN2 = 0;

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (95)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;		//에러메뉴보여준후 다시 돌아갈곳.
				break;
			case 2: //클랜칩이거나 클랜원일 경우
				WebDB.Suspend();
				C_menuN2 = 0;

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (96)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;		//에러메뉴보여준후 다시 돌아갈곳.
				break;
			case 1: //부클랜칩 해임 성공				
				WebDB.Suspend();
				C_menuN2 = 0;
				//C_menuN = CLANCHIP_SUBCHIP_RELEASE_FLAG;				
				C_menuN = CLANCHIP_RELEASESUBCHIP_END;
				menuInit(C_menuN);


				void SetClanWon(); //서버에게 업데이트할것을 알림
				SetClanWon();

				if (bisSubChip)
				{
					C_menuN = CLANCHIP_RESUBCHIP_APPOINT;
					menuInit(C_menuN);
				}
				break;

			case 100:								//클랜을 만든것이 성공(클랜마크설명메뉴로..)				
				WebDB.Suspend();
				C_menuN2 = 0;

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (97)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;		//에러메뉴보여준후 다시 돌아갈곳.
				break;
			case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (98)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);

				break;
			default:
				if (ANSdata.ret_val != -1) {		//전혀엉뚱한 답이 와서 에러가 났다.
					WebDB.Suspend();
					C_menuN2 = 0;
					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (99)", clanszError_Msg.szMsg);
					cClanReport.InitMsg(szErrorMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					CLAN_ERROR_ret = CLAN_AllEnd;		//에러메뉴보여준후 다시 돌아갈곳.
				}
				break;
			}
		}
		break;
	case CLANCHIP_GO_RELEASEMESSAGE:
		C_menuN = CLANCHIP_RELEASEMESSAGE;
		menuInit(C_menuN);
		break;
	case CLANCHIP_RELEASEMESSAGE:
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

				C_menuN = CLANCHIP_RELEASE_FLAG;
				menuInit(C_menuN);
				C_menuN2 = 0;

				break;
			default:
				i = i;
				break;

			}
		}
		break;
	case CLAN_REMOVE_SHORTCLANWON_LOADING:
		if (ANSdata.ret_val != -1) C_menuN = CLAN_REMOVE_SHORTCLANWON;
		break;
	case CLAN_REMOVE_LOADING:
		if (ANSdata.ret_val != -1) C_menuN = CLAN_REMOVE;
		break;
	case CLAN_RELEASE_LOADING:
		if (ANSdata.ret_val != -1) C_menuN = CLAN_RECONF_RELEASE;
		break;
	case CLAN_CHIP:
		i = chkeckMenuN();
		memset(menuMouseOver, -1, sizeof(menuMouseOver));
		switch (i)
		{

		case 2: //클랜 마크
			menuMouseOver[2] = 1;
			break;
		case 3: //추방
			menuMouseOver[3] = 1;
			break;
		case 4: //클랜 해체
			menuMouseOver[4] = 1;
			break;

		case 5: //도움말
			menuMouseOver[5] = 1;
			break;
		case 6: //나가기

			menuMouseOver[6] = 1;
			break;
		case 7: //테두리			
			menuMouseOver[7] = 1;
			break;
		case 18: //이임
			if (cldata.stats[0] == '0')
				menuMouseOver[18] = 0;
			else
				menuMouseOver[18] = 1;
			break;

		case 19:
			if (cldata.stats[0] == '0') menuMouseOver[19] = 0;
			else menuMouseOver[19] = 1;
			break;

		default:
			memset(menuMouseOver, -1, sizeof(menuMouseOver));
			break;
		}
		//ygy : 살려야함
		if (MOUSE0())
		{
			//ygy : 살려야함
			MOUSE0() = 0;

			switch (i)
			{
			case 2: //클랜 마크 : 보류
				//ygy : 살려야함				
				wsprintf(szClanMark, "%s", cldata.ClanMark);
				nMark = chkMark(szClanMark);
				switch (nMark)
				{
				case 0:  //클라이언트,서버 두곳에 클랜 마크이미지가 없음
					C_menuN = CLAN_MARK1;
					menuInit(CLAN_MARK1);
					break;
				case 1: //클라이언트에만 이미지가 있음
					C_menuN = CLAN_MARK2;
					menuInit(CLAN_MARK2);
					break;
				case 2: //클라이언트 서버 두곳에 이미지가 있음
					C_menuN = CLAN_MARK3;
					menuInit(CLAN_MARK3);
					break;
				}
				break;
			case 3: //추방
				ZeroMemory(banisF, sizeof(banisF));
				ZeroMemory(banisBuf1, sizeof(banisBuf1));
				ZeroMemory(banisBuf2, sizeof(banisBuf2));
				banisCnt = 1;

				C_menuN = CLAN_REMOVE;
				menuInit(CLAN_REMOVE);
				C_menuN2 = -1;

				break;
			case 4: //클랜 해체 
				C_menuN2 = -1;
				C_menuN = CLAN_RELEASE;
				menuInit(CLAN_RELEASE);
				break;
			case 5: //도움말
				LoadHelpImage();
				C_menuN2 = -1;
				//C_menuN = CLAN_HELP;
				LoadHelp(HELPCONTENT_TXT);
				C_menuN = CLAN_HELP_CONTENT;
				menuInit(C_menuN);

				break;
			case 6: //나가기				
				C_menuN2 = -1;
				C_menuN = CLAN_AllEnd;		//나가기 : 끝내는걸로간다.
				break;
			case 18: //이임
				if (cldata.stats[0] == '0')
				{
					C_menuN = CLANCHIP_NOLEAVECLAN;
				}
				else
				{
					C_menuN = CLANCHIP_LEAVECLAN_CONFIRM;
				}

				menuInit(C_menuN);
				break;
			case 19:
				if (cldata.stats[0] == '0')
				{
					C_menuN = CLANCHIP_NOSUBCHIP;
					menuInit(C_menuN);

				}
				else
				{
					C_menuN = CLANCHIP_SUBCHIP_LOAD_DATA;
					menuInit(C_menuN);
					C_menuN2 = 0;
				}

				break;
			default:
				break;
			}
		}
		break;
	case CLAN_WAREHOUSE:					//창고
		wsprintf(szErrorMsg, "창고메뉴는 준비중입니다.");
		C_menuN = CLAN_ERROR;
		menuInit(C_menuN);
		CLAN_ERROR_ret = CLAN_CHIP;
		break;


	case CLAN_MARK1:
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
				C_menuN = 4;		//전 단계로 돌아감
				menuInit(C_menuN);
				break;
			default:
				break;
			}
		}
		break;
	case CLAN_MARK2: //클라이언트에만 클랜 마크가 존재함
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
			case 0:	//확인 :  클랜 마크를 등록함			
				break;
			case 1: //취소
				C_menuN = CLAN_CHIP;		//전 단계로 돌아감
				menuInit(C_menuN);
				break;
			default:
				break;
			}
		}
		break;
	case CLAN_MARK3: //클라이언트,서버에 클랜 마크가 존재함
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
		//ygy : mouse0살려야함
		if (MOUSE0())
		{
			MOUSE0() = 0;
			switch (i)
			{
			case 0:	//확인 :  클랜 마크를 교체
				break;
			case 1: //취소
				C_menuN = CLAN_CHIP;		//전 단계로 돌아감
				menuInit(C_menuN);
				break;
			default:
				break;
			}
		}
		break;

	case CLANCHIP_LEAVECLAN_MESSAGE: //이임이 되고나서 npc를 만날때 클랜칩이 바뀌었다는 메세지를 보여줌
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
				C_menuN = CLANCHIP_LEAVECLAN_MESSAGEEND;
				menuInit(C_menuN);
				C_menuN2 = 0;
				break;
			default:
				i = i;
				break;

			}
		}
		break;
	case CLANCHIP_LEAVECLAN_NOLEVEL: //레벨이 50미만일 경우의 메세지 처리
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
				C_menuN = CLAN_CHIP;
				menuInit(C_menuN);

				C_menuN2 = -1;
				CLAN_ERROR_ret = -1;
				break;
			default:
				i = i;
				break;
			}
		}
		break;
	case CLANCHIP_LEAVECLANDOWNLEVEL: //클랜장보다 수용할수 있는 클랜원수가 적을때 보여주는 메세지
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
				C_menuN = CLAN_CHIP;
				menuInit(C_menuN);

				C_menuN2 = -1;
				CLAN_ERROR_ret = -1;
				break;
			default:
				i = i;
				break;

			}
		}
		break;

	case CLANCHIP_NOLEAVECLAN:  //클랜이 미등록 상태이기때문에 이임할수 없다는 메세지 처리
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
				C_menuN = CLAN_CHIP;
				//C_menuN = CLAN_ERROR_ret;		//나가기 : 끝내는걸로간다.
				menuInit(C_menuN);

				C_menuN2 = -1;
				CLAN_ERROR_ret = -1;
				break;
			default:
				i = i;
				break;

			}
		}
		break;
	case CLANCHIP_LEAVECLAN_MESSAGEEND: //npc를 만나고나서 클랜장이 바뀌었다는 메세지를 읽어다고 플래그 값 201을 넣음
		switch (C_menuN2)
		{
		case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();		//웹db를 재개한다.

			if ((cldata.nKFlag == 1) && (cldata.nKFlag_Count == 1)) //클랜칩 위임
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "2", "0");
			}
			else if ((cldata.nKFlag == 5) && (cldata.nKFlag_Count == 1)) //칩이임 부침임명
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "2", "0");
			}
			else if ((cldata.nKFlag == 17) && (cldata.nKFlag_Count == 1)) //칩이임 부침해임
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "2", "0");
			}
			else if ((cldata.nKFlag == 21) && (cldata.nKFlag_Count == 1)) //칩이임 부침해임
			{
				WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "2", "0");
			}

			C_menuN2 = 1;
			break;
		case 1:
			switch (ANSdata.ret_val)
			{
			case 0://플래그 삽입 실패
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (86)", clanszError_Msg.szMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				cClanReport.InitMsg(szErrorMsg);
				C_menuN2 = -1;
				break;
			case 1: //플래그 삽입 성공							
				WebDB.Suspend();
				C_menuN2 = -1;
				if ((cldata.nKFlag == 1) && (cldata.nKFlag_Count == 1))
					cldata.nKFlag_Count = 0;
				else if (cldata.nKFlag == 17)
				{
					cldata.nKFlag_Count = 1;

					C_menuN = CLANCHIP_SUBCHIP_RELEASEMSG;
					menuInit(C_menuN);
					break;
				}
				else if (cldata.nKFlag == 5)
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANCHIP_SUBCHIP_APPOINTMSG;
					menuInit(C_menuN);
					break;
				}
				else if (cldata.nKFlag == 21)
				{
					cldata.nKFlag_Count = 1;
					if (cldata.SubChip[0] == 0)
					{
						bSubChip = FALSE;
						C_menuN = CLANCHIP_SUBCHIP_APPOINTMSG;
					}
					else
					{
						bSubChip = TRUE;
						C_menuN = CLANCHIP_SUBCHIP_RELEASEMSG;
					}

					menuInit(C_menuN);
					break;
				}
				if ((lstrcmp(cldata.stats, "0") == 0) && (lstrcmp(cldata.PFlag, "0") == 0))
				{
					wsprintf(szDrawMenuMsg, clanMsg6.szMsg, cldata.nLastDay);
					lstrcpy(szTemp, clanMsg6.szMsg);
					lstrcpy(clanMsg6.szMsg, szDrawMenuMsg);
					CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);
					lstrcpy(clanMsg6.szMsg, szTemp);

					if (cldata.bIsOneDay)
					{
						wsprintf(szDrawMenuMsg, clanMsg7.szMsg, cldata.nHour, cldata.nMinute);
						lstrcpy(szTemp, clanMsg6.szMsg);
						lstrcpy(clanMsg6.szMsg, szDrawMenuMsg);
						CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);
						lstrcpy(clanMsg6.szMsg, szTemp);
					}
					else
					{
						wsprintf(szDrawMenuMsg, clanMsg6.szMsg, cldata.nLastDay);

						lstrcpy(szTemp, clanMsg6.szMsg);
						lstrcpy(clanMsg6.szMsg, szDrawMenuMsg);
						CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);
						lstrcpy(clanMsg6.szMsg, szTemp);
					}

					C_menuN = CLAN_NOMAKE;
					menuInit(C_menuN);
					bPFlag = FALSE;
					C_menuN2 = -1;
					break;
				}
				else if ((lstrcmp(cldata.stats, "1") == 0) && (lstrcmp(cldata.PFlag, "0") == 0))
				{
					lstrcpy(cldata.PFlag, "2");
					lstrcpy(szTemp, clanMakeFinishClan.szMsg);
					wsprintf(szDrawMenuMsg, clanMakeFinishClan.szMsg, cldata.name);
					lstrcpy(clanMakeFinishClan.szMsg, szDrawMenuMsg);
					CheckMsgPos(&clanMakeFinishClan, BOX_MAX_WIDTH, 0);
					C_menuN = CLANCHIP_MAKE_FIRSTMESSAGE;
					menuInit(C_menuN);
					lstrcpy(clanMakeFinishClan.szMsg, szTemp);
					C_menuN2 = -1;
					bPFlag = TRUE;
					break;
				}
				else if ((lstrcmp(cldata.stats, "1") == 0) && (lstrcmp(cldata.PFlag, "2") == 0) && (nClanWon_Num < 5))
				{
					wsprintf(szDrawMenuMsg, clanMsg6.szMsg, cldata.nLastDay);
					lstrcpy(szTemp, clanMsg6.szMsg);
					lstrcpy(clanMsg6.szMsg, szDrawMenuMsg);
					CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);
					lstrcpy(clanMsg6.szMsg, szTemp);

					if (cldata.bIsOneDay)
					{
						wsprintf(szDrawMenuMsg, clanMsg7.szMsg, cldata.nHour, cldata.nMinute);
						lstrcpy(szTemp, clanMsg6.szMsg);
						lstrcpy(clanMsg6.szMsg, szDrawMenuMsg);
						CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);
						lstrcpy(clanMsg6.szMsg, szTemp);
					}
					else
					{
						wsprintf(szDrawMenuMsg, clanMsg6.szMsg, cldata.nLastDay);

						lstrcpy(szTemp, clanMsg6.szMsg);
						lstrcpy(clanMsg6.szMsg, szDrawMenuMsg);
						CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);
						lstrcpy(clanMsg6.szMsg, szTemp);
					}

					C_menuN = CLAN_NOMAKE;
					menuInit(C_menuN);
					C_menuN2 = -1;
					bPFlag = FALSE;
				}

				else
				{
					C_menuN = CLAN_CHIP;
					menuInit(C_menuN);
					C_menuN2 = -1;
					bPFlag = TRUE;
				}
				C_menuN2 = -1;
				break;
			default:

				if (ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (87)", clanszError_Msg.szMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					cClanReport.InitMsg(szErrorMsg);
					C_menuN2 = -1;
				}
				break;
			}
		}
		break;
	case CLANCHIP_LEAVECLAN_PFLAG:
		switch (C_menuN2)
		{
		case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();

			WebDB.isKPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "200", "1");

			C_menuN2 = 1;
			break;
		case 1:
			switch (ANSdata.ret_val)
			{
			case 0:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (88)", clanszError_Msg.szMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				cClanReport.InitMsg(szErrorMsg);
				C_menuN2 = -1;
				break;
			case 1:
				WebDB.Suspend();
				C_menuN2 = -1;
				C_menuN = CLANCHIP_LEAVECLAN_SUCESS;
				menuInit(C_menuN);

				C_menuN2 = -1;
				break;
			default:

				if (ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (89)", clanszError_Msg.szMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					cClanReport.InitMsg(szErrorMsg);
					C_menuN2 = -1;
				}
				break;
			}
		}
		break;

		//이임을 하기 위한 asp를 호출
	case CLANCHIP_LEAVECLAN_DO:
		switch (C_menuN2) {
		case 1:
			ANSdata.ret_val = -1;
			WebDB.Resume();		//웹db를 재개한다.
			WebDB.LeaveClan(cldata.name, cldata.clanWon[nSavePos], cldata.gserver);
			C_menuN2 = 2;

			break;
		case 2:
			switch (ANSdata.ret_val)
			{
			case 1: //변경 성공
				//C_menuN = CLANCHIP_LEAVECLAN_SUCESS;
				WebDB.Suspend();
				C_menuN2 = 0;

				int sinMinusMoney(int Money, int Kind = 0);
				sinMinusMoney(300000);

				C_menuN = CLANCHIP_LEAVECLAN_PFLAG;
				menuInit(C_menuN);
				break;
			case 2: //클랜원이 아님
				WebDB.Suspend();
				C_menuN2 = 0;

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (83)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;		//에러메뉴보여준후 다시 돌아갈곳.
				break;
			case 3: //존재하지 않는 클랜
				WebDB.Suspend();
				C_menuN2 = 0;

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (82)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;		//에러메뉴보여준후 다시 돌아갈곳.
				break;
			case 4: //레벨 50미만
				WebDB.Suspend();
				C_menuN2 = 0;
				C_menuN = CLANCHIP_LEAVECLAN_NOLEVEL;
				menuInit(C_menuN);
				//C_menuN = CLAN_ERROR;
				//wsprintf(szErrorMsg,"%s (81)", clanszError_Msg.szMsg);
				//cClanReport.InitMsg(szErrorMsg);
				//cClanReport.menuInit(C_menuN,clanszError_Msg.pos.x,clanszError_Msg.pos.y);
				//CLAN_ERROR_ret=CLAN_AllEnd;		//에러메뉴보여준후 다시 돌아갈곳.
				break;
			case 5: //권한 자격만 성공
				WebDB.Suspend();
				C_menuN2 = 0;
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (80)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;		//에러메뉴보여준후 다시 돌아갈곳.
				break;
			case 6: //지정캐릭터의 포용최대인원수 보다 현재 인원수가 큼
				WebDB.Suspend();
				C_menuN2 = 0;
				C_menuN = CLANCHIP_LEAVECLAN_NOLEVEL;
				menuInit(C_menuN);

				/*C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg,"%s (79)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN,clanszError_Msg.pos.x,clanszError_Msg.pos.y);
				CLAN_ERROR_ret=CLAN_AllEnd;		//에러메뉴보여준후 다시 돌아갈곳.
				*/
				break;
			case 100:								//클랜을 만든것이 성공(클랜마크설명메뉴로..)				
				WebDB.Suspend();
				C_menuN2 = 0;

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (76)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;		//에러메뉴보여준후 다시 돌아갈곳.
				break;
			case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (77)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);

				break;
			default:
				if (ANSdata.ret_val != -1) {		//전혀엉뚱한 답이 와서 에러가 났다.
					WebDB.Suspend();
					C_menuN2 = 0;
					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (78)", clanszError_Msg.szMsg);
					cClanReport.InitMsg(szErrorMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					CLAN_ERROR_ret = CLAN_AllEnd;		//에러메뉴보여준후 다시 돌아갈곳.
				}
				break;
			}
		}
		break;
	case CLANCHIP_LEAVECLAN_RECONFIRM:

		i = chkeckMenuN();				//================================================
		switch (i) {
		case 0:		//yes
			menuMouseOver[0] = 1;
			break;
		case 1:		//no
			menuMouseOver[1] = 1;
			break;
		default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
		}
		//ygy : 꼭 살릴것
		if (MOUSE0())
		{
			MOUSE0() = 0;
			switch (i)
			{
			case 0:
				//ktj : 이부분 다시 열것:

				C_menuN2 = 1;
				C_menuN = CLANCHIP_LEAVECLAN_DO;			//Y : 클랜결성하겟다.  대금지불의사로간다.
				menuInit(C_menuN);

				break;

			case 1: //클랜 만들기를 취소
				//ygy : 꼭 살릴것

				C_menuN = CLAN_CHIP;			//취소				
				menuInit(C_menuN);
				break;

			default:
				break;
			}
		}
		break;
	case CLANCHIP_LEAVECLAN_CONFIRM:
		i = chkeckMenuN();				//================================================
		switch (i) {
		case 0:		//yes
			menuMouseOver[0] = 1;
			break;
		case 1:		//no
			menuMouseOver[1] = 1;
			break;
		default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
		}
		//ygy : 꼭 살릴것
		if (MOUSE0())
		{
			MOUSE0() = 0;
			switch (i)
			{
			case 0: //이임
				//ktj : 이부분 다시 열것:
				if (cldata.money < CLANCHIP_LEAVECLAN_MONEY)
				{
					C_menuN = CLANCHIP_LEAVECLAN_NOMONEY;
				}
				else
				{
					C_menuN = CLANCHIP_LEAVECLAN;
				}

				menuInit(C_menuN);

				break;

			case 1: //이임 취소			

				C_menuN = CLAN_CHIP;			//취소				
				menuInit(C_menuN);
				break;

			default:
				break;
			}
		}
		break;
	case CLANCHIP_LEAVECLAN_NOMONEY:
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
				C_menuN = CLAN_CHIP;
				menuInit(C_menuN);
				//C_menuN = CLAN_AllEnd;
				//C_menuN = CLAN_ERROR_ret;		//나가기 : 끝내는걸로간다.


				C_menuN2 = -1;
				CLAN_ERROR_ret = -1;
				break;
			default:
				i = i;
				break;

			}
		}
		break;
	case CLANCHIP_LEAVECLAN_SUCESS:
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
				C_menuN = CLAN_AllEnd;
				//C_menuN = CLAN_ERROR_ret;		//나가기 : 끝내는걸로간다.
				//menuInit(C_menuN );

				C_menuN2 = -1;
				CLAN_ERROR_ret = -1;
				break;
			default:
				i = i;
				break;

			}
		}
		break;
	case CLANCHIP_LEAVECLAN://이임
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

		//ktj : 삭제
			//ygy : 윌관련한 변수 TJwheel살려야함
		if (TJwheel != 0) {			//ktj : wheel>0 휠 앞으로 굴리기  wheel<0 휠 뒤로 굴리기
			scrIconPos.top = tscr.ret_WHEELpoint(TJwheel, scrIconPos.top);
			nScl_Bar = tscr.topScrollLineNum(scrIconPos.top);
			TJwheel = 0;
		}


		//ygy : 살려야함
		if (MOUSE0())
		{
			switch (i)
			{
			case 12:
				nScl_Bar = tscr.topScrollLineNum(pCursorPos.y);
				//ktj : 스크롤 아이콘 위치재설정
				scrIconPos.top = pCursorPos.y - 8;//BackStartPos.y + SCROOBAR_TOP;
				break;

			case 4:
			case 5:
			case 6:
			case 7:
			case 8:		//추방할사람을 설정한다.
			case 9:
			case 10:
			case 11:
				//if(nReleaseClanWon >= 5){	
				if (banisF[i - 4 + nScl_Bar] > 0) {
					banisF[i - 4 + nScl_Bar] = !banisF[i - 4 + nScl_Bar];
					//		nReleaseClanWon-=1;
					nSavePos = i - 4 + nScl_Bar;
				}
				else
				{
					ZeroMemory(banisF, sizeof(banisF));
					banisF[i - 4 + nScl_Bar] = !banisF[i - 4 + nScl_Bar];
					nSavePos = i - 4 + nScl_Bar;
				}
				//}
				//else{

				//	banisF[i-4+nScl_Bar] = !banisF[i-4+nScl_Bar];
				//	if(banisF[i-4+nScl_Bar]){
				//		nReleaseClanWon+=1;
				//	}
				//	else{
				//		nReleaseClanWon-=1;
				//	}
				//}

				//ygy :살려야함
				MOUSE0() = 0;
				break;
			case 15:
			case 16:
			case 17:
			case 18:
			case 19:
			case 20:
			case 21:
			case 22:
				//if(nReleaseClanWon >= 5){	
				if (banisF[i - 15 + nScl_Bar] > 0) {
					banisF[i - 15 + nScl_Bar] = !banisF[i - 15 + nScl_Bar];
					nSavePos = i - 14 + nScl_Bar;
					//		nReleaseClanWon-=1;
				}
				else
				{
					ZeroMemory(banisF, sizeof(banisF));
					banisF[i - 15 + nScl_Bar] = !banisF[i - 15 + nScl_Bar];
					nSavePos = i - 15 + nScl_Bar;
				}
				//	}
				//	else{

				//		banisF[i-14+nScl_Bar] = !banisF[i-14+nScl_Bar];
				//		if(banisF[i-14+nScl_Bar]){
				//			nReleaseClanWon+=1;
				//		}
				//		else{
				//			nReleaseClanWon-=1;
				//		}
				//	}

					//ygy : 살려야함
				MOUSE0() = 0;
				break;

			case 0: //이임 ======================== 프로그램 짤것....

				C_menuN2 = 0;		//ktj : php로 추방할 데이타를  집어넣어 실행하는 루틴으로 간다.
				if (nSavePos < 0)
				{
					C_menuN = CLAN_CHIP;
				}
				else
				{
					C_menuN = CLANCHIP_LEAVECLAN_RECONFIRM;
				}

				menuInit(C_menuN);
				//ygy : 살려야함
				MOUSE0() = 0;
				break;
			case 1:
				C_menuN = CLAN_CHIP;				//닫기 : 그냥 돌아감.
				menuInit(C_menuN);
				//ygy : 살려야함
				MOUSE0() = 0;
				break;
			default:
				//ygy : 살려야함
				MOUSE0() = 0;
				break;
			}
		}
		break;
		//이임==========================================end

		//========추방

	case CLAN_REMOVE:
		switch (C_menuN2) {
		case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();		//웹db를 재개한다.
			WebDB.Banishiment(cldata.szID, cldata.gserver, cldata.ClanZang_Name, cldata.name, szRemoveClanWon);
			C_menuN2 = 1;
			break;
		case 1:

			if (ANSdata.ret_val != -1) {
				ANSdata.ret_val = ANSdata.ret_val;
			}

			switch (ANSdata.ret_val)
			{
			case -1:
				C_menuN = CLAN_REMOVE_LOADING;
				menuInit(C_menuN);
				break;
				//ygy
			case 0: //트랜잭션 오류
				WebDB.Suspend(); //웹db 중지
				//ygy : 에러 메세지 살려야함
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (12)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = 255;		//에러메뉴보여준후그냥끝낸다.
				C_menuN2 = -1;

				break;
			case 1: //클랜원 탈퇴 성공
			case 3: //탈퇴는 성공했으나 클랜회원수가 6명이하로 떨어졌을 경우(LimitDate 설정)

				WebDB.Suspend(); //웹db 중지
				void SetClanWon();
				SetClanWon();
				C_menuN2 = 0;
				C_menuN = CLAN_REMOVE_RESULT;
				menuInit(C_menuN);

				break;
			case 2: //클랜이 존재하지 않거나 클랜 장이 아닌경우 또는 클랜원이 아닌경우
				WebDB.Suspend(); //웹db 중지
				//wsprintf(szErrorMsg, "클랜이 존재하지 않거나 클랜 장이 아닌경우 또는 클랜원이 아닌경우.");
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (13)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				//menuInit(C_menuN);
				CLAN_ERROR_ret = 255;		//에러메뉴보여준후그냥끝낸다.

				C_menuN2 = -1;

				break;
			case 100: //엉둥한 값
				WebDB.Suspend(); //웹db 중지
				//ygy : 에러 메세지 살려야함
				//wsprintf(szErrorMsg, sz100Error);
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (14)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				//menuInit(C_menuN);
				CLAN_ERROR_ret = 255;		//에러메뉴보여준후그냥끝낸다.
				C_menuN2 = -1;

				break;
			case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				//ygy : 에러 메세지 살려야함
				wsprintf(szErrorMsg, "%s (15)", clanszError_Msg.szMsg);
				C_menuN = CLAN_ERROR;
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);

				break;
				//end ygy

			default:
				if (ANSdata.ret_val != -1) {		//전혀엉뚱한 답이 와서 에러가 났다.
					WebDB.Suspend();

					//ygy : 살려야함
					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (16)", clanszError_Msg.szMsg);
					cClanReport.InitMsg(szErrorMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					CLAN_ERROR_ret = 255;		//에러메뉴보여준후그냥끝낸다.
					C_menuN2 = -1;
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

		//ktj : 삭제
			//ygy : 윌관련한 변수 TJwheel살려야함
		if (TJwheel != 0) {			//ktj : wheel>0 휠 앞으로 굴리기  wheel<0 휠 뒤로 굴리기
			scrIconPos.top = tscr.ret_WHEELpoint(TJwheel, scrIconPos.top);
			nScl_Bar = tscr.topScrollLineNum(scrIconPos.top);
			TJwheel = 0;
		}


		//ygy : 살려야함
		if (MOUSE0())
		{
			switch (i)
			{
			case 12:
				nScl_Bar = tscr.topScrollLineNum(pCursorPos.y);
				//ktj : 스크롤 아이콘 위치재설정
				scrIconPos.top = pCursorPos.y - 8;//BackStartPos.y + SCROOBAR_TOP;
				break;

			case 4:
			case 5:
			case 6:
			case 7:
			case 8:		//추방할사람을 설정한다.
			case 9:
			case 10:
			case 11:
				if (nReleaseClanWon >= 5) {
					if (banisF[i - 4 + nScl_Bar] > 0) {
						banisF[i - 4 + nScl_Bar] = !banisF[i - 4 + nScl_Bar];
						nReleaseClanWon -= 1;
					}
				}
				else {

					banisF[i - 4 + nScl_Bar] = !banisF[i - 4 + nScl_Bar];
					if (banisF[i - 4 + nScl_Bar]) {
						nReleaseClanWon += 1;
					}
					else {
						nReleaseClanWon -= 1;
					}
				}

				//ygy :살려야함
				MOUSE0() = 0;
				break;
			case 14:
			case 15:
			case 16:
			case 17:
			case 18:
			case 19:
			case 20:
			case 21:
				if (nReleaseClanWon >= 5) {
					if (banisF[i - 14 + nScl_Bar] > 0) {
						banisF[i - 4 + nScl_Bar] = !banisF[i - 14 + nScl_Bar];
						nReleaseClanWon -= 1;
					}
				}
				else {

					banisF[i - 14 + nScl_Bar] = !banisF[i - 14 + nScl_Bar];
					if (banisF[i - 14 + nScl_Bar]) {
						nReleaseClanWon += 1;
					}
					else {
						nReleaseClanWon -= 1;
					}
				}

				//ygy : 살려야함
				MOUSE0() = 0;
				break;

			case 0: //추방 ======================== 프로그램 짤것....
				ZeroMemory(szRemoveClanWon, sizeof(szRemoveClanWon));
				for (i = 0; i < nClanWon_Num; i++) {
					if (banisF[i]) {
						wsprintf(banisBuf1, "clwon%d=%s", banisCnt, cldata.clanWon[i]);

						if (banisCnt == 1) {
							wsprintf(banisBuf2, "%s", banisBuf1);
						}
						else {
							wsprintf(banisBuf2, "%s&%s", szRemoveClanWon, banisBuf1);
						}
						memcpy(szRemoveClanWon, banisBuf2, strlen(banisBuf2) + 1);
						banisCnt++;
					}
				}
				if (szRemoveClanWon[0] == 0)
				{
					C_menuN = CLAN_CHIP;				//닫기 : 그냥 돌아감.
					menuInit(C_menuN);
					//ygy : 살려야함
					MOUSE0() = 0;
					break;
				}
				//ygy : 살려야함
				ReMoveClanWon(szRemoveClanWon);
				if ((nClanWon_Num - nReleaseClanWon) < 5)
				{
					bRemoveSecondCheck = FALSE;
					C_menuN = CLAN_REMOVE_SHORTCLANWON;
					menuInit(C_menuN);
					//ygy : 살려야함
					MOUSE0() = 0;
					break;
				}
				else
				{
					//6명 이상이여도 중간 메세지를 보여주기 위해서
					bRemoveSecondCheck = TRUE;
					C_menuN = CLAN_REMOVE_SHORTCLANWON;
					menuInit(C_menuN);
					//ygy : 살려야함
					MOUSE0() = 0;
					break;
				}
				C_menuN2 = 0;		//ktj : php로 추방할 데이타를  집어넣어 실행하는 루틴으로 간다.
				//ygy : 살려야함
				MOUSE0() = 0;
				break;
			case 1:
				C_menuN = CLAN_CHIP;				//닫기 : 그냥 돌아감.
				menuInit(C_menuN);
				//ygy : 살려야함
				MOUSE0() = 0;
				break;
			default:
				//ygy : 살려야함
				MOUSE0() = 0;
				break;
			}
		}
		break;
	case CLAN_REMOVE_SHORTCLANWON:
		switch (C_menuN2) {
		case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();		//웹db를 재개한다.			
			WebDB.Banishiment(cldata.szID, cldata.gserver, cldata.ClanZang_Name, cldata.name, szRemoveClanWon);

			C_menuN2 = 1;
			break;
		case 1:

			switch (ANSdata.ret_val)
			{
			case -1:
				C_menuN = CLAN_REMOVE_SHORTCLANWON_LOADING;
				menuInit(C_menuN);
				break;
				//ygy
			case 0: //트랜잭션 오류
				WebDB.Suspend(); //웹db 중지
				//ygy : 에러 메세지 살려야함
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (17)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				//menuInit(C_menuN);
				CLAN_ERROR_ret = 255;		//에러메뉴보여준후그냥끝낸다.
				C_menuN2 = -1;
				break;
			case 1: //클랜원 탈퇴 성공					
			case 3: //탈퇴는 성공했으나 클랜회원수가 6명이하로 떨어졌을 경우(LimitDate 설정)
				//fd2(" 답받음. ret_val == 100 ");
				WebDB.Suspend(); //웹db 중지
				C_menuN2 = 0;

				void SetClanWon();
				SetClanWon();

				//ygy : 살려야함
				//wsprintf(szErrorMsg, szRemoveShowrtClanWonResultMsg);
				if (nReleaseClanWon > 0) cldata.nCurrentClanWon_Num -= nReleaseClanWon; //추방하고 나서 현재 클랜원수 세팅

				C_menuN = CLAN_REMOVE_SHORTCLANWON_RESULT;
				menuInit(C_menuN);
				//



				break;
			case 2: //클랜이 존재하지 않거나 클랜 장이 아닌경우 또는 클랜원이 아닌경우
				WebDB.Suspend(); //웹db 중지
				//wsprintf(szErrorMsg, "클랜이 존재하지 않거나 클랜 장이 아닌경우 또는 클랜원이 아닌경우.");
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (18)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);

				menuInit(C_menuN);
				CLAN_ERROR_ret = 255;		//에러메뉴보여준후그냥끝낸다.

				C_menuN2 = -1;
				break;

			case 100: //엉둥한 값
				WebDB.Suspend(); //웹db 중지
				//ygy : 살려야함
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (19)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = 255;		//에러메뉴보여준후그냥끝낸다.
				C_menuN2 = -1;

				break;
			case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				//ygy : 에러 메세지 살려야함
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (20)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				break;
				//end ygy

			default:
				if (ANSdata.ret_val != -1) {		//전혀엉뚱한 답이 와서 에러가 났다.
					WebDB.Suspend();
					//ygy : 살려야함
					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (21)", clanszError_Msg.szMsg);
					cClanReport.InitMsg(szErrorMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					CLAN_ERROR_ret = 255;		//에러메뉴보여준후그냥끝낸다.
					C_menuN2 = -1;
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
		//ygy : 살려야함
		if (MOUSE0())
		{
			MOUSE0() = 0;
			switch (i)
			{
			case 0:
				C_menuN2 = 0;
				break;
			case 1:
				ZeroMemory(banisBuf1, sizeof(banisBuf1));
				ZeroMemory(banisBuf2, sizeof(banisBuf2));

				memset(banisF, 0, sizeof(int) * 100);
				ZeroMemory(szRemoveClanWon, sizeof(char) * 500);
				ZeroMemory(szRemoveClanWonResult, sizeof(szRemoveClanWonResult));  //클랜원을 저장할 변수 초기화
				banisCnt = 1;
				C_menuN = CLAN_REMOVE;
				menuInit(C_menuN);
				break;
			}
		}
		break;
	case CLAN_REMOVE_SHORTCLANWON_RESULT:
		i = chkeckMenuN();
		switch (i) {
		case 0:
			menuMouseOver[0] = 1;
			break;

		default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;

		}
		//ygy : 살려야함
		if (MOUSE0())
		{
			MOUSE0() = 0;
			switch (i)
			{
			case 0:
				bClan6Down = TRUE;
				C_menuN2 = 0;
				C_menuN = CLAN_CHIP_ReadDATA;
				//C_menuN = CLAN_CHIP;				//닫기 : 그냥 돌아감.
				menuInit(C_menuN);

				break;
			default:
				break;
			}
		}
		break;
	case CLAN_REMOVE_RESULT:
		i = chkeckMenuN();
		switch (i) {
		case 0:
			menuMouseOver[0] = 1;
			break;

		default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;

		}
		//ygy : 살려야함
		if (MOUSE0())
		{
			MOUSE0() = 0;
			switch (i)
			{
			case 0:
				C_menuN2 = 0;
				C_menuN = CLAN_CHIP_ReadDATA;
				//C_menuN = CLAN_CHIP;				//닫기 : 그냥 돌아감.
				menuInit(C_menuN);
				break;
			default:
				break;
			}
		}
		break;

	case CLAN_RELEASE: //해체
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
			case 0:			//해체하기 실행(위쪽에서 실행됨)				
				if (strcmp(cldata.stats, "0") == 0) {
					//ygy : 살려야함
					wsprintf(szReconfReleaseMsg, clanNoRecordReleaseMsg.szMsg);
				}
				else {
					//ygy : 살려야함
					wsprintf(szReconfReleaseMsg, clanszReConfReleaseMsg.szMsg);

				}
				C_menuN = CLAN_RECONF_RELEASE;
				menuInit(C_menuN);
				break;
			case 1:			//돌아간다.
				C_menuN = CLAN_CHIP;
				menuInit(C_menuN);
				break;
			default:
				break;
			}
		}
		break;
	case CLAN_RECONF_RELEASE:
		switch (C_menuN2) {
		case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();		//웹db를 재개한다.			
			WebDB.BreakUP_Clan(cldata.szID, cldata.gserver, cldata.ClanZang_Name, cldata.name);		//클랜헤체
			C_menuN2 = 1;
			break;
		case 1:
			switch (ANSdata.ret_val)
			{
			case -1:
				C_menuN = CLAN_RELEASE_LOADING;
				menuInit(C_menuN);
				break;
			case 0: //트랜잭션 오류
				WebDB.Suspend();
				//ygy : 에러 메세지 살려야함
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (22)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = 255;
				break;
			case 1: //삭제 성공				
				WebDB.Suspend(); //웹db 중지				
				cldata.myPosition = CLANNO_REGESTER;
				C_menuN = CLAN_FINISH_RELEASE;		//끝낸다.
				menuInit(C_menuN);

				C_menuN2 = 0;

				void SetClanWon();
				SetClanWon();

				cldata.myPosition = CLANNO_REGESTER;
				ZeroMemory(cldata.name, sizeof(cldata.name));
				ZeroMemory(cldata.explanation, sizeof(cldata.explanation));
				ZeroMemory(cldata.ClanZang_Name, sizeof(cldata.ClanZang_Name));
				ZeroMemory(cldata.ClanMark, sizeof(cldata.ClanMark));
				cldata.intClanMark = 0;
				ZeroMemory(cldata.PFlag, sizeof(cldata.PFlag));

				ZeroMemory(szChatClanWon, sizeof(szChatClanWon));

				DELET(cldata.hClanMark);
				DELET(cldata.hClanMark16);




#ifdef VOICE_CHAT
				if (bCheckClan)
				{
					g_CtrlProcess.SetSelectCha(cldata.szID, cldata.ChaName,
						NULL, 0, cldata.myPosition);
					// bCheckClan = FALSE;

				}
#endif
				break;
			case 2: //현재 캐릭명이 현재 클랜의 장이 아니거나 해당클랜이 없음
				WebDB.Suspend();
				//ygy : 살려야함
				//wsprintf(szErrorMsg, szReleseError);
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (23)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = 255;
				break;
			case 100: //알수 없는 오류
				WebDB.Suspend();
				//ygy : 살려야함
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (24)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = 255;
				break;
			case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				//ygy : 살려야함
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (25)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				break;

			default:
				if (ANSdata.ret_val != -1) {		//전혀엉뚱한 답이 와서 에러가 났다.
					WebDB.Suspend();
					//ygy : 살려야함
					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (26)", clanszError_Msg.szMsg);
					cClanReport.InitMsg(szErrorMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					CLAN_ERROR_ret = 255;		//에러메뉴보여준후그냥끝낸다.
					C_menuN2 = -1;
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
		//ygy : 살려야함
		if (MOUSE0())
		{
			MOUSE0() = 0;
			switch (i)
			{
			case 0:			//해체하기 실행(위쪽에서 실행됨)
				C_menuN2 = 0;
				bRelease = TRUE;
				break;
			case 1:			//돌아간다.
				C_menuN = CLAN_CHIP;
				menuInit(C_menuN);
				break;
			default:
				break;
			}
		}
		break;
	case CLAN_FINISH_RELEASE:  //도움말
		i = chkeckMenuN();
		switch (i) {
		case 0:
			menuMouseOver[0] = 1;
			break;
		default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;

		}
		//ygy : 살려야함
		if (MOUSE0())
		{
			MOUSE0() = 0;
			switch (i)
			{
			case 0:			//해체하기 실행(위쪽에서 실행됨)

				C_menuN = CLAN_AllEnd;;
				menuInit(C_menuN);
				break;
			default:
				break;
			}
		}
		break;
	case CLAN_HELP:  //도움말
		i = chkeckMenuN();
		memset(menuMouseOver, -1, sizeof(int) * 30);

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

		//ygy : 살려야함
		if (MOUSE0())
		{
			switch (i)
			{
			case 0:
				//ygy : 살려야함
				DestroyClanHelpIcon();
				C_menuN = CLAN_CHIP;	//전단계로 돌아간다
				menuInit(C_menuN);
				//ygy : 살려야함
				MOUSE0() = 0;

				break;
			case 2:
			case 3:
			case 4:
			case 5:
				//ygy : 살려야함
			//	g_HelpIconNumber = 0;				
			//	g_HelpIconNumber = i+nScl_Bar-2;

				//ygy : 살려야함
				LoadHelp(ClanHelpIcon[i + nScl_Bar - 2].TextFilePath);

				C_menuN = CLAN_HELP_CONTENT;		//도움말로 돌아감.
				menuInit(C_menuN);
				//ygy : 살려야함
				MOUSE0() = 0;

				break;


			case 6:
				nScl_Bar = tscr.topScrollLineNum(pCursorPos.y);
				//ktj : 스크롤 아이콘 위치재설정
				scrIconPos.top = pCursorPos.y - 8;//BackStartPos.y + SCROOBAR_TOP;
				break;

			default:
				//ygy : 살려야함
				MOUSE0() = 0;
				break;
			}
		}
		break;
	case CLAN_HELP_CONTENT://도움말
		i = chkeckMenuN();
		switch (i) {
		case 0:
			menuMouseOver[0] = 1;
			break;
		default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}


		//ktj : 삭제
		//ygy : 윌관련한 변수 TJwheel살려야함
		if (TJwheel != 0) {			//ktj : wheel>0 휠 앞으로 굴리기  wheel<0 휠 뒤로 굴리기
			scrIconPos.top = tscr.ret_WHEELpoint(TJwheel, scrIconPos.top);
			nScl_Bar = tscr.topScrollLineNum(scrIconPos.top);
			TJwheel = 0;
		}


		//ygy : 살려야함
		if (MOUSE0())
		{
			switch (i)
			{
			case 0:
				C_menuN = CLAN_CHIP;		//도움말로 돌아감.
				menuInit(C_menuN);
				//ygy : 살려야함
				MOUSE0() = 0;

				//ktj 스크롤관련
				tscr.Init(0);
				break;
			case 5:
				nScl_Bar = tscr.topScrollLineNum(pCursorPos.y);
				//ktj : 스크롤 아이콘 위치재설정
				scrIconPos.top = pCursorPos.y - 8;//BackStartPos.y + SCROOBAR_TOP;
				break;

			default:
				//ygy : 살려야함
				MOUSE0() = 0;
				break;
			}
		}

		break;
	case CLANCHIP_RELEASE_FLAG:
		switch (C_menuN2) {
		case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();		//웹db를 재개한다.
			WebDB.isPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, "100", "0");
			C_menuN2 = 1;
			break;
		case 1:
			switch (ANSdata.ret_val) {
			case 0://플래그 삽입 실패
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (27)", clanszError_Msg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				cClanReport.InitMsg(szErrorMsg);
				C_menuN2 = -1;
				break;
			case 1: //플래그 삽입 성공
				WebDB.Suspend();
				C_menuN2 = -1;
				C_menuN = CLAN_AllEnd;

				break;
			default:
				if (ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (28)", clanszError_Msg.szMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					cClanReport.InitMsg(szErrorMsg);
					C_menuN2 = -1;

				}
				break;
			}
		}
		break;
	case ISPFLAG_CHIP:
		switch (C_menuN2)
		{
		case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();		//웹db를 재개한다.

			WebDB.isPFlag(cldata.szID, cldata.name, cldata.ChaName, cldata.gserver, cldata.PFlag, "0");

			C_menuN2 = 1;

			break;
		case 1:
			switch (ANSdata.ret_val) {
			case 0://플래그 삽입 실패
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (29)", clanszError_Msg.szMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				cClanReport.InitMsg(szErrorMsg);
				C_menuN2 = -1;
				break;
			case 1: //플래그 삽입 성공							
				WebDB.Suspend();
				C_menuN2 = -1;
				C_menuN = CLAN_CHIP;
				menuInit(C_menuN);

				C_menuN2 = -1;
				break;
			default:

				if (ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (30)", clanszError_Msg.szMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					cClanReport.InitMsg(szErrorMsg);
					C_menuN2 = -1;
				}
				break;
			}
		}
		break;
	case CLANCHIP_MAKE_FIRSTMESSAGE:
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
			switch (i)
			{
			case 0:
				C_menuN = ISPFLAG_CHIP;		//도움말로 돌아감.
				menuInit(C_menuN);
				C_menuN2 = 0;
				break;
			default:
				break;
			}
		}
		break;
	case CLANCHIP_DOWN6_CLANWON_MESSAGE:
		i = chkeckMenuN();
		switch (i) {
		case 0:
			menuMouseOver[0] = 1;
			break;
		default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}
		//ygy : 살려야함
		if (MOUSE0())
		{
			MOUSE0() = 0;
			switch (i)
			{
			case 0:
				C_menuN = CLAN_CHIP;		//도움말로 돌아감.
				menuInit(C_menuN);
				C_menuN2 = 0;
				break;
			default:
				break;
			}
		}
		break;

	case CLANCHIP_DOWN6_CLANWON:     //클랜원이 6명 이하
		i = chkeckMenuN();
		switch (i) {
		case 0:
			menuMouseOver[0] = 1;
			break;
		default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}
		//ygy : 살려야함
		if (MOUSE0())
		{
			MOUSE0() = 0;
			switch (i)
			{
			case 0:
				C_menuN = ISPFLAG_CHIP;		//도움말로 돌아감.
				menuInit(C_menuN);
				C_menuN2 = 0;
				break;
			default:
				break;
			}
		}
		break;
	case CLAN_NOMAKE:               //아직 클랜이 결성되지 않았을때
		i = chkeckMenuN();
		switch (i) {
		case 0:
			menuMouseOver[0] = 1;
			break;
		default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}
		//ygy : 살려야함
		if (MOUSE0())
		{
			MOUSE0() = 0;
			switch (i)
			{
			case 0:
				C_menuN = CLAN_CHIP;		//도움말로 돌아감.
				menuInit(C_menuN);
				break;
			default:
				break;
			}
		}

		break;

		//===========클랜 정보 읽어오기
	case CLAN_CHIP_ReadDATA:

		switch (C_menuN2) {
		case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();		//웹db를 재개한다.
			//클랜의 멤버데이타를 읽는다.
			WebDB.ReadClan(cldata.szID, cldata.gserver, cldata.ClanZang_Name);
			C_menuN2 = 1;
			break;
		case 1:

			switch (ANSdata.ret_val)
			{
			case -1:
				//C_menuN = CLAN_CHIP_ReadDATA_LOADING;
				//menuInit(C_menuN);
				break;
				//ygy
			case 0://가입한 클랜이 없음
				WebDB.Suspend();
				//wsprintf(szErrorMsg, "가입한 클랜이 없음");
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (31)", clanszError_Msg.szMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				cClanReport.InitMsg(szErrorMsg);
				CLAN_ERROR_ret = 255;		//에러메뉴보여준후그냥끝낸다.
				C_menuN2 = -1;
				break;
			case 1://정상적으로 클랜멤보데이타받아 파싱
				WebDB.Suspend();
				ParsigClanWon(ANSdata.ret_Buf);
				if (bClan6Down)
				{
					bClan6Down = FALSE;
					C_menuN = CLAN_CHIP;
					menuInit(C_menuN);
					break;
				}
				//npc접근했을때 클랜칩 이임,부클랜칩 임명,해임 관련메세지 출력.......
				if (cldata.nKFlag == 1) //클랜칩 위임  확인 : 3
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANCHIP_LEAVECLAN_MESSAGE;
					menuInit(C_menuN);
					break;
				}
				else if (cldata.nKFlag == 16) //부클랜장 해임  확인 32
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANCHIP_SUBCHIP_RELEASEMSG;
					menuInit(C_menuN);
					break;
				}
				else if (cldata.nKFlag == 4) //부클랜장 임명 확인 8
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANCHIP_SUBCHIP_APPOINTMSG;
					menuInit(C_menuN);
					break;
				}
				else if (cldata.nKFlag == 17)//칩이임,부침해임에서 
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANCHIP_LEAVECLAN_MESSAGE;
					menuInit(C_menuN);
					break;
				}
				else if (cldata.nKFlag == 19) //칩이임,부침해임에서 칩이임만 했을경우
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANCHIP_SUBCHIP_RELEASEMSG;
					menuInit(C_menuN);
					break;
				}
				else if (cldata.nKFlag == 5) //칩이임,부침임명
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANCHIP_LEAVECLAN_MESSAGE;
					menuInit(C_menuN);
					break;
				}
				else if (cldata.nKFlag == 7) //칩이임과 부침임명에서 칩이임만 확앴으핸
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANCHIP_SUBCHIP_APPOINTMSG;
					menuInit(C_menuN);
					break;
				}
				else if (cldata.nKFlag == 20) //부칩해임 부칩임명
				{
					if (cldata.SubChip[0] == 0)
					{
						bSubChip = FALSE;
						cldata.nKFlag_Count = 1;
						C_menuN = CLANCHIP_SUBCHIP_APPOINTMSG;
						menuInit(C_menuN);
					}
					else
					{
						bSubChip = TRUE;
						cldata.nKFlag_Count = 1;
						C_menuN = CLANCHIP_SUBCHIP_RELEASEMSG;
						menuInit(C_menuN);
					}
					break;
				}
				else if (cldata.nKFlag == 52)//부칩해임 부칩임명에서 부칩해임만 확인했을 경우
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANCHIP_SUBCHIP_APPOINTMSG;
					menuInit(C_menuN);
					break;
				}
				else if (cldata.nKFlag == 21) //칩이임,부침임명,부칩해임
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANCHIP_LEAVECLAN_MESSAGE;
					menuInit(C_menuN);
					break;
				}
				else if (cldata.nKFlag == 23) //클랜칩이임 부클랜칩 해임 부클랜칩 임명에서 (클랜칩 이임만 확인)
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANCHIP_SUBCHIP_RELEASEMSG;
					menuInit(C_menuN);
					break;
				}
				else if (cldata.nKFlag == 28)
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANCHIP_SUBCHIP_RELEASEMSG;
					menuInit(C_menuN);
					break;
				}
				else if (cldata.nKFlag == 55)
				{
					cldata.nKFlag_Count = 1;
					C_menuN = CLANCHIP_SUBCHIP_APPOINTMSG;
					menuInit(C_menuN);
					break;
				}
				if ((lstrcmp(cldata.stats, "0") == 0) && (lstrcmp(cldata.PFlag, "0") == 0))
				{
					wsprintf(szDrawMenuMsg, clanMsg6.szMsg, cldata.nLastDay);
					lstrcpy(szTemp, clanMsg6.szMsg);
					lstrcpy(clanMsg6.szMsg, szDrawMenuMsg);
					CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);
					lstrcpy(clanMsg6.szMsg, szTemp);

					if (cldata.bIsOneDay)
					{
						wsprintf(szDrawMenuMsg, clanMsg7.szMsg, cldata.nHour, cldata.nMinute);
						lstrcpy(szTemp, clanMsg6.szMsg);
						lstrcpy(clanMsg6.szMsg, szDrawMenuMsg);
						CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);
						lstrcpy(clanMsg6.szMsg, szTemp);
					}
					else
					{
						wsprintf(szDrawMenuMsg, clanMsg6.szMsg, cldata.nLastDay);

						lstrcpy(szTemp, clanMsg6.szMsg);
						lstrcpy(clanMsg6.szMsg, szDrawMenuMsg);
						CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);

						lstrcpy(clanMsg6.szMsg, szTemp);
					}

					C_menuN = CLAN_NOMAKE;
					menuInit(C_menuN);
					bPFlag = FALSE;
					C_menuN2 = -1;
					break;
				}
				else if ((lstrcmp(cldata.stats, "1") == 0) && (lstrcmp(cldata.PFlag, "0") == 0))
				{
					lstrcpy(cldata.PFlag, "2");
					lstrcpy(szTemp, clanMakeFinishClan.szMsg);
					wsprintf(szDrawMenuMsg, clanMakeFinishClan.szMsg, cldata.name);
					lstrcpy(clanMakeFinishClan.szMsg, szDrawMenuMsg);
					CheckMsgPos(&clanMakeFinishClan, BOX_MAX_WIDTH, 0);
					C_menuN = CLANCHIP_MAKE_FIRSTMESSAGE;
					menuInit(C_menuN);
					lstrcpy(clanMakeFinishClan.szMsg, szTemp);
					C_menuN2 = -1;
					bPFlag = TRUE;
					break;
				}
				else if ((lstrcmp(cldata.stats, "1") == 0) && (lstrcmp(cldata.PFlag, "2") == 0) && (nClanWon_Num < 5))
				{
					wsprintf(szDrawMenuMsg, clanMsg6.szMsg, cldata.nLastDay);
					lstrcpy(szTemp, clanMsg6.szMsg);
					lstrcpy(clanMsg6.szMsg, szDrawMenuMsg);
					CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);
					lstrcpy(clanMsg6.szMsg, szTemp);

					if (cldata.bIsOneDay)
					{
						wsprintf(szDrawMenuMsg, clanMsg7.szMsg, cldata.nHour, cldata.nMinute);
						lstrcpy(szTemp, clanMsg6.szMsg);
						lstrcpy(clanMsg6.szMsg, szDrawMenuMsg);
						CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);
						lstrcpy(clanMsg6.szMsg, szTemp);
					}
					else
					{
						wsprintf(szDrawMenuMsg, clanMsg6.szMsg, cldata.nLastDay);

						lstrcpy(szTemp, clanMsg6.szMsg);
						lstrcpy(clanMsg6.szMsg, szDrawMenuMsg);
						CheckMsgPos(&clanMsg6, BOX_MAX_WIDTH, 0);
						lstrcpy(clanMsg6.szMsg, szTemp);
					}

					C_menuN = CLAN_NOMAKE;
					menuInit(C_menuN);
					C_menuN2 = -1;
					bPFlag = FALSE;
				}
				else
				{
					C_menuN = CLAN_CHIP;
					menuInit(C_menuN);
					C_menuN2 = -1;
					bPFlag = TRUE;
				}
				break;
			case 100:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (32)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;
				C_menuN2 = -1;
				break;
			case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (33)", clanszError_Msg.szMsg);
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
		break;
	}
}
void CLANEntity_chip::RenderMain()
{
	if (life == 0) return;

}
void CLANEntity_chip::menuInit(int num)
{
	int bx = 0, by = 0;
	int      nNext = 0, i, nIconCount = 0, nIconPos = 0, nAdd = 0, nWidth = 0;
	int      nFirstIconSave = 0;
	switch (num)
	{
	case CLANCHIP_SUBCHIP_APPOINTMSG:
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
	case CLANCHIP_SUBCHIP_RELEASEMSG://클랜부침이 해임되다고 한번 보여줌
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
	case CLANCHIP_SUBCHIP_LIST:
		menuSu = 6 + DISPLAY_MAX + 9;

		nScl_Bar = 0;
		nSavePos = -1;
		nReleaseClanWon = 0;
		ZeroMemory(banisF, sizeof(banisF));
		memset(menuPos, 0, sizeof(RECT) * 30);

		bx = 32;
		by = 16;


		menuPos[0].left = BackStartPos.x + BUTTON2_X;		//추방
		menuPos[0].top = BackStartPos.y + BUTTON2_Y;
		menuPos[0].right = menuPos[0].left + BUTTONTEXT_WIDTH;
		menuPos[0].bottom = menuPos[0].top + BUTTONTEXT_HEIGHT;

		bx = 32;
		by = 16;

		menuPos[1].left = BackStartPos.x + BUTTON3_X;		//닫기
		menuPos[1].top = BackStartPos.y + BUTTON3_Y;
		menuPos[1].right = menuPos[1].left + BUTTONTEXT_WIDTH;
		menuPos[1].bottom = menuPos[1].top + BUTTONTEXT_HEIGHT;

		bx = 68;
		by = 27;

		menuPos[2].left = BackStartPos.x + BUTTON2_BOX_X;		//추방 테두리 박스
		menuPos[2].top = BackStartPos.y + BUTTON2_BOX_Y;
		menuPos[2].right = menuPos[2].left + BUTTONBOX_WIDTH;
		menuPos[2].bottom = menuPos[2].top + BUTTONBOX_HEIGHT;

		bx = 32;
		by = 16;

		menuPos[3].left = BackStartPos.x + BUTTON3_BOX_X;		//닫기 테두리 박스
		menuPos[3].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[3].right = menuPos[3].left + BUTTONBOX_WIDTH;
		menuPos[3].bottom = menuPos[3].top + BUTTONBOX_HEIGHT;

		nIconCount = 3;

		memset(nClanWon, 0, sizeof(int) * 40);

		for (i = 0; i < nClanWon_Num; i++)

		{
			if (i >= DISPLAY_MAX)
				break;
			nIconCount += 1;

			bx = 13;
			by = 17;


			menuPos[nIconCount].left = BackStartPos.x + CLANWONLIST_X;
			menuPos[nIconCount].top = BackStartPos.y + CLANWONLIST_Y + nAdd;//ICON_START + nAdd + REMOVE_ICON;
			menuPos[nIconCount].right = menuPos[nIconCount].left + 13;
			menuPos[nIconCount].bottom = menuPos[nIconCount].top + 17;
			nNext += 1;
			nAdd += ICON_ADD;
			nClanWon[nIconCount] = 1;
		}
		nIconCount = 11;

		if (nClanWon_Num > DISPLAY_MAX)
		{
			nIconCount += 1;

			bx = 8;
			by = 160;

			menuPos[nIconCount].left = BackStartPos.x + SCROLLBAR_LEFT;//SCROLLBAR_LEFT;
			menuPos[nIconCount].top = BackStartPos.y + SCROOBAR_TOP;
			menuPos[nIconCount].right = menuPos[nIconCount].left + 8;
			menuPos[nIconCount].bottom = menuPos[nIconCount].top + 160;
			nClanWon[nIconCount] = 1;

			tscr.Init(1);
			tscr.Init(menuPos[nIconCount].top, menuPos[nIconCount].top + 160, nClanWon_Num, DISPLAY_MAX);

			scrIconPos.left = BackStartPos.x + SCROLLBAR_LEFT - 5;//SCROLLBAR_LEFT-4;
			scrIconPos.top = menuPos[nIconCount].top - 8;//(BackStartPos.y + SCROOBAR_TOP)-8;
		}

		nIconCount += 1;

		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;


		menuPos[nIconCount].left = BackStartPos.x + CLANTITLE_X;//CLANTEXT_IMAGE_X;		//텍스트 이미지 출력
		menuPos[nIconCount].top = BackStartPos.y + CLANTITLE_Y;//CLANTEXT_IMAGE_Y;
		menuPos[nIconCount].right = menuPos[nIconCount].left + bx;
		menuPos[nIconCount].bottom = menuPos[nIconCount].top + by;


		nIconCount += 1;

		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;


		menuPos[nIconCount].left = BackStartPos.x + 9;//CLANTEXT_IMAGE_X;		//텍스트 이미지 출력
		menuPos[nIconCount].top = BackStartPos.y + 109 - 70;//CLANTEXT_IMAGE_Y;
		menuPos[nIconCount].right = menuPos[nIconCount].left + bx;
		menuPos[nIconCount].bottom = menuPos[nIconCount].top + by;
		break;

	case CLANCHIP_RESUBCHIP_APPOINT:		//부 클랜칩 임명 재확인
		menuSu = 2;

		bx = 32;
		by = 16;


		menuPos[0].left = BackStartPos.x + BUTTON2_X;//174;		//yes
		menuPos[0].top = BackStartPos.y + +BUTTON2_Y;//353;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		bx = 32;
		by = 16;

		menuPos[1].left = BackStartPos.x + BUTTON3_X;//254		//no
		menuPos[1].top = BackStartPos.y + BUTTON3_Y; //353
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;

		menuPos[2].left = BackStartPos.x + SubChipAppoint.pos.x;
		menuPos[2].top = BackStartPos.y + SubChipAppoint.pos.y + 30;
		menuPos[2].right = menuPos[2].left + 280;
		menuPos[2].bottom = menuPos[2].top + 250;

		bx = 68;
		by = 27;


		menuPos[3].left = BackStartPos.x + BUTTON2_BOX_X;//166;		//yes 테두리 박스
		menuPos[3].top = BackStartPos.y + BUTTON2_BOX_Y;//348
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;

		bx = 68;
		by = 27;

		menuPos[4].left = BackStartPos.x + BUTTON3_BOX_X;	//246	//no 테두리 박스
		menuPos[4].top = BackStartPos.y + BUTTON3_BOX_Y;//348
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;

		bx = 68;
		by = 27;

		menuPos[5].left = BackStartPos.x + 9;	//246	//라인
		menuPos[5].top = BackStartPos.y + 109 - 65;//348
		menuPos[5].right = menuPos[5].left + bx;
		menuPos[5].bottom = menuPos[5].top + by;

		bx = 68;
		by = 27;

		menuPos[6].left = BackStartPos.x + CLANTITLE_X;	//246	//no 테두리 박스
		menuPos[6].top = BackStartPos.y + CLANTITLE_Y;//348
		menuPos[6].right = menuPos[6].left + bx;
		menuPos[6].bottom = menuPos[6].top + by;

		break;
	case CLANCHIP_RESUBCHIP_APPOINT_END:	//부 클랜칩임명 마지막 메세지
		menuSu = 3;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		//텍스트 출력 위치
		menuPos[1].left = BackStartPos.x + SubChipAppointEnd.pos.x;
		menuPos[1].top = BackStartPos.y + SubChipAppointEnd.pos.y;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		break;
	case CLANCHIP_RELEASESUBCHIP:			//부 클랜칩해임 재확인
		menuSu = 2;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON2_X;//174;		//yes
		menuPos[0].top = BackStartPos.y + +BUTTON2_Y;//353;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		bx = 32;
		by = 16;

		menuPos[1].left = BackStartPos.x + BUTTON3_X;//254		//no
		menuPos[1].top = BackStartPos.y + BUTTON3_Y; //353
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;

		//텍스트 출력 위치
		menuPos[2].left = BackStartPos.x + SubChipRelease.pos.x;
		menuPos[2].top = BackStartPos.y + SubChipRelease.pos.y + 30;
		menuPos[2].right = menuPos[2].left + 280;
		menuPos[2].bottom = menuPos[2].top + 250;

		bx = 68;
		by = 27;


		menuPos[3].left = BackStartPos.x + BUTTON2_BOX_X;//166;		//yes 테두리 박스
		menuPos[3].top = BackStartPos.y + BUTTON2_BOX_Y;//348
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;

		bx = 68;
		by = 27;

		menuPos[4].left = BackStartPos.x + BUTTON3_BOX_X;	//246	//no 테두리 박스
		menuPos[4].top = BackStartPos.y + BUTTON3_BOX_Y;//348
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;

		bx = 68;
		by = 27;

		menuPos[5].left = BackStartPos.x + 9;	//246	//라인
		menuPos[5].top = BackStartPos.y + 109 - 65;//348
		menuPos[5].right = menuPos[5].left + bx;
		menuPos[5].bottom = menuPos[5].top + by;

		bx = 68;
		by = 27;

		menuPos[6].left = BackStartPos.x + CLANTITLE_X;	//246	//no 테두리 박스
		menuPos[6].top = BackStartPos.y + CLANTITLE_Y;//348
		menuPos[6].right = menuPos[6].left + bx;
		menuPos[6].bottom = menuPos[6].top + by;

		break;
	case CLANCHIP_RELEASESUBCHIP_END:		//클랜칩 해임 마지막 메세지
		menuSu = 3;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		//텍스트 출력 위치
		menuPos[1].left = BackStartPos.x + SubChipReleaseEnd.pos.x;
		menuPos[1].top = BackStartPos.y + SubChipReleaseEnd.pos.y;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		break;
	case CLAN_CHIP:  //클랜 칩						
		menuSu = 20;
		if (hMark == NULL)
			hMark = GetClanMark();

		bx = 152;
		by = 28;

		menuPos[0].left = BackStartPos.x + CLANNAME_X;		//클랜 이름
		menuPos[0].top = BackStartPos.y + CLANNAME_Y + 4;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		bx = 64;
		by = 16;

		menuPos[10].left = BackStartPos.x + CLANNAMETEXT_X;		//클랜이름
		menuPos[10].top = BackStartPos.y + CLANNAMETEXT_Y + 4;//BackStartPos.y +BUTTON3_BOX_Y;
		menuPos[10].right = 0;//menuPos[7].left + bx;
		menuPos[10].bottom = 0;//menuPos[7].top + by;

		bx = 16;
		by = 16;


		menuPos[1].left = BackStartPos.x + CLANMARKBOX_X - 68;		//마크 박스
		menuPos[1].top = BackStartPos.y + CLANMARKBOX_Y + 55;
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;

		bx = 16;
		by = 16;

		menuPos[9].left = BackStartPos.x + CLANMARK_X - 68;		//마크
		menuPos[9].top = BackStartPos.y + CLANMARK_Y + 55;
		menuPos[9].right = menuPos[9].left + bx;
		menuPos[9].bottom = menuPos[9].top + by;

		bx = 48;
		by = 23;


		menuPos[8].left = BackStartPos.x + BUTTON1_BOX_X;		// 나가기 테두리 박스
		menuPos[8].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[8].right = menuPos[8].left + bx;
		menuPos[8].bottom = menuPos[8].top + by;

		bx = 50;
		by = 44;

		menuPos[2].left = -1;//BackStartPos.x + 185+ CHIP_BUTTON_X_MOVE;		//클랜마크
		menuPos[2].top = -1;//BackStartPos.y +  110-CHIP_BUTTON_Y_MOVE;
		menuPos[2].right = -1;//menuPos[2].left + bx;
		menuPos[2].bottom = -1;//menuPos[2].top + by;

		bx = 120;
		by = 30;

		menuPos[3].left = BackStartPos.x + CLANCHIPMENU_REMOVE_X;		//추방
		menuPos[3].top = BackStartPos.y + CLANCHIPMENU_REMOVE_Y;
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;

		bx = 120;
		by = 30;


		menuPos[4].left = BackStartPos.x + CLANCHIPMENU_RELEASE_X; 	//클랜 해제
		menuPos[4].top = BackStartPos.y + CLANCHIPMENU_RELEASE_y;
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;

		bx = 120;
		by = 30;


		menuPos[5].left = BackStartPos.x + CLANCHIPMENU_HELP_X;		//도움말
		menuPos[5].top = BackStartPos.y + CLANCHIPMENU_HELP_Y;
		menuPos[5].right = menuPos[5].left + bx;
		menuPos[5].bottom = menuPos[5].top + by;

		bx = 32;
		by = 16;

		menuPos[6].left = BackStartPos.x + BUTTON1_X;		//나가기
		menuPos[6].top = BackStartPos.y + BUTTON1_Y;
		menuPos[6].right = menuPos[6].left + bx;
		menuPos[6].bottom = menuPos[6].top + by;

		bx = 48;
		by = 27;

		menuPos[7].left = BackStartPos.x + BUTTON1_BOX_X;		//나가기 테두리 박스
		menuPos[7].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[7].right = menuPos[7].left + bx;
		menuPos[7].bottom = menuPos[7].top + by;

		bx = 30;
		by = 30;


		menuPos[11].left = BackStartPos.x + 75;		//해체 왼쪽
		menuPos[11].top = BackStartPos.y + 105;
		menuPos[11].right = menuPos[11].left + bx;
		menuPos[11].bottom = menuPos[11].top + by;

		bx = 30;
		by = 30;

		menuPos[12].left = BackStartPos.x + 216;		//해체 오른쪽
		menuPos[12].top = BackStartPos.y + 105;
		menuPos[12].right = menuPos[12].left + bx;
		menuPos[12].bottom = menuPos[12].top + by;

		bx = 30;
		by = 30;

		menuPos[13].left = BackStartPos.x + 75;		//추방 왼쪽
		menuPos[13].top = BackStartPos.y + 155;
		menuPos[13].right = menuPos[13].left + bx;
		menuPos[13].bottom = menuPos[13].top + by;

		bx = 30;
		by = 30;

		menuPos[14].left = BackStartPos.x + 216;		//추방 오른쪽
		menuPos[14].top = BackStartPos.y + 155;
		menuPos[14].right = menuPos[14].left + bx;
		menuPos[14].bottom = menuPos[14].top + by;

		bx = 30;
		by = 30;

		menuPos[15].left = BackStartPos.x + 75;		//도움말 왼쪽
		menuPos[15].top = BackStartPos.y + 205;
		menuPos[15].right = menuPos[15].left + bx;
		menuPos[15].bottom = menuPos[15].top + by;

		bx = 30;
		by = 30;

		menuPos[16].left = BackStartPos.x + 216;		//도움말 오른쪽
		menuPos[16].top = BackStartPos.y + 205;
		menuPos[16].right = menuPos[16].left + bx;
		menuPos[16].bottom = menuPos[16].top + by;

		bx = 30;
		by = 30;

		menuPos[17].left = BackStartPos.x + 9;		//라인
		menuPos[17].top = BackStartPos.y + 109 - 60;
		menuPos[17].right = menuPos[17].left + bx;
		menuPos[17].bottom = menuPos[17].top + by;

		bx = 120;
		by = 30;

		menuPos[18].left = BackStartPos.x + CLANCHIPMENU_LC_X;		//이임
		menuPos[18].top = BackStartPos.y + CLANCHIPMENU_LC_Y;
		menuPos[18].right = menuPos[18].left + bx;
		menuPos[18].bottom = menuPos[18].top + by;

		bx = 120;
		by = 30;

		menuPos[19].left = BackStartPos.x + CLANCHIPMENU_SUBCHIP_X;		//부침임명 및 해임
		menuPos[19].top = BackStartPos.y + CLANCHIPMENU_SUBCHIP_Y;
		menuPos[19].right = menuPos[19].left + bx;
		menuPos[19].bottom = menuPos[19].top + by;

		break;
	case CLANCHIP_LEAVECLAN_MESSAGE:
		menuSu = 3;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		//텍스트 출력 위치
		menuPos[1].left = BackStartPos.x + LeaveClanMessage.pos.x;
		menuPos[1].top = BackStartPos.y + LeaveClanMessage.pos.y;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		break;
	case CLANCHIP_LEAVECLAN_RECONFIRM:
		menuSu = 2;

		bx = 32;
		by = 16;


		menuPos[0].left = BackStartPos.x + BUTTON2_X;//174;		//yes
		menuPos[0].top = BackStartPos.y + +BUTTON2_Y;//353;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		bx = 32;
		by = 16;


		menuPos[1].left = BackStartPos.x + BUTTON3_X;//254		//no
		menuPos[1].top = BackStartPos.y + BUTTON3_Y; //353
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;

		//텍스트 출력 위치
		menuPos[2].left = BackStartPos.x + LeaveClanReConfirm.pos.x;
		menuPos[2].top = BackStartPos.y + LeaveClanReConfirm.pos.y;
		menuPos[2].right = menuPos[2].left + 280;
		menuPos[2].bottom = menuPos[2].top + 250;

		bx = 68;
		by = 27;


		menuPos[3].left = BackStartPos.x + BUTTON2_BOX_X;//166;		//yes 테두리 박스
		menuPos[3].top = BackStartPos.y + BUTTON2_BOX_Y;//348
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;

		bx = 68;
		by = 27;

		menuPos[4].left = BackStartPos.x + BUTTON3_BOX_X;	//246	//no 테두리 박스
		menuPos[4].top = BackStartPos.y + BUTTON3_BOX_Y;//348
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;
		break;
	case CLANCHIP_LEAVECLANDOWNLEVEL:
		menuSu = 3;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		//텍스트 출력 위치
		menuPos[1].left = BackStartPos.x + LeaveClanDownLevel.pos.x;
		menuPos[1].top = BackStartPos.y + LeaveClanDownLevel.pos.y;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		break;
	case CLANCHIP_NOSUBCHIP:
		menuSu = 3;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		//텍스트 출력 위치
		menuPos[1].left = BackStartPos.x + NoSubChip.pos.x;
		menuPos[1].top = BackStartPos.y + NoSubChip.pos.y;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		break;

	case CLANCHIP_NOLEAVECLAN:
		menuSu = 3;

		bx = 32;
		by = 16;


		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		//텍스트 출력 위치
		menuPos[1].left = BackStartPos.x + NoLeaveClan.pos.x;
		menuPos[1].top = BackStartPos.y + NoLeaveClan.pos.y;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		break;
	case CLANCHIP_LEAVECLAN_NOLEVEL:
		menuSu = 3;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		//텍스트 출력 위치
		menuPos[1].left = BackStartPos.x + LeaveClanNoLevel.pos.x;
		menuPos[1].top = BackStartPos.y + LeaveClanNoLevel.pos.y;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;
		break;
	case CLANCHIP_LEAVECLAN_CONFIRM:
		menuSu = 2;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON2_X;//174;		//yes
		menuPos[0].top = BackStartPos.y + +BUTTON2_Y;//353;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		bx = 32;
		by = 16;

		menuPos[1].left = BackStartPos.x + BUTTON3_X;//254		//no
		menuPos[1].top = BackStartPos.y + BUTTON3_Y; //353
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;

		//텍스트 출력 위치
		menuPos[2].left = BackStartPos.x + LeaveClanConfirm.pos.x;
		menuPos[2].top = BackStartPos.y + LeaveClanConfirm.pos.y + 30;
		menuPos[2].right = menuPos[2].left + 280;
		menuPos[2].bottom = menuPos[2].top + 250;

		bx = 68;
		by = 27;

		menuPos[3].left = BackStartPos.x + BUTTON2_BOX_X;//166;		//yes 테두리 박스
		menuPos[3].top = BackStartPos.y + BUTTON2_BOX_Y;//348
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;

		bx = 68;
		by = 27;

		menuPos[4].left = BackStartPos.x + BUTTON3_BOX_X;	//246	//no 테두리 박스
		menuPos[4].top = BackStartPos.y + BUTTON3_BOX_Y;//348
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;

		bx = 68;
		by = 27;

		menuPos[5].left = BackStartPos.x + 9;	//246	//라인
		menuPos[5].top = BackStartPos.y + 109 - 65;//348
		menuPos[5].right = menuPos[5].left + bx;
		menuPos[5].bottom = menuPos[5].top + by;

		bx = 68;
		by = 27;

		menuPos[6].left = BackStartPos.x + CLANTITLE_X;	//246	//no 테두리 박스
		menuPos[6].top = BackStartPos.y + CLANTITLE_Y;//348
		menuPos[6].right = menuPos[6].left + bx;
		menuPos[6].bottom = menuPos[6].top + by;

		break;
	case CLANCHIP_LEAVECLAN_NOMONEY:
		menuSu = 3;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		//텍스트 출력 위치
		menuPos[1].left = BackStartPos.x + LeaveClanNoMoney.pos.x;
		menuPos[1].top = BackStartPos.y + LeaveClanNoMoney.pos.y;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		break;
	case CLANCHIP_LEAVECLAN_SUCESS:
		menuSu = 3;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		//텍스트 출력 위치
		menuPos[1].left = BackStartPos.x + LeaveClanSuccess.pos.x;
		menuPos[1].top = BackStartPos.y + LeaveClanSuccess.pos.y;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		break;
	case CLANCHIP_LEAVECLAN:
		menuSu = 6 + DISPLAY_MAX + 9;

		nScl_Bar = 0;
		nSavePos = -1;
		nReleaseClanWon = 0;
		ZeroMemory(banisF, sizeof(banisF));
		memset(menuPos, 0, sizeof(RECT) * 30);

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON2_X;		//추방
		menuPos[0].top = BackStartPos.y + BUTTON2_Y;
		menuPos[0].right = menuPos[0].left + BUTTONTEXT_WIDTH;
		menuPos[0].bottom = menuPos[0].top + BUTTONTEXT_HEIGHT;

		bx = 32;
		by = 16;

		menuPos[1].left = BackStartPos.x + BUTTON3_X;		//닫기
		menuPos[1].top = BackStartPos.y + BUTTON3_Y;
		menuPos[1].right = menuPos[1].left + BUTTONTEXT_WIDTH;
		menuPos[1].bottom = menuPos[1].top + BUTTONTEXT_HEIGHT;

		bx = 68;
		by = 27;

		menuPos[2].left = BackStartPos.x + BUTTON2_BOX_X;		//추방 테두리 박스
		menuPos[2].top = BackStartPos.y + BUTTON2_BOX_Y;
		menuPos[2].right = menuPos[2].left + BUTTONBOX_WIDTH;
		menuPos[2].bottom = menuPos[2].top + BUTTONBOX_HEIGHT;

		bx = 32;
		by = 16;

		menuPos[3].left = BackStartPos.x + BUTTON3_BOX_X;		//닫기 테두리 박스
		menuPos[3].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[3].right = menuPos[3].left + BUTTONBOX_WIDTH;
		menuPos[3].bottom = menuPos[3].top + BUTTONBOX_HEIGHT;

		nIconCount = 3;
		memset(nClanWon, 0, sizeof(int) * 40);

		for (i = 0; i < nClanWon_Num; i++)

		{
			if (i >= DISPLAY_MAX)
				break;
			nIconCount += 1;

			bx = 13;
			by = 17;

			menuPos[nIconCount].left = BackStartPos.x + CLANWONLIST_X;
			menuPos[nIconCount].top = BackStartPos.y + CLANWONLIST_Y + nAdd;//ICON_START + nAdd + REMOVE_ICON;
			menuPos[nIconCount].right = menuPos[nIconCount].left + 13;
			menuPos[nIconCount].bottom = menuPos[nIconCount].top + 17;
			nNext += 1;
			nAdd += ICON_ADD;
			nClanWon[nIconCount] = 1;
		}
		nIconCount = 11;

		//================스크롤 바
		if (nClanWon_Num > DISPLAY_MAX)

		{
			nIconCount += 1;

			bx = 8;
			by = 160;

			menuPos[nIconCount].left = BackStartPos.x + SCROLLBAR_LEFT;//SCROLLBAR_LEFT;
			menuPos[nIconCount].top = BackStartPos.y + SCROOBAR_TOP;
			menuPos[nIconCount].right = menuPos[nIconCount].left + 8;
			menuPos[nIconCount].bottom = menuPos[nIconCount].top + 160;
			nClanWon[nIconCount] = 1;


			//ktj 스크롤관련
			tscr.Init(1);
			tscr.Init(menuPos[nIconCount].top,//BackStartPos.y + SCROOBAR_TOP, 
				menuPos[nIconCount].top + 160,//256,
				nClanWon_Num, DISPLAY_MAX);

			scrIconPos.left = BackStartPos.x + SCROLLBAR_LEFT - 5;//SCROLLBAR_LEFT-4;
			scrIconPos.top = menuPos[nIconCount].top - 8;//(BackStartPos.y + SCROOBAR_TOP)-8;
		}

		nIconCount += 1;

		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;


		menuPos[nIconCount].left = BackStartPos.x + CLANTITLE_X;//CLANTEXT_IMAGE_X;		//텍스트 이미지 출력
		menuPos[nIconCount].top = BackStartPos.y + CLANTITLE_Y;//CLANTEXT_IMAGE_Y;
		menuPos[nIconCount].right = menuPos[nIconCount].left + bx;
		menuPos[nIconCount].bottom = menuPos[nIconCount].top + by;


		nIconCount += 1;

		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;


		menuPos[nIconCount].left = BackStartPos.x + 9;//CLANTEXT_IMAGE_X;		//텍스트 이미지 출력
		menuPos[nIconCount].top = BackStartPos.y + 109 - 70;//CLANTEXT_IMAGE_Y;
		menuPos[nIconCount].right = menuPos[nIconCount].left + bx;
		menuPos[nIconCount].bottom = menuPos[nIconCount].top + by;
		break;
	case CLAN_REMOVE://추방
		menuSu = 6 + DISPLAY_MAX + 8;

		nScl_Bar = 0;
		nReleaseClanWon = 0;
		memset(menuPos, 0, sizeof(RECT) * 30);

		bx = 32;
		by = 16;


		menuPos[0].left = BackStartPos.x + BUTTON2_X;		//추방
		menuPos[0].top = BackStartPos.y + BUTTON2_Y;
		menuPos[0].right = menuPos[0].left + BUTTONTEXT_WIDTH;
		menuPos[0].bottom = menuPos[0].top + BUTTONTEXT_HEIGHT;

		bx = 32;
		by = 16;

		menuPos[1].left = BackStartPos.x + BUTTON3_X;		//닫기
		menuPos[1].top = BackStartPos.y + BUTTON3_Y;
		menuPos[1].right = menuPos[1].left + BUTTONTEXT_WIDTH;
		menuPos[1].bottom = menuPos[1].top + BUTTONTEXT_HEIGHT;

		bx = 68;
		by = 27;

		menuPos[2].left = BackStartPos.x + BUTTON2_BOX_X;		//추방 테두리 박스
		menuPos[2].top = BackStartPos.y + BUTTON2_BOX_Y;
		menuPos[2].right = menuPos[2].left + BUTTONBOX_WIDTH;
		menuPos[2].bottom = menuPos[2].top + BUTTONBOX_HEIGHT;

		bx = 32;
		by = 16;

		menuPos[3].left = BackStartPos.x + BUTTON3_BOX_X;		//닫기 테두리 박스
		menuPos[3].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[3].right = menuPos[3].left + BUTTONBOX_WIDTH;
		menuPos[3].bottom = menuPos[3].top + BUTTONBOX_HEIGHT;

		//================아이콘 설정				
		nIconCount = 3;
		//int	nClanWon[40];
		memset(nClanWon, 0, sizeof(int) * 40);

		for (i = 0; i < nClanWon_Num; i++)

		{
			if (i >= DISPLAY_MAX)
				break;
			nIconCount += 1;

			bx = 13;
			by = 17;

			menuPos[nIconCount].left = BackStartPos.x + CLANWONLIST_X;
			menuPos[nIconCount].top = BackStartPos.y + CLANWONLIST_Y + nAdd;//ICON_START + nAdd + REMOVE_ICON;
			menuPos[nIconCount].right = menuPos[nIconCount].left + 13;
			menuPos[nIconCount].bottom = menuPos[nIconCount].top + 17;
			nNext += 1;
			nAdd += ICON_ADD;
			nClanWon[nIconCount] = 1;
		}
		nIconCount = 11;

		//================스크롤 바
		if (nClanWon_Num > DISPLAY_MAX)

		{
			nIconCount += 1;

			bx = 8;
			by = 160;

			menuPos[nIconCount].left = BackStartPos.x + SCROLLBAR_LEFT;//SCROLLBAR_LEFT;
			menuPos[nIconCount].top = BackStartPos.y + SCROOBAR_TOP;
			menuPos[nIconCount].right = menuPos[nIconCount].left + 8;
			menuPos[nIconCount].bottom = menuPos[nIconCount].top + 160;
			nClanWon[nIconCount] = 1;


			//ktj 스크롤관련
			tscr.Init(1);
			tscr.Init(menuPos[nIconCount].top,//BackStartPos.y + SCROOBAR_TOP, 
				menuPos[nIconCount].top + 160,//256,
				nClanWon_Num, DISPLAY_MAX);

			scrIconPos.left = BackStartPos.x + SCROLLBAR_LEFT - 5;//SCROLLBAR_LEFT-4;
			scrIconPos.top = menuPos[nIconCount].top - 8;//(BackStartPos.y + SCROOBAR_TOP)-8;
		}

		nIconCount += 1;

		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;


		menuPos[nIconCount].left = BackStartPos.x + CLANTITLE_X;//CLANTEXT_IMAGE_X;		//텍스트 이미지 출력
		menuPos[nIconCount].top = BackStartPos.y + CLANTITLE_Y;//CLANTEXT_IMAGE_Y;
		menuPos[nIconCount].right = menuPos[nIconCount].left + bx;
		menuPos[nIconCount].bottom = menuPos[nIconCount].top + by;


		break;
	case CLAN_REMOVE_SHORTCLANWON: //이 클랜원을 추방할경우 클랜원이 6명이하로 떨어진다고 메세지 출력
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


		//텍스트 출력 위치
		if (bRemoveSecondCheck) //6명 이상일 경우
		{
			menuPos[2].left = BackStartPos.x + clanRemoveSecond.pos.x;
			menuPos[2].top = BackStartPos.y + clanRemoveSecond.pos.y - 20;
		}
		else
		{
			menuPos[2].left = BackStartPos.x + clanszRemoveShortClanWonMsg.pos.x;
			menuPos[2].top = BackStartPos.y + clanszRemoveShortClanWonMsg.pos.y;
		}
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
	case CLAN_REMOVE_SHORTCLANWON_RESULT:
		menuSu = 3;

		bx = 64;
		by = 64;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		//텍스트 출력 위치
		if (bRemoveSecondCheck) //6명 이상일 경우
		{
			menuPos[1].left = BackStartPos.x + clanRemoveSecondResult.pos.x;
			menuPos[1].top = BackStartPos.y + clanRemoveSecondResult.pos.y;
		}
		else
		{
			menuPos[1].left = BackStartPos.x + clanRemoveShowrtClanWonResultMsg.pos.x;
			menuPos[1].top = BackStartPos.y + clanRemoveShowrtClanWonResultMsg.pos.y;
		}

		menuPos[1].right = menuPos[1].left + 190;
		menuPos[1].bottom = menuPos[1].top + 180;

		bx = 68;
		by = 27;


		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인 테두리 박스
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;
		break;
	case CLAN_REMOVE_RESULT: //클랜원 추방 결과 보여주기
		menuSu = 3;

		bx = 64;
		by = 64;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		//텍스트 출력 위치
		menuPos[1].left = BackStartPos.x + clanReMoveHeaderMsg.pos.x;
		menuPos[1].top = BackStartPos.y + clanReMoveHeaderMsg.pos.y - 20;
		menuPos[1].right = menuPos[1].left + 190;
		menuPos[1].bottom = menuPos[1].top + 180;

		bx = 68;
		by = 27;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인 테두리 박스
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;
		break;
	case CLANCHIP_RELEASEMESSAGE:
		menuSu = 3;

		bx = 64;
		by = 64;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		//텍스트 출력 위치
		menuPos[1].left = BackStartPos.x + clanClanUserRelease.pos.x;
		menuPos[1].top = BackStartPos.y + clanClanUserRelease.pos.y;
		menuPos[1].right = menuPos[1].left + 190;
		menuPos[1].bottom = menuPos[1].top + 180;

		bx = 68;
		by = 27;


		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인 테두리 박스
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;
		break;
	case CLAN_WAREHOUSE_RIGHT:
		menuSu = 6;

		bx = 13;
		by = 17;

		menuPos[0].left = BackStartPos.x + 70;		// 아이콘
		menuPos[0].top = BackStartPos.y + 50 + WHR_ICON;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		bx = 13;
		by = 17;

		menuPos[1].left = BackStartPos.x + 70;		//아이콘
		menuPos[1].top = BackStartPos.y + 80 + WHR_ICON;
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;

		bx = 13;
		by = 17;


		menuPos[2].left = BackStartPos.x + 70;		//아이콘
		menuPos[2].top = BackStartPos.y + 110 + WHR_ICON;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		bx = 13;
		by = 17;

		menuPos[3].left = BackStartPos.x + 70;		//아이콘
		menuPos[3].top = BackStartPos.y + 140 + WHR_ICON;
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;

		bx = 13;
		by = 17;

		menuPos[4].left = BackStartPos.x + 70;		//아이콘
		menuPos[4].top = BackStartPos.y + 170 + WHR_ICON;
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;

		bx = 32;
		by = 16;

		menuPos[5].left = BackStartPos.x + BUTTON3_X;		//확인
		menuPos[5].top = BackStartPos.y + BUTTON3_Y;
		menuPos[5].right = menuPos[5].left + bx;
		menuPos[5].bottom = menuPos[5].top + by;

		//텍스트 출력 위치
		menuPos[6].left = menuPos[0].left + bx + XCAP;
		menuPos[6].top = menuPos[0].top + YDOWN;

		menuPos[7].left = menuPos[1].left + bx + XCAP;
		menuPos[7].top = menuPos[1].top + YDOWN;

		menuPos[8].left = menuPos[2].left + bx + XCAP;
		menuPos[8].top = menuPos[2].top + YDOWN;

		menuPos[9].left = menuPos[3].left + bx + XCAP;
		menuPos[9].top = menuPos[3].top + YDOWN;

		menuPos[10].left = menuPos[4].left + bx + XCAP;
		menuPos[10].top = menuPos[4].top + YDOWN;

		bx = 64;
		by = 16;

		menuPos[11].left = BackStartPos.x + BUTTON3_BOX_X;		//확인 테두리 박스
		menuPos[11].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[11].right = menuPos[11].left + bx;
		menuPos[11].bottom = menuPos[11].top + by;

		break;





	case CLAN_MARK1: // 클라이언트, 서버에 클랜 마크가 업음
		menuSu = 1;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON3_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON3_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		//텍스트 출력 위치
		menuPos[1].left = BackStartPos.x + 60;
		menuPos[1].top = BackStartPos.y + 100;
		menuPos[1].right = menuPos[1].left + 260;
		menuPos[1].bottom = menuPos[1].top + 180;

		bx = 64;
		by = 64;

		menuPos[2].left = BackStartPos.x + BUTTON3_BOX_X;		//확인 테두리 박스
		menuPos[2].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;


		menuPos[3].left = BackStartPos.x + CLANTEXT_IMAGE_X;		//텍스트 이미지 출력
		menuPos[3].top = BackStartPos.y + CLANTEXT_IMAGE_Y;
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;
		break;
	case CLAN_MARK2: //클랜마크가 클라이언트에만 있음
		menuSu = 2;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//yes
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		bx = 32;
		by = 16;

		menuPos[1].left = BackStartPos.x + BUTTON2_X;		//no
		menuPos[1].top = BackStartPos.y + BUTTON2_Y;
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;

		bx = 64;
		by = 64;


		menuPos[2].left = BackStartPos.x + 150;		//이미지 디스플레이
		menuPos[2].top = BackStartPos.y + 150;
		menuPos[2].right = menuPos[2].left + 15;
		menuPos[2].bottom = menuPos[2].top + 15;



		//텍스트 출력 위치
		menuPos[3].left = BackStartPos.x + 60;
		menuPos[3].top = BackStartPos.y + 100;
		menuPos[3].right = menuPos[3].left + 260;
		menuPos[3].bottom = menuPos[3].top + 180;

		bx = 64;
		by = 64;


		menuPos[4].left = BackStartPos.x + BUTTON1_BOX_X;	//YES 테두리 박스
		menuPos[4].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[4].right = menuPos[4].left + 15;
		menuPos[4].bottom = menuPos[4].top + 15;

		bx = 64;
		by = 64;

		menuPos[5].left = BackStartPos.x + BUTTON2_BOX_X;		//NO 테두리 박스
		menuPos[5].top = BackStartPos.y + BUTTON2_BOX_Y;
		menuPos[5].right = menuPos[5].left + 15;
		menuPos[5].bottom = menuPos[5].top + 15;

		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;

		menuPos[6].left = BackStartPos.x + CLANTEXT_IMAGE_X;		//텍스트 이미지 출력
		menuPos[6].top = BackStartPos.y + CLANTEXT_IMAGE_Y;
		menuPos[6].right = menuPos[6].left + bx;
		menuPos[6].bottom = menuPos[6].top + by;

		break;
	case CLAN_MARK3: //클랜 마크가 클라이언트,서버에 다 존재함
		menuSu = 2;

		bx = 64;
		by = 64;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//yes
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		bx = 64;
		by = 64;

		menuPos[1].left = BackStartPos.x + BUTTON2_X;		//no
		menuPos[1].top = BackStartPos.y + BUTTON2_Y;
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;

		bx = 64;
		by = 64;

		menuPos[2].left = BackStartPos.x + 100;		//이미지 디스플레이
		menuPos[2].top = BackStartPos.y + 150;
		menuPos[2].right = menuPos[2].left + 15;
		menuPos[2].bottom = menuPos[2].top + 15;

		bx = 64;
		by = 64;

		menuPos[3].left = BackStartPos.x + 200;		//이미지 디스플레이
		menuPos[3].top = BackStartPos.y + 150;
		menuPos[3].right = menuPos[3].left + 15;
		menuPos[3].bottom = menuPos[3].top + 15;

		//텍스트 출력 위치
		menuPos[4].left = BackStartPos.x + 60;
		menuPos[4].top = BackStartPos.y + 100;
		menuPos[4].right = menuPos[4].left + 260;
		menuPos[4].bottom = menuPos[4].top + 180;

		bx = 64;
		by = 64;

		menuPos[5].left = BackStartPos.x + BUTTON1_BOX_X;	//YES 테두리 박스
		menuPos[5].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[5].right = menuPos[5].left + 15;
		menuPos[5].bottom = menuPos[5].top + 15;

		bx = 64;
		by = 64;

		menuPos[6].left = BackStartPos.x + BUTTON2_BOX_X;		//NO 테두리 박스
		menuPos[6].top = BackStartPos.y + BUTTON2_BOX_Y;
		menuPos[6].right = menuPos[6].left + 15;
		menuPos[6].bottom = menuPos[6].top + 15;

		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;

		menuPos[7].left = BackStartPos.x + CLANTEXT_IMAGE_X;		//텍스트 이미지 출력
		menuPos[7].top = BackStartPos.y + CLANTEXT_IMAGE_Y;
		menuPos[7].right = menuPos[7].left + bx;
		menuPos[7].bottom = menuPos[7].top + by;
		break;


	case CLAN_RELEASE:
		menuSu = 2;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON2_X;		//yes
		menuPos[0].top = BackStartPos.y + BUTTON2_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		bx = 32;
		by = 16;

		menuPos[1].left = BackStartPos.x + BUTTON3_X;		//no
		menuPos[1].top = BackStartPos.y + BUTTON3_Y;
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;

		menuPos[2].left = BackStartPos.x + clanMsg15.pos.x;
		menuPos[2].top = BackStartPos.y + clanMsg15.pos.y;
		menuPos[2].right = menuPos[2].left + 280;
		menuPos[2].bottom = menuPos[2].top + 250;

		bx = 64;
		by = 16;

		menuPos[3].left = BackStartPos.x + BUTTON2_BOX_X;		//YES 테두리 박스
		menuPos[3].top = BackStartPos.y + BUTTON2_BOX_Y;
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;

		bx = 64;
		by = 16;

		menuPos[4].left = BackStartPos.x + BUTTON3_BOX_X;		//NO 테두리 박스
		menuPos[4].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;

		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;

		menuPos[5].left = BackStartPos.x + CLANTITLE_X;		//텍스트 이미지 출력
		menuPos[5].top = BackStartPos.y + CLANTITLE_Y;
		menuPos[5].right = menuPos[5].left + bx;
		menuPos[5].bottom = menuPos[5].top + by;

		break;
	case CLAN_RECONF_RELEASE:
		menuSu = 6;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON2_X;		//yes
		menuPos[0].top = BackStartPos.y + BUTTON2_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		bx = 32;
		by = 16;

		menuPos[1].left = BackStartPos.x + BUTTON3_X;		//no
		menuPos[1].top = BackStartPos.y + BUTTON3_Y;
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;

		//텍스트 출력 위치
		menuPos[2].left = BackStartPos.x + CLAN_RECONF_RELEASE_X;
		menuPos[2].top = BackStartPos.y + CLAN_RECONF_RELEASE_Y;
		menuPos[2].right = 0;//menuPos[2].left + 280;
		menuPos[2].bottom = 0;//menuPos[2].top + 250;

		bx = 64;
		by = 16;

		menuPos[3].left = BackStartPos.x + BUTTON2_BOX_X;		//YES 테두리 박스
		menuPos[3].top = BackStartPos.y + BUTTON2_BOX_Y;
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;

		bx = 64;
		by = 16;

		menuPos[4].left = BackStartPos.x + BUTTON3_BOX_X;		//NO 테두리 박스
		menuPos[4].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;

		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;

		menuPos[5].left = BackStartPos.x + CLANTITLE_X;		//텍스트 이미지 출력
		menuPos[5].top = BackStartPos.y + CLANTITLE_Y;
		menuPos[5].right = menuPos[5].left + bx;
		menuPos[5].bottom = menuPos[5].top + by;

		break;
	case CLAN_FINISH_RELEASE:
		menuSu = 4;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		bx = 64;
		by = 16;

		menuPos[1].left = BackStartPos.x + BUTTON1_BOX_X;		//YES 테두리 박스
		menuPos[1].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;

		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;

		menuPos[2].left = BackStartPos.x + CLANTITLE_X;		//텍스트 이미지 출력
		menuPos[2].top = BackStartPos.y + CLANTITLE_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		menuPos[3].left = BackStartPos.x + clanFinishReleaseMsg.pos.x;
		menuPos[3].top = BackStartPos.y + clanFinishReleaseMsg.pos.y;
		menuPos[3].right = 0;
		menuPos[3].bottom = 0;

		break;
	case CLAN_HELP:
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
			//nWidth += CLANHELPICON_HEIGHT;
		}
		nIconPos = 6;

		//ktj 스크롤관련
		tscr.Init(0);

		//================스크롤 바
		if (g_nClanIconNum > CLANHELPICON_DISPLAY_MAX)
		{

			bx = 16;
			by = 16;

			menuPos[nIconPos].left = BackStartPos.x + SCROLLBAR_LEFT;
			menuPos[nIconPos].top = BackStartPos.y + SCROOBAR_TOP;
			menuPos[nIconPos].right = menuPos[nIconPos].left + 8;
			menuPos[nIconPos].bottom = menuPos[nIconPos].top + 160;
			//nClanWon[nIconPos] = 1;

			//ktj 스크롤관련
			tscr.Init(1);
			tscr.Init(menuPos[nIconPos].top, //BackStartPos.y + SCROOBAR_TOP, 
				menuPos[nIconPos].top + 160,//256,						
				g_nClanIconNum, CLANHELPICON_DISPLAY_MAX);

			scrIconPos.left = BackStartPos.x + SCROLLBAR_LEFT - 5;//SCROLLBAR_LEFT-4;
			scrIconPos.top = menuPos[nIconPos].top - 8;//(BackStartPos.y + SCROOBAR_TOP)-8;
		}
		//텍스트 이미지 출력
		nIconPos += 1;

		bx = CLANTEXT_IMAGE_WIDTH;
		by = CLANTEXT_IMAGE_HEIGHT;

		menuPos[nIconPos].left = BackStartPos.x + CLANTITLE_X;
		menuPos[nIconPos].top = BackStartPos.y + CLANTITLE_Y;
		menuPos[nIconPos].right = menuPos[nIconPos].left + bx;
		menuPos[nIconPos].bottom = menuPos[nIconPos].top + by;


		break;
	case CLAN_HELP_CONTENT: //헬프에서 첫번째 지문
		menuSu = 1 + HLEPDISPLAY_MAX + 5;

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
		menuPos[2].top = BackStartPos.y + CLANTITLE_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		bx = 30;
		by = 30;

		menuPos[3].left = BackStartPos.x + 14;
		menuPos[3].top = BackStartPos.y + 12;
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;

		bx = 30;
		by = 30;

		menuPos[4].left = BackStartPos.x + 9;
		menuPos[4].top = BackStartPos.y + 45;
		menuPos[4].right = menuPos[3].left + bx;
		menuPos[4].bottom = menuPos[3].top + by;



		//텍스트 출력 위치
		nIconPos = 5;

		if (g_HelpDisPlay > HLEPDISPLAY_MAX)
		{

			bx = 16;
			by = 16;

			menuPos[nIconPos].left = BackStartPos.x + SCROLLBAR_LEFT;
			menuPos[nIconPos].top = BackStartPos.y + SCROOBAR_TOP;
			menuPos[nIconPos].right = menuPos[nIconPos].left + 8;
			menuPos[nIconPos].bottom = menuPos[nIconPos].top + 160;

			//ktj 스크롤관련
			tscr.Init(1);
			tscr.Init(menuPos[nIconPos].top,//BackStartPos.y + SCROOBAR_TOP, 
				menuPos[nIconPos].top + 160,//256,
				g_HelpDisPlay, HLEPDISPLAY_MAX);

			scrIconPos.left = BackStartPos.x + SCROLLBAR_LEFT - 5;//SCROLLBAR_LEFT-4;
			scrIconPos.top = menuPos[nIconPos].top - 8;
		}


		nIconPos = 7;
		nAdd = 0;
		for (i = 0; i < HLEPDISPLAY_MAX; i++)
		{
			bx = 64;
			by = 16;

			menuPos[nIconPos].left = BackStartPos.x + HELPCONTENT_X;
			menuPos[nIconPos].top = BackStartPos.y + HELPCONTENT_Y + nAdd;//BackStartPos.y +  HELPCONTENT_Y+nAdd;
			menuPos[nIconPos].right = 0;//menuPos[nIconPos].left + CLANHELPICON_WIDTH;
			menuPos[nIconPos].bottom = 0;//menuPos[nIconPos].top + CLANHELPICON_HEIGHT;
			nIconPos += 1;
			nAdd += HELPCONTENT_CAP;
		}



		break;
	case CLANCHIP_MAKE_FIRSTMESSAGE:
		menuSu = 3;

		bx = 64;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		//텍스트 출력 위치
		menuPos[1].left = BackStartPos.x + clanMakeFinishClan.pos.x;
		menuPos[1].top = BackStartPos.y + clanMakeFinishClan.pos.y;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인 테두리
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;
		break;
	case CLANCHIP_DOWN6_CLANWON:
	case CLANCHIP_DOWN6_CLANWON_MESSAGE:
	case CLAN_NOMAKE:
		menuSu = 3;

		bx = 64;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		//텍스트 출력 위치
		menuPos[1].left = BackStartPos.x + clanMsg6.pos.x;
		menuPos[1].top = BackStartPos.y + clanMsg6.pos.y;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인 테두리
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;
		break;
	case CLANCHIP_SUBCHIP_LOAD_DATA:
	case CLANCHIP_SUBCHIP_READMSG_FLAG:
	case	CLANCHIP_APPOINTSUBCHIP_DO:	//클랜부칩 임명 ASP호출
	case CLANCHIP_RELEASESUBCHIP_DO:	//클랜부칩 해임 ASP호출
	case CLANCHIP_LEAVECLAN_PFLAG:
	case CLANCHIP_LEAVECLAN_DO:
	case ISPFLAG_CHIP:
	case CLAN_REMOVE_SHORTCLANWON_LOADING:
	case CLAN_REMOVE_LOADING:
	case CLAN_RELEASE_LOADING:
	case CLAN_CHIP_ReadDATA:

		menuPos[0].left = BackStartPos.x + clanLoading.pos.x;
		menuPos[0].top = BackStartPos.y + clanLoading.pos.y;
		menuPos[0].right = 0;
		menuPos[0].bottom = 0;

		break;
	}
}

int CLANEntity_chip::chkMark(char *clanName)
{
	nChkMark = -1;
	if (!SearchMarkClient(clanName))
	{
		if (!SearchMarkServer(clanName))
			nChkMark = 0;
	}
	else if (SearchMarkClient(clanName))
	{
		if (!SearchMarkServer(clanName))
			nChkMark = 1;
		else
			nChkMark = 2;
	}

	return nChkMark;
}

BOOL CLANEntity_chip::CheckMark(char* filename)
{
	WIN32_FIND_DATA wfd;
	HANDLE hFind;
	char szTemp[50];
	memset(szTemp, 0, sizeof(char) * 50);

	wsprintf(szTemp, "image\\clanDATA\\%s.bmp", filename);
	hFind = FindFirstFile(szTemp, &wfd);

	if (hFind == INVALID_HANDLE_VALUE)
		return FALSE;
	return TRUE;
}

BOOL CLANEntity_chip::SearchMarkClient(char *clanName)
{
	WIN32_FIND_DATA wfd;
	HANDLE hFind;
	char szTemp[50];
	memset(szTemp, 0, sizeof(char) * 50);

	wsprintf(szTemp, "image\\clanDATA\\%s.bmp", clanName);
	hFind = FindFirstFile(szTemp, &wfd);

	if (hFind == INVALID_HANDLE_VALUE)
		return FALSE;

	hClinetMark = LoadDibSurfaceOffscreen(szTemp);

	FindClose(hFind);
	return TRUE;
}

BOOL CLANEntity_chip::SearchMarkServer(char *clanName)
{
	WIN32_FIND_DATA wfd;
	HANDLE hFind;
	char szTemp[50];
	memset(szTemp, 0, sizeof(char) * 50);

	wsprintf(szTemp, "image\\clanDATA\\%s.bmp", clanName);
	hFind = FindFirstFile(szTemp, &wfd);

	if (hFind == INVALID_HANDLE_VALUE)
		return FALSE;

	hServerMark = LoadDibSurfaceOffscreen(szTemp);

	FindClose(hFind);
	return TRUE;
}

void CLANEntity_chip::Draw()
{
	int i = 0, nIconCount = 0;
	int nIconPos = 0;
	char szClanWon[30];
	int nSaveTop = 0, nAdd = 0;
	int nStrLen = 0;

	int bx, by;
	char szTemp[256];
	char szHelpContent[HELPWIDTH];

	char string[500];

	switch (C_menuN)
	{
	case CLANCHIP_SUBCHIP_APPOINTMSG:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		if (cldata.SubChip[0] == 0)
			wsprintf(szDrawMenuMsg, SubChipAppointEnd.szMsg, cldata.OldSubChip);
		else
			wsprintf(szDrawMenuMsg, SubChipAppointEnd.szMsg, cldata.SubChip);
		Draw_C_Text(szDrawMenuMsg, menuPos[1].left, menuPos[1].top);
		break;
	case CLANCHIP_SUBCHIP_RELEASEMSG:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		wsprintf(szDrawMenuMsg, SubChipReleaseEnd.szMsg, cldata.OldSubChip);
		Draw_C_Text(szDrawMenuMsg, menuPos[1].left, menuPos[1].top);
		break;

	case CLANCHIP_SUBCHIP_LIST:
		nIconCount = 11;
		if (nClanWon_Num > DISPLAY_MAX)
		{
			nIconCount += 1;

			DrawSprite(menuPos[nIconCount].left, menuPos[nIconCount].top, hScl_Bar, 0, 0, 8, 160, 1);
			sinDrawTexImage(hScl_icon_tj, (float)scrIconPos.left, (float)scrIconPos.top, 16, 16);

		}
		nIconCount += 1;
		DrawSprite(menuPos[nIconCount].left, menuPos[nIconCount].top, hTxt_SubChip[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		nIconCount += 1;

		sinDrawTexImage(hLine, (float)menuPos[nIconCount].left, (float)menuPos[nIconCount].top, (float)240, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 255);

		nIconCount = 3;
		for (i = 0; i < DISPLAY_MAX; i++)
		{
			if (i == nClanWon_Num) break;
			nIconCount += 1;
			if (banisF[nScl_Bar + i])
				DrawSprite(menuPos[nIconCount].left, menuPos[nIconCount].top, hIcon_Click, 0, 0, 13, 17, 1);
			else
				DrawSprite(menuPos[nIconCount].left, menuPos[nIconCount].top, hIcon, 0, 0, 13, 17, 1);
		}


		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[3].left, menuPos[3].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);
		if (menuMouseOver[1] > 0)
			DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Gray, 0, 0, 32, 16, 1);

		nIconCount = 15;
		nAdd = 0;
		for (i = 0; i < nClanWon_Num; i++)
		{
			if (i >= DISPLAY_MAX)
				break;

			bx = 13;
			by = 17;

			menuPos[nIconCount].left = BackStartPos.x + CLANWONLIST_X + 30;
			menuPos[nIconCount].top = BackStartPos.y + CLANWONLIST_Y + nAdd;
			menuPos[nIconCount].right = (BackStartPos.x + 120) + cldata.clanWonStrLen[i + nScl_Bar];
			menuPos[nIconCount].bottom = menuPos[nIconCount].top + 17;

			nAdd += ICON_ADD;
			nClanWon[nIconCount] = 1;
			nIconCount += 1;
		}

		nIconCount = 15;
		for (i = 0; i < DISPLAY_MAX; i++)
		{
			if (nClanWon[nIconCount])
			{
				if (strcmp(cldata.clanWon[i + nScl_Bar], cldata.SubChip) == 0)
				{
					lstrcpy(szClanWon, cldata.clanWon[i + nScl_Bar]);
					Draw_C_Text2(szClanWon, menuPos[nIconCount].left + 30, menuPos[nIconCount].top);
				}
				else
				{
					ZeroMemory(szClanWon, sizeof(szClanWon));
					lstrcpy(szClanWon, cldata.clanWon[i + nScl_Bar]);
					Draw_C_Text(szClanWon, menuPos[nIconCount].left + 30, menuPos[nIconCount].top);
				}
				nIconCount += 1;
			}
		}

		break;
	case CLANCHIP_RESUBCHIP_APPOINT:		//부 클랜칩 임명 재확인
		DrawSprite(menuPos[3].left, menuPos[3].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[4].left, menuPos[4].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Gray, 0, 0, 32, 16, 1);
		if (menuMouseOver[1] > 0)
			DrawSprite(menuPos[1].left, menuPos[1].top, hNo_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[1].left, menuPos[1].top, hNo_Gray, 0, 0, 32, 16, 1);

		DrawSprite(menuPos[6].left, menuPos[6].top, hTxt_LeaveClan[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);

		sinDrawTexImage(hLine, (float)menuPos[5].left, (float)menuPos[5].top, (float)240, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 255);
		wsprintf(szDrawMenuMsg, SubChipAppoint.szMsg, cldata.clanWon[nSavePos]);
		Draw_C_Text(szDrawMenuMsg, menuPos[2].left, menuPos[2].top);

		break;

	case CLANCHIP_RESUBCHIP_APPOINT_END:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		wsprintf(szDrawMenuMsg, SubChipAppointEnd.szMsg, cldata.clanWon[nSavePos]);
		Draw_C_Text(szDrawMenuMsg, menuPos[1].left, menuPos[1].top);
		break;
	case CLANCHIP_RELEASESUBCHIP:
		DrawSprite(menuPos[3].left, menuPos[3].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[4].left, menuPos[4].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Gray, 0, 0, 32, 16, 1);
		if (menuMouseOver[1] > 0)
			DrawSprite(menuPos[1].left, menuPos[1].top, hNo_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[1].left, menuPos[1].top, hNo_Gray, 0, 0, 32, 16, 1);

		DrawSprite(menuPos[6].left, menuPos[6].top, hTxt_LeaveClan[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);

		sinDrawTexImage(hLine, (float)menuPos[5].left, (float)menuPos[5].top, (float)240, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 255);

		wsprintf(szDrawMenuMsg, SubChipRelease.szMsg, cldata.SubChip);
		Draw_C_Text(szDrawMenuMsg, menuPos[2].left, menuPos[2].top);

		break;
	case CLANCHIP_RELEASESUBCHIP_END:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);


		wsprintf(szDrawMenuMsg, SubChipReleaseEnd.szMsg, cldata.SubChip);//cldata.clanWon[nSavePos]);
		Draw_C_Text(szDrawMenuMsg, menuPos[1].left, menuPos[1].top);
		break;

	case CLAN_CHIP:
		DrawSprite(menuPos[0].left, menuPos[0].top, hClanName, 0, 0, CLANNAME_WIDTH, CLANNAME_HEIGHT, 1);

		if (menuMouseOver[3] > 0)
			DrawSprite(menuPos[3].left, menuPos[3].top, hTxt_Remove[1], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		else
			DrawSprite(menuPos[3].left, menuPos[3].top, hTxt_Remove[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		if (menuMouseOver[4] > 0)
			DrawSprite(menuPos[4].left, menuPos[4].top, hTxt_Release[1], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		else
			DrawSprite(menuPos[4].left, menuPos[4].top, hTxt_Release[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		if (menuMouseOver[5] > 0)
			DrawSprite(menuPos[5].left, menuPos[5].top, hTxt_Help[1], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		else
			DrawSprite(menuPos[5].left, menuPos[5].top, hTxt_Help[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);

		if (menuMouseOver[18] > 0)
			DrawSprite(menuPos[18].left, menuPos[18].top, hTxt_LeaveClan[1], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		else
			DrawSprite(menuPos[18].left, menuPos[18].top, hTxt_LeaveClan[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		if (menuMouseOver[19] > 0)
			DrawSprite(menuPos[19].left, menuPos[19].top, hTxt_SubChip[1], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		else
			DrawSprite(menuPos[19].left, menuPos[19].top, hTxt_SubChip[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);

		DrawSprite(menuPos[1].left, menuPos[1].top, hMark_box, 0, 0, 69, 59, 1);

		if (cldata.hClanMark)
			DrawSprite(menuPos[9].left, menuPos[9].top, cldata.hClanMark, 0, 0, 32, 32, 1);

		DrawSprite(menuPos[7].left, menuPos[7].top, hButton_Box, 0, 0, 48, 23, 1);

		if (menuMouseOver[6] > 0) DrawSprite(menuPos[6].left, menuPos[6].top, hClose[1], 0, 0, 32, 16, 1);
		else DrawSprite(menuPos[6].left, menuPos[6].top, hClose[0], 0, 0, 32, 16, 1);

		nStrLen = lstrlen(cldata.name) / 2;

		if (nStrLen % 2)
		{
			nStrLen = nStrLen / 2;
			nStrLen += 1;
			Draw_C_Text(cldata.name, menuPos[10].left - (nStrLen * 11), menuPos[10].top, 2);
		}
		else
		{
			nStrLen = nStrLen / 2;
			Draw_C_Text(cldata.name, menuPos[10].left - (nStrLen * 11) - 3, menuPos[10].top, 2);
		}

		sinDrawTexImage(hLine, (float)menuPos[17].left, (float)menuPos[17].top, (float)240, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 255);

		break;
	case CLANCHIP_LEAVECLAN_NOLEVEL:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(LeaveClanNoLevel.szMsg, menuPos[1].left, menuPos[1].top);

		break;
	case CLANCHIP_LEAVECLAN_RECONFIRM:
		DrawSprite(menuPos[3].left, menuPos[3].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[4].left, menuPos[4].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Gray, 0, 0, 32, 16, 1);
		if (menuMouseOver[1] > 0)
			DrawSprite(menuPos[1].left, menuPos[1].top, hNo_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[1].left, menuPos[1].top, hNo_Gray, 0, 0, 32, 16, 1);

		wsprintf(szDrawMenuMsg, LeaveClanReConfirm.szMsg, cldata.clanWon[nSavePos]);
		Draw_C_Text(szDrawMenuMsg, menuPos[2].left, menuPos[2].top);

		break;
	case CLANCHIP_LEAVECLAN_CONFIRM:
		DrawSprite(menuPos[3].left, menuPos[3].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[4].left, menuPos[4].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Gray, 0, 0, 32, 16, 1);
		if (menuMouseOver[1] > 0)
			DrawSprite(menuPos[1].left, menuPos[1].top, hNo_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[1].left, menuPos[1].top, hNo_Gray, 0, 0, 32, 16, 1);

		DrawSprite(menuPos[6].left, menuPos[6].top, hTxt_LeaveClan[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		sinDrawTexImage(hLine, (float)menuPos[5].left, (float)menuPos[5].top, (float)240, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 255);
		Draw_C_Text(LeaveClanConfirm.szMsg, menuPos[2].left, menuPos[2].top);

		break;
	case CLANCHIP_LEAVECLAN_MESSAGE:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		wsprintf(szDrawMenuMsg, LeaveClanMessage.szMsg, cldata.OldChipChaName, cldata.ClanZang_Name);
		Draw_C_Text(szDrawMenuMsg, menuPos[1].left, menuPos[1].top);
		break;
	case CLANCHIP_LEAVECLANDOWNLEVEL:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(LeaveClanDownLevel.szMsg, menuPos[1].left, menuPos[1].top);
		break;
	case CLANCHIP_NOSUBCHIP:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(NoSubChip.szMsg, menuPos[1].left, menuPos[1].top);
		break;
	case CLANCHIP_NOLEAVECLAN:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(NoLeaveClan.szMsg, menuPos[1].left, menuPos[1].top);
		break;
	case CLANCHIP_LEAVECLAN_NOMONEY:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(LeaveClanNoMoney.szMsg, menuPos[1].left, menuPos[1].top);
		break;
	case CLANCHIP_LEAVECLAN_SUCESS:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);


		wsprintf(szDrawMenuMsg, LeaveClanSuccess.szMsg, cldata.clanWon[nSavePos]);
		Draw_C_Text(szDrawMenuMsg, menuPos[1].left, menuPos[1].top);
		break;
	case CLANCHIP_LEAVECLAN://이임
		nIconCount = 11;
		if (nClanWon_Num > DISPLAY_MAX)
		{
			nIconCount += 1;
			DrawSprite(menuPos[nIconCount].left, menuPos[nIconCount].top, hScl_Bar, 0, 0, 8, 160, 1);
			sinDrawTexImage(hScl_icon_tj, (float)scrIconPos.left, (float)scrIconPos.top, 16, 16);

		}
		nIconCount += 1;
		DrawSprite(menuPos[nIconCount].left, menuPos[nIconCount].top, hTxt_LeaveClan[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		nIconCount += 1;

		sinDrawTexImage(hLine, (float)menuPos[nIconCount].left, (float)menuPos[nIconCount].top, (float)240, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 255);

		nIconCount = 3;
		for (i = 0; i < DISPLAY_MAX; i++)
		{
			if (i == nClanWon_Num)
				break;
			nIconCount += 1;
			if (banisF[nScl_Bar + i])
				DrawSprite(menuPos[nIconCount].left, menuPos[nIconCount].top, hIcon_Click, 0, 0, 13, 17, 1);
			else
				DrawSprite(menuPos[nIconCount].left, menuPos[nIconCount].top, hIcon, 0, 0, 13, 17, 1);
		}


		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[3].left, menuPos[3].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);
		if (menuMouseOver[1] > 0) DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Yellow, 0, 0, 32, 16, 1);
		else DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Gray, 0, 0, 32, 16, 1);

		nIconCount = 15;
		nAdd = 0;
		for (i = 0; i < nClanWon_Num; i++)
		{
			if (i >= DISPLAY_MAX)
				break;

			bx = 13;
			by = 17;

			menuPos[nIconCount].left = BackStartPos.x + CLANWONLIST_X + 30;
			menuPos[nIconCount].top = BackStartPos.y + CLANWONLIST_Y + nAdd;
			menuPos[nIconCount].right = (BackStartPos.x + 120) + cldata.clanWonStrLen[i + nScl_Bar];
			menuPos[nIconCount].bottom = menuPos[nIconCount].top + 17;

			nAdd += ICON_ADD;
			nClanWon[nIconCount] = 1;
			nIconCount += 1;
		}

		nIconCount = 15;
		for (i = 0; i < DISPLAY_MAX; i++)
		{

			if (nClanWon[nIconCount])
			{
				ZeroMemory(szClanWon, sizeof(szClanWon));
				lstrcpy(szClanWon, cldata.clanWon[i + nScl_Bar]);
				Draw_C_Text(szClanWon, menuPos[nIconCount].left + 30, menuPos[nIconCount].top);
				nIconCount += 1;
			}
		}
		break;
	case CLAN_REMOVE:
		nIconCount = 11;
		if (nClanWon_Num > DISPLAY_MAX)
		{
			nIconCount += 1;


			DrawSprite(menuPos[nIconCount].left, menuPos[nIconCount].top, hScl_Bar, 0, 0, 8, 160, 1);

			sinDrawTexImage(hScl_icon_tj, (float)scrIconPos.left, (float)scrIconPos.top, 16, 16);
		}
		nIconCount += 1;
		DrawSprite(menuPos[nIconCount].left, menuPos[nIconCount].top, hTxt_Remove[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);

		nIconCount = 3;
		for (i = 0; i < DISPLAY_MAX; i++)
		{
			if (i == nClanWon_Num)
				break;
			nIconCount += 1;
			if (banisF[nScl_Bar + i])
				DrawSprite(menuPos[nIconCount].left, menuPos[nIconCount].top, hIcon_Click, 0, 0, 13, 17, 1);
			else
				DrawSprite(menuPos[nIconCount].left, menuPos[nIconCount].top, hIcon, 0, 0, 13, 17, 1);
		}


		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[3].left, menuPos[3].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hRemoveToMenu[1], 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hRemoveToMenu[0], 0, 0, 32, 16, 1);
		if (menuMouseOver[1] > 0)
			DrawSprite(menuPos[1].left, menuPos[1].top, hClose[1], 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[1].left, menuPos[1].top, hClose[0], 0, 0, 32, 16, 1);

		nIconCount = 14;
		nAdd = 0;
		for (i = 0; i < nClanWon_Num; i++)
		{
			if (i >= DISPLAY_MAX)
				break;

			bx = 13;
			by = 17;

			menuPos[nIconCount].left = BackStartPos.x + CLANWONLIST_X + 30;
			menuPos[nIconCount].top = BackStartPos.y + CLANWONLIST_Y + nAdd;
			menuPos[nIconCount].right = (BackStartPos.x + 120) + cldata.clanWonStrLen[i + nScl_Bar];
			menuPos[nIconCount].bottom = menuPos[nIconCount].top + 17;

			nAdd += ICON_ADD;
			nClanWon[nIconCount] = 1;
			nIconCount += 1;
		}

		nIconCount = 14;
		for (i = 0; i < DISPLAY_MAX; i++)
		{

			if (nClanWon[nIconCount])
			{
				ZeroMemory(szClanWon, sizeof(szClanWon));
				lstrcpy(szClanWon, cldata.clanWon[i + nScl_Bar]);
				Draw_C_Text(szClanWon, menuPos[nIconCount].left + 30, menuPos[nIconCount].top);
				nIconCount += 1;
			}
		}
		break;

	case CLAN_REMOVE_SHORTCLANWON:
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

		for (i = 0; i < 5; i++)
		{
			if (szRemoveClanWonResult[i][0])
			{
				Draw_C_Text(szRemoveClanWonResult[i], menuPos[2].left, menuPos[2].top + nAdd);
				nSaveTop = menuPos[2].top + nAdd;
				nAdd += 20;
			}
		}

		if (bRemoveSecondCheck)
			Draw_C_Text(clanRemoveSecond.szMsg, menuPos[2].left, nSaveTop + 20);
		else
			Draw_C_Text(clanszRemoveShortClanWonMsg.szMsg, menuPos[2].left, nSaveTop + 20);
		break;
	case CLAN_REMOVE_SHORTCLANWON_RESULT:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		if (bRemoveSecondCheck)
			Draw_C_Text(clanRemoveSecondResult.szMsg, menuPos[1].left, menuPos[1].top);
		else
			Draw_C_Text(clanRemoveShowrtClanWonResultMsg.szMsg, menuPos[1].left, menuPos[1].top);
		break;
	case CLANCHIP_RELEASEMESSAGE:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);
		Draw_C_Text(clanClanUserRelease.szMsg, menuPos[1].left, menuPos[1].top);
		break;
	case CLAN_REMOVE_RESULT:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(clanReMoveHeaderMsg.szMsg, menuPos[1].left, menuPos[1].top);

		for (i = 0; i < 5; i++)
		{
			if (szRemoveClanWonResult[i][0])
			{
				Draw_C_Text(szRemoveClanWonResult[i], menuPos[1].left, menuPos[1].top + 20 + nAdd);
				nSaveTop = menuPos[1].top + 40 + nAdd;
				nAdd += 20;
			}
		}
		break;
	case CLAN_MARK1:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 8, 27, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Gray, 0, 0, 32, 16, 1);
		DrawSprite(menuPos[3].left, menuPos[3].top, hTxt_Mark[1], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);

		wsprintf(string, "%s", szMark1);
		Draw_C_Text(string, menuPos[1].left, menuPos[1].top);
		break;
	case CLAN_MARK2:
		DrawSprite(menuPos[4].left, menuPos[4].top, hButton_Box, 0, 0, 48, 27, 1);
		DrawSprite(menuPos[5].left, menuPos[5].top, hButton_Box, 0, 0, 48, 27, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);
		if (menuMouseOver[1] > 0)
			DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Gray, 0, 0, 32, 16, 1);

		DrawSprite(menuPos[6].left, menuPos[6].top, hTxt_Mark[1], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		wsprintf(string, "%s", szMark2);
		Draw_C_Text(string, menuPos[2].left, menuPos[2].top);

		break;
	case CLAN_MARK3:
		DrawSprite(menuPos[5].left, menuPos[5].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[6].left, menuPos[6].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[7].left, menuPos[7].top, hTxt_Mark[1], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);
		if (menuMouseOver[1] > 0)
			DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Gray, 0, 0, 32, 16, 1);

		DrawSprite(menuPos[2].left, menuPos[2].top, hClinetMark, 0, 0, 32, 32, 1);
		DrawSprite(menuPos[3].left, menuPos[3].top, hServerMark, 0, 0, 32, 32, 1);

		wsprintf(string, "%s", szMark3);
		Draw_C_Text(string, menuPos[4].left, menuPos[4].top);

		break;

	case CLAN_RELEASE:

		DrawSprite(menuPos[3].left, menuPos[3].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[4].left, menuPos[4].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Gray, 0, 0, 32, 16, 1);
		if (menuMouseOver[1] > 0)
			DrawSprite(menuPos[1].left, menuPos[1].top, hNo_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[1].left, menuPos[1].top, hNo_Gray, 0, 0, 32, 16, 1);

		DrawSprite(menuPos[5].left, menuPos[5].top, hTxt_Release[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);

		Draw_C_Text(clanMsg15.szMsg, menuPos[2].left, menuPos[2].top);

		break;
	case CLAN_RECONF_RELEASE:
		DrawSprite(menuPos[3].left, menuPos[3].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[4].left, menuPos[4].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Gray, 0, 0, 32, 16, 1);
		if (menuMouseOver[1] > 0)
			DrawSprite(menuPos[1].left, menuPos[1].top, hNo_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[1].left, menuPos[1].top, hNo_Gray, 0, 0, 32, 16, 1);

		DrawSprite(menuPos[5].left, menuPos[5].top, hTxt_Release[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		Draw_C_Text(szReconfReleaseMsg, menuPos[2].left, menuPos[2].top);
		break;
	case CLAN_FINISH_RELEASE:
		DrawSprite(menuPos[1].left, menuPos[1].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		DrawSprite(menuPos[2].left, menuPos[2].top, hTxt_Release[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		Draw_C_Text(clanFinishReleaseMsg.szMsg, menuPos[3].left, menuPos[3].top);

		break;

	case CLAN_HELP:

		DrawSprite(menuPos[1].left, menuPos[1].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);
		nIconPos = 2;
		for (i = 0; i < CLANHELPICON_DISPLAY_MAX; i++)
		{
			if (i == g_nClanIconNum) break;
			if (menuMouseOver[nIconPos] > 0)
				DrawSprite(menuPos[nIconPos].left, menuPos[nIconPos].top, hClanHelpIcon[i + nScl_Bar][0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
			else
				DrawSprite(menuPos[nIconPos].left, menuPos[nIconPos].top, hClanHelpIcon[i + nScl_Bar][1], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);

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
	case CLAN_HELP_CONTENT:


		DrawSprite(menuPos[1].left, menuPos[1].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		DrawSprite(menuPos[2].left, menuPos[2].top, hTxt_Help[0], 0, 0, CLANTEXT_IMAGE_WIDTH, CLANTEXT_IMAGE_HEIGHT, 1);
		DrawSprite(menuPos[3].left, menuPos[3].top, hBt_Help, 0, 0, 30, 30, 1);

		sinDrawTexImage(hLine, (float)menuPos[4].left, (float)menuPos[4].top,
			(float)240, 10.0f,
			0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 255);

		nIconPos = 5;
		if (g_HelpDisPlay > HLEPDISPLAY_MAX)
		{
			DrawSprite(menuPos[nIconPos].left, menuPos[nIconPos].top, hScl_Bar,
				0, 0, 8, 160, 1);
			sinDrawTexImage(hScl_icon_tj, (float)scrIconPos.left, (float)scrIconPos.top, 16, 16);
		}
		nIconPos = 7;
		for (i = 0; i < HLEPDISPLAY_MAX; i++)
		{
			if (i == g_HelpDisPlay) break;

			ZeroMemory(szHelpContent, sizeof(char)*HELPWIDTH);

			STRINGCOPY(szHelpContent, HelpContents[i + nScl_Bar].szHelpContent);
			Draw_C_Text(szHelpContent, menuPos[nIconPos].left, menuPos[nIconPos].top);
			nIconPos += 1;
		}

		break;

	case CLANCHIP_MAKE_FIRSTMESSAGE:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);
		Draw_C_Text(szDrawMenuMsg, menuPos[1].left, menuPos[1].top);
		break;
	case CLANCHIP_DOWN6_CLANWON_MESSAGE:
	case CLANCHIP_DOWN6_CLANWON:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		if (cldata.bIsOneDay)
		{
			wsprintf(szTemp, "시간 : %d : %d 남았습니다", cldata.nMinute, cldata.nHour);
			wsprintf(szDrawMenuMsg, szClanWon6Down, szTemp);
			Draw_C_Text(szDrawMenuMsg, menuPos[1].left, menuPos[1].top);
		}
		else
		{
			wsprintf(szTemp, "날짜 : %d일 남았습니다", cldata.nLastDay);
			wsprintf(szDrawMenuMsg, szClanWon6Down, szTemp);
			Draw_C_Text(szDrawMenuMsg, menuPos[1].left, menuPos[1].top);
		}
		break;

	case CLAN_NOMAKE:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		if (cldata.bIsOneDay)
			Draw_C_Text(szDrawMenuMsg, menuPos[1].left, menuPos[1].top);
		else
			Draw_C_Text(szDrawMenuMsg, menuPos[1].left, menuPos[1].top);
		break;

	case CLANCHIP_SUBCHIP_APPOINT_FLAG:		//클랜부침이 임명되어다는 플래그세팅
	case CLANCHIP_SUBCHIP_RELEASE_FLAG:		//클랜부침이 해임되어다는 플래그세팅	
	case CLANUSER_SUBCHIP_READMSG_FLAG:		//클랜유저가 부침관련 메세지를 읽어다는 플래그 세팅

	case	CLANCHIP_APPOINTSUBCHIP_DO:		//클랜부칩 임명 ASP호출
	case CLANCHIP_RELEASESUBCHIP_DO:		//클랜부칩 해임 ASP호출
	case CLANCHIP_LEAVECLAN_PFLAG:
	case CLANCHIP_LEAVECLAN_DO:
	case ISPFLAG_CHIP:
	case CLAN_REMOVE_SHORTCLANWON_LOADING:
	case CLAN_REMOVE_LOADING:
	case CLAN_RELEASE_LOADING:
	case CLAN_CHIP_ReadDATA:
		Draw_C_Text(clanLoading.szMsg, menuPos[0].left, menuPos[0].top);
		break;
	}
}