#include "StdAfx.h"
#define CE_NOTICE_CPP

#include "tjclanDEF.h"
#include "..\\..\\HoBaram\\HoTextFile.h"


#include "tjclan.h"
#include "tjscroll.h"
#include "cE_report.h"
#include "cE_CViewClanInfo.h"
#include "..\\isaocheck\\auth.h"
#include "..\\isaocheck\\isaocheck.h"
#include "cE_Notice.h"

extern int m_nNoticeCount;
extern int GoNotice_chking;
int nHeight_Count[NOTICECOUNT] = { -1, };

CLANEntity_Notice::CLANEntity_Notice()
{
	ZeroMemory(szNotice, sizeof(szNotice));
	//memset(nHeight_Count,-1,sizeof(nHeight_Count));
	nScl_Bar = 0;
	//m_nNoticeCount= 0;


}

CLANEntity_Notice::~CLANEntity_Notice()
{
}


int CLANEntity_Notice::Init(int Life)
{
	life = Life;
	return 1;
}
int CLANEntity_Notice::Clear()
{
	return 1;
}

void CLANEntity_Notice::Main()
{
	int i;
	switch (C_menuN) {
		//=====================================================================
	case CLAN_DRAWNOTICE_END:
		--m_nNoticeCount;
		if (m_nNoticeCount > -1)
		{
			OpenFlag = 0;
			//GoNotice_chking = 1;
			C_menuN = CLAN_DRAWNOTICE;
			menuInit(C_menuN);
			C_menuN2 = 0;
			break;
		}

		extern BOOL bip_port_error;
		if (bip_port_error == 1) {
			OpenFlag = 0;
			C_menuN = 0;
			C_menuN2 = 0;
			//ktj
			ClanCharMove = 0;
			ClanCLCharMove = 0;

			void TJBscrollWheelClear();	//hoparty.cpp에 사용키위한함수
			TJBscrollWheelClear();		//hoparty.cpp에 사용키위한함수
			isDrawClanMenu = 0;		//메뉴안그림
		}
		else {
			C_menuN = CLAN_AllEnd;
			OpenFlag = 0;
			C_menuN = 0;
			C_menuN2 = 0;
			//ktj
			ClanCharMove = 0;
			ClanCLCharMove = 0;

			void TJBscrollWheelClear();	//hoparty.cpp에 사용키위한함수
			TJBscrollWheelClear();		//hoparty.cpp에 사용키위한함수
			isDrawClanMenu = 0;
		}
		break;
		//=====================================================================



	case CLAN_DRAWNOTICE:

		//int left, top, right, bottom;
		//left   = menuPos[0].left;
		//top    = menuPos[0].top;
		//right  = menuPos[0].right;
		//bottom = menuPos[0].bottom;
		//menuPos[0].left   -= 10;
		//menuPos[0].top    -= 5;
		//menuPos[0].right  += 10;
		//menuPos[0].bottom += 60;

		i = chkeckMenuN();

		//menuPos[0].left   = left;
		//menuPos[0].top    = top;
		//menuPos[0].right  = right;
		//menuPos[0].bottom = bottom;

		/*
		if(menuPos[0].left <= pCursorPos.x && pCursorPos.x <= menuPos[0].right)
			if(menuPos[0].top <= pCursorPos.y && pCursorPos.y <= menuPos[0].bottom)
				i = 1;
		*/

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

		if (MOUSE0())
		{
			MOUSE0() = 0;
			i = i;
			switch (i)
			{
			case 0:
				C_menuN = CLAN_DRAWNOTICE_END;
				C_menuN2 = -1;
				CLAN_ERROR_ret = -1;
				break;
			case 5:
				nScl_Bar = tscr.topScrollLineNum(pCursorPos.y);
				//ktj : 스크롤 아이콘 위치재설정
				scrIconPos.top = pCursorPos.y - 8;//BackStartPos.y + SCROOBAR_TOP;
				break;
			default:
				i = i;
				break;

			}
		}
		break;
	case CLAN_NOTICE:
		switch (C_menuN2) {
		case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();		//웹db를 재개한다.
			WebDB.ReadNotice(cldata.szID, cldata.ChaName, cldata.gserver);
			C_menuN2 = 1;
			break;
		case 1:

			if (ANSdata.ret_val != -1) {
				ANSdata.ret_val = ANSdata.ret_val;
			}

			switch (ANSdata.ret_val)
			{
				//ygy
			case 0: //트랜잭션 오류
				OpenFlag = 0;
				WebDB.Suspend(); //웹db 중지
				C_menuN = CLAN_DRAWNOTICE_END;
				C_menuN2 = -1;
				CLAN_ERROR_ret = -1;
				//ygy : 에러 메세지 살려야함
				//C_menuN = CLAN_ERROR;
				//wsprintf(szErrorMsg,"%s (63)",szError_Msg);
				//cClanReport.InitMsg(szErrorMsg);
				//cClanReport.menuInit(C_menuN);
				//CLAN_ERROR_ret=255;		//에러메뉴보여준후그냥끝낸다.
				//C_menuN2=-1;
				break;
			case 1:
				OpenFlag = 0;
				WebDB.Suspend(); //웹db 중지						
				NoticeCheck(ANSdata.ret_Buf);
				//++m_nNoticeCount;
				///NoticeCheck("Txt=교육인적자원부는 26일 교육행정정보시스템(NEIS) 27개 영역 중 논란이 돼온 교무학사, 보건, 입(진)학 3개 영역에 대해 “NEIS 체제 시행을 전면 재검토키로 했다”며 사실상 NEIS 전면 중단을 골자로 한 최종 입장을 발표했다. 그러자 전국 16개 시·도교육감들이 교육부가 소집한 회의에 불참하고 공개적으로 거부하고 나서는 등 NEIS 갈등이 최악의 사태로 번지고 있다.최대 교원단체인 한국교총은 성명을 내 교육부총리 퇴진을 요구하는 등 거세게 반발했으며, 전국 교장들의 모임인 한국국공사립초중고교교장회장협의회도 “전교조 횡포 앞에 비굴하게 항복한 책임을 지고 윤 부총리는 물러나야 한다”고 촉구했다.윤덕홍(尹德弘) 교육부총리는 26일 오전 기자회견을 갖고 “올해 대학입시에 차질이 없도록 고3에 한해서는 NEIS 체제를 운영하되, 고2 이하 학생의 경우 3개 영역에 대해 2004년 2월 이전까지 한시적으로 NEIS 이전 체제(CS)로 시행키로 했다”고 밝혔다.이는 NEIS 강행을 천명해온 그동안의 방침을 스스로 번복하고, 3개 영역 NEIS 시행 폐지와 이전 체제 회귀를 주장해온 전교조의 주장을 대폭 수용한 것이다. 전교조는 이에 따라 28일로 예정된 연가투쟁을 취소했다. 특히 ‘한시적’이란 전제를 달기는 했지만, 고2 이하 학생에 대해 NEIS 이전 체제인 학교종합정보시스템(CS)을 적용키로 함으로써 NEIS 시행은 사실상 불가능해졌다는 지적이다.");
				//++m_nNoticeCount;
				//NoticeCheck("Txt= 특히 ‘한시적’이란 전제를 달기는 했지만, 고2 이하 학생에 대해 NEIS 이전 체제인 학교종합정보시스템(CS)을 적용키로 함으로써 NEIS 시행은 사실상 불가능해졌다는 지적이다.교육인적자원부는 26일 교육행정정보시스템(NEIS) 27개 영역 중 논란이 돼온 교무학사, 보건, 입(진)학 3개 영역에 대해 “NEIS 체제 시행을 전면 재검토키로 했다”며 사실상 NEIS 전면 중단을 골자로 한 최종 입장을 발표했다. 그러자 전국 16개 시·도교육감들이 교육부가 소집한 회의에 불참하고 공개적으로 거부하고 나서는 등 NEIS 갈등이 최악의 사태로 번지고 있다.최대 교원단체인 한국교총은 성명을 내 교육부총리 퇴진을 요구하는 등 거세게 반발했으며, 전국 교장들의 모임인 한국국공사립초중고교교장회장협의회도 “전교조 횡포 앞에 비굴하게 항복한 책임을 지고 윤 부총리는 물러나야 한다”고 촉구했다.윤덕홍(尹德弘) 교육부총리는 26일 오전 기자회견을 갖고 “올해 대학입시에 차질이 없도록 고3에 한해서는 NEIS 체제를 운영하되, 고2 이하 학생의 경우 3개 영역에 대해 2004년 2월 이전까지 한시적으로 NEIS 이전 체제(CS)로 시행키로 했다”고 밝혔다.이는 NEIS 강행을 천명해온 그동안의 방침을 스스로 번복하고, 3개 영역 NEIS 시행 폐지와 이전 체제 회귀를 주장해온 전교조의 주장을 대폭 수용한 것이다. 전교조는 이에 따라 28일로 예정된 연가투쟁을 취소했다.");
				C_menuN = CLAN_DRAWNOTICE;
				menuInit(C_menuN);
				break;

			case 100: //엉둥한 값
				OpenFlag = 0;
				WebDB.Suspend(); //웹db 중지
				C_menuN = CLAN_DRAWNOTICE_END;
				C_menuN2 = -1;
				CLAN_ERROR_ret = -1;
				//ygy : 에러 메세지 살려야함
				//wsprintf(szErrorMsg, sz100Error);
				//C_menuN = CLAN_ERROR;
				//wsprintf(szErrorMsg,"%s (60)",szError_Msg);
				//cClanReport.InitMsg(szErrorMsg);
				//cClanReport.menuInit(C_menuN);
				//menuInit(C_menuN);
				//CLAN_ERROR_ret=255;		//에러메뉴보여준후그냥끝낸다.
				//C_menuN2=-1;
				break;
			case ISAO_ERR_TCP_CONNECT:
				OpenFlag = 0;
				WebDB.Suspend();
				C_menuN = CLAN_DRAWNOTICE_END;
				C_menuN2 = -1;
				CLAN_ERROR_ret = -1;
				//ygy : 에러 메세지 살려야함
				//wsprintf(szErrorMsg,"%s (61)",szError_Msg);
				//C_menuN = CLAN_ERROR;
				//cClanReport.InitMsg(szErrorMsg);
				//cClanReport.menuInit(C_menuN);
				break;
				//end ygy

			default:
				if (ANSdata.ret_val != -1) {		//전혀엉뚱한 답이 와서 에러가 났다.
					OpenFlag = 0;
					WebDB.Suspend();
					C_menuN = CLAN_DRAWNOTICE_END;
					C_menuN2 = -1;
					CLAN_ERROR_ret = -1;
					//ygy : 살려야함
					//C_menuN = CLAN_ERROR;
					//wsprintf(szErrorMsg,"%s (62)",szError_Msg);
					//cClanReport.InitMsg(szErrorMsg);
					//cClanReport.menuInit(C_menuN);					
					//CLAN_ERROR_ret=255;		//에러메뉴보여준후그냥끝낸다.
					//C_menuN2=-1;
				}
				break;
			}
			break;
		}//C_menu2


		break;
	}

}

void CLANEntity_Notice::Draw()
{
	int i, nCap = 0, nIconPos = 0;

	switch (C_menuN)
	{
	case CLAN_DRAWNOTICE:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);

		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		DrawSprite(menuPos[3].left, menuPos[3].top, hClanName, 0, 0, CLANNAME_WIDTH, CLANNAME_HEIGHT, 1);

		dsDrawTexImage(hLine, menuPos[4].left, menuPos[4].top, 403, 10, 255);

		Draw_C_Text("안    내", menuPos[3].left + 50, menuPos[3].top + 10);
		Draw_C_Text("안    내", menuPos[3].left + 51, menuPos[3].top + 10);
		Draw_C_Text("안    내", menuPos[3].left + 50, menuPos[3].top + 11);
		Draw_C_Text("안    내", menuPos[3].left + 51, menuPos[3].top + 11);


		nIconPos = 5;
		if (nHeight_Count[m_nNoticeCount] > HEIGHT_MAX)
		{
			sinDrawTexImage(hScl_Bar_tj, (float)menuPos[nIconPos].left, (float)menuPos[nIconPos].top, 8, 290);//256);
			sinDrawTexImage(hScl_icon_tj, (float)scrIconPos.left, (float)scrIconPos.top, 16, 16);
		}

		for (i = nScl_Bar, nCap = 0; i < nScl_Bar + 14; i++)
		{
			if (i >= nHeight_Count[m_nNoticeCount]) break;
			Draw_C_Text(szNotice[m_nNoticeCount][i], menuPos[1].left, menuPos[1].top + nCap);
			nCap += 20;
		}
		break;
	}
}


void CLANEntity_Notice::menuInit(int num)
{
	int bx = 0, by = 0;
	int nScrollPos = 0;
	nScl_Bar = 0;

	switch (num)
	{
	case CLAN_DRAWNOTICE:
		menuSu = 6;

		bx = 32;
		by = 16;


		menuPos[0].left = NOTICE_X + 185 + 9;		//확인
		menuPos[0].top = NOTICE_Y + 381 + 4 - 50;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		//텍스트 출력 위치
		menuPos[1].left = NOTICE_X + 30;
		menuPos[1].top = NOTICE_Y + 70 - 50;

		bx = 64;
		by = 16;

		menuPos[2].left = NOTICE_X + 185;		//확인
		menuPos[2].top = NOTICE_Y + 381 - 50;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		bx = 64;
		by = 16;

		menuPos[3].left = NOTICE_X + 115 + 18;//BUTTON1_BOX_X;		//확인
		menuPos[3].top = 77 - 50;//BUTTON1_BOX_Y;
		menuPos[3].right = menuPos[2].left + bx;
		menuPos[3].bottom = menuPos[2].top + by;

		bx = 64;
		by = 16;

		menuPos[4].left = NOTICE_X + 7;
		menuPos[4].top = 105 - 50;
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;

		nScrollPos = 5;

		if (nHeight_Count[m_nNoticeCount] > HEIGHT_MAX)
		{
			bx = 16;
			by = 16;


			menuPos[nScrollPos].left = BackStartPos.x + NOTICE_SCROLLBAR_LEFT;
			menuPos[nScrollPos].top = BackStartPos.y + 20 - 50;
			menuPos[nScrollPos].right = menuPos[nScrollPos].left + 8;
			menuPos[nScrollPos].bottom = menuPos[nScrollPos].top + 290;

			tscr.Init(1);
			tscr.Init(menuPos[nScrollPos].top, menuPos[nScrollPos].top + 290, nHeight_Count[m_nNoticeCount], HEIGHT_MAX);

			scrIconPos.left = BackStartPos.x + NOTICE_SCROLLBAR_LEFT - 5;
			scrIconPos.top = menuPos[nScrollPos].top;
		}
		break;
	}
}

#define MAX_CHACOUNT 58
void CLANEntity_Notice::NoticeCheck(char* buf)
{
	int nStrlen = 0, i = 0, nCount = 0, nCnt = 0;///,
	nHeight_Count[m_nNoticeCount] = 0;

	buf = strstr(buf, "Txt=");
	buf = &buf[lstrlen("Txt=")];
	nStrlen = lstrlen(buf);

	ZeroMemory(szNotice[m_nNoticeCount], sizeof(szNotice));

	if (nStrlen > NOTICE_MAX)
	{
		nStrlen = NOTICE_MAX;
	}
	while (nHeight_Count[m_nNoticeCount] < NOTICE_HEIGHT)
	{
		if (buf[i] == 0)
			break;

		if (buf[i] == '\r')
		{
			if (buf[i + 1] == '\n')
			{
				nCount = 0;
				szNotice[m_nNoticeCount][nHeight_Count[m_nNoticeCount]][nCnt] = 0;//buf[i];
				++nCount;
				if (i != 0)
					nHeight_Count[m_nNoticeCount]++;

				nCnt = 0;
				i++;
				i++;
				continue;

			}
			else
			{
				nCount = 0;
				++nCount;
				if (i != 0)
					nHeight_Count[m_nNoticeCount]++;

				nCnt = 0;
				i++;
				continue;
			}

		}
		else
		{
			if (IsDBCSLeadByte(buf[i]))
			{
				szNotice[m_nNoticeCount][nHeight_Count[m_nNoticeCount]][nCnt] = buf[i];
				nCnt += 1;
				i += 1;
				szNotice[m_nNoticeCount][nHeight_Count[m_nNoticeCount]][nCnt] = buf[i];
				nCount += 2;;
			}
			else
			{
				if (buf[i] == 0x09)
				{
					szNotice[m_nNoticeCount][nHeight_Count[m_nNoticeCount]][nCnt] = 0x20;
					nCnt++;
					szNotice[m_nNoticeCount][nHeight_Count[m_nNoticeCount]][nCnt] = 0x20;
					nCnt++;
					szNotice[m_nNoticeCount][nHeight_Count[m_nNoticeCount]][nCnt] = 0x20;
					nCnt++;
					szNotice[m_nNoticeCount][nHeight_Count[m_nNoticeCount]][nCnt] = 0x20;
				}
				else
					szNotice[m_nNoticeCount][nHeight_Count[m_nNoticeCount]][nCnt] = buf[i];

				++nCount;

			}


		}
		if (nCount >= (MAX_CHACOUNT))
		{
			nCount = 0;
			nCnt += 1;
			szNotice[m_nNoticeCount][nHeight_Count[m_nNoticeCount]][nCnt] = '\n';
			szNotice[m_nNoticeCount][nHeight_Count[m_nNoticeCount]][nCnt + 1] = 0;

			nHeight_Count[m_nNoticeCount]++;
			nCnt = 0;
			i++;
			continue;
		}

		nCnt++;
		i++;
	}
}