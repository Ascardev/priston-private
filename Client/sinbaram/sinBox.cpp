#include "sinLinkHeader.h"
#include "..\\field.h"


#define TELEPORT_PAGE	4
#define SMASHTV_MONEY	300

cSINBOX cSinBox;

sSODELEMENT sSODElement;

sTELEPORTS sTelePorts[TELEPORT_PAGE][10] = 
{
	{{1		,"风之路"		,20	,FieldLimitLevel_Table[20]},{2	,"秋之谷"		,19	,FieldLimitLevel_Table[19]},{3	,"心情树林"		,17	,FieldLimitLevel_Table[17]},{4	,"胶之林"			,0	,FieldLimitLevel_Table[0]	},{5	,"自由庭院"		,2	,FieldLimitLevel_Table[2]	},{6	,"废墟墓地"		,4	,FieldLimitLevel_Table[4]	},{7	,"废墟"			,5	,FieldLimitLevel_Table[5]	},{8	,"遗忘之地"	,7	,FieldLimitLevel_Table[7]	},{9	,"诅咒之地"		,8	,FieldLimitLevel_Table[8]	},{10	,"绿洲"			,10	,FieldLimitLevel_Table[10]	},},
	{{11	,"古代战场"		,11	,FieldLimitLevel_Table[11]},{12	,"封印之地"		,12	,FieldLimitLevel_Table[12]},{13	,"蜂房洞穴"		,25	,FieldLimitLevel_Table[25]},{14	,"蘑菇洞穴"			,24	,FieldLimitLevel_Table[24]	},{15	,"暗黑圣殿"		,26	,FieldLimitLevel_Table[26]	},{16	,"地牢1层"		,13	,FieldLimitLevel_Table[13]	},{17	,"地牢2层"		,14	,FieldLimitLevel_Table[14]	},{18	,"地牢3层"	,15	,FieldLimitLevel_Table[15]	},{19	,"晦气寺庙1层"	,22	,FieldLimitLevel_Table[22]	},{20	,"晦气寺庙2层"	,23	,FieldLimitLevel_Table[23]	},},
	{{21	,"晦气寺庙3层"	,42	,FieldLimitLevel_Table[42]},{22	,"贪婪之湖"		,34	,FieldLimitLevel_Table[34]},{23	,"末日都市"		,27	,FieldLimitLevel_Table[27]},{24	,"普龙心脏"			,28	,FieldLimitLevel_Table[28]	},{25	,"凯拉笔山谷"	,31	,FieldLimitLevel_Table[31]	},{26	,"冰风谷"		,35	,FieldLimitLevel_Table[35]	},{27	,"凯尔维苏洞穴"	,36	,FieldLimitLevel_Table[36]	},{28	,"迷失之地"	,37	,FieldLimitLevel_Table[37]	},{29	,"迷失寺庙"		,38	,FieldLimitLevel_Table[38]	},{30	,"无尽之塔1层"	,40	,FieldLimitLevel_Table[40]	},},
	{{31	,"无尽之塔2层"	,41	,FieldLimitLevel_Table[41]},{32	,"无尽之塔3层"	,43	,FieldLimitLevel_Table[43]},{33	,"凯拉笔洞穴"	,44	,FieldLimitLevel_Table[44]},{34	,"内维斯克洞穴"		,45	,FieldLimitLevel_Table[45]	},{35	,"古代寺庙"		,46	,FieldLimitLevel_Table[46]	},{0	,												},{0	,												},{0	,											},{0	,												},{0	,												},},
};

cSINBOX::cSINBOX()
{

}
cSINBOX::~cSINBOX()
{

}
void cSINBOX::Init()
{
	Load();
	OpenFlag	= FALSE;
	CloseFlag	= FALSE;
	EnterFlag	= FALSE;
	PageFlag[0]	= FALSE;
	PageFlag[1]	= FALSE;
	Kind		= 0;
	x			= 0;
	y			= 0;
	Page		= 0;
}
void cSINBOX::Load()
{
	lpBoxClose[0]		= LoadDibSurfaceOffscreen("Image\\Sinimage\\help\\buttons\\close.png");
	lpBoxClose[1]		= LoadDibSurfaceOffscreen("Image\\Sinimage\\help\\buttons\\close_.png");
	lpBoxEnter[0]		= LoadDibSurfaceOffscreen("Image\\Sinimage\\help\\buttons\\enter.png");
	lpBoxEnter[1]		= LoadDibSurfaceOffscreen("Image\\Sinimage\\help\\buttons\\enter_.png");
	lpBoxTelePort[0]	= LoadDibSurfaceOffscreen("Image\\Sinimage\\help\\buttons\\teleport.png");
	lpBoxTelePort[1]	= LoadDibSurfaceOffscreen("Image\\Sinimage\\help\\buttons\\teleport_.png");
	lpBoxButtonHelp[0]	= LoadDibSurfaceOffscreen("Image\\Sinimage\\help\\misc\\button_help.tga");
	lpBoxButtonHelp[1]	= LoadDibSurfaceOffscreen("Image\\Sinimage\\help\\misc\\button_help_.tga");
	lpBoxTransLogo		= LoadDibSurfaceOffscreen("Image\\Sinimage\\help\\misc\\compass.png");
	lpBoxSodLogo		= LoadDibSurfaceOffscreen("Image\\Sinimage\\help\\misc\\logo.png");
	lpBoxElement[0]		= LoadDibSurfaceOffscreen("Image\\Sinimage\\help\\misc\\fire.png");
	lpBoxElement[1]		= LoadDibSurfaceOffscreen("Image\\Sinimage\\help\\misc\\wind.png");
	lpBoxElement[2]		= LoadDibSurfaceOffscreen("Image\\Sinimage\\help\\misc\\water.png");
	lpBoxElement[3]		= LoadDibSurfaceOffscreen("Image\\Sinimage\\help\\misc\\earth.png");
	lpBoxScrollbar[0]	= LoadDibSurfaceOffscreen("Image\\Sinimage\\help\\misc\\scrollbar.tga");
	lpBoxScrollbar[1]	= LoadDibSurfaceOffscreen("Image\\Sinimage\\help\\misc\\scrollber.tga");
	lpBoxTitle[0]		= LoadDibSurfaceOffscreen("Image\\Sinimage\\help\\title\\quest.png");
	lpBoxTitle[1]		= LoadDibSurfaceOffscreen("Image\\Sinimage\\help\\title\\teleport.png");
	lpBoxTitleSub[0]	= LoadDibSurfaceOffscreen("Image\\Sinimage\\help\\undertitle\\field.png");
	lpBoxTitleSub[1]	= LoadDibSurfaceOffscreen("Image\\Sinimage\\help\\undertitle\\quest.png");
	lpBoxCheckBox[0]	= LoadDibSurfaceOffscreen("Image\\Sinimage\\help\\misc\\checkbox.tga");
	lpBoxCheckBox[1]	= LoadDibSurfaceOffscreen("Image\\Sinimage\\help\\misc\\checkbox_.tga");
	lpBoxLeftArrow[0]	= LoadDibSurfaceOffscreen("Image\\Sinimage\\help\\misc\\LeftArrow_.bmp");
	lpBoxLeftArrow[1]	= LoadDibSurfaceOffscreen("Image\\Sinimage\\help\\misc\\LeftArrow.bmp");
	lpBoxRightArrow[0]	= LoadDibSurfaceOffscreen("Image\\Sinimage\\help\\misc\\RightArrow_.bmp");
	lpBoxRightArrow[1]	= LoadDibSurfaceOffscreen("Image\\Sinimage\\help\\misc\\RightArrow.bmp");
	lpBoxWindow[0]		= LoadDibSurfaceOffscreen("Image\\Sinimage\\help\\window.png");
	lpBoxWindow[1]		= LoadDibSurfaceOffscreen("Image\\Sinimage\\help\\window2.png");
	lpBoxSodBar			= LoadDibSurfaceOffscreen("Image\\Sinimage\\help\\sodbar.png");
	lpBoxLine			= LoadDibSurfaceOffscreen("Image\\Sinimage\\help\\misc\\Line.tga");
}
void cSINBOX::Release()
{
	for (int i = 0; i < 2; i ++)
	{
		SAFE_RELEASE(lpBoxClose[i]);
		SAFE_RELEASE(lpBoxEnter[i]);
		SAFE_RELEASE(lpBoxTelePort[i]);
		SAFE_RELEASE(lpBoxButtonHelp[i]);
		SAFE_RELEASE(lpBoxScrollbar[i]);
		SAFE_RELEASE(lpBoxCheckBox[i]);
		SAFE_RELEASE(lpBoxLeftArrow[i]);
		SAFE_RELEASE(lpBoxRightArrow[i]);
	}
	for (int i = 0; i < 4; i ++)
		SAFE_RELEASE(lpBoxElement[i]);

	SAFE_RELEASE(lpBoxTitle[0]);
	SAFE_RELEASE(lpBoxTitle[1]);
	SAFE_RELEASE(lpBoxTitleSub[0]);
	SAFE_RELEASE(lpBoxTitleSub[1]);
	SAFE_RELEASE(lpBoxWindow[0]);
	SAFE_RELEASE(lpBoxWindow[1]);
	SAFE_RELEASE(lpBoxTransLogo);
	SAFE_RELEASE(lpBoxSodLogo);
	SAFE_RELEASE(lpBoxSodBar);
	SAFE_RELEASE(lpBoxLine);
}
void cSINBOX::Main()
{
	if (OpenFlag)
	{
		switch(Kind)
		{
		case HAQUEST_CODE_ELEMENTARY_A:
		case HAQUEST_CODE_ELEMENTARY_B:
		case HAQUEST_CODE_ELEMENTARY_C:
		case HAQUEST_CODE_ELEMENTARY_D:
		case HAQUEST_CODE_ELEMENTARY_E:

			if ((Kind == HAQUEST_CODE_ELEMENTARY_A && chaQuest.sHaQuestElementary[Quest_A].State == 0) || 
				(Kind == HAQUEST_CODE_ELEMENTARY_B && chaQuest.sHaQuestElementary[Quest_B].State == 0) || 
				(Kind == HAQUEST_CODE_ELEMENTARY_C && chaQuest.sHaQuestElementary[Quest_C].State == 0) || 
				(Kind == HAQUEST_CODE_ELEMENTARY_D && chaQuest.sHaQuestElementary[Quest_D].State == 0) ||
				(Kind == HAQUEST_CODE_ELEMENTARY_E))
			{
				if (pCursorPos.x > x + 180 && pCursorPos.y > y + 328 && pCursorPos.x < x + 180 + 100 && pCursorPos.y < y + 328 + 21)
				{
					if (CloseFlag == FALSE)
						CloseFlag = TRUE;
				}
				else if (pCursorPos.x > x + 70 && pCursorPos.y > y + 328 && pCursorPos.x < x + 70 + 100 && pCursorPos.y < y + 328 + 21)
				{
					if (EnterFlag == FALSE)
						EnterFlag = TRUE;
				}
				else
				{
					if (CloseFlag == TRUE)
						CloseFlag = FALSE;
					if (EnterFlag == TRUE)
						EnterFlag = FALSE;
				}
			}
			else
			{
				if (pCursorPos.x > x + 125 && pCursorPos.y > y + 328 && pCursorPos.x < x + 125 + 100 && pCursorPos.y < y + 328 + 21)
				{
					if (EnterFlag == FALSE)
						EnterFlag = TRUE;
				}
				else
				{
					if (EnterFlag == TRUE)
						EnterFlag = FALSE;
				}
			}
			break;
		case SIN_HELP_KIND_TELEPORT_SCROLL:
			if (pCursorPos.x > x + 180 && pCursorPos.y > y + 328 && pCursorPos.x < x + 180 + 100 && pCursorPos.y < y + 328 + 21)
			{
				if (CloseFlag == FALSE)
					CloseFlag = TRUE;
			}
			else if (pCursorPos.x > x + 70 && pCursorPos.y > y + 328 && pCursorPos.x < x + 70 + 100 && pCursorPos.y < y + 328 + 21)
			{
				if (EnterFlag == FALSE)
					EnterFlag = TRUE;
			}
			else if (pCursorPos.x > x + 45 && pCursorPos.y > y + 328 && pCursorPos.x < x + 45 + 20 && pCursorPos.y < y + 328 + 20)
			{
				if (PageFlag[0] == FALSE)
					PageFlag[0] = TRUE;
			}
			else if (pCursorPos.x > x + 290 && pCursorPos.y > y + 328 && pCursorPos.x < x + 290 + 20 && pCursorPos.y < y + 328 + 20)
			{
				if (PageFlag[1] == FALSE)
					PageFlag[1] = TRUE;
			}
			else
			{
				if (CloseFlag == TRUE)
					CloseFlag = FALSE;
				if (EnterFlag == TRUE)
					EnterFlag = FALSE;
				if (PageFlag[0] = TRUE)
					PageFlag[0] = FALSE;
				if (PageFlag[1] == TRUE)
					PageFlag[1] = FALSE;
			}
			for (int i = 0; i < 10; i ++)
			{
				if (pCursorPos.x > x + 30 && pCursorPos.y > y + 90 + i * 20 && pCursorPos.x < x + 30 + 290 && pCursorPos.y < y + 90 + i * 20 + 20)
				{
					if (sTelePorts[Page][i].PNo)
					{
						if (sTelePorts[Page][i].MoveFlag == FALSE)
							sTelePorts[Page][i].MoveFlag = TRUE;
					}
				}
				else
				{
					if (sTelePorts[Page][i].PNo)
					{
						if (sTelePorts[Page][i].MoveFlag == TRUE)
							sTelePorts[Page][i].MoveFlag = FALSE;
					}
				}
			}
			break;
		case SIN_EVENT_SMASHTV:
			if (pCursorPos.x > x + 180 && pCursorPos.y > y + 328 && pCursorPos.x < x + 180 + 100 && pCursorPos.y < y + 328 + 21)
			{
				if (CloseFlag == FALSE)
					CloseFlag = TRUE;
			}
			else if (pCursorPos.x > x + 70 && pCursorPos.y > y + 328 && pCursorPos.x < x + 70 + 100 && pCursorPos.y < y + 328 + 21)
			{
				if (EnterFlag == FALSE)
					EnterFlag = TRUE;
			}
			else
			{
				if (CloseFlag == TRUE)
					CloseFlag = FALSE;
				if (EnterFlag == TRUE)
					EnterFlag = FALSE;
			}
			break;
		}
	}
}
void cSINBOX::Draw()
{
	if (OpenFlag)
	{
		switch(Kind)
		{
		case HAQUEST_CODE_ELEMENTARY_A:
		case HAQUEST_CODE_ELEMENTARY_B:
		case HAQUEST_CODE_ELEMENTARY_C:
		case HAQUEST_CODE_ELEMENTARY_D:
		case HAQUEST_CODE_ELEMENTARY_E:
			DrawSprite(x		,y		,lpBoxWindow[1]		,0,0,350,360);	//BOX框子
			DrawSprite(x + 75	,y + 10	,lpBoxTitle[0]		,0,0,200,40);	//标题头
			DrawSprite(x + 5	,y + 40	,lpBoxLine			,0,0,340,16);	//横线

			if ((Kind == HAQUEST_CODE_ELEMENTARY_A && chaQuest.sHaQuestElementary[Quest_A].State == 0) || 
				(Kind == HAQUEST_CODE_ELEMENTARY_B && chaQuest.sHaQuestElementary[Quest_B].State == 0) || 
				(Kind == HAQUEST_CODE_ELEMENTARY_C && chaQuest.sHaQuestElementary[Quest_C].State == 0) || 
				(Kind == HAQUEST_CODE_ELEMENTARY_D && chaQuest.sHaQuestElementary[Quest_D].State == 0) ||
				(Kind == HAQUEST_CODE_ELEMENTARY_E))
			{
				if (EnterFlag == TRUE)
					DrawSprite(x + 70	,y + 328,lpBoxEnter[1]		,0,0,100,21);	//传送
				else
					DrawSprite(x + 70	,y + 328,lpBoxEnter[0]		,0,0,100,21);	//传送

				if (CloseFlag == TRUE)
					DrawSprite(x + 180	,y + 328,lpBoxClose[1]		,0,0,100,21);	//关闭
				else
					DrawSprite(x + 180	,y + 328,lpBoxClose[0]		,0,0,100,21);	//关闭
			}
			else
			{
				if (EnterFlag == TRUE)
					DrawSprite(x + 125	,y + 328,lpBoxEnter[1]		,0,0,100,21);	//传送
				else
					DrawSprite(x + 125	,y + 328,lpBoxEnter[0]		,0,0,100,21);	//传送
			}
			break;
		case SIN_HELP_KIND_TELEPORT_SCROLL:
			DrawSprite(x		,y		,lpBoxWindow[0]		,0,0,350,360);	//BOX框子
			DrawSprite(x + 75	,y + 10	,lpBoxTitle[1]		,0,0,200,40);	//标题头
			DrawSprite(x + 270	,y + 10	,lpBoxTransLogo		,0,0,65	,64);	//LOG
			DrawSprite(x + 100	,y + 55	,lpBoxTitleSub[0]	,0,0,150,20);	//小标题

			for (int i = 0; i < 10; i ++)
			{
				if (sTelePorts[Page][i].PNo)
				{
					if (sTelePorts[Page][i].Flag)
						DrawSprite(x + 280	,y + 90 + i * 20,lpBoxCheckBox[1]		,0,0,14,14);	//传送
					else
						DrawSprite(x + 280	,y + 90 + i * 20,lpBoxCheckBox[0]		,0,0,14,14);	//传送
				}
			}
			if (PageFlag[0] == TRUE)
				DrawSprite(x + 45	,y + 328,lpBoxLeftArrow[1]		,0,0,20,20);	//左边按钮
			else
				DrawSprite(x + 45	,y + 328,lpBoxLeftArrow[0]		,0,0,20,20);	//左边按钮

			if (PageFlag[1] == TRUE)
				DrawSprite(x + 290	,y + 328,lpBoxRightArrow[1]		,0,0,20,20);	//右边按钮
			else
				DrawSprite(x + 290	,y + 328,lpBoxRightArrow[0]		,0,0,20,20);	//右边按钮

			if (EnterFlag == TRUE)
				DrawSprite(x + 70	,y + 328,lpBoxTelePort[1]		,0,0,100,21);	//传送
			else
				DrawSprite(x + 70	,y + 328,lpBoxTelePort[0]		,0,0,100,21);	//传送

			if (CloseFlag == TRUE)
				DrawSprite(x + 180	,y + 328,lpBoxClose[1]		,0,0,100,21);	//关闭
			else
				DrawSprite(x + 180	,y + 328,lpBoxClose[0]		,0,0,100,21);	//关闭
			break;
		case SIN_EVENT_SMASHTV:
			DrawSprite(x		,y		,lpBoxWindow[1]		,0,0,350,360);	//BOX框子
			DrawSprite(x + 43	,y + 10	,lpBoxSodLogo		,0,0,264,110);	//标题头
			DrawSprite(x + 25	,y + 130,lpBoxSodBar		,0,0,300,20);	//标题头
			DrawSprite(x + 300	,y + 10	,lpBoxButtonHelp[0]	,0,0,32	,32);	//帮助
			DrawSprite(x + 80	,y + 130,lpBoxElement[sSODElement.Element]	,0,0,20	,20);	//属性

			if (EnterFlag == TRUE)
				DrawSprite(x + 70	,y + 328,lpBoxEnter[1]		,0,0,100,21);	//传送
			else
				DrawSprite(x + 70	,y + 328,lpBoxEnter[0]		,0,0,100,21);	//传送

			if (CloseFlag == TRUE)
				DrawSprite(x + 180	,y + 328,lpBoxClose[1]		,0,0,100,21);	//关闭
			else
				DrawSprite(x + 180	,y + 328,lpBoxClose[0]		,0,0,100,21);	//关闭
			break;
		}
	}
}
void cSINBOX::DrawText()
{
	char StrBuf[128];

	DWORD Color = D3DCOLOR_XRGB(255,255,255);

	if (OpenFlag)
	{
		switch(Kind)
		{
		case HAQUEST_CODE_ELEMENTARY_A:
		case HAQUEST_CODE_ELEMENTARY_B:
		case HAQUEST_CODE_ELEMENTARY_C:
		case HAQUEST_CODE_ELEMENTARY_D:
		case HAQUEST_CODE_ELEMENTARY_E:
			for (int i = 0; i < 80; i ++)
				dsTextLineOut(cDXGraphic.lpD3DFont,x +  25	,y + 60 + i * 20,szBuff[i],lstrlen(szBuff[i]),Color);
			break;
		case SIN_HELP_KIND_TELEPORT_SCROLL:
			for (int i = 0; i < 10; i ++)
			{
				if (sTelePorts[Page][i].PNo)
				{
					wsprintf(StrBuf,"%02d:",sTelePorts[Page][i].PNo);

					if (sTelePorts[Page][i].Flag || sTelePorts[Page][i].MoveFlag)
						dsTextLineOut(cDXGraphic.lpD3DFont,x +  35	,y + 90 + i * 20,StrBuf,lstrlen(StrBuf),D3DCOLOR_XRGB(218,165,32));
					else
						dsTextLineOut(cDXGraphic.lpD3DFont,x +  35	,y + 90 + i * 20,StrBuf,lstrlen(StrBuf),Color);
					wsprintf(StrBuf,"%s",sTelePorts[Page][i].szFileName);
					if (sTelePorts[Page][i].Flag || sTelePorts[Page][i].MoveFlag)
						dsTextLineOut(cDXGraphic.lpD3DFont,x +  125	,y + 90 + i * 20,StrBuf,lstrlen(StrBuf),D3DCOLOR_XRGB(218,165,32));
					else
						dsTextLineOut(cDXGraphic.lpD3DFont,x +  125	,y + 90 + i * 20,StrBuf,lstrlen(StrBuf),Color);
				}
			}
			break;
		case SIN_EVENT_SMASHTV:
			wsprintf(StrBuf,"房间:");
			dsTextLineOut(cDXGraphic.lpD3DFont,x +  50	,y + 135,StrBuf,lstrlen(StrBuf),Color);

			switch(sSODElement.Element)
			{
			case 1:
				Color = D3DCOLOR_XRGB(0,162,113);
				wsprintf(StrBuf,"风");
				break;
			case 2:
				Color = D3DCOLOR_XRGB(0,35,255);
				wsprintf(StrBuf,"水");
				break;
			case 3:
				Color = D3DCOLOR_XRGB(197,137,0);
				wsprintf(StrBuf,"地");
				break;
			default:
				Color = D3DCOLOR_XRGB(255,0,0);
				wsprintf(StrBuf,"火");
				break;
			}
			dsTextLineOut(cDXGraphic.lpD3DFont,x +  105	,y + 135,StrBuf,lstrlen(StrBuf),Color);
			wsprintf(StrBuf,"#房间人数: %d",sSODElement.Count);
			Color = D3DCOLOR_XRGB(255,255,255);
			dsTextLineOut(cDXGraphic.lpD3DFont,x +  155	,y + 135,StrBuf,lstrlen(StrBuf),Color);

			for (int i = 0; i < 80; i ++)
				dsTextLineOut(cDXGraphic.lpD3DFont,x +  25	,y + 160 + i * 20,szBuff[i],lstrlen(szBuff[i]),Color);

			wsprintf(StrBuf,"%d × 角色等级 + TEX = %d 金",SMASHTV_MONEY,SMASHTV_MONEY * sinChar->Level);

			dsTextLineOut(cDXGraphic.lpD3DFont,x +  25	,y + 300,StrBuf,lstrlen(StrBuf),D3DCOLOR_XRGB(148,200,178));
			break;
		}
	}
}
void cSINBOX::LButtonDown(int px,int py)
{
	if (OpenFlag)
	{
		switch(Kind)
		{
		case HAQUEST_CODE_ELEMENTARY_A:
			if (CloseFlag == TRUE)
			{
				CloseFlag	= FALSE;
				Kind		= 0;
				OpenFlag	= FALSE;
				return;
			}
			if (EnterFlag == TRUE)
			{
				EnterFlag	= FALSE;
				Kind		= 0;
				OpenFlag	= FALSE;

				switch(chaQuest.sHaQuestElementary[Quest_A].State)
				{
				case 0:
					chaQuest.sHaQuestElementary[Quest_A].CODE  = HAQUEST_CODE_ELEMENTARY_A;
					chaQuest.sHaQuestElementary[Quest_A].State = 1;
					chaQuest.haSetQuestTimer();
					if(cInvenTory.SearchItemCode(sinQT1|sin14) == FALSE)
						SendQuestCommandToServer(HAQUEST_CODE_ELEMENTARY_A,1,0,0);
					SaveGameData();
					break;
				case 2:
					SendQuestCommandToServer(HAQUEST_CODE_ELEMENTARY_A,2,0,0);
					haElementaryQuestLog |= QUESTBIT_ELEMENTARY_A;
					chaQuest.sHaQuestElementary[Quest_A].State	= 3;
					chaQuest.sHaQuestElementary[Quest_A].CODE	= 0;
					cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
					SaveGameData();
					break;
				}
			}
			break;
		case HAQUEST_CODE_ELEMENTARY_B:
			if (CloseFlag == TRUE)
			{
				CloseFlag	= FALSE;
				Kind		= 0;
				OpenFlag	= FALSE;
				return;
			}
			if (EnterFlag == TRUE)
			{
				EnterFlag	= FALSE;
				Kind		= 0;
				OpenFlag	= FALSE;

				switch(chaQuest.sHaQuestElementary[Quest_B].State)
				{
				case 0:
					chaQuest.sHaQuestElementary[Quest_B].CODE  = HAQUEST_CODE_ELEMENTARY_B;
					chaQuest.sHaQuestElementary[Quest_B].State = 1;
					if (GetRace(sinChar->JOB_CODE) == BROOD_CODE_TEMPSKRON)
					{
						chaQuest.sHaQuestElementary[Quest_B].Kind = MONSTER_HOBGOBLIN;
						lstrcpy(chaQuest.szQuestMonsterName,"魔兽兵");
					}
					else
					{
						chaQuest.sHaQuestElementary[Quest_B].Kind = MONSTER_NORTHGOBLIN;
						lstrcpy(chaQuest.szQuestMonsterName,"巨魔兽");
					}
					chaQuest.haSetQuestTimer();
					SaveGameData();
					break;
				case 2:
					if(cInvenTory.SearchItemCode(sinQT1|sin16))
					{
						DeleteQuestItem(sinQT1|sin16);
						SendQuestCommandToServer(HAQUEST_CODE_ELEMENTARY_B,2,0,0);
						haElementaryQuestLog |= QUESTBIT_ELEMENTARY_B;
						chaQuest.sHaQuestElementary[Quest_B].State	= 3;
						chaQuest.sHaQuestElementary[Quest_B].CODE	= 0;
						cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
						SaveGameData();
					}
					break;
				}
			}
			break;
		case HAQUEST_CODE_ELEMENTARY_C:
			if (CloseFlag == TRUE)
			{
				CloseFlag	= FALSE;
				Kind		= 0;
				OpenFlag	= FALSE;
				return;
			}
			if (EnterFlag == TRUE)
			{
				EnterFlag	= FALSE;
				Kind		= 0;
				OpenFlag	= FALSE;

				switch(chaQuest.sHaQuestElementary[Quest_C].State)
				{
				case 0:
					chaQuest.sHaQuestElementary[Quest_C].CODE	= HAQUEST_CODE_ELEMENTARY_C;
					chaQuest.sHaQuestElementary[Quest_C].State	= 1;
					chaQuest.sHaQuestElementary[Quest_C].Kind	= MONSTER_ZOBI;
					lstrcpy(chaQuest.szQuestMonsterName,"僵尸");
					chaQuest.sHaQuestElementary[Quest_C].Monster[0] = 0;
					chaQuest.sHaQuestElementary[Quest_C].Monster[1] = 10;
					chaQuest.haSetQuestTimer();
					SaveGameData();
					break;
				case 2:
					SendQuestCommandToServer(HAQUEST_CODE_ELEMENTARY_C,2,0,0);
					haElementaryQuestLog |= QUESTBIT_ELEMENTARY_C;
					chaQuest.sHaQuestElementary[Quest_C].State	= 3;
					chaQuest.sHaQuestElementary[Quest_C].CODE	= 0;
					cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
					SaveGameData();
					break;
				}
			}
			break;
		case HAQUEST_CODE_ELEMENTARY_D:
			if (CloseFlag == TRUE)
			{
				CloseFlag	= FALSE;
				Kind		= 0;
				OpenFlag	= FALSE;
				return;
			}
			if (EnterFlag == TRUE)
			{
				EnterFlag	= FALSE;
				Kind		= 0;
				OpenFlag	= FALSE;

				switch(chaQuest.sHaQuestElementary[Quest_D].State)
				{
				case 0:
					SendQuestCommandToServer(HAQUEST_CODE_ELEMENTARY_D,1,0,0);
					haElementaryQuestLog |= QUESTBIT_ELEMENTARY_D;
					chaQuest.sHaQuestElementary[Quest_D].State	= 1;
					chaQuest.sHaQuestElementary[Quest_D].CODE	= 0;
					SaveGameData();
					break;
				}
			}
			break;
		case HAQUEST_CODE_ELEMENTARY_E:
			if (CloseFlag == TRUE)
			{
				CloseFlag	= FALSE;
				Kind		= 0;
				OpenFlag	= FALSE;
				return;
			}
			if (EnterFlag == TRUE)
			{
				EnterFlag	= FALSE;
				Kind		= 0;
				OpenFlag	= FALSE;

				switch(chaQuest.sHaQuestElementary[Quest_E].State)
				{
				case 0:
					if(cInvenTory.SearchItemCode(sinQT1|sin15) == FALSE)
						SendQuestCommandToServer(HAQUEST_CODE_ELEMENTARY_E,1,0,0);
					chaQuest.sHaQuestElementary[Quest_E].CODE	= HAQUEST_CODE_ELEMENTARY_E;
					chaQuest.sHaQuestElementary[Quest_E].State	= 1;
					chaQuest.haSetQuestTimer(180);
					break;
				case 1:
					if (cSkill.SearchContiueSkill(CHANGE_ELEMENTARY_QUEST))
					{
						SendQuestCommandToServer(HAQUEST_CODE_ELEMENTARY_E,2,0,0);
						chaQuest.sHaQuestElementary[Quest_E].CODE	= 0;
						chaQuest.sHaQuestElementary[Quest_E].State	= 2;
						haElementaryQuestLog |= QUESTBIT_ELEMENTARY_E;
						cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
						SaveGameData();
					}
					break;
				}
			}
			break;
		case SIN_HELP_KIND_TELEPORT_SCROLL:
			if (CloseFlag == TRUE)
			{
				CloseFlag	= FALSE;
				Kind		= 0;
				OpenFlag	= FALSE;
				return;
			}
			if (PageFlag[0] == TRUE)
			{
				if (Page > 0)
					Page --;
				return;
			}
			if (PageFlag[1] == TRUE)
			{
				if (Page < TELEPORT_PAGE - 1)
					Page ++;
				return;
			}
			if (EnterFlag == TRUE)
			{
				int isSelect = FALSE;
				for (int i = 0; i < TELEPORT_PAGE; i ++)
				{
					for (int j = 0; j < 10; j ++)
					{
						if (sTelePorts[i][j].PNo && sTelePorts[i][j].Flag)
						{
							//传送
							isSelect = TRUE;
							/*if (chaPremiumitem.UserTeleportItem(sTelePorts[i][j].FileCode,sTelePorts[i][j].FileLevel))
							{
								EnterFlag	= FALSE;
								Kind		= 0;
								OpenFlag	= FALSE;
								return;
							}*/
						}
					}
				}

				if (isSelect == FALSE)
					cMessageBox.ShowMessageEvent("请选择一个需要传送的地图    ");

				return;
			}
			for (int i = 0; i < 10; i ++)
			{
				if (sTelePorts[Page][i].PNo)
				{
					if (px > x + 30 && py > y + 90 + i * 20 && px < x + 30 + 290 && py < y + 90 + i * 20 + 20)
					{
						sTelePorts[Page][i].Flag ^= TRUE;

						for (int j = 0; j < TELEPORT_PAGE; j ++)
						{
							for (int k = 0; k < 10; k ++)
							{
								if (j == Page)
								{
									if (i != k)
									{
										if (sTelePorts[j][k].PNo)
											sTelePorts[j][k].Flag = FALSE;
									}
								}
								else
								{
									if (sTelePorts[j][k].PNo)
										sTelePorts[j][k].Flag = FALSE;
								}
							}
						}
						break;
					}
				}
			}
			break;
		case SIN_EVENT_SMASHTV:
			if (CloseFlag == TRUE)
			{
				CloseFlag	= FALSE;
				Kind		= 0;
				OpenFlag	= FALSE;
				return;
			}
			if (EnterFlag == TRUE)
			{
				EnterFlag	= FALSE;
				Kind		= 0;
				OpenFlag	= FALSE;
				if(sinChar->Money < (sinChar->Level * SMASHTV_MONEY))
				{
					cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
					return;
				}
				CheckCharForm();
				sinMinusMoney((sinChar->Level * SMASHTV_MONEY));
				ReformCharForm();
				SendCollectMoney(sinChar->Level * SMASHTV_MONEY);
				sinPlaySound(SIN_SOUND_COIN);
				return;
			}
			break;
		}
	}
}
void cSINBOX::LButtonUp(int px,int py)
{

}
void cSINBOX::RButtonDown(int px,int py)
{

}
void cSINBOX::RButtonUp(int px,int py)
{

}
void cSINBOX::KeyDown()
{

}
int cSINBOX::sinShow(int kind,int px,int py,char *FileName)
{
	if (OpenFlag == FALSE)
	{
		switch(kind)
		{
		case SIN_HELP_KIND_TELEPORT_SCROLL:
			OpenFlag	= TRUE;
			Kind		= kind;
			x			= px;
			y			= py;
			Page		= 0;

			for (int i = 0; i < TELEPORT_PAGE; i ++)
			{
				for (int j = 0; j < 10; j ++)
				{
					if (sTelePorts[i][j].PNo)
					{
						if (sTelePorts[i][j].Flag)
							sTelePorts[i][j].Flag = FALSE;
					}
				}
			}
			return TRUE;
		case SIN_EVENT_SMASHTV:
		case HAQUEST_CODE_ELEMENTARY_A:
		case HAQUEST_CODE_ELEMENTARY_B:
		case HAQUEST_CODE_ELEMENTARY_C:
		case HAQUEST_CODE_ELEMENTARY_D:
			if (FileName == NULL)
				return FALSE;
			OpenFlag	= TRUE;
			Kind		= kind;
			x			= px;
			y			= py;

			ReadFileData(FileName);
			ZeroMemory(szBuff,sizeof(szBuff));

			ReadFileDataDivide(&szBuff[0][0]);
			return TRUE;
		}
	}
	return FALSE;
}
int cSINBOX::ReadFileData(char *FileName)
{
	HANDLE hFile;
	hFile = CreateFile(FileName,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING , FILE_ATTRIBUTE_NORMAL,NULL);

	ZeroMemory((void*)szFileReadBuf,sizeof(szFileReadBuf));

	if(hFile != INVALID_HANDLE_VALUE)
	{
		DWORD rbyte;

		ReadFile(hFile,(LPVOID)szFileReadBuf,sizeof(szFileReadBuf),&rbyte,NULL);

		CloseHandle(hFile);
		return TRUE;
	}
	return FALSE;
}
int cSINBOX::ReadFileDataDivide(char *szBuf)
{
	char c;
	int cnt = 0;
	int bufC = 0;

	for(int i=0; ; i++)
	{
		while(TRUE)
		{
			c = szFileReadBuf[cnt++];

			if(c == 0)
				break;
			if(c == '\n')
				break;

			szBuf[i*128 + bufC] = c;

			bufC ++;
		}
		bufC = 0;

		if (c == 0)
			break;
	}

	return TRUE;
}
void cSINBOX::Close()
{
	Release();
}