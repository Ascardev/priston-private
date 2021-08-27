#include "StdAfx.h"
#define CE_CHATLIST_CPP
#include "tjclanDEF.h"
#include "..\\..\\HoBaram\\HoTextFile.h"

#include "tjclan.h"

#include "tjscroll.h"
#include "cE_chatlist.h"

#include "..\\Park\\MICVOL\\MicVolume.h"
//#include "..\\..\\Korean\\K_VolText.h"

#include "cE_report.h"
#include "cE_CViewClanInfo.h"
#include "..\\isaocheck\\auth.h"
#include "..\\isaocheck\\isaocheck.h"

#include "..\\ygy\\ygyheader.h"

extern int TJmb2[3];

extern int vrunRuning;


#define MOUSE0_2() TJmb2[0]


int OpenBuf_x[50] = { 800, 800, 800, 800, 800, 800,
800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800, 800,
750,700,650,600,560,550,548,546,544,540,539,-1,-1 };


int CloseBuf_x[50] = { 500,556,606,656,706,756,800 };

extern POINT	pCursorPos;
extern char szConnServerName[16];


extern BOOL bMic;
int g_nMicBtn;
int micInit;



//Ã¤ÆÃ¸®½ºÆ®½ºÇÇÄ¿ÀÇ ÇÃ·¡±×¸¦ ¾Ë¾Æ³½´Ù.
int chatlistSPEAKERflag()
{
	return cClanChatting.Chatting_button;			//½ºÇÇÄ¿ on,off 
}

//0,1À» ³ÖÀ»¼öÀÖÀ½.
void chatlistSPEAKERflagChg(int flag)
{
	cClanChatting.Chatting_button = flag;			//½ºÇÇÄ¿ on,off 


	if (flag == 0) {		//½ºÇÇÄ¿¸¦ ²ô¸é
		for (int i = 0; i < 40; i++) {
			banisF[i] = 0;			//»ç¶÷ÀÌ¸§¾Õ¿¡ ´­¸°°ÍÀ» ¾Ë·ÁÁø°ÍÀ» Áö¿î´Ù.
		}
		void clan_chat_WhisperPartyPlayer_close();	//hoparty.cpp¿¡¼­ ºÒ¸§.
		clan_chat_WhisperPartyPlayer_close();	//hoparty.cpp¿¡¼­ ºÒ¸§.
	}
}



//*****************************************************************************
CLANEntity_chatting::CLANEntity_chatting()
{
	ZeroMemory(&ClanChatList, sizeof(CHATLIST));
	nBoxMove = 0;
	bIsDrawBoxFinish = 0;
	hChatListBoxLine = 0;
	hChatListBoxTitle = NULL;
	for (int i = 0; i < 2; i++)
	{
		hButtonClose[i] = NULL;
		hClanWon[i] = NULL;
		hChatIcon[i] = NULL;
		//¹ÚÃ¶È£
#ifdef PARKMENU
		hMicOption[i] = NULL;
		hMicVOLUPDOWN[i] = NULL;
#endif
	}

	hMark = NULL;
	Chatting_button = 0;
	nSaveClanWonPos = -1;
	nDoublClick = -1;

	//¹ÚÃ¶È£
#ifdef PARKMENU
	MicOpt_button = 0;
	g_nMicBtn = 0;
	hMicOptTitle = NULL;
	hMicSortLine = NULL;
	hMicONBack = NULL;
	hMicONChk = NULL;
	hMicVolBar = NULL;
#endif
}

CLANEntity_chatting::~CLANEntity_chatting()
{
	DELET(hChatListBoxTitle);
	DELET(hChatClanWon);
	for (int i = 0; i < 2; i++)
	{
		DELET(hButtonClose[i]);
		DELET(hClanWon[i]);
		DELET(hChatIcon[i]);
		DELET(hChatIcon[i]);
		DELET(hMicOption[i]);
		DELET(hMicVOLUPDOWN[i]);
	}
	DELET(hMicOptTitle);
	DELET(hMicSortLine);
	DELET(hMicONBack);
	DELET(hMicONChk);
	DELET(hMicVolBar);
	DELET(hMicOptToolTip);
	DELET(hClanChatToolTip);
	DELET(hBtnCloseToolTip);
}


//*****************************************************************************
int CLANEntity_chatting::Init(int Life)
{
	life = Life;
	InitClanChatList();
	return 1;
}

void CLANEntity_chatting::Close()
{
	DELET(hMark);
	DELET(hChatListBoxTitle);

	for (int i = 0; i < 2; i++)
	{
		DELET(hButtonClose[i]);
		DELET(hClanWon[i]);
		DELET(hChatIcon[i]);
		DELET(hMicOption[i]);
		DELET(hMicVOLUPDOWN[i]);
	}

	DELET(hMicOptTitle);
	DELET(hMicSortLine);
	DELET(hMicONBack);
	DELET(hMicONChk);
	DELET(hMicVolBar);
	DELET(hMicOptToolTip);
	DELET(hBtnCloseToolTip);
	DELET(hClanChatToolTip);
	DELET(hChatClanWon);
}













int cN_Pressf = 0;	//¸®½ºÆ®Áß ´©¸¥ ¹øÈ£
int cN_PressfDBL = 0;	//¸®½ºÆ®Áß ´õºíÅ¬¸¯ ´©¸¥ ¹øÈ£.



void cN_PressfDBL_clear()
{
	cN_PressfDBL = 0;
}



void CLANEntity_chatting::chat_WhisperPartyPlayer2(int num)
{
	if (cN_Pressf == 0)
	{
		cN_Pressf = num;
		return;
	}
	else
	{
		cN_PressfDBL = cN_Pressf;
		cN_Pressf = 0;
		WhisperPartyPlayer(szChatClanWon[(cN_PressfDBL - 4)]);
	}
}





//µ¿·á->Ä£±¸->ÃÖ±Ù¸ñ·Ï,Ä£±¸¸ñ·Ï¿¡¼­ ´õºíÅ¬¸¯½Ã ±Ó¸»ÇÑ´Ù.
void CLANEntity_chatting::chat_WhisperPartyPlayer(int num)
{
	if (num != -1)
	{
		cN_Pressf = num;		//ÆÄ¶õ»ö
		return;
	}
	else
	{
		if (cN_PressfDBL == cN_Pressf)
		{
			cN_PressfDBL = 0;
			return;
		}

		cN_PressfDBL = cN_Pressf;

		WhisperPartyPlayer(szChatClanWon[(cN_PressfDBL - 4)]);
	}
}


void clan_chat_WhisperPartyPlayer_close()	//hoparty.cpp¿¡¼­ ºÒ¸§.
{
	cClanChatting.chat_WhisperPartyPlayer_close();
}
//±Ó¸»º¸³»±â ¿£ÅÍÄ£ÈÄ ºÎ¸¥´Ù.
void CLANEntity_chatting::chat_WhisperPartyPlayer_close()
{
	//cN_PressfDBL =0;
	cN_Pressf = 0;

	//i+nScl_Bar
	//if(ClanChatList.clanWon[i+nScl_Bar])
	//{
}













//
void chatList_Main_CHATLIST_END()
{
	bOpenChatList = FALSE;   //´ÝÇû´Ù´Â°ÍÀ» ¾Ë·ÁÁÜ.
}


//*****************************************************************************
int ret_menuN = 0;
void CLANEntity_chatting::Main()
{


	int i;
	char szFile[255];
	char server;
	char uniqueclanmark[64];
	if (life == 0) return;

	ret_menuN = 0;

	switch (ChatList_CmenuN)
	{
	case CHATLIST_END:
		//C_menuN = CLAN_AllEnd;				
		OpenFlag = 0;
		ChatList_CmenuN = 0;
		ChatList_CmenuN2 = 0;
		//ktj
		ClanCharMove = 0;
		ClanCLCharMove = 0;
		cnt = 0;
		CLAN_ERROR_ret = -1;
		//bIsClose = FALSE;			
		//MOUSE0()=0;	
		ClanCLCharMove = 0;
		ret_menuN = 3;

		g_nMicBtn = 0;


		void TJBscrollWheelClear_ChatL();	//hoparty.cpp¿¡ »ç¿ëÅ°À§ÇÑÇÔ¼ö
		TJBscrollWheelClear_ChatL();		//hoparty.cpp¿¡ »ç¿ëÅ°À§ÇÑÇÔ¼ö
		break;

	case CHATLIST_READDATA:

		switch (ChatList_CmenuN2)
		{
		case 0:
			bIsReadData = TRUE;
			ClanCLCharMove = 1;		//¿ùµå¿¡ ¸¶¿ì½º Ã½Å©¾ÈµÇµµ·ÏÇÔ.

			ANSdata.ret_val = -1;

			WebDB.Resume();		//À¥db¸¦ Àç°³ÇÑ´Ù.
			//Å¬·£ÀÇ ¸â¹öµ¥ÀÌÅ¸¸¦ ÀÐ´Â´Ù.
			WebDB.ReadClan(cldata.szID, cldata.gserver, cldata.ClanZang_Name);
			ChatList_CmenuN2 = 1;
			break;
		case 1:
			switch (ANSdata.ret_val)
			{
				//ygy
			case 0://°¡ÀÔÇÑ Å¬·£ÀÌ ¾øÀ½
				WebDB.Suspend();

				ChatList_CmenuN = CHATLIST_END;		//¿¡·¯¸Þ´ºº¸¿©ÁØÈÄ±×³É³¡³½´Ù.
				ChatList_CmenuN2 = -1;
				break;
			case 1://Á¤»óÀûÀ¸·Î Å¬·£¸âº¸µ¥ÀÌÅ¸¹Þ¾Æ ÆÄ½Ì
				WebDB.Suspend();
				ParsigClanWon(ANSdata.ret_Buf);
				server = cldata.ClanMark[0];
				lstrcpy(uniqueclanmark, &cldata.ClanMark[3]);

				wsprintf(szFile, "%s\\%s\\%c_%s.%s", SAVE_DIR, szConnServerName, server, uniqueclanmark, SAVE_EXE);

				if (strcmp(szFile_hMark, szFile) != 0)
				{
					lstrcpy(szFile_hMark, szFile);
					hMark = LoadDibSurfaceOffscreen(szFile_hMark);

					extern char loadis[256];
					wsprintf(loadis, "·ÎµåµÊ %s ", szFile_hMark);

					if (hMark == NULL)
					{
						wsprintf(loadis, "·Îµå¸øÇß´Ù. %s ", szFile_hMark);

						ChatList_CmenuN = CHATLIST_READ_CLANMARK;
						ChatList_CmenuN2 = 0;
						break;
					}
				}

				ChatList_CmenuN = CLAN_DISPLAY_OPEN;
				menuInit(ChatList_CmenuN);
				ChatList_CmenuN2 = -1;
				break;
			case 100:
				WebDB.Suspend();

				ChatList_CmenuN = CHATLIST_END;
				ChatList_CmenuN2 = -1;
				break;
			case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				ChatList_CmenuN = CLAN_ERROR;
				break;
			default:
				if (ANSdata.ret_val != -1)
				{
					WebDB.Suspend();
					ChatList_CmenuN = 254;
					menuInit(ChatList_CmenuN);

					ChatList_CmenuN2 = -1;
				}
				break;
			}
			break;
		}
		break;
	case CLAN_DISPLAY_BEFORE:
		ChatList_CmenuN = CLAN_DISPLAY_INFO;
		menuInit(ChatList_CmenuN);
		break;
	case CLAN_DISPLAY_INFO:
		i = chkeckMenuN();
		switch (i)
		{
		case 0:
			menuMouseOver[0] = 1;
			break;
		case 1:
			menuMouseOver[1] = 1;
			break;
		case 12:
			i = i;
			break;
		case 13:
			i = i;
			break;
		case 24:
			menuMouseOver[24] = 1;
			break;
		case 25:
			if (g_nMicBtn == 0)
				break;
			else if (g_nMicBtn == 1)
				menuMouseOver[25] = 1;
			break;
		case 26:
			if (g_nMicBtn == 0)
				break;
			else if (g_nMicBtn == 1)
				menuMouseOver[26] = 1;
			break;
		case 27:
			if (g_nMicBtn == 0)
				break;
			else if (g_nMicBtn == 1)
				menuMouseOver[27] = 1;
			break;
		case 28:
			if (g_nMicBtn == 0)
				break;
			else if (g_nMicBtn == 1)
				menuMouseOver[28] = 1;
			break;
		case 29:
			if (g_nMicBtn == 0)
				break;
			else if (g_nMicBtn == 1)
				menuMouseOver[29] = 1;
			break;

		default:
			memset(menuMouseOver, -1, sizeof(int) * 30);
			break;
		}




		extern BOOL IsDrawGuideHelp;
		//ygy : ²À »ì¸±°Í
		if (!IsDrawGuideHelp)
		{
			if (TJwheel != 0)
			{
				scrIconPos.top = tscr_CL.ret_WHEELpoint(TJwheel, scrIconPos.top);
				nScl_Bar = tscr_CL.topScrollLineNum(scrIconPos.top);
				TJwheel = 0;
			}
		}

		if (MOUSE0_2())
		{
			i = i;
			switch (i)
			{
			case 16:
			case 17:
			case 18:
			case 19:
			case 20:
			case 21:
			case 22:
			case 23:
				if (cldata.clanWon[(i - 16) + nScl_Bar][0] != 0)
					chat_WhisperPartyPlayer((i - 12) + nScl_Bar);
				break;
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
				MOUSE0_2() = 0;
				if (cldata.clanWon[(i - 4) + nScl_Bar][0] != 0)
					chat_WhisperPartyPlayer2(i + nScl_Bar);

				if (!banisF[(i - 4) + nScl_Bar])
				{
					ZeroMemory(banisF, sizeof(banisF));
					banisF[(i - 4) + nScl_Bar] = !banisF[(i - 4) + nScl_Bar];
				}
				break;
			case 0:
				int IsClanChatting();
				IsClanChatting();

				MOUSE0_2() = 0;
				break;
			case 1:
				ChatList_CmenuN = CHATLIST_END;
				cnt = 0;
				CLAN_ERROR_ret = -1;
				ClanCLCharMove = 0;
				OpenFlag = 0;
				ChatList_CmenuN = 0;
				ChatList_CmenuN2 = 0;
				ClanCharMove = 0;
				ClanCLCharMove = 0;
				bOpenChatList = FALSE;
				ret_menuN = 3;
				g_nMicBtn = 0;
				break;
			case 12:
				nScl_Bar = tscr_CL.topScrollLineNum(pCursorPos.y);
				scrIconPos.top = pCursorPos.y - 8;
				break;
			case 15:
				if (cN_PressfDBL != 0)
					break;
				void TJBscrollWheelClear_ChatL();
				TJBscrollWheelClear_ChatL();

				ChatList_CmenuN = CHATLIST_END;
				cnt = 0;
				CLAN_ERROR_ret = -1;
				ClanCLCharMove = 0;
				OpenFlag = 0;
				ChatList_CmenuN = 0;
				ChatList_CmenuN2 = 0;
				ClanCharMove = 0;
				ClanCLCharMove = 0;
				bOpenChatList = FALSE;
				ret_menuN = 1;
				g_nMicBtn = 0;
				break;
			case 14:
				if (cN_PressfDBL != 0)
					break;
				void TJBscrollWheelClear_ChatL();
				TJBscrollWheelClear_ChatL();

				ChatList_CmenuN = CHATLIST_END;
				cnt = 0;
				CLAN_ERROR_ret = -1;
				ClanCLCharMove = 0;
				OpenFlag = 0;
				ChatList_CmenuN = 0;
				ChatList_CmenuN2 = 0;
				ClanCharMove = 0;
				ClanCLCharMove = 0;
				bOpenChatList = FALSE;
				ret_menuN = 2;

				g_nMicBtn = 0;
				break;
				void fd2(char *fmt, ...);
			case 24:

				MOUSE0_2() = 0;
				if (g_nMicBtn == 1)
					g_nMicBtn = 0;
				else if (g_nMicBtn == 0)
				{
					g_nMicBtn = 1;
					if (micInit == 0)
					{
						micInit = cmicvol.Init();
						if (micInit != 0)
							nVol = (int)(cmicvol.VolDevice(&cmicvol.m_MicIn) / cmicvol.nVolStep);
					}
				}
				break;
			case 25:
				MOUSE0_2() = 0;
				if (g_nMicBtn == 1)
					g_nMicBtn = 0;
				break;
			case 26:
				MOUSE0_2() = 0;
				if (bMic == FALSE)
				{
					bMic = TRUE;
					void ParkSetMicOnOFF();
					ParkSetMicOnOFF();
				}
				break;
			case 27:
				MOUSE0_2() = 0;
				if (bMic == TRUE)
				{
					bMic = FALSE;
					void ParkSetMicOnOFF();
					ParkSetMicOnOFF();
				}
				break;
			case 28:
				MOUSE0_2() = 0;
				if (micInit != 0)
				{
					nVol = nVol - 10;
					if (nVol < 0)
					{
						nVol = 0;
						break;
					}
					else
					{
						float ntmp;
						ntmp = ((float)nVol / 10)*cmicvol.nVolStep;
						if (ntmp <= 0)
							ntmp = 0;
						cmicvol.SetDeviceCtrl(&cmicvol.m_MicIn, ntmp);
						break;
					}
				}
				break;
			case 29:
				MOUSE0_2() = 0;
				if (micInit != 0)
				{
					nVol = nVol + 10;
					if (nVol >= 90)
					{
						nVol = 90;
						break;
					}
					else
					{
						float ntmp;
						ntmp = ((float)nVol / 10)*cmicvol.nVolStep;
						if (ntmp >= cmicvol.m_MicIn.nMax)
							ntmp = (float)cmicvol.m_MicIn.nMax;
						cmicvol.SetDeviceCtrl(&cmicvol.m_MicIn, ntmp);
						break;
					}
				}
				break;
			default:
				MOUSE0_2() = 0;
				break;
			}
		}
		if (MouseDblClick)
		{
			switch (i)
			{
			case 16:
			case 17:
			case 18:
			case 19:
			case 20:
			case 21:
			case 22:
			case 23:
				chat_WhisperPartyPlayer(-1);
				MouseDblClick = 0;
				break;
			}
		}

		break;
	case CLAN_DISPLAY_OPEN:

		OCcnt++;
		if (OpenBuf_x[OCcnt] == -1)
		{
			bOpenChatList = TRUE;
			ChatList_CmenuN = CLAN_DISPLAY_INFO;
			menuInit(ChatList_CmenuN);
			OCcnt--;
		}
		else
			ChatListBoxX = OpenBuf_x[OCcnt];
		break;

	case CLAN_DISPLAY_CLOSE:
		OCcnt--;
		if (OCcnt == 0)
		{
			bOpenChatList = FALSE;
			ChatList_CmenuN = CHATLIST_END;
			menuInit(ChatList_CmenuN);
			OCcnt = 0;
		}
		ChatListBoxX = OpenBuf_x[OCcnt];

		break;

	case CLAN_CLOSE_END_BEFORE:
		bIsClose = TRUE;
		AddSize = 0;
		cnt = 0;
		ChatList_CmenuN = CLAN_CLOSE_ENDING;
		break;

	case CLAN_CLOSE_ENDING:
		OCcnt--;
		if (OCcnt == 0)
		{
			ChatList_CmenuN2 = 0;
			OpenFlag = 1;
			joinAnswer = 0;
			ChatList_CmenuN = CLAN_NPC_START;
			menuInit(ChatList_CmenuN);
			OCcnt = 0;
			AddSize = 0;
		}
		ChatListBoxX = OpenBuf_x[OCcnt];
		break;

	case CHATLIST_READ_CLANMARK:

		switch (ChatList_CmenuN2)
		{
		case 0:
			ANSdata.ret_val = -1;
			WebDB.Resume();
			WebDB.MarkREAD(cldata.name, cldata.ClanMark);
			ChatList_CmenuN2 = 1;
			break;
		case 1:
			switch (ANSdata.ret_val)
			{
			case 1:
				WebDB.Suspend();
				ChatList_CmenuN = CHATLIST_READDATA;
				ChatList_CmenuN2 = 0;
				break;
			case 2:
				WebDB.Suspend();
				break;
			case ISAO_ERR_TCP_CONNECT:
				WebDB.Suspend();
				break;
			default:
				if (ANSdata.ret_val != -1)
					WebDB.Suspend();
				break;
			}
		}
		break;
	}
}

void CLANEntity_chatting::menuInit(int num)
{
	int bx = 0, by = 0;
	int      nNext = 0, nMenuPos = 0, nAdd = 0, nWidth = 0;
	int      nFirstIconSave = 0;
	char szFile[255];
	char server;
	char UniqueClanMark[64];

	switch (num)
	{
	case CLAN_DISPLAY_INFO:
		if (vrunRuning == 0)
			ChatList_menuSu = 23;
		else if (vrunRuning == 1)
			ChatList_menuSu = 30;

		nScl_Bar = 0;
		SortClanWonList();
		server = cldata.ClanMark[0];
		lstrcpy(UniqueClanMark, &cldata.ClanMark[3]);

		wsprintf(szFile, "%s\\%s\\%c_%s.%s", SAVE_DIR, szConnServerName, server, UniqueClanMark, SAVE_EXE);

		if (lstrcmp(szFile_hMark, szFile) != 0)
		{
			lstrcpy(szFile_hMark, szFile);

			DELET(hMark);

			hMark = LoadDibSurfaceOffscreen(szFile_hMark);

			extern char loadis[256];
			wsprintf(loadis, "·ÎµåµÊ %s ", szFile_hMark);


			if (hMark == NULL)
			{
				wsprintf(loadis, "·Îµå¸øÇß´Ù. %s ", szFile_hMark);
				ChatList_CmenuN = CHATLIST_READ_CLANMARK;
				ChatList_CmenuN2 = 0;

			}
		}

		bx = 20;
		by = 20;

		ChatList_menuPos[0].left = CHATICON_X;//174;		//yes
		ChatList_menuPos[0].top = CHATICON_Y;//353;
		ChatList_menuPos[0].right = ChatList_menuPos[0].left + bx;
		ChatList_menuPos[0].bottom = ChatList_menuPos[0].top + by;

		bx = 20;
		by = 20;


		ChatList_menuPos[1].left = CHATCLOSE_X;//254		//no
		ChatList_menuPos[1].top = CHATICON_Y; //353
		ChatList_menuPos[1].right = ChatList_menuPos[1].left + bx;
		ChatList_menuPos[1].bottom = ChatList_menuPos[1].top + by;

		bx = 68;
		by = 27;

		ChatList_menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;//166;		//yes Å×µÎ¸® ¹Ú½º
		ChatList_menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;//348
		ChatList_menuPos[2].right = ChatList_menuPos[2].left + bx;
		ChatList_menuPos[2].bottom = ChatList_menuPos[2].top + by;

		bx = 68;
		by = 27;

		ChatList_menuPos[3].left = BackStartPos.x + BUTTON2_BOX_X;	//246	//no Å×µÎ¸® ¹Ú½º
		ChatList_menuPos[3].top = BackStartPos.y + BUTTON2_BOX_Y;//348
		ChatList_menuPos[3].right = ChatList_menuPos[3].left + bx;
		ChatList_menuPos[3].bottom = ChatList_menuPos[3].top + by;

		bx = 13;
		by = 17;

		ChatList_menuPos[4].left = CHATING_CLANWON_LIST_X;	//246	//no Å×µÎ¸® ¹Ú½º
		ChatList_menuPos[4].top = CHATING_CLANWON_LIST_Y;//348
		ChatList_menuPos[4].right = ChatList_menuPos[4].left + bx;
		ChatList_menuPos[4].bottom = ChatList_menuPos[4].top + by;

		bx = 13;
		by = 17;

		ChatList_menuPos[5].left = CHATING_CLANWON_LIST_X;
		ChatList_menuPos[5].top = CHATING_CLANWON_LIST_Y + (CHATING_CLANWON_LIST_CAP * 1);
		ChatList_menuPos[5].right = ChatList_menuPos[5].left + bx;
		ChatList_menuPos[5].bottom = ChatList_menuPos[5].top + by;

		bx = 13;
		by = 17;

		ChatList_menuPos[6].left = CHATING_CLANWON_LIST_X;
		ChatList_menuPos[6].top = CHATING_CLANWON_LIST_Y + (CHATING_CLANWON_LIST_CAP * 2);
		ChatList_menuPos[6].right = ChatList_menuPos[6].left + bx;
		ChatList_menuPos[6].bottom = ChatList_menuPos[6].top + by;

		bx = 13;
		by = 17;

		ChatList_menuPos[7].left = CHATING_CLANWON_LIST_X;
		ChatList_menuPos[7].top = CHATING_CLANWON_LIST_Y + (CHATING_CLANWON_LIST_CAP * 3);
		ChatList_menuPos[7].right = ChatList_menuPos[7].left + bx;
		ChatList_menuPos[7].bottom = ChatList_menuPos[7].top + by;

		bx = 13;
		by = 17;

		ChatList_menuPos[8].left = CHATING_CLANWON_LIST_X;
		ChatList_menuPos[8].top = CHATING_CLANWON_LIST_Y + (CHATING_CLANWON_LIST_CAP * 4);
		ChatList_menuPos[8].right = ChatList_menuPos[8].left + bx;
		ChatList_menuPos[8].bottom = ChatList_menuPos[8].top + by;

		bx = 13;
		by = 17;

		ChatList_menuPos[9].left = CHATING_CLANWON_LIST_X;
		ChatList_menuPos[9].top = CHATING_CLANWON_LIST_Y + (CHATING_CLANWON_LIST_CAP * 5);
		ChatList_menuPos[9].right = ChatList_menuPos[9].left + bx;
		ChatList_menuPos[9].bottom = ChatList_menuPos[9].top + by;

		bx = 13;
		by = 17;

		ChatList_menuPos[10].left = CHATING_CLANWON_LIST_X;
		ChatList_menuPos[10].top = CHATING_CLANWON_LIST_Y + (CHATING_CLANWON_LIST_CAP * 6);
		ChatList_menuPos[10].right = ChatList_menuPos[10].left + bx;
		ChatList_menuPos[10].bottom = ChatList_menuPos[10].top + by;

		bx = 13;
		by = 17;

		ChatList_menuPos[11].left = CHATING_CLANWON_LIST_X;
		ChatList_menuPos[11].top = CHATING_CLANWON_LIST_Y + (CHATING_CLANWON_LIST_CAP * 7);
		ChatList_menuPos[11].right = ChatList_menuPos[11].left + bx;
		ChatList_menuPos[11].bottom = ChatList_menuPos[11].top + by;

		tscr_CL.Init(0);


		nMenuPos = 12;
		//================½ºÅ©·Ñ ¹Ù
		//if(nTotalClanWon> CHATING_DISPLAY_MAX)		
		if (nClanWon_Num > CHATING_DISPLAY_MAX)
		{
			bx = 16;
			by = 16;

			ChatList_menuPos[nMenuPos].left = CHATLIST_SBAR_X;
			ChatList_menuPos[nMenuPos].top = CHATLIST_SBAR_Y;
			ChatList_menuPos[nMenuPos].right = ChatList_menuPos[nMenuPos].left + 8;
			ChatList_menuPos[nMenuPos].bottom = ChatList_menuPos[nMenuPos].top + 160;

			tscr_CL.Init(1);
			tscr_CL.Init(ChatList_menuPos[nMenuPos].top,
				ChatList_menuPos[nMenuPos].top + 160,
				nClanWon_Num, CHATING_DISPLAY_MAX);


			scrIconPos.left = ChatList_menuPos[nMenuPos].left - 5;
			scrIconPos.top = ChatList_menuPos[nMenuPos].top + 2;
		}

		nMenuPos = 13;  //Å¬·£

		nMenuPos += 1; //Ä£±¸
		ChatList_menuPos[nMenuPos].left = 665;
		ChatList_menuPos[nMenuPos].top = CHATLIST_BOX_Y + 10;

		ChatList_menuPos[nMenuPos].right = ChatList_menuPos[nMenuPos].left + 50;
		ChatList_menuPos[nMenuPos].bottom = ChatList_menuPos[nMenuPos].top + 23;

		nMenuPos += 1; //µ¿·á
		ChatList_menuPos[nMenuPos].left = 603;
		ChatList_menuPos[nMenuPos].top = CHATLIST_BOX_Y + 10;
		ChatList_menuPos[nMenuPos].right = ChatList_menuPos[nMenuPos].left + 56;
		ChatList_menuPos[nMenuPos].bottom = ChatList_menuPos[nMenuPos].top + 23;

		bx = 64;
		by = 17;

		ChatList_menuPos[16].left = ChatList_menuPos[4].left + 35;
		ChatList_menuPos[16].top = ChatList_menuPos[4].top;
		ChatList_menuPos[16].right = ChatList_menuPos[16].left + bx;
		ChatList_menuPos[16].bottom = ChatList_menuPos[16].top + by;


		ChatList_menuPos[17].left = ChatList_menuPos[5].left + 35;
		ChatList_menuPos[17].top = ChatList_menuPos[5].top;
		ChatList_menuPos[17].right = ChatList_menuPos[17].left + bx;
		ChatList_menuPos[17].bottom = ChatList_menuPos[17].top + by;

		ChatList_menuPos[18].left = ChatList_menuPos[6].left + 35;
		ChatList_menuPos[18].top = ChatList_menuPos[6].top;
		ChatList_menuPos[18].right = ChatList_menuPos[18].left + bx;
		ChatList_menuPos[18].bottom = ChatList_menuPos[18].top + by;

		ChatList_menuPos[19].left = ChatList_menuPos[7].left + 35;
		ChatList_menuPos[19].top = ChatList_menuPos[7].top;
		ChatList_menuPos[19].right = ChatList_menuPos[19].left + bx;
		ChatList_menuPos[19].bottom = ChatList_menuPos[19].top + by;

		ChatList_menuPos[20].left = ChatList_menuPos[8].left + 35;
		ChatList_menuPos[20].top = ChatList_menuPos[8].top;
		ChatList_menuPos[20].right = ChatList_menuPos[20].left + bx;
		ChatList_menuPos[20].bottom = ChatList_menuPos[20].top + by;

		ChatList_menuPos[21].left = ChatList_menuPos[9].left + 35;
		ChatList_menuPos[21].top = ChatList_menuPos[9].top;
		ChatList_menuPos[21].right = ChatList_menuPos[21].left + bx;
		ChatList_menuPos[21].bottom = ChatList_menuPos[21].top + by;

		ChatList_menuPos[22].left = ChatList_menuPos[10].left + 35;
		ChatList_menuPos[22].top = ChatList_menuPos[10].top;
		ChatList_menuPos[22].right = ChatList_menuPos[22].left + bx;
		ChatList_menuPos[22].bottom = ChatList_menuPos[22].top + by;

		ChatList_menuPos[23].left = ChatList_menuPos[11].left + 35;
		ChatList_menuPos[23].top = ChatList_menuPos[11].top;
		ChatList_menuPos[23].right = ChatList_menuPos[23].left + bx;
		ChatList_menuPos[23].bottom = ChatList_menuPos[23].top + by;

		bx = 20;
		by = 20;

		ChatList_menuPos[24].left = CHATICON_X + 30;
		ChatList_menuPos[24].top = CHATICON_Y;
		ChatList_menuPos[24].right = ChatList_menuPos[24].left + bx;
		ChatList_menuPos[24].bottom = ChatList_menuPos[24].top + by;

		bx = 20;
		by = 20;

		ChatList_menuPos[25].left = 560;
		ChatList_menuPos[25].top = 375;
		ChatList_menuPos[25].right = ChatList_menuPos[25].left + bx;
		ChatList_menuPos[25].bottom = ChatList_menuPos[25].top + by;

		bx = 20;
		by = 20;

		ChatList_menuPos[26].left = 511;
		ChatList_menuPos[26].top = 249;
		ChatList_menuPos[26].right = ChatList_menuPos[26].left + bx;
		ChatList_menuPos[26].bottom = ChatList_menuPos[26].top + by;

		bx = 20;
		by = 20;

		ChatList_menuPos[27].left = 559;
		ChatList_menuPos[27].top = 249;
		ChatList_menuPos[27].right = ChatList_menuPos[27].left + bx;
		ChatList_menuPos[27].bottom = ChatList_menuPos[27].top + by;

		bx = 20;
		by = 20;

		ChatList_menuPos[28].left = 438;
		ChatList_menuPos[28].top = 300;
		ChatList_menuPos[28].right = ChatList_menuPos[28].left + bx;
		ChatList_menuPos[28].bottom = ChatList_menuPos[28].top + by;

		bx = 20;
		by = 20;

		ChatList_menuPos[29].left = 557;
		ChatList_menuPos[29].top = 300;
		ChatList_menuPos[29].right = ChatList_menuPos[29].left + bx;
		ChatList_menuPos[29].bottom = ChatList_menuPos[29].top + by;

		break;
	case CLAN_DISPLAY_OPEN: //Å¬·£ ±¸¼º¿ø
		SortClanWonList();
		ChatList_menuSu = 9;
		nScl_Bar = 0;

		bx = 20;
		by = 20;


		ChatList_menuPos[0].left = BackStartPos.x + CHATICON_X;//174;		//yes
		ChatList_menuPos[0].top = BackStartPos.y + CHATICON_Y;//353;
		ChatList_menuPos[0].right = ChatList_menuPos[0].left + bx;
		ChatList_menuPos[0].bottom = ChatList_menuPos[0].top + by;

		bx = 20;
		by = 20;

		ChatList_menuPos[1].left = BackStartPos.x + CHATCLOSE_X;//254		//no
		ChatList_menuPos[1].top = BackStartPos.y + CHATICON_Y; //353
		ChatList_menuPos[1].right = ChatList_menuPos[1].left + bx;
		ChatList_menuPos[1].bottom = ChatList_menuPos[1].top + by;

		bx = 68;
		by = 27;

		ChatList_menuPos[2].left = BackStartPos.x + BUTTON1_BOX_X;//166;		//yes Å×µÎ¸® ¹Ú½º
		ChatList_menuPos[2].top = BackStartPos.y + BUTTON1_BOX_Y;//348
		ChatList_menuPos[2].right = ChatList_menuPos[2].left + bx;
		ChatList_menuPos[2].bottom = ChatList_menuPos[2].top + by;

		bx = 68;
		by = 27;

		ChatList_menuPos[3].left = BackStartPos.x + BUTTON2_BOX_X;	//246	//no Å×µÎ¸® ¹Ú½º
		ChatList_menuPos[3].top = BackStartPos.y + BUTTON2_BOX_Y;//348
		ChatList_menuPos[3].right = ChatList_menuPos[3].left + bx;
		ChatList_menuPos[3].bottom = ChatList_menuPos[3].top + by;

		bx = 139;
		by = 30;


		ChatList_menuPos[4].left = BackStartPos.x + 10;	//246	//no Å×µÎ¸® ¹Ú½º
		ChatList_menuPos[4].top = BackStartPos.y + 55;//348
		ChatList_menuPos[4].right = ChatList_menuPos[4].left + bx;
		ChatList_menuPos[4].bottom = ChatList_menuPos[4].top + by;

		bx = 139;
		by = 30;


		ChatList_menuPos[4].left = BackStartPos.x + CHATING_CLANWON_LIST_X;	//246	//no Å×µÎ¸® ¹Ú½º
		ChatList_menuPos[4].top = BackStartPos.y + CHATING_CLANWON_LIST_Y;//348
		ChatList_menuPos[4].right = ChatList_menuPos[4].left + bx;
		ChatList_menuPos[4].bottom = ChatList_menuPos[4].top + by;

		bx = 139;
		by = 30;

		ChatList_menuPos[5].left = BackStartPos.x + CHATING_CLANWON_LIST_X;
		ChatList_menuPos[5].top = BackStartPos.y + CHATING_CLANWON_LIST_Y + (CHATING_CLANWON_LIST_CAP * 1);
		ChatList_menuPos[5].right = ChatList_menuPos[5].left + bx;
		ChatList_menuPos[5].bottom = ChatList_menuPos[5].top + by;

		bx = 139;
		by = 30;

		ChatList_menuPos[6].left = BackStartPos.x + CHATING_CLANWON_LIST_X;
		ChatList_menuPos[6].top = BackStartPos.y + CHATING_CLANWON_LIST_Y + (CHATING_CLANWON_LIST_CAP * 2);
		ChatList_menuPos[6].right = ChatList_menuPos[6].left + bx;
		ChatList_menuPos[6].bottom = ChatList_menuPos[6].top + by;

		bx = 139;
		by = 30;

		ChatList_menuPos[7].left = BackStartPos.x + CHATING_CLANWON_LIST_X;
		ChatList_menuPos[7].top = BackStartPos.y + CHATING_CLANWON_LIST_Y + (CHATING_CLANWON_LIST_CAP * 3);
		ChatList_menuPos[7].right = ChatList_menuPos[7].left + bx;
		ChatList_menuPos[7].bottom = ChatList_menuPos[7].top + by;

		//ktj ½ºÅ©·Ñ°ü·Ã
		tscr_CL.Init(0);


		nMenuPos = 8;

		if (nClanWon_Num > CHATING_DISPLAY_MAX)
		{
			bx = 16;
			by = 16;

			ChatList_menuPos[nMenuPos].left = BackStartPos.x + CHATLIST_SBAR_X;
			ChatList_menuPos[nMenuPos].top = BackStartPos.y + CHATLIST_SBAR_Y;
			ChatList_menuPos[nMenuPos].right = ChatList_menuPos[nMenuPos].left + 8;
			ChatList_menuPos[nMenuPos].bottom = ChatList_menuPos[nMenuPos].top + 160;

			tscr_CL.Init(1);
			tscr_CL.Init(ChatList_menuPos[nMenuPos].top, //BackStartPos.y + SCROOBAR_TOP, 
				ChatList_menuPos[nMenuPos].top + 160,//256,
			//g_nClanIconNum, CLANHELPICON_DISPLAY_MAX);
				nClanWon_Num, CHATING_DISPLAY_MAX);


			scrIconPos.left = ChatList_menuPos[nMenuPos].left - 5;//BackStartPos.x + 275-5;//SCROLLBAR_LEFT-4;
			scrIconPos.top = ChatList_menuPos[nMenuPos].top + 2;//BackStartPos.y  + 87 -8;//(BackStartPos.y + SCROOBAR_TOP)-8;
		}

		break;

	}
}




void CLANEntity_chatting::Draw()
{
	int i = 0, nIconCount = 0;
	int nIconPos = 0;
	int nSaveTop = 0, nAdd = 0;
	int nStrLen = 0;
	char szDrawMenuMsg[2024];
	ZeroMemory(szDrawMenuMsg, sizeof(char) * 2024);
	int nMenuPos = 0;

	switch (ChatList_CmenuN)
	{
	case CHATLIST_END:
	case CHATLIST_READDATA:
		DrawBox();
		break;
	case CLAN_DISPLAY_INFO:
		DrawBox();
		Draw_C_menuN();
		break;


	case CLAN_DISPLAY_OPEN:
		DrawBox();
		break;
	case CLAN_DISPLAY_CLOSE:
	case CLAN_CLOSE_ENDING:
		DrawBox();
		break;

	}
}


void CLANEntity_chatting::InitClanWon()
{
	nTotalClanWon = 6;
	nRest_Num = nTotalClanWon - CHATING_DISPLAY_MAX;
}

void CLANEntity_chatting::SortClanWonList()
{
	int ZangL = lstrlen(cldata.ClanZang_Name);
	int ZangL2 = lstrlen(cldata.SubChip);
	BOOL bFlag = FALSE;
	int i;

	ZeroMemory(szChatClanWon, sizeof(szChatClanWon));

	if (cldata.myPosition == CLANCHIP)
	{
		if (cldata.SubChip[0] != 0)
		{
			if (cldata.SubChip[0] != 0)
				lstrcpy(szChatClanWon[0], cldata.SubChip);
			for (i = 0; i < nClanWon_Num; i++)
			{
				if (i > CLANWON_MAX)
					break;
				else
				{
					if (bFlag)
						lstrcpy(szChatClanWon[i + 1], cldata.clanWon[i + 1]);
					else
					{
						if (((ZangL2 == lstrlen(cldata.clanWon[i])) && lstrcmp(cldata.clanWon[i], cldata.SubChip) == 0))
						{
							lstrcpy(szChatClanWon[i + 1], cldata.clanWon[i + 1]);
							bFlag = TRUE;
						}
						else
							lstrcpy(szChatClanWon[i + 1], cldata.clanWon[i]);
					}
				}
			}
		}
		else
			memcpy(szChatClanWon, cldata.clanWon, sizeof(cldata.clanWon));
	}
	int j = 0;

	if ((cldata.myPosition == CLANUSER) || (cldata.myPosition == CLAN_SUBCHIP))
	{
		i = 0;
		lstrcpy(szChatClanWon[0], cldata.ClanZang_Name);
		if (cldata.SubChip[0] != 0)
		{
			if (lstrcmp(cldata.ChaName, cldata.SubChip) != 0)
			{
				lstrcpy(szChatClanWon[1], cldata.SubChip);
				i = 1;
			}

		}
		while (i < nClanWon_Num)
		{
			if (((ZangL == lstrlen(cldata.clanWon[j])) && lstrcmp(cldata.clanWon[j], cldata.ClanZang_Name) == 0) || ((ZangL2 == lstrlen(cldata.clanWon[j])) && lstrcmp(cldata.clanWon[j], cldata.SubChip) == 0))
				j++;
			else
			{
				++i;
				lstrcpy(szChatClanWon[i], cldata.clanWon[j]);
				j++;
			}
		}
	}
}

void CLANEntity_chatting::Load2()
{
	hChatListBoxLine = CreateTextureMaterial("image\\party\\party_win.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	hChatListBoxTitle2 = CreateTextureMaterial("image\\party\\title-clan.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	hChatMicOpt = CreateTextureMaterial("image\\party\\quest_win.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

}

void CLANEntity_chatting::Load()
{
	hChatListBoxLine = CreateTextureMaterial("image\\party\\party_win.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);


	hChatListBoxTitle2 = CreateTextureMaterial("image\\party\\title-clan.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	hChatListBoxTitle = LoadDibSurfaceOffscreen("image\\party\\title-clan.bmp");


	hButtonClose[0] = LoadDibSurfaceOffscreen("image\\party\\close_.bmp");
	hButtonClose[1] = LoadDibSurfaceOffscreen("image\\party\\ButtonExit.bmp");
	hClanWon[0] = LoadDibSurfaceOffscreen("image\\party\\party_man_0.bmp");
	hClanWon[1] = LoadDibSurfaceOffscreen("image\\party\\party_man_1.bmp");
	hChatIcon[0] = LoadDibSurfaceOffscreen("image\\party\\ButtonChatting_.bmp");
	hChatIcon[1] = LoadDibSurfaceOffscreen("image\\party\\ButtonChatting.bmp");
	hChatClanWon = LoadDibSurfaceOffscreen("image\\party\\chattng-icon-c.bmp");

	hMicOption[0] = LoadDibSurfaceOffscreen("image\\party\\ButtonMike_.bmp");
	hMicOption[1] = LoadDibSurfaceOffscreen("image\\party\\ButtonMike.bmp");
	hMicOptTitle = LoadDibSurfaceOffscreen("image\\party\\mike-title.bmp");
	hMicSortLine = LoadDibSurfaceOffscreen("image\\party\\mike-line.bmp");
	hMicONBack = LoadDibSurfaceOffscreen("image\\party\\mike-onoffbox.bmp");
	hMicONChk = LoadDibSurfaceOffscreen("image\\party\\mike-onoff.bmp");
	hMicVolBar = LoadDibSurfaceOffscreen("image\\party\\mike-updown.bmp");
	hMicVOLUPDOWN[0] = LoadDibSurfaceOffscreen("image\\party\\mike-btdown.bmp");
	hMicVOLUPDOWN[1] = LoadDibSurfaceOffscreen("image\\party\\mike-btup.bmp");
	hMicOptToolTip = LoadDibSurfaceOffscreen("image\\party\\ButtonInfo-clan2.bmp");
	hChatMicOpt = CreateTextureMaterial("image\\party\\quest_win.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);


	hClanChatToolTip = LoadDibSurfaceOffscreen("image\\party\\ButtonInfo-chatting.bmp");
	hBtnCloseToolTip = LoadDibSurfaceOffscreen("image\\party\\ButtonInfo-5.bmp");
}

void CLANEntity_chatting::DisplayInfo()
{

}

void CLANEntity_chatting::ChatListUserData(char *id, char *gserver, char *chaid)
{
	lstrcpy(ClanChatList.szUserID, id);
	lstrcpy(ClanChatList.szChaName, chaid);
	lstrcpy(ClanChatList.szGameServer, gserver);
}

void CLANEntity_chatting::ChatListParsingIsClanMember(char* data)
{
	chk_readStrBuf("CZang=", data, ClanChatList.szClanZang_Name);
}


void CLANEntity_chatting::DrawBox()
{
	dsDrawTexImage(hChatListBoxTitle2, ChatListBoxX, CHATLIST_BOX_Y, 256, 32, 255);
	dsDrawTexImage(hChatListBoxLine, ChatListBoxX, CHATLIST_BOX_Y + 8, 256, 256, 255);

	if (g_nMicBtn == 1)
		dsDrawTexImage(hChatMicOpt, ChatListBoxX - 198, CHATLIST_BOX_Y + 23, 256, 256, 255);
}

int cnt__00 = 0;

void CLANEntity_chatting::Draw_C_menuN()
{
	SortClanWonList();
	int nMenuPos, i;
	char szClanWon[40];

	if (Chatting_button > 0)
		DrawSprite(ChatList_menuPos[0].left, ChatList_menuPos[0].top, hChatIcon[1], 0, 0, 20, 20, 1);
	else DrawSprite(ChatList_menuPos[0].left, ChatList_menuPos[0].top, hChatIcon[0], 0, 0, 20, 20, 1);

	if (menuMouseOver[0] > 0)
	{
		DrawSprite(ChatList_menuPos[0].left, ChatList_menuPos[0].top, hChatIcon[1], 0, 0, 20, 20, 1);
		DrawSprite(ChatList_menuPos[0].left - 28, ChatList_menuPos[0].top - 23, hClanChatToolTip, 0, 0, 76, 27, 1);
	}

	if (menuMouseOver[1] > 0)
	{
		DrawSprite(ChatList_menuPos[1].left, ChatList_menuPos[1].top, hButtonClose[1], 0, 0, 20, 20, 1);
		DrawSprite(ChatList_menuPos[1].left - 28, ChatList_menuPos[1].top - 23, hBtnCloseToolTip, 0, 0, 76, 27, 1);
	}
	else DrawSprite(ChatList_menuPos[1].left, ChatList_menuPos[1].top, hButtonClose[0], 0, 0, 20, 20, 1);

	nMenuPos = 4;

	if (vrunRuning == 1)
	{
		if (menuMouseOver[24] > 0)
		{
			DrawSprite(ChatList_menuPos[24].left, ChatList_menuPos[24].top, hMicOption[1], 0, 0, 20, 20, 1);
			DrawSprite(ChatList_menuPos[24].left - 28, ChatList_menuPos[24].top - 23, hMicOptToolTip, 0, 0, 76, 27, 1);
		}
		else DrawSprite(ChatList_menuPos[24].left, ChatList_menuPos[24].top, hMicOption[0], 0, 0, 20, 20, 1);
	}

	if (g_nMicBtn == 1)
	{
		//¸¶ÀÌÅ© ¿É¼Ç Å¸ÀÌÆ² ÀÌ¹ÌÁö
		DrawSprite(446, 196, hMicOptTitle, 0, 0, 17, 23, 1);

		//¸¶ÀÌÅ© ¿É¼Ç °¡·ÎÁß
		DrawSprite(419, 225, hMicSortLine, 0, 0, 174, 3, 1);

		//¸¶ÀÌÅ© on,off ¹é±×¶ó¿îµå
		DrawSprite(511, 249, hMicONBack, 0, 0, 14, 14, 1);
		DrawSprite(559, 249, hMicONBack, 0, 0, 14, 14, 1);

		if (micInit != 0)
		{
			//¸¶ÀÌÅ© º¼·ý¹Ù
			DrawSprite(438, 300, hMicVolBar, 0, 0, 135, 16, 1);
		}

		//¸¶ÀÌÅ© ¿É¼Ç¹öÆ° ¼±ÅÃ‰ç´Ù.
		DrawSprite(ChatList_menuPos[24].left, ChatList_menuPos[24].top, hMicOption[1], 0, 0, 20, 20, 1);

		//¸¶ÀÌÅ© ¿É¼ÇÃ¢ ´Ý±â
		if (menuMouseOver[25] == 1)
		{
			DrawSprite(ChatList_menuPos[25].left, ChatList_menuPos[25].top, hButtonClose[1], 0, 0, 20, 20, 1);
			DrawSprite(ChatList_menuPos[25].left - 28, ChatList_menuPos[25].top - 23, hBtnCloseToolTip, 0, 0, 76, 27, 1);
		}
		else DrawSprite(ChatList_menuPos[25].left, ChatList_menuPos[25].top, hButtonClose[0], 0, 0, 20, 20, 1);

		if (bMic == TRUE)
		{
			DrawSprite(ChatList_menuPos[26].left + 2, ChatList_menuPos[26].top + 2, hMicONChk, 0, 0, 10, 10, 1);
		}
		else
			DrawSprite(ChatList_menuPos[27].left + 2, ChatList_menuPos[27].top + 2, hMicONChk, 0, 0, 10, 10, 1);

		if (micInit != 0)
		{
			//¸¶ÀÌÅ© º¼·ý up
			if (menuMouseOver[28] == 1)
				DrawSprite(ChatList_menuPos[28].left, ChatList_menuPos[28].top, hMicVOLUPDOWN[0], 0, 0, 16, 16, 1);

			//¸¶ÀÌÅ© º¼·ý down
			if (menuMouseOver[29] == 1)
				DrawSprite(ChatList_menuPos[29].left, ChatList_menuPos[29].top, hMicVOLUPDOWN[1], 0, 0, 16, 16, 1);

			DrawSprite(455 + nVol, 304, hMicONChk, 0, 0, 10, 10, 1);
		}


		// ÅØ½ºÆ®¹öÆÛ, x, y, RED, GREEN, BLUE, flag
		//Draw_C_TextPark(parkTextVO , 470, 200, 154, 236, 252, 2);

		//Draw_C_TextPark(parkTextMIC , 438, 251, 255, 255, 255, 0);

		//Draw_C_TextPark(parkTextMicON , 492, 251, 255, 255, 255, 0);
		//Draw_C_TextPark(parkTextMicOFF , 539, 251, 255, 255, 255, 0);

		if (micInit != 0)
		{
			//Draw_C_TextPark(parkTextVol, 438, 283, 255, 255, 255, 0);

			//Draw_C_TextPark(parkTextVolLow, 438, 320, 255, 255, 255, 0);

			//Draw_C_TextPark(parkTextVolHigh, 560, 320, 255, 255, 255, 0);
		}
		else
		{
			//Draw_C_TextPark(parkTextVolErr1, 438, 283, 255, 255, 255, 0);
			//Draw_C_TextPark(parkTextVolErr2, 438, 303, 255, 255, 255, 0);
		}

		extern int vrunRuning;
		if (vrunRuning == 1)
		{
			int cnt = 0;

			extern char voiceInfoStr[256];
			if (voiceInfoStr[0] != 0)
			{
				Draw_C_TextPark(voiceInfoStr, 438, 360, 255, 255, 255, 0);
			}
		}
	}

	nMenuPos = 4;

	if (cldata.myPosition == CLANCHIP)
	{
		for (i = 0; i < CHATING_DISPLAY_MAX; i++)
		{
			if (i == nClanWon_Num) break;
			if (ClanChatList.clanWon[i + nScl_Bar])
			{

				lstrcpy(szClanWon, szChatClanWon[i + nScl_Bar]);

				if ((i + nScl_Bar) == (cN_PressfDBL - 4))
				{
					DrawSprite(ChatList_menuPos[nMenuPos].left, ChatList_menuPos[nMenuPos].top, hChatClanWon, 0, 0, 16, 16, 1);
					Draw_C_Text2(szClanWon, ChatList_menuPos[nMenuPos].left + 35, ChatList_menuPos[nMenuPos].top + 3);
				}
				else if ((i + nScl_Bar) == (cN_Pressf - 4))
				{
					if ((cldata.SubChip[0] != 0) && (lstrcmp(szChatClanWon[i + nScl_Bar], cldata.SubChip) == 0))
						DrawSprite(ChatList_menuPos[nMenuPos].left, ChatList_menuPos[nMenuPos].top, hSubChip, 0, 0, 13, 17, 1);
					else
						DrawSprite(ChatList_menuPos[nMenuPos].left, ChatList_menuPos[nMenuPos].top, hClanWon[0], 0, 0, 13, 17, 1);

					Draw_C_Text3(szClanWon, ChatList_menuPos[nMenuPos].left + 35, ChatList_menuPos[nMenuPos].top + 3);
				}


				else {



					//ºÎÅ¬·£¯…Àº Å¬·£¸¶Å©¸¦ Âï¾îÁØ´Ù.
					if ((cldata.SubChip[0] != 0) && (strcmp(szChatClanWon[i + nScl_Bar], cldata.SubChip) == 0))
					{
						DrawSprite(ChatList_menuPos[nMenuPos].left, ChatList_menuPos[nMenuPos].top, hSubChip, 0, 0, 13, 17, 1);

						Draw_C_Text(szClanWon, ChatList_menuPos[nMenuPos].left + 35, ChatList_menuPos[nMenuPos].top + 3);
					}
					else
					{


						//»ç¶÷¾ó±¼ ½ºÇÁ¶óÀÌÆ®
						DrawSprite(ChatList_menuPos[nMenuPos].left, ChatList_menuPos[nMenuPos].top, hClanWon[0], 0, 0, 13, 17, 1);
						Draw_C_Text(szClanWon, ChatList_menuPos[nMenuPos].left + 35, ChatList_menuPos[nMenuPos].top + 3);


					}

				}

				nMenuPos += 1;
			}
		}
	}

	if ((cldata.myPosition == CLANUSER) || (cldata.myPosition == CLAN_SUBCHIP))
	{
		for (i = 0; i < CHATING_DISPLAY_MAX; i++)
		{
			if (i == nClanWon_Num) break;
			if (szChatClanWon[i + nScl_Bar])
			{
				lstrcpy(szClanWon, szChatClanWon[i + nScl_Bar]);

				if ((i + nScl_Bar) == (cN_PressfDBL - 4))
				{
					DrawSprite(ChatList_menuPos[nMenuPos].left, ChatList_menuPos[nMenuPos].top, hChatClanWon, 0, 0, 16, 16, 1);
					Draw_C_Text2(szClanWon, ChatList_menuPos[nMenuPos].left + 35, ChatList_menuPos[nMenuPos].top + 3);
				}

				else if ((i + nScl_Bar) == (cN_Pressf - 4))
				{
					if (lstrcmp(szChatClanWon[i + nScl_Bar], cldata.ClanZang_Name) == 0)
						DrawSprite(ChatList_menuPos[nMenuPos].left, ChatList_menuPos[nMenuPos].top, cldata.hClanMark16, 0, 0, 16, 16, 1);
					else if ((cldata.SubChip[0] != 0) && (lstrcmp(szChatClanWon[i + nScl_Bar], cldata.SubChip) == 0))
						DrawSprite(ChatList_menuPos[nMenuPos].left, ChatList_menuPos[nMenuPos].top, hSubChip, 0, 0, 13, 17, 1);
					else
						DrawSprite(ChatList_menuPos[nMenuPos].left, ChatList_menuPos[nMenuPos].top, hClanWon[0], 0, 0, 13, 17, 1);

					Draw_C_Text3(szClanWon, ChatList_menuPos[nMenuPos].left + 35, ChatList_menuPos[nMenuPos].top + 3);
				}

				else
				{

					if (lstrcmp(szChatClanWon[i + nScl_Bar], cldata.ClanZang_Name) == 0)
						DrawSprite(ChatList_menuPos[nMenuPos].left, ChatList_menuPos[nMenuPos].top, cldata.hClanMark16, 0, 0, 16, 16, 1);
					else if ((cldata.SubChip[0] != 0) && (lstrcmp(szChatClanWon[i + nScl_Bar], cldata.SubChip) == 0))
						DrawSprite(ChatList_menuPos[nMenuPos].left, ChatList_menuPos[nMenuPos].top, hSubChip, 0, 0, 13, 17, 1);
					else
					{
						DrawSprite(ChatList_menuPos[nMenuPos].left, ChatList_menuPos[nMenuPos].top, hClanWon[0], 0, 0, 13, 17, 1);
						Draw_C_Text3(szClanWon, ChatList_menuPos[nMenuPos].left + 35, ChatList_menuPos[nMenuPos].top + 3);
					}
					Draw_C_Text(szClanWon, ChatList_menuPos[nMenuPos].left + 35, ChatList_menuPos[nMenuPos].top + 3);
				}
				nMenuPos += 1;
			}
		}
	}

	nMenuPos = 12;

	if (nClanWon_Num > CHATING_DISPLAY_MAX)
	{
		DrawSprite(ChatList_menuPos[nMenuPos].left, ChatList_menuPos[nMenuPos].top, hScl_Bar, 0, 0, 8, 160, 1);

		dsDrawTexImage(hScl_icon_tj, scrIconPos.left, scrIconPos.top, 16, 16, 255);
	}

	char buf[256];
	wsprintf(buf, "[%s]", cldata.name);

	Draw_C_Text3(buf, ChatListBoxX + 115, CHATLIST_BOX_Y + 38);
}

void CLANEntity_chatting::InitClanChatList()
{
	OCcnt = 0;
	ChatListBoxX = 800;
	ChatListBoxY = 94;

	cnt = 0;
	AddSize = 0;
}

void CLANEntity_chatting::MoveClose()
{
	ChatList_CmenuN = CLAN_DISPLAY_CLOSE;
}

void CLANEntity_chatting::NoScroll()
{
	OCcnt = 28;
	ChatListBoxX = OpenBuf_x[OCcnt];
	OCcnt += 1;

	bOpenChatList = TRUE;
}

int CLANEntity_chatting::chkMenu(int x, int y, RECT *r)
{
	if (r->left <= x && x <= r->right)
		if (r->top <= y && y <= r->bottom)
			return 1;
	return 0;
}
int CLANEntity_chatting::chkeckMenuN()
{
	int i;

	for (i = 0; i < ChatList_menuSu; i++) {
		if (chkMenu(pCursorPos.x, pCursorPos.y, &ChatList_menuPos[i])) {
			return i;
		}
	}
	return -1;
}

void CLANEntity_chatting::DoubleClick(int i)
{
	if (banisF[(i - 4) + nScl_Bar] == 1)
		banisF[(i - 4) + nScl_Bar] = 2;
	else if (banisF[(i - 4) + nScl_Bar] == 2) banisF[(i - 4) + nScl_Bar] = 0;
	else
	{
		banisF[(i - 4) + nScl_Bar] = 2;
	}
}