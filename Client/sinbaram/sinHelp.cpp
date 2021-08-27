#include "StdAfx.h"
#include "..\\tjboy\\clanmenu\\tjclanDEF.h"
#include "..\\tjboy\\clanmenu\\tjclan.h"

cSINHELP cSinHelp;
sSINHELP sSinHelp[SIN_MAX_HELP_NUMBER];
char szFileReadBuf2[80 * 128];
sSOD_RANK sSod_Rank[10];

sTONY_TEST_IMAGE sTonyTest[10];

char szHelpDocBuff[100][128];

int HelpBoxKindIndex = 0;

int MatHelpBoxImage[10];

int TempScrollPosiY = 50;
int WingItemQuestIndex = 0;

int MatGuideHelpTitle = 0;
int MatGuideHelpIcon = 0;
int MatGuideHelpIconGlay = 0;

int MatHelpTitle = 0;
int MatHelpTitleIcon = 0;
int MatHelpTitleIconGlay = 0;

int GuideHelpFlag = 0;
char *TeleportFilePath = "image\\Sinimage\\help\\Teleport.sin";
int sinTeleportIndex = 0;
int sinFallgameIndex = 0;
int sinTeleportMoneyIndex = 0;
int TeleportUseCose[] = { 100,100,500,1000 };


char *haC_TeleportFilePath = "image\\Sinimage\\help\\CastleTeleport.sin";
char *haC_Not_TeleportFilePath = "image\\Sinimage\\help\\CastleTeleport_.sin";

int  haC_TeleportIndex = 0;
int  haC_TeleportMoney = 0;

char *haResearchFilePath1 = "image\\Sinimage\\help\\Research1.sin";
char *haResearchFilePath2 = "image\\Sinimage\\help\\Research2.sin";
char *haResearchFilePath3 = "image\\Sinimage\\help\\Research3.sin";

int   haResearchIndex = 0;

shaResearch haResearch;


cSINHELP::cSINHELP()
{

}
cSINHELP::~cSINHELP()
{

}
void cSINHELP::Init()
{
	MatScrollButton = CreateTextureMaterial("Image\\SinImage\\Help\\scl_icon.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatScrollBar = CreateTextureMaterial("Image\\SinImage\\Help\\scl_bar.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatHelpBoxImage[0] = CreateTextureMaterial("Image\\SinImage\\Help\\HelpBoxCorner.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatHelpBoxImage[1] = CreateTextureMaterial("Image\\SinImage\\Help\\HelpBoxLine.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	char szBuff[128];

	for (int i = 2; i < 9; i++)
	{
		wsprintf(szBuff, "Image\\SinImage\\Help\\box%d.tga", i + 1);
		MatHelpBoxImage[i] = CreateTextureMaterial(szBuff, 0, 0, 0, SMMAT_BLEND_ALPHA);
	}
	MatHelpBoxImage[9] = CreateTextureMaterial("Image\\SinImage\\Help\\Box_Line.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatGuideHelpTitle = CreateTextureMaterial("Image\\SinImage\\Help\\help_icon02t.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatGuideHelpIcon = CreateTextureMaterial("Image\\SinImage\\Help\\help_icon02.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatGuideHelpIconGlay = CreateTextureMaterial("Image\\SinImage\\Help\\help_icon02_.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatHelpTitle = CreateTextureMaterial("Image\\SinImage\\Help\\help_icon01t.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatHelpTitleIcon = CreateTextureMaterial("Image\\SinImage\\Help\\help_icon01.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatHelpTitleIconGlay = CreateTextureMaterial("Image\\SinImage\\Help\\help_icon01_.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);


	Load();

	if (!bCheckHostNameandPort)
		Interface_clanmenu.NoticeMessage_Init();

	ScrollLineCount = 0;
	cSinHelp.NPCTeleportFlag = 0;

}
void cSINHELP::Load()
{
	lpHelpTitle = LoadDibSurfaceOffscreen("Image\\SinImage\\Help\\box-test-title.png");
	lpChangeJobTitle = LoadDibSurfaceOffscreen("Image\\SinImage\\Help\\box-test-title.bmp");
	lpHelpOk = LoadDibSurfaceOffscreen("Image\\SinImage\\Help\\box-test-title2.bmp");
}
void cSINHELP::Release()
{

}
void cSINHELP::Draw()
{
	int i, j, k;
	for (i = 0; i < SIN_MAX_HELP_NUMBER; i++)
	{
		if (sSinHelp[i].KindFlag)
		{
			for (j = 0; j < sSinHelp[i].SizeW; j++)
			{
				for (k = 0; k < sSinHelp[i].SizeH; k++)
				{
					if (sSinHelp[i].MatFlag[j][k])
					{
						sinDrawTexImage(sSinHelp[i].sHelp_Box[j][k]->Mat,
							sSinHelp[i].sHelp_Box[j][k]->x,
							sSinHelp[i].sHelp_Box[j][k]->y,
							sSinHelp[i].sHelp_Box[j][k]->w,
							sSinHelp[i].sHelp_Box[j][k]->h,
							sSinHelp[i].sHelp_Box[j][k]->surW,
							sSinHelp[i].sHelp_Box[j][k]->surH,
							sSinHelp[i].sHelp_Box[j][k]->tLeft,
							sSinHelp[i].sHelp_Box[j][k]->tTop,
							sSinHelp[i].sHelp_Box[j][k]->tRight,
							sSinHelp[i].sHelp_Box[j][k]->tBottom,
							sSinHelp[i].sHelp_Box[j][k]->Transp);
					}
				}
			}
			for (j = 0; j < sSinHelp[i].SizeW - 2; j++)
			{
				for (k = 0; k < sSinHelp[i].SizeH - 2; k++)
					sinDrawTexImage(MatHelpBoxImage[4], (float)sSinHelp[i].PosiX + 64 + (32 * j), (float)sSinHelp[i].PosiY + 32 + (32 * k), 32.0f, 32.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 255);
			}
			if (sSinHelp[i].KindFlag != SIN_HELP_KIND_SOD)
				sinDrawTexImage(MatHelpBoxImage[9], (float)sSinHelp[i].PosiX + 8, (float)sSinHelp[i].PosiY + 48, (float)(sSinHelp[i].SizeW * 32) + 50, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 255);

			if (sSinHelp[i].KindFlag == SIN_HELP_KIND_NORMAL)
			{
				dsDrawTexImage(MatGuideHelpTitle, sSinHelp[i].PosiX + 340, sSinHelp[i].PosiY + 14, 64, 32, 255);
				if (GuideHelpFlag)
					dsDrawTexImage(MatGuideHelpIcon, sSinHelp[i].PosiX + 300 + 5, sSinHelp[i].PosiY + 14, 32, 32, 255);
				else
					dsDrawTexImage(MatGuideHelpIconGlay, sSinHelp[i].PosiX + 300 + 5, sSinHelp[i].PosiY + 14, 32, 32, 255);

				dsDrawTexImage(MatHelpTitle, sSinHelp[i].PosiX + 55, sSinHelp[i].PosiY + 13, 64, 32, 255);
				dsDrawTexImage(MatHelpTitleIcon, sSinHelp[i].PosiX + 25, sSinHelp[i].PosiY + 13, 32, 32, 255);
			}
			if (sSinHelp[i].ScrollFlag)
			{
				sinDrawTexImage(MatScrollBar, (float)(sSinHelp[i].PosiX + (sSinHelp[i].SizeW - 1) * 32 + 80 - 6), (float)(sSinHelp[i].PosiY + TempScrollPosiY), (float)8, (float)256);
				sinDrawTexImage(MatScrollButton, (float)sSinHelp[i].ScrollButton.x, (float)sSinHelp[i].ScrollButton.y - 7, (float)16, (float)16);

			}
			if (sSinHelp[i].KindFlag == SIN_HELP_KIND_SOD)
			{
				DrawSprite(sSinHelp[i].PosiX + 18, sSinHelp[i].PosiY + 22, lpSodMenu, 0, 0, 318, 33);
				for (int h = 0; h < 10; h++)
				{
					DrawSprite(sSinHelp[i].PosiX + 18, sSinHelp[i].PosiY + 59 + (h * 24), lpSodLine, 0, 0, 318, 21);
					if (sSod_Rank[h].Flag)
						DrawSprite(sSinHelp[i].PosiX + 18 + 34, sSinHelp[i].PosiY + 59 + (h * 24) - 1, lpSodJobFace[sSod_Rank[h].Job - 1], 0, 0, 23, 19);
				}
			}
			else
				DrawSprite(sSinHelp[i].TitlePosi.x, sSinHelp[i].TitlePosi.y, lpHelpTitle, 0, 0, 181, 32);

			if (sSinHelp[i].KindFlag != SIN_HELP_KIND_WARPGATE && sSinHelp[i].KindFlag != SIN_HELP_KIND_INITPOINT && sSinHelp[i].KindFlag != SIN_HELP_KIND_RESEARCH)
			{
				DrawSprite(sSinHelp[i].ButtonPosi.x, sSinHelp[i].ButtonPosi.y, lpHelpOk, 0, 0, 48, 23);
				DrawSprite(sSinHelp[i].ButtonPosi.x + 9, sSinHelp[i].ButtonPosi.y + 4, cMessageBox.lpButtonOk[0], 0, 0, 32, 16);

				if (sSinHelp[i].ButtonShowFlag)
					DrawSprite(sSinHelp[i].ButtonPosi.x + 9, sSinHelp[i].ButtonPosi.y + 4, cMessageBox.lpButtonOk[1], 0, 0, 32, 16);
			}
			if (sSinHelp[i].KindFlag == SIN_HELP_KIND_RESEARCH)
			{
				sSinHelp[i].ButtonPosi.x = 250;
				DrawSprite(sSinHelp[i].ButtonPosi.x, sSinHelp[i].ButtonPosi.y, lpHelpOk, 0, 0, 48, 23);
				DrawSprite(sSinHelp[i].ButtonPosi.x + 9, sSinHelp[i].ButtonPosi.y + 4, cMessageBox.lpButtonCancel[0], 0, 0, 32, 16);
				if (sSinHelp[i].ButtonShowFlag)
					DrawSprite(sSinHelp[i].ButtonPosi.x + 9, sSinHelp[i].ButtonPosi.y + 4, cMessageBox.lpButtonCancel[1], 0, 0, 32, 16);
				haResearch.ButtonPosi.x = 150, haResearch.ButtonPosi.y = sSinHelp[i].ButtonPosi.y;
				DrawSprite(haResearch.ButtonPosi.x, haResearch.ButtonPosi.y, lpHelpOk, 0, 0, 48, 23);
				DrawSprite(haResearch.ButtonPosi.x + 9, haResearch.ButtonPosi.y + 4, cMessageBox.lpButtonOk[0], 0, 0, 32, 16);
				if (haResearch.ButtonShowFlag)
					DrawSprite(haResearch.ButtonPosi.x + 9, haResearch.ButtonPosi.y + 4, cMessageBox.lpButtonOk[1], 0, 0, 32, 16);
			}
		}
	}
	for (i = 0; i < 10; i++)
	{
		if (sTonyTest[i].Flag)
		{
			if (sTonyTest[i].FileFormat == TONY_TGA)
				dsDrawTexImage(sTonyTest[i].Mat, sTonyTest[i].Posi.x, sTonyTest[i].Posi.y, sTonyTest[i].Size.x, sTonyTest[i].Size.y, 255);
			if (sTonyTest[i].FileFormat == TONY_BMP)
				DrawSprite(sTonyTest[i].Posi.x, sTonyTest[i].Posi.y, sTonyTest[i].lpTony, 0, 0, sTonyTest[i].Size.x, sTonyTest[i].Size.y);
		}
	}
	for (int i = 0; i < MAX_INVEN_PARTICLE; i++)
	{
		if (sInven_Effect[i].Time)
		{
			switch (sInven_Effect[i].Kind)
			{
			case SIN_EFFECT_SHOW_INVEN:
				if (cInvenTory.OpenFlag)
					cInvenTory.sinDrawInvenTexImage(&sInven_Effect[i].InvenFace);
				break;
			case SIN_EFFECT_SHOW_WAREHOUSE:
				if (cWareHouse.OpenFlag)
					cInvenTory.sinDrawInvenTexImage(&sInven_Effect[i].InvenFace);
				break;
			case SIN_EFFECT_SHOW_TRADE:
				if (cTrade.OpenFlag)
					cInvenTory.sinDrawInvenTexImage(&sInven_Effect[i].InvenFace);
				break;

			}
		}
	}
}
void cSINHELP::Main()
{
	GuideHelpFlag = 0;
	sinTeleportIndex = 0;
	haC_TeleportIndex = 0;
	int sinTelePortLevel = 4;

	for (int i = 0; i < SIN_MAX_HELP_NUMBER; i++)
	{
		if (sSinHelp[i].KindFlag)
		{
			sSinHelp[i].ButtonShowFlag = 0;
			haResearch.ButtonShowFlag = 0;

			if (sSinHelp[i].ButtonPosi.x + 18 < pCursorPos.x  && sSinHelp[i].ButtonPosi.x + 18 + 32 > pCursorPos.x && sSinHelp[i].ButtonPosi.y + 7 < pCursorPos.y  && sSinHelp[i].ButtonPosi.y + 7 + 16 > pCursorPos.y)
				sSinHelp[i].ButtonShowFlag = 1;

			if (sSinHelp[i].ScrollMouseDownFlag)
			{
				if (pCursorPos.y > sSinHelp[i].ScrollMAXPosiY_UP - 10 && pCursorPos.y < sSinHelp[i].ScrollMAXPosiY_DOWN + 10)
				{
					sSinHelp[i].ScrollButton.y = pCursorPos.y;
					if (sSinHelp[i].ScrollButton.y < sSinHelp[i].ScrollMAXPosiY_UP)
						sSinHelp[i].ScrollButton.y = sSinHelp[i].ScrollMAXPosiY_UP;
					if (sSinHelp[i].ScrollButton.y > sSinHelp[i].ScrollMAXPosiY_DOWN)
						sSinHelp[i].ScrollButton.y = sSinHelp[i].ScrollMAXPosiY_DOWN;
				}
			}
			if (sSinHelp[i].KindFlag == SIN_HELP_KIND_NORMAL)
			{
				if (sSinHelp[i].PosiX + 300 < pCursorPos.x  && sSinHelp[i].PosiX + 300 + 100 > pCursorPos.x && sSinHelp[i].PosiY + 7 < pCursorPos.y  && sSinHelp[i].PosiY + 7 + 32 > pCursorPos.y)
					GuideHelpFlag = 1;
			}

			if (isDrawClanMenu)
				ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));

			if (sSinHelp[i].KindFlag == SIN_HELP_KIND_WARPGATE)
			{
				if (!sSinWarpGate.ShowFlag)
					ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
			}
			if (sSinHelp[i].KindFlag == SIN_HELP_KIND_INITPOINT)
			{
				if (sinInitPointFlag7 == 0)
					ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
			}
			if (sSinHelp[i].KindFlag == SIN_HELP_KIND_TELEPORT)
			{
				if (sinChar->iLevel < 55) sinTelePortLevel = 3;
				for (int j = 0; j < sinTelePortLevel; j++)
				{
					if (sSinHelp[i].PosiX + 20 < pCursorPos.x  && sSinHelp[i].PosiX + sSinHelp[i].SizeW * 32 > pCursorPos.x && sSinHelp[i].PosiY + 230 + (13 * j) < pCursorPos.y  && sSinHelp[i].PosiY + 230 + (13 * (j + 1)) > pCursorPos.y)
						sinTeleportIndex = j + 1;
				}
			}
			if (sSinHelp[i].KindFlag == SIN_HELP_KIND_TELEPORT_MILTER)
			{
				for (int j = 0; j < 1; j++)
				{
					if (sSinHelp[i].PosiX + 20 < pCursorPos.x  && sSinHelp[i].PosiX + sSinHelp[i].SizeW * 32 > pCursorPos.x && sSinHelp[i].PosiY + 270 + (13 * j) < pCursorPos.y  && sSinHelp[i].PosiY + 270 + (13 * (j + 1)) > pCursorPos.y)
						sinTeleportIndex = j + 1;
				}
			}
			if (sSinHelp[i].KindFlag == SIN_HELP_KIND_C_TELEPORT)
			{
				if (sSinHelp[i].PosiX + 20 < pCursorPos.x  && sSinHelp[i].PosiX + sSinHelp[i].SizeW * 32 > pCursorPos.x && sSinHelp[i].PosiY + 230 + (13 * 3) < pCursorPos.y  && sSinHelp[i].PosiY + 230 + (13 * 4) > pCursorPos.y)
					haC_TeleportIndex = 1;
			}
			if (sSinHelp[i].KindFlag == SIN_HELP_KIND_RESEARCH)
			{
				haResearchIndex = 0;
				if (haResearch.ButtonPosi.x + 18 < pCursorPos.x  && haResearch.ButtonPosi.x + 18 + 32 > pCursorPos.x && haResearch.ButtonPosi.y + 7 < pCursorPos.y  && haResearch.ButtonPosi.y + 7 + 16 > pCursorPos.y)
					haResearch.ButtonShowFlag = 1;

				for (int j = 0; j < sSinHelp[i].LineCnt + 1; j++)
				{
					if (sSinHelp[i].PosiX + 20 < pCursorPos.x  && sSinHelp[i].PosiX + sSinHelp[i].SizeW * 32 > pCursorPos.x && sSinHelp[i].PosiY + 70 + (13 * j) < pCursorPos.y  && sSinHelp[i].PosiY + 70 + (13 * (j + 1)) > pCursorPos.y)
						haResearchIndex = j - j / 8;
				}
			}
			chaQuest.iFuryQuestIndex[0] = 0;

			if (sSinHelp[i].KindFlag == HAQUEST_CODE_FURYOFPHANTOM)
			{
				for (int j = 0; j < MAX_JOBNUM; j++)
				{
					if (sSinHelp[i].PosiX + 20 < pCursorPos.x  && sSinHelp[i].PosiX + sSinHelp[i].SizeW * 20 > pCursorPos.x && sSinHelp[i].PosiY + 236 + (14 * j) - ScrollLineCount * 14 < pCursorPos.y  && sSinHelp[i].PosiY + 236 + (14 * (j + 1)) - ScrollLineCount * 14 > pCursorPos.y)
					{
						if (pCursorPos.y < 340)
							chaQuest.iFuryQuestIndex[0] = j + 1;
					}
				}
			}
			chaPremiumitem.TelePortCore.FieldIndex[0] = 0;
			short Temp = 0;
			//传送卷轴传送
			if (sSinHelp[i].KindFlag == SIN_HELP_KIND_TELEPORT_SCROLL)
			{
				if (chaPremiumitem.TelePortCore.PageIndex == 3)
					Temp = 6;	//选择到第几个
				else
					Temp = 10;
				for (int j = 0; j < Temp; j++)
				{
					if (sSinHelp[i].PosiX + 20 < pCursorPos.x  && sSinHelp[i].PosiX + sSinHelp[i].SizeW * 20 > pCursorPos.x && sSinHelp[i].PosiY + 106 + (14 * j) - ScrollLineCount * 14 < pCursorPos.y  && sSinHelp[i].PosiY + 106 + (14 * (j + 1)) - ScrollLineCount * 14 > pCursorPos.y)
						chaPremiumitem.TelePortCore.FieldIndex[0] = j + 1;
				}
			}
		}
	}
}
/*----------------------------------------------------------------------------*
*							     辆丰
*-----------------------------------------------------------------------------*/
void cSINHELP::Close()
{

}
/*----------------------------------------------------------------------------*
*							   LButtonDown
*-----------------------------------------------------------------------------*/

void cSINHELP::LButtonDown(int x, int y)
{
	ItemData TempItem;

	if (GuideHelpFlag)
	{
		void InitGuideHelp();
		InitGuideHelp();

		for (int i = 0; i < SIN_MAX_HELP_NUMBER; i++)
		{
			if (sSinHelp[i].KindFlag)
			{
				if (sSinHelp[i].KindFlag == SIN_HELP_KIND_NORMAL)
				{
					HelpBoxKindIndex = 0;
					ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
				}
			}
		}
	}

	char strBuff[128];
	int cnt = 0;
	int Tempcnt = 0;
	int	Tempcnt2 = 0;
	int k, p;

	for (int i = 0; i < SIN_MAX_HELP_NUMBER; i++)
	{
		if (sSinHelp[i].KindFlag)
		{
			if (sSinHelp[i].KindFlag == SIN_HELP_KIND_TELEPORT_SCROLL)
			{
				if (chaPremiumitem.TelePortCore.FieldIndex[0])
				{
					HelpBoxKindIndex = 0;
					ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
					chaPremiumitem.TelePortCore.FieldIndex[1] = chaPremiumitem.TelePortCore.FieldIndex[0] + (chaPremiumitem.TelePortCore.PageIndex * 10);
					cMessageBox.ShowMessage3(MESSAGE_TELEPORT_CORE, chaPremiumitem.TelePortCore.FieldName);
					chaPremiumitem.Using_ItemKind = 0;
				}
			}
			if (sSinHelp[i].KindFlag == HAQUEST_CODE_FURYOFPHANTOM)
			{
				if (chaQuest.iFuryQuestIndex[0] && chaQuest.sHaQuest100LV.State == 12)
				{
					HelpBoxKindIndex = 0;
					ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
					chaQuest.iFuryQuestIndex[1] = 0;
					chaQuest.iFuryQuestIndex[1] = chaQuest.iFuryQuestIndex[0];
					chaQuest.showFuryQuestItem();
					chaQuest.sHaQuest100LV.State++;
					break;
				}
			}
			if (sSinHelp[i].KindFlag == SIN_HELP_KIND_RESEARCH)
			{
				if (haResearch.ButtonPosi.x + 18 < pCursorPos.x  && haResearch.ButtonPosi.x + 18 + 32 > pCursorPos.x && haResearch.ButtonPosi.y + 7 < pCursorPos.y  && haResearch.ButtonPosi.y + 7 + 16 > pCursorPos.y)
				{
					cMessageBox.ShowMessage(MESSAGE_THANKS_RESEARCH);
					cSinHelp.SendResearch();
					ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
					break;
				}
				if (haResearchIndex)
				{
					for (k = 0; k < sSinHelp[i].LineCnt - 1; k++)
					{
						wsprintf(strBuff, "%s", sSinHelp[i].szDocBuff[k]);
						cnt = lstrlen(strBuff);

						for (p = 0; p < cnt; p++)
						{
							if (strBuff[p] == '>')
							{
								Tempcnt++;
							}
							if (strBuff[p] == ')')
							{
								if ((haResearchIndex + haResearch.Result[0]) == k)
								{
									haResearch.Result[Tempcnt] = (haResearchIndex + haResearch.Result[0]);
									haResearch.Value[Tempcnt - 1] = atoi(&strBuff[p - 1]);
								}
								if (haResearch.Value[0] == 2)
								{
									haResearch.Result[1 + 1] = 0;
									haResearch.Value[1] = 0;
								}
								if (haResearch.Value[0] == 1)
								{
									haResearch.Result[2 + 1] = 0;
									haResearch.Value[2] = 0;
								}
							}
						}
					}
				}
			}
			//任务传送
			if (sSinHelp[i].KindFlag == SIN_HELP_KIND_TELEPORT)
			{
				if (sinTeleportIndex)
				{
					if (sinTeleportIndex == 4)
					{
						if (MAPLEVEL(12) > sinChar->iLevel)
							break;
					}
					if (cShop.haBuyMoneyCheck(TeleportUseCose[sinTeleportIndex - 1]))
					{
						sinTeleportMoneyIndex = sinTeleportIndex;
						cMessageBox.ShowMessage3(MESSAGE_TELEPORT, sinTeleportDoc[sinTeleportIndex - 1]);
						cSinHelp.NPCTeleportFlag = 0;
						HelpBoxKindIndex = 0;
						ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
						break;
					}
					else
						cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
				}
			}
			if (sSinHelp[i].KindFlag == SIN_HELP_KIND_TELEPORT_MILTER)
			{
				if (sinTeleportIndex)
				{
					sinTeleportMoneyIndex = sinTeleportIndex;
#ifdef ENGLISH_LANGUAGE
					cMessageBox.ShowMessage3(MESSAGE_TELEPORT_DUNGEON, "Endless Tower");
#else
					cMessageBox.ShowMessage3(MESSAGE_TELEPORT_DUNGEON, "无尽之塔");
#endif
					cSinHelp.NPCTeleportFlag = 0;
					HelpBoxKindIndex = 0;
					ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
					break;
				}

			}
			if (sSinHelp[i].KindFlag == SIN_HELP_KIND_C_TELEPORT)
			{
				if (haC_TeleportIndex)
				{
					if (haC_TeleportMoney <= sinChar->iGold)
					{
						cMessageBox.ShowMessage3(MESSAGE_CASTLE_TELEPORT, HaWarpGateName[0]);
						HelpBoxKindIndex = 0;
						ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
						break;
					}
					else
						cMessageBox.ShowMessage(MESSAGE_NOT_ENOUGH_MONEY);
				}
			}

			if (sSinHelp[i].ScrollButton.x < x &&  sSinHelp[i].ScrollButton.x + 16 > x && sSinHelp[i].ScrollButton.y - 7 < y &&  sSinHelp[i].ScrollButton.y + 16 + 7 > y)
				sSinHelp[i].ScrollMouseDownFlag = 1;

			if (sSinHelp[i].ScrollButton.x < x &&  sSinHelp[i].ScrollButton.x + 16 > x && sSinHelp[i].ScrollMAXPosiY_UP < y &&  sSinHelp[i].ScrollMAXPosiY_DOWN > y)
				sSinHelp[i].ScrollButton.y = pCursorPos.y;

			if (sSinHelp[i].ButtonPosi.x - 20 < x &&  sSinHelp[i].ButtonPosi.x + 68 + 20 > x && sSinHelp[i].ButtonPosi.y - 20 < y &&  sSinHelp[i].ButtonPosi.y + 27 + 20 > y)
			{
				if (sSinHelp[i].KindFlag == SIN_HELP_KIND_TELEPORT_SCROLL)
					chaPremiumitem.Using_ItemKind = 0;

				if (sSinHelp[i].KindFlag == SIN_HELP_KIND_TELEPORT)
					cSinHelp.NPCTeleportFlag = 0;

				if (sSinHelp[i].KindFlag == SIN_HELP_KIND_TELEPORT_MILTER)
					cSinHelp.NPCTeleportFlag = 0;

				if (sSinHelp[i].KindFlag == MESSAGE_FALLGAME)
					cSinHelp.NPCTeleportFlag = 0;

				if (sSinHelp[i].KindFlag == HAQUEST_CODE_FURYOFPHANTOM)
				{
					switch (chaQuest.sHaQuest100LV.State)
					{
					case 0:
						cMessageBox.ShowMessage3(MESSAGE_QUEST_100LV, "疯狂幽灵");
						break;
					case 1:
						break;
					case 3:
					case 4:
						if (chaQuest.FuryBattleFlag)
						{
							chaQuest.sHaQuest100LV.State++;
							GAMEMAP->LoadWarpMap(MAPID_PhillaiTown);
							chaQuest.FuryBattleFlag = false;
						}
						else
							cMessageBox.ShowMessage3(MESSAGE_QUEST_100LVBATTLEOK, "");
						break;
					case 5:
						chaQuest.sHaQuest100LV.State = 6;
						chaQuest.showFuryQuest();
						break;
					case 8:
					case 9:
					case 10:
					case 11:
						if (chaQuest.FuryBattleFlag)
						{
							chaQuest.sHaQuest100LV.State++;
							GAMEMAP->LoadWarpMap(MAPID_PhillaiTown);
							chaQuest.FuryBattleFlag = false;
						}
						else
							cMessageBox.ShowMessage3(MESSAGE_QUEST_100LVBATTLEOK, "");
						break;
					case 13:
						if (chaQuest.iFuryQuestIndex[1])
							cMessageBox.ShowMessage3(MESSAGE_QUEST_100LVITEMOK, ha100LVQuestItemName[chaQuest.iFuryQuestIndex[1] - 1]);
						break;
					}

					chaQuest.bFuryQuestFlag = false;
					HelpBoxKindIndex = 0;
					memset(&sSinHelp[i], 0, sizeof(sSINHELP));
					break;
				}
				if (sSinHelp[i].KindFlag == SIN_HELP_KIND_RESEARCH)
				{
					for (int i = 0; i < 10; i++)
					{
						haResearch.Result[i] = 0;
						haResearch.Value[i] = 0;
					}
				}
				// 30级任务
				if (sSinHelp[i].KindFlag == SIN_HELP_KIND_Q_LEVEL30)
				{
					if (sinQuest_Level30.State == 0)
						cMessageBox.ShowMessage3(MESSAGE_QUEST_LEVEL30, "");
					if (sinQuest_Level30.State == 2)
					{
						cSkill.CancelContinueSkill(CHANGE_JOB3_QUEST);
						CheckCharForm();
						sinChar->iStatPoints += 5;
						cMessageBox.ShowMessage(MESSAGE_PLUS_STATE_POINT5);
						sinPlaySound(SIN_SOUND_EAT_POTION2);
						sinQuest_levelLog |= QUESTBIT_LEVEL_30;
						sinQuest_Level30.BackUpCode = sinQuest_Level30.CODE;
						sinQuest_Level30.CODE = 0;
						sinQuest_Level30.State = 3;
						EndQuest_Code(sinQuest_Level30.BackUpCode);
						ReformCharForm();
						SaveGameData();
					}
					HelpBoxKindIndex = 0;
					memset(&sSinHelp[i], 0, sizeof(sSINHELP));
					break;
				}
				//55级任务
				if (sSinHelp[i].KindFlag == SIN_HELP_KIND_Q_LEVEL55)
				{
					if (sinQuest_Level55.State == 0)
						cMessageBox.ShowMessage3(MESSAGE_QUEST_LEVEL55, "");

					if (sinQuest_Level55.State == 2)
					{
						cSkill.CancelContinueSkill(CHANGE_JOB3_QUEST);
						CheckCharForm();
						sinSkill.SkillPoint += 1;
						cMessageBox.ShowMessage(MESSAGE_PLUS_SKILL_POINT);
						sinPlaySound(SIN_SOUND_EAT_POTION2);
						sinQuest_levelLog |= QUESTBIT_LEVEL_55;
						sinQuest_Level55.BackUpCode = sinQuest_Level55.CODE;
						sinQuest_Level55.CODE = 0;
						sinQuest_Level55.State = 3;
						EndQuest_Code(sinQuest_Level55.BackUpCode);
						ReformCharForm();
						SaveGameData();
					}
					HelpBoxKindIndex = 0;
					memset(&sSinHelp[i], 0, sizeof(sSINHELP));
					break;

				}
				if (sSinHelp[i].KindFlag == SIN_HELP_KIND_Q_LEVEL55_2)
				{
					if (sinQuest_Level55_2.State == 0)
						cMessageBox.ShowMessage3(MESSAGE_QUEST_LEVEL55_2, "");
					if (sinQuest_Level55_2.State == 2)
					{
						cSkill.CancelContinueSkill(CHANGE_JOB3_QUEST);
						CheckCharForm();
						sinSkill.SkillPoint += 1;
						cMessageBox.ShowMessage(MESSAGE_PLUS_SKILL_POINT);
						sinPlaySound(SIN_SOUND_EAT_POTION2);
						sinQuest_levelLog |= QUESTBIT_LEVEL_55;
						sinQuest_Level55_2.BackUpCode = sinQuest_Level55_2.CODE;
						sinQuest_Level55_2.CODE = 0;
						sinQuest_Level55_2.State = 3;
						EndQuest_Code(sinQuest_Level55_2.BackUpCode);
						ReformCharForm();
						SaveGameData();
					}
					HelpBoxKindIndex = 0;
					memset(&sSinHelp[i], 0, sizeof(sSINHELP));
					break;
				}
				// 70级任务
				if (sSinHelp[i].KindFlag == SIN_HELP_KIND_Q_LEVEL70)
				{
					if (sinQuest_Level70.State == 0)
						cMessageBox.ShowMessage3(MESSAGE_QUEST_LEVEL70, "");
					if (sinQuest_Level70.State == 2)
					{
						cSkill.CancelContinueSkill(CHANGE_JOB3_QUEST);
						CheckCharForm();
						sinChar->iStatPoints += 5;
						sinSkill.SkillPoint += 1;
						cMessageBox.ShowMessage(MESSAGE_PLUS_POINT_70);
						sinPlaySound(SIN_SOUND_EAT_POTION2);
						sinQuest_levelLog |= QUESTBIT_LEVEL_70;
						sinQuest_Level70.BackUpCode = sinQuest_Level70.CODE;
						sinQuest_Level70.CODE = 0;
						sinQuest_Level70.State = 3;
						EndQuest_Code(sinQuest_Level70.BackUpCode);
						ReformCharForm();
						SaveGameData();
					}
					HelpBoxKindIndex = 0;
					memset(&sSinHelp[i], 0, sizeof(sSINHELP));
					break;
				}
				// 80级任务
				if (sSinHelp[i].KindFlag == SIN_HELP_KIND_Q_LEVEL80)
				{
					if (sinQuest_Level80.State == 0)
						cMessageBox.ShowMessage3(MESSAGE_QUEST_LEVEL80, "");
					if (sinQuest_Level80.State == 2)
					{
						cSkill.CancelContinueSkill(CHANGE_JOB3_QUEST);
						CheckCharForm();
						sinChar->iStatPoints += 5;
						sinSkill.SkillPoint += 2;
						cMessageBox.ShowMessage(MESSAGE_PLUS_POINT_80);
						sinPlaySound(SIN_SOUND_EAT_POTION2);
						sinQuest_levelLog |= QUESTBIT_LEVEL_80;
						sinQuest_Level80.BackUpCode = sinQuest_Level80.CODE;
						sinQuest_Level80.CODE = 0;
						sinQuest_Level80.State = 3;
						EndQuest_Code(sinQuest_Level80.BackUpCode);
						ReformCharForm();
						SaveGameData();
					}
					HelpBoxKindIndex = 0;
					ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
					break;
				}
				if (sSinHelp[i].KindFlag == SIN_HELP_KIND_Q_LEVEL85)
				{
					if (sinQuest_Level85.State == 0)
						cMessageBox.ShowMessage3(MESSAGE_QUEST_LEVEL85, "");
					if (sinQuest_Level85.State == 1)
					{
						if (!cInvenTory.SearchItemCode(sinQT1 | sin08))
							SendQuestCommandToServer(SIN_QUEST_CODE_LEVEL85, 1, 0, 0);
						sinQuest_Level85.State = 2;
						sinQuest_Level85.Monster[0] = 0;
					}
					if (sinQuest_Level85.State == 3)
					{
						cSkill.CancelContinueSkill(CHANGE_JOB3_QUEST);
						CheckCharForm();
						sinQuest_levelLog |= QUESTBIT_LEVEL_85;
						sinQuest_Level85.State = 4;
						sinQuest_Level85.BackUpCode = sinQuest_Level85.CODE;
						sinQuest_Level85.CODE = 0;
						EndQuest_Code(sinQuest_Level85.BackUpCode);
						ReformCharForm();
					}
					HelpBoxKindIndex = 0;
					ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
					break;
				}
				if (sSinHelp[i].KindFlag == SIN_HELP_KIND_Q_LEVEL90)
				{
					if (sinQuest_Level90.State == 0)
						cMessageBox.ShowMessage3(MESSAGE_QUEST_LEVEL90, "");
					if (sinQuest_Level90.State == 2)
					{
						cSkill.CancelContinueSkill(CHANGE_JOB3_QUEST);
						CheckCharForm();
						sinQuest_levelLog |= QUESTBIT_LEVEL_90;
						sinQuest_Level90.State = 3;
						sinQuest_Level90.BackUpCode = sinQuest_Level90.CODE;
						sinQuest_Level90.CODE = 0;
						EndQuest_Code(sinQuest_Level90.BackUpCode);
						ReformCharForm();
						cInvenTory.SetItemToChar();
						if (cInvenTory.SearchItemCode(sinQT1 | sin07) == FALSE)
							SendQuestCommandToServer(SIN_QUEST_CODE_LEVEL90, 1, 0, 0);
					}
					HelpBoxKindIndex = 0;
					ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
				}
				// 80级任务
				if (sSinHelp[i].KindFlag == SIN_HELP_KIND_Q_LEVEL80_2)
				{
					if (NPCFlag == 0)
					{
						if (sinQuest_Level80_2.State == 0)
							cMessageBox.ShowMessage3(MESSAGE_QUEST_LEVEL80_2, "");

						if (sinQuest_Level80_2.State == 3)
						{
							CheckCharForm();
							sinQuest_levelLog |= QUESTBIT_LEVEL_80_2;
							sinQuest_Level80_2.BackUpCode = sinQuest_Level80_2.CODE;
							sinQuest_Level80_2.CODE = 0;
							EndQuest_Code(sinQuest_Level80_2.BackUpCode);
							if (cInvenTory.SearchItemCode(sinQT1 | sin12))
								DeleteQuestItem(sinQT1 | sin12);

							ReformCharStatePoint(sinChar, sinQuest_levelLog, sinFruitStatus[0]);
							ReformCharForm();
							cInvenTory.SetItemToChar();
							sinPlaySound(SIN_SOUND_EAT_POTION2);
							cMessageBox.ShowMessage(MESSAGE_PLUS_POINT_80_2);
							SaveGameData();
						}
					}
					if (NPCFlag == 1)
					{
						if (sinQuest_Level80_2.State == 1)
						{
							sinQuest_Level80_2.Monster[0] = 0;
							sinQuest_Level80_2.Monster[1] = 0;
							lstrcpy(szQuestMonsterName, "BOSS");
							sinSetQuestTimer(SIN_QUEST_CODE_LEVEL80_2);
							sinQuest_Level80_2.State = 2;
							SetQuestBoard();
							SaveGameData();
							HelpBoxKindIndex = 0;
							ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
							break;
						}
						if (sinQuest_Level80_2.State == 2)
						{
							if (cInvenTory.SearchItemCode(sinQT1 | sin09) && cInvenTory.SearchItemCode(sinQT1 | sin10) && cInvenTory.SearchItemCode(sinQT1 | sin11))
							{
								cSkill.CancelContinueSkill(CHANGE_JOB3_QUEST);
								if (cInvenTory.SearchItemCode(sinQT1 | sin12) == FALSE)
									SendQuestCommandToServer(SIN_QUEST_CODE_LEVEL80_2, 1, 0, 0);

#ifdef ENGLISH_LANGUAGE
								cMessageBox.ShowMessageEvent("Received Recommendation Letter      ");
#else
								cMessageBox.ShowMessageEvent("获得了一份介绍信      ");
#endif
								sinPlaySound(SIN_SOUND_EAT_POTION2);

								sinQuest_Level80_2.State = 3;

								DeleteQuestItem(sinQT1 | sin09);
								DeleteQuestItem(sinQT1 | sin10);
								DeleteQuestItem(sinQT1 | sin11);
								SetQuestBoard();
								SaveGameData();
							}
						}
					}

					HelpBoxKindIndex = 0;
					ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
				}

				if (sSinHelp[i].KindFlag == SIN_HELP_KIND_Q_LEVEL90_2)
				{
					if (NPCFlag == 0)
					{
						if (sinQuest_Level90_2.State == 0)
							cMessageBox.ShowMessage3(MESSAGE_QUEST_LEVEL90_2, "");
					}
					if (NPCFlag == 1)
					{
						if (sinQuest_Level90_2.State == 1)
						{
							sinQuest_Level90_2.Kind = GetRandomPos(13, 15);
							sinQuest_Level90_2.Monster[0] = 0;
							sinQuest_Level90_2.Monster[1] = 50;
							sinQuest_Level90_2.State = 2;
							lstrcpy(szQuestMonsterName, sinLevelQuest90_2Mon[sinQuest_Level90_2.Kind - 13]);
							sinSetQuestTimer(SIN_QUEST_CODE_LEVEL90_2);
							cInvenTory.SetItemToChar();
							SetQuestBoard();
						}
						if (sinQuest_Level90_2.State == 3)
						{
							cSkill.CancelContinueSkill(CHANGE_JOB3_QUEST);
							CheckCharForm();
							sinQuest_levelLog |= QUESTBIT_LEVEL_90_2;
							sinQuest_Level90_2.BackUpCode = sinQuest_Level90_2.CODE;
							sinQuest_Level90_2.CODE = 0;
							EndQuest_Code(sinQuest_Level90_2.BackUpCode);
							sinQuest_Level90_2.State = 4;
							ReformCharStatePoint(sinChar, sinQuest_levelLog, sinFruitStatus[0]);
							ReformCharForm();
							cInvenTory.SetItemToChar();
							sinPlaySound(SIN_SOUND_EAT_POTION2);
							cMessageBox.ShowMessage(MESSAGE_PLUS_POINT_90_2);
							SetQuestBoard();
						}
					}
					HelpBoxKindIndex = 0;
					ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
				}

				if (ChangeJobButonCheck2)
				{
					ChangeJobButonCheck2 = 0;
					break;
				}
				if (sSinHelp[i].KindFlag == SIN_HELP_KIND_QUEST)
				{
					if (ChangeJobButonCheck2)
					{
						ChangeJobButonCheck2 = 0;
						break;
					}
					// 1转任务 开始
					if (sinChar->iRank == 0)
					{
						int Race = GetRace(sinChar->iClass);

						switch (Race)
						{
						case BROOD_CODE_TEMPSKRON:
							switch (sinQuest_ChangeJob.State)
							{
							case  0:
								cMessageBox.ShowMessage3(MESSAGE_QUEST, "");
								ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
								break;
							case SIN_QUEST_PROGRESS:
							{
								auto ps = GetCharacterClassData(sinChar->iClass, sinChar->iRank + 1);

								if (ps)
								{
									cMessageBox.ShowMessage3(MESSAGE_CHANGE_JOB, ps->pszName);
									HelpBoxKindIndex = 0;
									ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
								}
							}
								
								break;
							case SIN_QUEST_COMPLETE:
								break;
							}
							break;
						case BROOD_CODE_MORAYION:
							switch (sinQuest_ChangeJob2.State)
							{
							case  0:
								if ((FindLastQuestCode(SIN_QUEST_CODE_CHANGEJOB2_NPC_M) || FindLastQuestCode(SIN_QUEST_CODE_CHANGEJOB2_NPC_D)) && sinChar->iRank < 1)
								{
									auto ps = GetCharacterClassData(sinChar->iClass, sinChar->iRank + 1);

									if (ps)
									{
										cMessageBox.ShowMessage3(MESSAGE_CHANGE_JOB, ps->pszName);
										HelpBoxKindIndex = 0;
									}									
								}
								else
									cMessageBox.ShowMessage3(MESSAGE_QUEST_CHANGEJOB_MORAYOIN, "");
								memset(&sSinHelp[i], 0, sizeof(sSINHELP));
								break;
							case SIN_QUEST_PROGRESS:
								break;
							case 4:
								break;
							}
							break;
						}
					}
					if (sinChar->iRank == 1)
					{
						switch (sinQuest_ChangeJob3.State)
						{
						case 0:
							cMessageBox.ShowMessage3(MESSAGE_QUEST_CHANGEJOB3, "");
							break;
						case 1:
							break;
						case 2:
							switch (sinChar->iClass)
							{
							case CHARACTERCLASS_Fighter:
								TempItem.sBaseItemID = (sinWA1 | sin08);
								break;
							case CHARACTERCLASS_Mechanician:
								TempItem.sBaseItemID = (sinWC1 | sin08);
								break;
							case CHARACTERCLASS_Archer:
								TempItem.sBaseItemID = (sinWS1 | sin10);
								break;
							case CHARACTERCLASS_Pikeman:
								TempItem.sBaseItemID = (sinWP1 | sin09);
								break;
							case CHARACTERCLASS_Atalanta:
								TempItem.sBaseItemID = (sinWT1 | sin09);
								break;
							case CHARACTERCLASS_Knight:
								TempItem.sBaseItemID = (sinWS2 | sin10);
								break;
							case CHARACTERCLASS_Magician:
								TempItem.sBaseItemID = (sinWM1 | sin09);
								break;
							case CHARACTERCLASS_Priestess:
								TempItem.sBaseItemID = (sinWM1 | sin09);
								break;
							case CHARACTERCLASS_Assassin:
								TempItem.sBaseItemID = (sinWD1 | sin09);
								break;
							case CHARACTERCLASS_Shaman:
								TempItem.sBaseItemID = (sinWN1 | sin09);
								break;
							}
							cInvenTory.ChangeSpecialItem(2);

							if (cInvenTory.CheckInvenEmpty(&TempItem))
							{
								if (sinChar->sWeight.sMin + 35 <= sinChar->sWeight.sMax)
								{
									SendWingQuestItem();
									sinQuest_ChangeJob3.State = 3;
									DeleteQuestItem((sinQT1 | sin06));
									StartQuest_Code(sinQuest_ChangeJob3.CODE);
								}
								else
								{
									sinQuest_ChangeJob3.State = 1;
									cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
								}
							}
							else
							{
								sinQuest_ChangeJob3.State = 1;
								cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
							}
							break;
						case 3:
							break;
						case 4:
						{
							auto ps = GetCharacterClassData(sinChar->iClass, sinChar->iRank + 1);

							if (ps)
							{
								cMessageBox.ShowMessage3(MESSAGE_CHANGE_JOB, ps->pszName);
								HelpBoxKindIndex = 0;
								sinChar->wVersion[1] = 0;
							}
						}
							break;
						}
						HelpBoxKindIndex = 0;
						memset(&sSinHelp[i], 0, sizeof(sSINHELP));
					}
					if (sinQuest_ChangeJob3.CODE && sinChar->iRank == 2 && sinQuest_ChangeJob3.State == 6)
					{
						sinQuest_ChangeJob3.BackUpCode = sinQuest_ChangeJob3.CODE;
						sinChar->wVersion[1] = 0;
						sinQuest_ChangeJob3.CODE = 0;
						sinQuest_ChangeJob3.State = 0;
						EndQuest_Code(sinQuest_ChangeJob3.BackUpCode);
						cMessageBox.ShowMessage(MESSAGE_INCRE_LIFE15);
						cInvenTory.SetItemToChar();
						HelpBoxKindIndex = 0;
						memset(&sSinHelp[i], 0, sizeof(sSINHELP));
					}
					if (sSinHelp[i].KindFlag == SIN_HELP_KIND_QUEST && sinChar->iRank == 2)
					{
						switch (sinQuest_ChangeJob4.State)
						{
						case 0:
							if (sinQuest_ChangeJob4.Monster[1])
							{
								sinQuest_ChangeJob4.State = 1;
								sinChangeJob4MonSet(&sinQuest_ChangeJob4);
								SetQuestBoard();
							}
							else
								cMessageBox.ShowMessage3(MESSAGE_CHANGE_JOB4, "");
							break;
						case 2:
							sinChangeJob4MonSet(&sinQuest_ChangeJob4);
							sinQuest_ChangeJob4.State = 3;
							SaveGameData();
							SetQuestBoard();

							break;
						case 4:
						case 7:
							sinChangeJob4MonSet(&sinQuest_ChangeJob4);
							sinQuest_ChangeJob4.State = 5;
							SetQuestBoard();
							break;
						case 6:
							if (MouseItem.bValid)
								return;
							DeleteQuestItem(sinQT1 | sin13);
							sinQuest_ChangeJob4.State = 7;
							Start_QuestArena(SIN_QUEST_CODE_CHANGEJOB4, 0, 0);
							break;
						case 8:
						{
							auto ps = GetCharacterClassData(sinChar->iClass, sinChar->iRank + 1);

							if (ps)
							{
								cMessageBox.ShowMessage3(MESSAGE_CHANGE_JOB4_2, ps->pszName);
							}
						}
							break;
						}
						HelpBoxKindIndex = 0;
						ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
					}
				}

				if (sSinHelp[i].KindFlag == SIN_HELP_KIND_QUEST_WING)
				{
#ifdef ENGLISH_LANGUAGE
					switch (WingItemQuestIndex)
					{
					case 0:
						cMessageBox.ShowMessage3(MESSAGE_RECVITEM, "Metal Wing");
						break;
					case 1:
						cMessageBox.ShowMessage3(MESSAGE_RECVITEM, "Silver Wing");
						break;
					case 2:
						cMessageBox.ShowMessage3(MESSAGE_RECVITEM, "Gold Wing");
						break;
					case 3:
						cMessageBox.ShowMessage3(MESSAGE_RECVITEM, "Diamond Wing");
						break;
					case 4:
						cMessageBox.ShowMessage3(MESSAGE_RECVITEM, "Chaos Wing");
						break;
					case 5:
						cMessageBox.ShowMessage3(MESSAGE_RECVITEM, "Extreme Wing");
						break;
					}
#else
					switch (WingItemQuestIndex)
					{
					case 0:
						cMessageBox.ShowMessage3(MESSAGE_RECVITEM, "金属之翼");
						break;
					case 1:
						cMessageBox.ShowMessage3(MESSAGE_RECVITEM, "银色之翼");
						break;
					case 2:
						cMessageBox.ShowMessage3(MESSAGE_RECVITEM, "黄金之翼");
						break;
					case 3:
						cMessageBox.ShowMessage3(MESSAGE_RECVITEM, "大地之翼");
						break;
					case 4:
						cMessageBox.ShowMessage3(MESSAGE_RECVITEM, "混乱之翼");
						break;
					case 5:
						cMessageBox.ShowMessage3(MESSAGE_RECVITEM, "迷失之翼");
						break;
					}
#endif
					ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
				}
				switch (HelpBoxKindIndex)
				{
				case SIN_HELP:
					if (sSinHelp[i].KindFlag == SIN_HELP_KIND_NORMAL)
					{
						HelpBoxKindIndex = 0;
						ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
					}
					break;
				case SIN_CHANGEJOB_MESSAGE:
					break;
				case SIN_EVENT_SMASHTV:
					if (sSinHelp[i].KindFlag == SIN_HELP_KIND_SMASHTV)
					{
						cMessageBox.ShowMessage3(MESSAGE_EVENT_SMASHTV, "");
						HelpBoxKindIndex = 0;
						ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
					}
					break;
				case SIN_MESSAGE_DEFAULT:
					HelpBoxKindIndex = 0;
					ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
					break;
				case SIN_POST_BOX:
					HelpBoxKindIndex = 0;
					ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
					break;
				case SIN_SOD:
					HelpBoxKindIndex = 0;
					ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
					break;
				}

				ItemData TempItem;
				TempItem.iWidth = ITEMSIZE * 2;
				TempItem.iHeight = ITEMSIZE * 4;
				TempItem.sItem.iWeight = 60;
				TempItem.bValid = 1;

				if (sSinHelp[i].KindFlag == HAQUEST_CODE_ELEMENTARY_A)
				{
					if (NPCFlag == 0)
					{
						if (chaQuest.sHaQuestElementary[Quest_A].State == 0)
							cMessageBox.ShowMessage3(MESSAGE_QUEST_ElementaryA, "");

						if (chaQuest.sHaQuestElementary[Quest_A].State == 2)
						{
							SendQuestCommandToServer(HAQUEST_CODE_ELEMENTARY_A, 2, 0, 0);
							haElementaryQuestLog |= QUESTBIT_ELEMENTARY_A;
							chaQuest.sHaQuestElementary[Quest_A].BackUpCode = chaQuest.sHaQuestElementary[Quest_A].CODE;
							chaQuest.sHaQuestElementary[Quest_A].CODE = 0;
							chaQuest.sHaQuestElementary[Quest_A].State = 3;
							cMessageBox.ShowMessageEvent("Received 50.000 Gold    ");
							sinPlaySound(SIN_SOUND_EAT_POTION2);
							EndQuest_Code(chaQuest.sHaQuestElementary[Quest_A].BackUpCode);
							SaveGameData();
						}
					}
					if (NPCFlag == 1)
					{
						if (chaQuest.sHaQuestElementary[Quest_A].State == 1)
						{
							DeleteQuestItem(sinQT1 | sin14);
							chaQuest.sHaQuestElementary[Quest_A].State = 2;
						}
					}
					HelpBoxKindIndex = 0;
					ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
					break;

				}
				if (sSinHelp[i].KindFlag == HAQUEST_CODE_ELEMENTARY_B)
				{
					if (chaQuest.sHaQuestElementary[Quest_B].State == 0)
						cMessageBox.ShowMessage3(MESSAGE_QUEST_ElementaryB, "");

					if (chaQuest.sHaQuestElementary[Quest_B].State == 1)
					{
						if (cInvenTory.SearchItemCode(sinQT1 | sin16))
						{
							DeleteQuestItem(sinQT1 | sin16);
							cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
							SendQuestCommandToServer(HAQUEST_CODE_ELEMENTARY_B, 1, 0, 0);
							haElementaryQuestLog |= QUESTBIT_ELEMENTARY_B;
							chaQuest.sHaQuestElementary[Quest_B].BackUpCode = chaQuest.sHaQuestElementary[Quest_B].CODE;
							chaQuest.sHaQuestElementary[Quest_B].CODE = 0;
							chaQuest.sHaQuestElementary[Quest_B].State = 2;
							cMessageBox.ShowMessageEvent("Received 100.000 Gold     ");
							sinPlaySound(SIN_SOUND_EAT_POTION2);
							EndQuest_Code(chaQuest.sHaQuestElementary[Quest_B].BackUpCode);
							SaveGameData();
						}
					}
					HelpBoxKindIndex = 0;
					ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
					break;
				}
				if (sSinHelp[i].KindFlag == HAQUEST_CODE_ELEMENTARY_C)
				{
					if (chaQuest.sHaQuestElementary[Quest_C].State == 0)
						cMessageBox.ShowMessage3(MESSAGE_QUEST_ElementaryC, "");

					if (chaQuest.sHaQuestElementary[Quest_C].State == 2)
					{
						cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
						SendQuestCommandToServer(HAQUEST_CODE_ELEMENTARY_C, 1, 0, 0);
						haElementaryQuestLog |= QUESTBIT_ELEMENTARY_C;
						chaQuest.sHaQuestElementary[Quest_C].BackUpCode = chaQuest.sHaQuestElementary[Quest_C].CODE;
						chaQuest.sHaQuestElementary[Quest_C].CODE = 0;
						chaQuest.sHaQuestElementary[Quest_C].State = 3;
						cMessageBox.ShowMessageEvent("Received 250.000 Gold    ");
						sinPlaySound(SIN_SOUND_EAT_POTION2);
						EndQuest_Code(chaQuest.sHaQuestElementary[Quest_C].BackUpCode);
						SaveGameData();
					}
					HelpBoxKindIndex = 0;
					ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
					break;
				}
				if (sSinHelp[i].KindFlag == HAQUEST_CODE_ELEMENTARY_D)
				{
					if (NPCFlag == 0)
					{
						if (chaQuest.sHaQuestElementary[Quest_D].State == 0)
							cMessageBox.ShowMessage3(MESSAGE_QUEST_ElementaryD, "");

						if (chaQuest.sHaQuestElementary[Quest_D].State == 1)
						{
							if (cInvenTory.SearchItemCode(sinQT1 | sin15) == FALSE)
								SendQuestCommandToServer(HAQUEST_CODE_ELEMENTARY_D, 1, 0, 0);
							szQuestMonsterName[0] = '\0';
							chaQuest.sHaQuestElementary[Quest_D].Monster[0] = 0;
							chaQuest.sHaQuestElementary[Quest_D].Monster[1] = 0;
							chaQuest.sHaQuestElementary[Quest_D].State = 2;
							chaQuest.haSetQuestTimer(180);
						}
					}
					if (NPCFlag == 1)
					{
						if (chaQuest.sHaQuestElementary[Quest_D].State == 2)
						{
							if (cSkill.SearchContiueSkill(CHANGE_ELEMENTARY_QUEST) && cInvenTory.SearchItemCode(sinQT1 | sin15))
							{
								cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
								DeleteQuestItem(sinQT1 | sin15);
								SendQuestCommandToServer(HAQUEST_CODE_ELEMENTARY_D, 2, 0, 0);
								haElementaryQuestLog |= QUESTBIT_ELEMENTARY_D;
								chaQuest.sHaQuestElementary[Quest_D].BackUpCode = chaQuest.sHaQuestElementary[Quest_D].CODE;
								chaQuest.sHaQuestElementary[Quest_D].CODE = 0;
								chaQuest.sHaQuestElementary[Quest_D].State = 3;
								cMessageBox.ShowMessageEvent("Received 500.000 Gold    ");
								sinPlaySound(SIN_SOUND_EAT_POTION2);
								EndQuest_Code(chaQuest.sHaQuestElementary[Quest_D].BackUpCode);
								SaveGameData();
							}
							else
							{
								chaQuest.sHaQuestElementary[Quest_D].State = 1;
								cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
							}
						}
					}
					HelpBoxKindIndex = 0;
					memset(&sSinHelp[i], 0, sizeof(sSINHELP));
					break;
				}
				//25级任务
				if (sSinHelp[i].KindFlag == HAQUEST_CODE_ELEMENTARY_E)
				{
					if (chaQuest.sHaQuestElementary[Quest_E].State == 0)
						cMessageBox.ShowMessage3(MESSAGE_QUEST_ElementaryE, "");
					if (chaQuest.sHaQuestElementary[Quest_E].State == 2)
					{
						cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
						SendQuestCommandToServer(HAQUEST_CODE_ELEMENTARY_E, 1, 0, 0);
						haElementaryQuestLog |= QUESTBIT_ELEMENTARY_E;
						chaQuest.sHaQuestElementary[Quest_E].BackUpCode = chaQuest.sHaQuestElementary[Quest_E].CODE;
						chaQuest.sHaQuestElementary[Quest_E].CODE = 0;
						chaQuest.sHaQuestElementary[Quest_E].State = 3;
						cMessageBox.ShowMessageEvent("Received 1.000.000 EXP    ");
						sinPlaySound(SIN_SOUND_EAT_POTION2);
						EndQuest_Code(chaQuest.sHaQuestElementary[Quest_E].BackUpCode);
						SaveGameData();
					}
					HelpBoxKindIndex = 0;
					memset(&sSinHelp[i], 0, sizeof(sSINHELP));
					break;
				}
				if (sSinHelp[i].KindFlag == HAQUEST_CODE_ELEMENTARY_F)
				{
					if (chaQuest.sHaQuestElementary[Quest_F].State == 0)
						cMessageBox.ShowMessage3(MESSAGE_QUEST_ElementaryF, "");
					if (chaQuest.sHaQuestElementary[Quest_F].State == 2)
					{
						cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
						SendQuestCommandToServer(HAQUEST_CODE_ELEMENTARY_F, 1, 0, 0);
						haElementaryQuestLog |= QUESTBIT_ELEMENTARY_F;
						chaQuest.sHaQuestElementary[Quest_F].BackUpCode = chaQuest.sHaQuestElementary[Quest_F].CODE;
						chaQuest.sHaQuestElementary[Quest_F].CODE = 0;
						chaQuest.sHaQuestElementary[Quest_F].State = 3;
#ifdef ENGLISH_LANGUAGE
						cMessageBox.ShowMessageEvent("Received 1.000.000 Gold    ");
#else
						cMessageBox.ShowMessageEvent("获得了 1.000.000 金钱    ");
#endif
						sinPlaySound(SIN_SOUND_EAT_POTION2);
						EndQuest_Code(chaQuest.sHaQuestElementary[Quest_F].BackUpCode);
						SaveGameData();
					}
					HelpBoxKindIndex = 0;
					memset(&sSinHelp[i], 0, sizeof(sSINHELP));
					break;
				}
				if (sSinHelp[i].KindFlag == HAQUEST_CODE_ELEMENTARY_G)
				{
					if (chaQuest.sHaQuestElementary[Quest_G].State == 0)
						cMessageBox.ShowMessage3(MESSAGE_QUEST_ElementaryG, "");
					if (chaQuest.sHaQuestElementary[Quest_G].State == 2)
					{
						if (sinChar->sWeight.sMin + 2 > sinChar->sWeight.sMax)
						{
							cMessageBox.ShowMessage(MESSAGE_OVER_WEIGHT);
							HelpBoxKindIndex = 0;
							ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
							break;
						}
						if (cInvenTory.CheckSetEmptyArea(&TempItem))
						{
							cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
							SendQuestCommandToServer(HAQUEST_CODE_ELEMENTARY_G, 1, 0, 0);
							haElementaryQuestLog |= QUESTBIT_ELEMENTARY_G;
							cMessageBox.ShowMessageEvent("Received 5.000.000 EXP and crystal    ");
							sinPlaySound(SIN_SOUND_EAT_POTION2);
							chaQuest.sHaQuestElementary[Quest_G].BackUpCode = chaQuest.sHaQuestElementary[Quest_G].CODE;
							chaQuest.sHaQuestElementary[Quest_G].CODE = 0;
							chaQuest.sHaQuestElementary[Quest_G].State = 3;
							EndQuest_Code(chaQuest.sHaQuestElementary[Quest_G].BackUpCode);
							SaveGameData();
						}
						else
						{
							cMessageBox.ShowMessage(MESSAGE_OVER_SPACE);
							HelpBoxKindIndex = 0;
							ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
							break;
						}
					}
					HelpBoxKindIndex = 0;
					ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
					break;
				}
				if (sSinHelp[i].KindFlag == HAQUEST_CODE_ELEMENTARY_H)
				{
					if (chaQuest.sHaQuestElementary[Quest_H].State == 0)
						cMessageBox.ShowMessage3(MESSAGE_QUEST_ElementaryH, "");
					if (chaQuest.sHaQuestElementary[Quest_H].State == 2)
					{
						cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
						SendQuestCommandToServer(HAQUEST_CODE_ELEMENTARY_H, 1, 0, 0);
						haElementaryQuestLog |= QUESTBIT_ELEMENTARY_H;
						chaQuest.sHaQuestElementary[Quest_H].BackUpCode = chaQuest.sHaQuestElementary[Quest_H].CODE;
						chaQuest.sHaQuestElementary[Quest_H].CODE = 0;
						chaQuest.sHaQuestElementary[Quest_H].State = 3;
#ifdef ENGLISH_LANGUAGE
						cMessageBox.ShowMessageEvent("Received Gold Bag        ");
#else
						cMessageBox.ShowMessageEvent("获得了钱袋        ");
#endif
						sinPlaySound(SIN_SOUND_EAT_POTION2);
						EndQuest_Code(chaQuest.sHaQuestElementary[Quest_H].BackUpCode);
						SaveGameData();
					}
					HelpBoxKindIndex = 0;
					ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
					break;
				}
				if (sSinHelp[i].KindFlag == HAQUEST_CODE_ELEMENTARY_I)
				{
					if (chaQuest.sHaQuestElementary[Quest_I].State == 0)
						cMessageBox.ShowMessage3(MESSAGE_QUEST_ElementaryI, "");
					if (chaQuest.sHaQuestElementary[Quest_I].State == 2)
					{
						cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
						SendQuestCommandToServer(HAQUEST_CODE_ELEMENTARY_I, 1, 0, 0);
						haElementaryQuestLog |= QUESTBIT_ELEMENTARY_I;
						chaQuest.sHaQuestElementary[Quest_I].BackUpCode = chaQuest.sHaQuestElementary[Quest_I].CODE;
						chaQuest.sHaQuestElementary[Quest_I].CODE = 0;
						chaQuest.sHaQuestElementary[Quest_I].State = 3;
#ifdef ENGLISH_LANGUAGE
						cMessageBox.ShowMessageEvent("Received 250.000.000 EXP     ");
#else
						cMessageBox.ShowMessageEvent("获得了 250.000.000 经验     ");
#endif
						sinPlaySound(SIN_SOUND_EAT_POTION2);
						EndQuest_Code(chaQuest.sHaQuestElementary[Quest_I].BackUpCode);
						SaveGameData();
					}
					HelpBoxKindIndex = 0;
					ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
					break;
				}
				if (sSinHelp[i].KindFlag == HAQUEST_CODE_ELEMENTARY_J)
				{
					if (chaQuest.sHaQuestElementary[Quest_J].State == 0)
						cMessageBox.ShowMessage3(MESSAGE_QUEST_ElementaryJ, "");
					if (chaQuest.sHaQuestElementary[Quest_J].State == 2)
					{
						cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
						SendQuestCommandToServer(HAQUEST_CODE_ELEMENTARY_J, 1, 0, 0);
						haElementaryQuestLog |= QUESTBIT_ELEMENTARY_J;
						chaQuest.sHaQuestElementary[Quest_J].BackUpCode = chaQuest.sHaQuestElementary[Quest_J].CODE;
						chaQuest.sHaQuestElementary[Quest_J].CODE = 0;
						chaQuest.sHaQuestElementary[Quest_J].State = 3;
#ifdef ENGLISH_LANGUAGE
						cMessageBox.ShowMessageEvent("Received 500.000.000 EXP     ");
#else
						cMessageBox.ShowMessageEvent("获得了 500.000.000 经验     ");
#endif
						sinPlaySound(SIN_SOUND_EAT_POTION2);
						EndQuest_Code(chaQuest.sHaQuestElementary[Quest_J].BackUpCode);
						SaveGameData();
					}
					HelpBoxKindIndex = 0;
					ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
					break;
				}
				if (sSinHelp[i].KindFlag == HAQUEST_CODE_ELEMENTARY_K)
				{
					if (chaQuest.sHaQuestElementary[Quest_K].State == 0)
						cMessageBox.ShowMessage3(MESSAGE_QUEST_ElementaryK, "");
					if (chaQuest.sHaQuestElementary[Quest_K].State == 2)
					{
						cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
						SendQuestCommandToServer(HAQUEST_CODE_ELEMENTARY_K, 1, 0, 0);
						haElementaryQuestLog |= QUESTBIT_ELEMENTARY_K;
						chaQuest.sHaQuestElementary[Quest_K].BackUpCode = chaQuest.sHaQuestElementary[Quest_K].CODE;
						chaQuest.sHaQuestElementary[Quest_K].CODE = 0;
						chaQuest.sHaQuestElementary[Quest_K].State = 2;
#ifdef ENGLISH_LANGUAGE
						cMessageBox.ShowMessageEvent("Received 2.000.000.000 EXP     ");
#else
						cMessageBox.ShowMessageEvent("获得了 2.000.000.000 经验     ");
#endif
						sinPlaySound(SIN_SOUND_EAT_POTION2);
						EndQuest_Code(chaQuest.sHaQuestElementary[Quest_K].BackUpCode);
						SaveGameData();
					}
					HelpBoxKindIndex = 0;
					ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
					break;
				}
				if (sSinHelp[i].KindFlag == HAQUEST_CODE_ELEMENTARY_L)
				{
					if (chaQuest.sHaQuestElementary[Quest_L].State == 0)
						cMessageBox.ShowMessage3(MESSAGE_QUEST_ElementaryL, "");

					if (chaQuest.sHaQuestElementary[Quest_L].State == 1)
					{
						if (cInvenTory.SearchItemCode(sinQT1 | sin19))
						{
							DeleteQuestItem(sinQT1 | sin19);
							SendQuestCommandToServer(HAQUEST_CODE_ELEMENTARY_L, 1, 0, 0);
							haElementaryQuestLog |= QUESTBIT_ELEMENTARY_L;
							chaQuest.sHaQuestElementary[Quest_L].BackUpCode = chaQuest.sHaQuestElementary[Quest_L].CODE;
							chaQuest.sHaQuestElementary[Quest_L].CODE = 0;
							chaQuest.sHaQuestElementary[Quest_L].State = 2;
#ifdef ENGLISH_LANGUAGE
							cMessageBox.ShowMessageEvent("Received 250.000.000 EXP     ");
#else
							cMessageBox.ShowMessageEvent("获得了 2.500.000.000 经验     ");
#endif
							sinPlaySound(SIN_SOUND_EAT_POTION2);
							EndQuest_Code(chaQuest.sHaQuestElementary[Quest_L].BackUpCode);
							SaveGameData();
						}
					}
				}
				HelpBoxKindIndex = 0;
				ZeroMemory(&sSinHelp[i], sizeof(sSINHELP));
			}
		}
		break;
	}
}
void cSINHELP::LButtonUp(int x, int y)
{
	for (int i = 0; i < SIN_MAX_HELP_NUMBER; i++)
	{
		if (sSinHelp[i].KindFlag)
		{
			if (sSinHelp[i].ScrollMouseDownFlag)
				sSinHelp[i].ScrollMouseDownFlag = 0;
		}
	}
}
void cSINHELP::RButtonDown(int x, int y)
{

}
void cSINHELP::RButtonUp(int x, int y)
{

}

int KeyFlag = 0;

void cSINHELP::KeyDown()
{
	if (SETTINGHANDLE->Get().bDebugMode)
	{
		if (sinGetKeyClick('6'))
			memset(&sSinHelp, 0, sizeof(sSINHELP) * 10);

		if (sinGetKeyClick('7'))
		{
			for (int i = 0; i < SIN_MAX_HELP_NUMBER; i++)
			{
				if (sSinHelp[i].KindFlag)
					sSinHelp[i].ScrollButton.y++;
			}
		}
	}
	sinGetKeyScrollDown();
}
void sinCopyText(char to[], char from[])
{
	int i = 0;
	int j = 0;
	int cnt = lstrlen(from);
	while (cnt > j)
	{
		if (from[j] == '$')
		{

		}
		else
		{
			to[i] = from[j];
			i++;
		}
		j++;
	}
}

// 帮助文字渲染
void cSINHELP::DrawText()
{
	int sinTest5 = 0;
	int Len = 0;
	int cnt = 0;
	char strBuff[1024];
	char strBuff2[1024];

	DWORD Color = D3DCOLOR_XRGB(255, 255, 255);

	int i, j, tHeight, TempLine, TempLine2, TempLine3, TempLine4;

	for (i = 0; i < SIN_MAX_HELP_NUMBER; i++)
	{
		if (sSinHelp[i].KindFlag)
		{
			tHeight = (sSinHelp[i].SizeH - 2) * 32 / 15;
			TempLine = sSinHelp[i].ScrollButton.y - (sSinHelp[i].PosiY + 32 + 7);

			TempLine2 = sSinHelp[i].ScrollMAXPosiY_DOWN - sSinHelp[i].ScrollMAXPosiY_UP;
			TempLine3 = (int)(((float)TempLine / (float)TempLine2)*100.0f);
			TempLine4 = (int)((float)(sSinHelp[i].LineCnt - ((float)tHeight - 1.0f)) / 100.0f *(float)TempLine3);

			if (sSinHelp[i].LineCnt > 21)
				TempLine4 -= 7;
			if (TempLine4 < 0)
				TempLine4 = 0;

			ScrollLineCount = TempLine4;

			haResearch.Number = 0;
			//传送
			if (sSinHelp[i].KindFlag == SIN_HELP_KIND_TELEPORT_SCROLL)
			{
				for (j = 0; j < tHeight - 1; j++)
				{
					if (sSinHelp[i].szDocBuff[j + TempLine4])
					{
						wsprintf(strBuff, "%s", sSinHelp[i].szDocBuff[j + TempLine4]);
						cnt = lstrlen(strBuff);

						for (int p = 0; p < cnt; p++)
						{
							if (strBuff[p] == '.')
							{
								if (atoi(&strBuff[p - 1]) == chaPremiumitem.TelePortCore.FieldIndex[0] - 1 && chaPremiumitem.TelePortCore.FieldIndex[0] != 0)
								{
									Color = D3DCOLOR_XRGB(255, 100, 45);
									lstrcpy(chaPremiumitem.TelePortCore.FieldName, &strBuff[p + 1]);
								}
								else
									Color = D3DCOLOR_XRGB(240, 240, 240);
							}

						}
						dsTextLineOut(0, sSinHelp[i].PosiX + 30, sSinHelp[i].PosiY + 66 + (15 * j), strBuff, lstrlen(strBuff), Color);
					}
					else
						sinTest5 = 1;
				}
			}
			//100LV 任务
			else if (sSinHelp[i].KindFlag == HAQUEST_CODE_FURYOFPHANTOM)
			{
				for (j = 0; j < tHeight - 1; j++)
				{
					if (sSinHelp[i].szDocBuff[j + TempLine4])
					{
						wsprintf(strBuff, "%s", sSinHelp[i].szDocBuff[j + TempLine4]);
						cnt = lstrlen(strBuff);

						for (int p = 0; p < cnt; p++)
						{
							if (strBuff[p] == '*')
							{
								if (atoi(&strBuff[p + 1]) == chaQuest.iFuryQuestIndex[0])
									Color = D3DCOLOR_XRGB(255, 100, 45);
								else
									Color = D3DCOLOR_XRGB(240, 240, 240);
							}
						}

						int font = 0;

						if (chaQuest.iFuryQuestIndex[1])
						{
							if (haSearchString(strBuff, '['))
							{
								font = 1;
								Color = D3DCOLOR_XRGB(128, 255, 128);
							}
							else
								Color = D3DCOLOR_XRGB(240, 240, 240);
						}

						dsTextLineOut(font, sSinHelp[i].PosiX + 30, sSinHelp[i].PosiY + 66 + (15 * j), strBuff, lstrlen(strBuff), Color);

					}
					else
						sinTest5 = 1;
				}
			}
			else if (sSinHelp[i].KindFlag == SIN_HELP_KIND_RESEARCH)
			{
				for (j = 0; j < tHeight - 1; j++)
				{
					if (sSinHelp[i].szDocBuff[j + TempLine4])
					{
						haResearch.Result[0] = TempLine4;
						wsprintf(strBuff, "%s", sSinHelp[i].szDocBuff[j + TempLine4]);
						cnt = lstrlen(strBuff);

						for (int p = 0; p < cnt; p++)
						{
							if (strBuff[p] == '>')
								haResearch.Number++;
						}
						if (j > 1)
						{
							if (haResearch.Result[1] - TempLine4 == j)
								Color = D3DCOLOR_XRGB(255, 100, 45);
							else if (haResearch.Result[2] - TempLine4 == j)
								Color = D3DCOLOR_XRGB(255, 100, 45);
							else if (haResearch.Result[3] - TempLine4 == j)
								Color = D3DCOLOR_XRGB(255, 100, 45);
							else
								Color = D3DCOLOR_XRGB(255, 255, 255);
						}
						dsTextLineOut(0, sSinHelp[i].PosiX + 30, sSinHelp[i].PosiY + 66 + (15 * j), strBuff, lstrlen(strBuff), Color);

					}
					else
						sinTest5 = 1;
				}
			}
			else if (sSinHelp[i].KindFlag == SIN_HELP_KIND_TELEPORT)
			{
				for (j = 0; j < tHeight - 1; j++)
				{
					if (sSinHelp[i].szDocBuff[j + TempLine4])
					{
						wsprintf(strBuff, "%s", sSinHelp[i].szDocBuff[j + TempLine4]);
						if (sinTeleportIndex + 10 == j)
							Color = D3DCOLOR_XRGB(255, 171, 45);
						else
							Color = D3DCOLOR_XRGB(255, 255, 255);

						if (sinChar->iLevel < MAPLEVEL(12) && j == 14)
							Color = D3DCOLOR_XRGB(128, 128, 128);

						dsTextLineOut(0, sSinHelp[i].PosiX + 30, sSinHelp[i].PosiY + 66 + (15 * j), strBuff, lstrlen(strBuff), Color);
					}
					else
						sinTest5 = 1;
				}
			}
			else if (sSinHelp[i].KindFlag == SIN_HELP_KIND_TELEPORT_MILTER)
			{
				for (j = 0; j < tHeight - 1; j++)
				{
					if (sSinHelp[i].szDocBuff[j + TempLine4])
					{
						wsprintf(strBuff, "%s", sSinHelp[i].szDocBuff[j + TempLine4]);
						if (sinTeleportIndex + 13 == j)
							Color = D3DCOLOR_XRGB(255, 171, 45);
						else
							Color = D3DCOLOR_XRGB(255, 255, 255);

						if (sinChar->iLevel < MAPLEVEL(12) && j == 14)
							Color = D3DCOLOR_XRGB(128, 128, 128);
						dsTextLineOut(0, sSinHelp[i].PosiX + 30, sSinHelp[i].PosiY + 66 + (15 * j), strBuff, lstrlen(strBuff), Color);
					}
					else
						sinTest5 = 1;
				}
			}
			else  if (sSinHelp[i].KindFlag == SIN_HELP_KIND_C_TELEPORT)
			{
				for (j = 0; j < tHeight - 1; j++)
				{
					if (sSinHelp[i].szDocBuff[j + TempLine4])
					{
						wsprintf(strBuff, "%s", sSinHelp[i].szDocBuff[j + TempLine4]);
						if (haC_TeleportIndex + 13 == j)
							Color = D3DCOLOR_XRGB(255, 171, 45);
						else
							Color = D3DCOLOR_XRGB(255, 255, 255);

						dsTextLineOut(0, sSinHelp[i].PosiX + 30, sSinHelp[i].PosiY + 66 + (15 * j), strBuff, lstrlen(strBuff), Color);
					}
					else
						sinTest5 = 1;
				}
			}
			else
			{
				for (j = 0; j < tHeight - 1; j++)
				{
					if (sSinHelp[i].szDocBuff[j + TempLine4])
					{
						wsprintf(strBuff, "%s", sSinHelp[i].szDocBuff[j + TempLine4]);

						if (sinQuest_Level90_2.CODE)
						{
							cnt = lstrlen(strBuff);

							for (int p = 0; p < cnt; p++)
							{
								if (strBuff[p] == '$' && strBuff[p + 1] == '$')
								{
									memset(strBuff2, 0, sizeof(strBuff2));
									sinCopyText(strBuff2, strBuff);
									wsprintf(strBuff, strBuff2, sinLevelQuest90_2Mon[sinQuest_Level90_2.Kind - 1]);
									break;
								}
							}
						}

						dsTextLineOut(0, sSinHelp[i].PosiX + 30, sSinHelp[i].PosiY + 66 + (15 * j), strBuff, lstrlen(strBuff), Color);
					}
					else
						sinTest5 = 1;
				}
			}

			DWORD Color = D3DCOLOR_XRGB(255, 255, 240);

			if (sSinHelp[i].KindFlag == SIN_HELP_KIND_NORMAL)
				dsTextLineOut(1, sSinHelp[i].TitlePosi.x + 65, sSinHelp[i].TitlePosi.y + 9, "Help", lstrlen("Help"), Color);

			else if (sSinHelp[i].KindFlag == SIN_HELP_KIND_SOD)
			{
				for (int h = 0; h < 10; h++)
				{
					if (sSod_Rank[h].Flag)
					{
						wsprintf(strBuff, "%d", h + 1);

						if (h == 9)
							dsTextLineOut(1, sSinHelp[i].PosiX + 20, sSinHelp[i].PosiY + 64 + (h * 24), strBuff, lstrlen(strBuff), D3DCOLOR_XRGB(255, 200, 100));
						else
							dsTextLineOut(1, sSinHelp[i].PosiX + 25, sSinHelp[i].PosiY + 64 + (h * 24), strBuff, lstrlen(strBuff), D3DCOLOR_XRGB(255, 200, 100));

						Len = lstrlen(sSod_Rank[h].Name);
						dsTextLineOut(0, sSinHelp[i].PosiX + 25 + (116 - ((Len * 6) / 2)), sSinHelp[i].PosiY + 64 + (h * 24), sSod_Rank[h].Name, lstrlen(sSod_Rank[h].Name), D3DCOLOR_XRGB(222, 231, 255));

						wsprintf(strBuff, "%d", sSod_Rank[h].Score);
						Len = lstrlen(strBuff);
						dsTextLineOut(0, sSinHelp[i].PosiX + 25 + 97 + (116 - ((Len * 6) / 2)), sSinHelp[i].PosiY + 64 + (h * 24), strBuff, lstrlen(strBuff), D3DCOLOR_XRGB(128, 255, 128));

						wsprintf(strBuff, "%d", sSod_Rank[h].KillNum);
						Len = lstrlen(strBuff);
						dsTextLineOut(0, sSinHelp[i].PosiX + 25 + 97 + 70 + (116 - ((Len * 6) / 2)), sSinHelp[i].PosiY + 64 + (h * 24), strBuff, lstrlen(strBuff), D3DCOLOR_XRGB(110, 165, 250));
					}
				}
			}
			else if (sSinHelp[i].KindFlag == SIN_HELP_KIND_C_TELEPORT)
				dsTextLineOut(1, sSinHelp[i].TitlePosi.x + 65, sSinHelp[i].TitlePosi.y + 9, HaWarpGateName[0], lstrlen(HaWarpGateName[0]), Color);
			else if (sSinHelp[i].KindFlag == SIN_HELP_KIND_WARPGATE)
			{
				if (sSinWarpGate.GateSelect > -1)
					dsTextLineOut(1, sSinHelp[i].TitlePosi.x + 65, sSinHelp[i].TitlePosi.y + 9, WarpGateName[sSinWarpGate.GateSelect + 1], lstrlen(WarpGateName[sSinWarpGate.GateSelect + 1]), Color);
				else
					dsTextLineOut(1, sSinHelp[i].TitlePosi.x + 65, sSinHelp[i].TitlePosi.y + 9, WarpGateName[0], lstrlen(WarpGateName[0]), Color);
			}
			else if (sSinHelp[i].KindFlag == SIN_HELP_KIND_INITPOINT)
				dsTextLineOut(1, sSinHelp[i].TitlePosi.x + 65, sSinHelp[i].TitlePosi.y + 9, "Pumpkin Fairy", lstrlen("Pumpkin Fairy"), Color);
			else if (sSinHelp[i].KindFlag == SIN_HELP_KIND_BABEL)
				dsTextLineOut(1, sSinHelp[i].TitlePosi.x + 65, sSinHelp[i].TitlePosi.y + 9, " Quest ", lstrlen(" Quest "), Color);
			else if (sSinHelp[i].KindFlag == SIN_HELP_KIND_RESEARCH)
				dsTextLineOut(1, sSinHelp[i].TitlePosi.x + 65, sSinHelp[i].TitlePosi.y + 9, " View ", lstrlen(" View "), Color);
			else if (sSinHelp[i].KindFlag == SIN_HELP_KIND_TELEPORT_SCROLL)
				dsTextLineOut(1, sSinHelp[i].TitlePosi.x + 65, sSinHelp[i].TitlePosi.y + 9, " Transport ", lstrlen(" Transport"), Color);
			else if (sSinHelp[i].KindFlag == SIN_HELP_KIND_TELEPORT_MILTER)
				dsTextLineOut(1, sSinHelp[i].TitlePosi.x + 65, sSinHelp[i].TitlePosi.y + 9, " Transport ", lstrlen(" Transport"), Color);
			else
				dsTextLineOut(1, sSinHelp[i].TitlePosi.x + 65, sSinHelp[i].TitlePosi.y + 9, " Quest ", lstrlen(" Quest "), Color);
		}
	}
}
int  cSINHELP::sinShowHelp(int Kind, int PosiX, int PosiY, int SizeW, int SizeH, DWORD BackColor, char *File, int NPCNum)
{
	int flag = 0;
	if (isDrawClanMenu)
		return FALSE;

	if (Kind != SIN_HELP_KIND_TELEPORT_SCROLL && cSinHelp.sinGetHelpShowFlagNum())
	{
		flag = cSinHelp.sinGetHelpShowFlagNum();
		if (flag != 40)
			return FALSE;
	}

	int i = 0, j = 0, k = 0;

	for (i = 0; i < SIN_MAX_HELP_NUMBER; i++)
	{
		if (sSinHelp[i].KindFlag)
		{
			if (sSinHelp[i].KindFlag == SIN_HELP_KIND_WARPGATE)
			{
				if (sSinHelp[i].Code != sSinWarpGate.GateSelect)
				{
					memset(&sSinHelp[i], 0, sizeof(sSINHELP));
					sSinHelp[i].Code = sSinWarpGate.GateSelect;
					break;
				}
				else
					return FALSE;
			}
			else if (sSinHelp[i].KindFlag == HAQUEST_CODE_FURYOFPHANTOM || sSinHelp[i].KindFlag == SIN_HELP_KIND_TELEPORT_SCROLL)
			{
				memset(&sSinHelp[i], 0, sizeof(sSINHELP));
				break;
			}
			else
			{
				chaPremiumitem.Using_ItemKind = 0;
				return FALSE;
			}
		}
	}

	NPCFlag = NPCNum;

	int  Wapecnt = 0;
	int  WapeGateMoney[6] = { 100,300,500,1000,2000,4000 };
	int  TeleportMoney[4] = { 100,100,500,1000 };
	char StrTemp[128];

	for (i = 0; i < SIN_MAX_HELP_NUMBER; i++)
	{
		if (!sSinHelp[i].KindFlag)
		{
			memset(szHelpDocBuff, 0, (char)100 * 128);
			sinReadFileData(File);
			sinReadFileDataDivide(&szHelpDocBuff[0][0], 128, SizeW * 8);

			for (int t = 0; t < 80; t++)
			{
				if (Kind == SIN_HELP_KIND_WARPGATE)
				{
					if (haSearchString(&szHelpDocBuff[t][0], '%'))
					{
						wsprintf(StrTemp, &szHelpDocBuff[t][0], cShop.haShopItemPrice(WapeGateMoney[Wapecnt]));
						lstrcpy(&szHelpDocBuff[t][0], StrTemp);
						Wapecnt++;
					}
				}
				if (Kind == SIN_HELP_KIND_TELEPORT)
				{
					if (haSearchString(&szHelpDocBuff[t][0], '%'))
					{
						wsprintf(StrTemp, &szHelpDocBuff[t][0], cShop.haShopItemPrice(TeleportMoney[Wapecnt]));
						lstrcpy(&szHelpDocBuff[t][0], StrTemp);
						Wapecnt++;
					}
				}
				if (Kind == SIN_HELP_KIND_C_TELEPORT)
				{
					if (haSearchString(&szHelpDocBuff[t][0], '%'))
					{
						wsprintf(StrTemp, &szHelpDocBuff[t][0], haC_TeleportMoney);
						lstrcpy(&szHelpDocBuff[t][0], StrTemp);
						Wapecnt++;
					}
				}
				if (szHelpDocBuff[t][0] || szHelpDocBuff[t + 1][0] || szHelpDocBuff[t + 2][0] || szHelpDocBuff[t + 3][0])
				{
					sSinHelp[i].szDocBuff[t] = &szHelpDocBuff[t][0];
					sSinHelp[i].LineCnt++;
				}
			}
			sSinHelp[i].LineCnt++;

			sSinHelp[i].KindFlag = Kind;
			sSinHelp[i].PosiX = PosiX;
			sSinHelp[i].PosiY = PosiY;
			sSinHelp[i].SizeW = SizeW;
			sSinHelp[i].SizeH = SizeH;
			sSinHelp[i].BackColor = BackColor;

			sSinHelp[i].ScrollButton.x = sSinHelp[i].PosiX + (sSinHelp[i].SizeW - 1) * 32 + 80 - 10;

			if (sSinHelp[i].SizeH <= 10)
			{
				TempScrollPosiY = 53;
				sSinHelp[i].ScrollButton.y = sSinHelp[i].PosiY + TempScrollPosiY;
			}
			else
			{
				TempScrollPosiY = 64;
				sSinHelp[i].ScrollButton.y = sSinHelp[i].PosiY + 64;
			}

			sSinHelp[i].ScrollMAXPosiY_UP = sSinHelp[i].PosiY + TempScrollPosiY + 7;
			sSinHelp[i].ScrollMAXPosiY_DOWN = sSinHelp[i].PosiY + TempScrollPosiY + 7 + 236;

			if (sSinHelp[i].KindFlag == SIN_HELP_KIND_NORMAL)
			{
				sSinHelp[i].TitlePosi.x = sSinHelp[i].PosiX + ((sSinHelp[i].SizeW * 32) + 64) / 2 - (181 / 2);
				sSinHelp[i].TitlePosi.y = sSinHelp[i].PosiY + -10;
				sSinHelp[i].ButtonPosi.x = sSinHelp[i].PosiX + ((sSinHelp[i].SizeW * 32) + 64) / 2 - (48 / 2);
				sSinHelp[i].ButtonPosi.y = sSinHelp[i].PosiY + (sSinHelp[i].SizeH) * 32 - 2;
			}
			else
			{
				sSinHelp[i].TitlePosi.x = sSinHelp[i].PosiX + ((sSinHelp[i].SizeW * 32) + 64) / 2 - (181 / 2);
				sSinHelp[i].TitlePosi.y = sSinHelp[i].PosiY + -10;
				sSinHelp[i].ButtonPosi.x = sSinHelp[i].PosiX + ((sSinHelp[i].SizeW * 32) + 64) / 2 - (48 / 2);
				sSinHelp[i].ButtonPosi.y = sSinHelp[i].PosiY + (sSinHelp[i].SizeH) * 32 - 2;
			}

			if (sSinHelp[i].LineCnt > 16)
				sSinHelp[i].ScrollFlag = 1;

			for (j = 0; j < SizeW; j++)
			{
				for (k = 0; k < SizeH; k++)
				{
					sSinHelp[i].sHelp_Box[j][k] = new sSINHELP_BOX;

					if (j == 0 && k == 0)
					{
						sSinHelp[i].sHelp_Box[j][k]->Mat = MatHelpBoxImage[0];
						sSinHelp[i].MatFlag[j][k] = 1;
						sSinHelp[i].sHelp_Box[j][k]->x = (float)PosiX;
						sSinHelp[i].sHelp_Box[j][k]->y = (float)PosiY;
						sSinHelp[i].sHelp_Box[j][k]->w = 64;
						sSinHelp[i].sHelp_Box[j][k]->h = 32;
					}
					if (j == SizeW - 1 && k == 0)
					{
						sSinHelp[i].sHelp_Box[j][k]->Mat = MatHelpBoxImage[2];
						sSinHelp[i].MatFlag[j][k] = 1;
						sSinHelp[i].sHelp_Box[j][k]->x = (float)PosiX + ((SizeW - 1) * 32) + 32;
						sSinHelp[i].sHelp_Box[j][k]->y = (float)PosiY;
						sSinHelp[i].sHelp_Box[j][k]->w = 64;
						sSinHelp[i].sHelp_Box[j][k]->h = 32;
					}
					if (j == SizeW - 1 && k == SizeH - 1)
					{
						sSinHelp[i].sHelp_Box[j][k]->Mat = MatHelpBoxImage[8];
						sSinHelp[i].MatFlag[j][k] = 1;
						sSinHelp[i].sHelp_Box[j][k]->x = (float)PosiX + ((SizeW - 1) * 32) + 32;
						sSinHelp[i].sHelp_Box[j][k]->y = (float)PosiY + ((SizeH - 1) * 32);
						sSinHelp[i].sHelp_Box[j][k]->w = 64;
						sSinHelp[i].sHelp_Box[j][k]->h = 64;
					}
					if (j == 0 && k == SizeH - 1)
					{
						sSinHelp[i].sHelp_Box[j][k]->Mat = MatHelpBoxImage[6];
						sSinHelp[i].MatFlag[j][k] = 1;
						sSinHelp[i].sHelp_Box[j][k]->x = (float)PosiX;
						sSinHelp[i].sHelp_Box[j][k]->y = (float)PosiY + ((SizeH - 1) * 32);
						sSinHelp[i].sHelp_Box[j][k]->w = 64;
						sSinHelp[i].sHelp_Box[j][k]->h = 64;
					}
					if (j != 0 && k == 0 && j != SizeW - 1)
					{
						sSinHelp[i].sHelp_Box[j][k]->Mat = MatHelpBoxImage[1];
						sSinHelp[i].MatFlag[j][k] = 1;
						sSinHelp[i].sHelp_Box[j][k]->x = (float)PosiX + (j * 32) + 32;
						sSinHelp[i].sHelp_Box[j][k]->y = (float)PosiY;
						sSinHelp[i].sHelp_Box[j][k]->w = 32;
						sSinHelp[i].sHelp_Box[j][k]->h = 32;
					}
					if (j == SizeW - 1 && k != 0 && k != SizeH - 1)
					{
						sSinHelp[i].sHelp_Box[j][k]->Mat = MatHelpBoxImage[5];
						sSinHelp[i].MatFlag[j][k] = 1;
						sSinHelp[i].sHelp_Box[j][k]->x = (float)PosiX + ((SizeW - 1) * 32) + 32;
						sSinHelp[i].sHelp_Box[j][k]->y = (float)PosiY + (k * 32);
						sSinHelp[i].sHelp_Box[j][k]->w = 64;
						sSinHelp[i].sHelp_Box[j][k]->h = 32;
					}
					if (j != 0 && j != SizeW - 1 && k == SizeH - 1)
					{
						sSinHelp[i].sHelp_Box[j][k]->Mat = MatHelpBoxImage[7];
						sSinHelp[i].MatFlag[j][k] = 1;
						sSinHelp[i].sHelp_Box[j][k]->x = (float)PosiX + (j * 32) + 32;
						sSinHelp[i].sHelp_Box[j][k]->y = (float)PosiY + ((SizeH - 1) * 32);
						sSinHelp[i].sHelp_Box[j][k]->w = 32;
						sSinHelp[i].sHelp_Box[j][k]->h = 64;
					}
					if (j == 0 && k != SizeH - 1 && k != 0)
					{
						sSinHelp[i].sHelp_Box[j][k]->Mat = MatHelpBoxImage[3];
						sSinHelp[i].MatFlag[j][k] = 1;
						sSinHelp[i].sHelp_Box[j][k]->x = (float)PosiX;
						sSinHelp[i].sHelp_Box[j][k]->y = (float)PosiY + (k * 32);
						sSinHelp[i].sHelp_Box[j][k]->w = 64;
						sSinHelp[i].sHelp_Box[j][k]->h = 32;
					}
					sSinHelp[i].sHelp_Box[j][k]->surW = 0;
					sSinHelp[i].sHelp_Box[j][k]->surH = 0;
					sSinHelp[i].sHelp_Box[j][k]->Transp = 255;
				}
			}
			break;
		}
	}

	return TRUE;
}
int sinDrawTexImage(int Mat, float x, float y, float w, float h, float surW, float surH, float tLeft, float tTop, float tRight, float tBottom, int Transp)
{
	D3DTLVERTEX9 tlVertex[4];
	int cnt;

	for (cnt = 0; cnt < 4; cnt++)
	{
		tlVertex[cnt].rhw = 1;
		tlVertex[cnt].color = D3DCOLOR_RGBA(255, 255, 255, Transp);
		tlVertex[cnt].specular = D3DCOLOR_RGBA(0, 0, 0, 0);
		tlVertex[cnt].sz = 0;
	}

	tlVertex[0].sx = x + surW;
	tlVertex[0].sy = y + surH;
	tlVertex[0].tu = 0;
	tlVertex[0].tv = 0;

	tlVertex[1].sx = x + surH;
	tlVertex[1].sy = (y + h) - surW;
	tlVertex[1].tu = 0;
	tlVertex[1].tv = 0.996f;

	tlVertex[2].sx = (x + w) - surH;
	tlVertex[2].sy = y + surW;
	tlVertex[2].tu = 0.996f;
	tlVertex[2].tv = 0;

	tlVertex[3].sx = (x + w) - surW;
	tlVertex[3].sy = (y + h) - surH;
	tlVertex[3].tu = 0.996f;
	tlVertex[3].tv = 0.996f;

	psSetRenderState(0);

	if (smMaterial[Mat].smTexture[0] != NULL && smMaterial[Mat].smTexture[0]->m_pTexture != NULL)
		psDraw2DImage(smMaterial[Mat].smTexture[0]->m_pTexture, tlVertex);

	return TRUE;
}
int cSINHELP::sinReadFileData(char *name)
{
	HANDLE hFile;
	DWORD dwAcess = 0;
	hFile = CreateFile(name, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	ZeroMemory((void*)szFileReadBuf2, sizeof(szFileReadBuf2));

	if (hFile != INVALID_HANDLE_VALUE)
	{
		DWORD rbyte;
		int chk = ReadFile(hFile, (LPVOID)szFileReadBuf2, sizeof(szFileReadBuf2), &rbyte, NULL);

		CloseHandle(hFile);
		return TRUE;
	}

	return FALSE;

}
int cSINHELP::sinReadFileDataDivide(char *SaveBuf, int Linelen, int Size)
{
	int i, bufC = 0, cnt = 0, cnt2 = 0;
	char c;
	int CheckByteFlag = 0;
	int CountType = 0;

	for (i = 0; ; i++)
	{
		while (1)
		{
			c = szFileReadBuf2[cnt++];

			if (c == 0)
				break;
			if (c == 13)
			{
				cnt++;
				break;
			}
			SaveBuf[i*Linelen + bufC] = c;
			bufC++;

		}
		bufC = 0;
		if (c == 0)
			break;
	}
	return TRUE;
}
static char sinDecode[512];
static char sinLine[512];

int cSINHELP::TonyGetFileData()
{
	memset(&sTonyTest, 0, sizeof(sTONY_TEST_IMAGE) * 10);

	char *szFilePath = "Image\\SinImage\\Tony\\";
	char szTempBuffFile[128];
	char szTempBuff[128];


	FILE	*fp;
	char strBuff[64];
	char *p;
	int Count = 0;
	int NextFlag = 0;

	wsprintf(szTempBuffFile, "%sTony.INI", szFilePath);
	fopen_s(&fp,szTempBuffFile, "rb");
	if (fp == NULL)
		return FALSE;

	while (!feof(fp))
	{
		NextFlag = 0;
		if (fgets(sinLine, 255, fp) == NULL)
			break;

		p = GetWord(sinDecode, sinLine);

		if (!NextFlag && lstrcmp(sinDecode, "*捞固瘤颇老捞抚") == 0)
		{
			p = GetWord(strBuff, p);
			lstrcpy(sTonyTest[Count].ImageFileName, strBuff);

			NextFlag = TRUE;

		}
		if (!NextFlag && lstrcmp(sinDecode, "*捞固瘤困摹") == 0)
		{
			p = GetWord(strBuff, p);
			sTonyTest[Count].Posi.x = atoi(strBuff);
			p = GetWord(strBuff, p);
			sTonyTest[Count].Posi.y = atoi(strBuff);
			NextFlag = TRUE;

		}
		if (!NextFlag && lstrcmp(sinDecode, "*捞固瘤农扁") == 0)
		{
			p = GetWord(strBuff, p);
			sTonyTest[Count].Size.x = atoi(strBuff);
			p = GetWord(strBuff, p);
			sTonyTest[Count].Size.y = atoi(strBuff);
			NextFlag = TRUE;

		}
		if (!NextFlag && lstrcmp(sinDecode, "*颇老器杆") == 0)
		{
			p = GetWord(strBuff, p);
			if (lstrcmp(strBuff, "TGA") == 0)
				sTonyTest[Count].FileFormat = TONY_TGA;
			if (lstrcmp(strBuff, "BMP") == 0)
				sTonyTest[Count].FileFormat = TONY_BMP;

		}

		if (!NextFlag && lstrcmp(sinDecode, "*场") == 0)
		{
			sTonyTest[Count].Flag = 1;
			wsprintf(szTempBuff, "%s%s", szFilePath, sTonyTest[Count].ImageFileName);
			if (sTonyTest[Count].FileFormat == TONY_TGA)
				sTonyTest[Count].Mat = CreateTextureMaterial("Image\\SinImage\\Tony\\shop-1.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

			if (sTonyTest[Count].FileFormat == TONY_BMP)
				sTonyTest[Count].lpTony = LoadDibSurfaceOffscreen(szTempBuff);

			Count++;
		}
	}
	if (fp)
		fclose(fp);

	return TRUE;

}
int cSINHELP::sinGetScrollMove(int Num)
{

	int i;
	for (i = 0; i < SIN_MAX_HELP_NUMBER; i++)
	{
		if (sSinHelp[i].KindFlag)
		{
			if (sSinHelp[i].ScrollFlag)
			{
				sSinHelp[i].ScrollButton.y += Num;
				if (sSinHelp[i].ScrollButton.y < sSinHelp[i].ScrollMAXPosiY_UP)
					sSinHelp[i].ScrollButton.y = sSinHelp[i].ScrollMAXPosiY_UP;
				if (sSinHelp[i].ScrollButton.y > sSinHelp[i].ScrollMAXPosiY_DOWN)
					sSinHelp[i].ScrollButton.y = sSinHelp[i].ScrollMAXPosiY_DOWN;
				return TRUE;
			}
		}
	}

	return FALSE;

}
int cSINHELP::sinGetKeyScrollDown()
{
	int i;
	for (i = 0; i < SIN_MAX_HELP_NUMBER; i++)
	{
		if (sSinHelp[i].KindFlag)
		{
			if (sSinHelp[i].ScrollFlag)
			{
				if (sinGetKeyClick(VK_PRIOR))
					sSinHelp[i].ScrollButton.y -= 30;

				if (sinGetKeyClick(VK_NEXT))
					sSinHelp[i].ScrollButton.y += 30;

				if (VRKeyBuff[VK_UP])
					sSinHelp[i].ScrollButton.y--;

				if (VRKeyBuff[VK_DOWN])
					sSinHelp[i].ScrollButton.y++;

				if (sSinHelp[i].ScrollButton.y < sSinHelp[i].ScrollMAXPosiY_UP)
					sSinHelp[i].ScrollButton.y = sSinHelp[i].ScrollMAXPosiY_UP;

				if (sSinHelp[i].ScrollButton.y > sSinHelp[i].ScrollMAXPosiY_DOWN)
					sSinHelp[i].ScrollButton.y = sSinHelp[i].ScrollMAXPosiY_DOWN;
			}
		}
	}

	return TRUE;
}
int cSINHELP::sinGetHelpShowFlag()
{
	int i;
	for (i = 0; i < SIN_MAX_HELP_NUMBER; i++)
	{
		if (sSinHelp[i].KindFlag)
			return TRUE;
	}

	extern BOOL IsDrawGuideHelp;

	if (IsDrawGuideHelp)
		return TRUE;
	return FALSE;
}

struct sSCORESORT
{
	int	Score;
	int Index;
};
sSCORESORT sScoreSort[11];


int cSINHELP::ShowSodRanking(TRANS_SOD_RESULT *SodResult, int MyGame)
{
	int  i = 0, j = 0;

	if (!lpSodMenu)
		lpSodMenu = LoadDibSurfaceOffscreen("Image\\SinImage\\Help\\sod_list.bmp");
	if (!lpSodLine)
		lpSodLine = LoadDibSurfaceOffscreen("Image\\SinImage\\Help\\sod_list-line.bmp");

	char szBuff[128];

	for (i = 0; i < MAX_JOBNUM; i++)
	{
		if (!lpSodJobFace[i])
		{
			wsprintf(szBuff, "Image\\SinImage\\Help\\sod_cr-%d.bmp", i + 1);
			lpSodJobFace[i] = LoadDibSurfaceOffscreen(szBuff);
		}
	}

	ZeroMemory(sScoreSort, sizeof(sSCORESORT) * 11);
	ZeroMemory(sSod_Rank, sizeof(sSOD_RANK) * 10);

	for (i = 0; i < SodResult->ResultCount; i++)
	{
		sSod_Rank[i].Flag = 1;
		sScoreSort[i].Score = SodResult->Result[i].Score;

		if (sScoreSort[i].Score < 0)
			sScoreSort[i].Score = 0;
		sScoreSort[i].Index = i;

	}
	int Temp = 0;

	for (i = 10; i > 0; i--)
	{
		for (j = 0; j < i; j++)
		{
			if (sScoreSort[j].Score < sScoreSort[j + 1].Score)
			{
				Temp = sScoreSort[j + 1].Score;
				sScoreSort[j + 1].Score = sScoreSort[j].Score;
				sScoreSort[j].Score = Temp;

				Temp = sScoreSort[j + 1].Index;
				sScoreSort[j + 1].Index = sScoreSort[j].Index;
				sScoreSort[j].Index = Temp;
			}
		}
	}

	for (j = 0; j < 10; j++)
	{
		if (sSod_Rank[j].Flag)
		{
			sSod_Rank[j].Job = SodResult->Result[sScoreSort[j].Index].JobCode;
			lstrcpy(sSod_Rank[j].Name, SodResult->Result[sScoreSort[j].Index].szName);
			sSod_Rank[j].Score = SodResult->Result[sScoreSort[j].Index].Score;
			if (sSod_Rank[j].Score < 0)
				sSod_Rank[j].Score = 0;
			sSod_Rank[j].KillNum = SodResult->Result[sScoreSort[j].Index].Monster;

			if (sSod_Rank[j].KillNum < 0)
				sSod_Rank[j].KillNum = 0;
		}
	}

	HelpBoxKindIndex = SIN_SOD;
	if (MyGame)
		cSinHelp.sinShowHelp(SIN_HELP_KIND_SOD, QuestMessageBoxPosi2.x + 170, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "");
	else
		cSinHelp.sinShowHelp(SIN_HELP_KIND_SOD, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "");

	return TRUE;
}
int cSINHELP::GetSodRankBoxState()
{
	for (int i = 0; i < SIN_MAX_HELP_NUMBER; i++)
	{
		if (sSinHelp[i].KindFlag)
		{
			if (sSinHelp[i].KindFlag == SIN_HELP_KIND_SOD)
			{
				if (sSinHelp[i].PosiX < QuestMessageBoxPosi2.x + 170)
					return TRUE;
			}
		}
	}
	return FALSE;
}

int sinShowHelp()
{
	char *HelpFilePath = "image\\Sinimage\\Help\\Help.sin";
	cSinHelp.sinShowHelp(SIN_HELP_KIND_NORMAL, 208, 61 - 50, 11, 11, D3DCOLOR_RGBA(19, 27, 20, 165), HelpFilePath);
	HelpBoxKindIndex = SIN_HELP;
	return TRUE;
}

int sinShowTeleportMap()
{
	cSinHelp.NPCTeleportFlag = 1;
	cSinHelp.sinShowHelp(SIN_HELP_KIND_TELEPORT, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), TeleportFilePath);
	return TRUE;

}
int TeleportDungeon()
{
	char *TeleportText = "image\\Sinimage\\Help\\EndlessTeleport.sin";
	cSinHelp.NPCTeleportFlag = 1;
	cSinHelp.sinShowHelp(SIN_HELP_KIND_TELEPORT_MILTER, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), TeleportText);
	return TRUE;
}
int haShowCastleTeleportMap()
{
	haC_TeleportMoney = sinChar->iLevel * 500;
	cSinHelp.sinShowHelp(SIN_HELP_KIND_C_TELEPORT, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), haC_TeleportFilePath);

	return TRUE;
}
int cSINHELP::ShowResearchMenu(int Kind, int Flag)
{
	switch (Kind)
	{
	case 1:
		haResearch.Index = Kind;
		if (Flag)
			cSinHelp.sinShowHelp(SIN_HELP_KIND_RESEARCH, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), haResearchFilePath1);
		else
			cMessageBox.ShowMessage(MESSAGE_NOT_RESEARCH);

	case 2:
		haResearch.Index = Kind;
		if (Flag)
			cSinHelp.sinShowHelp(SIN_HELP_KIND_RESEARCH, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), haResearchFilePath2);
		else
			cMessageBox.ShowMessage(MESSAGE_NOT_RESEARCH);
		break;
	case 3:
		haResearch.Index = Kind;
		if (Flag)
			cSinHelp.sinShowHelp(SIN_HELP_KIND_RESEARCH, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), haResearchFilePath3);
		else
			cMessageBox.ShowMessage(MESSAGE_NOT_RESEARCH);
		break;
	}

	return TRUE;
}
int cSINHELP::SendResearch()
{
	for (int i = 0; i < haResearch.Number; i++)
		haResearch.bSendPollingData[i] = haResearch.Value[i];
	SendPublicPollingToServer(haResearch.Index, haResearch.Number, haResearch.bSendPollingData);
	return TRUE;
}
int cSINHELP::sinGetHelpShowFlagNum()
{
	int KindFlag = 0;
	for (int i = 0; i < SIN_MAX_HELP_NUMBER; i++)
	{
		if (sSinHelp[i].KindFlag)
		{
			KindFlag = sSinHelp[i].KindFlag;
			return KindFlag;
		}
	}
	return KindFlag;
}