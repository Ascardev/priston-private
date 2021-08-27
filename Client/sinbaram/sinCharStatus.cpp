#include "StdAfx.h"
#include "..\\Language.h"
#include "..\\tjboy\\clanmenu\\tjclanDEF.h"
#include "..\\tjboy\\clanmenu\\tjclan.h"
#include "..\\tjboy\\clanmenu\\cE_CViewClanInfo.h"

cCHARSTATUS cCharStatus;
sDISPLAYSTATE sDisplayState[10];
sDISPLAYSTATE sDisplayStateShow;

int OldLevel;

int OldLevelTemp;

int sinLevelPoint = 0;

int sinPointButtonDown = FALSE;

int ShowCharArrow = 0;

int RegiInfoPosi = 0;

int ReHeight3 = 2;

sCHARRECTPOSI	sCharRectPosi[MAX_CHAR_RECT_POSI] =
{
	{"Class"    ,{ 75   , 442 + ReHeight3  , 160 , 454  }}, //0
	{"Name"     ,{ 75   , 463 + ReHeight3  , 160 , 479  }}, //1
	{"Level"    ,{ 75   , 503 + ReHeight3  , 160 , 480  }}, //2
	{"Exp"      ,{ 75   , 543 + ReHeight3  , 160 , 549  }}, //3
	{"Next_Exp" ,{ 75   , 563 + ReHeight3  , 160 , 574  }}, //4
	{"Life"		,{ 391  , 429 + ReHeight3  , 482 , 440  }}, //5
	{"Mana"     ,{ 391  , 454 + ReHeight3  , 482 , 466  }}, //6
	{"Stamina"  ,{ 391  , 479 + ReHeight3  , 482 , 490  }}, //7

	{"Strength" ,{ 585 , 433 + ReHeight3 , 632 , 444  }}, //8
	{"Spirit"   ,{ 585 , 454 + ReHeight3 , 632 , 464  }}, //9  
	{"Talent"   ,{ 585 , 473 + ReHeight3 , 632 , 485  }}, //10  
	{"Dexterity",{ 585 , 493 + ReHeight3 , 632 , 504  }}, //11
	{"Health"   ,{ 585 , 513 + ReHeight3 , 632 , 524  }}, //12	

	{"Bionic"   ,{ 217 + 3 , 449 + 8 + ReHeight3 , 248  , 468 }}, //13
	{"Poison"   ,{ 286 + 3 , 448 + 8 + ReHeight3 , 315  , 469 }}, //14
	{"Fire"     ,{ 217 + 3 , 486 + 8 + ReHeight3 , 248  , 469 }}, //15
	{"Lighting" ,{ 286 + 3 , 486 + 8 + ReHeight3 , 315  , 505 }}, //16
	{"Ice"      ,{ 217 + 3 , 523 + 8 + ReHeight3 , 248  , 543 }}, //17

	{"Attack_Rating" ,{ 710 , 455 + ReHeight3 - 1 , 769 , 464 }}, //18
	{"Attack_Damage" ,{ 710 , 474 + ReHeight3 - 1 , 769 , 484 }}, //19
	{"Defence"       ,{ 710 , 495 + ReHeight3 - 1 , 769 , 504 }}, //20
	{"Speed"         ,{ 710 , 515 + ReHeight3 - 1 , 769 , 524 }}, //21
	{"Absorption"    ,{ 710 , 534 + ReHeight3 - 1 , 769 , 545 }}, //22
	{"Point"         ,{ 585 , 533 + ReHeight3 - 1 , 632 , 544 }}, //23
};

int RegiBox[5][4] =
{
	{ 185 , 445 , 216  , 475 },
	{ 185 , 482 , 216  , 512 },
	{ 185 , 519 , 216  , 550 },
	{ 251 , 445 , 281  , 475 },
	{ 251 , 482 , 281  , 512 },
};

int PointButton[6][4] =
{
	{565 + 1,431 + 1,583,449},
	{565 + 1,452 + 1,583,469},
	{565 + 1,472 + 1,583,488},
	{565 + 1,491 + 1,583,508},
	{565 + 1,511 + 1,583,529},
	{565 + 1,531 + 1,583,549},
};

int PointButtonPosi = 0;

smTEXTUREHANDLE *lpStatusMain;


int MatChatBotton_Glay = 0;
smTEXTUREHANDLE *lpChatButton[5];
smTEXTUREHANDLE *lpChatButton_Notice[3];
smTEXTUREHANDLE *lpChatLine;

int sinMatMike = 0;

cCHARSTATUS::cCHARSTATUS()
{
	OpenFlag = 0;
	ZeroMemory(TempStatePoint[0], sizeof(TempStatePoint[0]));
	ZeroMemory(TempStatePoint[1], sizeof(TempStatePoint[1]));
}

cCHARSTATUS::~cCHARSTATUS()
{

}

void cCHARSTATUS::Init()
{
	Load();

	SkillTextColor[SIN2_ATTACK_RATE] = SIN_TEXT_COLOR_WHITE;
	SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_WHITE;
	SkillTextColor[SIN2_DEFENSE] = SIN_TEXT_COLOR_WHITE;
	SkillTextColor[SIN2_ABSORB] = SIN_TEXT_COLOR_WHITE;
	SkillTextColor[SIN2_SPEED] = SIN_TEXT_COLOR_WHITE;

	MatChatBotton_Glay = CreateTextureMaterial("Image\\SinImage\\Inter\\Chat\\Chatting06.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	sinMatMike = CreateTextureMaterial("Image\\SinImage\\Inter\\mike.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);

	ShowFastAddPoint[0] = 0;
	ShowFastAddPoint[1] = 0;

}

void cCHARSTATUS::Load()
{
	lpRegiBox[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Status\\RegiInfo\\BioInfo.bmp");
	lpRegiBox[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\Status\\RegiInfo\\FireInfo.bmp");
	lpRegiBox[2] = LoadDibSurfaceOffscreen("Image\\SinImage\\Status\\RegiInfo\\IceInfo.bmp");
	lpRegiBox[3] = LoadDibSurfaceOffscreen("Image\\SinImage\\Status\\RegiInfo\\PoisonInfo.bmp");
	lpRegiBox[4] = LoadDibSurfaceOffscreen("Image\\SinImage\\Status\\RegiInfo\\LightInfo.bmp");

	lpChangeArrow[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Status\\ChangeArrow.png");
	lpSelectArrow[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Status\\SelectArrow.png");
	lpSelectArrow[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\Status\\SelectArrow2.png");
	lpStatusPoint[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Status\\StatusPoint.bmp");
	lpStatusPoint[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\Status\\StatusPointS.bmp");

	lpStatusMain = LoadDibSurfaceOffscreen("Image\\SinImage\\Status\\Status.png");

	lpChatButton[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\Chat\\ChatTap_01.bmp");
	lpChatButton[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\Chat\\ChatTap_02.bmp");
	lpChatButton[2] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\Chat\\ChatTap_03.bmp");
	lpChatButton[3] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\Chat\\ChatTap_04.bmp");
	lpChatButton[4] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\Chat\\ChatTap_05.bmp");

	lpChatButton_Notice[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\Chat\\ChatTap_N11.bmp");
	lpChatButton_Notice[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\Chat\\ChatTap_N12.bmp");
	lpChatButton_Notice[2] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\Chat\\ChatTap_N22.bmp");

	lpChatLine = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\Chat\\n_line.bmp");
}

void cCHARSTATUS::Release()
{
	for (int i = 0; i < 5; i++)
		DELET(lpRegiBox[i]);

	DELET(lpChangeArrow[0]);
	DELET(lpSelectArrow[0]);
	DELET(lpSelectArrow[1]);
	DELET(lpStatusPoint[0]);
	DELET(lpStatusPoint[1]);
}

extern BOOL bMic;

void cCHARSTATUS::Draw()
{
	int TempLen = 0;
	int TempCount2 = 0;

	if (sinMoveKindInter[SIN_CHARSTATUS] != 0)
	{
		DrawSprite(0, 600 - sinMoveKindInter[SIN_CHARSTATUS] + 56, lpStatusMain, 0, 0, 800, 200);

		if (ShowCharArrow)
		{
			DrawSprite(251, 565 + (256 - sinMoveKindInter[SIN_CHARSTATUS]), cShop.lpExit, 0, 0, 20, 20);
			DrawSprite(251, 565 - 27 + (256 - sinMoveKindInter[SIN_CHARSTATUS]), cInvenTory.lpExitInfo, 0, 0, 47, 27);
		}

		if (sinChar->iStatPoints)
		{
			// 属性点 快速加点
			DrawSprite(566, 532 + (256 - sinMoveKindInter[SIN_CHARSTATUS]), lpSelectArrow[1], 0, 0, 18, 17);
			if (ShowFastAddPoint[0] || ShowFastAddPoint[1])
				DrawSprite(622, 532 + (256 - sinMoveKindInter[SIN_CHARSTATUS]), lpStatusPoint[1], 0, 0, 18, 17);

			for (int i = 0; i < 5; i++)
				DrawSprite(PointButton[i][0], PointButton[i][1] + (256 - sinMoveKindInter[SIN_CHARSTATUS]), lpChangeArrow[0], 0, 0, 18, 17);

			if (sinPointButtonDown)
			{
				if (PointButtonPosi <= 5 && PointButtonPosi != 0)
					DrawSprite(PointButton[PointButtonPosi - 1][0] + 1, PointButton[PointButtonPosi - 1][1] + (256 - sinMoveKindInter[SIN_CHARSTATUS]) + 1, lpSelectArrow[0], 0, 0, 18, 17);

				if (PointButtonPosi == 6)
					DrawSprite(PointButton[PointButtonPosi - 1][0] + 1, PointButton[PointButtonPosi - 1][1] + (256 - sinMoveKindInter[SIN_CHARSTATUS]) + 1, lpSelectArrow[1], 0, 0, 18, 17);
				if (ShowFastAddPoint[0])
					DrawSprite(622 + 1, 532 + 1 + (256 - sinMoveKindInter[SIN_CHARSTATUS]), lpStatusPoint[1], 0, 0, 18, 17);
			}
		}
		if (cldata.myPosition == 100 || cldata.myPosition == 101 || cldata.myPosition == 104)
		{
			if (cldata.hClanMark16)
			{
				TempLen = lstrlen(cldata.name);
				TempCount2 = 6 - (TempLen / 2);
				DrawSprite(CheckEditSize(sCharRectPosi[1].Rect.left, sCharRectPosi[1].Rect.right, cldata.name) - ((12 - TempLen / 2)) - TempCount2, sCharRectPosi[1].Rect.top + 15 + (256 - sinMoveKindInter[SIN_CHARSTATUS]), cldata.hClanMark16, 0, 0, 16, 16);
			}
		}
		switch (RegiInfoPosi)
		{
		case 1:
			DrawSprite(RegiBox[0][0] + 3, RegiBox[0][1] - 27 + (256 - sinMoveKindInter[SIN_CHARSTATUS]), lpRegiBox[0], 0, 0, 70, 27);
			break;
		case 2:
			DrawSprite(RegiBox[1][0] + 3, RegiBox[1][1] - 27 + (256 - sinMoveKindInter[SIN_CHARSTATUS]), lpRegiBox[1], 0, 0, 70, 27);
			break;
		case 3:
			DrawSprite(RegiBox[2][0] + 3, RegiBox[2][1] - 27 + (256 - sinMoveKindInter[SIN_CHARSTATUS]), lpRegiBox[2], 0, 0, 70, 27);
			break;
		case 4:
			DrawSprite(RegiBox[3][0] + 3, RegiBox[3][1] - 27 + (256 - sinMoveKindInter[SIN_CHARSTATUS]), lpRegiBox[3], 0, 0, 70, 27);
			break;
		case 5:
			DrawSprite(RegiBox[4][0] + 3, RegiBox[4][1] - 27 + (256 - sinMoveKindInter[SIN_CHARSTATUS]), lpRegiBox[4], 0, 0, 70, 27);
			break;

		}
	}
}

DWORD dwSkillTextTime = 0;
DWORD dwSkillTextTimeFlag = 0;
void cCHARSTATUS::Main()
{
	if (cSkill.SearchContiueSkill(SKILL_FROST_JAVELIN))
	{
		dwSkillTextTime++;
		if (dwSkillTextTime > 70)
		{
			switch (dwSkillTextTimeFlag)
			{
			case 0:
				dwSkillTextTimeFlag = 1;
				break;
			case 1:
				dwSkillTextTimeFlag = 2;
				break;
			case 2:
				dwSkillTextTimeFlag = 1;
				break;
			}
			dwSkillTextTime = 0;
		}
	}
	else dwSkillTextTimeFlag = 0;

	int  i;
	ShowCharArrow = 0;
	RegiInfoPosi = 0;
	PointButtonPosi = 0;

	if (pCursorPos.x > 251 && pCursorPos.x < 269 && pCursorPos.y > 565 && pCursorPos.y < 583)
		ShowCharArrow = 1;

	if (OpenFlag)
	{
		for (i = 0; i < 8; i++)
		{
			if (pCursorPos.x >= RegiBox[i][0] && pCursorPos.x <= RegiBox[i][2] && pCursorPos.y >= RegiBox[i][1] && pCursorPos.y <= RegiBox[i][3])
				RegiInfoPosi = i + 1;
		}
		for (i = 0; i < 6; i++)
		{
			if (pCursorPos.x >= PointButton[i][0] && pCursorPos.x <= PointButton[i][2] && pCursorPos.y >= PointButton[i][1] && pCursorPos.y <= PointButton[i][3])
				PointButtonPosi = i + 1;
		}
		if (pCursorPos.x > 620 && pCursorPos.x < 639 && pCursorPos.y > 531 && pCursorPos.y < 550 && sinChar->iStatPoints >= 10)
			ShowFastAddPoint[0] = TRUE;
		else
			ShowFastAddPoint[0] = FALSE;
		if (sinChar->iStatPoints < 10)
			ShowFastAddPoint[1] = FALSE;
	}
	else
	{
		ZeroMemory(TempStatePoint[0], sizeof(TempStatePoint[0]));
		ZeroMemory(TempStatePoint[1], sizeof(TempStatePoint[1]));
	}

	if (sinLoadOK)
		CheckLevel();
}

void cCHARSTATUS::Close()
{

}
void cCHARSTATUS::LButtonDown(int x, int y)
{
	int cnt;

	if (OpenFlag)
	{
		if (x > 251 && x < 269 && y > 565 && y < 583)
			OpenFlag = SIN_CLOSE;
		if (x > 620 && x < 639 && y > 531 && y < 550 && sinChar->iStatPoints >= 10)
		{
			sinPointButtonDown = TRUE;
			ShowFastAddPoint[1] ^= TRUE;
		}

		if (ShowFastAddPoint[1])
		{
			if (sinChar->iStatPoints > 9)
			{
				sinPointButtonDown = TRUE;
				switch (PointButtonPosi)
				{
				case 1: //力量
					CheckCharForm();
					sinChar->iStrength += 10;
					sinChar->iStatPoints -= 10;
					for (cnt = 0; cnt < 4; cnt++)
						TempStatePoint[0][cnt] = TempStatePoint[0][cnt + 1];
					TempStatePoint[0][4] = POINT_STRENGTH;
					ReformCharForm();
					cInvenTory.SetItemToChar();
					cInvenTory.CheckDamage();

					break;
				case 2: //精神
					CheckCharForm();
					sinChar->iSpirit += 10;
					sinChar->iStatPoints -= 10;
					for (cnt = 0; cnt < 4; cnt++)
						TempStatePoint[0][cnt] = TempStatePoint[0][cnt + 1];
					TempStatePoint[0][4] = POINT_SPIRIT;
					ReformCharForm();
					cInvenTory.SetItemToChar();
					cInvenTory.CheckDamage();
					break;
				case 3: //才能
					CheckCharForm();
					sinChar->iTalent += 10;
					sinChar->iStatPoints -= 10;
					for (cnt = 0; cnt < 4; cnt++)
						TempStatePoint[0][cnt] = TempStatePoint[0][cnt + 1];
					TempStatePoint[0][4] = POINT_TALENT;
					ReformCharForm();
					cInvenTory.SetItemToChar();

					break;
				case 4: //敏捷
					CheckCharForm();
					sinChar->iAgility += 10;
					sinChar->iStatPoints -= 10;
					for (cnt = 0; cnt < 4; cnt++)
						TempStatePoint[0][cnt] = TempStatePoint[0][cnt + 1];
					TempStatePoint[0][4] = POINT_DEXTERITY;
					ReformCharForm();
					cInvenTory.SetItemToChar();
					cInvenTory.CheckDamage();
					break;
				case 5: //体质
					CheckCharForm();
					sinChar->iHealth += 10;
					sinChar->iStatPoints -= 10;
					for (cnt = 0; cnt < 4; cnt++)
						TempStatePoint[0][cnt] = TempStatePoint[0][cnt + 1];
					TempStatePoint[0][4] = POINT_HEALTH;
					ReformCharForm();
					cInvenTory.SetItemToChar();
					cInvenTory.CheckDamage();
					break;
				case 6:
					for (cnt = 4; cnt >= 0; cnt--)
					{
						if (TempStatePoint[0][cnt])
						{
							switch (TempStatePoint[0][cnt])
							{
							case POINT_STRENGTH:
								CheckCharForm();
								sinChar->iStrength -= 10;
								sinChar->iStatPoints += 10;
								TempStatePoint[0][cnt] = 0;
								ReformCharForm();
								cInvenTory.SetItemToChar();
								cInvenTory.CheckDamage();
								break;
							case POINT_SPIRIT:
								CheckCharForm();
								sinChar->iSpirit -= 10;
								sinChar->iStatPoints += 10;
								TempStatePoint[0][cnt] = 0;
								ReformCharForm();
								cInvenTory.SetItemToChar();
								cInvenTory.CheckDamage();
								break;
							case POINT_TALENT:
								CheckCharForm();
								sinChar->iTalent -= 10;
								sinChar->iStatPoints += 10;
								TempStatePoint[0][cnt] = 0;
								ReformCharForm();
								cInvenTory.SetItemToChar();
								cInvenTory.CheckDamage();
								break;
							case POINT_DEXTERITY:
								CheckCharForm();
								sinChar->iAgility -= 10;
								sinChar->iStatPoints += 10;
								TempStatePoint[0][cnt] = 0;
								ReformCharForm();
								cInvenTory.SetItemToChar();
								cInvenTory.CheckDamage();

								break;
							case POINT_HEALTH:
								CheckCharForm();
								sinChar->iHealth -= 10;
								sinChar->iStatPoints += 10;
								TempStatePoint[0][cnt] = 0;
								ReformCharForm();
								cInvenTory.SetItemToChar();
								cInvenTory.CheckDamage();
								break;
							}
							break;
						}
					}
					break;
				}
			}
		}
		else
		{
			if (sinChar->iStatPoints > 0)
			{
				sinPointButtonDown = TRUE;
				switch (PointButtonPosi)
				{
					// 力量
				case 1:
					CheckCharForm();
					sinChar->iStrength++;
					sinChar->iStatPoints--;
					for (cnt = 0; cnt < 4; cnt++)
						TempStatePoint[1][cnt] = TempStatePoint[1][cnt + 1];
					TempStatePoint[1][4] = POINT_STRENGTH;
					ReformCharForm();
					cInvenTory.SetItemToChar();
					cInvenTory.CheckDamage();

					break;
					//精神
				case 2:
					CheckCharForm();
					sinChar->iSpirit++;
					sinChar->iStatPoints--;
					for (cnt = 0; cnt < 4; cnt++)
						TempStatePoint[1][cnt] = TempStatePoint[1][cnt + 1];
					TempStatePoint[1][4] = POINT_SPIRIT;
					ReformCharForm();
					cInvenTory.SetItemToChar();
					cInvenTory.CheckDamage();
					break;
					//才能
				case 3:
					CheckCharForm();
					sinChar->iTalent++;
					sinChar->iStatPoints--;
					for (cnt = 0; cnt < 4; cnt++)
						TempStatePoint[1][cnt] = TempStatePoint[1][cnt + 1];
					TempStatePoint[1][4] = POINT_TALENT;
					ReformCharForm();
					cInvenTory.SetItemToChar();
					cInvenTory.CheckDamage();

					break;
					//敏捷
				case 4:
					CheckCharForm();
					sinChar->iAgility++;
					sinChar->iStatPoints--;
					for (cnt = 0; cnt < 4; cnt++)
						TempStatePoint[1][cnt] = TempStatePoint[1][cnt + 1];
					TempStatePoint[1][4] = POINT_DEXTERITY;
					ReformCharForm();
					cInvenTory.SetItemToChar();
					cInvenTory.CheckDamage();
					break;
					//体质
				case 5:
					CheckCharForm();
					sinChar->iHealth++;
					sinChar->iStatPoints--;
					for (cnt = 0; cnt < 4; cnt++)
						TempStatePoint[1][cnt] = TempStatePoint[1][cnt + 1];
					TempStatePoint[1][4] = POINT_HEALTH;
					ReformCharForm();
					cInvenTory.SetItemToChar();
					cInvenTory.CheckDamage();
					break;
				case 6:
					for (cnt = 4; cnt >= 0; cnt--)
					{
						if (TempStatePoint[1][cnt])
						{
							switch (TempStatePoint[1][cnt])
							{
							case POINT_STRENGTH:
								CheckCharForm();
								sinChar->iStrength--;
								sinChar->iStatPoints++;
								TempStatePoint[1][cnt] = 0;
								ReformCharForm();
								cInvenTory.SetItemToChar();
								break;
							case POINT_SPIRIT:
								CheckCharForm();
								sinChar->iSpirit--;
								sinChar->iStatPoints++;
								TempStatePoint[1][cnt] = 0;
								ReformCharForm();
								cInvenTory.SetItemToChar();
								cInvenTory.CheckDamage();
								break;
							case POINT_TALENT:
								CheckCharForm();
								sinChar->iTalent--;
								sinChar->iStatPoints++;
								TempStatePoint[1][cnt] = 0;
								ReformCharForm();
								cInvenTory.SetItemToChar();
								cInvenTory.CheckDamage();
								break;
							case POINT_DEXTERITY:
								CheckCharForm();
								sinChar->iAgility--;
								sinChar->iStatPoints++;
								TempStatePoint[1][cnt] = 0;
								ReformCharForm();
								cInvenTory.SetItemToChar();
								cInvenTory.CheckDamage();

								break;
							case POINT_HEALTH:
								CheckCharForm();
								sinChar->iHealth--;
								sinChar->iStatPoints++;
								TempStatePoint[1][cnt] = 0;
								ReformCharForm();
								cInvenTory.SetItemToChar();
								cInvenTory.CheckDamage();
								break;
							}
							break;
						}
					}
					break;
				}
			}
		}
	}
}
void cCHARSTATUS::LButtonUp(int x, int y)
{
	sinPointButtonDown = FALSE;
}
void cCHARSTATUS::RButtonDown(int x, int y)
{
	
}
void cCHARSTATUS::RButtonUp(int x, int y)
{

}
void cCHARSTATUS::KeyDown()
{

	if (sinGetKeyClick('C'))
	{
		cHelpPet.PetMessage("*CarStatus", 3);
		if (cCharStatus.OpenFlag)
			cCharStatus.OpenFlag = SIN_CLOSE;
		else
			cCharStatus.OpenFlag = SIN_OPEN;
		cInterFace.CheckAllBox(SIN_CHARSTATUS);
		if (cCharStatus.OpenFlag)
		{
			if (!sinFireShow)
			{
				StartMenuFlame(0, 350);
				sinPlaySound(0);
			}
			else
				sinPlaySound(SIN_SOUND_SHOW_INTER);
			sinFireShow = 1;
		}
	}
	if (cCharStatus.OpenFlag)
	{
		if (sinGetKeyClick('B'))
			ShowFastAddPoint[1] ^= TRUE;
	}
}

DWORD CharStatusColor[10] = { D3DCOLOR_XRGB(255,255,255) , D3DCOLOR_XRGB(255,0,0) ,D3DCOLOR_XRGB(255,220,0),
					D3DCOLOR_XRGB(142,230,254) , D3DCOLOR_XRGB(128,255,128) ,D3DCOLOR_XRGB(255,225,0),
					D3DCOLOR_XRGB(255,180,200) , D3DCOLOR_XRGB(255,230,10) ,   D3DCOLOR_XRGB(255,220,0),
					D3DCOLOR_XRGB(255,220,0)

};

int sinBackupTextColor = 0;


void cCHARSTATUS::DrawCharText()
{
	CheckChageStateDisplay();
	if (!sinMoveKindInter[SIN_CHARSTATUS])
		return;

	int TempLen = 0;
	char strBuff[128];
	ZeroMemory(strBuff, sizeof(strBuff));

	DWORD Color = D3DCOLOR_XRGB(255, 255, 255);

	wsprintf(strBuff, "%s", cInvenTory.JobName);
	dsTextLineOut(0, CheckEditSize(sCharRectPosi[0].Rect.left, sCharRectPosi[0].Rect.right, strBuff), sCharRectPosi[0].Rect.top + (256 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff), Color);

	wsprintf(strBuff, "%s", sinCharDisplay.szName);
	dsTextLineOut(0, CheckEditSize(sCharRectPosi[1].Rect.left, sCharRectPosi[1].Rect.right, strBuff), sCharRectPosi[1].Rect.top + (256 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff), Color);

	if (cldata.myPosition == 100 || cldata.myPosition == 101 || cldata.myPosition == 104)
	{
		TempLen = lstrlen(cldata.name);
		wsprintf(strBuff, "%s", cldata.name);
		dsTextLineOut(0, CheckEditSize(sCharRectPosi[1].Rect.left, sCharRectPosi[1].Rect.right, strBuff) + TempLen, sCharRectPosi[1].Rect.top + 20 + (256 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff), Color);
	}

	wsprintf(strBuff, "%d", sinCharDisplay.iLevel);
	dsTextLineOut(0, CheckEditSize(sCharRectPosi[2].Rect.left, sCharRectPosi[2].Rect.right, strBuff), sCharRectPosi[2].Rect.top + (256 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff), Color);

	if (sinChar->iLevel > 79)
	{
		wsprintf(strBuff, "%dM", cCharStatus.sinGetNowExp());
		dsTextLineOut(0, CheckEditSize(sCharRectPosi[3].Rect.left, sCharRectPosi[3].Rect.right, strBuff), sCharRectPosi[3].Rect.top + (256 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff), Color);
	}
	else
	{
		wsprintf(strBuff, "%d", cCharStatus.sinGetNowExp());
		dsTextLineOut(0, CheckEditSize(sCharRectPosi[3].Rect.left, sCharRectPosi[3].Rect.right, strBuff), sCharRectPosi[3].Rect.top + (256 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff), Color);
	}

	if (sinChar->iLevel > 79)
	{
		wsprintf(strBuff, "%dM", cCharStatus.sinGetNextExp());
		dsTextLineOut(0, CheckEditSize(sCharRectPosi[4].Rect.left, sCharRectPosi[4].Rect.right, strBuff), sCharRectPosi[4].Rect.top + (256 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff), Color);
	}
	else
	{
		wsprintf(strBuff, "%d", cCharStatus.sinGetNextExp());
		dsTextLineOut(0, CheckEditSize(sCharRectPosi[4].Rect.left, sCharRectPosi[4].Rect.right, strBuff), sCharRectPosi[4].Rect.top + (256 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff), Color);
	}

	if (AddVirtualLife[1])
		AddVirtualLife[0] = ((int)sinGetLife() * sinVirtualLifePercent) / 100;

	if (AddVirtualMana[1])
		AddVirtualMana[0] = ((int)sinGetMana() * sinVirtualManaPercent) / 100;

	if (AddVirtualStamina[1])
		AddVirtualStamina[0] = ((int)sinGetStamina() * sinVirtualStaminaPercent) / 100;

	wsprintf(strBuff, "%d/%d", sinGetLife() + AddVirtualLife[0], sinCharDisplay.sHP.sMax + AddVirtualLife[1]);
	dsTextLineOut(0, CheckEditSize(sCharRectPosi[5].Rect.left, sCharRectPosi[5].Rect.right, strBuff), sCharRectPosi[5].Rect.top + (256 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff), CharStatusColor[SkillTextColor[SIN2_LIFE]]);

	wsprintf(strBuff, "%d/%d", sinGetMana(), sinCharDisplay.sMP.sMax);
	dsTextLineOut(0, CheckEditSize(sCharRectPosi[6].Rect.left, sCharRectPosi[6].Rect.right, strBuff), sCharRectPosi[6].Rect.top + (256 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff), CharStatusColor[SkillTextColor[SIN2_MANA]]);

	wsprintf(strBuff, "%d/%d", sinGetStamina(), sinCharDisplay.sSP.sMax);
	dsTextLineOut(0, CheckEditSize(sCharRectPosi[7].Rect.left, sCharRectPosi[7].Rect.right, strBuff), sCharRectPosi[7].Rect.top + (256 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff), CharStatusColor[SkillTextColor[SIN2_STAMINA]]);

	wsprintf(strBuff, "%d", sinCharDisplay.iStrength);
	dsTextLineOut(0, CheckEditSize(sCharRectPosi[8].Rect.left, sCharRectPosi[8].Rect.right, strBuff), sCharRectPosi[8].Rect.top + (256 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff), Color);

	wsprintf(strBuff, "%d", sinCharDisplay.iSpirit);
	dsTextLineOut(0, CheckEditSize(sCharRectPosi[9].Rect.left, sCharRectPosi[9].Rect.right, strBuff), sCharRectPosi[9].Rect.top + (256 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff), Color);

	wsprintf(strBuff, "%d", sinCharDisplay.iTalent);
	dsTextLineOut(0, CheckEditSize(sCharRectPosi[10].Rect.left, sCharRectPosi[10].Rect.right, strBuff), sCharRectPosi[10].Rect.top + (256 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff), Color);

	wsprintf(strBuff, "%d", sinCharDisplay.iAgility);
	dsTextLineOut(0, CheckEditSize(sCharRectPosi[11].Rect.left, sCharRectPosi[11].Rect.right, strBuff), sCharRectPosi[11].Rect.top + (256 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff), Color);

	wsprintf(strBuff, "%d", sinCharDisplay.iHealth);
	dsTextLineOut(0, CheckEditSize(sCharRectPosi[12].Rect.left, sCharRectPosi[12].Rect.right, strBuff), sCharRectPosi[12].Rect.top + (256 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff), Color);

	if (sinChar->iStatPoints)
	{
		wsprintf(strBuff, "%d", sinChar->iStatPoints);
		dsTextLineOut(0, CheckEditSize(sCharRectPosi[23].Rect.left, sCharRectPosi[23].Rect.right, strBuff), sCharRectPosi[23].Rect.top + (256 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff), Color);
	}

	wsprintf(strBuff, "%d", sinCharDisplay.iAttackRating + sDisplayStateShow.Attack_Rate);
	dsTextLineOut(0, CheckEditSize(sCharRectPosi[18].Rect.left, sCharRectPosi[18].Rect.right, strBuff), sCharRectPosi[18].Rect.top + (256 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff), CharStatusColor[SkillTextColor[SIN2_ATTACK_RATE]]);


	if (dwSkillTextTimeFlag == 1)
		SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_BLUE;

	if (dwSkillTextTimeFlag == 2)
		SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_YELLOW;

	int DisplayDamage2[2] = { 0,0 };

	DisplayDamage2[0] = sinCharDisplay.iMinDamage + sinTempDamage2[0] + sDisplayStateShow.Damage[0];
	DisplayDamage2[1] = sinCharDisplay.iMaxDamage + sinTempDamage2[1] + sDisplayStateShow.Damage[1];
	if (DisplayDamage2[0] < 0)
		DisplayDamage2[0] = 0;
	if (DisplayDamage2[1] < 0)
		DisplayDamage2[1] = 0;

	wsprintf(strBuff, "%d-%d", DisplayDamage2[0], DisplayDamage2[1]);
	dsTextLineOut(0, CheckEditSize(sCharRectPosi[19].Rect.left, sCharRectPosi[19].Rect.right, strBuff), sCharRectPosi[19].Rect.top + (256 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff), CharStatusColor[SkillTextColor[SIN2_DAMAGE]]);

	wsprintf(strBuff, "%d", sinCharDisplay.iDefenseRating + sDisplayStateShow.Defense);
	dsTextLineOut(0, CheckEditSize(sCharRectPosi[20].Rect.left, sCharRectPosi[20].Rect.right, strBuff), sCharRectPosi[20].Rect.top + (256 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff), CharStatusColor[SkillTextColor[SIN2_DEFENSE]]);

	wsprintf(strBuff, "%d", sinCharDisplay.iAbsorbRating + sinTempAbsorb + sDisplayStateShow.Absorb);
	dsTextLineOut(0, CheckEditSize(sCharRectPosi[21].Rect.left, sCharRectPosi[21].Rect.right, strBuff), sCharRectPosi[21].Rect.top + (256 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff), CharStatusColor[SkillTextColor[SIN2_ABSORB]]);

	wsprintf(strBuff, "%d", sinCharDisplay.iMovementSpeed);
	dsTextLineOut(0, CheckEditSize(sCharRectPosi[22].Rect.left, sCharRectPosi[22].Rect.right, strBuff), sCharRectPosi[22].Rect.top + (256 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff), CharStatusColor[SkillTextColor[SIN2_SPEED]]);

	wsprintf(strBuff, "%d", sinCharDisplay.sElementalDef[0]);
	dsTextLineOut(0, CheckEditSize(sCharRectPosi[13].Rect.left, sCharRectPosi[13].Rect.right, strBuff), sCharRectPosi[13].Rect.top + (256 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff), Color);

	wsprintf(strBuff, "%d", sinCharDisplay.sElementalDef[5]);
	dsTextLineOut(0, CheckEditSize(sCharRectPosi[14].Rect.left, sCharRectPosi[14].Rect.right, strBuff), sCharRectPosi[14].Rect.top + (256 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff), Color);

	wsprintf(strBuff, "%d", sinCharDisplay.sElementalDef[2]);
	dsTextLineOut(0, CheckEditSize(sCharRectPosi[15].Rect.left, sCharRectPosi[15].Rect.right, strBuff), sCharRectPosi[15].Rect.top + (256 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff), Color);

	wsprintf(strBuff, "%d", sinCharDisplay.sElementalDef[4]);
	dsTextLineOut(0, CheckEditSize(sCharRectPosi[16].Rect.left, sCharRectPosi[16].Rect.right, strBuff), sCharRectPosi[16].Rect.top + (256 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff), Color);

	wsprintf(strBuff, "%d", sinCharDisplay.sElementalDef[3]);
	dsTextLineOut(0, CheckEditSize(sCharRectPosi[17].Rect.left, sCharRectPosi[17].Rect.right, strBuff), sCharRectPosi[17].Rect.top + (256 - sinMoveKindInter[SIN_CHARSTATUS]), strBuff, lstrlen(strBuff), Color);
}

void cCHARSTATUS::OtherStateShow()
{
	char strBuff[128];
	memset(strBuff, 0, sizeof(strBuff));

	DWORD Color = D3DCOLOR_XRGB(255, 255, 255);
	wsprintf(strBuff, "傍拜加档:%d", sinCharDisplay.iAttackSpeed);
	dsTextLineOut(0, 100, 300, strBuff, lstrlen(strBuff), Color);

	wsprintf(strBuff, "喉钒啦:%d", sinCharDisplay.iBlockRating);
	dsTextLineOut(0, 200, 300, strBuff, lstrlen(strBuff), Color);

	wsprintf(strBuff, "农府萍拿:%d", sinCharDisplay.iBlockRating);
	dsTextLineOut(0, 300, 300, strBuff, lstrlen(strBuff), Color);

	wsprintf(strBuff, "酱泼辨捞:%d", sinCharDisplay.iAttackRange);
	dsTextLineOut(0, 400, 300, strBuff, lstrlen(strBuff), Color);
}

void cCHARSTATUS::CheckLevel()
{
	int UpLevelPoint;
	if (OldLevelTemp - 176 != OldLevel)
		return;
	if (sinChar->iLevel > OldLevel)
	{
		cInvenTory.SetItemToChar();
		UpLevelPoint = sinChar->iLevel - OldLevel;
		CheckCharForm();
		if ((sinChar->iLevel % 2) == 0 && sinChar->iLevel >= 10)
			sinSkill.SkillPoint++;

		if ((sinChar->iLevel % 2) == 0 && sinChar->iLevel >= 60)
			sinSkill.SkillPoint4++;


		sinLevelPoint = sinChar->iLevel - OldLevel;

		if ((sinQuest_levelLog & QUESTBIT_LEVEL_80_2) == QUESTBIT_LEVEL_80_2)
		{
			if ((sinQuest_levelLog & QUESTBIT_LEVEL_90_2) == QUESTBIT_LEVEL_90_2)
			{
				if (sinChar->iLevel >= 90)
					sinChar->iStatPoints += 3;
			}
			if (sinChar->iLevel >= 80)
				sinChar->iStatPoints += 2;
		}
		sinChar->iStatPoints += sinLevelPoint * 5;
		OldLevel = sinChar->iLevel;
		OldLevelTemp = OldLevel + 176;
		ReformCharForm();
		sinSetLife(sinChar->sHP.sMax);
		sinSetMana(sinChar->sMP.sMax);
		sinSetStamina(sinChar->sSP.sMax);
		cInvenTory.CheckDamage();

		if (cHelpPet.PetKind && cHelpPet.PetShow)
		{
			cHelpPet.LevelFlag = 1;
			switch (sinChar->iLevel)
			{
			case 2:
				cHelpPet.PetMessageHelp("*Level_Message2-1");
				cHelpPet.PetMessageHelp("*Level_Message2-2");
				break;
			case 3:
				cHelpPet.PetMessageHelp("*Level_Message3");
				break;
			case 4:
				cHelpPet.PetMessageHelp("*Level_Message4");
				break;
			case 5:
				cHelpPet.PetMessageHelp("*Level_Message5");
				break;
			case 6:
				cHelpPet.PetMessageHelp("*Level_Message6-1");
				cHelpPet.PetMessageHelp("*Level_Message6-2");
				break;
			case 7:
				cHelpPet.PetMessageHelp("*Level_Message7");
				break;
			case 8:
				cHelpPet.PetMessageHelp("*Level_Message8");
				break;
			case 9:
				cHelpPet.PetMessageHelp("*Level_Message9-1");
				cHelpPet.PetMessageHelp("*Level_Message9-2");
				break;
			case 10:
				cHelpPet.PetMessageHelp("*Level_Message10-1");
				cHelpPet.PetMessageHelp("*Level_Message10-2");
				break;
			}

		}
		ResetEnergyGraph(3);

		void InitHelp();
		InitHelp();
	}
}

void cCHARSTATUS::BackUpsinCharState(Unit *pChar)
{

}

int cCHARSTATUS::sinGetNowExp()
{
	INT64 sinExp64 = 0;
	int   sinExp = 0;
	sinExp64 = GAMEUNIT->GetExp(lpCurPlayer);
	if (sinChar->iLevel > 79)
		sinExp = (int)(sinExp64 / 1000000);
	else
		sinExp = (int)(sinExp64);

	return sinExp;

}
int cCHARSTATUS::sinGetNextExp()
{
	int sinExp = 0;

	if (sinChar->iLevel > 79)
		sinExp = (int)((GetNextExp(sinChar->iLevel) / 1000000));
	else
		sinExp = (int)GetNextExp(sinChar->iLevel);

	return sinExp;
}
int cCHARSTATUS::InitCharStatus(int kind)
{
	int Total, Total2;

	switch (kind)
	{
	case 0:
		if (sinChar->wVersion[1] == 1)
		{
			sinSkillPontInitButtonFlag = 0;
			cMessageBox.ShowMessage(MESSAGE_ALREADY_INITSTATE);
			return FALSE;
		}
		sinSkillPontInitButtonFlag = 1;
		sinInitPointPassFlag = 1;
		break;
	}
	cMessageBox.ShowMessage(MESSAGE_GYUNGFUM_OK);
	Total = sinChar->iStrength + sinChar->iSpirit + sinChar->iTalent + sinChar->iAgility + sinChar->iHealth + sinChar->iStatPoints;

	for (int i = 0; i < CHARACTER_JOB_MAX; i++)
	{
		if (sinChar->iClass == TempNewCharacterInit[i][0])
		{
			sinChar->iStrength = TempNewCharacterInit[i][1] + sinTempStatus[0];
			sinChar->iSpirit = TempNewCharacterInit[i][2] + sinTempStatus[1];
			sinChar->iTalent = TempNewCharacterInit[i][3] + sinTempStatus[2];
			sinChar->iAgility = TempNewCharacterInit[i][4] + sinTempStatus[3];
			sinChar->iHealth = TempNewCharacterInit[i][5] + sinTempStatus[4];
			Total2 = sinChar->iStrength + sinChar->iSpirit + sinChar->iTalent + sinChar->iAgility + sinChar->iHealth;
			sinChar->iStatPoints = Total - Total2;
			sinChar->wVersion[1] = 1;
			ReformCharForm();
			cInvenTory.SetItemToChar();
			return TRUE;
		}
		if (sinChar->iClass == MorNewCharacterInit[i][0])
		{
			sinChar->iStrength = MorNewCharacterInit[i][1] + sinTempStatus[0];
			sinChar->iSpirit = MorNewCharacterInit[i][2] + sinTempStatus[1];
			sinChar->iTalent = MorNewCharacterInit[i][3] + sinTempStatus[2];
			sinChar->iAgility = MorNewCharacterInit[i][4] + sinTempStatus[3];
			sinChar->iHealth = MorNewCharacterInit[i][5] + sinTempStatus[4];
			Total2 = sinChar->iStrength + sinChar->iSpirit + sinChar->iTalent + sinChar->iAgility + sinChar->iHealth;
			sinChar->iStatPoints = Total - Total2;
			sinChar->wVersion[1] = 1;
			ReformCharForm();
			cInvenTory.SetItemToChar();
			return TRUE;
		}
	}

	return TRUE;
}
int cCHARSTATUS::CheckChageStateDisplay()
{
	ZeroMemory(&sDisplayStateShow, sizeof(sDISPLAYSTATE));
	for (int i = 0; i < 10; i++)
	{
		if (sDisplayState[i].MaxTime)
		{
			sDisplayStateShow.Absorb += sDisplayState[i].Absorb;
			sDisplayStateShow.Attack_Rate += sDisplayState[i].Attack_Rate;
			sDisplayStateShow.Damage[0] += sDisplayState[i].Damage[0];
			sDisplayStateShow.Damage[1] += sDisplayState[i].Damage[1];
			if (sDisplayState[i].PercentDamage[0])
				sDisplayStateShow.Damage[0] += (short)(sinChar->iMinDamage * sDisplayState[i].PercentDamage[0]) / 100;
			if (sDisplayState[i].PercentDamage[1])
				sDisplayStateShow.Damage[1] += (short)(sinChar->iMaxDamage * sDisplayState[i].PercentDamage[1]) / 100;

			sDisplayStateShow.Defense += sDisplayState[i].Defense;

			if (sDisplayStateShow.Absorb < 0)
				SkillTextColor[SIN2_ABSORB] = SIN_TEXT_COLOR_RED;
			if (sDisplayStateShow.Defense < 0)
				SkillTextColor[SIN2_DEFENSE] = SIN_TEXT_COLOR_RED;
			if (sDisplayStateShow.Damage[0] < 0 || sDisplayStateShow.Damage[1])
				SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_RED;

			if (sDisplayState[i].MaxTime <= dwPlayTime)
			{
				ZeroMemory(&sDisplayState[i], sizeof(sDISPLAYSTATE));
				cInvenTory.SetItemToChar();
			}
		}
	}
	if (sinQuest_Level90_2.CODE && sinQuest_Level90_2.State >= 2)
		SkillTextColor[SIN2_DAMAGE] = SIN_TEXT_COLOR_RED;

	return TRUE;
}
int cCHARSTATUS::UseGravityScrool()
{
	float fstrength, fhealth, ftalent, fLevel, fSpirit;

	fstrength = (float)sinChar->iStrength;
	fhealth = (float)sinChar->iHealth;
	ftalent = (float)sinChar->iTalent;
	fSpirit = (float)sinChar->iSpirit;
	fLevel = (float)sinChar->iLevel;

	if (sinChar->GravityScroolCheck[0] == 0)
		sinChar->sWeight.sMax= (short)(((fstrength * 2) + (fhealth*1.5) + fLevel * 3) + 60);

	else if (sinChar->GravityScroolCheck[0] > 0)
		sinChar->sWeight.sMax = (short)(((fstrength * 2) + (fhealth*1.5) + fLevel * 3) + 60) + (sinChar->GravityScroolCheck[0]) * 50;

	sinChar->wVersion[1] = 1;
	ReformCharForm();
	cInvenTory.SetItemToChar();

	return TRUE;
}

int cCHARSTATUS::InitCharStatus_Attribute(int kind)
{
	int Total, Total2;
	int Brood_code = 0;
	int Job_Num = 0;

	cMessageBox.ShowMessage(MESSAGE_GYUNGFUM_OK);
	Total = sinChar->iStrength + sinChar->iSpirit + sinChar->iTalent + sinChar->iAgility + sinChar->iHealth + sinChar->iStatPoints;

	for (int i = 0; i < CHARACTER_JOB_MAX; i++)
	{
		if (sinChar->iClass == TempNewCharacterInit[i][0])
		{
			Brood_code = BROOD_CODE_TEMPSKRON;
			Job_Num = i;
		}
		if (sinChar->iClass == MorNewCharacterInit[i][0])
		{
			Brood_code = BROOD_CODE_MORAYION;
			Job_Num = i;
		}
	}

	if (Brood_code == BROOD_CODE_TEMPSKRON)
	{
		switch (kind)
		{
		case 1:
			sinChar->iStrength = TempNewCharacterInit[Job_Num][1];
			break;
		case 2:
			sinChar->iSpirit = TempNewCharacterInit[Job_Num][2];
			break;
		case 3:
			sinChar->iTalent = TempNewCharacterInit[Job_Num][3];
			break;
		case 4:
			sinChar->iAgility = TempNewCharacterInit[Job_Num][4];
			break;
		case 5:
			sinChar->iHealth = TempNewCharacterInit[Job_Num][5];
			break;
		}
	}
	else
	{
		switch (kind)
		{
		case 1:
			sinChar->iStrength = MorNewCharacterInit[Job_Num][1];
			break;
		case 2:
			sinChar->iSpirit = MorNewCharacterInit[Job_Num][2];
			break;
		case 3:
			sinChar->iTalent = MorNewCharacterInit[Job_Num][3];
			break;
		case 4:
			sinChar->iAgility = MorNewCharacterInit[Job_Num][4];
			break;
		case 5:
			sinChar->iHealth = MorNewCharacterInit[Job_Num][5];
			break;
		}
	}

	sinPlaySound(SIN_SOUND_EAT_POTION2);
	StartEffect(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, EFFECT_AGING);

	Total2 = sinChar->iStrength + sinChar->iSpirit + sinChar->iTalent + sinChar->iAgility + sinChar->iHealth;
	sinChar->iStatPoints = Total - Total2;
	sinChar->wVersion[1] = 1;
	ReformCharForm();
	cInvenTory.SetItemToChar();

	return TRUE;
}
