#include "StdAfx.h"

#include "smwsock.h"
#include "character.h"
#include "playmain.h"
#include "srcsound\\dxwav.h"
#include "fileread.h"

#include "particle.h"
#include "netplay.h"

#include "effectsnd.h"

#include "record.h"
#include "playsub.h"
#include "skillsub.h"
#include "damage.h"

#include "tjboy\\clanmenu\\tjclanDEF.h"
#include "tjboy\\clanmenu\\tjclan.h"
#include "tjboy\\clanmenu\\cE_CViewClanInfo.h"

#include "cracker.h"
#include "damage.h"
#include "AreaServer.h"

extern HWND hwnd;
extern int MouseButton[3];

//ÇÊµå¸Ê ·Îµù
int LoadFieldMap(int PosNum, BaseMap *lpField, smSTAGE3D *lpStage);

DWORD dwRainTime = 0;

//¹«´ë ¼¼Æ® Å¬·¡½º´Ù!
smSTAGE3D		*smStage = 0;
smSTAGE3D		*smGameStage[2] = { 0,0 };


rsRECORD_DBASE	rsRecorder;					//¼­¹ö¿¡ °ÔÀÓµ¥ÀÌÅ¸ ±â·ÏÀåÄ¡

char szGameStageName[2][64];
DWORD			dwPlayTime = 0;					//ÇöÀçÀÇ À©µµ¿ì ½Ã°£ ( ÇÃ·¹ÀÌ ¿ë )
DWORD			dwMemError = 8080;				//¸Þ¸ð¸® ¿¡·¯ È®ÀÎ ÄÚµå

int	smStageCount = 0;

int	NightDayTime = 0;					//¹ã³· ±¸ºÐ

int invPlayerArmor = 0;

DWORD	dwBattleTime = 0;				//ÃÖ±Ù ÀüÅõ ½Ã°£
DWORD	dwBattleQuitTime = 0;			//ÀüÅõÁß Á¾·á ÇÏ·Á ÇÒ¶§
DWORD	dwCloseBoxTime = 0;				//ÀÛ¾÷Ã¢ Á¾·á ¸Þ¼¼Áö

int		RestartPlayCount = 0;					//Àç½ÃÀÛ ¹«Àû ½ÃÀÛ Ä«¿îÆ®

DWORD SkillFalconPoint;					//ÆÈÄÜ ½ºÅ³ Æ÷ÀÎÆ® ÀúÀå¿ë

int InvArmorFileCode[] =
{ 0 ,9,1, 5 };

int	DarkLevel = 0;					//¾îµÒ °ª
int	BackColor_R = 0;				//¹è°æ»ö R
int	BackColor_G = 0;				//¹è°æ»ö G
int	BackColor_B = 0;				//¹è°æ»ö B

int	BackColor_mR = 0;				//¹è°æ»ö º¯°æ°ª R
int	BackColor_mG = 0;				//¹è°æ»ö º¯°æ°ª G
int	BackColor_mB = 0;				//¹è°æ»ö º¯°æ°ª B

int	DarkLevel_Fix = 0;				//¾îµÒ °ª °íÁ¤

int	DarkLightRange = 180 * fONE;		//¾îµÎ¿ï¶§ Á¶¸í ¹üÀ§

int DarkLight = 0;

//³¯¾¾ °ü·Ã
int WeatherMode = 0;
int Thunder = 0;

//PK¸ðµå
int	PkMode = 0;

int DispApp_SkillPoint = 0;			//¼³Á¤µÈ ½Ã°£Àû¿ë ½ºÅ³ Æ÷ÀÎÆ®

int rcnt2;

int modelX = 255;
int modelZ = 512;
int wflag = 0;
int wrad = 0;

DWORD	UseEtherCoreCode = 0;			//¿¡Æ¼¸£ ÄÚ¾î »ç¿ë

int	RecordFailCount = 0;				//ÀúÀå ½ÇÇÇ Ä«¿îÅÍ

//°ø°Ý ¹Þ¾ÒÀ»¶§ È¸ÇÇ Ä«¿îÅÍ
int	Record_BlockCount = 0;
int	Record_DefenceCount = 0;
int Record_RecvDamageCount = 0;
int Record_TotalRecvDamageCount = 0;


//È­»ì
//smPAT3D *PatTest;

//È­»ì
smPAT3D *PatArrow;
//¹æÆÐ ÀÌÆåÆ®
smPAT3D *PatEffectShield = 0;
//½ºÆÄÅ©½¯µå ÀÌÆåÆ®
smPAT3D *PatSparkShield = 0;
//µð¹ÙÀÎÀÎÇÒ·¹ÀÌ¼Ç
smPAT3D *PatDivineShield = 0;
//°¡µé¸® ½¯µå
smPAT3D *PatGodlyShield = 0;
//ºí·¹½ºÄ³½½ ¿Õ°ü
smPAT3D *PatCrown = 0;

//±×¸²ÀÚ
smPAT3D *PatShadow[SHADOW_PAT_MAX] = { 0,0,0,0 };

smPAT3D *PatIceFoot[ICE_FOOT_PAT_MAX];


int	Moving_DblClick = 0;
POINT3D	MousePos_DblClick;

POINT3D	TracePos_DblClick;
int TraceMode_DblClick = 0;

int	ActionGameMode = 0;


Unit		*lpCurPlayer = 0;

DWORD	dwRotPlayDelayTime = 0;


scITEM	scItems[DISP_ITEM_MAX];

Unit	chrOtherPlayer[MAX_UNITS];

CharacterData	sCharacterData_Back;			//NPC ¼³Ä¡½Ã ±âº» µ¥ÀÌÅ¸ ÀÓ½Ã ÀúÀå


int	MatEachBox;
int	MatEachMenuBox;
int MatEnergyBox[2];
int MatEnergyBoxNew[2];
int MatLight[4];

int	MatEachTradeButton[2];	//¸Þ´º ¾ÆÀÌÅÛ ±³È¯ ¹öÆ° 
int MatMonBroodImage[8];	//¸ó½ºÅÍ Á¾Á· ÀÌ¹ÌÁö

//µ¿·á È¸º¹ ¿¹¾à°ª
smTRANS_COMMAND	sPartyPosion;
DWORD			dwPartyPosionTime;

smTEXTUREHANDLE	*lpDDS_ParTradeButton[4][2];			//¸Þ´º¹× Æ®·¹ÀÌµå ¹öÆ°
smTEXTUREHANDLE	*lpDDS_ParTradeToolTip[4];			//¸Þ´º¹× Æ®·¹ÀÌµå ÅøÆÁ


//ºÒ²É ¾Ö´Ï¸ÞÀÌ¼Ç
char *szFlame[8] = {
	"image\\flame1.bmp",
	"image\\flame2.bmp",
	"image\\flame3.bmp",
	"image\\flame4.bmp",
	"image\\flame5.bmp",
	"image\\flame6.bmp",
	"image\\flame7.bmp",
	"image\\flame8.bmp"
};

char *szShine[] = {
	"image\\shine0.bmp",
	"image\\shine2.bmp",
	"image\\shine4.bmp",
	"image\\shine6.bmp",
	"image\\shine8.bmp",
	""
};

char *szBlood1[] = {
	"image\\blood\\b1_001.tga",
	"image\\blood\\b1_002.tga",
	"image\\blood\\b1_003.tga",
	"image\\blood\\b1_004.tga"
};

char *szBlood2[] = {
	"image\\blood\\b2_001.tga",
	"image\\blood\\b2_002.tga",
	"image\\blood\\b2_003.tga",
	"image\\blood\\b2_004.tga"
};


char *szShadowImageFile = "image\\bshadow.bmp";


char *g_IceFootImageFileBuff[ICE_FOOT_PAT_MAX] =
{
	"image\\mk-r.tga",
	"image\\mk-l.tga",
};



//¹è°æ ·Î´õ ÃÊ±âÈ­
void InitStageLoader()
{
	szGameStageName[0][0] = 0;
	szGameStageName[1][0] = 0;
	smGameStage[0] = 0;
	smGameStage[1] = 0;
}

int PlayCounter = 0;

char PlayerName[64] = { 0,0,0,0 };


Point3D InitStage()
{
	szGameStageName[0][0] = 0;
	szGameStageName[1][0] = 0;

	InitFieldMap();

	Point3D sPosition;

	if (GameStartField < 0)
	{
		sPosition = GAMEMAP->WarpMap();
	}
	else
	{
		Point3D s = Point3D(1746, 0, -19756) * 256;

		if (CharacterPosX == s.iX && CharacterPosZ == s.iZ)
		{
			GAMEMAP->WarpMap(MAPID_RicartenTown);
			sPosition = s;
		}
		else
			GAMEMAP->WarpMap((EMapID)GameStartField, CharacterPosX, CharacterPosZ);
	}

	smRender.Color_R = 0;
	smRender.Color_G = 0;
	smRender.Color_B = 0;
	smRender.Color_A = 0;

	return sPosition;
}


void CloseStage()
{
	DELET(smGameStage[1]);
	DELET(smGameStage[0]);
}


struct _DRAW_LIGHTLIST {
	smLIGHT3D	*smLight;
	int			x, y, z;
};


_DRAW_LIGHTLIST	DrawLight[64];
_DRAW_LIGHTLIST	DrawLightSmall[64];
int DrawLightCnt;
int DrawLightSmallCnt;


int DrawLightImage(smSTAGE3D *lpStage, int x, int y, int z)
{
	POINT	Pos;
	RECT	Rect;

	int cnt, cnt2;
	int dx, dy, dz, dist;
	int tz;

	int x1, y1, z1, x2, y2, z2, x3, y3, z3;
	smRENDFACE *rendface;
	smRENDVERTEX *rv;
	int flg;

	int type;

	for (cnt = 0; cnt < lpStage->nLight; cnt++)
	{
		type = lpStage->smLight[cnt].type;

		if ((type&smLIGHT_TYPE_LENS) && (!(lpStage->smLight[cnt].type&smLIGHT_TYPE_NIGHT) || NightDayTime))
		{
			dx = (x - lpStage->smLight[cnt].x) >> FLOATNS;
			dy = (y - lpStage->smLight[cnt].y) >> FLOATNS;
			dz = (z - lpStage->smLight[cnt].z) >> FLOATNS;
			dist = dx * dx + dy * dy + dz * dz;

			if (dist < DIST_TRANSLEVEL_LOW && abs(dx) < 64 * 38 && abs(dz) < 64 * 38)
			{
				if (tz = smRender.GetRect2D(lpStage->smLight[cnt].x, lpStage->smLight[cnt].y, lpStage->smLight[cnt].z, 0, 0, &Rect, &Pos))
				{

					if (Pos.x > 0 && Pos.x < (int)RESOLUTION_WIDTH && Pos.y>0 && Pos.y < (int)RESOLUTION_HEIGHT)
					{
						tz -= 64 * fONE;

						if (tz > (64 * 22 * fONE))
						{
							DrawLightSmall[DrawLightSmallCnt].smLight = &lpStage->smLight[cnt];
							DrawLightSmall[DrawLightSmallCnt].x = Pos.x;
							DrawLightSmall[DrawLightSmallCnt].y = Pos.y;
							DrawLightSmall[DrawLightSmallCnt].z = tz;
							DrawLightSmallCnt++;
						}
						else
						{
							for (cnt2 = 0; cnt2 < smRender.nRendFace; cnt2++)
							{
								if (!(smRender.RendFace[cnt2].ClipStatus&SMCLIP_DISPLAYOUT))
								{
									rendface = &smRender.RendFace[cnt2];

									rv = rendface->lpRendVertex[0];
									x1 = (int)rv->xy[0];
									y1 = (int)rv->xy[1];
									z1 = rv->tz;
									rv = rendface->lpRendVertex[1];
									x2 = (int)rv->xy[0];
									y2 = (int)rv->xy[1];
									z2 = rv->tz;
									rv = rendface->lpRendVertex[2];
									x3 = (int)rv->xy[0];
									y3 = (int)rv->xy[1];
									z3 = rv->tz;

									flg = 0;
									if (tz > z1 && tz > z2 && tz > z3)
									{

										if (Pos.x < x1 && Pos.x < x2 && Pos.x < x3) flg++;
										if (Pos.x > x1 && Pos.x > x2 && Pos.x > x3) flg++;
										if (Pos.y < y1 && Pos.y < y2 && Pos.y < y3) flg++;
										if (Pos.y > y1 && Pos.y > y2 && Pos.y > y3) flg++;
										if (flg == 0) break;
									}
								}
							}
							if (cnt2 >= smRender.nRendFace)
							{
								DrawLight[DrawLightCnt].smLight = &lpStage->smLight[cnt];
								DrawLight[DrawLightCnt].x = Pos.x;
								DrawLight[DrawLightCnt].y = Pos.y;
								DrawLight[DrawLightCnt].z = tz;
								DrawLightCnt++;
							}
							else
							{
								DrawLightSmall[DrawLightSmallCnt].smLight = &lpStage->smLight[cnt];
								DrawLightSmall[DrawLightSmallCnt].x = Pos.x;
								DrawLightSmall[DrawLightSmallCnt].y = Pos.y;
								DrawLightSmall[DrawLightSmallCnt].z = tz;
								DrawLightSmallCnt++;
							}
						}
					}
				}
			}
		}
	}

	return TRUE;
}


int DrawLightImage()
{
	smFACE2D face2d;
	int size;
	smRENDFACE *RendFace;
	int cnt;

	smRender.SetMaterialGroup(smMaterialGroup);

	smRender.Init();

	for (cnt = 0; cnt < DrawLightSmallCnt; cnt++)
	{
		size = 40 * fONE;

		if (size > 0)
		{
			face2d.TexRect.left = 0;
			face2d.TexRect.right = 1;
			face2d.TexRect.top = 0;
			face2d.TexRect.bottom = 1;
			face2d.width = size;
			face2d.height = size;
			face2d.Transparency = 255;
			face2d.r = 255; face2d.g = 255; face2d.b = 255;
			face2d.x = DrawLightSmall[cnt].smLight->x;
			face2d.y = DrawLightSmall[cnt].smLight->y;
			face2d.z = DrawLightSmall[cnt].smLight->z;
			face2d.MatNum = MatLight[1];

			RendFace = smRender.AddFace2D(&face2d);
		}
	}

	if (smRender.nRendFace > 0)
	{
		smRender.SetClipStates(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);
		smRender.ClipRendFace();
		smRender.GeomVertex2D(FALSE);
		smRender.RenderD3D();
	}

	smRender.Init();

	for (cnt = 0; cnt < DrawLightCnt; cnt++)
	{
		size = 160 * fONE;

		if (size > 0)
		{
			face2d.TexRect.left = 0;
			face2d.TexRect.right = 1;
			face2d.TexRect.top = 0;
			face2d.TexRect.bottom = 1;
			face2d.width = size;
			face2d.height = size;
			face2d.Transparency = 255;
			face2d.r = 255; face2d.g = 255; face2d.b = 255;
			face2d.x = DrawLight[cnt].smLight->x;
			face2d.y = DrawLight[cnt].smLight->y;
			face2d.z = DrawLight[cnt].smLight->z;
			face2d.MatNum = MatLight[0];

			RendFace = smRender.AddFace2D(&face2d);
		}
	}

	if (smRender.nRendFace > 0)
	{
		smRender.SetClipStates(SMCLIP_LEFT | SMCLIP_RIGHT | SMCLIP_TOP | SMCLIP_BOTTOM);
		smRender.ClipRendFace();
		smRender.GeomVertex2D(FALSE);
		for (cnt = 0; cnt < smRender.nRendVertex; cnt++)
			smRender.RendVertex[cnt].zb = 0.001f;
		smRender.RenderD3D();
	}


	return TRUE;

}

int SetStageDynLight(smSTAGE3D *lpStage, int x, int y, int z)
{
	int cnt;
	int dx, dy, dz, dist;
	int type;

	for (cnt = 0; cnt < lpStage->nLight; cnt++)
	{
		dx = (x - lpStage->smLight[cnt].x) >> FLOATNS;
		dy = (y - lpStage->smLight[cnt].y) >> FLOATNS;
		dz = (z - lpStage->smLight[cnt].z) >> FLOATNS;
		dist = dx * dx + dy * dy + dz * dz;

		type = lpStage->smLight[cnt].type;

		if (dist < 0x300000 && (type&smLIGHT_TYPE_DYNAMIC) && abs(dx) < 0x2000 && abs(dz) < 0x2000)
		{
			// Ò¹ÍíµÆ¹â
			if ((lpStage->smLight[cnt].type&smLIGHT_TYPE_NIGHT) && NightDayTime)
				smRender.AddDynamicLight(lpStage->smLight[cnt].type, lpStage->smLight[cnt].x, lpStage->smLight[cnt].y, lpStage->smLight[cnt].z, (lpStage->smLight[cnt].r) >> 8, (lpStage->smLight[cnt].g) >> 8, (lpStage->smLight[cnt].b) >> 8, 0, lpStage->smLight[cnt].Range);
			else
			{
				if (DarkLevel > 0)
					smRender.AddDynamicLight(lpStage->smLight[cnt].type, lpStage->smLight[cnt].x, lpStage->smLight[cnt].y, lpStage->smLight[cnt].z, (lpStage->smLight[cnt].r*DarkLevel) >> 8, (lpStage->smLight[cnt].g*DarkLevel) >> 8, (lpStage->smLight[cnt].b*DarkLevel) >> 8, 0, lpStage->smLight[cnt].Range);
				else
					smRender.AddDynamicLight(lpStage->smLight[cnt].type, lpStage->smLight[cnt].x, lpStage->smLight[cnt].y, lpStage->smLight[cnt].z, (lpStage->smLight[cnt].r) >> 8, (lpStage->smLight[cnt].g) >> 8, (lpStage->smLight[cnt].b) >> 8, 0, lpStage->smLight[cnt].Range);
			}
		}
	}

	return TRUE;
}

int doop = 0;

int DisplayStage(int x, int y, int z, int angX, int angY, int angZ)
{
	int cnt;
	int r, g, b, l;

	DrawLightCnt = 0;
	DrawLightSmallCnt = 0;

	smRender.ZWriteAuto = TRUE;

	if (!SETTINGHANDLE->Get().bHightTextureQuality)
	{
		GRAPHICENGINE->GetDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
		GRAPHICENGINE->GetDevice()->SetSamplerState(0, D3DSAMP_MAXMIPLEVEL, 16);
	}

	for (cnt = 0; cnt < 2; cnt++)
	{
		if (smGameStage[cnt])
		{
			if (DarkLevel > 0 && STAGE_MAP[cnt]->iMapType == MAPTYPE_Town)
			{
				r = smRender.Color_R;
				g = smRender.Color_G;
				b = smRender.Color_B;
				l = smRender.nRendLight;

				smRender.Color_R >>= 1;
				smRender.Color_G >>= 1;
				smRender.Color_B >>= 1;

				if (smRender.nRendLight > 0 && smRender.smRendLight[0].Range == DarkLightRange)
				{
					smRender.smRendLight[0].Range = 0;
					l = 1;
				}
				else
					l = 0;

				if (smGameStage[cnt]->DrawStage2(x, y, z, angX, angY, angZ) == TRUE)
				{
					DrawLightImage(smGameStage[cnt], x, y, z);
					smGameStage[cnt]->StageObject->Draw(x, y, z, angX, angY, angZ);
				}

				smRender.Color_R = r;
				smRender.Color_G = g;
				smRender.Color_B = b;

				if (l)
					smRender.smRendLight[0].Range = DarkLightRange;
			}
			else
			{
				if (smGameStage[cnt]->DrawStage2(x, y, z, angX, angY, angZ) == TRUE)
				{
					DrawLightImage(smGameStage[cnt], x, y, z);
					smGameStage[cnt]->StageObject->Draw(x, y, z, angX, angY, angZ);
				}
			}
		}
	}

	if (!SETTINGHANDLE->Get().bHightTextureQuality)
		GRAPHICENGINE->GetDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);

	smRender.ZWriteAuto = FALSE;

	if ((MaterialFrame & 0x3F) == 0)
		CheckInvenItemCode();

	return TRUE;
}

void CreatePatIceFoot(int Num, int sizeX, int sizeZ)
{
	int MatShadow = CreateTextureMaterial(g_IceFootImageFileBuff[Num], 0, 0, 0, SMMAT_BLEND_ALPHA);

	smTPOINT tPoint[4];
	tPoint[0].u = 0;
	tPoint[0].v = 0;
	tPoint[1].u = 256;
	tPoint[1].v = 0;
	tPoint[2].u = 0;
	tPoint[2].v = 256;
	tPoint[3].u = 256;
	tPoint[3].v = 256;

	smOBJ3D *objIceFoot = new smOBJ3D(4, 2);
	objIceFoot->AddVertex(-sizeX, -sizeZ, 0);
	objIceFoot->AddVertex(sizeX, -sizeZ, 0);
	objIceFoot->AddVertex(-sizeX, sizeZ, 0);
	objIceFoot->AddVertex(sizeX, sizeZ, 0);

	objIceFoot->AddFace(0, 1, 2, &tPoint[2], &tPoint[3], &tPoint[0]);
	objIceFoot->AddFace(2, 1, 3, &tPoint[0], &tPoint[3], &tPoint[1]);
	objIceFoot->ZeroNormals();

	objIceFoot->SetFaceMaterial(0, MatShadow);
	objIceFoot->SetFaceMaterial(1, MatShadow);

	PatIceFoot[Num] = new smPAT3D;
	PatIceFoot[Num]->AddObject(objIceFoot);
}

void CreatePatShadow(int Num, int sizeX, int sizeZ)
{
	smTPOINT tPoint[4];
	smOBJ3D *objShadow;

	int MatShadow;

	MatShadow = CreateTextureMaterial(szShadowImageFile, 0, 0, 0, SMMAT_BLEND_SHADOW);
	smMaterial[MatShadow].SelfIllum = 1;

	tPoint[0].u = 0;
	tPoint[0].v = 0;
	tPoint[1].u = 256;
	tPoint[1].v = 0;
	tPoint[2].u = 0;
	tPoint[2].v = 256;
	tPoint[3].u = 256;
	tPoint[3].v = 256;


	objShadow = new smOBJ3D(4, 2);
	objShadow->AddVertex(-sizeX, -sizeZ, 0);
	objShadow->AddVertex(sizeX, -sizeZ, 0);
	objShadow->AddVertex(-sizeX, sizeZ, 0);
	objShadow->AddVertex(sizeX, sizeZ, 0);

	objShadow->AddFace(0, 1, 2, &tPoint[0], &tPoint[1], &tPoint[2]);
	objShadow->AddFace(2, 1, 3, &tPoint[2], &tPoint[1], &tPoint[3]);
	objShadow->ZeroNormals();

	objShadow->SetFaceMaterial(0, MatShadow);
	objShadow->SetFaceMaterial(1, MatShadow);

	PatShadow[Num] = new smPAT3D;
	PatShadow[Num]->AddObject(objShadow);
}

void CreatePatShadow2(int Num, int sizeX, int sizeZ)
{
	smTPOINT tPoint[9];
	smOBJ3D *objShadow;

	int MatShadow;

	MatShadow = CreateTextureMaterial(szShadowImageFile, 0, 0, 0, SMMAT_BLEND_SHADOW);
	smMaterial[MatShadow].SelfIllum = 1;

	tPoint[0].u = 0;
	tPoint[0].v = 0;
	tPoint[1].u = 128;
	tPoint[1].v = 0;
	tPoint[2].u = 256;
	tPoint[2].v = 0;

	tPoint[3].u = 0;
	tPoint[3].v = 128;
	tPoint[4].u = 128;
	tPoint[4].v = 128;
	tPoint[5].u = 256;
	tPoint[5].v = 128;

	tPoint[6].u = 0;
	tPoint[6].v = 256;
	tPoint[7].u = 128;
	tPoint[7].v = 256;
	tPoint[8].u = 256;
	tPoint[8].v = 256;


	objShadow = new smOBJ3D(9, 8);
	objShadow->AddVertex(-sizeX, -sizeZ, 0);
	objShadow->AddVertex(0, -sizeZ, 0);
	objShadow->AddVertex(sizeX, -sizeZ, 0);

	objShadow->AddVertex(-sizeX, 0, 0);
	objShadow->AddVertex(0, 0, 0);
	objShadow->AddVertex(sizeX, 0, 0);

	objShadow->AddVertex(-sizeX, sizeZ, 0);
	objShadow->AddVertex(0, sizeZ, 0);
	objShadow->AddVertex(sizeX, sizeZ, 0);

	objShadow->AddFace(0, 1, 3, &tPoint[0], &tPoint[1], &tPoint[3]);
	objShadow->AddFace(3, 1, 4, &tPoint[3], &tPoint[1], &tPoint[4]);

	objShadow->AddFace(1, 2, 4, &tPoint[0], &tPoint[2], &tPoint[4]);
	objShadow->AddFace(4, 2, 5, &tPoint[4], &tPoint[2], &tPoint[5]);

	objShadow->AddFace(3, 4, 6, &tPoint[3], &tPoint[4], &tPoint[6]);
	objShadow->AddFace(6, 4, 7, &tPoint[6], &tPoint[4], &tPoint[7]);

	objShadow->AddFace(4, 5, 7, &tPoint[4], &tPoint[5], &tPoint[7]);
	objShadow->AddFace(7, 5, 8, &tPoint[7], &tPoint[5], &tPoint[8]);

	objShadow->SetFaceMaterial(0, MatShadow);
	objShadow->SetFaceMaterial(1, MatShadow);
	objShadow->SetFaceMaterial(2, MatShadow);
	objShadow->SetFaceMaterial(3, MatShadow);
	objShadow->SetFaceMaterial(4, MatShadow);
	objShadow->SetFaceMaterial(5, MatShadow);
	objShadow->SetFaceMaterial(6, MatShadow);
	objShadow->SetFaceMaterial(7, MatShadow);

	PatShadow[Num] = new smPAT3D;
	PatShadow[Num]->AddObject(objShadow);
}

static char szDataDirectory[256];
char szCharFileList[256][256];
int CharFileCnt;
int CharPlayCnt = 0;

//ÆÄÀÏ ÀÌ¸§À¸·Î ºÎÅÍ µð·ºÅä¸®¸¦ Ã£¾Æ ¼³Á¤
static char *SetDirectoryFromFile(char *filename)
{
	int len;
	int cnt;

	lstrcpy(szDataDirectory, filename);

	len = lstrlen(szDataDirectory);

	for (cnt = len; cnt >= 0; cnt--)
		if (szDataDirectory[cnt] == '\\') break;

	szDataDirectory[cnt + 1] = NULL;

	return szDataDirectory;
}


//Ä³¸¯ÅÍ ÆÄÀÏ ¸®½ºÆ® ¼³Á¤
int SetCharFileList(char *szCharFile)
{
	CharFileCnt = 0;
	char szFindPath[256];

	SetDirectoryFromFile(szCharFile);

	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;

	lstrcpy(szFindPath, szDataDirectory);
	lstrcat(szFindPath, "\\*.ini");

	//ÆÄÀÏÀ» Ã£À½( È®ÀåÀÚ º¯°æ ÆÄÀÏ )
	hFindHandle = FindFirstFile(szFindPath, &fd);
	if (hFindHandle == INVALID_HANDLE_VALUE) {
		FindClose(hFindHandle);
		return 0;
	}
	while (1) {
		lstrcpy(szCharFileList[CharFileCnt], szDataDirectory);
		lstrcat(szCharFileList[CharFileCnt], fd.cFileName);
		CharFileCnt++;

		if (FindNextFile(hFindHandle, &fd) == FALSE) break;
		if (CharFileCnt > 255) break;
	}
	FindClose(hFindHandle);


	return TRUE;
}

void SetPlayerBodyPattern(char *szBodyFile)
{
	char szBuff[256];
	FILE *fp;

	if (lpCurPlayer->bLoading)
		return;

	wsprintf(szBuff, "char\\tmABCD\\%s.ini", szBodyFile);
	fopen_s(&fp, szBuff, "rb");
	if (!fp)
		return;
	fclose(fp);

	lpCurPlayer->bLoading = TRUE;
	AddLoaderPattern(lpCurPlayer, szBuff, lpCurPlayer->sCharacterData.Player.szHeadModel);
	lpCurPlayer->DisplayTools = TRUE;
}

void SetPlayerPattern(char *szFile)
{
	FILE *fp;

	if (lpCurPlayer->bLoading)
		return;

	fopen_s(&fp, szFile, "rb");
	if (!fp)
		return;
	fclose(fp);

	lpCurPlayer->bLoading = TRUE;
	AddLoaderPattern(lpCurPlayer, szFile, 0);
	lpCurPlayer->DisplayTools = TRUE;

	ReformCharForm();

	lpCurPlayer->sCharacterData.bUpdateInfo[0]++;
	SendSetObjectSerial(lpCurPlayer->iID);

}


char szNpcFileList[64][64];
int NpcFileCnt;
int NpcPlayCnt = 0;

char *NpcSelectedName = 0;

//Ä³¸¯ÅÍ ÆÄÀÏ ¸®½ºÆ® ¼³Á¤
int SetNpcFileList(char *szNpcDirectory)
{
	NpcFileCnt = 0;
	char szFindPath[256];

	HANDLE hFindHandle;
	WIN32_FIND_DATA	fd;

	lstrcpy(szFindPath, szNpcDirectory);
	lstrcat(szFindPath, "*.npc");

	hFindHandle = FindFirstFile(szFindPath, &fd);
	if (hFindHandle == INVALID_HANDLE_VALUE)
	{
		FindClose(hFindHandle);
		return 0;

	}
	while (1)
	{
		lstrcpy(szNpcFileList[NpcFileCnt], szNpcDirectory);
		lstrcat(szNpcFileList[NpcFileCnt], fd.cFileName);
		NpcFileCnt++;

		if (FindNextFile(hFindHandle, &fd) == FALSE) break;
		if (NpcFileCnt > 64) break;

	}
	FindClose(hFindHandle);

	return TRUE;
}

//////////////// µ¿·á È¸º¹ ÇÔ¼ö ////////////////
int LaunchPartyPostion()
{
	int x, y, z, dist, ddist;
	int cnt;
	Unit *lpChar;

	x = lpCurPlayer->pX;
	y = lpCurPlayer->pY + 48 * fONE;
	z = lpCurPlayer->pZ;

	if (sPartyPosion.code == smTRANSCODE_PARTY_POTION)
	{
		if (lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Die)
		{
			CheckCharForm();
			if (sPartyPosion.WParam)
			{
				sinSetLife(sinGetLife() + sPartyPosion.WParam);
				StartEffect(x, y, z, EFFECT_POTION1);
			}
			if (sPartyPosion.LParam)
			{
				sinSetMana(sinGetMana() + sPartyPosion.LParam);
				StartEffect(x, y, z, EFFECT_POTION2);
			}
			if (sPartyPosion.SParam)
			{
				sinSetStamina(sinGetStamina() + sPartyPosion.SParam);
				StartEffect(x, y, z, EFFECT_POTION3);
			}
			ResetEnergyGraph(3);						//¿¡³ÊÁö ±×·¡ÇÁ Ã½Å© ÃÊ±âÈ­
			ReformCharForm();
			sinPlaySound(SIN_SOUND_EAT_POTION, GetDistVolume(x, y, z));			//¹°¾à¸Ô´Â ¼Ò¸®
		}

		for (cnt = 0; cnt < MAX_UNITS; cnt++)
		{
			if (chrOtherPlayer[cnt].bActive && chrOtherPlayer[cnt].iID && chrOtherPlayer[cnt].dwExclusiveNum &&
				chrOtherPlayer[cnt].iID != sPartyPosion.EParam &&
				chrOtherPlayer[cnt].psModelAnimation->iType != ANIMATIONTYPE_Die &&
				chrOtherPlayer[cnt].RendSucess)
			{

				x = chrOtherPlayer[cnt].pX;
				y = chrOtherPlayer[cnt].pY + 48 * fONE;
				z = chrOtherPlayer[cnt].pZ;

				if (sPartyPosion.WParam)
					StartEffect(x, y, z, EFFECT_POTION1);
				if (sPartyPosion.LParam)
					StartEffect(x, y, z, EFFECT_POTION2);
				if (sPartyPosion.SParam)
					StartEffect(x, y, z, EFFECT_POTION3);
			}
		}


	}

	switch (sPartyPosion.code)
	{
	case smTRANSCODE_HEALING:
		if (lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Die)
		{
			CheckCharForm();
			if (sPartyPosion.WParam)
				sinSetLife(sinGetLife() + sPartyPosion.WParam);
			ResetEnergyGraph(0);
			ReformCharForm();
		}
		break;

	case smTRANSCODE_GRAND_HEALING:
		//±×·£µå Èú¸µ
		if (sPartyPosion.EParam == lpCurPlayer->iID) {
			lpChar = lpCurPlayer;
		}
		else
			lpChar = FindAutoPlayer(sPartyPosion.EParam);

		if (!lpChar) break;

		ddist = sPartyPosion.SParam*sPartyPosion.SParam;

		x = (lpCurPlayer->pX - lpChar->pX) >> FLOATNS;
		y = (lpCurPlayer->pY - lpChar->pY) >> FLOATNS;
		z = (lpCurPlayer->pZ - lpChar->pZ) >> FLOATNS;
		dist = x * x + y * y + z * z;
		if (dist < ddist && lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Die) {
			//À¯È¿°Å¸®³» Èú¸µ ½ÇÇà
			if (sPartyPosion.LParam) {
				CheckCharForm();
				sinSetLife(sinGetLife() + sPartyPosion.LParam);
				ResetEnergyGraph(0);						//¿¡³ÊÁö ±×·¡ÇÁ Ã½Å© ÃÊ±âÈ­
				ReformCharForm();
			}

			if (lpChar != lpCurPlayer)
				sinSkillEffect_Great_Healing_Party(lpCurPlayer);
		}


		//ÆÄÆ¼¿øµé Èú¸µ ÀÌÆåÆ®
		for (cnt = 0; cnt < MAX_UNITS; cnt++) {
			if (chrOtherPlayer[cnt].bActive && chrOtherPlayer[cnt].iID && lpChar != &chrOtherPlayer[cnt] &&
				chrOtherPlayer[cnt].dwExclusiveNum && chrOtherPlayer[cnt].psModelAnimation->iType != ANIMATIONTYPE_Die) {

				x = (chrOtherPlayer[cnt].pX - lpChar->pX) >> FLOATNS;
				y = (chrOtherPlayer[cnt].pY - lpChar->pY) >> FLOATNS;
				z = (chrOtherPlayer[cnt].pZ - lpChar->pZ) >> FLOATNS;
				dist = x * x + y * y + z * z;

				if (dist < ddist) {
					sinSkillEffect_Great_Healing_Party(&chrOtherPlayer[cnt]);
				}
			}
		}
		break;
	}

	sPartyPosion.code = 0;
	dwPartyPosionTime = 0;

	return TRUE;
}

//µ¿·á È¸º¹ ¼³Á¤
int SetPartyPosion(smTRANS_COMMAND *lpTransCommand)
{
	if (dwPartyPosionTime) {
		//ÀÌ¹Ì ¿¹¾àÁß
		LaunchPartyPostion();
	}

	dwPartyPosionTime = dwPlayTime + 1000;
	memcpy(&sPartyPosion, lpTransCommand, sizeof(smTRANS_COMMAND));

	return TRUE;
}



char szPlayerCode[32];
int CharacterJob = 0;			//Á÷¾÷ ÄÚµå ³Ñ°ÜÁÜ

char *szAnimShieldEffectFile[] = {
	"Weapons\\test1.tga",
	"Weapons\\test2.tga",
	"Weapons\\test3.tga",
	"Weapons\\test2.tga"
};

char *szBangImage = "weapons\\bang2.bmp";
char *szClowImage = "weapons\\crown.tga";

DWORD	dwSoD_ResultTime = 0;		//SoD »óÈ²Ã¢ °»½Å ½Ã°£


sBILLING_INFO	*sBiInfo = 0;


int InitPat3D(Point3D sPosition)
{
	int cnt, cnt2, size;
	POINT3D Posi, Angle;

	DWORD nsize = 62;

	if (!sBiInfo) {
		sBiInfo = new sBILLING_INFO;
		ZeroMemory(sBiInfo, sizeof(sBILLING_INFO));
	}

	if (PlayerName[0] == 0)
		GetComputerName(PlayerName, &nsize);

	InterfaceParty.chatbuild_INIfiles();

	rsRecorder.dwRecordTime = 0;
	rsRecorder.dwNextRecordTime = GetCurrentTime() + 10 * 60 * 1000;


	cInterFace.sInterFlags.CameraAutoFlag = 2;

	cInterFace.sInterFlags.MapOnFlag = TRUE;
	cInterFace.sInterFlags.RunFlag = TRUE;

	if (((GetCurrentTime() >> 4) & 1) == 0) lstrcpy(szPlayerCode, "p");
	else lstrcpy(szPlayerCode, "f");

	CreatePatIceFoot(0, 6 * fONE, 6 * fONE);
	CreatePatIceFoot(1, 6 * fONE, 6 * fONE);

	CreatePatShadow(0, 12 * fONE, 10 * fONE);
	CreatePatShadow(1, 17 * fONE, 14 * fONE);
	CreatePatShadow2(2, 26 * fONE, 20 * fONE);
	CreatePatShadow2(3, 38 * fONE, 30 * fONE);

	Posi.x = sPosition.iX;
	Posi.y = sPosition.iY;
	Posi.z = sPosition.iZ;
	
	Angle.x = 0;
	Angle.y = 0;
	Angle.z = 0;

	invPlayerArmor = 0;

	LoadOftenArmor();
	LoadOftenFace();
	LoadOftenItem();
	LoadOftenNpc();
	LoadOftenModels();

	sinChar = &lpCurPlayer->sCharacterData;

	CheckCharForm();

	if (CharacterName1[0])
	{
		cnt = NewCharInfo.Dexterity + NewCharInfo.Health + NewCharInfo.Spirit + NewCharInfo.Strength + NewCharInfo.Talent;

		lpCurPlayer->sCharacterData.iClass = (ECharacterClass)NewCharInfo.JobCode;

		if (cnt < 103)
		{
			lpCurPlayer->sCharacterData.iAgility = NewCharInfo.Dexterity;
			lpCurPlayer->sCharacterData.iHealth = NewCharInfo.Health;
			lpCurPlayer->sCharacterData.iSpirit = NewCharInfo.Spirit;
			lpCurPlayer->sCharacterData.iStrength = NewCharInfo.Strength;
			lpCurPlayer->sCharacterData.iTalent = NewCharInfo.Talent;
		}
		else
		{
			lpCurPlayer->sCharacterData.iAgility = 1;
			lpCurPlayer->sCharacterData.iHealth = 8;//NewCharInfo.Health;
			lpCurPlayer->sCharacterData.iSpirit = 1;//NewCharInfo.Spirit;
			lpCurPlayer->sCharacterData.iStrength = 8;//NewCharInfo.Strength;
			lpCurPlayer->sCharacterData.iTalent = 1;//NewCharInfo.Talent;
			lpCurPlayer->sCharacterData.iStatPoints = 0;//NewCharInfo.Talent;
		}
	}
	if (CharacterName1[0])
	{
		SetLoadPattern(lpCurPlayer, CharacterName1, CharacterName2, &Posi, &Angle);

		cnt2 = 0;

		for (cnt = 0; cnt < (int)lpCurPlayer->smMotionInfo->MotionCount; cnt++)
		{
			if (lpCurPlayer->smMotionInfo->MotionInfo[cnt].iType == ANIMATIONTYPE_Die)
			{
				size = lpCurPlayer->smMotionInfo->MotionInfo[cnt].EndFrame - lpCurPlayer->smMotionInfo->MotionInfo[cnt].StartFrame;
				if (size > 8) cnt2++;
			}
			if (lpCurPlayer->smMotionInfo->MotionInfo[cnt].iType == ANIMATIONTYPE_Attack)
			{
				size = lpCurPlayer->smMotionInfo->MotionInfo[cnt].EndFrame - lpCurPlayer->smMotionInfo->MotionInfo[cnt].StartFrame;
				if (size < 40 && !SETTINGHANDLE->Get().bDebugMode)
				{
					GAMESOCKET->iDisconnectTime = TICKCOUNT;
					quit = TRUE;
				}
			}
		}
		if (cnt2 == 0 && !SETTINGHANDLE->Get().bDebugMode)
		{
			GAMESOCKET->iDisconnectTime = TICKCOUNT;
			quit = TRUE;
		}
	}


	lpCurPlayer->sCharacterData.iLevel = 1;

	lpCurPlayer->sCharacterData.iMinDamage = 5;
	lpCurPlayer->sCharacterData.iMaxDamage = 10;

	lstrcpy(lpCurPlayer->sCharacterData.szName, PlayerName);
	lpCurPlayer->sCharacterData.iType = CHARACTERTYPE_Player;
	lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Revive);

	lpCurPlayer->sCharacterData.SizeLevel = 1;
	lpCurPlayer->PatSizeLevel = 1;

	lpCurPlayer->sCharacterData.iAttackRating = 100;
//	lpCurPlayer->sCharacterData.iOwnerID = 1000;

	lpCurPlayer->sUnitInfo.dwHashCharacterName = 0;

	lpCurPlayer->sCharacterData.sHP.sMin = 1000;
	lpCurPlayer->sCharacterData.sHP.sMax = 1000;

	lpCurPlayer->MoveMode = TRUE;
	lpCurPlayer->MoveCnt = 0;

	lpCurPlayer->sCharacterData.CostmePos = 0;

	PkMode = 0;

	ReformCharForm();

	lpCurPlayer->iLoadedMapIndex = -1;
	if (smGameStage[0])
	{
		cnt = smGameStage[0]->GetFloorHeight(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, lpCurPlayer->Pattern->SizeHeight);
		lpCurPlayer->iLoadedMapIndex = 0;
	}
	if (cnt == CLIP_OUT && smGameStage[1])
	{
		lpCurPlayer->iLoadedMapIndex = 1;
	}


	for (cnt = 0; cnt < MAX_UNITS; cnt++)
	{
		chrOtherPlayer[cnt].Init();
	}

	smMATERIAL *mat;

	smASE_SetPhysique(0);
	PatArrow = smASE_Read("weapons\\arrow.ase");
	PatEffectShield = smASE_Read("weapons\\Test8.ASE");
	PatSparkShield = smASE_Read("weapons\\Mc3_sparkShield.ASE");
	PatDivineShield = smASE_Read("weapons\\Nt3_DivineI.ASE");
	PatGodlyShield = smASE_Read("weapons\\Godly_Shield.ASE");
	PatCrown = smASE_Read("weapons\\Crown.ASE");

	if (PatEffectShield)
	{
		PatEffectShield->Frame = 0;

		mat = PatEffectShield->smMaterialGroup->FindMaterialFromTextureName(szBangImage);

		if (mat)
		{
			mat->BlendType = SMMAT_BLEND_ADDCOLOR;
			mat->SelfIllum = 1;
		}
	}

	if (PatCrown)
	{
		PatCrown->Frame = 0;

		mat = PatCrown->smMaterialGroup->FindMaterialFromTextureName(szClowImage);

		if (mat)
		{
			mat->BlendType = SMMAT_BLEND_ADDCOLOR;
			mat->SelfIllum = 1;
		}
	}

	smASE_SetPhysique(0);

	MatEachBox = CreateTextureMaterial("image\\cw.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);

	MatEachMenuBox = CreateTextureMaterial("image\\cw-1.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	MatEachTradeButton[0] = CreateTextureMaterial("image\\CW-trade0.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	MatEachTradeButton[1] = CreateTextureMaterial("image\\CW-trade1.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);

	lpDDS_ParTradeButton[0][0] = LoadDibSurfaceOffscreen("image\\party\\icon-c5_.bmp");
	lpDDS_ParTradeButton[0][1] = LoadDibSurfaceOffscreen("image\\party\\icon-c5.bmp");

	lpDDS_ParTradeButton[1][0] = LoadDibSurfaceOffscreen("image\\party\\icon-c1_.bmp");
	lpDDS_ParTradeButton[1][1] = LoadDibSurfaceOffscreen("image\\party\\icon-c1.bmp");

	lpDDS_ParTradeButton[2][0] = LoadDibSurfaceOffscreen("image\\party\\icon-c2_.bmp");
	lpDDS_ParTradeButton[2][1] = LoadDibSurfaceOffscreen("image\\party\\icon-c2.bmp");

	lpDDS_ParTradeButton[3][0] = LoadDibSurfaceOffscreen("image\\party\\icon_clan_.bmp");
	lpDDS_ParTradeButton[3][1] = LoadDibSurfaceOffscreen("image\\party\\icon_clan.bmp");


	lpDDS_ParTradeToolTip[0] = LoadDibSurfaceOffscreen("image\\party\\ButtonInfo-c5.bmp");
	lpDDS_ParTradeToolTip[1] = LoadDibSurfaceOffscreen("image\\party\\ButtonInfo-c1.bmp");
	lpDDS_ParTradeToolTip[2] = LoadDibSurfaceOffscreen("image\\party\\ButtonInfo-c0.bmp");
	lpDDS_ParTradeToolTip[3] = LoadDibSurfaceOffscreen("image\\party\\ButtonInfo-c10.bmp");

	MatEnergyBox[0] = CreateTextureMaterial("image\\Energy_Red.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	MatEnergyBox[1] = CreateTextureMaterial("image\\Energy_Blue.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);

	MatEnergyBoxNew[0] = CreateTextureMaterial("image\\Energy_Red_New.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	MatEnergyBoxNew[1] = CreateTextureMaterial("image\\Energy_Blue_New.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);

	MatLight[0] = CreateTextureMaterial("image\\glow01.bmp", 0, TRUE, FALSE, SMMAT_BLEND_ADDCOLOR);
	smMaterial[MatLight[0]].SelfIllum = TRUE;
	MatLight[1] = CreateTextureMaterial("image\\glow02.bmp", 0, TRUE, FALSE, SMMAT_BLEND_ADDCOLOR);
	smMaterial[MatLight[1]].SelfIllum = TRUE;

	MatMonBroodImage[0] = CreateTextureMaterial("image\\M_Nm.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	MatMonBroodImage[1] = CreateTextureMaterial("image\\M_Mt.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	MatMonBroodImage[2] = CreateTextureMaterial("image\\M_Un.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	MatMonBroodImage[3] = CreateTextureMaterial("image\\M_D.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);
	MatMonBroodImage[4] = CreateTextureMaterial("image\\M_mc.tga", 0, TRUE, FALSE, SMMAT_BLEND_ALPHA);

	InitWeatherSystem();

	InitParticle();

	InitDynLight();

	UseEtherCoreCode = 0;

	dwPartyPosionTime = 0;

	InitTimeEffect();

#ifdef	_SET_PROCTECT_MEM2

	cnt = Check_PlaySubReleaseFunc();
	if (cnt)
		SendSetHackUser2(1120, cnt);
#endif

	ResetEnergyGraph(3);
	ResetInvenItemCode();
	ResetInvenMoney();

	CheckDLL_Module();

	ZeroMemory(&rsBlessCastle, sizeof(rsBLESS_CASTLE));

	return TRUE;

}

int ClosePat3D()
{
	int cnt;

	ClosePatterns();

	if (PatArrow)
	{
		delete PatArrow;
		PatArrow = NULL;
	}

	if (PatEffectShield)
	{
		delete PatEffectShield;
		PatEffectShield = NULL;
	}
	for (cnt = 0; cnt < ICE_FOOT_PAT_MAX; cnt++)
	{
		if (PatIceFoot[cnt])
		{
			delete PatIceFoot[cnt];
			PatIceFoot[cnt] = NULL;
		}
	}

	for (cnt = SHADOW_PAT_MAX - 1; cnt >= 0; cnt--)
		if (PatShadow[cnt]) delete PatShadow[cnt];

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			DELET(lpDDS_ParTradeButton[i][j]);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		DELET(lpDDS_ParTradeToolTip[i]);
	}

	if (sBiInfo) delete sBiInfo;

	return TRUE;
}

int PartCnt = 0;



//int LoadTest = 0;


int		MsTraceCount = 0;
int		MsTraceMode = 0;
RECT	MsSelRect;
POINT	MsSelPos;

int		SelMouseButton = 0;			//»ç¿ë ¼±ÅÃµÈ ¸¶¿ì½º ¹öÆ°

Unit	*lpCharSelPlayer = 0;		//¼±ÅÃ Ä³¸¯ÅÍ
Unit	*lpCharMsTrace = 0;			//ÀÌµ¿ ¸ñÇ¥ Ä³¸¯ÅÍ

scITEM	*lpSelItem = 0;				//¼±ÅÃµÈ ¾ÆÀÌÅÛ
scITEM	*lpMsTraceItem = 0;			//ÀÌµ¿ ¸ñÇ¥ ¾ÆÀÌÅÛ

int AttFlag = 0;
int	AttCancel;						//°ø°Ý Ãë¼Ò
int	AttAutoCont = 0;				//¿¬¼Ó °ø°Ý ¸ðµå

//°ø°Ý ¼³Á¤
int TraceAttackPlay()
{
	if (lpCharSelPlayer)
	{
		MsTraceMode = TRUE;
		lpCharMsTrace = lpCharSelPlayer;
		AttFlag = TRUE;
		if (VRKeyBuff[VK_SHIFT] && lpCharSelPlayer->sCharacterData.iType == CHARACTERTYPE_Monster)
			AttAutoCont = TRUE;
		else
			AttAutoCont = FALSE;


		if (VRKeyBuff['O'] && SETTINGHANDLE->Get().bDebugMode)
			SkillWarriorBetserker(lpCharSelPlayer, 15);

		return TRUE;
	}

	if (lpSelItem) {
		MsTraceMode = TRUE;
		lpMsTraceItem = lpSelItem;
		return TRUE;
	}

	return FALSE;

}

//°ø°Ý Ãë¼Ò
int CancelAttack()
{
	SelMouseButton = 0;
	MsTraceMode = FALSE;
	lpCharMsTrace = 0;
	lpMsTraceItem = 0;
	AttFlag = 0;

	return TRUE;
}

int	DamageExp(Unit *lpChar, int AttackDamage)
{
	int AttackResult;

	if (AttackDamage && lpChar->sCharacterData.iType == CHARACTERTYPE_Monster && lpChar->sCharacterData.iMonsterType != MONSTERTYPE_Friendly && lpChar->sCharacterData.sHP.sMin > 0)
	{
		AttackResult = (AttackDamage << 8) / lpChar->sCharacterData.sHP.sMax;
		if (AttackResult > 256)
			AttackResult = 256;
		AttackResult = (lpChar->sCharacterData.iExp * AttackResult) >> 8;
		AttackResult /= 10;
		if (AttackResult <= 0)
			AttackResult = 1;
		lpCurPlayer->AttackExp = AttackResult;
	}

	return TRUE;
}

int HardCoreEventArea[4] = { 18516 , 25715, 1541 , 7178 };

POINT3D	HardCoreEventOpenPos[7][3] =
{
	{ // »ð
		{ 18967,  1154,	3055 },
		{ 19995,  1154,	2134 },
		{ 19485,  1154,	2615 }
	},
	{// Ë®
		{ 20838,  1154,	3024 },
		{ 21671,  1154,	2193 },
		{ 21255,  1154,	2615 }
	},
	{// µØ
		{ 22478,  1154,	3049 },
		{ 23437,  1154,	2135 },
		{ 22948,  1154,	2615 }
	},
	{// ·ç
		{ 24204,  1154,	3094 },
		{ 25173,  1154,	2135 },
		{ 24674,  1154,	2615 }
	},
	{// ÔÂ
		{ 20509,  1621,	5284 },
		{ 21544,  1621,	4261 },
		{ 21012,  1621,	4773 }
	},
	{// ÈÕ
		{ 22575,  1621,	5253 },
		{ 23610,  1621,	4230 },
		{ 23077,  1621,	4742 }
	},
	{// ÌìÌÃ
		{ 21538,  1638,	7057 },
		{ 22527,  1638,	6079 },
		{ 22018,  1638,	6569 }
	}
};

int GetSoD_AreaCode(int x, int y, int z)
{
	int mx, my, mz;
	int cnt;

	mx = x >> FLOATNS;
	my = y >> FLOATNS;
	mz = z >> FLOATNS;

	if (y >= HardCoreEventOpenPos[0][0].y - 32)
	{
		if (HardCoreEventArea[0]<mx && HardCoreEventArea[1]>mx && HardCoreEventArea[2]<mz && HardCoreEventArea[3]>mz)
		{
			for (cnt = 0; cnt < 7; cnt++)
			{
				if (mx > HardCoreEventOpenPos[cnt][0].x && mx < HardCoreEventOpenPos[cnt][1].x && mz>HardCoreEventOpenPos[cnt][1].z && mz < HardCoreEventOpenPos[cnt][0].z)
					return cnt;
			}
		}
	}

	return -1;
}

int CheckHardCoreEventArea(int x, int y, int z)
{
	int mx, my, mz;

	mx = x >> FLOATNS;
	my = y >> FLOATNS;
	mz = z >> FLOATNS;

	if (y >= HardCoreEventOpenPos[0][0].y - 32)
	{
		if (HardCoreEventArea[0]<mx && HardCoreEventArea[1]>mx && HardCoreEventArea[2]<mz && HardCoreEventArea[3]>mz)
			return TRUE;
	}

	return FALSE;
}


#define AUTO_DEAD_COUNT		(70*60*8)
int AutoDeathCounter = 0;
int FixedWidth = 200;
DWORD	dwClassDelayTime = 0;


int PlayPat3D()
{
	int cnt;
	int attack;
	int	attack_UserMonster;
	int	attack_RegState;

	int	attackMode;
	sSKILL *lpAttackSkill;
	int	skFlag;

	lpCurPlayer->Main();

	EachPlayerMain();

	AutoDeathCounter++;

	if (PkMode > 0)
		PkMode--;

	if (VRKeyBuff[VK_CONTROL])
		PkMode = TRUE;
	else
		PkMode = FALSE;

	if (lpCurPlayer->iStunTimeLeft)
	{
		if (MsTraceMode)
		{
			CancelAttack();
			lpCurPlayer->MoveFlag = 0;
			MouseButton[0] = 0;
			MouseButton[1] = 0;
			MouseButton[2] = 0;
		}
		if (lpCurPlayer->psModelAnimation && (lpCurPlayer->psModelAnimation->iType == ANIMATIONTYPE_Walking || lpCurPlayer->psModelAnimation->iType == ANIMATIONTYPE_Running))
		{
			lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Idle);
			CancelAttack();
			lpCurPlayer->MoveFlag = 0;
			MouseButton[0] = 0;
			MouseButton[1] = 0;
			MouseButton[2] = 0;
		}
		lpCurPlayer->dwNextMotionCode = 0;
		lpCurPlayer->MotionLoop = 0;
	}

	if (MsTraceMode && 
		lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Attack &&
		lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Potion &&
		lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Skill)
	{
		attackMode = FALSE;
		AttCancel = FALSE;
		attack_UserMonster = FALSE;

		CheckPlaySubFunc2();

		if ((MsTraceCount & 0x1F) == 0)
		{
			lpCurPlayer->MoveFlag = TRUE;
			lpCurPlayer->Angle.y = GetMouseSelAngle();
		}

		int AttackRange = 0;
		int	AttackResult = 0;

		lpAttackSkill = 0;
		switch (SelMouseButton)
		{
		case 1:
			if (sinSkill.pLeftSkill && sinSkill.pLeftSkill->CODE != SKILL_NORMAL_ATTACK)
				lpAttackSkill = sinSkill.pLeftSkill;
			break;
		case 2:
			if (sinSkill.pRightSkill && sinSkill.pRightSkill->CODE != SKILL_NORMAL_ATTACK)
				lpAttackSkill = sinSkill.pRightSkill;
			break;
		}
		if (GAMECHARACTER->IsStageVillage())
			lpAttackSkill = 0;

		if (lpCharMsTrace)
		{
			if (lpCharMsTrace->sCharacterData.sHP.sMin <= 0 || (lpCharMsTrace->dwLastTransTime + DISPLAY_TRANS_TIME_OVER) < dwPlayTime || cTrade.OpenFlag)
				CancelAttack();
			else
			{
				if (!MouseButton[0] && !MouseButton[1])
					AttFlag = 0;

				if (lpCurPlayer->sCharacterData.iType == CHARACTERTYPE_Monster)
					attackMode = TRUE;
				else
				{
					if (PkMode)
						attackMode = TRUE;
				}

				if (lpCharMsTrace->sCharacterData.iMonsterEffectID == snCHAR_SOUND_KELVEZU)
					AttackRange = 130 * fONE;
				else
					AttackRange = 50 * fONE;

				if (lpCurPlayer->dwActionItemCode)
					AttackRange += lpCurPlayer->AttackToolRange;

				if (lpCurPlayer->ShootingMode && lpCharMsTrace->sCharacterData.iType != CHARACTERTYPE_None)
				{
					if (lpCharMsTrace->sCharacterData.iType != CHARACTERTYPE_Player || attackMode)
					{
						if ((lpCurPlayer->dwActionItemCode & sinITEM_MASK2) == sinWD1 && sinChar->iClass == CHARACTERCLASS_Assassin)
						{
							if (lpAttackSkill == NULL)
								AttackRange = 150 * fONE;
						}
						else
							AttackRange = lpCurPlayer->sCharacterData.iAttackRange*fONE;
					}
				}

				if (lpCharMsTrace->sCharacterData.iMonsterEffectID == snCHAR_SOUND_CASTLE_TOWER_B)
					AttackRange += 40 * fONE;

				attack = lpCharMsTrace->sCharacterData.iType;

				if (lpCharMsTrace->sCharacterData.iType == CHARACTERTYPE_Player)
				{
					if (!attackMode || GAMECHARACTER->IsStageVillage())
						attack = 0;
				}

				if (lpCharMsTrace->sCharacterData.iType == CHARACTERTYPE_Monster && lpCharMsTrace->sCharacterData.iMonsterType == MONSTERTYPE_Friendly)
				{
					if (!PkMode)
					{
						attack_UserMonster = TRUE;;
						attack = 0;
					}
				}

				if (lpAttackSkill)
				{
					if (lpAttackSkill->CODE == SKILL_HEALING || lpAttackSkill->CODE == SKILL_ENCHANT_WEAPON || lpAttackSkill->CODE == SKILL_VIRTUAL_LIFE || lpAttackSkill->CODE == SKILL_TRIUMPH_OF_VALHALLA)
					{
						if (attack_UserMonster && lpAttackSkill->CODE == SKILL_HEALING)
							attack_UserMonster = 0;

						skFlag = 1;
					}
					else
						skFlag = 0;

					if ((lpCharMsTrace->sCharacterData.iType == CHARACTERTYPE_Monster && !attack_UserMonster) || (PkMode && lpCharMsTrace->sCharacterData.iType == CHARACTERTYPE_Player) || skFlag)
					{
						cnt = GetSkillDistRange(lpAttackSkill, AttackRange, attack);
						if (cnt)
							AttackRange = cnt;

						attack = 0;
					}
				}
				if (!lpCurPlayer->ShootingFlag && lpCurPlayer->PlayAttackFromPosi(lpCharMsTrace->pX, lpCharMsTrace->pY, lpCharMsTrace->pZ, AttackRange, attack) == TRUE && lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Potion)
				{
					LastAttackDamage = 0;

					if (lpCharMsTrace->sCharacterData.iType == CHARACTERTYPE_Player)
					{
						if (lpCharMsTrace->dwTradeMsgCode)
							Send_ShowMyShopItem(lpCharMsTrace);
						else
						{
							EachTradeButton = 1;

							if ((cldata.myPosition == 101 || cldata.myPosition == 104) &&
								!lpCharMsTrace->sCharacterData.iClanID)

								EachTradeButtonMode = TRUE;
							else
								EachTradeButtonMode = FALSE;
						}
					}
					else
						EachTradeButton = 0;

					if (lpCharMsTrace->sCharacterData.iType == CHARACTERTYPE_None)
					{
						OpenEachPlayer(lpCharMsTrace);
						DispEachMode = TRUE;
					}

					lpCurPlayer->chrAttackTarget = lpCharMsTrace;
					lpCurPlayer->AttackExp = 0;

					lpCurPlayer->AttackCritcal = FALSE;

					if (!attack_UserMonster && (lpCharMsTrace->sCharacterData.iType != CHARACTERTYPE_Player || GAMECHARACTER->IsStageVillage()))
					{
						AttackResult = TRUE;

						if (!PlaySkillAttack(lpAttackSkill, lpCharMsTrace))
						{
							if (attack || lpCharMsTrace->sCharacterData.iType != CHARACTERTYPE_Player)
							{
								if (lpCurPlayer->ShootingMode && lpCharMsTrace->sCharacterData.iType != CHARACTERTYPE_NPC)
								{
									if (lpCurPlayer->CheckShootingTest(lpCharMsTrace) == TRUE)
										AttackResult = dm_SendTransDamage(lpCharMsTrace, 0, 0, 0, 0, lpCurPlayer->AttackSkil, TRUE);
									else
									{
										lpCurPlayer->AttackCritcal = -1;
										lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Idle);
									}
								}
								else
								{
									attack_RegState = 0;

									if (lpCharMsTrace->sCharacterData.iType == CHARACTERTYPE_NPC)
									{
										if (sinQuest_ChangeJob2.CODE)
										{
											attack_RegState = (sinQuest_ChangeJob2.CODE << 16);
											if (sinQuest_ChangeJob2.CODE == SIN_QUEST_CODE_CHANGEJOB2_NPC_M || sinQuest_ChangeJob2.CODE == SIN_QUEST_CODE_CHANGEJOB2_NPC_D)
											{
												if (!cInvenTory.SearchItemCode(sinMA1 | sin01) && !cInvenTory.SearchItemCode(sinQT1 | sin04) && !cInvenTory.SearchItemCode(sinQT1 | sin05))
													attack_RegState |= 1;
											}
										}
										if (dwClassDelayTime < dwPlayTime)
										{
											if (lpCharMsTrace->sCharacterData.sGlow)
											{
												switch (lpCharMsTrace->sCharacterData.sGlow)
												{
													//Àï²éÔÓ»õµê
												case 1001:
													if (GetRace(lpCurPlayer->sCharacterData.iClass) == BROOD_CODE_TEMPSKRON)
													{
														chaQuest.haElementaryQuest_A(0);
														sinCheckLevelQuest30();
													}
													break;
													//·Æ¶ûÀ­ÔÓ»õµê
												case 1002:
													if (GetRace(lpCurPlayer->sCharacterData.iClass) == BROOD_CODE_MORAYION)
													{
														chaQuest.haElementaryQuest_A(0);
														sinCheckLevelQuest30();
													}
													break;
													//¼¼ÄÜÊ¦
												case 1003:
													if (GetRace(lpCurPlayer->sCharacterData.iClass) == BROOD_CODE_TEMPSKRON)
													{
														chaQuest.haElementaryQuest_C();
														sinCheckLevelQuest55();
													}
													break;
													//¼¼ÄÜÊ¦
												case 1004:
													if (GetRace(lpCurPlayer->sCharacterData.iClass) == BROOD_CODE_MORAYION)
													{
														chaQuest.haElementaryQuest_C();
														sinCheckLevelQuest55_2();
													}
													break;
													// »ÞÆøËÂÃíÃÅ¿Ú
												case 1005:
													sinCheckLevelQuest70();
													chaQuest.haElementaryQuest_J();
													sinCheckLevelQuest80();
													sinCheckLevelQuest85();
													break;
													// Á¦Á¿´óÊ¦
												case 1006:
													sinCheckLevelQuest90();
													break;
													// ÄÚÎ¬Ë¹¿Ë¾ÓÃñ
												case 1011:
													sinCheckLevelQuest80_2(1);
													break;
													// 2¼¶¾ôÊ¿
												case 1012:
													sinCheckLevelQuest80_2(0);
													sinCheckLevelQuest90_2(0);
													break;
													// ·Æ¶ûÀ­Ä§·¨Ê¦
												case 1013:
													sinCheckLevelQuest90_2(1);
													//chaQuest.showFuryQuest();
													break;
													//ºÏ³ÉÊ¦
												case 1014:
													if (GetRace(lpCurPlayer->sCharacterData.iClass) == BROOD_CODE_TEMPSKRON)
														chaQuest.haElementaryQuest_A(1);
													break;
													//¶ÍÔìÊ¦
												case 1015:
													if (GetRace(lpCurPlayer->sCharacterData.iClass) == BROOD_CODE_MORAYION)
														chaQuest.haElementaryQuest_A(1);
													break;
													//·Æ¶ûÀ­ÊØÎÀ
												case 1016:
													if (GetRace(lpCurPlayer->sCharacterData.iClass) == BROOD_CODE_TEMPSKRON)
														chaQuest.haElementaryQuest_B(BROOD_CODE_TEMPSKRON);
													break;
													//Àï²éÊØÎÀ
												case 1017:
													if (GetRace(lpCurPlayer->sCharacterData.iClass) == BROOD_CODE_MORAYION)
														chaQuest.haElementaryQuest_B(BROOD_CODE_MORAYION);
													break;
													//·Æ¶ûÀ­²Ö¿â
												case 1018:
													chaQuest.haElementaryQuest_D(0);
													break;
													//ÂÞ¸ñË¹
												case 1019:
													chaQuest.haElementaryQuest_D(1);
													chaQuest.haElementaryQuest_M();
													break;
													// ÂÞË¹
												case 1020:
													chaQuest.haElementaryQuest_E();
													break;
													// ¹ÅµÇ
												case 1021:
													if (GetRace(lpCurPlayer->sCharacterData.iClass) == BROOD_CODE_TEMPSKRON)
														chaQuest.haElementaryQuest_F();
													break;
													// ÌØË¹
												case 1022:
													if (GetRace(lpCurPlayer->sCharacterData.iClass) == BROOD_CODE_MORAYION)
														chaQuest.haElementaryQuest_F();
													break;
													// ÄÚÎ¬Ë¹¿ËÔÓ»õµê
												case 1023:
													chaQuest.haElementaryQuest_G();
													break;
													// µØÀÎ1NPC
												case 1024:
													chaQuest.haElementaryQuest_H();
													break;
													// Ä¢¹½¶´NPC
												case 1025:
													if (GetRace(lpCurPlayer->sCharacterData.iClass) == BROOD_CODE_TEMPSKRON)
														chaQuest.haElementaryQuest_I();
													break;
													// ÃÛ·ä¶´NPC
												case 1026:
													if (GetRace(lpCurPlayer->sCharacterData.iClass) == BROOD_CODE_MORAYION)
														chaQuest.haElementaryQuest_I();
													break;
													// ÀÇÎÑNPC
												case 1027:
													chaQuest.haElementaryQuest_K();
													break;
												}

												//HaCheckQuestNpc(lpCharMsTrace->sCharacterData.sGlow);

												dwClassDelayTime = dwPlayTime + 1000 * 5;
											}
										}
									}

									AttackResult = dm_SendTransDamage(lpCharMsTrace, 0, 0, 0, attack_RegState, lpCurPlayer->AttackSkil, TRUE);
								}
								if ((AttackResult && lpCurPlayer->WeaponEffect == (sITEMINFO_LIGHTING + 1) || AttackResult && lpCurPlayer->WeaponEffect == (sITEMINFO_ICE + 1) || AttackResult && lpCurPlayer->WeaponEffect == (sITEMINFO_FIRE + 1)) && lpCurPlayer->EnchantEffect_Point > 0 && lpCurPlayer->EnchantEffect_Point <= 10)
								{
									if (lpCurPlayer->AttackCritcal >= 0)
									{
										dm_SelectRange(lpCharMsTrace->pX, lpCharMsTrace->pY, lpCharMsTrace->pZ, 50, TRUE);
										dm_SendRangeDamage(lpCharMsTrace->pX, lpCharMsTrace->pY, lpCharMsTrace->pZ, 0, 0, 0, 0, 0, (SKILL_PLAY_ENCHANT_WEAPON | (lpCurPlayer->EnchantEffect_Point << 8)));
									}
								}
								if (AttackResult && (lpCurPlayer->HvRightHand.ElementEffect || lpCurPlayer->HvLeftHand.ElementEffect))
								{
									if (lpCurPlayer->AttackCritcal >= 0)
									{
										if (lpCurPlayer->HvRightHand.ElementEffect)
											SendElementDamage(lpCharMsTrace, lpCurPlayer->HvRightHand.ElementEffect);
										if (lpCurPlayer->HvLeftHand.ElementEffect)
											SendElementDamage(lpCharMsTrace, lpCurPlayer->HvLeftHand.ElementEffect);
									}
								}
							}
							if (!lpAttackSkill && !AttackResult)
								lpCurPlayer->AttackCritcal = -1;
							else
								DamageExp(lpCharMsTrace, AttackResult);
						}
					}

					if (!AttackResult)
						lpCurPlayer->AttackCritcal = -1;

					if (!AttCancel)
					{
						lpCurPlayer->MoveFlag = FALSE;
						lpCurPlayer->CriticalLog = lpCurPlayer->AttackCritcal;

						if (lpCharMsTrace && (lpCharMsTrace->sCharacterData.iType == CHARACTERTYPE_NPC || lpCharMsTrace->dwTradeMsgCode))
						{
							MouseButton[0] = 0;
							MouseButton[1] = 0;
							AttAutoCont = FALSE;
						}

						if (!AttFlag && !AttAutoCont)
						{
							MsTraceMode = 0;
							lpCharMsTrace = 0;
						}
					}
				}
				else
				{
					if (!lpCharMsTrace->bActive || lpCharMsTrace->psModelAnimation->iType == ANIMATIONTYPE_Die)
					{
						lpCharMsTrace = NULL;
						MsTraceMode = 0;
						lpCurPlayer->MoveFlag = FALSE;
						AttAutoCont = FALSE;
					}
				}
			}
		}

		if (lpMsTraceItem)
		{
			if (lpCurPlayer->PlayAttackFromPosi(lpMsTraceItem->pX, lpMsTraceItem->pY, lpMsTraceItem->pZ, 8000, FALSE) == TRUE)
			{
				smTRANS_ACITON_ITEM		TransActionItem;
				char	szBuff[64];
				int		len;

				TransActionItem.code = smTRANSCODE_PUTITEM;
				TransActionItem.size = sizeof(smTRANS_ACITON_ITEM);

				TransActionItem.x = lpMsTraceItem->pX;
				TransActionItem.y = lpMsTraceItem->pY;
				TransActionItem.z = lpMsTraceItem->pZ;
				TransActionItem.lpStgArea = lpMsTraceItem->lpStgArea;

				if (CheckRecvTrnsItemQue() == TRUE)
				{
					cnt = 0;

					if ((lpMsTraceItem->ItemCode&sinITEM_MASK2) == sinCH1)
					{
						switch (lpMsTraceItem->ItemCode)
						{
						case (sinCH1 | sin01):
						case (sinCH1 | sin02):
							if (lpCurPlayer->sCharacterData.iClass != CHARACTERCLASS_Atalanta && lpCurPlayer->sCharacterData.iClass != CHARACTERCLASS_Archer && lpCurPlayer->sCharacterData.iClass != CHARACTERCLASS_Priestess && lpCurPlayer->sCharacterData.iClass == CHARACTERCLASS_Assassin)
							{
								cMessageBox.ShowMessage(MESSAGE_NOT_PICKUP_FEMALE);
								cnt = 1;
							}
							break;
						case (sinCH1 | sin03):
						case (sinCH1 | sin04):
							if (lpCurPlayer->sCharacterData.iClass == CHARACTERCLASS_Atalanta || lpCurPlayer->sCharacterData.iClass == CHARACTERCLASS_Archer || lpCurPlayer->sCharacterData.iClass == CHARACTERCLASS_Priestess && lpCurPlayer->sCharacterData.iClass == CHARACTERCLASS_Assassin)
							{
								cMessageBox.ShowMessage(MESSAGE_NOT_PICKUP_MALE);
								cnt = 1;
							}
							break;
						}
					}
					if (!cnt)
					{
						if (lpMsTraceItem->ItemCode == (sinGG1 | sin01))
						{
							lstrcpy(szBuff, lpMsTraceItem->szName);
							len = lstrlen(szBuff);

							for (cnt = 0; cnt < len; cnt++)
							{
								if (szBuff[cnt]<'0' || szBuff[cnt]>'9')
								{
									szBuff[cnt] = 0;
									break;
								}
							}

							cnt = atoi(szBuff);

							if (cInvenTory.CheckMoneyLimit(cnt) == TRUE)
							{
								SENDPACKETG(&TransActionItem);
							}
						}
						else
						{
							SENDPACKETG(&TransActionItem);
						}
					}
				}

				MsTraceMode = 0;
				lpMsTraceItem = NULL;
				lpCurPlayer->MoveFlag = FALSE;
				MouseButton[0] = 0;
			}
			else
			{
				if (!lpMsTraceItem->Flag)
				{
					lpMsTraceItem = NULL;
					MsTraceMode = 0;
					lpCurPlayer->MoveFlag = FALSE;
				}
			}
		}
	}

	MsTraceCount++;

	for (cnt = 0; cnt < MAX_UNITS; cnt++)
	{
		if (chrOtherPlayer[cnt].bActive)
		{
			chrOtherPlayer[cnt].Main();
			if (chrOtherPlayer[cnt].dwTarget)
			{
				if (lpCurPlayer->psModelAnimation->iType != ANIMATIONTYPE_Flinch && chrOtherPlayer[cnt].psModelAnimation->iType == ANIMATIONTYPE_Attack)
					lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Flinch);
			}
		}
	}

	MainFieldMap();

	PlayParticle();

	DynLightMain();

	BGM_Main();

	SodScoreMain();

	PlayCounter++;

	GAMEMAP->Update();

	int fldSky, fflag;

	int	RainTime = 0x200;
	int	RainLength = 60 * 7;
	int	BackSel = 0;

	fldSky = -1;
	fflag = 0;

	if ((PlayCounter & 0xFF) == 0 && lpCurPlayer->iID)
	{
		if (dwSoD_ResultTime < dwPlayTime)
		{
			// SODÊ±¼ä
			dwSoD_ResultTime = dwPlayTime + 12000;

			if (cSinHelp.GetSodRankBoxState() == TRUE)
				SendCommand_AreaServer(smTRANSCODE_SOD_RESULT2, 0, 0, 0, 0);
		}

		if (cldata.myPosition)
		{
			if (lpCurPlayer->sCharacterData.iClanID != cldata.intClanMark)
			{
				if (cldata.myPosition == 100 || cldata.myPosition == 101 || cldata.myPosition == 104)
				{
					lpCurPlayer->sCharacterData.iClanID = cldata.intClanMark;
					lpCurPlayer->dwClanManageBit = cldata.CNFlag;
					lpCurPlayer->sCharacterData.bUpdateInfo[0]++;
					SendUpdateClanInfo();
				}
				else
				{
					cldata.intClanMark = 0;
					lpCurPlayer->sCharacterData.iClanID = 0;
					lpCurPlayer->sCharacterData.bUpdateInfo[0]++;
					SendUpdateClanInfo();
				}
			}
		}
		if ((PlayCounter & 0x3FF) == 0 && lpCurPlayer->dwVipBit && lpCurPlayer->dwVipTime > 0)
			SendUpdataVipInfo();

		if (lpCurPlayer->sCharacterData.wPlayerKilling[0] > 0)
		{
			lpCurPlayer->sCharacterData.wPlayerKilling[0]--;

			if (lpCurPlayer->sCharacterData.wPlayerKilling[0] == 0)
			{
				lpCurPlayer->MoveFlag = FALSE;

				Point3D sPosition = GAMEMAP->WarpMap();

				lpCurPlayer->SetPosi(sPosition.iX, 0, sPosition.iZ, 0, 0, 0);
				TraceCameraPosi.x = lpCurPlayer->pX;
				TraceCameraPosi.y = lpCurPlayer->pY;
				TraceCameraPosi.z = lpCurPlayer->pZ;
				TraceTargetPosi.x = lpCurPlayer->pX;
				TraceTargetPosi.y = lpCurPlayer->pY;
				TraceTargetPosi.z = lpCurPlayer->pZ;
				lpCurPlayer->SetMotionFromCode(ANIMATIONTYPE_Revive);
				StartEffect(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, EFFECT_GAME_START1);
				SetDynLight(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, 100, 100, 100, 0, 200);
				CharPlaySound(lpCurPlayer);

				lpCurPlayer->iLoadedMapIndex = -1;
				if (smGameStage[0])
				{
					cnt = smGameStage[0]->GetFloorHeight(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, lpCurPlayer->Pattern->SizeHeight);
					lpCurPlayer->iLoadedMapIndex = 0;
				}
				if (cnt == CLIP_OUT && smGameStage[1])
					lpCurPlayer->iLoadedMapIndex = 1;
			}
		}
		if (WeatherMode == 0)
		{
			DWORD dwHour = GAMEMAP->GetGameHour();

			if (dwHour < GAME_HOUR_DAY || dwHour >= GAME_HOUR_NIGHT)
			{
				BackSel = 2;
			}
			else
			{
				if (dwHour >= GAME_HOUR_DAY && dwHour < GAME_HOUR_GLOW)
					BackSel = 0;
				else
					BackSel = 1;
			}
		}
		if (lpCurPlayer->iLoadedMapIndex >= 0)
		{
			if (STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == MAPID_Bellatra)
			{
				cnt = GetSoD_AreaCode(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ);

				switch (cnt)
				{
				case 0:
				case 1:
				case 2:
				case 3:
					fldSky = MAPSKY_Battle_None;
					break;
				case 4:
					fldSky = MAPSKY_Battle_Sun;
					break;
				case 5:
					fldSky = MAPSKY_Battle_Moon;
					break;
				case 6:
					fldSky = MAPSKY_Battle_Event;
					break;
				}
				if (cnt == 2)
					esPlayEffectBgm(4);
				else
					esPlayEffectBgm(3);

				if (fldSky >= 0) ChangeSky(fldSky);
			}
			// °Í±ðËþµØÍ¼Ð§¹û

			else if (STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == BabelPlayField && dwBabelPlayTime > dwPlayTime)
			{
				ChangeSky(MAPSKY_Iron_BOSS);
				esPlayEffectBgm(11);
			}
			else
			{
				fldSky = STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iaSky[BackSel];

				if (!WeatherMode && fldSky >= 0)
					ChangeSky(fldSky);

				if (WeatherMode == 0)
				{
					switch (STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType)
					{
					case MAPTYPE_Wasteland:
						esPlayEffectBgm(3);
						break;
					case MAPTYPE_Desert:
						esPlayEffectBgm(4);
						break;
					case MAPTYPE_Dungeon:
						if (STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID <= 16 || STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == 32)
						{
							esPlayEffectBgm(5);
							break;
						}
						if (STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID <= 23)
						{
							esPlayEffectBgm(6);
							break;
						}
						if (STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID <= 25)
						{
							esPlayEffectBgm(7);
							break;
						}
						if (STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID <= 26)
						{
							esPlayEffectBgm(8);
							break;
						}
						break;
					case MAPTYPE_Forest:
						if (GAMEMAP->GetGameHour() < GAME_HOUR_DAY || GAMEMAP->GetGameHour() >= GAME_HOUR_DARKNESS)
							esPlayEffectBgm(2);
						else
							esPlayEffectBgm(1);
						break;

					case MAPTYPE_Town:
						esPlayEffectBgm(0);
						break;

					case MAPTYPE_ChessRoom:
						esPlayEffectBgm(-1);
						break;

					case MAPTYPE_Iron:
						esPlayEffectBgm(9);
						break;

					case MAPTYPE_Ice:
						esPlayEffectBgm(12);
						break;
					}
				}
				else
					esPlayEffectBgm(-1);

				if (STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iBackgroundMusicID)
					ChangeBGM(STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iBackgroundMusicID);
			}
		}
	}

	if ((PlayCounter & 0x3) == 0)
	{
		DWORD dwHour = GAMEMAP->GetGameHour();

		if (STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType != MAPTYPE_ChessRoom &&
			(dwHour < GAME_HOUR_DAY || dwHour >= GAME_HOUR_DARKNESS || STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_Dungeon))
			NightDayTime = 1;
		else
			NightDayTime = 0;

		cnt = DarkLight;
		if (DarkLevel < cnt)
			DarkLevel++;
		if (DarkLevel > cnt)
			DarkLevel--;

		if ((PlayCounter & 0x7) == 0)
		{
			if (BackColor_mR < BackColor_R)
				BackColor_R--;
			if (BackColor_mR > BackColor_R)
				BackColor_R++;

			if (BackColor_mG < BackColor_G)
				BackColor_G--;
			if (BackColor_mG > BackColor_G)
				BackColor_G++;

			if (BackColor_mB < BackColor_B)
				BackColor_B--;
			if (BackColor_mB > BackColor_B)
				BackColor_B++;
		}

		if (SETTINGHANDLE->Get().bDebugMode)
		{
			if (DarkLevel_Fix)
				DarkLevel = DarkLevel_Fix;
		}
		if ((PlayCounter & 0xFF) == 0)
		{
			Ptect_GetAttackCount();

			if ((PlayCounter & 0xFFF) == 0)
			{
				if ((PlayCounter & 0x3FFF) == 0)
					SendUsingItemListToServer2();
				else
					SendUsingItemListToServer();
			}

			// ÏÂÓêÐ§¹û
			if (dwWeatherPlayTime)
			{
				if (dwWeatherPlayTime > dwPlayTime)
				{
					if (lpCurPlayer->iLoadedMapIndex >= 0 && STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_Forest)
					{
						switch (WeatherMode)
						{
						case 0:
							ChangeSky(0);
							dwRainTime = dwPlayTime + 10 * 1000;
							WeatherMode = 1;
							break;
						case 1:
							if (dwRainTime)
							{
								if (dwRainTime < dwPlayTime)
								{
									PlayWav(1, 1, 400, 2205);
									WeatherMode = 2;
									dwRainTime = 0;
								}
							}
							break;
						case 2:
							break;
						}
					}
				}
			}
			if (dwWeatherPlayTime)
			{
				if (dwWeatherPlayTime < dwPlayTime)
				{
					if (WeatherMode)
					{
						if (WeatherMode == 2)
							StopWav(1);
						WeatherMode = 0;
					}
				}

				dwWeatherPlayTime = 0;
			}
			else
			{
				if (WeatherMode)
				{
					if (WeatherMode == 2)
						StopWav(1);
					WeatherMode = 0;
				}
			}
			if (rsRecorder.dwNextRecordTime < dwPlayTime)
			{
				if (GetSaveResult() == TRUE)
					SaveGameData();
			}
			if (rsRecorder.dwRecordTime && (rsRecorder.dwRecordTime + 1000 * 8) < dwPlayTime)
			{
				if (SETTINGHANDLE->Get().bDebugMode)
					CHATGAMEHANDLE->AddChatBoxText("SaveGame TimeOut / Retry SaveGame");

				RecordFailCount++;

				rsRecorder.dwRecordTime = 0;
				SaveGameData();
			}

			if (!GAMESOCKET->iDisconnectTime  && RecordFailCount >= 6)
			{
				SendSetHackUser2(2700, RecordFailCount);
				GAMESOCKET->iDisconnectTime = TICKCOUNT;

				if (SETTINGHANDLE->Get().bDebugMode)
					CHATGAMEHANDLE->AddChatBoxText("SaveGame Failed over times");
			}

			DWORD dwHour = GAMEMAP->GetGameHour();

			if (lpCurPlayer->iLoadedMapIndex >= 0 && STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_Forest &&
				(dwHour < GAME_HOUR_DAY || dwHour >= GAME_HOUR_DARKNESS) && (PlayCounter & 0x1FF) == 0)
			{
				if (!WeatherMode)
				{
					if (((dwPlayTime >> 3) & 1) == 0)
						StartEffect(lpCurPlayer->pX, lpCurPlayer->pY, lpCurPlayer->pZ, EFFECT_BANDI1);
				}
			}
		}

		if (lpCurPlayer->iLoadedMapIndex >= 0)
			STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->PlayAmbient();
		else
		{
			if (ResetLastVolumeDist() > 800)
				esPlayObjectSound2(-1, 0, 0, 0, 0);
		}
	}

	dsMenuCursorPos(&pCursorPos, 4);
	MainInterfaceParty();
	dsMenuCursorPos(&pCursorPos, 0);

	GAMEMAP->UpdateWarpGate();

	if (RestartPlayCount > 0) RestartPlayCount--;


	if ((PlayCounter & 0xFFF) == 0)
	{
		CheckCharForm();

		if (SETTINGHANDLE->Get().bDebugMode)
			CHATGAMEHANDLE->AddChatBoxText("1Min.");

		if (!lpCurPlayer->HoSkillCode && !lpCurPlayer->dwDispAppSkill)
		{
			if (!dwRotPlayDelayTime || dwRotPlayDelayTime < dwPlayTime)
			{
				Unit	*lpTempChar;
				Unit	*lpOldChar;

				lpOldChar = lpCurPlayer;

				lpTempChar = SelectRotPlayer(lpCurPlayer);
				if (lpTempChar)
				{
					lpCurPlayer = lpTempChar;
					sinChar = &lpCurPlayer->sCharacterData;

					for (cnt = 0; cnt < MAX_UNITS; cnt++)
					{
						if (chrOtherPlayer[cnt].bActive && chrOtherPlayer[cnt].chrAttackTarget == lpOldChar)
							chrOtherPlayer[cnt].chrAttackTarget = lpCurPlayer;
					}
				}
			}
		}
		else
			dwRotPlayDelayTime = dwPlayTime + 30 * 1000;

		if ((PlayCounter & 0x3FFF) == 0 && SETTINGHANDLE->Get().bDebugMode)
			SendAdminMode2(SETTINGHANDLE->Get().bDebugMode);

		CheckEnergyGraphError();
	}

	TimeEffectMain();

	CheckEnergyGraph();

	if (dwPartyPosionTime && dwPartyPosionTime < dwPlayTime)
		LaunchPartyPostion();

	if ((PlayCounter & 0x1FF) == 0)
	{
		CheckEnergyGraphError();
	}

	return TRUE;
}
extern int RestoreTexFlag;
extern POINT	pCursorPos;

int GetMouseSelAngle()
{
	int x1, x2, z1, z2;

	if (lpCharMsTrace)
	{
		x1 = lpCurPlayer->pX >> FLOATNS;
		z1 = lpCurPlayer->pZ >> FLOATNS;

		x2 = lpCharMsTrace->pX >> FLOATNS;
		z2 = lpCharMsTrace->pZ >> FLOATNS;

		return GetRadian2D(x1, z1, x2, z2);
	}

	if (lpMsTraceItem)
	{
		x1 = lpCurPlayer->pX >> FLOATNS;
		z1 = lpCurPlayer->pZ >> FLOATNS;

		x2 = lpMsTraceItem->pX >> FLOATNS;
		z2 = lpMsTraceItem->pZ >> FLOATNS;

		return GetRadian2D(x1, z1, x2, z2);
	}

	return -1;
}
int GetCharAngle(Unit *lpChar1, Unit *lpChar2)
{
	int x1, x2, z1, z2;

	x1 = lpChar1->pX >> FLOATNS;
	z1 = lpChar1->pZ >> FLOATNS;

	x2 = lpChar2->pX >> FLOATNS;
	z2 = lpChar2->pZ >> FLOATNS;

	return GetRadian2D(x1, z1, x2, z2);
}


int testframe = 0;
int	LastRendSucessCount = 0;
int	DispCharLimitMode = 0;

#define	DISP_CHAR_LIMIT			20
#define	DISP_CHAR_LIMIT_MAX		30
#define	DISP_CHAR_NEAR_DIST		( (10*64)*(10*64) )

int DrawPat3D(int x, int y, int z, int ax, int ay, int az)
{
	int cnt;
	int SelZ;
	int sez;
	RECT	rect;
	RECT	SelRect;
	POINT	SelPos;
	RECT	*lpRect;
	Unit	*lpSelChar;
	scITEM	*lpItem;
	int		dx, dz;
	int		pow;

	POINT	sPos;
	int		RendSucessCount;
	int		DispFlag = FALSE;
	int		r, g, b;
	DWORD	dwDispAppSKill;

	dwDispAppSKill = lpCurPlayer->dwDispAppSkill;
	lpCurPlayer->dwDispAppSkill = 0;

	for (cnt = 0; cnt < SIN_MAX_SKILL_LIST; cnt++)
	{
		if (ContinueSkill[cnt].Flag)
		{
			switch (ContinueSkill[cnt].CODE)
			{
			case SKILL_EXTREME_SHIELD:
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_EXTREME_SHIELD;
				break;
			case SKILL_PHYSICAL_ABSORB:
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_PHYSICAL_ABSORB;
				break;
			case SKILL_AUTOMATION:
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_AUTOMATION;
				break;
			case SKILL_MAXIMIZE:
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_AUTOMATION;
				break;
			case SKILL_CRITICAL_HIT:
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_ANGER;
				break;
			case SKILL_AMPLIFIED:
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_PHYSICAL_ABSORB;
				break;
			case SKILL_HOLY_BODY:
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_PHYSICAL_ABSORB;
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_HOLY_BODY;
				DispApp_SkillPoint = ContinueSkill[cnt].Point;
				break;
			case SKILL_ZENITH:
			case SKILL_T_ANIMA:
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_ANGER;
				break;
			case SKILL_SPARK_SHIELD:
			case SKILL_DIVINE_INHALATION:
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_SPARK_SHIELD;
				break;
			case SKILL_GODLY_SHIELD:
			case SKILL_FROST_JAVELIN:
			case SKILL_SUMMON_MUSPELL:
				lpCurPlayer->dwDispAppSkill |= SKILL_APPMASK_GODLY_SHIELD;
				break;
			}
		}
	}

	if ((lpCurPlayer->dwDispAppSkill&SKILL_APPMASK_PHYSICAL_ABSORB) == 0 && (dwDispAppSKill&SKILL_APPMASK_PHYSICAL_ABSORB) != 0)
		SkillStopSound(SKILL_SOUND_PHYSICAL_ABSORB3);
	if ((lpCurPlayer->dwDispAppSkill&SKILL_APPMASK_AUTOMATION) == 0 && (dwDispAppSKill&SKILL_APPMASK_AUTOMATION) != 0)
		SkillStopSound(SKILL_SOUND_SKILL_AUTOMATION3);
	if ((lpCurPlayer->dwDispAppSkill&SKILL_APPMASK_HOLY_BODY) == 0 && (dwDispAppSKill&SKILL_APPMASK_HOLY_BODY) != 0)
		SkillStopSound(SKILL_SOUND_PHYSICAL_ABSORB3);

	SelZ = 65536 * 16384;

	smRender.SetCameraPosi(x, y, z, x, ay, az);
	if (smGameStage[0])
		SetStageDynLight(smGameStage[0], x, y, z);
	if (smGameStage[1])
		SetStageDynLight(smGameStage[1], x, y, z);

	smCHAR_SetCameraPosi(x, y, z, ax, ay, az);
	if (!DebugPlayer)
	{
		cnt = RestartPlayCount;
		if (lpCurPlayer->PlayInvincible > 0)
			cnt = lpCurPlayer->PlayInvincible;

		if (cnt && (cnt & 0x10) == 0)
		{
			r = smRender.Color_R;
			g = smRender.Color_G;
			b = smRender.Color_B;

			smRender.Color_R += 80;
			smRender.Color_B += 80;

			lpCurPlayer->Draw();

			smRender.Color_R = r;
			smRender.Color_G = g;
			smRender.Color_B = b;
		}
		else
		{
			if (lpCurPlayer->PlayVanish <= 0)
				lpCurPlayer->Draw();
		}

		if (rsBlessCastle.dwMasterClan && lpCurPlayer->sCharacterData.iClanID)
			SetClanMaster_Player(rsBlessCastle.dwMasterClan);

	}
	lpSelChar = 0;
	RendSucessCount = 0;

	for (cnt = 0; cnt < MAX_UNITS; cnt++)
	{
		if (chrOtherPlayer[cnt].bActive && chrOtherPlayer[cnt].DisplayAlpha == 0)
		{
			DispFlag = TRUE;

			if (DispCharLimitMode)
			{
				dx = (lpCurPlayer->pX - chrOtherPlayer[cnt].pX) >> FLOATNS;
				dz = (lpCurPlayer->pZ - chrOtherPlayer[cnt].pZ) >> FLOATNS;
				if ((dx*dx + dz * dz) > DISP_CHAR_NEAR_DIST)
					DispFlag = FALSE;
			}
			if (DispFlag)
			{
				r = smRender.Color_R;
				g = smRender.Color_G;
				b = smRender.Color_B;

				if (lpCurPlayer->HoSkillCode && chrOtherPlayer[cnt].sCharacterData.sHP.sMin)
				{
					switch (lpCurPlayer->HoSkillCode)
					{
					case SKILL_SCOUT_HAWK:
						pow = GetSkillPower(lpCurPlayer, &chrOtherPlayer[cnt], 0, 0, 0);
						if (pow)
						{
							pow = DarkLevel >> 2;
							smRender.Color_R += 40 + pow;
							smRender.Color_G += 40 + pow;
							smRender.Color_B += 100 + pow;
						}
						break;
					}
				}

				DWORD dwOutlineEffectColor = 0;

				if (lpCharSelPlayer && lpCharSelPlayer == &chrOtherPlayer[cnt])
				{
					smRender.Color_R = r + 40;
					smRender.Color_G = g + 60;
					smRender.Color_B = b + 60;

					switch (lpCharSelPlayer->sCharacterData.iType)
					{
					case CHARACTERTYPE_Player:
						dwOutlineEffectColor = D3DCOLOR_RGBA(255, 255, 255, 255);
						break;
					case CHARACTERTYPE_NPC:
						dwOutlineEffectColor = D3DCOLOR_RGBA(0, 255, 100, 255);
						break;
					default:
						dwOutlineEffectColor = D3DCOLOR_RGBA(255, 30, 0, 255);
						break;
					}
				}

				if (!chrOtherPlayer[cnt].RenderLatter && chrOtherPlayer[cnt].AttackIce == 0 && chrOtherPlayer[cnt].RendAlpha == 0 && chrOtherPlayer[cnt].PlayVanish <= 0)
				{
					if (chrOtherPlayer[cnt].PlayInvincible && (chrOtherPlayer[cnt].PlayInvincible & 0x10) == 0)
					{
						smRender.Color_R += 80;
						smRender.Color_B += 80;
					}

					if (dwOutlineEffectColor > 0)
					{
						EFFECTGLOW->Begin(dwOutlineEffectColor, TRUE);
						chrOtherPlayer[cnt].Draw();
						EFFECTGLOW->End(TRUE);
						EFFECTGLOW->Begin(dwOutlineEffectColor, FALSE);
						chrOtherPlayer[cnt].Draw();
						EFFECTGLOW->End(FALSE);
					}

					chrOtherPlayer[cnt].Draw();
				}
				else
				{
					if (dwOutlineEffectColor > 0)
					{
						EFFECTGLOW->Begin(dwOutlineEffectColor, TRUE);
						chrOtherPlayer[cnt].VirtualDraw();
						EFFECTGLOW->End(TRUE);
						EFFECTGLOW->Begin(dwOutlineEffectColor, FALSE);
						chrOtherPlayer[cnt].VirtualDraw();
						EFFECTGLOW->End(FALSE);
					}

					chrOtherPlayer[cnt].VirtualDraw();
				}

				smRender.Color_R = r;
				smRender.Color_G = g;
				smRender.Color_B = b;

				if (chrOtherPlayer[cnt].RendSucess)
				{
					RendSucessCount++;

					sez = chrOtherPlayer[cnt].RendPoint.z;
					lpRect = &chrOtherPlayer[cnt].RendRect2D;

					if (chrOtherPlayer[cnt].sCharacterData.sHP.sMin > 0 && sez > (96 * fONE) && sez < SelZ && lpRect->left<pCursorPos.x && lpRect->right>pCursorPos.x && lpRect->top<pCursorPos.y && lpRect->bottom>pCursorPos.y)
					{
						SelZ = sez;
						lpSelChar = &chrOtherPlayer[cnt];
					}
				}
			}
			else
			{
				chrOtherPlayer[cnt].RendSucess = FALSE;
				RendSucessCount++;
			}
		}
	}

	LastRendSucessCount = RendSucessCount;

	if (DispCharLimitMode)
	{
		if (RendSucessCount < DISP_CHAR_LIMIT)
			DispCharLimitMode = FALSE;
	}
	else
	{
		if (RendSucessCount > DISP_CHAR_LIMIT_MAX)
			DispCharLimitMode = TRUE;
	}

	if (VRKeyBuff['A'])
	{
		lpSelChar = 0;
		SelZ = 65536 * 16384;
	}

	lpItem = 0;

	for (cnt = 0; cnt < DISP_ITEM_MAX; cnt++)
	{
		if (scItems[cnt].Flag)
		{
			if (scItems[cnt].ItemCode != 0 || DisplayDebug)
			{
				r = smRender.Color_R;
				g = smRender.Color_G;
				b = smRender.Color_B;

				if (lpSelItem && lpSelItem == &scItems[cnt])
				{
					smRender.Color_R = r + 40;
					smRender.Color_G = g + 60;
					smRender.Color_B = b + 60;

					DWORD dwColor = D3DCOLOR_RGBA(255, 255, 0, 255);

					EFFECTGLOW->Begin(dwColor, TRUE);
					scItems[cnt].Draw();
					EFFECTGLOW->End(TRUE);
					EFFECTGLOW->Begin(dwColor, FALSE);
					scItems[cnt].Draw();
					EFFECTGLOW->End(FALSE);
				}
				scItems[cnt].Draw();

				smRender.Color_R = r;
				smRender.Color_G = g;
				smRender.Color_B = b;

				smRender.SetCameraPosi(x, y, z, ax, ay, az);

				sez = smRender.GetRect2D(scItems[cnt].pX, scItems[cnt].pY + (16 * fONE), scItems[cnt].pZ, 32 * fONE, 32 * fONE, &rect, &sPos);

				scItems[cnt].RendPoint.x = sPos.x;
				scItems[cnt].RendPoint.y = sPos.y;
				scItems[cnt].RendPoint.z = sez;

				if (sez > 0 && sez < SelZ && rect.left<pCursorPos.x && rect.right>pCursorPos.x && rect.top<pCursorPos.y && rect.bottom>pCursorPos.y)
				{
					SelZ = sez;
					lpItem = &scItems[cnt];
					memcpy(&SelRect, &rect, sizeof(RECT));
					memcpy(&SelPos, &sPos, sizeof(POINT));
				}
			}
		}
	}

	if (lpSelChar)
	{
		lpCharSelPlayer = lpSelChar;
		lpItem = 0;
	}
	else
		lpCharSelPlayer = 0;

	if (lpItem)
	{
		lpSelItem = lpItem;
		memcpy(&MsSelRect, &SelRect, sizeof(RECT));
		memcpy(&MsSelPos, &SelPos, sizeof(POINT));
	}
	else
		lpSelItem = 0;

	if (cShop.OpenFlag || cCharShop.OpenFlag)
	{
		lpCharSelPlayer = 0;
		lpSelItem = 0;

		auto Icon = CURSORHANDLE->GetMouseCurosr();

		if (Icon == ECURSORICON_Attack ||
			Icon == ECURSORICON_Talk ||
			Icon == ECURSORICON_GetItem2 ||
			Icon == ECURSORICON_GetItem1)
			CURSORHANDLE->SetMouseCursor(ECURSORICON_Default);
		return TRUE;
	}

	ECursorIcon eIcon = ECURSORICON_None;

	if (!MouseItem.bValid)
	{
		eIcon = ECURSORICON_Default;

		if (lpCharSelPlayer)
		{
			switch (lpCharSelPlayer->sCharacterData.iType)
			{
			case CHARACTERTYPE_Monster:
				eIcon = ECURSORICON_Attack;
				break;
			case CHARACTERTYPE_Player:
				break;
			case CHARACTERTYPE_NPC:
				eIcon = ECURSORICON_Talk;
				break;
			}
		}

		if (lpSelItem)
		{
			eIcon = MouseButton[0] ? ECURSORICON_GetItem2 : ECURSORICON_GetItem1;
		}
	}

	CURSORHANDLE->SetMouseCursor(eIcon);

	return TRUE;
}

int DrawPat3D_Alpha()
{
	int cnt;
	int DispFlag;
	int dx, dz;
	int ap;
	int	RendFalg;
	int BackFrame;
	int cnt2;

	//°µÒþÖ®ÊõÐ§¹û
	if (lpCurPlayer->PlayVanish > 0)
	{
		ap = lpCurPlayer->DisplayAlpha;
		lpCurPlayer->DisplayAlpha = -160;

		if (lpCurPlayer->PlayVague)
		{
			SetItem2PassTexture(8, smTEXSTATE_FS_SCROLL5);
			lpCurPlayer->DisplayAlpha = -60;
		}
		lpCurPlayer->Draw();

		SetItem2PassTexture(-1);
		lpCurPlayer->DisplayAlpha = ap;
	}
	if (lpCurPlayer->sCharacterData.iClass == CHARACTERCLASS_Pikeman && (lpCurPlayer->AttackSkil & 0xFF) == SKILL_PLAY_SHADOW_MASTER && lpCurPlayer->psModelAnimation->iType == ANIMATIONTYPE_Skill)
	{
		ap = lpCurPlayer->DisplayAlpha;
		BackFrame = lpCurPlayer->iFrame;
		lpCurPlayer->DisplayAlpha = -140;
		for (cnt2 = 0; cnt2 < 6; cnt2++)
		{
			lpCurPlayer->iFrame -= 160 * 2;

			if (lpCurPlayer->iFrame > (lpCurPlayer->psModelAnimation->StartFrame * 160))
				lpCurPlayer->Draw();

			lpCurPlayer->DisplayAlpha -= 20;
		}
		lpCurPlayer->iFrame = BackFrame;
		lpCurPlayer->DisplayAlpha = ap;
	}

	for (cnt = 0; cnt < MAX_UNITS; cnt++)
	{
		if (chrOtherPlayer[cnt].bActive)
		{
			RendFalg = 0;

			if (chrOtherPlayer[cnt].DisplayAlpha != 0 || chrOtherPlayer[cnt].RendAlpha != 0 || chrOtherPlayer[cnt].AttackIce != 0 || chrOtherPlayer[cnt].RenderLatter || chrOtherPlayer[cnt].PlayVanish)
			{
				DispFlag = TRUE;

				if (DispCharLimitMode && chrOtherPlayer[cnt].AttackIce == 0)
				{

					dx = (lpCurPlayer->pX - chrOtherPlayer[cnt].pX) >> FLOATNS;
					dz = (lpCurPlayer->pZ - chrOtherPlayer[cnt].pZ) >> FLOATNS;

					if ((dx*dx + dz * dz) > DISP_CHAR_NEAR_DIST)
						DispFlag = FALSE;
				}

				if (chrOtherPlayer[cnt].PlayVanish > 0 && lpCurPlayer->iLoadedMapIndex >= 0 && STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == MAPID_BlessCastle)
				{
					if (lpCharSelPlayer != &chrOtherPlayer[cnt])
					{
						dx = (lpCurPlayer->pX - chrOtherPlayer[cnt].pX) >> FLOATNS;
						dz = (lpCurPlayer->pZ - chrOtherPlayer[cnt].pZ) >> FLOATNS;
						if ((dx*dx + dz * dz) > DIST_TRANSLEVEL_NEAR)
							DispFlag = FALSE;
					}
				}

				if (DispFlag)
				{
					ap = chrOtherPlayer[cnt].DisplayAlpha;

					if (chrOtherPlayer[cnt].PlayVanish > 0)
					{
						chrOtherPlayer[cnt].DisplayAlpha = -160;
						if (chrOtherPlayer[cnt].PlayVague)
							SetItem2PassTexture(8, smTEXSTATE_FS_SCROLL5);
					}

					if (chrOtherPlayer[cnt].RendAlpha && ap > chrOtherPlayer[cnt].RendAlpha)
					{
						chrOtherPlayer[cnt].DisplayAlpha = chrOtherPlayer[cnt].RendAlpha;

						if (chrOtherPlayer[cnt].psModelAnimation->iType >= 0x100 && (chrOtherPlayer[cnt].sCharacterData.iMonsterEffectID == snCHAR_SOUND_ILLUSIONKNIGHT || chrOtherPlayer[cnt].PlayVanish > 0))
							chrOtherPlayer[cnt].DisplayAlpha = ap;

						chrOtherPlayer[cnt].Draw();
						chrOtherPlayer[cnt].DisplayAlpha = ap;
					}
					else
						chrOtherPlayer[cnt].Draw();

					RendFalg++;

					SetItem2PassTexture(-1);
					chrOtherPlayer[cnt].DisplayAlpha = ap;
				}
			}

			if (RendFalg == 0)
			{
				if (chrOtherPlayer[cnt].sCharacterData.iClass == CHARACTERCLASS_Pikeman && (chrOtherPlayer[cnt].AttackSkil & 0xFF) == SKILL_PLAY_SHADOW_MASTER && chrOtherPlayer[cnt].psModelAnimation->iType == ANIMATIONTYPE_Skill)
				{
					ap = chrOtherPlayer[cnt].DisplayAlpha;
					BackFrame = chrOtherPlayer[cnt].iFrame;
					chrOtherPlayer[cnt].DisplayAlpha = -160;
					for (cnt2 = 0; cnt2 < 4; cnt2++)
					{
						chrOtherPlayer[cnt].iFrame -= 160 * 4;
						if (chrOtherPlayer[cnt].iFrame > (chrOtherPlayer[cnt].psModelAnimation->StartFrame * 160))
							chrOtherPlayer[cnt].Draw();
					}
					chrOtherPlayer[cnt].iFrame = BackFrame;
					chrOtherPlayer[cnt].DisplayAlpha = ap;
				}
			}
		}
	}

	return TRUE;
}
int DrawPatShadow(int x, int y, int z, int ax, int ay, int az)
{
	int cnt;

	smCHAR_SetCameraPosi(x, y, z, ax, ay, az);

	cnt = 0;

	lpCurPlayer->DrawShadow();

	if (lpCurPlayer->iLoadedMapIndex >= 0)
	{
		if (STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_Ice)
			lpCurPlayer->DrawIceFoot();
	}

	for (cnt = 0; cnt < MAX_UNITS; cnt++)
	{
		if (chrOtherPlayer[cnt].bActive && chrOtherPlayer[cnt].DisplayAlpha == 0 && chrOtherPlayer[cnt].RendAlpha == 0) {
			chrOtherPlayer[cnt].DrawShadow();
		}
	}

	return TRUE;
}

extern BYTE VRKeyBuff[256];

int Draw2DCounter = 0;

int DrawPat2D(int x, int y, int z, int ax, int ay, int az)
{
	int cnt;

	if (lpCurPlayer->Pattern == 0)
		return FALSE;

	smCHAR_SetCameraPosi(x, y, z, ax, ay, az);
	smRender.SetMaterialGroup(smMaterialGroup);

	for (cnt = 0; cnt < MAX_UNITS; cnt++)
	{
		if (chrOtherPlayer[cnt].bActive)
			chrOtherPlayer[cnt].DrawMotionBlur();
	}

	lpCurPlayer->DrawMotionBlur();

	DrawParticle(x, y, z, ax, ay, az);

	Draw2DCounter++;

	DrawLightImage();

	DrawWeather(ax);

	return TRUE;
}

extern int ViewPointLen;

extern DWORD smBackColor;



int InitBackGround()
{
	ChangeSky(0);

	return TRUE;
}

int CloseBackGround()
{
	return TRUE;
}


int BgFrame = 0;

RECT	PartyTradeButtonRect[4] =
{
	{	00,0, 20, 20	},
	{	25,0, 20, 20	},
	{	50,0, 20, 20	},
	{	75,0, 20, 20	}
};

RECT	PartyTradeToolTipRect = { 1,18,70,28 };

POINT	PartyButtonPoint = { -1, -1 };

int GetPartyTradeButtonPos(int x, int y)
{
	int cnt, sx;
	int AdjustX;
	int MaxCnt;

	int wx, wy;
	if (PartyButtonPoint.x < 0)
		return -1;

	wx = PartyButtonPoint.x;
	wy = PartyButtonPoint.y;

	if (EachTradeButtonMode)
	{
		AdjustX = -10;
		MaxCnt = 4;
	}
	else
	{
		AdjustX = 0;
		MaxCnt = 3;
	}

	for (cnt = 0; cnt < MaxCnt; cnt++)
	{
		sx = PartyTradeButtonRect[cnt].left + AdjustX + wx;
		if (sx<x && (sx + PartyTradeButtonRect[cnt].right)>x && PartyTradeButtonRect[cnt].top + wy<y && (PartyTradeButtonRect[cnt].top + wy + PartyTradeButtonRect[cnt].bottom)>y)
			return cnt;
	}

	return -1;
}
int DisplayPartyTradeButton()
{
	int SelNum;
	int cnt;
	int AdjustX;
	int MaxCnt;

	int wx, wy;
	if (PartyButtonPoint.x < 0)
		return -1;
	wx = PartyButtonPoint.x;
	wy = PartyButtonPoint.y;

	if (EachTradeButtonMode)
	{
		AdjustX = -10;
		MaxCnt = 4;
	}
	else
	{
		AdjustX = 0;
		MaxCnt = 3;
	}

	SelNum = GetPartyTradeButtonPos(pCursorPos.x, pCursorPos.y);

	for (cnt = 0; cnt < MaxCnt; cnt++)
	{
		if (SelNum == cnt)
		{
			if (lpDDS_ParTradeButton[cnt][1])
			{
				DrawSprite(PartyTradeButtonRect[cnt].left + AdjustX + wx, PartyTradeButtonRect[cnt].top + wy,
					lpDDS_ParTradeButton[cnt][1], 0, 0, PartyTradeButtonRect[cnt].right, PartyTradeButtonRect[cnt].bottom);
			}
		}
		else
		{
			if (lpDDS_ParTradeButton[cnt][0])
			{
				DrawSprite(PartyTradeButtonRect[cnt].left + AdjustX + wx, PartyTradeButtonRect[cnt].top + wy,
					lpDDS_ParTradeButton[cnt][0], 0, 0, PartyTradeButtonRect[cnt].right, PartyTradeButtonRect[cnt].bottom);
			}
		}
	}

	if (SelNum >= 0)
	{
		if (lpDDS_ParTradeToolTip[SelNum])
		{
			DrawSprite(PartyTradeButtonRect[SelNum].left - 60 + AdjustX + wx, PartyTradeToolTipRect.top + wy,
				lpDDS_ParTradeToolTip[SelNum], 0, 0, PartyTradeToolTipRect.right, PartyTradeToolTipRect.bottom);
		}
	}

	return TRUE;
}


Unit	chrEachPlayer;
Unit *chrEachMaster = 0;
int		EachTradeButton = 0;
int		EachTradeButtonMode = 0;
RECT	RectTradeButton;

POINT3D EachCameraPos;
int	DispEachMode = 0;


int FindBipPoint(smPAT3D *lpPat, char *szObjNodeName, int frame, int *nX, int *nY, int *nZ);

int OpenEachPlayer(Unit *lpChar)
{
	if (!lpChar || !lpChar->bActive || !lpChar->DisplayFlag)
		return FALSE;
	if (EachTradeButton)
		return FALSE;

	memcpy(&chrEachPlayer, lpChar, sizeof(Unit));
	chrEachPlayer.SetMotionFromCode(ANIMATIONTYPE_Idle);
	chrEachPlayer.ActionPattern = 101;
	chrEachMaster = lpChar;

	chrEachPlayer.bActive = TRUE;

	if (FindBipPoint(chrEachPlayer.AnimPattern, "Bip01 Head", chrEachPlayer.iFrame, &EachCameraPos.x, &EachCameraPos.y, &EachCameraPos.z) == NULL)
	{

		EachCameraPos.y = chrEachPlayer.PatHeight - 10 * fONE;
		EachCameraPos.x = 0;
		EachCameraPos.z = 0;
	}

	if (lpChar->sCharacterData.iType == CHARACTERTYPE_Monster || lpChar->sCharacterData.iType == CHARACTERTYPE_NPC)
	{
		EachCameraPos.y += lpChar->sCharacterData.sViewBoxZoom.sMin * fONE;
		EachCameraPos.z += lpChar->sCharacterData.sViewBoxZoom.sMax * fONE;
	}

	return TRUE;
}

int CloseEachPlayer()
{
	chrEachPlayer.bActive = FALSE;
	chrEachMaster = 0;
	EachTradeButton = 0;

	return TRUE;
}
int DrawClanMark_EachBox(smTEXTUREHANDLE *clanMark, int x, int y)
{
	UI::ImageRender::Render(clanMark->m_pTexture, x + 4, y + 4, 16, 16, 0, 0, -1);

	return TRUE;
}
int EachPlayerMain()
{
	if (!chrEachMaster || !chrEachMaster->bActive || chrEachMaster->iID != chrEachPlayer.iID || chrEachMaster->Pattern != chrEachPlayer.Pattern)
	{
		CloseEachPlayer();
		return TRUE;
	}

	if (chrEachPlayer.bActive)
	{
		if (DispEachMode)
		{
			if (chrEachPlayer.TalkSoundSum && chrEachPlayer.TalkSoundSum != g_PlayTalkSoundSum)
			{
				PlayTalkSound();
				chrEachPlayer.AutoChangeTalkMotion(TALK_MOTION_FILE);
			}
			else if (chrEachPlayer.TalkPattern && chrEachPlayer.TalkFrame == 0)
			{
				if (IsPlayTalkSound())
					chrEachPlayer.AutoChangeTalkMotion(TALK_MOTION_FILE);
				else
					chrEachPlayer.AutoChangeTalkMotion(FACIAL_MOTION_FILE);
			}
		}
		else
		{
			if (IsPlayTalkSound())
				StopTalkSound();

			chrEachPlayer.TalkSoundSum = 0;
			g_PlayTalkSoundSum = 0;
		}

		chrEachPlayer.Main();

		if (chrEachMaster && chrEachMaster->sCharacterData.iType == CHARACTERTYPE_NPC)
		{
			if (chrEachMaster->psModelAnimation->iType == ANIMATIONTYPE_Attack && chrEachPlayer.psModelAnimation->iType == ANIMATIONTYPE_Idle)
				chrEachPlayer.SetMotionFromCode(ANIMATIONTYPE_Attack);
		}

		if (chrEachMaster->psModelAnimation->iType == ANIMATIONTYPE_Die && chrEachMaster->iFrameTimer > 0x50)
			CloseEachPlayer();
	}

	return TRUE;
}
int DrawEachPlayer(float fx, float fy, int SizeMode)
{
	int x, y, z, w, h;
	int mx, my, he;
	POINT3D angle;
	int dist, len;
	DWORD	dwColor;
	int		ObjSizeBack;
	int		ModeFlag;
	int		ClanX, ClanY, ClanLen;
	char szBuff[256];
	int sx, sy;
	int StateBar;
	int sDist;

	if (chrEachPlayer.bActive && chrEachMaster && chrEachMaster->bActive)
	{
		chrEachPlayer.pX = 0;
		chrEachPlayer.pY = 0;
		chrEachPlayer.pZ = 0;

		chrEachPlayer.Angle.x = 0;
		chrEachPlayer.Angle.y = 0;
		chrEachPlayer.Angle.z = 0;

		mx = MidX;
		my = MidY;

		MidX = (int)((float)RESOLUTION_WIDTH * fx);
		MidY = (int)((float)RESOLUTION_HEIGHT * fy);

		int chrHeight;

		if (chrEachPlayer.sCharacterData.iType != CHARACTERTYPE_Player)
			chrHeight = chrEachPlayer.PatHeight - 8 * fONE;
		else
			chrHeight = chrEachPlayer.PatHeight;

		//µãNPCµÈµÄ½ÇÉ«¿ò
		if (SizeMode)
		{
			h = (int)((float)RESOLUTION_WIDTH / 2);
			w = (int)((float)RESOLUTION_HEIGHT * 1.34f / 4);

			w += 20;
			h += 20;

			smRender.SMSHIFT_PERSPECTIVE_WIDTH = RENDCLIP_DEFAULT_SHIFT_PERSPECTIVE_WIDTH * 3 / RENDCLIP_DEFAULT_SHIFT_PERSPECTIVE_WIDTH;
			smRender.SMMULT_PERSPECTIVE_HEIGHT = RENDCLIP_DEFAULT_MULT_PERSPECTIVE_HEIGHT * 2;

			dist = 30 * fONE;
			he = -1 * fONE;
		}
		else
		{
			h = (int)((float)RESOLUTION_WIDTH / 6);
			w = (int)((float)RESOLUTION_HEIGHT * 1.34f / 8);

			w += 10;
			h += 10;

			smRender.SMSHIFT_PERSPECTIVE_WIDTH = RENDCLIP_DEFAULT_SHIFT_PERSPECTIVE_WIDTH * 4 / RENDCLIP_DEFAULT_SHIFT_PERSPECTIVE_WIDTH;
			smRender.SMMULT_PERSPECTIVE_HEIGHT = RENDCLIP_DEFAULT_MULT_PERSPECTIVE_HEIGHT * 6;

			dist = 100 * fONE;
			he = 3 * fONE;

		}

		dist += EachCameraPos.y;

		if (MatEachBox >= 0)
		{
			dsDrawTexImage(MatEachBox, MidX - (w >> 1), MidY - (h >> 1), w, h, 255, 0);

			if (!SizeMode)
			{
				if (EachTradeButton)
				{
					PartyButtonPoint.y = MidY + (h >> 1);

					if (EachTradeButtonMode)
					{
						dsDrawTexImage(MatEachMenuBox, MidX - 60, MidY + (h >> 1) - 6, 120, 50, 255, 0);
						PartyButtonPoint.x = MidX - 46;
					}
					else
					{
						dsDrawTexImage(MatEachMenuBox, MidX - 50, MidY + (h >> 1) - 6, 100, 50, 255, 0);
						PartyButtonPoint.x = MidX - 36;
					}
				}
			}
		}

		GRAPHICENGINE->GetDevice()->Clear(0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

		smCHAR_SetCameraPosi(EachCameraPos.x, EachCameraPos.y + he, dist + EachCameraPos.z, 0, ANGLE_180, 0);

		if (chrEachMaster->psModelAnimation->iType >= 0x100)
			ModeFlag = TRUE;
		else
			ModeFlag = FALSE;

		if (ModeFlag && chrEachMaster->sCharacterData.iType == CHARACTERTYPE_NPC && chrEachPlayer.psModelAnimation->iType == ANIMATIONTYPE_Attack)
			ModeFlag = FALSE;

		sx = ((int)RESOLUTION_WIDTH >> 1) - (STATE_BAR_WIDTH_NEW >> 1);
		sy = 5;

		sDist = STATE_BAR_HEIGHT_NEW >> 1;
		StateBar = 0;

		if (ModeFlag)
		{
			x = chrEachMaster->pX;
			y = chrEachMaster->pY;
			z = chrEachMaster->pZ;
			memcpy(&angle, &chrEachMaster->Angle, sizeof(POINT3D));

			chrEachMaster->pX = 0;
			chrEachMaster->pY = 0;
			chrEachMaster->pZ = 0;
			ZeroMemory(&chrEachMaster->Angle, sizeof(POINT3D));

			ObjSizeBack = chrEachMaster->sCharacterData.sSize;
			chrEachMaster->sCharacterData.sSize = 0;

			chrEachMaster->Draw();

			chrEachMaster->sCharacterData.sSize = ObjSizeBack;

			if (SizeMode && chrEachMaster->sCharacterData.iType == CHARACTERTYPE_None && !EachTradeButton)
				StateBar = chrEachMaster->DrawStateBar(sx, sy);

			chrEachMaster->pX = x;
			chrEachMaster->pY = y;
			chrEachMaster->pZ = z;

			memcpy(&chrEachMaster->Angle, &angle, sizeof(POINT3D));
		}
		else
		{
			chrEachPlayer.AttackAnger = chrEachMaster->AttackAnger;

			ObjSizeBack = chrEachPlayer.sCharacterData.sSize;
			chrEachPlayer.sCharacterData.sSize = 0;

			chrEachPlayer.Draw();

			chrEachPlayer.sCharacterData.sSize = ObjSizeBack;

			if (SizeMode && chrEachMaster->sCharacterData.iType == CHARACTERTYPE_None)
				StateBar = chrEachMaster->DrawStateBar(sx, sy);
		}

		if (SizeMode)
		{
			if (chrEachPlayer.szMessage[0])
			{
				dist = lstrlen(chrEachPlayer.szMessage);
				if (dist > 34)
					dist = 34;
				dist >>= 1;
				dist *= 8;
				dist -= 8;

				DrawMessage(MidX - dist, MidY - (h >> 1) + h + 8, chrEachPlayer.szMessage, 36, BOX_ONE);
			}
			else
			{
				if (chrEachMaster->szMessage[0])
					lstrcpy(chrEachPlayer.szMessage, chrEachMaster->szMessage);
			}

			len = lstrlen(chrEachPlayer.sCharacterData.szName);

			dist = GetTextWidth(0,chrEachPlayer.sCharacterData.szName) >> 1;

			dsTextLineOut(0, MidX - dist + 1, MidY - (h >> 1) + h - 33, chrEachPlayer.sCharacterData.szName, len, D3DCOLOR_XRGB(0, 0, 0));
			dsTextLineOut(0, MidX - dist, MidY - (h >> 1) + h - 32, chrEachPlayer.sCharacterData.szName, len, D3DCOLOR_XRGB(255, 255, 180));
		}
		else
		{
			if (!EachTradeButton)
			{
				if (lpCurPlayer->iLoadedMapIndex >= 0 && STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_BlessCastle)
				{
					if (chrEachMaster->sCharacterData.iType == CHARACTERTYPE_Player || chrEachMaster->iCharacterType == CHARACTERTYPE_Player)
						//ÏÔÊ¾×£¸£BP
						chaSiege.ShowPickUserKillPoint(MidX - 32, MidY + (h >> 1) + 10, chrEachMaster->sBlessCastle_Damage[1]);
				}
			}

			if (chrEachPlayer.sCharacterData.iClanID && chrEachPlayer.iClanInfoIndex >= 0)
			{
				ClanLen = lstrlen(ClanInfo[chrEachPlayer.iClanInfoIndex].ClanInfoHeader.ClanName);

				ClanX = MidX - 26;
				ClanY = MidY - (h >> 1) + 8;

				// ¹«»áÍ¼±ê
				//DrawSprite(ClanX - 18,ClanX,ClanInfo[chrEachPlayer.ClanInfoNum].hClanMark,0,0,16,16,777);
				DrawClanMark_EachBox(ClanInfo[chrEachPlayer.iClanInfoIndex].hClanMark, ClanX - 18, ClanY);

				if (ClanLen < 12)
					ClanX += (12 - ClanLen) << 1;
				ClanY += 2;

				if (pCursorPos.x > (MidX - (w >> 1)) && pCursorPos.y < (MidY + (h >> 1)) && ClanInfo[chrEachPlayer.iClanInfoIndex].ClanInfoHeader.ClanReport[0])
					DrawClanMessage((MidX - (w >> 1)), 14, ClanInfo[chrEachPlayer.iClanInfoIndex].ClanInfoHeader.ClanReport, 42, D3DCOLOR_XRGB(255, 255, 255));
			}
			else
				ClanLen = 0;

			if (chrEachPlayer.sCharacterData.iType == CHARACTERTYPE_Monster &&
				!chrEachPlayer.sCharacterData.iClanID)
			{
				len = 0;
				switch (chrEachPlayer.sCharacterData.iMonsterType)
				{
				case MONSTERTYPE_Mutant:
					len = 1;
					break;
				case MONSTERTYPE_Undead:
					len = 2;
					break;
				case MONSTERTYPE_Demon:
					len = 3;
					break;
				case MONSTERTYPE_Mechanic:
					len = 4;
					break;
				case MONSTERTYPE_Friendly:
					len = -1;
					break;
				}
				if (len >= 0)
					dsDrawTexImage(MatMonBroodImage[len], MidX + (w / 2) - 24, MidY - (h / 2) + 8, 16, 16, 255, 0);
			}

			len = lstrlen(chrEachPlayer.sCharacterData.szName);

			dist = len * 3;

			dsTextLineOut(0, MidX - dist + 1, MidY - (h >> 1) + h - 17, chrEachPlayer.sCharacterData.szName, len, D3DCOLOR_XRGB(0, 0, 0));


			dwColor = D3DCOLOR_XRGB(255, 255, 255);

			switch (chrEachPlayer.sCharacterData.iType)
			{
			case CHARACTERTYPE_Monster:
				dwColor = D3DCOLOR_XRGB(255, 160, 120);// ¹ÖÎï
				break;
			case CHARACTERTYPE_NPC:
				dwColor = D3DCOLOR_XRGB(255, 255, 180);// NPC
				break;
			}

			dsTextLineOut(0, MidX - dist, MidY - (h >> 1) + h - 16, chrEachPlayer.sCharacterData.szName, len, dwColor);

			if (ClanLen)
			{
				dsTextLineOut(0, ClanX + 1, ClanY + 1, ClanInfo[chrEachPlayer.iClanInfoIndex].ClanInfoHeader.ClanName, ClanLen, D3DCOLOR_XRGB(0, 0, 0));
				dsTextLineOut(0, ClanX, ClanY, ClanInfo[chrEachPlayer.iClanInfoIndex].ClanInfoHeader.ClanName, ClanLen, D3DCOLOR_XRGB(150, 255, 200));
			}
			// ½ÇÉ«µÄHP°Ù·Ö±È
			if (StateBar == TRUE)
			{
				wsprintf(szBuff, "%d / %d", chrEachMaster->sCharacterData.sHP.sMin, chrEachMaster->sCharacterData.sHP.sMax);
				sx = ((int)RESOLUTION_WIDTH >> 1) - (lstrlen(szBuff) >> 1);

				dsTextLineOut(0, sx + 1, sDist + 5 + 1, szBuff, lstrlen(szBuff), D3DCOLOR_XRGB(0, 0, 0));
				dsTextLineOut(0, sx, sDist + 5, szBuff, lstrlen(szBuff), D3DCOLOR_XRGB(255, 255, 255));
			}
			if (SETTINGHANDLE->Get().bDebugMode && cInterFace.sInterFlags.MapOnFlag)
			{
				dwColor = D3DCOLOR_XRGB(255, 255, 255);
				char szBuff[256];
				int ly;

				ly = MidY + 80;
				wsprintf(szBuff, "Level   : %d", chrEachPlayer.sCharacterData.iLevel);
				dsTextLineOut(0, MidX - 50, ly, szBuff, lstrlen(szBuff), dwColor);
				ly += 16;
				wsprintf(szBuff, "Attack  : %d %d", chrEachPlayer.sCharacterData.iMinDamage, chrEachPlayer.sCharacterData.iMaxDamage);
				dsTextLineOut(0, MidX - 50, ly, szBuff, lstrlen(szBuff), dwColor);
				ly += 16;
				wsprintf(szBuff, "Defence : %d ", chrEachPlayer.sCharacterData.iDefenseRating);
				dsTextLineOut(0, MidX - 50, ly, szBuff, lstrlen(szBuff), dwColor);
				ly += 16;
				wsprintf(szBuff, "Absorpt : %d ", chrEachPlayer.sCharacterData.iAbsorbRating);
				dsTextLineOut(0, MidX - 50, ly, szBuff, lstrlen(szBuff), dwColor);
				ly += 16;
				wsprintf(szBuff, "Money   : %d ", chrEachPlayer.sCharacterData.iGold);
				dsTextLineOut(0, MidX - 50, ly, szBuff, lstrlen(szBuff), dwColor);
				ly += 16;
				wsprintf(szBuff, "EXP     : %d ", chrEachPlayer.sCharacterData.iExp);
				dsTextLineOut(0, MidX - 50, ly, szBuff, lstrlen(szBuff), dwColor);
				ly += 16;
				wsprintf(szBuff, "Rating  : %d ", sinGetAccuracy(chrEachPlayer.sCharacterData.iLevel, chrEachPlayer.sCharacterData.iDefenseRating));
				dsTextLineOut(0, MidX - 50, ly, szBuff, lstrlen(szBuff), dwColor);
				ly += 16;
				wsprintf(szBuff, "Critical: %d ", sinGetCritical(chrEachPlayer.sCharacterData.iLevel));
				dsTextLineOut(0, MidX - 50, ly, szBuff, lstrlen(szBuff), dwColor);
				ly += 16;
				wsprintf(szBuff, "Update  : %d", chrEachPlayer.sCharacterData.bUpdateInfo[0]);
				dsTextLineOut(0, MidX - 50, ly, szBuff, lstrlen(szBuff), dwColor);
				ly += 16;
				wsprintf(szBuff, "Clan : %d(%d)", chrEachPlayer.sCharacterData.iClanID, chrEachMaster->iClanInfoIndex);
				dsTextLineOut(0, MidX - 50, ly, szBuff, lstrlen(szBuff), dwColor);
				ly += 16;

				if (DisplayDebug)
				{
					wsprintf(szBuff, "Frame   :%d", chrEachMaster->iFrame);
					dsTextLineOut(0, MidX - 100, ly, szBuff, lstrlen(szBuff), dwColor);
					ly += 16;
					wsprintf(szBuff, "RcvMoton:%d,%d", (chrEachMaster->iPlayBuffCount & PLAYBUFF_MASK), (chrEachMaster->PlayBuffPosi_End&PLAYBUFF_MASK));
					dsTextLineOut(0, MidX - 100, ly, szBuff, lstrlen(szBuff), dwColor);
					ly += 16;
					wsprintf(szBuff, "User Code :%d", chrEachMaster->iID);
					dsTextLineOut(0, MidX - 100, ly, szBuff, lstrlen(szBuff), dwColor);
					ly += 16;
				}
			}
		}

		MidX = mx;
		MidY = my;

		smRender.SMSHIFT_PERSPECTIVE_WIDTH = RENDCLIP_DEFAULT_SHIFT_PERSPECTIVE_WIDTH;
		smRender.SMMULT_PERSPECTIVE_HEIGHT = RENDCLIP_DEFAULT_MULT_PERSPECTIVE_HEIGHT;
	}

	if (chrEachMaster && chrEachMaster->ActionPattern == 99)
	{
		if ((chrEachMaster->dwLastTransTime + DISPLAY_TRANS_TIME_OVER) < dwPlayTime)
		{
			CloseEachPlayer();
			return TRUE;
		}
	}

	if (lpCharMsTrace)
	{
		if (chrEachMaster != lpCharMsTrace)
		{
			EachTradeButton = 0;
			OpenEachPlayer(lpCharMsTrace);
			DispEachMode = 0;
		}
	}
	else
	{
		if (lpCharSelPlayer && (chrEachMaster != lpCharSelPlayer) && (chrEachMaster != &chrPartyPlayer) && !DispEachMode)
		{
			OpenEachPlayer(lpCharSelPlayer);
			DispEachMode = 0;
		}
	}
	if (EachTradeButton && chrEachMaster)
	{
		if (GetTradeDistance(chrEachMaster) == FALSE)
			EachTradeButton = 0;
	}

	return FALSE;
}
int FindBipPoint(smPAT3D *lpPat, char *szObjNodeName, int frame, int *nX, int *nY, int *nZ)
{
	smOBJ3D	*lpObj;

	lpObj = lpPat->GetObjectFromName(szObjNodeName);
	if (!lpObj)
		return FALSE;

	smMATRIX *mWorld;
	POINT3D angle;

	ZeroMemory(&angle, sizeof(POINT3D));
	angle.y = (-angle.y + ANGLE_180)&ANGCLIP;

	mWorld = &lpObj->mWorld;

	AnimObjectTree(lpObj, frame, angle.x, angle.y, angle.z);

	*nX = mWorld->_41;
	*nZ = mWorld->_42;
	*nY = mWorld->_43;

	return TRUE;
}
int Record_ClinetLogFile(char *szMessage)
{
	HANDLE	hFile;
	DWORD	dwAcess;
	DWORD	FileLength;
	SYSTEMTIME	st;
	int len;
	char	szBuff[256];

	GetLocalTime(&st);

	hFile = CreateFile("savedata\\game.log", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	wsprintf(szBuff, "%d-%d (%d:%d:%d) - %s", st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, szMessage);
	len = lstrlen(szBuff);
	if (szBuff[len - 1] != '\n')
	{
		szBuff[len] = '\r';
		szBuff[len + 1] = '\n';
		len += 2;
	}

	FileLength = GetFileSize(hFile, NULL);
	SetFilePointer(hFile, FileLength, NULL, FILE_BEGIN);
	WriteFile(hFile, szBuff, len, &dwAcess, NULL);
	CloseHandle(hFile);

	return TRUE;
}
#include "TJBOY\\park\\ParkPlayer\\ParkDXplayer.h"

int ParkPlayInit = 0;
int ParkPlayMode = 0;
int ParkPlaying = 0;
RECT ParkPlayRect;


int Init_ParkPlayer()
{
	ParkPlayInit = TRUE;
	ParkDXPlay.InitPlayer();
	ParkPlayMode = 0;
	ParkPlaying = 0;
	ParkPlayRect.left = 0;
	ParkPlayRect.top = 0;
	ParkPlayRect.right = RESOLUTION_WIDTH;
	ParkPlayRect.bottom = RESOLUTION_HEIGHT;

	return TRUE;
}
int Play_ParkPlayer(char *szPath, int x, int y, int w, int h, int PlayMode)
{
	if (ParkPlaying)
		Stop_ParkPlayer();

	Init_ParkPlayer();

	if (ParkDXPlay.LoadPlayerFile(hwnd, szPath))
	{
		ParkDXPlay.PlaySize(x, y, w, h);
		ParkDXPlay.PlayPlayer();
		ParkPlayMode = PlayMode;
		ParkPlaying = TRUE;

		ParkPlayRect.left = x;
		ParkPlayRect.top = y;
		ParkPlayRect.right = x + w;
		ParkPlayRect.bottom = y + h;

		return TRUE;
	}

	return FALSE;
}
int Stop_ParkPlayer()
{
	ParkDXPlay.StopPlayer();
	ParkPlayMode = 0;
	ParkPlaying = FALSE;

	return TRUE;
}
