#include "StdAfx.h"
#include "..\\tjboy\\clanmenu\\tjclan.h"

cINTERFACE	cInterFace;
sSHADOWSTATE sShadowState[3];

int sinBmpLength[5] = { 0,0,0,0,0 }; //¶óÀÌÇÁ ¸¶³ª ½ºÅ×¹Ì³ª °æÇèÄ¡ 

int TestKeyAniFlag = 0;

////////////////¹öÆ°°ü·Ã Flag
int ExitButtonClick = 0;
int HelpButtonClick = 0;
int MouseButtonPosi = 0;
int sinMenuBottonPosi = 0;
int sinRunCameraMapPosi = 0; //°È±â Ä«¸Þ¶ó ¸Ê 
int SunandMoonFlag[2] = { 0,0 }; //0 ÇØ 1 ´Þ 
int InterButtonDown = 0;  //ÀÎÅÍÆäÀÌ½º ¹öÆ° ´Ù¿î ÇÃ·¢ 
int sinFireShow = 1;      //ºÒÀ» º¸¿©ÁØ´Ù 

////////////////½ºÅ³ °ÔÀÌÁö (ÇöÀç´Â »ç¿ëµÇ°í ÀÖÁö ¾Ê´Ù )
int ReSizelpGage = 0;     //°ÔÀÌÁö ±×¸²À» Á¶Á¤ÇÑ´Ù 


////////////////
int InitStateFlag = 0;    //ÃÊ±âÈ­ ÇÃ·¢ 


//////////////// ¹é¾÷ Æ÷ÀÎÅÍ 
char szInfoMsgBuff5[512];  //»ý¸í·Â ±â·Â ±Ù·Â °æÇèÄ¡ ÀÇ ¼öÄ¡ ±â·Ï ¹öÆÛ 
char szInfoMsgBuff6[128];  //»ý¸í·Â ±â·Â ±Ù·Â °æÇèÄ¡ ÀÇ ¼öÄ¡ ±â·Ï ¹öÆÛ 
POINT InfoMessageBoxPos;  //ÅØ½º¸¦ Ç¥½ÃÇÒ ÁÂÇ¥ 


//////////////// Àü»ç (´Ù½Ã½ÃÀÛ )
int ReStartFlag = 0;  //°ªÀÌ µé¾î¿À¸é ´Ù½Ã½ÃÀÛ ÀÎÅÍÆäÀÌ½º¸¦ º¸¿©ÁØ´Ù 
POINT ReStartMainXY = { 0,0 }; //´Ù½Ã½ÃÀÛ ÁÂÇ¥ 
int ReStartIndex = 0;
POINT ReStartTextXY = { 0,0 };
char szReStartMsg[128];
char szReStartMsg2[128];

int RestartCheckExp = 0;
int ReStartOptionIndex = 0;
int ShowExpPercentFlag = 0;

//////////////// ½ºÅ³ Àü¾÷ Á¾·á  (´Ù½Ã½ÃÀÛ )

int SkillNpcFlag = 0;  //°ªÀÌ µé¾î¿À¸é ´Ù½Ã½ÃÀÛ ÀÎÅÍÆäÀÌ½º¸¦ º¸¿©ÁØ´Ù 
POINT SkillMasterMainXY = { 0,0 }; //´Ù½Ã½ÃÀÛ ÁÂÇ¥ 
int SkillMasterIndex = 0;
POINT SkillMasterTextXY = { 0,0 };
char szSkillMasterMsg[128];
char szSkillMasterMsg2[128];
int SkillMasterOptionIndex = 0;

////////½ºÅ³ »ç¿ë ºÒÃæÁ· ÀÌÆåÆ® 
int NotUseSkillEffect[3] = { 0,0,0 };

int SkillMouseButtonPosi[2] = { 0,0 };

/////////// ³· ¹ã
int DayOrNightFlag = 0;
int sinGageTime2 = 0;


int ReStartButtonRect[3][4] = {
	{21,22,21 + 44,22 + 44},			//ÇÊµå¿¡¼­ ½ÃÀÛ 
	{72,22,72 + 44,22 + 44},			//¸¶À»¿¡¼­ ½ÃÀÛ 
	{123,22,123 + 44,22 + 44},			//°ÔÀÓ Á¾·á 

};

int ButtonRect[6][5] = {   //¹Ú½º ¿ÀÇÂ ¹öÆ° 
	{648,560,648 + 25,560 + 27},
	{673,560,673 + 25,560 + 27},
	{698,560,698 + 25,560 + 27},
	{723,560,723 + 25,560 + 27},
	{748,560,748 + 25,560 + 27},
	{772,560,772 + 25,560 + 27},

};
int sinMenuRect[3][4] = {  //°ÔÀÓ Á¾·á ....
	{692,492,784,511},
	{692,517,784,536},
	{692,542,784,561}, //Á¾·á 


};

int sinRunCameraMap[3][4] = { //°È±â , Ä«¸Þ¶ó , ¸Ê 
	{569,555,569 + 26,555 + 26},
	{569 + 26,555,569 + 26 + 26,555 + 26},
	{569 + 26 + 26,555,569 + 26 + 26 + 26,555 + 26},

};


// Àü¾÷ °ü·Ã 
int ChangeJobButtonclick = 0;


//PK°ü·Ã
int sinPKWarningExpFlag = 0;
int sinPKWarnigExpTime = 0;


struct HAEFFECT
{
	int   Flag;
	int   Time;
	POINT Posi;
	POINT Size;
	int   Mat;
	int   Alpha;
};
char *HaEffectFilePath[] = {
	0,
	"Image\\SinImage\\Inter\\defense.tga", //1
	"Image\\SinImage\\Inter\\block.tga",   //2
	"Image\\SinImage\\Inter\\Evade.tga",   //3
	0,
};
#define  MAX_HAEFFECTNUM 10 //ÃÑ°¹¼ö

int HA_EffectIndex[4] = { 0, }; //

HAEFFECT HaEffect[MAX_HAEFFECTNUM];
//=====================================================================================

/*----------------------------------------------------------------------------*
*							Å¬·¡½º ÃÊ±â, Á¾·á
*-----------------------------------------------------------------------------*/
cINTERFACE::cINTERFACE()
{
	memset(&HaEffect, 0, sizeof(HAEFFECT));
	DayNightFlag = FALSE;
}
cINTERFACE::~cINTERFACE()
{
	Release();
}
/*----------------------------------------------------------------------------*
*							     ÃÊ±âÈ­
*-----------------------------------------------------------------------------*/
void cINTERFACE::Init()
{
	ReStartMainXY.x = (RESOLUTION_WIDTH / 2) - (187 / 2);
	ReStartMainXY.y = (RESOLUTION_HEIGHT / 2) - (127 / 2) - 100;

	ReStartTextXY.x = ReStartMainXY.x + 23;
	ReStartTextXY.y = ReStartMainXY.y + 73;

	SkillMasterMainXY.x = (RESOLUTION_WIDTH / 2) - (187 / 2) - 30;
	SkillMasterMainXY.y = (RESOLUTION_HEIGHT / 2) - (127 / 2) - 100;

	SkillMasterTextXY.x = SkillMasterMainXY.x + 23;
	SkillMasterTextXY.y = SkillMasterMainXY.y + 73;

	InitState();

	MatMenu[0] = CreateTextureMaterial("Image\\SinImage\\Inter\\Menu-1.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatMenu[1] = CreateTextureMaterial("Image\\SinImage\\Inter\\Menu-2.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatExitMenu = CreateTextureMaterial("Image\\SinImage\\Inter\\ExitMenu.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatClock = CreateTextureMaterial("Image\\SinImage\\Inter\\Clock.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatComPass = CreateTextureMaterial("Image\\SinImage\\Inter\\Compass.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatLife = CreateTextureMaterial("Image\\SinImage\\Inter\\ShadowLife.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatMana = CreateTextureMaterial("Image\\SinImage\\Inter\\ShadowMana.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	MatStamina = CreateTextureMaterial("Image\\SinImage\\Inter\\ShadowStamina.tga", 0, 0, 0, SMMAT_BLEND_ALPHA);
	Load();

}
/*----------------------------------------------------------------------------*
*						    BmpÆÄÀÏÀ» ·ÎµåÇÑ´Ù
*-----------------------------------------------------------------------------*/
void cINTERFACE::Load()
{
	lpLIFE = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\Bar_Life.bmp");
	lpMP = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\Bar_Mana.bmp");
	lpSTM = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\Bar_Stamina.bmp");

	lpButton[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\bStatus.bmp"); //¹«ºê ÀÌ¹ÌÁö 
	lpButton[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\bInvenTory.bmp");
	lpButton[2] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\bSkill.bmp");
	lpButton[3] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\bParty.bmp");
	lpButton[4] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\bQuest.bmp");
	lpButton[5] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\bSystem.bmp");

	lpButton2[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\bStatus-1.bmp"); //Å¬¸¯ ÀÌ¹ÌÁö 
	lpButton2[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\bInvenTory-1.bmp");
	lpButton2[2] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\bSkill-1.bmp");
	lpButton2[3] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\bParty-1.bmp");
	lpButton2[4] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\bQuest-1.bmp");
	lpButton2[5] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\bSystem-1.bmp");

	lpInfoBox[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\ButtonInfo\\StatusInfo.bmp"); //Ç³¼± µµ¿ò¸»
	lpInfoBox[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\ButtonInfo\\InvenInfo.bmp"); //Ç³¼± µµ¿ò¸»
	lpInfoBox[2] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\ButtonInfo\\SkillInfo.bmp"); //Ç³¼± µµ¿ò¸»
	lpInfoBox[3] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\ButtonInfo\\PartyInfo.bmp"); //Ç³¼± µµ¿ò¸»
	lpInfoBox[4] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\ButtonInfo\\QuestInfo.bmp"); //Ç³¼± µµ¿ò¸»
	lpInfoBox[5] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\ButtonInfo\\SystemInfo.bmp"); //Ç³¼± µµ¿ò¸»

	lpMenuButton[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\Option.bmp"); //¿É¼Ç 
	lpMenuButton[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\Config.bmp"); //´Ù½Ã½ÃÀÛ 
	lpMenuButton[2] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\Exit.bmp"); //³ª°¡±â

	lpWalk = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\Button\\Walk.bmp"); //°È±â 

	lpChatShowButton = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\Chat\\ChatDownButton.bmp"); //Ã¤ÆÃ¹öÆ°  

	lpSun = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\Flash\\Sun.bmp"); //ÇØ 
	lpMoon = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\Flash\\Moon.bmp"); //´Þ 

	lpGage[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Skill\\P-skill.bmp");  //¿ÞÂÊ  ½ºÅ³°ÔÀÌÁö
	lpGage[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\Skill\\P-skill2.bmp");  //¿À¸¥ÂÊ ½ºÅ³°ÔÀÌÁö

	lpBar_Anger = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\sinGage\\Bar_Anger.bmp");  //°ÔÀÌÁö ÀüÃ¼  
	lpBar_Time = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\sinGage\\Bar_Time.bmp");  //°ÔÀÌÁö ÀüÃ¼  
	lpBar_Exp = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\sinGage\\Bar_Exp_New.bmp");  //°ÔÀÌÁö ÀüÃ¼  
	lpButton_Anger = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\sinGage\\Button_Anger.bmp");  //°ÔÀÌÁö ÀüÃ¼   

	lpRunInfo = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\ButtonInfo\\Run.bmp");  //¶Ù±âÇ³¼± µµ¿ò¸» 
	lpWalkInfo = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\ButtonInfo\\Walk.bmp"); //°È±âÇ³¼± µµ¿ò¸» 

	lpCameraHandInfo = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\ButtonInfo\\Camera_Hand.bmp");   //¼öµ¿ Ä«¸Þ¶ó Ç³¼± µµ¿ò¸» 
	lpCameraFixInfo = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\ButtonInfo\\Camera_Fix.bmp");   //¼öµ¿ Ä«¸Þ¶ó Ç³¼± µµ¿ò¸» 
	lpCameraAutoInfo = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\ButtonInfo\\Camera_Auto.bmp");   //ÀÚµ¿ Ä«¸Þ¶ó Ç³¼± µµ¿ò¸» 

	lpMapOnInfo = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\ButtonInfo\\MapOn.bmp");   //ÀÚµ¿ Ä«¸Þ¶ó Ç³¼± µµ¿ò¸» 
	lpMapOffInfo = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\ButtonInfo\\MapOff.bmp");   //¼öµ¿ Ä«¸Þ¶ó Ç³¼± µµ¿ò¸» 

	lpMapOnImage = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\Button\\MapOnImage.bmp");  //¸ÊÇ¥½Ã ¿Â ÀÌ¹ÌÁö 
	lpCameraImage[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\Button\\AutoCameraImage.bmp"); //Ä«¸Þ¶ó AutoÀÌ¹ÌÁö 
	lpCameraImage[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\Button\\PixCameraImage.bmp"); //Ä«¸Þ¶ó °íÁ¤ ÀÌ¹ÌÁö

	lpLIFESpot = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\Bar_LifeSpot.bmp");        //¶óÀÌÇÁ 
	lpSTMSpot = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\Bar_StaminaSpot.bmp");        //½ºÅ×¹Ì³ª 
	lpMANASpot = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\Bar_ManaSpot.bmp");        //ºÐ³ë°ÔÀÌÁö 

	lpReStartMain = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\ReStart\\ReStartMain.bmp"); //´Ù½Ã½ÃÀÛ ¸ÞÀÎ 
	lpReStartButton[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\ReStart\\ReStart_Field.bmp"); //´Ù½Ã½ÃÀÛ ¹öÆ° 
	lpReStartButton[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\ReStart\\ReStart_Town.bmp"); //´Ù½Ã½ÃÀÛ ¹öÆ° 
	lpReStartButton[2] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\ReStart\\ReStart_Exit.bmp"); //´Ù½Ã½ÃÀÛ ¹öÆ° 

	lpSelectSkill_Main[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\SkillIcon\\G_Select_Skill.bmp"); //½ºÅ³ ¹è¿ì±â 0 ±×·¹ÀÌ 1 È°¼º 
	lpSelectSkill_Main[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\SkillIcon\\Select_Skill.bmp"); //½ºÅ³ ¹è¿ì±â 0 ±×·¹ÀÌ 1 È°¼º 

	lpSelectChangeJob[0] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\SkillIcon\\G_Select_ChangeJob.bmp"); //Àü¾÷        0 ±×·¹ÀÌ 2 È°¼º 
	lpSelectChangeJob[1] = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\SkillIcon\\Select_ChangeJob.bmp"); //Àü¾÷        0 ±×·¹ÀÌ 2 È°¼º 

	lpGrowInterLeft = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\inter_01.bmp"); //È®Àå ÀÎÅÍÆäÀÌ½º
	lpGrowInterMiddle = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\inter_02.bmp");
	lpGrowInterRight = LoadDibSurfaceOffscreen("Image\\SinImage\\Inter\\inter_03.bmp");
}
/*----------------------------------------------------------------------------*
*						     Release
*-----------------------------------------------------------------------------*/
void cINTERFACE::Release()
{
	DELET(lpLIFE);
	DELET(lpMP);
	DELET(lpSTM);

	for (int i = 0; i < 6; i++)
	{
		DELET(lpButton[i]);
		DELET(lpButton2[i]);
		DELET(lpInfoBox[i]);
	}
	for (int i = 0; i < 3; i++)
		DELET(lpMenuButton[i]);

	DELET(lpWalk);
	DELET(lpChatShowButton);
	DELET(lpSun);
	DELET(lpMoon);
	DELET(lpGage[0]);
	DELET(lpGage[1]);
	DELET(lpBar_Anger);
	DELET(lpBar_Time);
	DELET(lpBar_Exp);
	DELET(lpButton_Anger);
	DELET(lpRunInfo);
	DELET(lpWalkInfo);
	DELET(lpCameraHandInfo);
	DELET(lpCameraFixInfo);
	DELET(lpCameraAutoInfo);
	DELET(lpMapOnInfo);
	DELET(lpMapOffInfo);
	DELET(lpMapOnImage);
	DELET(lpCameraImage[0]);
	DELET(lpCameraImage[1]);
	DELET(lpLIFESpot);
	DELET(lpSTMSpot);
	DELET(lpMANASpot);
	DELET(lpReStartMain);

	for (int i = 0; i < 3; i++)
		DELET(lpReStartButton[i]);

	DELET(lpSelectSkill_Main[0]);
	DELET(lpSelectSkill_Main[1]);
	DELET(lpSelectChangeJob[0]);
	DELET(lpSelectChangeJob[1]);
	DELET(lpGrowInterLeft);
	DELET(lpGrowInterMiddle);
	DELET(lpGrowInterRight);
}
/*----------------------------------------------------------------------------*
*							     ±×¸®±â
*-----------------------------------------------------------------------------*/
int sinWinSizeX[] = { 1024,1280,1600 };
int sinWinSizeXindex[] = { 2,6,11 };
int nCheckSkillDraw = 0;
void cINTERFACE::Draw()
{
	int i = 0;
	int j = 0;

	dsDrawTexImage(cInterFace.MatMenu[0], 800 - 256 - 256, 600 - 128, 256, 128, 255);
	dsDrawTexImage(cInterFace.MatMenu[1], 800 - 256, 600 - 64, 256, 64, 255);

	DrawSprite(800, RESOLUTION_HEIGHT - 64, lpGrowInterLeft, 0, 0, 66, 64, 777);

	for (i = 0; i < 3; i++)
	{
		if (sinWinSizeX[i] == RESOLUTION_WIDTH)
		{
			for (j = 0; j < sinWinSizeXindex[i]; j++)
				DrawSprite(800 + 66 + (64 * j), RESOLUTION_HEIGHT - 64, lpGrowInterMiddle, 0, 0, 64, 64, 777);
		}
	}

	DrawSprite(800 + 66 + (64 * j), RESOLUTION_HEIGHT - 64, lpGrowInterRight, 0, 0, 40, 64, 777);


	for (i = 0; i < 3; i++)
	{
		if (sShadowState[i].Flag)
			dsDrawColorBox(sShadowState[i].Color, sShadowState[i].Posi.x, sShadowState[i].Posi.y, sShadowState[i].Size.x, sShadowState[i].Size.y);
	}

	DrawSprite(319, 500 + (94 - sinBmpLength[0]), lpLIFE, 0, (94 - sinBmpLength[0]), 16, 94);
	DrawSprite(465, 500 + (94 - sinBmpLength[1]), lpMP, 0, (94 - sinBmpLength[1]), 16, 94);
	DrawSprite(303, 518 + (76 - sinBmpLength[2]), lpSTM, 0, (76 - sinBmpLength[2]), 8, 76);

	if (ExitButtonClick)
	{
		dsDrawTexImage(MatExitMenu, 698, 476, 128, 96, 255);

		if (sinMenuBottonPosi == 1)
			DrawSprite(698, 510, lpMenuButton[0], 0, 0, 96, 19);

		if (sinMenuBottonPosi == 2)
			DrawSprite(698, 483, lpMenuButton[1], 0, 0, 96, 19);

		if (sinMenuBottonPosi == 3)
			DrawSprite(698, 540, lpMenuButton[2], 0, 0, 96, 19);
	}

	if (DayOrNightFlag == 1)
	{
		DrawSprite(363, 589, lpSun, 0, 0, 13, 13);
		DrawSprite(375, 593, lpBar_Time, 0, 0, sinGageTime2, 5);
	}
	else
	{
		DrawSprite(426, 589, lpMoon, 0, 0, 13, 13);
		DrawSprite(375 + (50 - sinGageTime2), 593, lpBar_Time, (50 - sinGageTime2), 0, 50, 5);
	}

	if (DayNightFlag == 1)
	{
		char buff1[32], buff2[32];

		if (DayOrNightFlag == 1)
			lstrcpy(buff1, "It is currently day time.");
		else
			lstrcpy(buff1, "It is currently night time.");

		STRINGFORMAT(buff2, "%02d:%02d", GAMEMAP->GetGameHour(), GAMEMAP->GetGameMin());

		DrawDayNightMessage(335, 520, buff1, buff2);
	}

	int TempGage = 0;

	if (sinSkill.pLeftSkill)
	{
		TempGage = (int)((41.0f*(float)sinSkill.pLeftSkill->GageLength) / 35.0f);
		DrawSprite(338, 542 + (41 - TempGage), lpGage[0], 0, TempGage, 16, 41 - (41 - TempGage));
	}

	if (sinSkill.pRightSkill)
	{
		TempGage = (int)((41.0f*(float)sinSkill.pRightSkill->GageLength) / 35.0f);
		DrawSprite(446, 542 + (41 - TempGage), lpGage[1], 0, TempGage, 16, 41 - (41 - TempGage));

	}
	// ¾­ÑéÌõ
	if (sinPKWarningExpFlag)
	{
		if (sinPKWarnigExpTime <= 15)
			DrawSprite(575, 593, lpBar_Exp, (221 - sinBmpLength[3]), 0, 221, 5);
	}
	else
		DrawSprite(575, 593, lpBar_Exp, 0, 0, sinBmpLength[3], 5);

	if (!sInterFlags.RunFlag)
		DrawSprite(575, 565, lpWalk, 0, 0, 24, 25);

	if (sInterFlags.CameraAutoFlag == 1)
		DrawSprite(575 + 24, 565, lpCameraImage[0], 0, 0, 24, 25);

	if (sInterFlags.CameraAutoFlag == 2)
		DrawSprite(575 + 24, 565, lpCameraImage[1], 0, 0, 24, 25);

	if (sInterFlags.MapOnFlag)
		DrawSprite(575 + 24 + 24, 565, lpMapOnImage, 0, 0, 24, 25);

	switch (sinRunCameraMapPosi)
	{
	case 1:
		if (sInterFlags.RunFlag)
			DrawSprite(575 + 12 - (76 / 2), 565 - 29, lpRunInfo, 0, 0, 77, 27);
		else
			DrawSprite(575 + 12 - (76 / 2), 565 - 29, lpWalkInfo, 0, 0, 77, 27);
		break;
	case 2:
		if (sInterFlags.CameraAutoFlag == 0)
		{
			DrawSprite(575 + 24 + 12 - (76 / 2), 565 - 29, lpCameraHandInfo, 0, 0, 77, 27);
			cHelpPet.PetMessage("*Camera_Hand", 0);
		}
		if (sInterFlags.CameraAutoFlag == 2)
		{
			DrawSprite(575 + 24 + 12 - (76 / 2), 565 - 29, lpCameraFixInfo, 0, 0, 77, 27);
			cHelpPet.PetMessage("*Camera_Fix", 0);
		}
		if (sInterFlags.CameraAutoFlag == 1)
		{
			DrawSprite(575 + 26 + 13 - (76 / 2), 565 - 29, lpCameraAutoInfo, 0, 0, 77, 27);
			cHelpPet.PetMessage("*Camera_Auto", 0);
		}
		break;
	case 3:
		if (sInterFlags.MapOnFlag)
			DrawSprite(575 + 24 + 24 + 12 - (76 / 2), 565 - 29, lpMapOffInfo, 0, 0, 77, 27);
		else
			DrawSprite(575 + 24 + 24 + 12 - (76 / 2), 565 - 29, lpMapOnInfo, 0, 0, 77, 27);
		break;

	}

	for (int t = 0; t < 6; t++)
	{
		if (MouseButtonPosi == t + 1)
		{
			if (InterButtonDown)
				DrawSprite(648 + (t * 25), 560, lpButton2[t], 0, 0, 25, 27);
			else
			{
				DrawSprite(648 + (t * 25), 560, lpButton[t], 0, 0, 25, 27);
				DrawSprite(648 - (77 - 23 - 1) + (t * 25), 560 - 27, lpInfoBox[t], 0, 0, 77, 27);
			}
		}
	}

	if (SkillNpcFlag)
	{
		DrawSprite(SkillMasterMainXY.x, SkillMasterMainXY.y, lpReStartMain, 0, 0, 188, 128);
		DrawSprite(SkillMasterMainXY.x + ReStartButtonRect[0][0], SkillMasterMainXY.y + ReStartButtonRect[0][1], lpSelectSkill_Main[0], 0, 0, 44, 44);
		DrawSprite(SkillMasterMainXY.x + ReStartButtonRect[1][0], SkillMasterMainXY.y + ReStartButtonRect[1][1], lpSelectChangeJob[0], 0, 0, 44, 44);
		if (SkillMasterIndex)
		{
			if (SkillMasterIndex == 1 && SkillMasterOkFlag[0])
				DrawSprite(SkillMasterMainXY.x + ReStartButtonRect[SkillMasterIndex - 1][0], SkillMasterMainXY.y + ReStartButtonRect[SkillMasterIndex - 1][1], lpSelectSkill_Main[1], 0, 0, 44, 44);
			if (SkillMasterIndex == 2 && SkillMasterOkFlag[1])
				DrawSprite(SkillMasterMainXY.x + ReStartButtonRect[SkillMasterIndex - 1][0], SkillMasterMainXY.y + ReStartButtonRect[SkillMasterIndex - 1][1], lpSelectChangeJob[1], 0, 0, 44, 44);
			if (SkillMasterIndex == 3)
				DrawSprite(SkillMasterMainXY.x + ReStartButtonRect[SkillMasterIndex - 1][0], SkillMasterMainXY.y + ReStartButtonRect[SkillMasterIndex - 1][1], lpReStartButton[2], 0, 0, 44, 44);
		}
	}
	if (ShowSkillClose)
	{
		DrawSprite(269, 571 + (256 - sinMoveKindInter[SIN_SKILL]), cShop.lpExit, 0, 0, 20, 20);
		DrawSprite(269, 571 - 27 + (256 - sinMoveKindInter[SIN_SKILL]), cInvenTory.lpExitInfo, 0, 0, 47, 27);
	}

	for (int k = 0; k < 10; k++)
	{
		if (HaEffect[k].Flag)
			dsDrawTexImage(HaEffect[k].Mat, HaEffect[k].Posi.x, HaEffect[k].Posi.y, HaEffect[k].Size.x, HaEffect[k].Size.y, HaEffect[k].Alpha);
	}

	int len = 0;
	int x = 0, y = 0;

	int dsDrawOffsetArrayBackup = dsDrawOffsetArray;

	dsDrawOffsetArray = dsARRAY_TOP;

	if (SkillMasterFlag == 1)
	{
		for (i = 0; i < SkillUpInfo.x; i++)
		{
			for (int j = 0; j < SkillUpInfo.y; j++)
			{
				if (i == 0 && j == 0)
					dsDrawTexImage(cItem.MatItemInfoBox_TopLeft, SkillUpInfoPosi.x + (i * 16), SkillUpInfoPosi.y + (j * 16), 16, 16, 255);
				if (j == 0 && i != 0 && i + 1 < SkillUpInfo.x)
					dsDrawTexImage(cItem.MatItemInfoBox_TopCenter, SkillUpInfoPosi.x + (i * 16), SkillUpInfoPosi.y + (j * 16), 16, 16, 255);
				if (j == 0 && i + 1 == SkillUpInfo.x)
					dsDrawTexImage(cItem.MatItemInfoBox_TopRight, SkillUpInfoPosi.x + (i * 16), SkillUpInfoPosi.y + (j * 16), 16, 16, 255);

				if (i == 0 && j != 0 && j + 1 != SkillUpInfo.y)
					dsDrawTexImage(cItem.MatItemInfoBox_Left, SkillUpInfoPosi.x + (i * 16), SkillUpInfoPosi.y + (j * 16), 16, 16, 255);
				if (i != 0 && j != 0 && i + 1 != SkillUpInfo.x && j + 1 != SkillUpInfo.y)
					dsDrawTexImage(cItem.MatItemInfoBox_Center, SkillUpInfoPosi.x + (i * 16), SkillUpInfoPosi.y + (j * 16), 16, 16, 255);
				if (i + 1 == SkillUpInfo.x && j != 0 && j + 1 != SkillUpInfo.y)
					dsDrawTexImage(cItem.MatItemInfoBox_Right, SkillUpInfoPosi.x + (i * 16), SkillUpInfoPosi.y + (j * 16), 16, 16, 255);

				if (i == 0 && j + 1 == SkillUpInfo.y)
					dsDrawTexImage(cItem.MatItemInfoBox_BottomLeft, SkillUpInfoPosi.x + (i * 16), SkillUpInfoPosi.y + (j * 16), 16, 16, 255);
				if (i != 0 && j + 1 == SkillUpInfo.y && i + 1 != SkillUpInfo.x)
					dsDrawTexImage(cItem.MatItemInfoBox_BottomCenter, SkillUpInfoPosi.x + (i * 16), SkillUpInfoPosi.y + (j * 16), 16, 16, 255);
				if (j + 1 == SkillUpInfo.y && i + 1 == SkillUpInfo.x)
					dsDrawTexImage(cItem.MatItemInfoBox_BottomRight, SkillUpInfoPosi.x + (i * 16), SkillUpInfoPosi.y + (j * 16), 16, 16, 255);
			}
		}

		if (ShowSkillUpInfo)
		{
			for (i = 0; i < 10; i++)
			{
				if (SkillIconIndex[i])
					DrawSprite(SkillUpInfoPosi.x + SkillIconPosi.x + (i * 18) - 10, SkillUpInfoPosi.y + SkillIconPosi.y, cSkill.lpWeaponIcon[SkillIconIndex[i]], 0, 0, 18, 24);
			}
		}

		int BoldFlag = 0;
		int MasteryLen = 0;
		int MasteryShowX = 0;

		char strBuff[128];
		memset(strBuff, 0, sizeof(strBuff));

		if (SkillMasterFlag == 1 && !ShowSkillUpInfo)
		{
			dsTextLineOut(1, 100, 225 - 80, SkillUseInfoText[0], lstrlen(SkillUseInfoText[0]), D3DCOLOR_XRGB(222, 231, 255));

			if (sinSkill.SkillPoint || sinSkill.SkillPoint4)
			{
				dsTextLineOut(0, 100, 260 - 80, SkillUseInfoText[1], lstrlen(SkillUseInfoText[1]), D3DCOLOR_XRGB(255, 255, 255));
				dsTextLineOut(0, 100, 280 - 80, SkillUseInfoText[2], lstrlen(SkillUseInfoText[2]), D3DCOLOR_XRGB(255, 255, 255));
				wsprintf(strBuff, "Skill Points: %d", sinSkill.SkillPoint);
				dsTextLineOut(1, 100, 310 - 80, strBuff, lstrlen(strBuff), D3DCOLOR_XRGB(247, 243, 193));
				wsprintf(strBuff, "Elite Skill Points: %d", sinSkill.SkillPoint4);
				dsTextLineOut(1, 103, 310 - 55, strBuff, lstrlen(strBuff), D3DCOLOR_XRGB(147, 243, 193));
			}
			else
			{
				dsTextLineOut(0, 100, 260 - 80, SkillUseInfoText[3], lstrlen(SkillUseInfoText[3]), D3DCOLOR_XRGB(255, 64, 64));
				dsTextLineOut(0, 100, 280 - 80, SkillUseInfoText[4], lstrlen(SkillUseInfoText[4]), D3DCOLOR_XRGB(255, 64, 64));
			}
		}
	}

	if (SkillMasterFlag && !ShowSkillUpInfo && (CheckQuestButtonShow1 || CheckQuestButtonShow2 || CheckQuestButtonShow3))
	{
		if (sinChangeJobButtonShow || sinChangeJobButtonShow2 || sinChangeJobButtonShow3 || sinChangeJobButtonShow4)
		{
			DrawSprite(240, 380, lpSelectChangeJob[1], 0, 0, 44, 44);
			nCheckSkillDraw = 1;
		}
		else
		{
			DrawSprite(240, 380, lpSelectChangeJob[0], 0, 0, 44, 44);
			nCheckSkillDraw = 2;
		}
	}

	if (SkillMasterFlag && !ShowSkillUpInfo && (nCheckSkillDraw == 1))
		DrawSprite(240, 380, lpSelectChangeJob[1], 0, 0, 44, 44);

	if (SkillMasterFlag && !ShowSkillUpInfo && (nCheckSkillDraw == 2))
		DrawSprite(240, 380, lpSelectChangeJob[0], 0, 0, 44, 44);

	dsDrawOffsetArray = dsDrawOffsetArrayBackup;

	if (SkillInfoShowFlag && !ShowSkillUpInfo)
	{
		if (SkillInfoShowFlag == 2)
			dsDrawOffsetArray = dsARRAY_TOP;
		for (i = 0; i < SkillBoxSize.x; i++)
		{
			for (int j = 0; j < SkillBoxSize.y; j++)
			{
				if (i == 0 && j == 0)
					dsDrawTexImage(cItem.MatItemInfoBox_TopLeft, SkillInfoBoxPosi.x + (i * 16), SkillInfoBoxPosi.y + (j * 16), 16, 16, 255);
				if (j == 0 && i != 0 && i + 1 < SkillBoxSize.x)
					dsDrawTexImage(cItem.MatItemInfoBox_TopCenter, SkillInfoBoxPosi.x + (i * 16), SkillInfoBoxPosi.y + (j * 16), 16, 16, 255);
				if (j == 0 && i + 1 == SkillBoxSize.x)
					dsDrawTexImage(cItem.MatItemInfoBox_TopRight, SkillInfoBoxPosi.x + (i * 16), SkillInfoBoxPosi.y + (j * 16), 16, 16, 255);
				if (i == 0 && j != 0 && j + 1 != SkillBoxSize.y)
					dsDrawTexImage(cItem.MatItemInfoBox_Left, SkillInfoBoxPosi.x + (i * 16), SkillInfoBoxPosi.y + (j * 16), 16, 16, 255);
				if (i != 0 && j != 0 && i + 1 != SkillBoxSize.x && j + 1 != SkillBoxSize.y)
					dsDrawTexImage(cItem.MatItemInfoBox_Center, SkillInfoBoxPosi.x + (i * 16), SkillInfoBoxPosi.y + (j * 16), 16, 16, 255);
				if (i + 1 == SkillBoxSize.x && j != 0 && j + 1 != SkillBoxSize.y)
					dsDrawTexImage(cItem.MatItemInfoBox_Right, SkillInfoBoxPosi.x + (i * 16), SkillInfoBoxPosi.y + (j * 16), 16, 16, 255);
				if (i == 0 && j + 1 == SkillBoxSize.y)
					dsDrawTexImage(cItem.MatItemInfoBox_BottomLeft, SkillInfoBoxPosi.x + (i * 16), SkillInfoBoxPosi.y + (j * 16), 16, 16, 255);
				if (i != 0 && j + 1 == SkillBoxSize.y && i + 1 != SkillBoxSize.x)
					dsDrawTexImage(cItem.MatItemInfoBox_BottomCenter, SkillInfoBoxPosi.x + (i * 16), SkillInfoBoxPosi.y + (j * 16), 16, 16, 255);
				if (j + 1 == SkillBoxSize.y && i + 1 == SkillBoxSize.x)
					dsDrawTexImage(cItem.MatItemInfoBox_BottomRight, SkillInfoBoxPosi.x + (i * 16), SkillInfoBoxPosi.y + (j * 16), 16, 16, 255);
			}
		}
		for (i = 0; i < 10; i++)
		{
			if (SkillIconIndex[i])
				DrawSprite(SkillInfoBoxPosi.x + SkillIconPosi.x + (i * 18), SkillInfoBoxPosi.y + SkillIconPosi.y, cSkill.lpWeaponIcon[SkillIconIndex[i]], 0, 0, 18, 24);
		}
	}

	if (InfoMessageBoxPos.x != 0 || InfoMessageBoxPos.y != 0)
		dsDrawTexImage(cItem.MatItemInfoBox_Center, InfoMessageBoxPos.x - 5, InfoMessageBoxPos.y - 1, lstrlen(szInfoMsgBuff5) * 6, 13, 255);

	cSkill.ShowClearSkillPointButton(SkillInfoBoxPosi.x + (SkillBoxSize.x * 16), SkillInfoBoxPosi.y + (SkillBoxSize.y * 16));

}
/*----------------------------------------------------------------------------*
*							     ¸ÞÀÎ
*-----------------------------------------------------------------------------*/
DWORD dwCheckTime; //½Ã°£À» Ã¼Å©ÇÑ´Ù 
int   CheckNotUseSkillTime[3] = { 0,0,0 };
int   CheckNotUseSkillCount[3] = { 0,0,0 };
int   CheckTime2[3] = { 0,0,0 };
int   CheckExpFlag = 0;
int   CheckExpFlag2 = 0;
int   CheckExpTime = 0;

DWORD dwTestKeyTime = 0;
int   TeskKeyMessageCnt = 0;
char *szTestKeyMsg[6] = { "³ª!  &(^_^)&    ",
						 "³ë!  /(^_^)/   ",
						 "³ª!  *(^_^)*  ",
						 "",
						 "",
						 "", };

void cINTERFACE::Main()
{
	int i = 0;

	if (GetFieldMapCursor() == TRUE && cInterFace.sInterFlags.MapOnFlag)
		cHelpPet.PetMessage("*Mini_Map", 0);

	if (365 < pCursorPos.x && 435 > pCursorPos.x && 589 < pCursorPos.y && 596 > pCursorPos.y)
		cHelpPet.PetMessage("*DayandNight", 0);

	GetWordTimeDisplay();

	if (sinPKWarningExpFlag)
	{
		sinPKWarnigExpTime++;

		if (sinPKWarnigExpTime > 30)
			sinPKWarnigExpTime = 0;
	}
	else
		sinPKWarnigExpTime = 0;

	sinMenuBottonPosi = 0;

	if (lpCurPlayer->psModelAnimation->iType == ANIMATIONTYPE_Die && lpCurPlayer->iFrameTimer > 100)
	{
		ReStartFlag = 1;

		if (!CheckExpFlag && !CheckExpFlag2)
		{
			if (!CheckFieldContExp())
				RestartCheckExp = 1;

			CheckExpFlag = 1;
		}

	}
	if (CheckExpFlag2)
	{
		CheckExpTime++;

		if (CheckExpTime > 100)
		{
			CheckExpFlag2 = 0;
			CheckExpTime = 0;
		}
	}

	DWORD dwHour = GAMEMAP->GetGameHour();

	if (dwHour >= 8 && dwHour <= 18)
	{
		SunandMoonFlag[0] = 1;
		SunandMoonFlag[1] = 0;
	}
	else
	{
		SunandMoonFlag[0] = 0;
		SunandMoonFlag[1] = 1;
	}
	if (sinLoadOK)
	{
		if (!InitStateFlag)InitState();
		CheckingState();
	}

	MouseButtonPosi = 0;

	for (i = 0; i < 6; i++)
	{
		if (ButtonRect[i][0] < pCursorPos.x  && ButtonRect[i][2] > pCursorPos.x  && ButtonRect[i][1] < pCursorPos.y  && ButtonRect[i][3] > pCursorPos.y)
		{
			MouseButtonPosi = i + 1;
			switch (MouseButtonPosi)
			{
			case 1:
				cHelpPet.PetMessage("*CarStatus", 0);
				break;
			case 2:
				cHelpPet.PetMessage("*InvenTory", 0);
				break;
			case 3:
				cHelpPet.PetMessage("*Skill", 0);
				break;
			case 4:
				cHelpPet.PetMessage("*Party", 0);
				break;
			case 5:
				cHelpPet.PetMessage("*Quest", 0);
				break;
			case 6:
				cHelpPet.PetMessage("*System", 0);
				break;
			}
		}
	}
	sinRunCameraMapPosi = 0;

	for (i = 0; i < 3; i++)
	{
		if (sinRunCameraMap[i][0] < pCursorPos.x  && sinRunCameraMap[i][2] > pCursorPos.x  && sinRunCameraMap[i][1] < pCursorPos.y  && sinRunCameraMap[i][3] > pCursorPos.y)
		{
			sinRunCameraMapPosi = i + 1;
			switch (sinRunCameraMapPosi)
			{
			case 1:
				cHelpPet.PetMessage("*RunAndWalk", 0);
				break;
			}
		}
	}

	if (ExitButtonClick)
	{
		if (pCursorPos.x > 698 && pCursorPos.y > 510 && pCursorPos.x < 795 && pCursorPos.y < 524)
			sinMenuBottonPosi = 1;
		else if (pCursorPos.x > 698 && pCursorPos.y > 483 && pCursorPos.x < 795 && pCursorPos.y < 496)
			sinMenuBottonPosi = 2;
		else if (pCursorPos.x > 698 && pCursorPos.y > 540 && pCursorPos.x < 795 && pCursorPos.y < 555)
			sinMenuBottonPosi = 3;
	}

	CheckingState();
	ShowParaState();
	ShowExpPercent();

	ReStartIndex = 0;
	memset(szReStartMsg, 0, lstrlen(szReStartMsg));
	memset(szReStartMsg2, 0, lstrlen(szReStartMsg2));

	if (ReStartFlag)
	{
		sinMenuBottonPosi = 0;

		for (i = 0; i < 3; i++)
		{
			if (ReStartMainXY.x + ReStartButtonRect[i][0] < pCursorPos.x  && ReStartMainXY.x + ReStartButtonRect[i][2] > pCursorPos.x  && ReStartMainXY.y + ReStartButtonRect[i][1] < pCursorPos.y  && ReStartMainXY.y + ReStartButtonRect[i][3] > pCursorPos.y)
			{
				if (RestartCheckExp)
				{
					if (i == 0)
					{
						ReStartIndex = i + 1;
						lstrcpy(szReStartMsg, ReStartMsg[3]);
						lstrcpy(szReStartMsg2, ReStartMsg2[3]);
					}
					else
					{
						ReStartIndex = i + 1;
						lstrcpy(szReStartMsg, ReStartMsg[i]);
						lstrcpy(szReStartMsg2, ReStartMsg2[i]);
					}
				}
				else if (i == 0 && lpCurPlayer->iLoadedMapIndex >= 0 &&
					STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_BlessCastle)
					ReStartIndex = 0;
				else
				{
					ReStartIndex = i + 1;
					lstrcpy(szReStartMsg, ReStartMsg[i]);
					lstrcpy(szReStartMsg2, ReStartMsg2[i]);
				}
			}
		}

		dwCheckTime++;

		if (dwCheckTime > 70 * 20)
		{
			ReStartFlag = 0;
			ReStartOptionIndex = RESTART_TOWN;
			CheckExpFlag = 0;
			CheckExpFlag2 = 1;
			RestartCheckExp = 0;
		}
	}
	else
		dwCheckTime = 0;

	SkillMasterIndex = 0;
	memset(szSkillMasterMsg, 0, lstrlen(szSkillMasterMsg));
	memset(szSkillMasterMsg2, 0, lstrlen(szSkillMasterMsg2));

	if (SkillNpcFlag)
	{
		sinMenuBottonPosi = 0;
		for (i = 0; i < 3; i++)
		{
			if (SkillMasterMainXY.x + ReStartButtonRect[i][0] < pCursorPos.x  && SkillMasterMainXY.x + ReStartButtonRect[i][2] > pCursorPos.x  && SkillMasterMainXY.y + ReStartButtonRect[i][1] < pCursorPos.y  && SkillMasterMainXY.y + ReStartButtonRect[i][3] > pCursorPos.y)
			{
				SkillMasterIndex = i + 1;
				lstrcpy(szSkillMasterMsg, SkillMaster[i]);
				lstrcpy(szSkillMasterMsg2, SkillMaster2[i]);
			}
		}
	}
	for (int t = 0; t < 3; t++)
	{
		if (NotUseSkillElement[t])
		{
			CheckNotUseSkillTime[t]++;

			if (CheckNotUseSkillTime[t] > 12)
			{
				if (NotUseSkillEffect[t])
					NotUseSkillEffect[t] = 0;
				else
					NotUseSkillEffect[t] = 1;

				CheckNotUseSkillTime[t] = 0;
				CheckNotUseSkillCount[t]++;

				if (CheckNotUseSkillCount[t] > 4)
				{
					CheckNotUseSkillCount[t] = 0;
					CheckNotUseSkillTime[t] = 0;
					NotUseSkillEffect[t] = 0;
					NotUseSkillElement[t] = 0;
					SkillMouseButtonPosi[0] = 0;
					SkillMouseButtonPosi[1] = 0;
				}
			}
		}

		if (NotUseSkillEffect[t])
			CheckTime2[t]++;
		else
			CheckTime2[t] = 0;

		if (CheckTime2[t] > 20)
			NotUseSkillEffect[t] = 0;


	}
	for (int k = 0; k < MAX_HAEFFECTNUM; k++)
	{
		if (HaEffect[k].Flag)
		{
			if (HaEffect[k].Time < 3000)
				HaEffect[k].Time += 20;

			switch (HaEffect[k].Time / 255)
			{
			case 0:
				HaEffect[k].Alpha = 255;
				break;
			case 1:
				HaEffect[k].Alpha = 255;
				break;
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
				HaEffect[k].Alpha -= 10;
				HaEffect[k].Posi.x -= 1;
				HaEffect[k].Posi.y -= 1;
				HaEffect[k].Size.x += 3;
				HaEffect[k].Size.y += 3;
				if (HaEffect[k].Alpha <= 0)
				{
					HaEffect[k].Alpha = 0;
					HaEffect[k].Time = 0;
					HaEffect[k].Flag = 0;
				}
				break;
			};
		}
	}
}
/*----------------------------------------------------------------------------*
*							     Á¾·á
*-----------------------------------------------------------------------------*/
void cINTERFACE::Close()
{
	Release();
}
/*----------------------------------------------------------------------------*
*							   LButtonDown
*-----------------------------------------------------------------------------*/
void cINTERFACE::LButtonDown(int x, int y)
{
	if (365 < pCursorPos.x && 435 > pCursorPos.x && 589 < pCursorPos.y && 596 > pCursorPos.y)
		cHelpPet.PetMessage("*DayandNight", 1);

	if (pCursorPos.x > 315 && pCursorPos.x < 337 && pCursorPos.y > 500 && pCursorPos.y < 594)
		cHelpPet.PetMessage("*Bar_Life", 1);

	if (pCursorPos.x > 463 && pCursorPos.x < 483 && pCursorPos.y > 498 && pCursorPos.y < 595)
		cHelpPet.PetMessage("*Bar_Mana", 1);

	if (pCursorPos.x > 300 && pCursorPos.x < 313 && pCursorPos.y > 513 && pCursorPos.y < 595)
		cHelpPet.PetMessage("*Bar_Stamina", 1);

	if (pCursorPos.x > 483 && pCursorPos.x < 483 + 10 && pCursorPos.y > 513 && pCursorPos.y < 595)
		cHelpPet.PetMessage("*Bar_Exp", 1);

	if (pCursorPos.x > 500 && pCursorPos.x < 570 && pCursorPos.y > 540 && pCursorPos.y < 594)
		cHelpPet.PetMessage("*Exp_Num", 1);

	if (GetFieldMapCursor() == TRUE && cInterFace.sInterFlags.MapOnFlag)
		cHelpPet.PetMessage("*Mini_Map", 1);

	SkillMouseButtonPosi[0] = 1;
	ChangeJobButtonclick = 0;
	ReStartOptionIndex = 0;

	switch (sinRunCameraMapPosi)
	{
	case 1:
		if (sInterFlags.RunFlag)
			sInterFlags.RunFlag = 0;
		else
			sInterFlags.RunFlag = 1;
		break;
	case 2:
		sInterFlags.CameraAutoFlag++;
		if (sInterFlags.CameraAutoFlag > 2)
			sInterFlags.CameraAutoFlag = 0;

		break;
	case 3:
		if (sInterFlags.MapOnFlag)
			sInterFlags.MapOnFlag = 0;
		else
			sInterFlags.MapOnFlag = 1;
		break;

	};

	char *HelpFilePath = "image\\Sinimage\\Help\\Help.sin";

	switch (sinMenuBottonPosi)
	{
	case 1:
		cSinHelp.sinShowHelp(SIN_HELP_KIND_NORMAL, 208, 61 - 50, 11, 11, D3DCOLOR_RGBA(19, 27, 20, 165), HelpFilePath);
		ExitButtonClick = 0;
		HelpBoxKindIndex = SIN_HELP;
		break;
	case 2:
		SETTINGWINDOW->Show();
		ExitButtonClick = 0;
		break;
	case 3:
		QuitGame();
		break;
	}

	if (MouseButtonPosi)
	{
		InterButtonDown = 1;

		switch (MouseButtonPosi)
		{
		case 1:
			cHelpPet.PetMessage("*CarStatus", 1);
			break;
		case 2:
			cHelpPet.PetMessage("*InvenTory", 1);
			break;
		case 3:
			cHelpPet.PetMessage("*Skill", 1);
			break;
		case 4:
			cHelpPet.PetMessage("*Party", 1);
			break;
		case 5:
			cHelpPet.PetMessage("*Quest", 1);
			break;
		case 6:
			cHelpPet.PetMessage("*System", 1);
			break;
		}

	}
	if (ReStartFlag)
	{
		switch (ReStartIndex)
		{
		case RESTART_TOWN:
			ReStartOptionIndex = RESTART_TOWN;
			ReStartFlag = 0;
			RestartCheckExp = 0;

			break;
		case RESTART_FEILD:
			if (RestartCheckExp)break;
			ReStartOptionIndex = RESTART_FEILD;
			ReStartFlag = 0;
			RestartCheckExp = 0;

			break;
		case RESTART_EXIT:
			ReStartOptionIndex = RESTART_EXIT;
			ReStartFlag = 0;
			RestartCheckExp = 0;

			break;

		}

		CheckExpFlag2 = 1;
		CheckExpFlag = 0;

	}

	if (SkillMasterIndex)
	{
		if (SkillMasterIndex == 1 && SkillMasterOkFlag[0])
		{
			SkillMasterFlag = SkillMasterIndex;
			SkillNpcFlag = 0;
			cSkill.OpenFlag = 1;
			cInterFace.CheckAllBox(SIN_SKILL);
		}
		if (SkillMasterIndex == 2 && SkillMasterOkFlag[1])
		{
			SkillMasterFlag = SkillMasterIndex;
			SkillNpcFlag = 0;

			auto ps = GetCharacterClassData(sinChar->iClass, sinChar->iRank + 1);

			if (ps)
			{
				cMessageBox.ShowMessage3(MESSAGE_CHANGE_JOB, ps->pszName);
			}
		}
		if (SkillMasterIndex == 3)
		{
			SkillMasterFlag = SkillMasterIndex;
			SkillNpcFlag = 0;
		}
	}

}
/*----------------------------------------------------------------------------*
*							   LButtonUp
*-----------------------------------------------------------------------------*/
void cINTERFACE::LButtonUp(int x, int y)
{
	if (MouseButtonPosi)
	{
		switch (MouseButtonPosi)
		{
		case 1:
			if (cCharStatus.OpenFlag)
				cCharStatus.OpenFlag = SIN_CLOSE;
			else
				cCharStatus.OpenFlag = SIN_OPEN;
			cInterFace.CheckAllBox(SIN_CHARSTATUS);
			if (cCharStatus.OpenFlag) {
				if (!sinFireShow) {
					StartMenuFlame(0, 350);
					sinPlaySound(0);

				}
				else
					sinPlaySound(SIN_SOUND_SHOW_INTER);
				sinFireShow = 1;
			}

			break;
		case 2:
			if (cInvenTory.OpenFlag)
				cInvenTory.OpenFlag = SIN_CLOSE;
			else
				cInvenTory.OpenFlag = SIN_OPEN;
			cInterFace.CheckAllBox(SIN_INVENTORY);
			if (cInvenTory.OpenFlag)
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

			break;
		case 3:

			if (cSkill.OpenFlag == SIN_CLOSE)
				cSkill.OpenFlag = SIN_OPEN;
			else
				cSkill.OpenFlag = SIN_CLOSE;
			cInterFace.CheckAllBox(SIN_SKILL);
			if (cSkill.OpenFlag)
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

			break;
		case 4:
			ShowParty();
			break;
		case 5:
			ShowQuest();
			break;
		case 6:
			if (!ExitButtonClick)ExitButtonClick = 1;
			else ExitButtonClick = 0;
			cInterFace.CheckAllBox(SIN_SYSTEM);

			break;
		}

	}

	InterButtonDown = 0;


}
/*----------------------------------------------------------------------------*
*							   RButtonDown
*-----------------------------------------------------------------------------*/
void cINTERFACE::RButtonDown(int x, int y)
{

	if (GetFieldMapCursor() == TRUE && cInterFace.sInterFlags.MapOnFlag)
		cHelpPet.PetMessage("*Mini_Map", 2);

	if (MouseButtonPosi)
	{
		switch (MouseButtonPosi)
		{
		case 1:
			cHelpPet.PetMessage("*CarStatus", 2);
			break;
		case 2:
			cHelpPet.PetMessage("*InvenTory", 2);
			break;
		case 3:
			cHelpPet.PetMessage("*Skill", 2);
			break;
		case 4:
			cHelpPet.PetMessage("*Party", 2);
			break;
		case 5:
			cHelpPet.PetMessage("*Quest", 2);
			break;
		case 6:
			cHelpPet.PetMessage("*System", 2);
			break;
		}
	}

	switch (sinRunCameraMapPosi)
	{
	case 1:
		cHelpPet.PetMessage("*RunAndWalk", 2);
		break;
	case 2:
		if (sInterFlags.CameraAutoFlag == 0)
			cHelpPet.PetMessage("*Camera_Hand", 2);
		if (sInterFlags.CameraAutoFlag == 2)
			cHelpPet.PetMessage("*Camera_Fix", 2);
		if (sInterFlags.CameraAutoFlag == 1)
			cHelpPet.PetMessage("*Camera_Auto", 2);
		break;
	case 3:
		//cHelpPet.PetMessage("*Mini_Map",2);
		break;
	}


	if (365 < pCursorPos.x && 435 > pCursorPos.x && 589 < pCursorPos.y && 596 > pCursorPos.y)
		cHelpPet.PetMessage("*DayandNight", 2);

	if (pCursorPos.x > 315 && pCursorPos.x < 337 && pCursorPos.y > 500 && pCursorPos.y < 594)
		cHelpPet.PetMessage("*Bar_Life", 2);

	if (pCursorPos.x > 463 && pCursorPos.x < 483 && pCursorPos.y > 498 && pCursorPos.y < 595)
		cHelpPet.PetMessage("*Bar_Mana", 2);

	if (pCursorPos.x > 300 && pCursorPos.x < 313 && pCursorPos.y > 513 && pCursorPos.y < 595)
		cHelpPet.PetMessage("*Bar_Stamina", 2);

	if (pCursorPos.x > 483 && pCursorPos.x < 483 + 10 && pCursorPos.y > 513 && pCursorPos.y < 595)
		cHelpPet.PetMessage("*Bar_Exp", 2);

	if (pCursorPos.x > 500 && pCursorPos.x < 570 && pCursorPos.y > 540 && pCursorPos.y < 594)
		cHelpPet.PetMessage("*Exp_Num", 2);

	SkillMouseButtonPosi[1] = 1;
}
/*----------------------------------------------------------------------------*
*							   RButtonUp
*-----------------------------------------------------------------------------*/
void cINTERFACE::RButtonUp(int x, int y)
{

}
/*----------------------------------------------------------------------------*
*							    KeyDown
*-----------------------------------------------------------------------------*/
char InputSecretCode[256];
char sinBuff[256];
int  ResetQuset3Flag = 0;

void cINTERFACE::KeyDown()
{
	/////////////¾ÏÈ£¸¦ Áý¾î ³Ö´Â´Ù 
	if (hFocusWnd)
	{
		//cHelpPet.PetMessage("*ChatBox",3); ÀÏ´Ü Ã¤ÆÃÀº »«´Ù
		if (SETTINGHANDLE->Get().bDebugMode)
		{
			GetWindowText(hFocusWnd, InputSecretCode, 90);
			if (InputSecretCode[0])
			{
				if (InputSecretCode[0] == '/')
				{
					memset(sinBuff, 0, sizeof(sinBuff));
					wsprintf(sinBuff, "%s", InputSecretCode);
				}
			}
		}
	}
	if (VRKeyBuff[VK_CONTROL])
	{

	}
	else
		sinPKWarningExpFlag = 0;
}
int DefaultLength[4] = { 94,94,76,221 };
float sinOldNowState[4] = { 0,0,0,0 };
float sinOldMaxState[4] = { 0,0,0,0 };

void cINTERFACE::InitState()
{
	float sinTemp;
	float sinMaxState[4] = { (float)sinChar->sHP.sMax,(float)sinChar->sMP.sMax ,(float)sinChar->sSP.sMax };
	float sinNowState[4] = { (float)sinGetLife(),(float)sinGetMana() ,(float)sinGetStamina() };

	for (int i = 0; i < 3; i++)
	{
		if (sinMaxState[i])
			sinTemp = (sinNowState[i] / sinMaxState[i]) * 100;
		else
			sinTemp = 0;

		sinBmpLength[i] = (int)((DefaultLength[i] * (sinTemp / 100)));
		sinOldNowState[i] = sinNowState[i];

	}

	if (sinChar->iLevel < 79)
	{
		sinMaxState[3] = (float)(uUnitExpTables[sinChar->iLevel] - uUnitExpTables[sinChar->iLevel - 1]);
		sinNowState[3] = (float)((GAMEUNIT->GetExp(lpCurPlayer)) - uUnitExpTables[sinChar->iLevel - 1]);
	}
	else
	{
		sinMaxState[3] = (float)((uUnitExpTables[sinChar->iLevel] - uUnitExpTables[sinChar->iLevel - 1]) / 1000000);
		sinNowState[3] = (float)(((GAMEUNIT->GetExp(lpCurPlayer)) - uUnitExpTables[sinChar->iLevel - 1]) / 1000000);
	}

	InitStateFlag = 1;

}

void cINTERFACE::CheckingState()
{

	float	sinTemp;
	float sinMaxState[4] = { (float)(sinChar->sHP.sMax),(float)sinChar->sMP.sMax ,(float)sinChar->sSP.sMax };
	float sinNowState[4] = { (float)sinGetLife(),(float)sinGetMana() ,(float)sinGetStamina() };

	if (sinChar->iLevel < 79)
	{
		sinMaxState[3] = (float)(uUnitExpTables[sinChar->iLevel] - uUnitExpTables[sinChar->iLevel - 1]);
		sinNowState[3] = (float)((GAMEUNIT->GetExp(lpCurPlayer)) - uUnitExpTables[sinChar->iLevel - 1]);
	}
	else
	{
		sinMaxState[3] = (float)((uUnitExpTables[sinChar->iLevel] - uUnitExpTables[sinChar->iLevel - 1]) / 1000000);
		sinNowState[3] = (float)(((GAMEUNIT->GetExp(lpCurPlayer)) - uUnitExpTables[sinChar->iLevel - 1]) / 1000000);
	}

	for (int i = 0; i < 4; i++) {
		if (sinOldNowState[i] != sinNowState[i] || sinOldNowState[i] != sinMaxState[i])
		{
			if (sinOldNowState[i] != sinNowState[i])
			{
				sinTemp = ((sinNowState[i]) / sinMaxState[i]) * 100;
				sinBmpLength[i] = (int)((DefaultLength[i] * (sinTemp / 100)));
				if (sinBmpLength[i] > DefaultLength[i])sinBmpLength[i] = DefaultLength[i];
				sinOldNowState[i] = sinNowState[i];
			}
		}
	}
}

//ÉúÃü Ä§·¨ Ãæ°å
void cINTERFACE::ShowParaState()
{
	InfoMessageBoxPos.x = 0;
	InfoMessageBoxPos.y = 0;

	szInfoMsgBuff5[0] = 0;
	lstrcpy(szInfoMsgBuff5, "");

	DayNightFlag = FALSE;

	//ÉúÃüÌõ
	if (pCursorPos.x > 315 && pCursorPos.x < 337 && pCursorPos.y > 500 && pCursorPos.y < 594)
	{
		if (AddVirtualLife[1])
			AddVirtualLife[0] = (int)((float)sinGetLife() * ((float)sinVirtualLifePercent / 100.f));

		cHelpPet.PetMessage("*Bar_Life", 0);
		wsprintf(szInfoMsgBuff5, "Health: %d/%d", (int)sinGetLife() + AddVirtualLife[0], (int)sinChar->sHP.sMax + AddVirtualLife[1]);
		InfoMessageBoxPos.x = 343;
		InfoMessageBoxPos.y = 500;

	}
	//Ä§·¨Ìõ
	if (pCursorPos.x > 463 && pCursorPos.x < 483 && pCursorPos.y > 498 && pCursorPos.y < 595)
	{
		if (AddVirtualMana[1])
			AddVirtualMana[0] = (int)((float)sinGetMana() * ((float)sinVirtualManaPercent / 100.f));

		wsprintf(szInfoMsgBuff5, "Mana: %d/%d", (int)sinGetMana(), (int)sinChar->sMP.sMax);
		cHelpPet.PetMessage("*Bar_Mana", 0);
		InfoMessageBoxPos.x = 490;
		InfoMessageBoxPos.y = 498;

	}
	//ÄÍÁ¦Ìõ
	if (pCursorPos.x > 300 && pCursorPos.x < 313 && pCursorPos.y > 513 && pCursorPos.y < 595)
	{
		if (AddVirtualStamina[1])
			AddVirtualStamina[0] = (int)((float)sinGetStamina() * ((float)sinVirtualStaminaPercent / 100.f));

		cHelpPet.PetMessage("*Bar_Stamina", 0);

		wsprintf(szInfoMsgBuff5, "Stamina: %d/%d", (int)sinGetStamina(), (int)sinChar->sSP.sMax);
		InfoMessageBoxPos.x = 320;
		InfoMessageBoxPos.y = 513;
	}
	//¾­ÑéÌõ
	if (pCursorPos.x > 570 && pCursorPos.x < 800 && pCursorPos.y > 590 && pCursorPos.y < 600)
		cHelpPet.PetMessage("*Bar_Exp", 0);

	//¾­Ñé°Ù·Ö±È
	if (pCursorPos.x > 500 && pCursorPos.x < 570 && pCursorPos.y > 590 && pCursorPos.y < 600)
		cHelpPet.PetMessage("*Exp_Num", 0);

	if (pCursorPos.x > 360 && pCursorPos.x < 430 && pCursorPos.y > 590 && pCursorPos.y < 600)
		DayNightFlag = TRUE;
}

//äÖÈ¾Ãæ°å×ÖÌå
void cINTERFACE::DrawInterText()
{
	DWORD Color = D3DCOLOR_XRGB(255, 255, 255);

	if (InfoMessageBoxPos.x != 0 || InfoMessageBoxPos.y != 0)
		dsTextLineOut(0, InfoMessageBoxPos.x, InfoMessageBoxPos.y, szInfoMsgBuff5, lstrlen(szInfoMsgBuff5), Color);
	if (ShowExpPercentFlag)
	{
		dsDrawOffsetArray = dsARRAY_BOTTOM;
		dsTextLineOut(0, 520, 590, szInfoMsgBuff6, lstrlen(szInfoMsgBuff6), D3DCOLOR_XRGB(202, 254, 251));
		dsDrawOffsetArray = dsARRAY_TOP;
	}
	if (SkillNpcFlag)
	{
		if (szSkillMasterMsg[0])
			dsTextLineOut(0, SkillMasterTextXY.x, SkillMasterTextXY.y + 2, szSkillMasterMsg, lstrlen(szSkillMasterMsg), Color);
		if (szReStartMsg2[0])
			dsTextLineOut(0, SkillMasterTextXY.x, SkillMasterTextXY.y + 18, szSkillMasterMsg2, lstrlen(szSkillMasterMsg2), Color);
	}
}

void cINTERFACE::CheckAllBox(int ButtonFlag)
{
	int i = 0;
	for (i = 0; i < SIN_MAX_HELP_NUMBER; i++)
	{
		if (sSinHelp[i].KindFlag)
		{
			if ((ButtonFlag == SIN_CRAFTITEM || ButtonFlag == SIN_AGING || ButtonFlag == SIN_SMELTING || ButtonFlag == SIN_MANUFACTURE))
				return;
		}
		if (sSinHelp[i].KindFlag == SIN_HELP_KIND_TELEPORT_SCROLL)
		{
			if (cTrade.OpenFlag)
			{
				SendRequestTrade(cTrade.TradeCharCode, 3);
				cTrade.CancelTradeItem();
			}
			if ((ButtonFlag == SIN_MYSHOP || ButtonFlag == SIN_TRADE))
				return;
		}
	}
	if (cWareHouse.OpenFlag)
	{
		if (ButtonFlag == SIN_TRADE || ButtonFlag == SIN_SHOP || ButtonFlag == SIN_CRAFTITEM || ButtonFlag == SIN_AGING || ButtonFlag == SIN_MYSHOP || ButtonFlag == SIN_CHARSHOP || ButtonFlag == SIN_SMELTING || ButtonFlag == SIN_MANUFACTURE || ButtonFlag == SIN_ELEMENT || ButtonFlag == SIN_CARAVAN)
			return;
	}
	if (MyShopSendButton || cMyShop.OpenFlag || cCharShop.OpenFlag)
	{
		if (ButtonFlag == SIN_TRADE || ButtonFlag == SIN_SHOP || ButtonFlag == SIN_WAREHOUSE || ButtonFlag == SIN_CRAFTITEM || ButtonFlag == SIN_AGING || ButtonFlag == SIN_CHARSHOP || ButtonFlag == SIN_SMELTING || ButtonFlag == SIN_MANUFACTURE || ButtonFlag == SIN_ELEMENT || ButtonFlag == SIN_CARAVAN)
			return;

	}
	if (cShop.OpenFlag || cCraftItem.OpenFlag || cAging.OpenFlag || cTrade.OpenFlag || cCharShop.OpenFlag || SmeltingItem.OpenFlag || ManufactureItem.m_OpenFlag || cMixtureReset.OpenFlag || cElement.OpenFlag || cCaravan.OpenFlag || cSocket.OpenFlag)
	{
		if (ButtonFlag == SIN_MYSHOP || ButtonFlag == SIN_CHARSHOP)
			return;

	}
	if (cShop.OpenFlag || cCraftItem.OpenFlag || cAging.OpenFlag || cTrade.OpenFlag || cMyShop.OpenFlag || cCharShop.OpenFlag || SmeltingItem.OpenFlag || ManufactureItem.m_OpenFlag)
	{
		if (ButtonFlag == SIN_CHARSHOP)
			return;
	}
	switch (ButtonFlag)
	{
	case SIN_CHARSTATUS:
		if (cInvenTory.OpenFlag)
			cInvenTory.OpenFlag = SIN_CLOSE;
		if (cSkill.OpenFlag)
			cSkill.OpenFlag = SIN_CLOSE;
		ExitButtonClick = 0;
		break;
	case SIN_SKILL:
		if (cCharStatus.OpenFlag)
			cCharStatus.OpenFlag = SIN_CLOSE;
		if (cInvenTory.OpenFlag)
			cInvenTory.OpenFlag = SIN_CLOSE;
		ExitButtonClick = 0;
		break;
	case SIN_INVENTORY:
		if (cCharStatus.OpenFlag)
			cCharStatus.OpenFlag = SIN_CLOSE;
		if (cSkill.OpenFlag)
			cSkill.OpenFlag = SIN_CLOSE;
		ExitButtonClick = 0;
		break;
	case SIN_TRADE:
		if (cCaravan.OpenFlag)
			cCaravan.OpenFlag = SIN_CLOSE;
		if (cElement.OpenFlag)
			cElement.OpenFlag = SIN_CLOSE;
		if (cSocket.OpenFlag)
			cSocket.OpenFlag = SIN_CLOSE;
		if (cMixtureReset.OpenFlag)
			cMixtureReset.OpenFlag = SIN_CLOSE;
		if (cAging.OpenFlag)
			cAging.OpenFlag = SIN_CLOSE;
		if (cCraftItem.OpenFlag)
			cCraftItem.OpenFlag = SIN_CLOSE;
		if (cShop.OpenFlag)
			cShop.OpenFlag = SIN_CLOSE;
		if (cWareHouse.OpenFlag)
			cWareHouse.OpenFlag = SIN_CLOSE;
		if (cCharStatus.OpenFlag)
			cCharStatus.OpenFlag = SIN_CLOSE;
		if (!cInvenTory.OpenFlag)
			cInvenTory.OpenFlag = SIN_OPEN;
		if (cSkill.OpenFlag)
			cSkill.OpenFlag = SIN_CLOSE;
		if (SmeltingItem.OpenFlag)
			SmeltingItem.OpenFlag = SIN_CLOSE;
		if (ManufactureItem.m_OpenFlag)
			ManufactureItem.m_OpenFlag = SIN_CLOSE;
		cTrade.ReFormTradeItem();
		cInvenTory.ChangeSpecialItem(2);
		break;

	case SIN_SHOP:
		if (cCaravan.OpenFlag)
			cCaravan.OpenFlag = SIN_CLOSE;
		if (cElement.OpenFlag)
			cElement.OpenFlag = SIN_CLOSE;
		if (cSocket.OpenFlag)
			cSocket.OpenFlag = SIN_CLOSE;
		if (cMixtureReset.OpenFlag)
			cMixtureReset.OpenFlag = SIN_CLOSE;
		if (cAging.OpenFlag)
			cAging.OpenFlag = SIN_CLOSE;
		if (cCraftItem.OpenFlag)
			cCraftItem.OpenFlag = SIN_CLOSE;
		if (cTrade.OpenFlag)
			cTrade.OpenFlag = SIN_CLOSE;
		if (cWareHouse.OpenFlag)
			cWareHouse.OpenFlag = SIN_CLOSE;
		if (cSkill.OpenFlag)
			cSkill.OpenFlag = SIN_CLOSE;
		if (cCharStatus.OpenFlag)
			cCharStatus.OpenFlag = SIN_CLOSE;
		if (SmeltingItem.OpenFlag)
			SmeltingItem.OpenFlag = SIN_CLOSE;
		if (ManufactureItem.m_OpenFlag)
			ManufactureItem.m_OpenFlag = SIN_CLOSE;
		if (!cInvenTory.OpenFlag)
			cInvenTory.OpenFlag = SIN_OPEN;
		if (!cShop.OpenFlag)
			cShop.OpenFlag = SIN_OPEN;
		cInvenTory.ChangeSpecialItem(2);

		break;

	case SIN_SYSTEM:
		if (cInvenTory.OpenFlag)
			cInvenTory.OpenFlag = SIN_CLOSE;
		if (cSkill.OpenFlag)
			cSkill.OpenFlag = SIN_CLOSE;
		if (cCharStatus.OpenFlag)
			cCharStatus.OpenFlag = SIN_CLOSE;
		break;
	case SIN_ALL_CLOSE:
		if (cTrade.OpenFlag)
			break;
		if (cInvenTory.OpenFlag)
			cInvenTory.OpenFlag = SIN_CLOSE;
		if (cSkill.OpenFlag)
			cSkill.OpenFlag = SIN_CLOSE;
		if (cCharStatus.OpenFlag)
			cCharStatus.OpenFlag = SIN_CLOSE;
		if (cShop.OpenFlag)
			cShop.OpenFlag = SIN_CLOSE;
		if (cTrade.OpenFlag)
			cTrade.OpenFlag = SIN_CLOSE;
		ExitButtonClick = 0;
		break;
	case SIN_WAREHOUSE:
		if (g_IsDxProjectZoomIn)
			break;
		if (cCaravan.OpenFlag)
			cCaravan.OpenFlag = SIN_CLOSE;
		if (cElement.OpenFlag)
			cElement.OpenFlag = SIN_CLOSE;
		if (cSocket.OpenFlag)
			cSocket.OpenFlag = SIN_CLOSE;
		if (cMixtureReset.OpenFlag)
			cMixtureReset.OpenFlag = SIN_CLOSE;
		if (cTrade.OpenFlag)
			cTrade.OpenFlag = SIN_CLOSE;
		if (cShop.OpenFlag)
			cShop.OpenFlag = SIN_CLOSE;
		if (cSkill.OpenFlag)
			cSkill.OpenFlag = SIN_CLOSE;
		if (cAging.OpenFlag)
			cAging.OpenFlag = SIN_CLOSE;
		if (cCraftItem.OpenFlag)
			cCraftItem.OpenFlag = SIN_CLOSE;
		if (cCharStatus.OpenFlag)
			cCharStatus.OpenFlag = SIN_CLOSE;
		if (!cInvenTory.OpenFlag)
			cInvenTory.OpenFlag = SIN_OPEN;
		if (!cWareHouse.OpenFlag)
			cWareHouse.OpenFlag = SIN_OPEN;
		if (SmeltingItem.OpenFlag)
			SmeltingItem.OpenFlag = SIN_CLOSE;
		if (ManufactureItem.m_OpenFlag)
			ManufactureItem.m_OpenFlag = SIN_CLOSE;
		cWareHouse.ReFormWareHouse();
		cWareHouse.CheckCopyItem();
		cWareHouse.DeleteCopyItem();
		cInvenTory.ChangeSpecialItem(2);
		break;

	case SIN_CRAFTITEM:
		if (cCaravan.OpenFlag)
			cCaravan.OpenFlag = SIN_CLOSE;
		if (cElement.OpenFlag)
			cElement.OpenFlag = SIN_CLOSE;
		if (cSocket.OpenFlag)
			cSocket.OpenFlag = SIN_CLOSE;
		if (cMixtureReset.OpenFlag)
			cMixtureReset.OpenFlag = SIN_CLOSE;
		if (cTrade.OpenFlag)
			cTrade.OpenFlag = SIN_CLOSE;
		if (cShop.OpenFlag)
			cShop.OpenFlag = SIN_CLOSE;
		if (cSkill.OpenFlag)
			cSkill.OpenFlag = SIN_CLOSE;
		if (cAging.OpenFlag)
			cAging.OpenFlag = SIN_CLOSE;
		if (cWareHouse.OpenFlag)
			cWareHouse.OpenFlag = SIN_CLOSE;
		if (cCharStatus.OpenFlag)
			cCharStatus.OpenFlag = SIN_CLOSE;
		if (!cInvenTory.OpenFlag)
			cInvenTory.OpenFlag = SIN_OPEN;
		if (!cCraftItem.OpenFlag)
			cCraftItem.OpenFlag = SIN_OPEN;
		if (SmeltingItem.OpenFlag)
			SmeltingItem.OpenFlag = SIN_CLOSE;
		if (ManufactureItem.m_OpenFlag)
			ManufactureItem.m_OpenFlag = SIN_CLOSE;
		cCraftItem.ReFormCraftItem();
		cInvenTory.ChangeSpecialItem(2);
		break;
	case SIN_AGING:
		if (cCaravan.OpenFlag)
			cCaravan.OpenFlag = SIN_CLOSE;
		if (cElement.OpenFlag)
			cElement.OpenFlag = SIN_CLOSE;
		if (cSocket.OpenFlag)
			cSocket.OpenFlag = SIN_CLOSE;
		if (cMixtureReset.OpenFlag)
			cMixtureReset.OpenFlag = SIN_CLOSE;
		if (cTrade.OpenFlag)
			cTrade.OpenFlag = SIN_CLOSE;
		if (cShop.OpenFlag)
			cShop.OpenFlag = SIN_CLOSE;
		if (cSkill.OpenFlag)
			cSkill.OpenFlag = SIN_CLOSE;
		if (cCraftItem.OpenFlag)
			cCraftItem.OpenFlag = SIN_CLOSE;
		if (cWareHouse.OpenFlag)
			cWareHouse.OpenFlag = SIN_CLOSE;
		if (cCharStatus.OpenFlag)
			cCharStatus.OpenFlag = SIN_CLOSE;
		if (!cInvenTory.OpenFlag)
			cInvenTory.OpenFlag = SIN_OPEN;
		if (!cAging.OpenFlag)
			cAging.OpenFlag = SIN_OPEN;
		if (SmeltingItem.OpenFlag)
			SmeltingItem.OpenFlag = SIN_CLOSE;
		if (ManufactureItem.m_OpenFlag)
			ManufactureItem.m_OpenFlag = SIN_CLOSE;
		cInvenTory.ChangeSpecialItem(2);

		break;
	case SIN_MIXTURE_RESET:
		if (cCaravan.OpenFlag)
			cCaravan.OpenFlag = SIN_CLOSE;
		if (cElement.OpenFlag)
			cElement.OpenFlag = SIN_CLOSE;
		if (cSocket.OpenFlag)
			cSocket.OpenFlag = SIN_CLOSE;
		if (cTrade.OpenFlag)
			cTrade.OpenFlag = SIN_CLOSE;
		if (cShop.OpenFlag)
			cShop.OpenFlag = SIN_CLOSE;
		if (cSkill.OpenFlag)
			cSkill.OpenFlag = SIN_CLOSE;
		if (cCraftItem.OpenFlag)
			cCraftItem.OpenFlag = SIN_CLOSE;
		if (cWareHouse.OpenFlag)
			cWareHouse.OpenFlag = SIN_CLOSE;
		if (cCharStatus.OpenFlag)
			cCharStatus.OpenFlag = SIN_CLOSE;
		if (cAging.OpenFlag)
			cAging.OpenFlag = SIN_CLOSE;
		if (SmeltingItem.OpenFlag)
			SmeltingItem.OpenFlag = SIN_CLOSE;
		if (ManufactureItem.m_OpenFlag)
			ManufactureItem.m_OpenFlag = SIN_CLOSE;
		if (!cInvenTory.OpenFlag)
			cInvenTory.OpenFlag = SIN_OPEN;
		if (!cMixtureReset.OpenFlag)
			cMixtureReset.OpenFlag = SIN_OPEN;

		cInvenTory.ChangeSpecialItem(2);
		break;
	case SIN_SMELTING:
		if (cCaravan.OpenFlag)
			cCaravan.OpenFlag = SIN_CLOSE;
		if (cElement.OpenFlag)
			cElement.OpenFlag = SIN_CLOSE;
		if (cSocket.OpenFlag)
			cSocket.OpenFlag = SIN_CLOSE;
		if (cMixtureReset.OpenFlag)
			cMixtureReset.OpenFlag = SIN_CLOSE;
		if (cTrade.OpenFlag)
			cTrade.OpenFlag = SIN_CLOSE;
		if (cShop.OpenFlag)
			cShop.OpenFlag = SIN_CLOSE;
		if (cSkill.OpenFlag)
			cSkill.OpenFlag = SIN_CLOSE;
		if (cCraftItem.OpenFlag)
			cCraftItem.OpenFlag = SIN_CLOSE;
		if (cWareHouse.OpenFlag)
			cWareHouse.OpenFlag = SIN_CLOSE;
		if (cCharStatus.OpenFlag)
			cCharStatus.OpenFlag = SIN_CLOSE;
		if (cAging.OpenFlag)
			cAging.OpenFlag = SIN_CLOSE;
		if (ManufactureItem.m_OpenFlag)
			ManufactureItem.m_OpenFlag = SIN_CLOSE;
		if (!cInvenTory.OpenFlag)
			cInvenTory.OpenFlag = SIN_OPEN;
		if (!SmeltingItem.OpenFlag)
			SmeltingItem.OpenFlag = SIN_OPEN;
		cInvenTory.ChangeSpecialItem(2);
		break;
	case SIN_MANUFACTURE:
		if (cCaravan.OpenFlag)
			cCaravan.OpenFlag = SIN_CLOSE;
		if (cElement.OpenFlag)
			cElement.OpenFlag = SIN_CLOSE;
		if (cSocket.OpenFlag)
			cSocket.OpenFlag = SIN_CLOSE;
		if (cMixtureReset.OpenFlag)
			cMixtureReset.OpenFlag = SIN_CLOSE;
		if (cTrade.OpenFlag)
			cTrade.OpenFlag = SIN_CLOSE;
		if (cShop.OpenFlag)
			cShop.OpenFlag = SIN_CLOSE;
		if (cSkill.OpenFlag)
			cSkill.OpenFlag = SIN_CLOSE;
		if (cCraftItem.OpenFlag)
			cCraftItem.OpenFlag = SIN_CLOSE;
		if (cWareHouse.OpenFlag)
			cWareHouse.OpenFlag = SIN_CLOSE;
		if (cCharStatus.OpenFlag)
			cCharStatus.OpenFlag = SIN_CLOSE;
		if (cAging.OpenFlag)
			cAging.OpenFlag = SIN_CLOSE;
		if (SmeltingItem.OpenFlag)
			SmeltingItem.OpenFlag = SIN_CLOSE;
		if (!cInvenTory.OpenFlag)
			cInvenTory.OpenFlag = SIN_OPEN;
		if (!ManufactureItem.m_OpenFlag)
		{
			ManufactureItem.m_OpenFlag = SIN_OPEN;
			if (!g_Manufacture_ItemInfo[0].ItemCode)
			{
				smTRANS_COMMAND	TransCommand;
				TransCommand.code = smTRANSCODE_MANUFACTURE_WEIGHT_PRICE;
				TransCommand.size = sizeof(smTRANS_COMMAND);
				TransCommand.WParam = 0;
				TransCommand.LParam = 0;
				TransCommand.SParam = 0;

				SENDPACKETG(&TransCommand);
			}
		}
		cInvenTory.ChangeSpecialItem(2);
		break;
	case SIN_ELEMENT:
		if (cCaravan.OpenFlag)
			cCaravan.OpenFlag = SIN_CLOSE;
		if (cMixtureReset.OpenFlag)
			cMixtureReset.OpenFlag = SIN_CLOSE;
		if (cTrade.OpenFlag)
			cTrade.OpenFlag = SIN_CLOSE;
		if (cSocket.OpenFlag)
			cSocket.OpenFlag = SIN_CLOSE;
		if (cShop.OpenFlag)
			cShop.OpenFlag = SIN_CLOSE;
		if (cSkill.OpenFlag)
			cSkill.OpenFlag = SIN_CLOSE;
		if (cCraftItem.OpenFlag)
			cCraftItem.OpenFlag = SIN_CLOSE;
		if (cWareHouse.OpenFlag)
			cWareHouse.OpenFlag = SIN_CLOSE;
		if (cCharStatus.OpenFlag)
			cCharStatus.OpenFlag = SIN_CLOSE;
		if (cAging.OpenFlag)
			cAging.OpenFlag = SIN_CLOSE;
		if (SmeltingItem.OpenFlag)
			SmeltingItem.OpenFlag = SIN_CLOSE;
		if (ManufactureItem.m_OpenFlag)
			ManufactureItem.m_OpenFlag = SIN_CLOSE;
		if (!cInvenTory.OpenFlag)
			cInvenTory.OpenFlag = SIN_OPEN;
		if (!cElement.OpenFlag)
			cElement.OpenFlag = SIN_OPEN;
		cInvenTory.ChangeSpecialItem(2);
		break;
	case SIN_SOCKET:
		if (cCaravan.OpenFlag)
			cCaravan.OpenFlag = SIN_CLOSE;
		if (cMixtureReset.OpenFlag)
			cMixtureReset.OpenFlag = SIN_CLOSE;
		if (cTrade.OpenFlag)
			cTrade.OpenFlag = SIN_CLOSE;
		if (cElement.OpenFlag)
			cElement.OpenFlag = SIN_CLOSE;
		if (cShop.OpenFlag)
			cShop.OpenFlag = SIN_CLOSE;
		if (cSkill.OpenFlag)
			cSkill.OpenFlag = SIN_CLOSE;
		if (cCraftItem.OpenFlag)
			cCraftItem.OpenFlag = SIN_CLOSE;
		if (cWareHouse.OpenFlag)
			cWareHouse.OpenFlag = SIN_CLOSE;
		if (cCharStatus.OpenFlag)
			cCharStatus.OpenFlag = SIN_CLOSE;
		if (cAging.OpenFlag)
			cAging.OpenFlag = SIN_CLOSE;
		if (SmeltingItem.OpenFlag)
			SmeltingItem.OpenFlag = SIN_CLOSE;
		if (ManufactureItem.m_OpenFlag)
			ManufactureItem.m_OpenFlag = SIN_CLOSE;
		if (!cInvenTory.OpenFlag)
			cInvenTory.OpenFlag = SIN_OPEN;
		if (!cSocket.OpenFlag)
			cSocket.OpenFlag = SIN_OPEN;
		cInvenTory.ChangeSpecialItem(2);
		break;
	case SIN_CARAVAN:
		if (cElement.OpenFlag)
			cElement.OpenFlag = SIN_CLOSE;
		if (cSocket.OpenFlag)
			cSocket.OpenFlag = SIN_CLOSE;
		if (cMixtureReset.OpenFlag)
			cMixtureReset.OpenFlag = SIN_CLOSE;
		if (cTrade.OpenFlag)
			cTrade.OpenFlag = SIN_CLOSE;
		if (cShop.OpenFlag)
			cShop.OpenFlag = SIN_CLOSE;
		if (cSkill.OpenFlag)
			cSkill.OpenFlag = SIN_CLOSE;
		if (cAging.OpenFlag)
			cAging.OpenFlag = SIN_CLOSE;
		if (cCraftItem.OpenFlag)
			cCraftItem.OpenFlag = SIN_CLOSE;
		if (cCharStatus.OpenFlag)
			cCharStatus.OpenFlag = SIN_CLOSE;
		if (!cInvenTory.OpenFlag)
			cInvenTory.OpenFlag = SIN_OPEN;
		if (!cCaravan.OpenFlag)
			cCaravan.OpenFlag = SIN_OPEN;
		if (cWareHouse.OpenFlag)
			cWareHouse.OpenFlag = SIN_CLOSE;
		if (SmeltingItem.OpenFlag)
			SmeltingItem.OpenFlag = SIN_CLOSE;
		if (ManufactureItem.m_OpenFlag)
			ManufactureItem.m_OpenFlag = SIN_CLOSE;
		cCaravan.ReFormCaravan();
		cCaravan.CheckCopyItem();
		cCaravan.DeleteCopyItem();
		cInvenTory.ChangeSpecialItem(2);
		break;
	case SIN_MYSHOP:
		if (lpCurPlayer->iLoadedMapIndex >= 0 &&
			STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_Town)
		{
			if (cElement.OpenFlag)
				cElement.OpenFlag = SIN_CLOSE;
			if (cSocket.OpenFlag)
				cSocket.OpenFlag = SIN_CLOSE;
			if (cMixtureReset.OpenFlag)
				cMixtureReset.OpenFlag = SIN_CLOSE;
			if (cTrade.OpenFlag)
				cTrade.OpenFlag = SIN_CLOSE;
			if (cShop.OpenFlag)
				cShop.OpenFlag = SIN_CLOSE;
			if (cSkill.OpenFlag)
				cSkill.OpenFlag = SIN_CLOSE;
			if (cAging.OpenFlag)
				cAging.OpenFlag = SIN_CLOSE;
			if (cCraftItem.OpenFlag)
				cCraftItem.OpenFlag = SIN_CLOSE;
			if (cCharStatus.OpenFlag)
				cCharStatus.OpenFlag = SIN_CLOSE;
			if (SmeltingItem.OpenFlag)
				SmeltingItem.OpenFlag = SIN_CLOSE;
			if (ManufactureItem.m_OpenFlag)
				ManufactureItem.m_OpenFlag = SIN_CLOSE;
			if (cCharShop.OpenFlag)
			{
				cCharShop.OpenFlag = 0;
				memset(cCharShop.CharShopItem, 0, sizeof(ItemData) * 30);
			}
			if (!cInvenTory.OpenFlag)
				cInvenTory.OpenFlag = SIN_OPEN;
			if (!cMyShop.OpenFlag)
				cMyShop.OpenFlag = SIN_OPEN;
			cInvenTory.ChangeSpecialItem(2);
		}
		break;
	case SIN_CHARSHOP:
		if (lpCurPlayer->iLoadedMapIndex >= 0 &&
			STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapType == MAPTYPE_Town)
		{
			if (cElement.OpenFlag)
				cElement.OpenFlag = SIN_CLOSE;
			if (cSocket.OpenFlag)
				cSocket.OpenFlag = SIN_CLOSE;
			if (cMixtureReset.OpenFlag)
				cMixtureReset.OpenFlag = SIN_CLOSE;
			if (cTrade.OpenFlag)
				cTrade.OpenFlag = SIN_CLOSE;
			if (cShop.OpenFlag)
				cShop.OpenFlag = SIN_CLOSE;
			if (cSkill.OpenFlag)
				cSkill.OpenFlag = SIN_CLOSE;
			if (cAging.OpenFlag)
				cAging.OpenFlag = SIN_CLOSE;
			if (cCraftItem.OpenFlag)
				cCraftItem.OpenFlag = SIN_CLOSE;
			if (cCharStatus.OpenFlag)
				cCharStatus.OpenFlag = SIN_CLOSE;
			if (SmeltingItem.OpenFlag)
				SmeltingItem.OpenFlag = SIN_CLOSE;
			if (ManufactureItem.m_OpenFlag)
				ManufactureItem.m_OpenFlag = SIN_CLOSE;
			if (cMyShop.OpenFlag)
			{
				cMyShop.OpenFlag = SIN_CLOSE;
				cMyShop.OpenFlag = 0;
				memset(cMyShop.MyShopItem, 0, sizeof(ItemData) * 30);
				memset(MyShopItemIndex, 0, sizeof(int) * 100);
				MyShopSendButton = 0;
			}
			if (!cInvenTory.OpenFlag)
				cInvenTory.OpenFlag = SIN_OPEN;
			if (!cCharShop.OpenFlag)
				cCharShop.OpenFlag = SIN_OPEN;
			cInvenTory.ChangeSpecialItem(2);
		}
		break;
	}
}
int cINTERFACE::GetWordTimeDisplay()
{
	float TempfHour = (float)GAMEMAP->GetGameHour();

	if (TempfHour >= 23 || TempfHour < 4)
		DayOrNightFlag = 2;
	else
		DayOrNightFlag = 1;

	if (DayOrNightFlag == 1)
		sinGageTime2 = (int)(50.0f*((TempfHour - 4.0f) / 19.0f));
	else
		sinGageTime2 = (int)(50.0f*((TempfHour + 1) / 5.0f));

	if (sinGageTime2 > 50)
		sinGageTime2 = 50;

	return TRUE;
}
void cINTERFACE::ShowExpPercent()
{
	ShowExpPercentFlag = 1;

	int ExpPercent = 0;
	int ExpPercentSpot = 0;
	int ExpSize = 0;
	int ExpNowSize = 0;

	szInfoMsgBuff6[0] = 0;

	if (sinChar->iLevel > 79)
	{
		ExpSize = (int)((GetNextExp(sinChar->iLevel) - GetNextExp(sinChar->iLevel - 1)) / 1000000);
		ExpNowSize = (int)(cCharStatus.sinGetNowExp() - (GetNextExp(sinChar->iLevel - 1) / 1000000));
		ExpPercent = (int)(100000.0f / (float)ExpSize * (float)ExpNowSize);
		ExpPercentSpot = (int)(ExpPercent % 1000);
		ExpPercent = ExpPercent / 1000;

		if (ExpPercent >= 100)
		{
			ExpPercent = 99;
			ExpPercentSpot = 999;
		}

		if (ExpPercentSpot < 10)
			wsprintf(szInfoMsgBuff6, "%d.00%d%s", ExpPercent, ExpPercentSpot, "%  ");
		else if (ExpPercentSpot >= 10 && ExpPercentSpot < 100)
			wsprintf(szInfoMsgBuff6, "%d.0%d%s", ExpPercent, ExpPercentSpot, "%  ");
		else
			wsprintf(szInfoMsgBuff6, "%d.%d%s", ExpPercent, ExpPercentSpot, "%  ");
	}
	else
	{
		ExpSize = (int)GetNextExp(sinChar->iLevel) - (int)GetNextExp(sinChar->iLevel - 1);
		ExpNowSize = cCharStatus.sinGetNowExp() - (int)GetNextExp(sinChar->iLevel - 1);
		ExpPercent = (int)(100000.0f / (float)ExpSize * (float)ExpNowSize);
		ExpPercentSpot = (int)(ExpPercent % 1000);
		ExpPercent = ExpPercent / 1000;

		cHelpPet.PetExp = ExpPercent;

		if (ExpPercentSpot < 10)
			wsprintf(szInfoMsgBuff6, "%d.00%d%s", ExpPercent, ExpPercentSpot, "%  ");
		else if (ExpPercentSpot >= 10 && ExpPercentSpot < 100)
			wsprintf(szInfoMsgBuff6, "%d.0%d%s", ExpPercent, ExpPercentSpot, "%  ");
		else
			wsprintf(szInfoMsgBuff6, "%d.%d%s", ExpPercent, ExpPercentSpot, "%  ");
	}
}
int cINTERFACE::SetStringEffect(int Index)
{
	if (!HA_EffectIndex[Index])
	{
		HA_EffectIndex[Index] = CreateTextureMaterial(HaEffectFilePath[Index], 0, 0, 0, SMMAT_BLEND_ALPHA);
		ReadTextures();
	}

	for (int i = 0; i < MAX_HAEFFECTNUM; i++)
	{
		if (!HaEffect[i].Flag)
		{
			HaEffect[i].Flag = 1;
			HaEffect[i].Time = 0;
			HaEffect[i].Mat = HA_EffectIndex[Index];
			HaEffect[i].Posi.x = 354;
			HaEffect[i].Posi.y = 488;
			HaEffect[i].Size.x = 128;
			HaEffect[i].Size.y = 64;
			return true;
		}
	}
	return false;
}
