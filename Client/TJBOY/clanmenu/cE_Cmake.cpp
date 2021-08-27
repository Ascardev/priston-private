#include "StdAfx.h"
#define CE_CMAKE_CPP

#include "tjclanDEF.h"
#include "../../SrcLang/jts.h"
#include "..\\..\\HoBaram\\HoTextFile.h"

#include "tjclan.h"
#include "cE_Cmake.h"
#include "cE_report.h"
#include "cE_CViewClanInfo.h"
#include "..\\isaocheck\\auth.h"
#include "..\\isaocheck\\isaocheck.h"
#include "..\\ygy\\ygyheader.h"
#include "..\\..\\CurseFilter.h"	//IsCurse 함수부분(해외)

//HWND hFocusWnd를 사용하고 있는지의 여부를 알아냄.
int usehFocus = 0;
int oldLIMITchattingWnd = 0;
extern char	szConnServerName[16];	//접속한 서버이름이 들어있는 버퍼
extern int g_ClanMakeMoney;


CLANEntity_make::CLANEntity_make()
{
	m_bEventClanMoney = false;
}
CLANEntity_make::~CLANEntity_make()
{

}

int CLANEntity_make::Init(int Life)
{
	life = Life;
	ZeroMemory(szClanMakeMsg, sizeof(szClanMakeMsg));
	return 1;
}

int CLANEntity_make::Clear()
{
	return 1;
}


void CLANEntity_make::Main()
{
	char szFile[256];
	char szFile2[256];
	char server;
	char UniqueClanMark[64];
	int  nMoney = 500000;
	if (life == 0) return;

	int i;
	switch (C_menuN)
	{
	case CLAN_ABILITYDOWN:
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
	case CLANMAKE_REAMMAKR_ERROR:
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
	case CLAN_GO_MAKE:
		C_menuN = CLAN_isCheckClanJang;
		menuInit(C_menuN);
		C_menuN2 = 1;
		break;
	case CLAN_isCheckClanJang_LOADING:
		if (ANSdata.ret_val != -1) C_menuN = CLAN_isCheckClanJang;
		break;

	case CLAN_isCheckClanJang:			//ktj 이 id가 클랜장으로 등록되어있지 않은경우만 클랜을 만들수있으므로
		switch (C_menuN2) {				//    그것에 대한 체크를 한다.
		case 1:
			ANSdata.ret_val = -1;
			WebDB.Resume();		//웹db를 재개한다.
			WebDB.isCheckClanJang(cldata.szID, cldata.gserver);
			C_menuN2 = 2;
			break;
		case 2:

			switch (ANSdata.ret_val)
			{
			case -1:
				//C_menuN = CLAN_isCheckClanJang_LOADING;
				//menuInit(C_menuN);
				break;
			case 1://클랜장으로 등록되어 있음				
				WebDB.Suspend();
				C_menuN2 = 0;
				//ygy : 꼭 살릴것
				//wsprintf(szErrorMsg, szisCheckClanJangErrorMsg);
				C_menuN = CLAN_isCheckClanJang_Result;
				menuInit(C_menuN);
				//cClanReport.InitMsg(szisCheckClanJangErrorMsg);
				break;
			case 0://클랜장으로 등록되어 있지 않음
				WebDB.Suspend();
				C_menuN2 = 0;
				C_menuN = CLAN_MAKE_is;
				menuInit(C_menuN);
				//=============================================================
				cldata.myPosition = CLANNO_REGESTER;
				ZeroMemory(cldata.name, sizeof(cldata.name));
				ZeroMemory(cldata.explanation, sizeof(cldata.explanation));
				ZeroMemory(cldata.ClanZang_Name, sizeof(cldata.ClanZang_Name));
				ZeroMemory(cldata.ClanMark, sizeof(cldata.ClanMark));
				cldata.intClanMark = 0;
				ZeroMemory(cldata.PFlag, sizeof(cldata.PFlag));
				//=============================================================
				//CLAN_ERROR_ret=CLAN_NAME_is;		//에러메뉴보여준후 다시 돌아갈곳.
				break;

			case 100:								//클랜을 만든것이 성공(클랜마크설명메뉴로..)
				//fd2(" 답받음. ret_val== 100 ");
				WebDB.Suspend();
				C_menuN2 = 0;

				//ygy : 꼭 살릴것
				wsprintf(szErrorMsg, "%s (1)", clanszError_Msg.szMsg);
				C_menuN = CLAN_ERROR;
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;		//에러메뉴보여준후 다시 돌아갈곳.
				break;
			case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				//ygy : 꼭 살릴것
				wsprintf(szErrorMsg, "%s (0)", clanszError_Msg.szMsg);
				C_menuN = CLAN_ERROR;
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;		//에러메뉴보여준후 다시 돌아갈곳.
				break;

			default:
				if (ANSdata.ret_val != -1) {		//전혀엉뚱한 답이 와서 에러가 났다.
					WebDB.Suspend();
					C_menuN2 = 0;
					//ygy : 꼭 살릴것
					wsprintf(szErrorMsg, "%s (2)", clanszError_Msg.szMsg);
					C_menuN = CLAN_ERROR;
					cClanReport.InitMsg(szErrorMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					CLAN_ERROR_ret = CLAN_AllEnd;		//에러메뉴보여준후 다시 돌아갈곳.
				}
				break;
			}
			break;
		}
		break;
	case CLANMAKE_NOMONEY:
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

				C_menuN2 = -1;
				CLAN_ERROR_ret = -1;
				break;
			default:
				i = i;
				break;

			}
		}
		break;
	case CLAN_isCheckClanJang_Result:
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
	case CLAN_MAKE_is:
		i = chkeckMenuN();
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
				if ((cldata.money - g_ClanMakeMoney) < 0) {	//돈이 없으면 255로 간다.				
								//if((cldata.money-0) < 0) {	//돈이 없으면 255로 간다.				
					//ygy : 꼭 살릴것
					//wsprintf(szErrorMsg, szMoneyErrorMsg );
					C_menuN = CLANMAKE_NOMONEY;
					menuInit(C_menuN);
					//menuInit(C_menuN);
					//cClanReport.InitMsg(szMoneyErrorMsg);

					CLAN_ERROR_ret = CLAN_AllEnd;		//에러메뉴보여준후 다시 돌아갈곳.
					break;
				}


				if (cldata.ability < ABILITY) {	//능력치가 부족하여 에러 처리
					//ygy : 꼭 살릴것
					//wsprintf(szErrorMsg, szAbilityErrorMsg);
					C_menuN = CLAN_ABILITYDOWN;
					menuInit(C_menuN);
					CLAN_ERROR_ret = CLAN_AllEnd;		//에러메뉴보여준후 다시 돌아갈곳.
					break;
				}


				//ktj : 이부분 다시 열것:
				C_menuN = CLAN_MONEY_is;			//Y : 클랜결성하겟다.  대금지불의사로간다.
				menuInit(C_menuN);

				break;

			case 1: //클랜 만들기를 취소
				//ygy : 꼭 살릴것
				//wsprintf(szErrorMsg, szCancelMakeClan );
				C_menuN = CLAN_ERROR;			//취소
				cClanReport.InitMsg(clanCancelMakeClan.szMsg);
				cClanReport.menuInit(C_menuN, clanCancelMakeClan.pos.x, clanCancelMakeClan.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;		//에러메뉴보여준후 다시 돌아갈곳.
				break;

			default:
				break;
			}
		}
		break;
		//================================================
	case CLAN_MONEY_is:					// 대금지불의사묻기
		i = chkeckMenuN();				//================================================
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
		//ygy : 꼭 살릴것
		if (MOUSE0())
		{
			MOUSE0() = 0;
			switch (i)
			{
			case 0:

				//ktj : 돈 감소시키기. : 여기서 안하고 다 만들어지면 한다.
				//int sinMinusMoney(int Money);
				//sinMinusMoney(500000);

				//복구시에 넣는다.
				//int sinPlusMoney(int Money);
				//sinPlusMoney(500000);

				C_menuN = CLAN_NAME_is;		//Y : 대금지불한다. 클랜이름설정으로 간다.
				keydownEnt = 0;				//CLAN_NAME_is 에서 엔터키사용여부임에주의
				menuInit(C_menuN);
				C_menuN2 = -1;
				break;

			case 1:
				//ygy : 꼭 살릴것
				//wsprintf(szErrorMsg, szCancelMakeClan );

				C_menuN = CLAN_ERROR;			//취소
				cClanReport.InitMsg(clanCancelMakeClan.szMsg);
				cClanReport.menuInit(C_menuN, clanCancelMakeClan.pos.x, clanCancelMakeClan.pos.y);
				//menuInit(C_menuN);
				CLAN_ERROR_ret = CLAN_AllEnd;		//에러메뉴보여준후 다시 돌아갈곳.
				break;

			default:
				break;
			}
		}
		break;
		//================================================
	case CLAN_NAME_is:					//클랜이름 설정.
										//================================================

		//START ==================== 주의 : 클랜이름을 서버에 넘겨주고 맞는지확인하는루틴으로 확인버튼을 누른후 실행되어짐
		switch (C_menuN2) {
		case 1:
			ANSdata.ret_val = -1;
			WebDB.Resume();		//웹db를 재개한다.
			WebDB.isCheckClanName(cldata.name, cldata.gserver);
			C_menuN2 = 2;
			break;
		case 2:

			switch (ANSdata.ret_val)
			{
			case 0://클랜이름이 중복되지 않음
				WebDB.Suspend();
				C_menuN2 = 0;
				C_menuN = CLAN_MARK_expl;;
				menuInit(C_menuN);

				break;
			case 1://클랜이름이 중복됨

				WebDB.Suspend();
				C_menuN2 = 0;

				C_menuN = CLAN_NAME_BEING;
				menuInit(C_menuN);
				break;

			case 100:								//클랜을 만든것이 성공(클랜마크설명메뉴로..)				
				WebDB.Suspend();
				C_menuN2 = 0;

				wsprintf(szErrorMsg, "%s (3)", clanszError_Msg.szMsg);
				C_menuN = CLAN_ERROR;
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;		//에러메뉴보여준후 다시 돌아갈곳.				

				break;
			case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				wsprintf(szErrorMsg, "%s (4)", clanszError_Msg.szMsg);

				C_menuN = CLAN_ERROR;
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);

				break;

			default:
				if (ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					C_menuN2 = 0;
					wsprintf(szErrorMsg, "%s (5)", clanszError_Msg.szMsg);
					C_menuN = CLAN_ERROR;
					cClanReport.InitMsg(szErrorMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					CLAN_ERROR_ret = CLAN_AllEnd;		//에러메뉴보여준후 다시 돌아갈곳.
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
		default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}

		//ygy : 클랜이름 넣을때 엔터키 관련 꼭 살릴것
		if (keydownEnt == 1) {
			keydownEnt = 0;
			goto keydownenter;
		}

		if (MOUSE0())
		{
			MOUSE0() = 0;
			switch (i)
			{
			case 0:

			keydownenter:
				if (cldata.name[0] == 0)
				{

					SendMessage(hFocusWnd, EM_SETLIMITTEXT, oldLIMITchattingWnd, 0);	//원래78자임
					hFocusWnd = 0;
					usehFocus = 0;
					SetIME_Mode(0);
					C_menuN = CLAN_NONAME;
					menuInit(C_menuN);
					break;
				}
				C_menuN2 = 1;

				SendMessage(hFocusWnd, EM_SETLIMITTEXT, oldLIMITchattingWnd, 0);	//원래78자임
				hFocusWnd = 0;				//입력받는부분삭제.
				usehFocus = 0;
				SetIME_Mode(0);

				break;

			default:
				break;
			}
		}
		break;
	case CLAN_NONAME:
		i = chkeckMenuN();
		switch (i) {
		case 0:
			menuMouseOver[0] = 1;
			break;
		default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}
		//ygy : 꼭 살릴것
		if (MOUSE0())
		{
			MOUSE0() = 0;
			switch (i)
			{
			case 0:
				C_menuN = CLAN_NAME_is;
				menuInit(C_menuN);
				//C_menuN2 =-1;
				//CLAN_ERROR_ret=-1;
				break;
			}
		}
		break;
	case CLAN_NAME_BEING:
		i = chkeckMenuN();
		switch (i) {
		case 0:
			menuMouseOver[0] = 1;
			break;
		default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}
		//ygy : 꼭 살릴것
		if (MOUSE0())
		{
			MOUSE0() = 0;
			switch (i)
			{
			case 0:
				C_menuN = CLAN_NAME_is;		//나가기 : 끝내는걸로간다.
				menuInit(C_menuN);

				//C_menuN2 =-1;
				//CLAN_ERROR_ret=-1;
				break;
			}
		}
		break;
		//================================================
	case CLAN_MARK_expl:			//클랜마크설명
									//================================================
		i = chkeckMenuN();
		switch (i) {
		case 0:
			menuMouseOver[0] = 1;
			break;
		default:
			memset(menuMouseOver, -1, sizeof(int) * 30);

			break;
		}

		//ygy : 꼭 살릴것
		if (MOUSE0())
		{
			MOUSE0() = 0;
			switch (i)
			{
			case 0:
				C_menuN = CLAN_INSPECTION_expl;		//확인 : 심사기간설명으로 간다.
				menuInit(C_menuN);
				break;

			}
		}
		break;

		//================================================
	case CLAN_INSPECTION_expl:		//심사기간설명
									//================================================
		//START ==================== 주의 : 클랜이름을 서버에 넘겨주고 맞는지확인하는루틴으로 확인버튼을 누른후 실행되어짐
		switch (C_menuN2)
		{
		case 1:
			ANSdata.ret_val = -1;
			WebDB.Resume();		//웹db를 재개한다.
			WebDB.make_Clan(cldata.szID, cldata.gserver, cldata.ChaName, cldata.name, "설명없음.", sinChar->iClass, sinChar->iLevel);

			C_menuN2 = 2;
			break;
		case 2:


			switch (ANSdata.ret_val)
			{
			case 0://트랜잭션 오류
				WebDB.Suspend();
				//ygy : 꼭 살릴것
				//wsprintf(szErrorMsg, szTranzationError);

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (6)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				//menuInit(C_menuN);
				CLAN_ERROR_ret = CLAN_AllEnd;		//에러메뉴보여준후 다시 돌아갈곳.
				break;
			case 1://삽입 성공

				WebDB.Suspend();
				C_menuN2 = 0;
				cldata.myPosition = CLANCHIP;
				C_menuN = CLANMAKE_DOWN_INFO;
				menuInit(C_menuN);

				int sinMinusMoney(int Money, int Kind = 0);
				sinMinusMoney(g_ClanMakeMoney);

				break;
			case 2://캐릭터가 이미 다른 클랜에 소속
				WebDB.Suspend();
				C_menuN2 = 0;
				//ygy : 꼭 살릴것
				wsprintf(szErrorMsg, "%s (7)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				C_menuN = CLAN_ERROR;
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_NAME_is;		//에러메뉴보여준후 다시 돌아갈곳.
				break;
			case 3://클랜이름 중복
				WebDB.Suspend();
				C_menuN2 = 0;
				//ygy : 꼭 살릴것
				//wsprintf(szErrorMsg, szClanNameError);
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (8)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				//menuInit(C_menuN);
				CLAN_ERROR_ret = CLAN_NAME_is;		//에러메뉴보여준후 다시 돌아갈곳.
				break;

			case 100:								//클랜을 만든것이 성공(클랜마크설명메뉴로..)				
				WebDB.Suspend();
				C_menuN2 = 0;

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (9)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;		//에러메뉴보여준후 다시 돌아갈곳.
				break;
			case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (10)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);

				break;
			default:
				if (ANSdata.ret_val != -1) {		//전혀엉뚱한 답이 와서 에러가 났다.
					WebDB.Suspend();
					C_menuN2 = 0;
					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (11)", clanszError_Msg.szMsg);
					cClanReport.InitMsg(szErrorMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					CLAN_ERROR_ret = CLAN_AllEnd;		//에러메뉴보여준후 다시 돌아갈곳.
				}
				break;
			}
			break;
		}
		//END ==================== 주의 : 클랜이름을 서버에 넘겨주고 맞는지확인하는루틴으로 확인버튼을 누른후 실행되어짐.
		i = chkeckMenuN();
		switch (i) {
		case 0:
			menuMouseOver[0] = 1;
			break;
		case 3:
			menuMouseOver[3] = 1;
			break;
		default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}
		//ygy : 꼭 살릴것
		if (MOUSE0())
		{
			MOUSE0() = 0;
			switch (i)
			{
			case 0:
				//C_menuN =CLAN_AllEnd;	//확인 : 끝내는걸로간다.
				//C_menuN = CLAN_MAKE_FINISH;
				C_menuN2 = 1;
				break;
			case 3:
				//ygy : 꼭 살릴것
				//wsprintf(szErrorMsg, szCancelMakeClan);
				C_menuN = CLAN_ERROR;
				cClanReport.InitMsg(clanCancelMakeClan.szMsg);
				cClanReport.menuInit(C_menuN, clanCancelMakeClan.pos.x, clanCancelMakeClan.pos.y);
				CLAN_ERROR_ret = CLAN_AllEnd;		//에러메뉴보여준후 다시 돌아갈곳.
				//C_menuN =CLAN_AllEnd
				break;
			}
		}
		break;
		//================================================
	case CLAN_NotMake:				//클랜결성못하니 돌아가라
									//================================================
		i = chkeckMenuN();
		switch (i) {
		case 0:
			menuMouseOver[0] = 1;
			break;
		default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}
		//ygy : 꼭 살릴것
		if (MOUSE0())			//눌렀을경우
		{
			MOUSE0() = 0;
			switch (i)
			{
			case 0:
				C_menuN = CLAN_AllEnd;	//확인 : 끝내는걸로간다.
				break;
			}
		}
		break;
	case CLANMAKE_DOWN_INFO:
		switch (C_menuN2) {
		case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();		//웹db를 재개한다.
			WebDB.isClanMember(cldata.szID, cldata.gserver, cldata.ChaName);		//이 id가 클랜원인지를 파악한다.						
			C_menuN2 = 1;
			break;
		case 1:

			//if(ANSdata.ret_val != -1) 
			//	ANSdata.ret_val= ANSdata.ret_val;			

			switch (ANSdata.ret_val)
			{
			case 0://무등록   				
				WebDB.Suspend();
				bIsLoading = FALSE;
				C_menuN = CLAN_AllEnd;
				cldata.myPosition = CLANNO_REGESTER;
				C_menuN2 = -1;
				CLAN_ERROR_ret = -1;

				break;


			case 1://클랜원등록
				WebDB.Suspend(); //웹db 중지
				bIsLoading = FALSE;
				//ygy : 꼭 살릴것
				ParsingIsClanMember(ANSdata.ret_Buf);
				cldata.myPosition = CLANUSER;			//클랜원 포지션 코드는 100번임				
				C_menuN2 = 0;
				//C_menuN=UPDATE_CLANWON;
				//C_menuN=CLAN_AllEnd;

#ifdef VOICE_CHAT
				if (bCheckClan)
				{
					g_CtrlProcess.SetSelectCha(cldata.szID, cldata.ChaName,
						cldata.name, (DWORD)atoi(cldata.ClanMark), cldata.myPosition);
					//bCheckClan = FALSE;

				}
#endif

				break;

			case 2://클랜장등록
				WebDB.Suspend(); //웹db 중지
				//bIsLoading = FALSE;
				//ygy : 꼭 살릴것
				ParsingIsClanMember(ANSdata.ret_Buf);
				WriteMyClanInfo();
				C_menuN2 = 0;
				C_menuN = CLANMAKE_READ_CLANMARK;
				menuInit(C_menuN);
				//C_menuN=UPDATE_CLANWON;
				//C_menuN=CLAN_AllEnd;
				cldata.myPosition = CLANCHIP;				//클랜장 포지션 코드는 101번임
#ifdef VOICE_CHAT
				if (bCheckClan)
				{
					g_CtrlProcess.SetSelectCha(cldata.szID, cldata.ChaName,
						cldata.name, (DWORD)cldata.intClanMark, cldata.myPosition);
					//bCheckClan = FALSE;

				}
#endif

				break;
			case 3: //클랜이 해체됨
				WebDB.Suspend();
				ParsingIsClanMember2(ANSdata.ret_Buf);
				bIsLoading = FALSE;
				C_menuN2 = 0;
				C_menuN = CLAN_AllEnd;
				cldata.myPosition = CLANNO_REGESTER;

#ifdef VOICE_CHAT
				if (bCheckClan)
				{
					g_CtrlProcess.SetSelectCha(cldata.szID, cldata.ChaName,
						NULL, 0, cldata.myPosition);
					//bCheckClan = FALSE;

				}
#endif

				break;
			case 100:
				WebDB.Suspend();
				cldata.myPosition = CLAN_NOCONNECT;
				C_menuN = CLAN_AllEnd;
				menuInit(C_menuN);
				break;
			case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				cldata.myPosition = CLAN_NOCONNECT;
				C_menuN = CLAN_AllEnd;
				menuInit(C_menuN);

				break;
			default:
				if (ANSdata.ret_val != -1) {		//전혀엉뚱한 답이 와서 에러가 났다.
					WebDB.Suspend();
					bIsLoading = FALSE;
					C_menuN2 = 0;
					C_menuN = CLAN_AllEnd;
					cldata.myPosition = CLAN_NOCONNECT;
				}
			}
		}
		break;
		//======================================================================
	case CLANMAKE_READ_CLANMARK:
		//======================================================================

		switch (C_menuN2) {
		case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();
			WebDB.MarkREAD(cldata.name, cldata.ClanMark);
			C_menuN2 = 1;
			break;
		case 1:

			if (ANSdata.ret_val != -1)
				ANSdata.ret_val = ANSdata.ret_val;


			switch (ANSdata.ret_val)
			{
			case 1:
				WebDB.Suspend();
				server = cldata.ClanMark[0];
				lstrcpy(UniqueClanMark, &cldata.ClanMark[3]);
				wsprintf(szFile, "%s\\%s\\%c_%s.%s", SAVE_DIR, szConnServerName, server, UniqueClanMark, SAVE_EXE);
				wsprintf(szFile2, "%s\\%s\\%c_%s_16.%s", SAVE_DIR, szConnServerName, server, UniqueClanMark, SAVE_EXE);

				DELET(cldata.hClanMark16);
				DELET(cldata.hClanMark);

				cldata.hClanMark16 = LoadDibSurfaceOffscreen(szFile2);
				cldata.hClanMark = LoadDibSurfaceOffscreen(szFile);


				C_menuN = CLAN_MAKE_FINISH;
				menuInit(C_menuN);
				C_menuN2 = -1;

				break;
			case 2:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (65)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);

				C_menuN2 = -1;
				break;
			case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (66)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);

				C_menuN2 = -1;
				break;
			default:
				if (ANSdata.ret_val != -1)
				{
					WebDB.Suspend();

					C_menuN = CLAN_AllEnd;
					C_menuN2 = -1;
					CLAN_ERROR_ret = -1;
				}
				break;
			}
		}
		break;
	case CLAN_MAKE_FINISH:
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
				C_menuN2 = -1;
				CLAN_ERROR_ret = -1;
				break;
			}
		}
		break;
	}

}
void CLANEntity_make::RenderMain()
{
	if (life == 0)
		return;
}
void CLANEntity_make::menuInit(int num)
{
	int bx = 0, by = 0;

	switch (num)
	{
	case CLAN_ABILITYDOWN:
		menuSu = 3;

		bx = 64;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		menuPos[1].left = BackStartPos.x + clanAbilityErrorMsg.pos.x;
		menuPos[1].top = BackStartPos.y + clanAbilityErrorMsg.pos.y;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		break;
	case CLANMAKE_REAMMAKR_ERROR:
		menuSu = 3;

		bx = 64;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		menuPos[1].left = BackStartPos.x + 30;
		menuPos[1].top = BackStartPos.y + 40;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		break;
	case CLANMAKE_NOMONEY:
		menuSu = 3;

		bx = 64;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		menuPos[1].left = BackStartPos.x + clanMoneyErrorMsg.pos.x;
		menuPos[1].top = BackStartPos.y + clanMoneyErrorMsg.pos.y;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		break;
	case CLAN_isCheckClanJang_Result:
		menuSu = 3;

		bx = 64;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		menuPos[1].left = BackStartPos.x + 18;
		menuPos[1].top = BackStartPos.y + 40;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		break;
	case CLANMAKE_DOWN_INFO:
		menuPos[0].left = BackStartPos.x + clanClanMakedowninfo.pos.x;
		menuPos[0].top = BackStartPos.y + clanClanMakedowninfo.pos.y;
		menuPos[0].right = 0;
		menuPos[0].bottom = 0;
		break;
	case CLANMAKE_READ_CLANMARK:
		menuPos[0].left = BackStartPos.x + clanClanMakedowninfo.pos.x;
		menuPos[0].top = BackStartPos.y + clanClanMakedowninfo.pos.y;
		menuPos[0].right = 0;
		menuPos[0].bottom = 0;
		break;
	case CLAN_isCheckClanJang:
		menuPos[0].left = BackStartPos.x + clanLoading.pos.x;
		menuPos[0].top = BackStartPos.y + clanLoading.pos.y;
		menuPos[0].right = 0;
		menuPos[0].bottom = 0;
		break;
	case CLAN_MAKE_is:
		menuSu = 2;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON2_X;
		menuPos[0].top = BackStartPos.y + +BUTTON2_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		bx = 32;
		by = 16;

		menuPos[1].left = BackStartPos.x + BUTTON3_X;
		menuPos[1].top = BackStartPos.y + BUTTON3_Y;
		menuPos[1].right = menuPos[1].left + bx;
		menuPos[1].bottom = menuPos[1].top + by;

		menuPos[2].left = BackStartPos.x + clanMake1.pos.x;
		menuPos[2].top = BackStartPos.y + clanMake1.pos.y;
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
	case CLAN_MONEY_is:
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

		//텍스트 출력 위치
		menuPos[2].left = BackStartPos.x + clanMake2.pos.x;
		menuPos[2].top = BackStartPos.y + clanMake2.pos.y;
		menuPos[2].right = menuPos[2].left + 280;
		menuPos[2].bottom = menuPos[2].top + 250;

		bx = 68;
		by = 27;


		menuPos[3].left = BackStartPos.x + BUTTON2_BOX_X;		//yes 테두리 박스
		menuPos[3].top = BackStartPos.y + BUTTON2_BOX_Y;
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;

		bx = 68;
		by = 27;

		menuPos[4].left = BackStartPos.x + BUTTON3_BOX_X;		//no 테두리 박스
		menuPos[4].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;

		break;
	case CLAN_NAME_is: //클랜 명칭
		if (hFocusWnd == 0)
		{
			ZeroMemory(cldata.name, sizeof(cldata.name));
			hFocusWnd = hTextWnd;
			SetWindowText(hFocusWnd, "");

			oldLIMITchattingWnd = SendMessage(hFocusWnd, EM_GETLIMITTEXT, 0, 0);
			SendMessage(hFocusWnd, EM_SETLIMITTEXT, 12, 0);
			usehFocus = 1;
		}

		menuSu = 2;

		bx = 32;
		by = 16;


		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		//텍스트 출력 위치
		menuPos[2].left = BackStartPos.x + 60;
		menuPos[2].top = BackStartPos.y + 40;
		menuPos[2].right = menuPos[2].left + 190;
		menuPos[2].bottom = menuPos[2].top + 180;

		bx = 68;
		by = 27;


		menuPos[3].left = BackStartPos.x + BUTTON1_BOX_X;		//확인 테두리 박스
		menuPos[3].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;

		bx = 68;
		by = 27;

		menuPos[4].left = BackStartPos.x + CLANINPUTNAME_X;		//클랜 이름 입력
		menuPos[4].top = BackStartPos.y + CLANINPUTNAME_Y;
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;


		break;
	case CLAN_NONAME:
		//menuSu = 3;			
		menuSu = 1;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		//텍스트 출력 위치
		menuPos[1].left = BackStartPos.x + clanNoName.pos.x;
		menuPos[1].top = BackStartPos.y + clanNoName.pos.y;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;
		break;
	case CLAN_NAME_BEING:
		menuSu = 3;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		//텍스트 출력 위치
		menuPos[1].left = BackStartPos.x + clanClanNameError.pos.x;
		menuPos[1].top = BackStartPos.y + clanClanNameError.pos.y;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;
		break;
	case CLAN_MARK_expl: //클랜 마크 확인
		menuSu = 1;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		//텍스트 출력 위치
		menuPos[1].left = BackStartPos.x + clanMake4.pos.x;
		menuPos[1].top = BackStartPos.y + clanMake4.pos.y;
		menuPos[1].right = menuPos[1].left + 190;
		menuPos[1].bottom = menuPos[1].top + 180;

		bx = 68;
		by = 27;


		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인 테두리 박스
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;
		break;
	case CLAN_INSPECTION_expl:		//클랜심사
		menuSu = 5;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON2_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON2_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		//텍스트 출력 위치
		menuPos[1].left = BackStartPos.x + clanMake5.pos.x;
		menuPos[1].top = BackStartPos.y + clanMake5.pos.y;
		menuPos[1].right = menuPos[1].left + 260;
		menuPos[1].bottom = menuPos[1].top + 180;

		bx = 68;
		by = 27;


		menuPos[2].left = BackStartPos.x + BUTTON2_BOX_X;		//확인 테두리 박스
		menuPos[2].top = BackStartPos.y + BUTTON2_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		bx = 32;
		by = 16;

		menuPos[3].left = BackStartPos.x + BUTTON3_X;		//취소
		menuPos[3].top = BackStartPos.y + BUTTON3_Y;
		menuPos[3].right = menuPos[3].left + bx;
		menuPos[3].bottom = menuPos[3].top + by;

		bx = 68;
		by = 27;


		menuPos[4].left = BackStartPos.x + BUTTON3_BOX_X;		//취소 테두리 박스
		menuPos[4].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;
		break;
	case CLAN_NotMake:				//클랜을 만들지 못한다는 메뉴
		menuSu = 3;

		bx = 64;
		by = 64;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		//텍스트 출력 위치
		menuPos[1].left = BackStartPos.x + clanMsg254.pos.x;
		menuPos[1].top = BackStartPos.y + clanMsg254.pos.y;
		menuPos[1].right = menuPos[1].left + 260;
		menuPos[1].bottom = menuPos[1].top + 180;

		bx = 68;
		by = 27;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인 테두리 박스
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;
		break;
	case CLAN_MAKE_FINISH:
		menuSu = 3;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//확인
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		//텍스트 출력 위치
		menuPos[1].left = BackStartPos.x + clanMake6.pos.x;
		menuPos[1].top = BackStartPos.y + clanMake6.pos.y;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//확인
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;
		break;
		//======================= 클랜 만들기용 메뉴 ======================end//

	}
}

void CLANEntity_make::Draw()
{
	int i = 0, nIconCount = 0;
	int nIconPos = 0;

	int nSaveTop = 0, nAdd = 0;
	int nStrLen = 0;
	char szDrawMenuMsg[2024];
	ZeroMemory(szDrawMenuMsg, sizeof(char) * 2024);

	switch (C_menuN)
	{
	case CLAN_ABILITYDOWN:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(clanAbilityErrorMsg.szMsg, menuPos[1].left, menuPos[1].top);
		break;
	case CLANMAKE_REAMMAKR_ERROR:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(szClanMakeMsg, menuPos[1].left, menuPos[1].top);
		break;

	case CLANMAKE_NOMONEY:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		wsprintf(szDrawMenuMsg, clanMoneyErrorMsg.szMsg, g_ClanMakeMoney);
		Draw_C_Text(szDrawMenuMsg, menuPos[1].left, menuPos[1].top);
		break;
	case CLAN_isCheckClanJang_Result:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(clanisCheckClanJangErrorMsg.szMsg, menuPos[1].left, menuPos[1].top);
		break;
	case CLAN_isCheckClanJang:
		Draw_C_Text(clanLoading.szMsg, menuPos[0].left, menuPos[0].top);
		break;
	case 0:		//클랜결성의사 확인을 위한 루틴돌아감.
		break;
	case CLAN_MAKE_is:		//클랜결성의사 확인 Y/N : 그림	
		DrawSprite(menuPos[3].left, menuPos[3].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[4].left, menuPos[4].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)	DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Gray, 0, 0, 32, 16, 1);
		if (menuMouseOver[1] > 0)	DrawSprite(menuPos[1].left, menuPos[1].top, hNo_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[1].left, menuPos[1].top, hNo_Gray, 0, 0, 32, 16, 1);
		Draw_C_Text(clanMake1.szMsg, menuPos[2].left, menuPos[2].top);

		break;

	case CLAN_MONEY_is:		// 대금지불의사묻기
		DrawSprite(menuPos[3].left, menuPos[3].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[4].left, menuPos[4].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);
		if (menuMouseOver[1] > 0)	DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Gray, 0, 0, 32, 16, 1);

		wsprintf(szDrawMenuMsg, clanMake2.szMsg, g_ClanMakeMoney);
		Draw_C_Text(szDrawMenuMsg, menuPos[2].left, menuPos[2].top);
		break;

	case CLAN_NAME_is:		//클랜이름 설정.
		DrawSprite(menuPos[3].left, menuPos[3].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(szMsg3, menuPos[2].left, menuPos[2].top);

		if (hFocusWnd != 0) {
			GetWindowText(hFocusWnd, cldata.name, 64);

			void KeyFilter(char *szBuffer);
			KeyFilter(cldata.name);

			DrawSprite(menuPos[4].left, menuPos[4].top, hClanNameInput, 0, 0, 100, 20, 1);
			//Draw_C_Text(cldata.name, BackStartPos.x+160-50+1, BackStartPos.y+200, 1);	//클랜이름입력받기위해 1임)
			Draw_C_Text(cldata.name, menuPos[4].left + 1, menuPos[4].top + 4, 1);	//클랜이름입력받기위해 1임)
		}
		break;
	case CLAN_NONAME:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(clanNoName.szMsg, menuPos[1].left, menuPos[1].top);
		break;
	case CLAN_NAME_BEING:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		//Draw_C_Text(szClanNameError, menuPos[1].left, menuPos[1].top);clanClanNameError.szMsg
		Draw_C_Text(clanClanNameError.szMsg, menuPos[1].left, menuPos[1].top);
		break;
	case CLAN_MARK_expl:		//클랜마크설명
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);
		Draw_C_Text(clanMake4.szMsg, menuPos[1].left, menuPos[1].top);

		break;
	case CLAN_INSPECTION_expl:		//심사기간설명
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[4].left, menuPos[4].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);
		if (menuMouseOver[3] > 0)	DrawSprite(menuPos[3].left, menuPos[3].top, hCancel_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[3].left, menuPos[3].top, hCancel_Gray, 0, 0, 32, 16, 1);
		wsprintf(szDrawMenuMsg, clanMake5.szMsg, cldata.name);
		Draw_C_Text(szDrawMenuMsg, menuPos[1].left, menuPos[1].top);

		break;

	case CLAN_NotMake:	//클랜결성못하니 돌아가라
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else					DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);
		//Draw_C_Text(szMsg254 , menuPos[1].left, menuPos[1].top);
		Draw_C_Text(clanMsg254.szMsg, menuPos[1].left, menuPos[1].top);


		break;
	case CLAN_MAKE_FINISH:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0) DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else	DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(clanMake6.szMsg, menuPos[1].left, menuPos[1].top);
		break;
	case CLANMAKE_DOWN_INFO:
		Draw_C_Text(clanClanMakedowninfo.szMsg, menuPos[0].left, menuPos[0].top);
		break;
	case CLANMAKE_READ_CLANMARK:
		Draw_C_Text(clanClanMakedowninfo.szMsg, menuPos[0].left, menuPos[0].top);
		break;

	}
}




void KeyFilter(char *szBuffer)
{
	int start;
	int result = 0;
	int index;

	if (hFocusWnd != NULL && hTextWnd != NULL)
	{
		for (index = 0; index < (int)lstrlen(szBuffer); index++)
		{

			if ((szBuffer[index] < 48 && szBuffer[index] > 0) ||
				(szBuffer[index] >= 58 && szBuffer[index] <= 64) ||
				(szBuffer[index] >= 91 && szBuffer[index] <= 96) ||
				(szBuffer[index] >= 123 && szBuffer[index] <= 127))
			{
				szBuffer[index] = 0;
				SetWindowText(hFocusWnd, 0);
				SetWindowText(hFocusWnd, szBuffer);
				SendMessage(hFocusWnd, EM_SETSEL, lstrlen(szBuffer), lstrlen(szBuffer) + 1);
				break;
			}
		}

		if (lstrlen(szBuffer) >= 1)
		{
			for (index = 0; index < (int)lstrlen(szBuffer); index++)
			{
				//쇱꿎渴흙匡俚，무삔匡俚
				if ((BYTE)szBuffer[index] >= 0x80)
				{
					int fstByte = (BYTE)szBuffer[index];
					int sndByte = (BYTE)szBuffer[index + 1];

					if (fstByte < 0xA1 || fstByte>0xF7 || sndByte < 0xA1 || sndByte>0xFE)
					{
						szBuffer[index] = 0;
						SetWindowText(hFocusWnd, 0);
						SetWindowText(hFocusWnd, szBuffer);
						SendMessage(hFocusWnd, EM_SETSEL, lstrlen(szBuffer), lstrlen(szBuffer) + 1);
						break;
					}
					else
						index++;
				}
			}
		}

		SendMessage(hFocusWnd, EM_GETSEL, (WPARAM)&start, NULL);
	}
}