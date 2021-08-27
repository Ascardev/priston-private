#include "StdAfx.h"
#define CE_CJOIN_CPP

#include "tjclanDEF.h"
#include "..\\..\\HoBaram\\HoTextFile.h"

#include "tjclan.h"
#include "cE_report.h"
#include "cE_CJoin.h"
#include "cE_CViewClanInfo.h"
#include "..\\isaocheck\\auth.h"
#include "..\\isaocheck\\isaocheck.h"

//void CheckMsgPos(CLANMSG* clanmsg,int width, int height);

CLANEntity_JOIN::CLANEntity_JOIN()
{
	nJoinAnswer = 0;
	ZeroMemory(szTemp, sizeof(szTemp));
	ZeroMemory(szTemp1, sizeof(szTemp1));
}

CLANEntity_JOIN::~CLANEntity_JOIN()
{

}

int CLANEntity_JOIN::Init(int Life)
{
	life = Life;
	ZeroMemory(szUserJoin, sizeof(szUserJoin));
	return 1;
}

int CLANEntity_JOIN::Clear()
{
	return 1;
}

void CLANEntity_JOIN::Main()
{
	int i;
	//char		szErrorMsg[256];
	switch (C_menuN)
	{
	case CLAN_CLANWONOVER:
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
				C_menuN = CLAN_AllEnd;
				//C_menuN = CLAN_ERROR_ret;		//³ª°¡±â : ³¡³»´Â°É·Î°£´Ù.
				//menuInit(C_menuN );

				C_menuN2 = -1;
				CLAN_ERROR_ret = -1;
				break;
			default:
				break;

			}
		}
		break;
	case CLAN_JOIN_before:

		switch (C_menuN2) {
		case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();		//À¥db¸¦ Àç°³ÇÑ´Ù.
			WebDB.isClanMember(cldata.szID, cldata.gserver, cldata.ChaName);		//ÀÌ id°¡ Å¬·£¿øÀÎÁö¸¦ ÆÄ¾ÇÇÑ´Ù.
			C_menuN2 = 1;
			break;
		case 1:
			switch (ANSdata.ret_val)
			{
			case 100:						//ÀÏ¹Ý Å¬·£¿ø

				WebDB.Suspend(); //À¥db ÁßÁö

				C_menuN = CLAN_JOIN_After;
				menuInit(C_menuN);
				joinAnswer = 100;			//ÀÌ¹Ì´Ù¸¥Å¬·£¿¡°¡ÀÔµÇÀÖ¾î °¡ÀÔºÒ°¡

				C_menuN2 = 0;
				break;

			case 1:                         //Å¬·£Ä¨
			case 2:                         //Å¬·£Àå
			case 5:						//ºÎÅ¬·£
			case 101:						//Å¬·£¯…( µ¥ÀÌÅ¸ÀÐ±â·Î °£´Ù)
			case 103:						//Å¬·£¯… ½É»çÀü
			case 104:						//Å¬·£¯… ½É»çÀü
				WebDB.Suspend();
				C_menuN = CLAN_JOIN_After;
				menuInit(C_menuN);
				joinAnswer = 101;			//ÀÌ¹Ì´Ù¸¥Å¬·£¿¡ Å¬·£¯…ÀÌ¶ó¼­ °¡ÀÔºÒ°¡

				C_menuN2 = 0;

				break;
			case 4:
			case 3:
			case 0:						//¹«µî·Ï.
			case 105:						//¿¡·¯
				WebDB.Suspend();
				C_menuN = CLAN_JOIN;
				//C_menuN = CLANUSER_JOIN;
				menuInit(C_menuN);

				C_menuN2 = 0;

				break;
			case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();

				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (55)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				break;
			default:
				if (ANSdata.ret_val != -1) {		//ÀüÇô¾û¶×ÇÑ ´äÀÌ ¿Í¼­ ¿¡·¯°¡ ³µ´Ù.
					WebDB.Suspend();

					C_menuN = CLAN_ERROR;				//Å¬·£°á¼º¸øÇÏ´Ï µ¹¾Æ°¡¶ó°í ÇÏ´Â¸Þ´º·Î °£´Ù.
					wsprintf(szErrorMsg, "%s (56)", clanszError_Msg.szMsg);
					cClanReport.InitMsg(szErrorMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);

					C_menuN2 = 0;
				}
				break;
			}
			break;
		}
		break;

	case CLANUSER_JOIN:

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
				//C_menuN = CLAN_ERROR_ret;		//³ª°¡±â : ³¡³»´Â°É·Î°£´Ù.
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


	case CLAN_JOIN:
		i = chkeckMenuN();				//================================================
		memset(menuMouseOver, -1, sizeof(int) * 30);
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
			break;
		}
		if (MOUSE0())
		{
			MOUSE0() = 0;
			switch (i)
			{
			case 0:

				wsprintf(szUserJoin, clanClanJoinMsg.szMsg, cldata.szJoinClanName, cldata.szJoinClanChipName, cldata.ChaName);
				//void CheckMsgPos(CLANMSG* clanmsg);
				CheckMsgPos(&clanClanJoinMsg, BOX_MAX_WIDTH, 0);
				C_menuN = CLANUSER_JOIN;

				menuInit(C_menuN);
				CLAN_ERROR_ret = CLAN_JOIN_After;
				nJoinAnswer = 1;

				SendJoinClan();

				break;
			case 1:
				nJoinAnswer = 0;
				C_menuN = CLAN_AllEnd;
				break;

			default:
				break;
			}
		}
		break;

	case CLAN_JOIN_After:
		C_menuN = CLAN_AllEnd;
		break;
	case CLAN_IS_CHECK_MEMBER_END:
		C_menuN = CLAN_AllEnd;
		break;
	case CLAN_IS_CHECK_MEMBER:
		switch (C_menuN2)
		{
		case 0:
			ANSdata.ret_val = -1;
			WebDB.Resume();
			WebDB.isCheckClanMember(cldata.gserver, cldata.TargetChar->sCharacterData.szName);
			C_menuN2 = 1;
			break;
		case 1:
			if (ANSdata.ret_val != -1)
			{
				if (ANSdata.ret_val == 0)
				{
					WebDB.Suspend();
					CLANMSG clanMsg;
					wsprintf(clanMsg.szMsg, "%s", "Error");
					clanMsg.pos.x = 0;
					clanMsg.pos.y = 0;
					CheckMsgPos(&clanMsg, BOX_MAX_WIDTH, 0);

					C_menuN = CLAN_ERROR;

					char TempBufferMsg[256];
					wsprintf(TempBufferMsg, ClanIs4DayCheckMsg.szMsg, cldata.TargetChar->sCharacterData.szName);
					cClanReport.InitMsg(TempBufferMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);

					CLAN_ERROR_ret = CLAN_IS_CHECK_MEMBER_END;		//¿¡·¯¸Þ´ºº¸¿©ÁØÈÄ ´Ù½Ã µ¹¾Æ°¥°÷.

				}
				else if (ANSdata.ret_val == 1)
				{
					WebDB.Suspend();
					SendClanJoinService(1, cldata.TargetChar);

					C_menuN = CLAN_IS_CHECK_MEMBER_END;
					C_menuN2 = 0;
					OpenFlag = 1;
					joinAnswer = 0;
					ClanCharMove = 1;

				}
				else
				{
					WebDB.Suspend();
					CLANMSG clanMsg;
					wsprintf(clanMsg.szMsg, "%s", "Error");
					clanMsg.pos.x = 0;
					clanMsg.pos.y = 0;
					CheckMsgPos(&clanMsg, BOX_MAX_WIDTH, 0);

					C_menuN = CLAN_ERROR;

					char TempBufferMsg[256];

					wsprintf(TempBufferMsg, "Å¬·£Å»Åð\n4ÀÏ°æ°úÃ¼Å©ÁßError");
					cClanReport.InitMsg(TempBufferMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);

					CLAN_ERROR_ret = CLAN_IS_CHECK_MEMBER_END;
				}
			}
		}
		break;
	case CLAN_JOIN_chip:
		switch (C_menuN2)
		{
		case 0:
			ANSdata.ret_val = -1;

			WebDB.Resume();

			WebDB.joinClanMember(cldata.szID, cldata.gserver, cldata.ChaName,

				cldata.name, cldata.clanJoinCharID, cldata.clanJoinID, sinChar->iLevel, cldata.clanJoinJob, cldata.clanJoinLevel, cldata.isSubChip);//Å¸ÀÓ

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
				menuInit(C_menuN);
				wsprintf(szErrorMsg, "%s (64)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_JOIN_After;

				C_menuN2 = 0;
				break;
			case 1:
				WebDB.Suspend();
				C_menuN = CLAN_JOIN_chip_YES;
				menuInit(C_menuN);

				AddClanWon();

				void SetClanWon();
				//SetClanWon();
				C_menuN2 = 0;
				break;
			case 2:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (49)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_JOIN_After;

				C_menuN2 = 0;

				break;
			case 3:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (50)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_JOIN_After;
				C_menuN2 = 0;
				break;
			case 4:
				WebDB.Suspend();
				C_menuN = CLAN_CLANWONOVER;
				cClanJoin.menuInit(C_menuN);
				CLAN_ERROR_ret = CLAN_JOIN_After;
				C_menuN2 = 0;
				break;
			case 100:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (52)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				CLAN_ERROR_ret = CLAN_JOIN_After;
				C_menuN2 = 0;
				break;
			case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				C_menuN = CLAN_ERROR;
				wsprintf(szErrorMsg, "%s (53)", clanszError_Msg.szMsg);
				cClanReport.InitMsg(szErrorMsg);
				cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
				break;
			default:
				if (ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					C_menuN = CLAN_ERROR;
					wsprintf(szErrorMsg, "%s (54)", clanszError_Msg.szMsg);
					cClanReport.InitMsg(szErrorMsg);
					cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
					CLAN_ERROR_ret = CLAN_JOIN_After;

					C_menuN2 = 0;
				}
				break;
			}
			break;
		}
		break;

	case CLAN_JOIN_chip_NO:
		wsprintf(szTemp, clanClanJoinCancelMsg.szMsg, cldata.clanJoinCharID);

		lstrcpy(szTemp1, clanszError_Msg.szMsg);
		lstrcpy(clanszError_Msg.szMsg, szTemp);

		CheckMsgPos(&clanszError_Msg, BOX_MAX_WIDTH, 0);

		C_menuN = CLAN_ERROR;
		cClanReport.InitMsg(szTemp);
		cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);

		lstrcpy(clanszError_Msg.szMsg, szTemp1);

		CLAN_ERROR_ret = CLAN_AllEnd;
		break;
	case CLAN_JOIN_chip_YES:
		wsprintf(szTemp, clanClanJoinsucesssMsg.szMsg, cldata.clanJoinCharID);

		lstrcpy(szTemp1, clanszError_Msg.szMsg);
		lstrcpy(clanszError_Msg.szMsg, szTemp);

		CheckMsgPos(&clanszError_Msg, BOX_MAX_WIDTH, 0);

		lstrcpy(szTemp, clanszError_Msg.szMsg);

		C_menuN = CLAN_ERROR;
		cClanReport.InitMsg(szTemp);
		cClanReport.menuInit(C_menuN, clanszError_Msg.pos.x, clanszError_Msg.pos.y);
		lstrcpy(clanszError_Msg.szMsg, szTemp1);
		CLAN_ERROR_ret = CLAN_AllEnd;

		void SetClanWon();
		SetClanWon();

		break;

	}
}

void CLANEntity_JOIN::menuInit(int num)
{
	int bx = 0, by = 0;
	switch (num) {
	case CLAN_CLANWONOVER:
		menuSu = 3;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//È®ÀÎ
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		//ÅØ½ºÆ® Ãâ·Â À§Ä¡
		menuPos[1].left = BackStartPos.x + clanClanWonOver.pos.x;
		menuPos[1].top = BackStartPos.y + clanClanWonOver.pos.y;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//È®ÀÎ
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;
		break;
	case CLANUSER_JOIN:
		menuSu = 3;

		bx = 32;
		by = 16;

		menuPos[0].left = BackStartPos.x + BUTTON1_X;		//È®ÀÎ
		menuPos[0].top = BackStartPos.y + BUTTON1_Y;
		menuPos[0].right = menuPos[0].left + bx;
		menuPos[0].bottom = menuPos[0].top + by;

		//ÅØ½ºÆ® Ãâ·Â À§Ä¡
		menuPos[1].left = BackStartPos.x + clanClanJoinMsg.pos.x;
		menuPos[1].top = BackStartPos.y + clanClanJoinMsg.pos.y;

		bx = 64;
		by = 16;

		menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;		//È®ÀÎ
		menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		break;
	case CLAN_JOIN:
		//Å¬·£¯…ÀÌ °¡ÀÔÇÏ¶ó°í ±ÇÀ¯ÇÒ¶§ »ó´ëÆí¿¡°Ô ¶ß´Â ¸Þ´º  =================================START

		menuSu = 5;

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

		menuPos[2].left = BackStartPos.x + 150;		//Å¬·£ ¸¶Å©
		menuPos[2].top = BackStartPos.y + 150;
		menuPos[2].right = menuPos[2].left + bx;
		menuPos[2].bottom = menuPos[2].top + by;

		//ÅØ½ºÆ® Ãâ·Â À§Ä¡
		menuPos[3].left = BackStartPos.x + clanJoin.pos.x;
		menuPos[3].top = BackStartPos.y + clanJoin.pos.y;
		menuPos[3].right = menuPos[3].left + 280;
		menuPos[3].bottom = menuPos[3].top + 250;

		bx = 64;
		by = 16;

		menuPos[4].left = BackStartPos.x + BUTTON2_BOX_X;		//yes Å×µå¸® ¹Ú½º
		menuPos[4].top = BackStartPos.y + BUTTON2_BOX_Y;
		menuPos[4].right = menuPos[4].left + bx;
		menuPos[4].bottom = menuPos[4].top + by;

		bx = 64;
		by = 16;


		menuPos[5].left = BackStartPos.x + BUTTON3_BOX_X;		//no Å×µå¸® ¹Ú½º
		menuPos[5].top = BackStartPos.y + BUTTON3_BOX_Y;
		menuPos[5].right = menuPos[6].left + bx;
		menuPos[5].bottom = menuPos[6].top + by;

		break;
	}

}

void CLANEntity_JOIN::Draw()
{
	char string[256];

	switch (C_menuN)
	{
	case CLAN_CLANWONOVER:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(clanClanWonOver.szMsg, menuPos[1].left, menuPos[1].top);
		break;
	case CLANUSER_JOIN:
		DrawSprite(menuPos[2].left, menuPos[2].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hOk_Gray, 0, 0, 32, 16, 1);

		Draw_C_Text(szUserJoin, menuPos[1].left, menuPos[1].top);
		break;
	case CLAN_JOIN:
		DrawSprite(menuPos[4].left, menuPos[4].top, hButton_Box, 0, 0, 48, 23, 1);
		DrawSprite(menuPos[5].left, menuPos[5].top, hButton_Box, 0, 0, 48, 23, 1);
		if (menuMouseOver[0] > 0)
			DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[0].left, menuPos[0].top, hYes_Gray, 0, 0, 32, 16, 1);

		if (menuMouseOver[1] > 0)
			DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Yellow, 0, 0, 32, 16, 1);
		else
			DrawSprite(menuPos[1].left, menuPos[1].top, hCancel_Gray, 0, 0, 32, 16, 1);

		//wsprintf(string,szJoin,cldata.szJoinClanName,cldata.szJoinClanChipName);
		wsprintf(string, clanJoin.szMsg, cldata.szJoinClanName, cldata.szJoinClanChipName);
		Draw_C_Text(string, menuPos[3].left, menuPos[3].top);
		break;
	}
}

void CLANEntity_JOIN::AddClanWon()
{
	int i;
	for (i = 0; i < CLANWON_MAX - 1; i++)
	{
		if (cldata.clanWon[i][0] == 0)
		{
			lstrcpy(cldata.clanWon[i], cldata.clanJoinCharID);
			nClanWon_Num += 1;

			cldata.nTotalClanWonCount = nClanWon_Num;
			cldata.nCurrentClanWon_Num += 1;
			break;
		}
	}

	void fd2(char *fmt, ...);

	for (i = 0; i < CLANWON_MAX - 1; i++)
	{
		if (cldata.clanWon[i][0] != 0)
		{
			fd2("Å¬·£¿ø¸®½ºÆ®  cldata.clanWon[%d] = %s  ", i, cldata.clanWon[i]);
		}
	}

}

int nClanWonLevelTable[] = {
	0,0,0,0,0,0,0,0,0,0, //0~9
		0,0,0,0,0,0,0,0,0,0, //10~19
		0,0,0,0,0,0,0,0,0,0, //20~29
		0,0,0,0,0,0,0,0,0,0, //30~39
		20,21,   //40~41
		22,23,   //42~43
		24,25,   //44~45
		26,27,   //46~47
		28,29,   //48~49
		30,31, //50~51
		32,33, //52~53
		34,35, //54~55
		36,37, //56~57
		38,39, //58~59
		40,41, //60~61
		42,43, //62~63
		44,45, //64~65
		46,47, //66~67
		48,49, //68~69
		50,51, //70,71
		52,53, //72,73
		54,55, //74,75
		56,57, //76,77
		58,59, //78,79
		60,61, //80,81
		62,63, //82.83
		64,65, //84,85
		66,67, //86,87
		68,69, //80~89
		70,71, //90,91
		72,73, //92,93
		74,75, //94,95
		76,77, //96,97
		78,80, //98~99
};

void CLANEntity_JOIN::SetLevelTable()
{

}

BOOL CLANEntity_JOIN::CheckClanWon(int level)
{
	int nMaxClanWonCount = 0;
	nMaxClanWonCount = nClanWonLevelTable[level];
	if (nMaxClanWonCount > cldata.nCurrentClanWon_Num)
	{
		return TRUE;
	}

	return TRUE;
}


int CLANEntity_JOIN::GetMaxClanWonCount(int level)
{
	return nClanWonLevelTable[level];
}

void SetLevelTable(int makeclanlevel, int makeclanlevel_clanwon, int addclanwonlevel_start, int addlevel, int addclanwon_num, int maxlevel)
{
	cClanJoin.SetLevelTable();
}
BOOL CheckClanWon(int level)
{
	BOOL bReturn = 0;
	bReturn = cClanJoin.CheckClanWon(level);
	return bReturn;
}
