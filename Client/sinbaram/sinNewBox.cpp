#include "sinLinkHeader.h"
#include "..\\field.h"


cSINNEWBOX cSinNewBox;


sNEWTELEPORTS sTelePorts[MAX_TELEPORT_FIELD] = 
{
	{1,		FieldLimitName[20],	20,	FieldLimitLevel_Table[20],	"Field\\Mini\\forever-fall-01.png"	},
	{2,		FieldLimitName[19],	19,	FieldLimitLevel_Table[19],	"Field\\Mini\\forever-fall-02.png"	},
	{3,		FieldLimitName[18],	18,	FieldLimitLevel_Table[18],	"Field\\Mini\\forever-fall-03.png"	},
	{4,		FieldLimitName[0],	0,	FieldLimitLevel_Table[0],	"Field\\Mini\\fore-3.png"			},
	{5,		FieldLimitName[2],	2,	FieldLimitLevel_Table[2],	"Field\\Mini\\fore-1.png"			},
	{6,		FieldLimitName[4],	4,	FieldLimitLevel_Table[4],	"Field\\Mini\\ruin-4.png"			},
	{7,		FieldLimitName[5],	5,	FieldLimitLevel_Table[5],	"Field\\Mini\\ruin-3.png"			},
	{8,		FieldLimitName[7],	7,	FieldLimitLevel_Table[7],	"Field\\Mini\\ruin-1.png"			},
	{9,		FieldLimitName[8],	8,	FieldLimitLevel_Table[8],	"Field\\Mini\\De-1.png"				},
	{10,	FieldLimitName[10],	10,	FieldLimitLevel_Table[10],	"Field\\Mini\\De-2.png"				},
	{11,	FieldLimitName[11],	11,	FieldLimitLevel_Table[11],	"Field\\Mini\\De-3.png"				},
	{12,	FieldLimitName[12],	12,	FieldLimitLevel_Table[12],	"Field\\Mini\\De-4.png"				},
	{13,	FieldLimitName[25],	25,	FieldLimitLevel_Table[25],	"Field\\Mini\\Mcave.png"			},
	{14,	FieldLimitName[24],	24,	FieldLimitLevel_Table[24],	"Field\\Mini\\Tcave.png"			},
	{15,	FieldLimitName[26],	26,	FieldLimitLevel_Table[26],	"Field\\Mini\\Dcave.png"			},
	{16,	FieldLimitName[13],	13,	FieldLimitLevel_Table[13],	"Field\\Mini\\dun-1.png"			},
	{17,	FieldLimitName[14],	14,	FieldLimitLevel_Table[14],	"Field\\Mini\\dun-2.png"			},
	{18,	FieldLimitName[15],	15,	FieldLimitLevel_Table[15],	"Field\\Mini\\dun-3.png"			},
	{19,	FieldLimitName[22],	22,	FieldLimitLevel_Table[22],	"Field\\Mini\\dun-4.png"			},
	{20,	FieldLimitName[23],	23,	FieldLimitLevel_Table[23],	"Field\\Mini\\dun-5.png"			},
	{21,	FieldLimitName[43],	23,	FieldLimitLevel_Table[43],	"Field\\Mini\\dun-9.png"			},
	{22,	FieldLimitName[34],	34,	FieldLimitLevel_Table[34],	"Field\\Mini\\Greedy.png"			},
	{23,	FieldLimitName[27],	27,	FieldLimitLevel_Table[27],	"Field\\Mini\\iron-1.png"			},
	{24,	FieldLimitName[28],	28,	FieldLimitLevel_Table[28],	"Field\\Mini\\iron-2.png"			},
	{25,	FieldLimitName[31],	31,	FieldLimitLevel_Table[31],	"Field\\Mini\\ice1.png"				},
	{26,	FieldLimitName[35],	35,	FieldLimitLevel_Table[35],	"Field\\Mini\\ice2.png"				},
	{27,	FieldLimitName[36],	36,	FieldLimitLevel_Table[36],	"Field\\Mini\\Boss.png"				},
	{28,	FieldLimitName[37],	37,	FieldLimitLevel_Table[37],	"Field\\Mini\\lost.png"				},
	{29,	FieldLimitName[38],	38,	FieldLimitLevel_Table[38],	"Field\\Mini\\Losttemple.png"		},
	{30,	FieldLimitName[40],	40,	FieldLimitLevel_Table[40],	"Field\\Mini\\dun-7.png"			},
	{31,	FieldLimitName[41],	41,	FieldLimitLevel_Table[41],	"Field\\Mini\\dun-8.png"			},
	{32,	FieldLimitName[43],	43,	FieldLimitLevel_Table[43],	"Field\\Mini\\dun-9.png"			},
	{33,	FieldLimitName[44],	44,	FieldLimitLevel_Table[44],	"Field\\Mini\\mine-1.png"			},
	{34,	FieldLimitName[45],	45,	FieldLimitLevel_Table[45],	"Field\\Mini\\Slab.png"				},
	{35,	FieldLimitName[46],	46,	FieldLimitLevel_Table[46],	"Field\\Mini\\AncientW.png"			},
	{36,	FieldLimitName[56],	56,	FieldLimitLevel_Table[56],	"Field\\Mini\\iron3.png"			}
};

sNEWQUESTTITLE sQuestDelay[3] =
{
	{"DAILY QUEST 1. An Arrny of Stone(105+)"},
	{"DAILY QUEST 2. Forgetten Souls(110+)"},
	{"DAILY QUEST 3. Eterne Punishment(120+)"},
};

sNEWQUESTTITLE sQuestSelect[3] = 
{
	{"Hard"},
	{"Normal",0,0,1},
	{"Easy"},
};
sNEWQUESTTITLE sQuestKillMonster = 
{
	">>Kill %d Stone Monster",
};

cSINNEWBOX::cSINNEWBOX()
{

}
cSINNEWBOX::~cSINNEWBOX()
{

}
void cSINNEWBOX::Init()
{
	OpenFlag	= FALSE;
	Kind		= 0;
	x			= 0;
	y			= 0;
	Page		= 0;
	Count		= 0;
	Element		= 0;
	ScrollFlag	= FALSE;
	CloseFlag	= FALSE;
	OkFlag		= FALSE;
	EventFlag	= FALSE;
	Load();
}
void cSINNEWBOX::Load()
{
	lpBoxWindow[0]		= LoadDibSurfaceOffscreen("Image\\Sinimage\\Interface\\window.png");
	lpBoxWindow[1]		= LoadDibSurfaceOffscreen("Image\\Sinimage\\Interface\\window.png");
	lpBoxHeadbg			= LoadDibSurfaceOffscreen("Image\\Sinimage\\Interface\\header_bg.png");
	lpBoxTeleportHead	= LoadDibSurfaceOffscreen("Image\\Sinimage\\Interface\\header_teleport.png");
	lpBoxScroll[0]		= LoadDibSurfaceOffscreen("Image\\Sinimage\\Interface\\scroller.png");
	lpBoxScroll[1]		= LoadDibSurfaceOffscreen("Image\\Sinimage\\Interface\\scrollbar.png");
	lpBoxLine[0]		= LoadDibSurfaceOffscreen("Image\\Sinimage\\Interface\\line_vertical.png");
	lpBoxLine[1]		= LoadDibSurfaceOffscreen("Image\\Sinimage\\Interface\\seperator_line.png");
	lpBoxClose[0]		= LoadDibSurfaceOffscreen("Image\\Sinimage\\Interface\\button_close.png");
	lpBoxClose[1]		= LoadDibSurfaceOffscreen("Image\\Sinimage\\Interface\\button_close_.png");
	lpBoxOk[0]			= LoadDibSurfaceOffscreen("Image\\Sinimage\\Interface\\button_ok.png");
	lpBoxOk[1]			= LoadDibSurfaceOffscreen("Image\\Sinimage\\Interface\\button_ok_.png");
	lpBoxEnter[0]		= LoadDibSurfaceOffscreen("Image\\Sinimage\\Interface\\button_enter.png");
	lpBoxEnter[1]		= LoadDibSurfaceOffscreen("Image\\Sinimage\\Interface\\button_enter_.png");
	lpBoxElement[0]		= LoadDibSurfaceOffscreen("Image\\Sinimage\\Interface\\SOD\\fire.png");
	lpBoxElement[1]		= LoadDibSurfaceOffscreen("Image\\Sinimage\\Interface\\SOD\\wind.png");
	lpBoxElement[2]		= LoadDibSurfaceOffscreen("Image\\Sinimage\\Interface\\SOD\\water.png");
	lpBoxElement[3]		= LoadDibSurfaceOffscreen("Image\\Sinimage\\Interface\\SOD\\earth.png");
	lpBoxSodLogo		= LoadDibSurfaceOffscreen("Image\\Sinimage\\Interface\\SOD\\logo.png");
	lpBoxSodBar			= LoadDibSurfaceOffscreen("Image\\Sinimage\\Interface\\SOD\\sodbar.png");
	lpBoxQuest			= LoadDibSurfaceOffscreen("Image\\Sinimage\\Interface\\quest.png");
	lpBoxCheckBox[0]	= LoadDibSurfaceOffscreen("Image\\Sinimage\\Interface\\checkbox.tga");
	lpBoxCheckBox[1]	= LoadDibSurfaceOffscreen("Image\\Sinimage\\Interface\\checkbox_.tga");

	for (int i = 0; i < MAX_TELEPORT_FIELD; i ++)
			lpBoxMini[i]	= LoadDibSurfaceOffscreen(sTelePorts[i].szMapFileName);
}
void cSINNEWBOX::Release()
{
	for (int i = 0; i < 2; i ++)
	{
		SAFE_RELEASE(lpBoxWindow[i]);
		SAFE_RELEASE(lpBoxScroll[i]);
		SAFE_RELEASE(lpBoxClose[i]);
		SAFE_RELEASE(lpBoxCheckBox[i]);
		SAFE_RELEASE(lpBoxOk[i]);
		SAFE_RELEASE(lpBoxEnter[i]);
	}
	SAFE_RELEASE(lpBoxHeadbg);
	SAFE_RELEASE(lpBoxTeleportHead);
	SAFE_RELEASE(lpBoxQuest);
	for (int i = 0; i < 4; i ++)
		SAFE_RELEASE(lpBoxElement[i]);
	SAFE_RELEASE(lpBoxSodLogo);
	SAFE_RELEASE(lpBoxSodBar);
	for (int i = 0; i < MAX_TELEPORT_FIELD; i ++)
		SAFE_RELEASE(lpBoxMini[i]);
}
void cSINNEWBOX::Main()
{
	int top;
	int bottom;
	int left;
	int right;

	int my;
	int Result = 0;

	if (OpenFlag)
	{
		switch(Kind)
		{
		case SIN_HELP_KIND_SMASHTV:
			if (pCursorPos.x > x + 180 && pCursorPos.y > y + 328 && pCursorPos.x < x + 180 + 100 && pCursorPos.y < y + 328 + 21)
			{
				if (CloseFlag == FALSE)
					CloseFlag = TRUE;
			}
			else if (pCursorPos.x > x + 70 && pCursorPos.y > y + 328 && pCursorPos.x < x + 70 + 100 && pCursorPos.y < y + 328 + 21)
			{
				if (OkFlag == FALSE)
					OkFlag = TRUE;
			}
			else
			{
				if (CloseFlag == TRUE)
					CloseFlag = FALSE;
				if (OkFlag == TRUE)
					OkFlag = FALSE;
			}
			break;
		case SIN_HELP_KIND_TELEPORT_SCROLL:

			top = y + 40;
			bottom = y + 40 + 270;
			left = x + 20;
			right = x + 20 + 175;
			my = top;

			for (int i = 0; i < MAX_TELEPORT_FIELD; i ++)
			{
				if (sinMessageBoxShowFlag == 0)
				{
					if (pCursorPos.x >= left && pCursorPos.x <= right && pCursorPos.y >= top && pCursorPos.y <= bottom)
					{
						if (pCursorPos.x >= left && pCursorPos.x <= right && pCursorPos.y >= my && pCursorPos.y <= my + 20)
						{
							sTelePorts[i+Page].MoveFlag = TRUE;

							Result = i +Page;
						}
						for (int j = 0; j < MAX_TELEPORT_FIELD; j ++)
						{
							if (j != Result)
								sTelePorts[j].MoveFlag = FALSE;
						}
						my += 20;
					}
				}
			}
			if (sinMessageBoxShowFlag == 0)
			{
				if (pCursorPos.x >= x +9 && pCursorPos.x <= x + 17 && pCursorPos.y >= y + 40 && pCursorPos.y <= y + 40 + 278)
				{
					if (ScrollFlag == TRUE && MouseButton[0] == TRUE)
					{
						Page = (pCursorPos.y - (y + 40))/ (MAX_TELEPORT_FIELD - 24);

						if (Page < 0)
							Page = 0;
						if (Page > MAX_TELEPORT_FIELD - 14)
							Page = MAX_TELEPORT_FIELD - 14;
					}
				}
				if (pCursorPos.x >= x + 125 && pCursorPos.x <= x + 125 + 97 && pCursorPos.y >= y + 326 && pCursorPos.y <= y + 326 + 23)
					CloseFlag = TRUE;
				else
					CloseFlag = FALSE;
			}
			break;
		case SIN_HELP_KIND_QUEST_BOX:

			top = y + 40;
			bottom = y + 40 + 270;
			left = x + 20;
			right = x + 20 + 300;

			if (pCursorPos.x >= x +9 + 323 && pCursorPos.x <= x + 17 + 323 && pCursorPos.y >= y + 40 && pCursorPos.y <= y + 40 + 290)
			{
				if (ScrollFlag == TRUE && MouseButton[0] == TRUE)
				{
					if (CountPage > 17)
						Page = (pCursorPos.y - (y + 40)) * (CountPage - 17) / 278;
					else
						Page = (pCursorPos.y - (y + 40)) * CountPage / 278; 

					if (Page < 0)
						Page = 0;
					if (Page > CountPage)
						Page = CountPage;
				}
			}
			if (pCursorPos.x >= left && pCursorPos.x <= right && pCursorPos.y >= top && pCursorPos.y <= bottom)
			{
				for (int i = 0; i < CountPage; i ++)
				{
					my = y + 40 + i * 16 - Page * 16;

					if (my >= top && my <= bottom)
					{
						for (int j = 0; j < 3; j ++)
						{
							if (i == sQuestDelay[j].number)
							{
								if (pCursorPos.x >= x + 25 && pCursorPos.x <= x + 25 + 300 && pCursorPos.y >= my && pCursorPos.y <= my + 18)
									sQuestDelay[j].MoveFlag = TRUE;
								else
									sQuestDelay[j].MoveFlag = FALSE;
							}
						}
					}
				}
			}
			if (pCursorPos.x >= x + 125 && pCursorPos.x <= x + 125 + 97 && pCursorPos.y >= y + 326 && pCursorPos.y <= y + 326 + 23)
				CloseFlag = TRUE;
			else
				CloseFlag = FALSE;
			break;
		case SIN_HELP_KIND_QUEST_BOX_105:
		case SIN_HELP_KIND_QUEST_BOX_110:
		case SIN_HELP_KIND_QUEST_BOX_120:

			top = y + 40;
			bottom = y + 40 + 270;
			left = x + 20;
			right = x + 20 + 300;

			if (pCursorPos.x >= x +9 + 323 && pCursorPos.x <= x + 17 + 323 && pCursorPos.y >= y + 40 && pCursorPos.y <= y + 40 + 290)
			{
				if (ScrollFlag == TRUE && MouseButton[0] == TRUE)
				{
					if (CountPage > 17)
						Page = (pCursorPos.y - (y + 40)) * (CountPage - 17) / 278;
					else
						Page = (pCursorPos.y - (y + 40)) * CountPage / 278; 

					if (Page < 0)
						Page = 0;
					if (Page > CountPage)
						Page = CountPage;
				}
			}
			if (chaQuest.sHaQuestElementary[Quest_Daily_105].State == 0 || chaQuest.sHaQuestElementary[Quest_Daily_110].State == 0 || chaQuest.sHaQuestElementary[Quest_Daily_120].State == 0)
			{
				if (pCursorPos.x >= left && pCursorPos.x <= right && pCursorPos.y >= top && pCursorPos.y <= bottom)
				{
					for (int i = 0; i < CountPage; i ++)
					{
						my = y + 40 + i * 16 - Page * 16;

						if (my >= top && my <= bottom)
						{
							if (i == sQuestSelect[0].number || i == sQuestSelect[1].number || i == sQuestSelect[2].number)
							{
								for (int j = 0 ; j < 3 ; j ++)
								{
									if (pCursorPos.x >= x + 25 + 40 + j * 80 - 18 && pCursorPos.x <= x + 25 + 40 + j * 80 - 18 + 14 && pCursorPos.y >= my && pCursorPos.y <= my + 14)
										sQuestSelect[j].MoveFlag = TRUE;
									else
										sQuestSelect[j].MoveFlag = FALSE;
								}
							}
						}
					}
				}

				if (pCursorPos.x >= x + 185 && pCursorPos.x <= x + 185 + 97 && pCursorPos.y >= y + 326 && pCursorPos.y <= y + 326 + 23)
					CloseFlag = TRUE;
				else
					CloseFlag = FALSE;
				if (pCursorPos.x >= x + 65 && pCursorPos.x <= x + 65 + 97 && pCursorPos.y >= y + 326 && pCursorPos.y <= y + 326 + 23)
					OkFlag = TRUE;
				else
					OkFlag = FALSE;
			}
			if (chaQuest.sHaQuestElementary[Quest_Daily_105].State == 1 || chaQuest.sHaQuestElementary[Quest_Daily_110].State == 1 || chaQuest.sHaQuestElementary[Quest_Daily_120].State == 1)
			{
				if (pCursorPos.x >= x + 125 && pCursorPos.x <= x + 125 + 97 && pCursorPos.y >= y + 326 && pCursorPos.y <= y + 326 + 23)
					CloseFlag = TRUE;
				else
					CloseFlag = FALSE;

				if (OkFlag == TRUE)
					OkFlag = FALSE;
			}
			if (chaQuest.sHaQuestElementary[Quest_Daily_105].State == 2 || chaQuest.sHaQuestElementary[Quest_Daily_110].State == 2 || chaQuest.sHaQuestElementary[Quest_Daily_120].State == 2)
			{
				if (pCursorPos.x >= x + 125 && pCursorPos.x <= x + 125 + 97 && pCursorPos.y >= y + 326 && pCursorPos.y <= y + 326 + 23)
					OkFlag = TRUE;
				else
					OkFlag = FALSE;

				if (CloseFlag == TRUE)
					CloseFlag = FALSE;
			}
			break;
		}
	}
}
void cSINNEWBOX::Draw()
{
	int top = y + 40;
	int bottom = y + 40 + 270;

	int my = 0;
	int mx = 0;
	int dist = 0;

	if (OpenFlag)
	{
		switch(Kind)
		{
		case SIN_HELP_KIND_SMASHTV:
			DrawSprite(x		,y		,lpBoxWindow[0]			,0,0,350,360);	//BOX框子
			DrawSprite(x + 43	,y + 10	,lpBoxSodLogo			,0,0,264,110);	//标题头
			DrawSprite(x + 25	,y + 130,lpBoxSodBar			,0,0,300,20);	//标题头
			DrawSprite(x + 80	,y + 130,lpBoxElement[Element]	,0,0,20	,20);	//属性

			if (OkFlag == TRUE)
				DrawSprite(x + 70	,y + 328,lpBoxEnter[1]		,0,0,100,21);	//传送
			else
				DrawSprite(x + 70	,y + 328,lpBoxEnter[0]		,0,0,100,21);	//传送

			if (CloseFlag == TRUE)
				DrawSprite(x + 180	,y + 328,lpBoxClose[1]		,0,0,100,21);	//关闭
			else
				DrawSprite(x + 180	,y + 328,lpBoxClose[0]		,0,0,100,21);	//关闭
			break;
		case SIN_HELP_KIND_TELEPORT_SCROLL:

			dist = 278 / CountPage;

			DrawSprite(x			,y		,lpBoxWindow[0]		,0,0,350,360);	//BOX框子
			DrawSprite(x + 100		,y + 10	,lpBoxHeadbg		,0,0,148,23);
			DrawSprite(x + 135		,y + 13	,lpBoxTeleportHead	,0,0,79,14);
			if (MAX_TELEPORT_FIELD > 14)
			{
				DrawSprite(x + 10		,y + 40	,lpBoxScroll[1]		,0,0,6,278);	//滚动条
				DrawSprite(x + 9		,y + 40	+ Page * dist,lpBoxScroll[0]		,0,0,8,11);	//滚动条的游标
			}

			DrawSprite(x + 20		,y + 40	,lpBoxLine[0]		,0,0,1,280);	//竖LINE
			DrawSprite(x + 20+175	,y + 40	,lpBoxLine[0]		,0,0,1,280);	//竖LINE
			for (int i = 0; i <= MAX_TELEPORT_FIELD; i ++)
			{
				mx = x + 20;
				my = y + 40	+ i * 20 - Page * 20;
				if (my >= top && my <= bottom)
					DrawSprite(mx	,my,lpBoxLine[1]		,0,0,175,1);	//标题头

				if (sTelePorts[i].MoveFlag == TRUE)
					DrawSprite(x + 20 + 175 + 10,y + 120,lpBoxMini[i],0,0,128,128);
			}
			if (CloseFlag == TRUE)
				DrawSprite(x + 125	,y + 326,lpBoxClose[1]		,0,0,97,23);
			else
				DrawSprite(x + 125	,y + 326,lpBoxClose[0]		,0,0,97,23);
			break;
		case SIN_HELP_KIND_QUEST_BOX:

			if (CountPage > 17)
				dist = 278 / (CountPage - 17);
			else
				dist = 278 / CountPage;

			DrawSprite(x			,y		,lpBoxWindow[0]		,0,0,350,360);	//BOX框子

			for (int i = 0; i < CountPage; i ++)
			{
				my = y + 40 + i * 16 - Page * 16;

				if (my >= top && my <= bottom)
				{
					if (i == sQuestDelay[0].number || i == sQuestDelay[1].number || i == sQuestDelay[2].number)
						DrawSprite(x + 15	,my - 10,lpBoxQuest		,0,0,32,32);
				}
			}
			if (CountPage > 17)
			{
				DrawSprite(x + 10+ 323		,y + 40	,lpBoxScroll[1]		,0,0,6,278);	//滚动条
				DrawSprite(x + 9 + 323		,y + 40	+ Page * dist,lpBoxScroll[0]		,0,0,8,11);	//滚动条的游标
			}

			if (CloseFlag == TRUE)
				DrawSprite(x + 125	,y + 326,lpBoxClose[1]		,0,0,97,23);
			else
				DrawSprite(x + 125	,y + 326,lpBoxClose[0]		,0,0,97,23);
			break;
		case SIN_HELP_KIND_QUEST_BOX_105:
		case SIN_HELP_KIND_QUEST_BOX_110:
		case SIN_HELP_KIND_QUEST_BOX_120:
			if (CountPage > 17)
				dist = 278 / (CountPage - 17);
			else
				dist = 278 / CountPage;

			DrawSprite(x			,y		,lpBoxWindow[0]		,0,0,350,360);	//BOX框子

			if (CountPage > 17)
			{
				DrawSprite(x + 10+ 323		,y + 40	,lpBoxScroll[1]		,0,0,6,278);	//滚动条
				DrawSprite(x + 9 + 323		,y + 40	+ Page * dist,lpBoxScroll[0]		,0,0,8,11);	//滚动条的游标
			}

			if (chaQuest.sHaQuestElementary[Quest_Daily_105].State == 0 || chaQuest.sHaQuestElementary[Quest_Daily_110].State == 0 || chaQuest.sHaQuestElementary[Quest_Daily_120].State == 0)
			{
				for (int i = 0; i < CountPage; i ++)
				{
					my = y + 40 + i * 16 - Page * 16;

					if (my >= top && my <= bottom)
					{
						if (i == sQuestSelect[0].number || i == sQuestSelect[0].number || i == sQuestSelect[0].number)
						{
							for (int j = 0 ; j < 3 ; j ++)
							{
								if (sQuestSelect[j].OKFlag == TRUE)
									DrawSprite(x + 25 + 40 + j * 80 - 18		,my,lpBoxCheckBox[1]		,0,0,14,14);
								else
									DrawSprite(x + 25 + 40 + j * 80 - 18		,my,lpBoxCheckBox[0]		,0,0,14,14);
							}
						}
					}
				}

				if (CloseFlag == TRUE)
					DrawSprite(x + 185	,y + 326,lpBoxClose[1]		,0,0,97,23);
				else
					DrawSprite(x + 185	,y + 326,lpBoxClose[0]		,0,0,97,23);

				if (OkFlag == TRUE)
					DrawSprite(x + 65	,y + 326,lpBoxOk[1]		,0,0,97,23);
				else
					DrawSprite(x + 65	,y + 326,lpBoxOk[0]		,0,0,97,23);
			}
			if (chaQuest.sHaQuestElementary[Quest_Daily_105].State == 1 || chaQuest.sHaQuestElementary[Quest_Daily_110].State == 1 || chaQuest.sHaQuestElementary[Quest_Daily_120].State == 1)
			{
				if (CloseFlag == TRUE)
					DrawSprite(x + 125	,y + 326,lpBoxClose[1]		,0,0,97,23);
				else
					DrawSprite(x + 125	,y + 326,lpBoxClose[0]		,0,0,97,23);
			}
			if (chaQuest.sHaQuestElementary[Quest_Daily_105].State == 2 || chaQuest.sHaQuestElementary[Quest_Daily_110].State == 2 || chaQuest.sHaQuestElementary[Quest_Daily_120].State == 2)
			{
				if (OkFlag == TRUE)
					DrawSprite(x + 125	,y + 326,lpBoxOk[1]		,0,0,97,23);
				else
					DrawSprite(x + 125	,y + 326,lpBoxOk[0]		,0,0,97,23);
			}
			break;
		}
	}
}
void cSINNEWBOX::DrawText()
{
	char strBuff[128];

	DWORD Color = D3DCOLOR_XRGB(255,255,255);

	int top;
	int bottom;

	int my = 0;
	int mx = 0;

	int len;

	if (OpenFlag)
	{
		switch(Kind)
		{
		case SIN_HELP_KIND_SMASHTV:
#ifdef ENGLISH_LANGUAGE
			wsprintf(strBuff,"room:");
#else
			wsprintf(strBuff,"房间:");
#endif
			dsTextLineOut(cDXGraphic.lpD3DFont,x +  50	,y + 135,strBuff,lstrlen(strBuff),Color);

			switch(Element)
			{
			case 1:
				Color = D3DCOLOR_XRGB(0,162,113);
#ifdef ENGLISH_LANGUAGE
				wsprintf(strBuff,"wind");
#else
				wsprintf(strBuff,"风");
#endif
				break;
			case 2:
				Color = D3DCOLOR_XRGB(0,35,255);
#ifdef ENGLISH_LANGUAGE
				wsprintf(strBuff,"water");
#else
				wsprintf(strBuff,"水");
#endif
				break;
			case 3:
				Color = D3DCOLOR_XRGB(197,137,0);
#ifdef ENGLISH_LANGUAGE
				wsprintf(strBuff,"earth");
#else
				wsprintf(strBuff,"地");
#endif
				break;
			default:
				Color = D3DCOLOR_XRGB(255,0,0);
#ifdef ENGLISH_LANGUAGE
				wsprintf(strBuff,"fire");
#else
				wsprintf(strBuff,"火");
#endif
				break;
			}

			dsTextLineOut(cDXGraphic.lpD3DFont,x +  105	,y + 135,strBuff,lstrlen(strBuff),Color);
#ifdef ENGLISH_LANGUAGE
			wsprintf(strBuff,"#PlayCount: %d",Count);
#else
			wsprintf(strBuff,"#房间人数: %d",Count);
#endif
			Color = D3DCOLOR_XRGB(255,255,255);
			dsTextLineOut(cDXGraphic.lpD3DFont,x +  155	,y + 135,strBuff,lstrlen(strBuff),Color);

			for (int i = 0; i < CountPage; i ++)
				dsTextLineOut(cDXGraphic.lpD3DFont,x +  25	,y + 160 + i * 20,szBuff[i],lstrlen(szBuff[i]),Color);

#ifdef ENGLISH_LANGUAGE
			wsprintf(strBuff,"%d × characterLevel + TEX = %d Gold",300,300 * sinChar->Level);
#else
			wsprintf(strBuff,"%d × 角色等级 + TEX = %d 金",300,300 * sinChar->Level);
#endif

			dsTextLineOut(cDXGraphic.lpD3DFont,x +  25	,y + 300,strBuff,lstrlen(strBuff),D3DCOLOR_XRGB(148,200,178));
			break;
		case SIN_HELP_KIND_TELEPORT_SCROLL:

			top = y + 45;
			bottom = y + 45 + 270;

			Color = D3DCOLOR_XRGB(190,160,110);
			for (int i = 0; i < MAX_TELEPORT_FIELD; i ++)
			{
				ZeroMemory(strBuff,sizeof(strBuff));

				if (sTelePorts[i].MapLevel == 0)
					sTelePorts[i].MapLevel = 1;
				wsprintf(strBuff,"%d.%s(%d)",sTelePorts[i].PNo,sTelePorts[i].lpMapName,sTelePorts[i].MapLevel);

				my = y + 45 + i * 20 - Page * 20;

				if (my >= top && my <= bottom)
				{
					if (sTelePorts[i].MoveFlag == TRUE)
						dsTextLineOut(cDXGraphic.lpD3DFont,x + 25,my,strBuff,lstrlen(strBuff),D3DCOLOR_XRGB(255,100,45));
					else
						dsTextLineOut(cDXGraphic.lpD3DFont,x + 25,my,strBuff,lstrlen(strBuff),Color);
				}


				if (sTelePorts[i].MoveFlag == TRUE)
				{
					SIZE sizecheck = { 0 };

					len = lstrlen(sTelePorts[i].lpMapName);

					GetTextExtentPoint32(cDXGraphic.lpD3DBoldFont->GetDC(),sTelePorts[i].lpMapName,len,&sizecheck);

					mx = 75 - (sizecheck.cx >> 1);

					dsTextLineOut(cDXGraphic.lpD3DBoldFont,x + 20 + 175 + mx,y + 80,sTelePorts[i].lpMapName,len,Color);

#ifdef ENGLISH_LANGUAGE
					wsprintf(strBuff,"Enter Level %d",sTelePorts[i].MapLevel);
#else
					wsprintf(strBuff,"需要等级 %d",sTelePorts[i].MapLevel);
#endif

					len = lstrlen(strBuff);

					GetTextExtentPoint32(cDXGraphic.lpD3DBoldFont->GetDC(),strBuff,len,&sizecheck);

					mx = 75 - (sizecheck.cx >> 1);

					dsTextLineOut(cDXGraphic.lpD3DBoldFont,x + 20 + 175 + mx,y + 280,strBuff,len,Color);
				}
			}
			break;
		case SIN_HELP_KIND_QUEST_BOX:

			top = y + 40;
			bottom = y + 40 + 270;

			for (int i = 0; i < CountPage; i ++)
			{
				my = y + 40 + i * 16 - Page * 16;

				if (my >= top && my <= bottom)
				{
					if (i == sQuestDelay[0].number || i == sQuestDelay[1].number || i == sQuestDelay[2].number)
					{
						if ((sQuestDelay[0].MoveFlag == TRUE && i == sQuestDelay[0].number) ||
							(sQuestDelay[1].MoveFlag == TRUE && i == sQuestDelay[1].number) ||
							(sQuestDelay[2].MoveFlag == TRUE && i == sQuestDelay[2].number))
							dsTextLineOut(cDXGraphic.lpD3DFont,x +  25 + 20	,my,szBuff[i],lstrlen(szBuff[i]),D3DCOLOR_XRGB(255,100,45));
						else
							dsTextLineOut(cDXGraphic.lpD3DFont,x +  25 + 20	,my,szBuff[i],lstrlen(szBuff[i]),Color);
					}
					else
						dsTextLineOut(cDXGraphic.lpD3DFont,x +  25	,my,szBuff[i],lstrlen(szBuff[i]),Color);
				}
			}
			break;
		case SIN_HELP_KIND_QUEST_BOX_105:
		case SIN_HELP_KIND_QUEST_BOX_110:
		case SIN_HELP_KIND_QUEST_BOX_120:
			top = y + 40;
			bottom = y + 40 + 270;

			for (int i = 0; i < CountPage; i ++)
			{
				my = y + 40 + i * 16 - Page * 16;

				if (my >= top && my <= bottom)
				{
					if (chaQuest.sHaQuestElementary[Quest_Daily_105].State == 0 || chaQuest.sHaQuestElementary[Quest_Daily_110].State == 0 || chaQuest.sHaQuestElementary[Quest_Daily_120].State == 0)
					{
						if (i == sQuestSelect[0].number || i == sQuestSelect[1].number || i == sQuestSelect[2].number)
						{
							for (int j = 0; j < 3; j ++)
								dsTextLineOut(cDXGraphic.lpD3DFont,x +  25 + 40 + j * 80		,my,sQuestSelect[j].szName,lstrlen(sQuestSelect[j].szName),Color);
						}
						if (i == sQuestKillMonster.number)
						{
							wsprintf(strBuff,sQuestKillMonster.szName,Count);

							dsTextLineOut(cDXGraphic.lpD3DFont,x +  25	,my,strBuff,lstrlen(strBuff),Color);
						}
					}
					dsTextLineOut(cDXGraphic.lpD3DFont,x +  25	,my,szBuff[i],lstrlen(szBuff[i]),Color);
				}
			}
			break;
		}
	}
}
void cSINNEWBOX::LButtonDown(int px,int py)
{
	int top;
	int bottom;
	int left;
	int right;

	int my = 0;

	if (OpenFlag)
	{
		switch(Kind)
		{
		case SIN_HELP_KIND_SMASHTV:
			if (sinMessageBoxShowFlag == 0)
			{
				if (CloseFlag == TRUE)
				{
					OpenFlag	= FALSE;
					return;
				}
				if (OkFlag == TRUE)
				{
					if(sinChar->Money < (sinChar->Level * 300))
					{
						cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
						return;
					}
					cMessageBox.ShowMessage3(MESSAGE_EVENT_SMASHTV,""); 
				}
			}
			break;
		case SIN_HELP_KIND_TELEPORT_SCROLL:
			top = y + 40;
			bottom = y + 40 + 270;
			left = x + 20;
			right = x + 20 + 175;

			if (sinMessageBoxShowFlag == 0)
			{
				if (px >= x +9 && px <= x + 17 && py >= y + 40 && py <= y + 40 + 278)
				{
					Page = (py - (y + 40))/ (MAX_TELEPORT_FIELD - 24);

					if (Page < 0)
						Page = 0;
					if (Page > MAX_TELEPORT_FIELD - 14)
						Page = MAX_TELEPORT_FIELD - 14;

					ScrollFlag = TRUE;
				}
				else
					ScrollFlag = FALSE;

				if (px >= left && px <= right && py >= top && py <= bottom)
				{
					for (int i = 0; i < MAX_TELEPORT_FIELD; i ++)
					{
						if (sTelePorts[i].MoveFlag == TRUE)
						{
							TelePorts.MapCode	= sTelePorts[i].MapCode;
							TelePorts.MapLevel	= sTelePorts[i].MapLevel; 
							cMessageBox.ShowMessage3(MESSAGE_TELEPORT_CORE,sTelePorts[i].lpMapName);
							chaPremiumitem.Using_ItemKind = 0;
							break;
						}
					}
				}
				if (CloseFlag == TRUE)
					OpenFlag = FALSE;
			}
			break;
		case SIN_HELP_KIND_QUEST_BOX:
			if (px >= x +9 + 323 && px <= x + 17 + 323 && py >= y + 40 && py <= y + 40 + 278)
			{
				if (CountPage > 17)
					Page = (py - (y + 40)) * (CountPage - 17) / 278;
				else
					Page = (py - (y + 40)) * CountPage / 278; 

				if (Page < 0)
					Page = 0;
				if (Page > CountPage)
					Page = CountPage;

				ScrollFlag = TRUE;
			}
			else
				ScrollFlag = FALSE;

			if (sQuestDelay[0].MoveFlag == TRUE && MouseButton[0] == TRUE)
			{
				if (CheckNowQuestState(0) == FALSE)
					return;

				if (sinChar->Level >= 105  && (QUESTBIT_ELEMENTARY_DAIL_105 & haElementaryQuestLog) == 0)
				{
					Kind = SIN_HELP_KIND_QUEST_BOX_105;

					ReadFileData("image\\Sinimage\\Quest\\3001_start.txt");
					ZeroMemory(szBuff,sizeof(szBuff));
					ReadFileDataDivide(&szBuff[0][0]);
					Page = 0;
					AddTextInfo("Choose Diffculty:");
					CountPage = GetTextLen() + 1;
					sQuestSelect[0].number = CountPage - 1;
					sQuestSelect[1].number = CountPage - 1;
					sQuestSelect[2].number = CountPage - 1;

					AddTextInfo("Objective");

					CountPage = GetTextLen() + 1;
					sQuestKillMonster.number = CountPage - 1;

					Count = 3000;

					EventFlag = SIN_HELP_KIND_QUEST_BOX_105;
				}
			}
			else if (sQuestDelay[1].MoveFlag == TRUE && MouseButton[0] == TRUE)
			{
				if (CheckNowQuestState(0) == FALSE)
					return;

				if (sinChar->Level >= 110 && (QUESTBIT_ELEMENTARY_DAIL_110 & haElementaryQuestLog) == 0)
				{
					Kind = SIN_HELP_KIND_QUEST_BOX_110;

					ReadFileData("image\\Sinimage\\Quest\\3002_start.txt");
					ZeroMemory(szBuff,sizeof(szBuff));
					ReadFileDataDivide(&szBuff[0][0]);
					Page = 0;
					AddTextInfo("Choose Diffculty:");
					CountPage = GetTextLen() + 1;
					sQuestSelect[0].number = CountPage - 1;
					sQuestSelect[1].number = CountPage - 1;
					sQuestSelect[2].number = CountPage - 1;

					AddTextInfo("Objective");

					CountPage = GetTextLen() + 1;
					sQuestKillMonster.number = CountPage - 1;

					Count = 3000;
					EventFlag = SIN_HELP_KIND_QUEST_BOX_110;
				}
			}
			else if (sQuestDelay[2].MoveFlag == TRUE && MouseButton[0] == TRUE)
			{
				if (CheckNowQuestState(0) == FALSE)
					return;

				if (sinChar->Level >= 120 && (QUESTBIT_ELEMENTARY_DAIL_120 & haElementaryQuestLog) == 0)
				{
					Kind = SIN_HELP_KIND_QUEST_BOX_120;

					ReadFileData("image\\Sinimage\\Quest\\3003_start.txt");
					ZeroMemory(szBuff,sizeof(szBuff));
					ReadFileDataDivide(&szBuff[0][0]);
					Page = 0;
					AddTextInfo("Choose Diffculty:");
					CountPage = GetTextLen() + 1;
					sQuestSelect[0].number = CountPage - 1;
					sQuestSelect[1].number = CountPage - 1;
					sQuestSelect[2].number = CountPage - 1;

					AddTextInfo("Objective");

					CountPage = GetTextLen() + 1;
					sQuestKillMonster.number = CountPage - 1;

					Count = 3000;

					EventFlag = SIN_HELP_KIND_QUEST_BOX_120;
				}
			}

			if (CloseFlag == TRUE)
				OpenFlag = FALSE;
			break;
		case SIN_HELP_KIND_QUEST_BOX_105:
		case SIN_HELP_KIND_QUEST_BOX_110:
		case SIN_HELP_KIND_QUEST_BOX_120:

			top = y + 40;
			bottom = y + 40 + 270;
			left = x + 20;
			right = x + 20 + 300;

			if (sinMessageBoxShowFlag == 0)
			{
				if (px >= x +9 + 323 && px <= x + 17 + 323 && py >= y + 40 && py <= y + 40 + 278)
				{
					if (CountPage > 17)
						Page = (py - (y + 40)) * (CountPage - 17) / 278;
					else
						Page = (py - (y + 40)) * CountPage / 278; 

					if (Page < 0)
						Page = 0;
					if (Page > CountPage)
						Page = CountPage;

					ScrollFlag = TRUE;
				}
				else
					ScrollFlag = FALSE;

				if (chaQuest.sHaQuestElementary[Quest_Daily_105].State == 0 || chaQuest.sHaQuestElementary[Quest_Daily_110].State == 0 || chaQuest.sHaQuestElementary[Quest_Daily_120].State == 0)
				{
					if (px >= left && px <= right && py >= top && py <= bottom)
					{
						for (int i = 0; i < 3; i ++)
						{
							if (sQuestSelect[i].MoveFlag == TRUE && MouseButton[0] == TRUE)
								sQuestSelect[i].OKFlag = TRUE;
							else
								sQuestSelect[i].OKFlag = FALSE;
						}
					}

					switch(Kind)
					{
					case SIN_HELP_KIND_QUEST_BOX_105:
						if (sQuestSelect[0].OKFlag == TRUE)
							Count = 3000;
						else if (sQuestSelect[1].OKFlag == TRUE)
							Count = 4000;
						else if (sQuestSelect[2].OKFlag == TRUE)
							Count = 5000;
						break;
					case SIN_HELP_KIND_QUEST_BOX_110:
						if (sQuestSelect[0].OKFlag == TRUE)
							Count = 3000;
						else if (sQuestSelect[1].OKFlag == TRUE)
							Count = 4000;
						else if (sQuestSelect[2].OKFlag == TRUE)
							Count = 5000;
						break;
					case SIN_HELP_KIND_QUEST_BOX_120:
						if (sQuestSelect[0].OKFlag == TRUE)
							Count = 3000;
						else if (sQuestSelect[1].OKFlag == TRUE)
							Count = 4000;
						else if (sQuestSelect[2].OKFlag == TRUE)
							Count = 5000;
						break;
					}
				}

				if (CloseFlag == TRUE)
					OpenFlag = FALSE;

				if (OkFlag == TRUE && MouseButton[0] == TRUE)
				{
					switch(Kind)
					{
					case SIN_HELP_KIND_QUEST_BOX_105:
						if (chaQuest.sHaQuestElementary[Quest_Daily_105].State == 0)
							cMessageBox.ShowMessage3(MESSAGE_QUEST_DAILY_105,"");

						if (chaQuest.sHaQuestElementary[Quest_Daily_105].State == 2)
						{
							cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
							SendQuestCommandToServer(HAQUEST_CODE_DAIL_105,1,0,0);
							haElementaryQuestLog |= QUESTBIT_ELEMENTARY_DAIL_105;
							chaQuest.sHaQuestElementary[Quest_Daily_105].BackUpCode = chaQuest.sHaQuestElementary[Quest_Daily_105].CODE;
							chaQuest.sHaQuestElementary[Quest_Daily_105].CODE		= 0;
							chaQuest.sHaQuestElementary[Quest_Daily_105].State		= 3;

#ifdef ENGLISH_LANGUAGE
							cMessageBox.ShowMessageEvent("Received 2.000.000.000 EXP     ");
#else
							cMessageBox.ShowMessageEvent("获得了 2.000.000.000 经验     ");
#endif

							sinPlaySound(SIN_SOUND_EAT_POTION2);
							EndQuest_Code(chaQuest.sHaQuestElementary[Quest_Daily_105].BackUpCode);
							SaveGameData();
							OpenFlag = FALSE;
						}
						break;
					case SIN_HELP_KIND_QUEST_BOX_110:
						if (chaQuest.sHaQuestElementary[Quest_Daily_110].State == 0)
							cMessageBox.ShowMessage3(MESSAGE_QUEST_DAILY_110,"");

						if (chaQuest.sHaQuestElementary[Quest_Daily_110].State == 2)
						{
							cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
							SendQuestCommandToServer(HAQUEST_CODE_DAIL_110,1,0,0);
							haElementaryQuestLog |= QUESTBIT_ELEMENTARY_DAIL_110;
							chaQuest.sHaQuestElementary[Quest_Daily_110].BackUpCode = chaQuest.sHaQuestElementary[Quest_Daily_110].CODE;
							chaQuest.sHaQuestElementary[Quest_Daily_110].CODE		= 0;
							chaQuest.sHaQuestElementary[Quest_Daily_110].State		= 3;

#ifdef ENGLISH_LANGUAGE
							cMessageBox.ShowMessageEvent("Received 2.000.000.000 EXP     ");
#else
							cMessageBox.ShowMessageEvent("获得了 2.000.000.000 经验     ");
#endif

							sinPlaySound(SIN_SOUND_EAT_POTION2);
							EndQuest_Code(chaQuest.sHaQuestElementary[Quest_Daily_110].BackUpCode);
							SaveGameData();
							OpenFlag = FALSE;
						}
						break;
					case SIN_HELP_KIND_QUEST_BOX_120:
						if (chaQuest.sHaQuestElementary[Quest_Daily_120].State == 0)
							cMessageBox.ShowMessage3(MESSAGE_QUEST_DAILY_120,"");

						if (chaQuest.sHaQuestElementary[Quest_Daily_120].State == 2)
						{
							cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
							SendQuestCommandToServer(HAQUEST_CODE_DAIL_120,1,0,0);
							haElementaryQuestLog |= QUESTBIT_ELEMENTARY_DAIL_120;
							chaQuest.sHaQuestElementary[Quest_Daily_120].BackUpCode = chaQuest.sHaQuestElementary[Quest_Daily_120].CODE;
							chaQuest.sHaQuestElementary[Quest_Daily_120].CODE		= 0;
							chaQuest.sHaQuestElementary[Quest_Daily_120].State		= 3;

#ifdef ENGLISH_LANGUAGE
							cMessageBox.ShowMessageEvent("Received 2.000.000.000 EXP     ");
#else
							cMessageBox.ShowMessageEvent("获得了 2.000.000.000 经验     ");
#endif

							sinPlaySound(SIN_SOUND_EAT_POTION2);
							EndQuest_Code(chaQuest.sHaQuestElementary[Quest_Daily_120].BackUpCode);
							SaveGameData();
							OpenFlag = FALSE;
						}
						break;
					}
				}
			}
			break;
		}
	}
}
void cSINNEWBOX::LButtonUp(int px,int py)
{

}
void cSINNEWBOX::RButtonDown(int px,int py)
{

}
void cSINNEWBOX::RButtonUp(int px,int py)
{

}
void cSINNEWBOX::KeyDown()
{

}
void cSINNEWBOX::Close()
{
	Release();
}
void cSINNEWBOX::CloseWindow()
{
	if (OpenFlag == TRUE)
		OpenFlag = FALSE;
}
int cSINNEWBOX::sinShow(int kind,int px,int py,char *FileName)
{
	if (OpenFlag == FALSE)
	{
		switch(kind)
		{
		case SIN_HELP_KIND_SMASHTV:
			OpenFlag	= TRUE;
			Kind		= kind;
			x			= px;
			y			= py;
			ReadFileData(FileName);
			ZeroMemory(szBuff,sizeof(szBuff));
			ReadFileDataDivide(&szBuff[0][0]);
			CountPage = GetTextLen();
			break;
		case SIN_HELP_KIND_TELEPORT_SCROLL:
			OpenFlag	= TRUE;
			Kind		= kind;
			x			= px;
			y			= py;
			CountPage	= MAX_TELEPORT_FIELD - 14;
			break;
		case SIN_HELP_KIND_QUEST_BOX:
			OpenFlag	= TRUE;
			Kind		= kind;
			x			= px;
			y			= py;

			Page		= 0;

			ReadFileData(FileName);
			ZeroMemory(szBuff,sizeof(szBuff));
			ReadFileDataDivide(&szBuff[0][0]);
			for (int i = 0; i < 3; i ++)
				sQuestDelay[i].MoveFlag = FALSE;

			sQuestDelay[0].number = AddTextInfo(sQuestDelay[0].szName);
			sQuestDelay[1].number = AddTextInfo(sQuestDelay[1].szName);
			sQuestDelay[2].number = AddTextInfo(sQuestDelay[2].szName);
			CountPage = GetTextLen();
			break;
		}
	}
	return FALSE;
}
int cSINNEWBOX::ReadFileData(char *FileName)
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
int cSINNEWBOX::ReadFileDataDivide(char *szBuf)
{
	char c;
	int cnt = 0;
	int bufC = 0;

	char *szBuffer = 0;

	ZeroMemory(szBuf,sizeof(szBuf));

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

	return FALSE;
}
int cSINNEWBOX::GetTextLen()
{
	for (int i = 0; i < 80; i ++)
	{
		if (szBuff[i][0] == '\0' && szBuff[i + 1][0] == '\0')
			return i;
	}
	return 0;
}
int cSINNEWBOX::AddTextInfo(char *buf)
{
	for (int i = 0; i < 80; i ++)
	{
		if (szBuff[i][0] == '\0' && szBuff[i +1][0] == '\0')
		{
			lstrcpy(szBuff[i + 1],buf);
			return i + 1;
		}
	}
	return 0;
}