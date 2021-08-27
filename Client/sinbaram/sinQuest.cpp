#include "StdAfx.h"

sQUEST_CHANGEJOB	sinQuest_ChangeJob;	//ƒ˘Ω∫∆Æ¿« ¿¸π›¿˚¿Œ ≥ªøÎ¿ª ¥Ÿ∑È¥Ÿ (≈€Ω∫≈©∑–)
sQUEST_CHANGEJOB	sinQuest_ChangeJob2;//ƒ˘Ω∫∆Æ¿« ¿¸π›¿˚¿Œ ≥ªøÎ¿ª ¥Ÿ∑È¥Ÿ (∏∂Û¿Ãø¬)
sQUEST_CHANGEJOB3   sinQuest_ChangeJob3;//≈€Ω∫≈©∑– ∏∂Û¿Ãø¬ 3¬˜ ¿¸¡˜ƒ˘Ω∫∆Æ 
sQUEST_CHANGEJOB3   sinQuest_ChangeJob4;//≈€Ω∫≈©∑– ∏∂Û¿Ãø¬ 3¬˜ ¿¸¡˜ƒ˘Ω∫∆Æ 


sQUEST_CHANGEJOB3   sinQuest_Level30;
sQUEST_CHANGEJOB3   sinQuest_Level55;
sQUEST_CHANGEJOB3   sinQuest_Level55_2;
sQUEST_CHANGEJOB3   sinQuest_Level70;
sQUEST_CHANGEJOB3   sinQuest_Level80;
sQUEST_CHANGEJOB3   sinQuest_Level85;
sQUEST_CHANGEJOB3   sinQuest_Level90;

sQUEST_CHANGEJOB3   sinQuest_Level80_2; //ªı∑Œ√ﬂ∞°µ» Ω∫≈› +7ƒ˘Ω∫∆Æ
sQUEST_CHANGEJOB3   sinQuest_Level90_2; //ªı∑Œ√ﬂ∞°µ» Ω∫≈› +10ƒ˘Ω∫∆Æ

DWORD sinQuest_levelLog = 0; //»ŒŒÒMASK
WORD sinFruitStatus[2] = { 0 }; //π˚ µ Ù–‘

BYTE sinTempStatus[8] = { 0 }; //¡Ÿ ± Ù–‘µ„

ItemData TempQuestItem;

int Quest_Flag = 0;

int sinChangeJobButtonShow = 0; //≈€Ω∫≈©∑– ¿¸æ˜ 2¬˜¿¸æ˜
int sinChangeJobButtonShow2 = 0; //∏∂Û¿Ãø¬ ¿¸æ˜ 2¬˜¿¸æ˜
int sinChangeJobButtonShow3 = 0; //≈€Ω∫≈©∑– ∏∂Û¿Ãø¬ 3¬˜¿¸æ˜
int sinChangeJobButtonShow4 = 0; //≈€Ω∫≈©∑– ∏∂Û¿Ãø¬ 4¬˜¿¸æ˜

int CheckQuestComplete = 0;		 //¿¸æ˜¿« ¡¯«‡ªÁ«◊
int CheckQuestButtonShow1 = 0;
int CheckQuestButtonShow2 = 0;
int CheckQuestButtonShow3 = 0;

POINT QuestMessageBoxPosi2 = { 50,45 };
POINT QuestMessageBoxSize2 = { 9,10 };

//ƒ˘Ω∫∆Æ ∆ƒ¿œ¿« ∞Ê∑Œ 
char *QuestFilePath[] = {
	"image\\Sinimage\\Quest\\ChangeJob1.sin",
		"image\\Sinimage\\Quest\\ChangeJob2.sin",
		"image\\Sinimage\\Quest\\ChangeJob2M.sin",
		"image\\Sinimage\\Quest\\ChangeJob2M_M1.sin",
		"image\\Sinimage\\Quest\\ChangeJob2M_M2.sin",
		"image\\Sinimage\\Quest\\ChangeJob2M_M3.sin",
		"image\\Sinimage\\Quest\\ChangeJob2M_D1.sin",
		"image\\Sinimage\\Quest\\ChangeJob2M_D2.sin",
		"image\\Sinimage\\Quest\\ChangeJob2M_D3.sin",
		"image\\Sinimage\\Quest\\ChangeJob2M_Success.sin",
		"image\\Sinimage\\Quest\\ChangeJob2M_M0.sin",
		"image\\Sinimage\\Quest\\ChangeJob2M_D0.sin",
		"image\\Sinimage\\Quest\\ChangeJob1.sin",
};

char *QuestFilePath3[] = {
	"image\\Sinimage\\Quest\\ChangeJob3_0.sin",
		"image\\Sinimage\\Quest\\ChangeJob3_1.sin",
		"image\\Sinimage\\Quest\\ChangeJob3_2.sin",
		"image\\Sinimage\\Quest\\ChangeJob3_3.sin",
		"image\\Sinimage\\Quest\\ChangeJob3_4.sin",
		"image\\Sinimage\\Quest\\ChangeJob3_5.sin",
};


char *WingQuestFilePath_a[] = {
	"image\\Sinimage\\Quest\\M_Wing_a.sin",
		"image\\Sinimage\\Quest\\S_Wing_a.sin",
		"image\\Sinimage\\Quest\\G_Wing_a.sin",
		"image\\Sinimage\\Quest\\D_Wing_a.sin",
		"image\\Sinimage\\Quest\\K_wing_a.sin", //ƒ…¿Ãæ∆Ω∫¿Æ
		"image\\Sinimage\\Quest\\E_wing_a.sin", //¿ÕΩ∫∆Æ∏≤¿Æ ∑ŒΩ∫∆Æ æ∆¿œ∑£µÂ (º∫±Ÿ√ﬂ∞°)
		"image\\Sinimage\\Quest\\Puzzle.sin",   //æÍ¥¬ ∆€¡Ò ~~~ ∞«µÈ¡ˆ ∏∂ººø∞ -0-

};

char *WingQuestFilePath_b[] = {
	"image\\Sinimage\\Quest\\M_Wing_b.sin",
		"image\\Sinimage\\Quest\\S_Wing_b.sin",
		"image\\Sinimage\\Quest\\G_Wing_b.sin",
		"image\\Sinimage\\Quest\\D_Wing_b.sin",
		"image\\Sinimage\\Quest\\K_wing_b.sin", //ƒ…¿Ãæ∆Ω∫¿Æ
		"image\\Sinimage\\Quest\\E_wing_b.sin", //¿ÕΩ∫∆Æ∏≤¿Æ ∑ŒΩ∫∆Æ æ∆¿œ∑£µÂ (º∫±Ÿ√ﬂ∞°)
		"image\\Sinimage\\Quest\\Wing_End.sin",

};

char *WarpGateDoc[] = {
	"image\\Sinimage\\WarpGateDoc\\Default.sin",
		"image\\Sinimage\\WarpGateDoc\\Ricarten.sin",
		"image\\Sinimage\\WarpGateDoc\\Pilai.sin",
		"image\\Sinimage\\WarpGateDoc\\Forest2.sin",
		"image\\Sinimage\\WarpGateDoc\\Forest3.sin",
		"image\\Sinimage\\WarpGateDoc\\Ruinen.sin",
		"image\\Sinimage\\WarpGateDoc\\Nevisco.sin",
		"image\\Sinimage\\WarpGateDoc\\Desert4.sin",
		"image\\Sinimage\\WarpGateDoc\\yura.sin",
		"image\\Sinimage\\WarpGateDoc\\chaoticpost.sin",	//∑ŒΩ∫∆Æ æ∆¿œ∑£µÂ (º∫±Ÿ√ﬂ∞°)

};
char *HaWarpGateDoc[] = {
	"image\\Sinimage\\WarpGateDoc\\B_Castle.sin"
};

char *WarningInitPoint[] = {
	"image\\Sinimage\\Help\\WarnigWeight.sin",

};
char *BabelEventDoc = "image\\Sinimage\\Quest\\BaBelEvent.sin";
char *NineTailFoxDoc = "image\\Sinimage\\Quest\\NineTailFoxEvent.sin";
char *StarDustDoc = "image\\Sinimage\\Quest\\StarDust.sin";		//≈©∏ÆΩ∫∏∂Ω∫ºˆ¡§
char *CristalEventDoc = "image\\Sinimage\\Quest\\CristalEvent.sin";//¿œ∞ˆ∞°¡ˆ ≈©∏ÆΩ∫≈ª¿« ∫∏¿∫

//π⁄¿Áø¯ - ºˆπ⁄ ∏æ∆ø¿±‚
char *WatermelonDoc = "image\\Sinimage\\Quest\\WatermelonEvent.sin";//ºˆπ⁄ ∏æ∆ø¿±‚ ¿Ã∫•∆Æ
//π⁄¿Áø¯ - »£π⁄ ∏æ∆ø¿±‚
char *PumpkinDoc = "image\\Sinimage\\Quest\\PumpkinEvent.sin";//»£π⁄ ∏æ∆ø¿±‚ ¿Ã∫•∆Æ
//π⁄¿Áø¯ - ∫∞¡∂∞¢ ∏æ∆ø¿±‚
char *StarDoc = "image\\Sinimage\\Quest\\StarEvent.sin";//π⁄¿Áø¯ - π„«œ¥√¿« º“ø¯ ¿Ã∫•∆Æ
//¿Â∫∞ - πﬂ∑ª≈∏¿Œ √ ƒ›∏¥ ∏æ∆ø¿±‚
char *ValentineDoc = "image\\Sinimage\\Quest\\ChocolateEvent.sin"; //πﬂ∑ª≈∏¿Œ √ ƒ›∏¥ ∏æ∆ø¿±‚ ¿Ã∫•∆Æ
// π⁄¿Áø¯ - æÀ∆ƒ∫™ ¡∂«’ ¿Ã∫•∆Æ
char *PristonAlphabetDoc = "image\\Sinimage\\Quest\\Priston.sin"; // π⁄¿Áø¯ - æÀ∆ƒ∫™ ¡∂«’ ¿Ã∫•∆Æ
// ¿Â∫∞ - ƒµµµ•¿Ã¡Ó
char *CandydaysDoc = "image\\Sinimage\\Quest\\CandydaysEvent.sin"; // ƒµµ ∏æ∆ø¿±‚ ¿Ã∫•∆Æ
// ¿Â∫∞ - ∏≈¡ˆƒ√±◊∏∞
char *MagicalGreenDoc = "image\\Sinimage\\Quest\\MagicalGreenEvent.sin";
// ¿Â∫∞ - ƒ´∂Û¿« ¥´π∞
char *TearOfKaraDoc = "image\\Sinimage\\Quest\\KarasTears.sin";

// ¿Â∫∞ - ¡∂ªÁø¯¿ª √£æ∆∂Û
char *Findinvestigator1_1Doc = "image\\Sinimage\\Quest\\Resercher_Start.sin";
char *Findinvestigator1_2Doc = "image\\Sinimage\\Quest\\Resercher_Pass1.sin";
char *Findinvestigator1_3Doc = "image\\Sinimage\\Quest\\Resercher_Pass2.sin";
char *Findinvestigator2_1Doc = "image\\Sinimage\\Quest\\Kamiyu_Start.sin";
char *Findinvestigator2_2Doc = "image\\Sinimage\\Quest\\Kamiyu_Pass.sin";
char *Findinvestigator3_1Doc = "image\\Sinimage\\Quest\\Eto_Start.sin";
char *Findinvestigator3_2Doc = "image\\Sinimage\\Quest\\Eto_Pass.sin";

char *LevelQuest30Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest30start.sin",
		"image\\Sinimage\\Quest\\LevelQuest30Path.sin",
		"image\\Sinimage\\Quest\\LevelQuest30end.sin",

};
char *LevelQuest55Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest55start.sin",
		"image\\Sinimage\\Quest\\LevelQuest55Path.sin",
		"image\\Sinimage\\Quest\\LevelQuest55end.sin",

};

char *LevelQuest55_2Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest55-2start.sin",
		"image\\Sinimage\\Quest\\LevelQuest55-2Path.sin",
		"image\\Sinimage\\Quest\\LevelQuest55-2end.sin",

};

char *LevelQuest70Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest70start.sin",
		"image\\Sinimage\\Quest\\LevelQuest70Path.sin",
		"image\\Sinimage\\Quest\\LevelQuest70end.sin",

};
char *LevelQuest80Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest80start.sin",
		"image\\Sinimage\\Quest\\LevelQuest80Path.sin",
		"image\\Sinimage\\Quest\\LevelQuest80end.sin",

};
char *LevelQuest85Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest85start.sin",
		"image\\Sinimage\\Quest\\LevelQuest85Path.sin",
		"image\\Sinimage\\Quest\\LevelQuest85Path2.sin",
		"image\\Sinimage\\Quest\\LevelQuest85end.sin",

};
char *LevelQuest90Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest90start.sin",
		"image\\Sinimage\\Quest\\LevelQuest90Path.sin",
		"image\\Sinimage\\Quest\\LevelQuest90end.sin",

};

char *LevelQuest80_2Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest80_2start.sin",
		"image\\Sinimage\\Quest\\LevelQuest80_2start2.sin",
		"image\\Sinimage\\Quest\\LevelQuest80_2Path.sin",
		"image\\Sinimage\\Quest\\LevelQuest80_2Path2.sin",
		"image\\Sinimage\\Quest\\LevelQuest80_2end.sin",

};

char *LevelQuest90_2Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest90_2start.sin",
		"image\\Sinimage\\Quest\\LevelQuest90_2start2.sin",
		"image\\Sinimage\\Quest\\LevelQuest90_2Path.sin",
		"image\\Sinimage\\Quest\\LevelQuest90_2Path2.sin",
		"image\\Sinimage\\Quest\\LevelQuest90_2end.sin",

};

char *QuestFilePath4[] = {
	"image\\Sinimage\\Quest\\ChangeJob4_1Start.sin",
		"image\\Sinimage\\Quest\\ChangeJob4_1Path.sin",
		"image\\Sinimage\\Quest\\ChangeJob4_2Start.sin",
		"image\\Sinimage\\Quest\\ChangeJob4_2Path.sin",
		"image\\Sinimage\\Quest\\ChangeJob4_3Start.sin",
		"image\\Sinimage\\Quest\\ChangeJob4_3Path.sin",
		"image\\Sinimage\\Quest\\ChangeJob4_4Start.sin",
		"image\\Sinimage\\Quest\\ChangeJob4_4End.sin",

};


// ºÏ≤‚÷∞“µ◊®÷∞	
int sinCheckChageJob()
{
	if (CheckQuestButtonShow1 && sinChar->iLevel >= 20 && sinChar->iRank == 0) // 2◊™
	{
		if (!sinQuest_ChangeJob.CODE && GetRace(sinChar->iClass) == BROOD_CODE_TEMPSKRON)
			sinChangeJobButtonShow = 1;
		if (!sinQuest_ChangeJob2.CODE && GetRace(sinChar->iClass) == BROOD_CODE_MORAYION)
		{
			if (!FindLastQuestCode(SIN_QUEST_CODE_CHANGEJOB2_NPC_M) && !FindLastQuestCode(SIN_QUEST_CODE_CHANGEJOB2_NPC_D) && sinChar->iRank < 1)
				sinChangeJobButtonShow2 = 1;
		}
	}
	if (CheckQuestButtonShow2&& sinChar->iLevel >= 40 && sinChar->iRank == 1) // 3◊™
	{
		if (!sinQuest_ChangeJob3.CODE && !FindLastQuestCode(SIN_QUEST_CODE_CHANGEJOB3))
		{
			sinChangeJobButtonShow3 = 1;

			switch (sinChar->iRank)
			{
			case 0:	ChangeJobSkillPlus = 5;
				break;
			case 1:	ChangeJobSkillPlus = 9;
				break;
			case 2:	ChangeJobSkillPlus = 13;
				break;
			case 3: ChangeJobSkillPlus = 17;
				break;
			case 4: ChangeJobSkillPlus = 21;
				break;
			}
			for (int i = 1; i < ChangeJobSkillPlus; i++)
			{
				if (!sinSkill.UseSkill[i].Point)
					sinChangeJobButtonShow3 = 0;
			}
		}
	}
	if (CheckQuestButtonShow3 && sinChar->iLevel >= 60 && sinChar->iRank == 2)  // 4◊™
	{
		if (!sinQuest_ChangeJob4.CODE)
		{
			sinChangeJobButtonShow4 = 1;
			switch (sinChar->iRank)
			{
			case 0:	ChangeJobSkillPlus = 5;
				break;
			case 1:	ChangeJobSkillPlus = 9;
				break;
			case 2:	ChangeJobSkillPlus = 13;
				break;
			case 3: ChangeJobSkillPlus = 17;
				break;
			case 4: ChangeJobSkillPlus = 21;
				break;
			}
			for (int i = 1; i < ChangeJobSkillPlus; i++)
			{
				if (!sinSkill.UseSkill[i].Point)
					sinChangeJobButtonShow4 = 0;
			}
		}
	}
	return TRUE;
}

// º”‘ÿ»ŒŒÒ	
int sinLoadQuest(int CODE, void *Buff)
{
	if (CODE == SIN_QUEST_CODE_CHANGEJOB)
	{
		memcpy(&sinQuest_ChangeJob, Buff, sizeof(sQUEST_CHANGEJOB));

		if (GetRace(sinChar->iClass) == BROOD_CODE_TEMPSKRON)
			sinSetQuestTimer(SIN_QUEST_CODE_CHANGEJOB);
	}
	if (CODE == SIN_QUEST_CODE_CHANGEJOB2_NPC_M || CODE == SIN_QUEST_CODE_CHANGEJOB2_NPC_D)
		memcpy(&sinQuest_ChangeJob2, Buff, sizeof(sQUEST_CHANGEJOB));
	if (CODE == SIN_QUEST_CODE_CHANGEJOB3)
		memcpy(&sinQuest_ChangeJob3, Buff, sizeof(sQUEST_CHANGEJOB3));
	if (CODE == SIN_QUEST_CODE_LEVEL30)
	{
		memcpy(&sinQuest_Level30, Buff, sizeof(sQUEST_CHANGEJOB3));

		if (sinQuest_Level30.State == 1 || sinQuest_Level30.State == 2)
		{
#ifdef ENGLISH_LANGUAGE
			lstrcpy(szQuestMonsterName, "Bargon");
#else
			lstrcpy(szQuestMonsterName, "µ∂∏´ ÷");
#endif
			sinSetQuestTimer(SIN_QUEST_CODE_LEVEL30);
		}
	}
	if (CODE == SIN_QUEST_CODE_LEVEL55)
	{
		memcpy(&sinQuest_Level55, Buff, sizeof(sQUEST_CHANGEJOB3));

		if (sinQuest_Level55.State == 1 || sinQuest_Level55.State == 2)
		{
#ifdef ENGLISH_LANGUAGE
			lstrcpy(szQuestMonsterName, "Mush");
#else
			lstrcpy(szQuestMonsterName, "À…±˝π÷");
#endif
			sinSetQuestTimer(SIN_QUEST_CODE_LEVEL55);
		}
	}
	if (CODE == SIN_QUEST_CODE_LEVEL55_2)
	{
		memcpy(&sinQuest_Level55_2, Buff, sizeof(sQUEST_CHANGEJOB3));

		if (sinQuest_Level55_2.State == 1 || sinQuest_Level55_2.State == 2)
		{
#ifdef ENGLISH_LANGUAGE
			lstrcpy(szQuestMonsterName, "Dire Bee");
#else
			lstrcpy(szQuestMonsterName, "√€∑‰æ´");
#endif
			sinSetQuestTimer(SIN_QUEST_CODE_LEVEL55_2);
		}
	}
	if (CODE == SIN_QUEST_CODE_LEVEL70)
	{
		memcpy(&sinQuest_Level70, Buff, sizeof(sQUEST_CHANGEJOB3));

		if (sinQuest_Level70.State == 1 || sinQuest_Level70.State == 2)
		{
#ifdef ENGLISH_LANGUAGE
			lstrcpy(szQuestMonsterName, "Typhoon");
#else
			lstrcpy(szQuestMonsterName, "Ã®∑Á");
#endif
			sinSetQuestTimer(SIN_QUEST_CODE_LEVEL70);
		}
	}
	if (CODE == SIN_QUEST_CODE_LEVEL80)
	{
		memcpy(&sinQuest_Level80, Buff, sizeof(sQUEST_CHANGEJOB3));

		if (sinQuest_Level80.State == 1 || sinQuest_Level80.State == 2)
		{
#ifdef ENGLISH_LANGUAGE
			lstrcpy(szQuestMonsterName, "Ratoo");
#else
			lstrcpy(szQuestMonsterName, "¬≥Õº");
#endif
			sinSetQuestTimer(SIN_QUEST_CODE_LEVEL80);
		}
	}
	if (CODE == SIN_QUEST_CODE_LEVEL80_2)
	{
		memcpy(&sinQuest_Level80_2, Buff, sizeof(sQUEST_CHANGEJOB3));

		if (sinQuest_Level80_2.State == 2)
		{
			lstrcpy(szQuestMonsterName, "BOSS");
			sinSetQuestTimer(SIN_QUEST_CODE_LEVEL80_2);
		}
	}
	if (CODE == SIN_QUEST_CODE_LEVEL85)
	{
		memcpy(&sinQuest_Level85, Buff, sizeof(sQUEST_CHANGEJOB3));
		if (sinQuest_Level85.State == 1 || sinQuest_Level85.State == 2 || sinQuest_Level85.State == 3)
		{
#ifdef ENGLISH_LANGUAGE
			lstrcpy(szQuestMonsterName, "Grotesque");
#else
			lstrcpy(szQuestMonsterName, "—«Ãÿ¿ºÀπæﬁ»À");
#endif
			sinSetQuestTimer(SIN_QUEST_CODE_LEVEL85);
		}
	}
	if (CODE == SIN_QUEST_CODE_LEVEL90)
	{
		memcpy(&sinQuest_Level90, Buff, sizeof(sQUEST_CHANGEJOB3));

		if (sinQuest_Level90.State == 1 || sinQuest_Level90.State == 2)
		{
#ifdef ENGLISH_LANGUAGE
			lstrcpy(szQuestMonsterName, "Iron Fist");
#else
			lstrcpy(szQuestMonsterName, "Ã˙»≠");
#endif
			sinSetQuestTimer(SIN_QUEST_CODE_LEVEL90);
		}
	}
	if (CODE == SIN_QUEST_CODE_LEVEL90_2)
	{
		memcpy(&sinQuest_Level90_2, Buff, sizeof(sQUEST_CHANGEJOB3));

		if (sinQuest_Level90_2.State == 2 || sinQuest_Level90_2.State == 3)
		{
			if (sinQuest_Level90_2.Kind)
			{
				lstrcpy(szQuestMonsterName, sinLevelQuest90_2Mon[sinQuest_Level90_2.Kind - 13]);
				sinSetQuestTimer(SIN_QUEST_CODE_LEVEL90_2);
			}
		}
	}
	if (CODE == SIN_QUEST_CODE_CHANGEJOB4)
	{
		memcpy(&sinQuest_ChangeJob4, Buff, sizeof(sQUEST_CHANGEJOB3));
		if (sinQuest_ChangeJob4.AgingCount)
		{
			if (sinQuest_ChangeJob4.State == 3 || sinQuest_ChangeJob4.State == 1)
			{
				sinSetQuestTimer(SIN_QUEST_CODE_CHANGEJOB4, sinQuest_ChangeJob4.AgingCount, sinQuest_ChangeJob4.StartLevel);
				lstrcpy(szQuestMonsterName, sinGetMonsterName(sinQuest_ChangeJob4.Kind));
			}
		}
	}
	if (CODE == HAQUEST_CODE_ELEMENTARY_A)
		memcpy(&chaQuest.sHaQuestElementary[Quest_A], Buff, sizeof(sQUEST_ELEMENTARY));

	if (CODE == HAQUEST_CODE_ELEMENTARY_B)
	{
		chaQuest.QuestKeyCode = Quest_B;
		memcpy(&chaQuest.sHaQuestElementary[Quest_B], Buff, sizeof(sQUEST_ELEMENTARY));

		if (chaQuest.sHaQuestElementary[Quest_B].State == 1)
		{
			if (GetRace(sinChar->iClass) == BROOD_CODE_TEMPSKRON)
#ifdef ENGLISH_LANGUAGE
				lstrcpy(chaQuest.szQuestMonsterName, "Hobgoblin");
			else
				lstrcpy(chaQuest.szQuestMonsterName, "North Goblin");
#else
				lstrcpy(chaQuest.szQuestMonsterName, "ƒß ﬁ±¯");
			else
				lstrcpy(chaQuest.szQuestMonsterName, "æﬁƒß ﬁ");
#endif

			chaQuest.haSetQuestTimer();
		}
	}
	if (CODE == HAQUEST_CODE_ELEMENTARY_C)
	{
		chaQuest.QuestKeyCode = Quest_C;
		memcpy(&chaQuest.sHaQuestElementary[Quest_C], Buff, sizeof(sQUEST_ELEMENTARY));

		if (chaQuest.sHaQuestElementary[Quest_C].State == 1 || chaQuest.sHaQuestElementary[Quest_C].State == 2)
		{
#ifdef ENGLISH_LANGUAGE
			lstrcpy(chaQuest.szQuestMonsterName, "Zombie");
#else
			lstrcpy(chaQuest.szQuestMonsterName, "Ω© ¨");
#endif
			chaQuest.haSetQuestTimer();
		}
	}
	if (CODE == HAQUEST_CODE_ELEMENTARY_D)
	{
		memcpy(&chaQuest.sHaQuestElementary[Quest_D], Buff, sizeof(sQUEST_ELEMENTARY));
	}
	if (CODE == HAQUEST_CODE_ELEMENTARY_E)
	{
		chaQuest.QuestKeyCode = Quest_E;
		memcpy(&chaQuest.sHaQuestElementary[Quest_E], Buff, sizeof(sQUEST_ELEMENTARY));

		if (chaQuest.sHaQuestElementary[Quest_E].State == 1 || chaQuest.sHaQuestElementary[Quest_E].State == 2)
		{
#ifdef ENGLISH_LANGUAGE
			lstrcpy(chaQuest.szQuestMonsterName, "Leeches");
#else
			lstrcpy(chaQuest.szQuestMonsterName, "»Îµÿ¡˙");
#endif
			chaQuest.haSetQuestTimer();
		}
	}

	if (CODE == HAQUEST_CODE_ELEMENTARY_F)
	{
		chaQuest.QuestKeyCode = Quest_F;
		memcpy(&chaQuest.sHaQuestElementary[Quest_F], Buff, sizeof(sQUEST_ELEMENTARY));

		if (chaQuest.sHaQuestElementary[Quest_F].State == 1 || chaQuest.sHaQuestElementary[Quest_F].State == 2)
		{
#ifdef ENGLISH_LANGUAGE
			lstrcpy(chaQuest.szQuestMonsterName, "Head Cutter");
#else
			lstrcpy(chaQuest.szQuestMonsterName, "ƒßΩ£ ø");
#endif
			chaQuest.haSetQuestTimer();
		}
	}
	if (CODE == HAQUEST_CODE_ELEMENTARY_G)
	{
		chaQuest.QuestKeyCode = Quest_G;
		memcpy(&chaQuest.sHaQuestElementary[Quest_G], Buff, sizeof(sQUEST_ELEMENTARY));

		if (chaQuest.sHaQuestElementary[Quest_G].State == 1 || chaQuest.sHaQuestElementary[Quest_G].State == 2)
		{
#ifdef ENGLISH_LANGUAGE
			lstrcpy(chaQuest.szQuestMonsterName, "Oasis's Monster");
#else
			lstrcpy(chaQuest.szQuestMonsterName, "¬Ã÷ﬁπ÷ŒÔ");
#endif
			chaQuest.haSetQuestTimer();
		}
	}
	if (CODE == HAQUEST_CODE_ELEMENTARY_H)
	{
		chaQuest.QuestKeyCode = Quest_H;
		memcpy(&chaQuest.sHaQuestElementary[Quest_H], Buff, sizeof(sQUEST_ELEMENTARY));

		if (chaQuest.sHaQuestElementary[Quest_H].State == 1 || chaQuest.sHaQuestElementary[Quest_H].State == 2)
		{
#ifdef ENGLISH_LANGUAGE
			lstrcpy(chaQuest.szQuestMonsterName, "Ancient Prison 2F's Monster");
#else
			lstrcpy(chaQuest.szQuestMonsterName, "µÿ¿Œ2≤„π÷ŒÔ");
#endif
			chaQuest.haSetQuestTimer();
		}
	}
	if (CODE == HAQUEST_CODE_ELEMENTARY_I)
	{
		chaQuest.QuestKeyCode = Quest_I;
		memcpy(&chaQuest.sHaQuestElementary[Quest_I], Buff, sizeof(sQUEST_ELEMENTARY));

		if (chaQuest.sHaQuestElementary[Quest_I].State == 1 || chaQuest.sHaQuestElementary[Quest_I].State == 2)
		{
#ifdef ENGLISH_LANGUAGE
			lstrcpy(chaQuest.szQuestMonsterName, "Dark Sanctuary's Monster");
#else
			lstrcpy(chaQuest.szQuestMonsterName, "∞µ∫⁄ •µÓπ÷ŒÔ");
#endif
			chaQuest.haSetQuestTimer();
		}
	}
	if (CODE == HAQUEST_CODE_ELEMENTARY_J)
	{
		chaQuest.QuestKeyCode = Quest_J;
		memcpy(&chaQuest.sHaQuestElementary[Quest_J], Buff, sizeof(sQUEST_ELEMENTARY));

		if (chaQuest.sHaQuestElementary[Quest_J].State == 1 || chaQuest.sHaQuestElementary[Quest_J].State == 2)
		{
#ifdef ENGLISH_LANGUAGE
			lstrcpy(chaQuest.szQuestMonsterName, "Cursed Temple 2nd Floor's Monster");
#else
			lstrcpy(chaQuest.szQuestMonsterName, "ªﬁ∆¯À¬√Ì2≤„π÷ŒÔ");
#endif
			chaQuest.haSetQuestTimer();
		}
	}
	if (CODE == HAQUEST_CODE_ELEMENTARY_K)
	{
		chaQuest.QuestKeyCode = Quest_K;
		memcpy(&chaQuest.sHaQuestElementary[Quest_K], Buff, sizeof(sQUEST_ELEMENTARY));

		if (chaQuest.sHaQuestElementary[Quest_K].State == 1 || chaQuest.sHaQuestElementary[Quest_K].State == 2)
		{
#ifdef ENGLISH_LANGUAGE
			lstrcpy(chaQuest.szQuestMonsterName, "Heart of Perum's Monster");
#else
			lstrcpy(chaQuest.szQuestMonsterName, "∆’¡˙–ƒ‘‡π÷ŒÔ");
#endif
			chaQuest.haSetQuestTimer();
		}
	}

	if (CODE == HAQUEST_CODE_ELEMENTARY_L)
	{
		chaQuest.QuestKeyCode = Quest_L;
		memcpy(&chaQuest.sHaQuestElementary[Quest_L], Buff, sizeof(sQUEST_ELEMENTARY));

		if (chaQuest.sHaQuestElementary[Quest_L].State == 1)
		{
#ifdef ENGLISH_LANGUAGE
			lstrcpy(chaQuest.szQuestMonsterName, "Babel");
#else
			lstrcpy(chaQuest.szQuestMonsterName, "∞Õ±À˛");
#endif
			chaQuest.haSetQuestTimer();
		}
	}

	if (CODE == HAQUEST_CODE_FURYOFPHANTOM)
	{
		memcpy(&chaQuest.sHaQuest100LV, Buff, sizeof(sQUEST_ELEMENTARY));

		if (chaQuest.sHaQuest100LV.State == 2 || chaQuest.sHaQuest100LV.State == 3)
		{
#ifdef ENGLISH_LANGUAGE
			lstrcpy(chaQuest.szQuestMonsterName, "Heart of Perum's Monster");
#else
			lstrcpy(chaQuest.szQuestMonsterName, "∆’¡˙–ƒ‘‡π÷ŒÔ");
#endif
			chaQuest.haSetQuestTimer();
		}
		if (chaQuest.sHaQuest100LV.State == 7 || chaQuest.sHaQuest100LV.State == 8)
		{
#ifdef ENGLISH_LANGUAGE
			lstrcpy(chaQuest.szQuestMonsterName, "Gallubia Valley's Monster");
#else
			lstrcpy(chaQuest.szQuestMonsterName, "ø≠¿≠± …Ωπ»π÷ŒÔ");
#endif
			chaQuest.haSetQuestTimer();
		}
	}

	return TRUE;
}

// ±£¥Ê»ŒŒÒ	
int sinSaveQuest(void *Buff)
{
	int ContinueSkillIndex = 0;
	if (sinQuest_ChangeJob4.CODE == SIN_QUEST_CODE_CHANGEJOB4)
	{
		if (ContinueSkillIndex = cSkill.SearchContiueSkillIndex(CHANGE_JOB3_QUEST))
		{
			sinQuest_ChangeJob4.AgingCount = ContinueSkill[ContinueSkillIndex - 1].UseTime;
			sinQuest_ChangeJob4.StartLevel = ContinueSkill[ContinueSkillIndex - 1].CheckTime;
		}
		memcpy(Buff, &sinQuest_ChangeJob4, sizeof(sQUEST_CHANGEJOB3));
		return sinQuest_ChangeJob4.CODE;
	}
	if (sinQuest_ChangeJob3.CODE == SIN_QUEST_CODE_CHANGEJOB3)
	{
		memcpy(Buff, &sinQuest_ChangeJob3, sizeof(sQUEST_CHANGEJOB3));
		return sinQuest_ChangeJob3.CODE;
	}
	if (sinQuest_ChangeJob.CODE == SIN_QUEST_CODE_CHANGEJOB)
	{
		memcpy(Buff, &sinQuest_ChangeJob, sizeof(sQUEST_CHANGEJOB));
		return sinQuest_ChangeJob.CODE;
	}
	if (sinQuest_ChangeJob2.CODE == SIN_QUEST_CODE_CHANGEJOB2_NPC_M || sinQuest_ChangeJob2.CODE == SIN_QUEST_CODE_CHANGEJOB2_NPC_D)
	{
		memcpy(Buff, &sinQuest_ChangeJob2, sizeof(sQUEST_CHANGEJOB));
		return sinQuest_ChangeJob2.CODE;
	}
	if (sinQuest_Level30.CODE == SIN_QUEST_CODE_LEVEL30)
	{
		memcpy(Buff, &sinQuest_Level30, sizeof(sQUEST_CHANGEJOB3));
		return sinQuest_Level30.CODE;
	}
	if (sinQuest_Level55.CODE == SIN_QUEST_CODE_LEVEL55)
	{
		memcpy(Buff, &sinQuest_Level55, sizeof(sQUEST_CHANGEJOB3));
		return sinQuest_Level55.CODE;
	}
	if (sinQuest_Level55_2.CODE == SIN_QUEST_CODE_LEVEL55_2)
	{
		memcpy(Buff, &sinQuest_Level55_2, sizeof(sQUEST_CHANGEJOB3));
		return sinQuest_Level55_2.CODE;
	}
	if (sinQuest_Level70.CODE == SIN_QUEST_CODE_LEVEL70)
	{
		memcpy(Buff, &sinQuest_Level70, sizeof(sQUEST_CHANGEJOB3));
		return sinQuest_Level70.CODE;
	}
	if (sinQuest_Level80.CODE == SIN_QUEST_CODE_LEVEL80)
	{
		memcpy(Buff, &sinQuest_Level80, sizeof(sQUEST_CHANGEJOB3));
		return sinQuest_Level80.CODE;
	}
	if (sinQuest_Level85.CODE == SIN_QUEST_CODE_LEVEL85)
	{
		memcpy(Buff, &sinQuest_Level85, sizeof(sQUEST_CHANGEJOB3));
		return sinQuest_Level85.CODE;
	}
	if (sinQuest_Level90.CODE == SIN_QUEST_CODE_LEVEL90)
	{
		memcpy(Buff, &sinQuest_Level90, sizeof(sQUEST_CHANGEJOB3));
		return sinQuest_Level90.CODE;
	}
	if (sinQuest_Level80_2.CODE == SIN_QUEST_CODE_LEVEL80_2)
	{
		memcpy(Buff, &sinQuest_Level80_2, sizeof(sQUEST_CHANGEJOB3));
		return sinQuest_Level80_2.CODE;
	}
	if (sinQuest_Level90_2.CODE == SIN_QUEST_CODE_LEVEL90_2)
	{
		memcpy(Buff, &sinQuest_Level90_2, sizeof(sQUEST_CHANGEJOB3));
		return sinQuest_Level90_2.CODE;
	}
	if (chaQuest.sHaQuestElementary[Quest_A].CODE == HAQUEST_CODE_ELEMENTARY_A)
	{
		memcpy(Buff, &chaQuest.sHaQuestElementary[Quest_A], sizeof(sQUEST_ELEMENTARY));
		return chaQuest.sHaQuestElementary[Quest_A].CODE;
	}
	if (chaQuest.sHaQuestElementary[Quest_B].CODE == HAQUEST_CODE_ELEMENTARY_B)
	{
		memcpy(Buff, &chaQuest.sHaQuestElementary[Quest_B], sizeof(sQUEST_ELEMENTARY));
		return chaQuest.sHaQuestElementary[Quest_B].CODE;
	}
	if (chaQuest.sHaQuestElementary[Quest_C].CODE == HAQUEST_CODE_ELEMENTARY_C)
	{
		memcpy(Buff, &chaQuest.sHaQuestElementary[Quest_C], sizeof(sQUEST_ELEMENTARY));
		return chaQuest.sHaQuestElementary[Quest_C].CODE;
	}
	if (chaQuest.sHaQuestElementary[Quest_D].CODE == HAQUEST_CODE_ELEMENTARY_D)
	{
		memcpy(Buff, &chaQuest.sHaQuestElementary[Quest_D], sizeof(sQUEST_ELEMENTARY));
		return chaQuest.sHaQuestElementary[Quest_D].CODE;
	}
	if (chaQuest.sHaQuestElementary[Quest_E].CODE == HAQUEST_CODE_ELEMENTARY_E)
	{
		memcpy(Buff, &chaQuest.sHaQuestElementary[Quest_E], sizeof(sQUEST_ELEMENTARY));
		return chaQuest.sHaQuestElementary[Quest_E].CODE;
	}
	if (chaQuest.sHaQuestElementary[Quest_F].CODE == HAQUEST_CODE_ELEMENTARY_F)
	{
		memcpy(Buff, &chaQuest.sHaQuestElementary[Quest_F], sizeof(sQUEST_ELEMENTARY));
		return chaQuest.sHaQuestElementary[Quest_F].CODE;
	}
	if (chaQuest.sHaQuestElementary[Quest_G].CODE == HAQUEST_CODE_ELEMENTARY_G)
	{
		memcpy(Buff, &chaQuest.sHaQuestElementary[Quest_G], sizeof(sQUEST_ELEMENTARY));
		return chaQuest.sHaQuestElementary[Quest_G].CODE;
	}
	if (chaQuest.sHaQuestElementary[Quest_H].CODE == HAQUEST_CODE_ELEMENTARY_H)
	{
		memcpy(Buff, &chaQuest.sHaQuestElementary[Quest_H], sizeof(sQUEST_ELEMENTARY));
		return chaQuest.sHaQuestElementary[Quest_H].CODE;
	}
	if (chaQuest.sHaQuestElementary[Quest_I].CODE == HAQUEST_CODE_ELEMENTARY_I)
	{
		memcpy(Buff, &chaQuest.sHaQuestElementary[Quest_I], sizeof(sQUEST_ELEMENTARY));
		return chaQuest.sHaQuestElementary[Quest_I].CODE;
	}
	if (chaQuest.sHaQuestElementary[Quest_J].CODE == HAQUEST_CODE_ELEMENTARY_J)
	{
		memcpy(Buff, &chaQuest.sHaQuestElementary[Quest_J], sizeof(sQUEST_ELEMENTARY));
		return chaQuest.sHaQuestElementary[Quest_J].CODE;
	}
	if (chaQuest.sHaQuestElementary[Quest_K].CODE == HAQUEST_CODE_ELEMENTARY_K)
	{
		memcpy(Buff, &chaQuest.sHaQuestElementary[Quest_K], sizeof(sQUEST_ELEMENTARY));
		return chaQuest.sHaQuestElementary[Quest_K].CODE;
	}
	if (chaQuest.sHaQuestElementary[Quest_L].CODE == HAQUEST_CODE_ELEMENTARY_L)
	{
		memcpy(Buff, &chaQuest.sHaQuestElementary[Quest_L], sizeof(sQUEST_ELEMENTARY));
		return chaQuest.sHaQuestElementary[Quest_L].CODE;
	}
	if (chaQuest.sHaQuest100LV.CODE == HAQUEST_CODE_FURYOFPHANTOM)
	{
		memcpy(Buff, &chaQuest.sHaQuest100LV, sizeof(sQUEST_ELEMENTARY));
		return chaQuest.sHaQuest100LV.CODE;
	}
	return FALSE;
}

/*----------------------------------------------------------------------------*
*					ƒ˘Ω∫∆ÆΩ√ NPC¿« ¥ÎªÁ∏¶ ∫∏ø©¡ÿ¥Ÿ
*-----------------------------------------------------------------------------*/
int sinMorayionNpcChangeJob_Two()
{
	//if(!chaQuest.haQuestCheck())return FALSE; //«ˆ¿Á √ ∫∏ ƒ˘Ω∫∆Æ ∞° ¡¯«‡¡ﬂ¿Ã∏È

	int i = 0;

	for (i = 0; i < INVENTORY_MAXITEM; i++)
	{
		if (cInvenTory.InvenItem[i].bValid)
		{
			if (cInvenTory.InvenItem[i].sBaseItemID.ToInt() == (sinQT1 | sin04) ||
				cInvenTory.InvenItem[i].sBaseItemID.ToInt() == (sinQT1 | sin05))
			{
				sinQuest_ChangeJob2.State = 3;
				cInvenTory.InvenItem[i].bValid = 0;
				cInvenTory.ReFormInvenItem();
				break;
			}
		}
		if (cInvenTory.InvenItemTemp[i].bValid)
		{
			if (cInvenTory.InvenItemTemp[i].sBaseItemID.ToInt() == (sinQT1 | sin04) ||
				cInvenTory.InvenItemTemp[i].sBaseItemID.ToInt() == (sinQT1 | sin05))
			{
				sinQuest_ChangeJob2.State = 3;
				cInvenTory.InvenItemTemp[i].bValid = 0;
				cInvenTory.ReFormInvenItem();
				break;
			}
		}
	}
	//ƒß¡È◊Â2◊™
	if (sinQuest_ChangeJob2.CODE == SIN_QUEST_CODE_CHANGEJOB2_NPC_M)
	{
		switch (sinQuest_ChangeJob2.State)
		{
		case 1:
			cSinHelp.sinShowHelp(SIN_MESSAGE_DEFAULT, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath[3]);
			sinQuest_ChangeJob2.State = 2;
			break;
		case 2:
			cSinHelp.sinShowHelp(SIN_MESSAGE_DEFAULT, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath[4]);
			break;
		case 3:
			cSinHelp.sinShowHelp(SIN_MESSAGE_DEFAULT, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath[5]);
			sinQuest_ChangeJob2.State = 4;
			sinQuest_ChangeJob2.BackUpCode = sinQuest_ChangeJob2.CODE;
			sinQuest_ChangeJob2.CODE = 0;
			EndQuest_Code(sinQuest_ChangeJob2.BackUpCode);
			sinChar->wVersion[1] = 0;
			break;
		}
	}
	if (sinQuest_ChangeJob2.CODE == SIN_QUEST_CODE_CHANGEJOB2_NPC_D)
	{
		switch (sinQuest_ChangeJob2.State)
		{
		case 1:
			cSinHelp.sinShowHelp(SIN_MESSAGE_DEFAULT, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath[6]);
			sinQuest_ChangeJob2.State = 2;
			break;
		case 2:
			cSinHelp.sinShowHelp(SIN_MESSAGE_DEFAULT, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath[7]);
			break;
		case 3:
			cSinHelp.sinShowHelp(SIN_MESSAGE_DEFAULT, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath[8]);
			sinQuest_ChangeJob2.BackUpCode = sinQuest_ChangeJob2.CODE;
			sinQuest_ChangeJob2.CODE = 0;
			EndQuest_Code(sinQuest_ChangeJob2.BackUpCode);
			sinQuest_ChangeJob2.CODE = 0;
			sinChar->wVersion[1] = 0;
			break;
		}
	}
	return TRUE;
}
/*----------------------------------------------------------------------------*
*				ƒ˘Ω∫∆ÆΩ√ NPC¿« ¥ÎªÁ∏¶ ∫∏ø©¡÷∞Ì æ∆¿Ã≈€¿ª √≥∏Æ«—¥Ÿ (3¬˜¿¸¡˜)
*-----------------------------------------------------------------------------*/
int sinNpcChangeJob3()
{
	ItemData *pItem = 0;
	int   Count = 0;
	int   i = 0;
	int   TempItemIndex[3] = { 0,0,0 };

	if (!sinQuest_ChangeJob3.CODE)
		return FALSE;

	if (sinQuest_ChangeJob3.State == 1)
	{
		for (i = 0; i < INVENTORY_MAXITEM * 2; i++)
		{
			if (i < 100)
			{
				if (!cInvenTory.InvenItem[i].bValid)
					continue;
				pItem = &cInvenTory.InvenItem[i];
			}
			else
			{
				if (!cInvenTory.InvenItemTemp[i - 100].bValid)
					continue;
				pItem = &cInvenTory.InvenItemTemp[i - 100];
			}
			if (pItem->sItem.sItemID.ToInt() == (sinQT1 | sin06))
			{
				if (Count >= 3)
					break;
				TempItemIndex[Count] = i;
				Count++;
			}
		}

		if (Count >= 3)
		{
			sinQuest_ChangeJob3.State = 2;
			memset(&sWingItem_Send, 0, sizeof(sCRAFTITEM_SERVER));
			for (int j = 0; j < Count; j++)
			{
				if (TempItemIndex[j] < 100)
				{
					sWingItem_Send.SheltomCode[j] = cInvenTory.InvenItem[TempItemIndex[j]].sItem.sItemID.ToInt();
					sWingItem_Send.Head[j] = cInvenTory.InvenItem[TempItemIndex[j]].sItem.iChk1;
					sWingItem_Send.CheckSum[j] = cInvenTory.InvenItem[TempItemIndex[j]].sItem.iChk2;
				}
				else
				{
					sWingItem_Send.SheltomCode[j] = cInvenTory.InvenItemTemp[TempItemIndex[j]].sItem.sItemID.ToInt();
					sWingItem_Send.Head[j] = cInvenTory.InvenItemTemp[TempItemIndex[j]].sItem.iChk1;
					sWingItem_Send.CheckSum[j] = cInvenTory.InvenItemTemp[TempItemIndex[j]].sItem.iChk2;

				}
			}
			cInvenTory.ReFormInvenItem();
		}
	}

	switch (sinQuest_ChangeJob3.State)
	{
	case 1:
		break;
	case 2:
		cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath3[2]);
		return TRUE;
		break;
	case 3:
		break;
	case 4:
		cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath3[4]);
		return TRUE;
		break;
	case 6:
		cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath3[5]);
		break;
	}
	return FALSE;
}


//…æ≥˝»ŒŒÒŒÔ∆∑
int DeleteQuestItem(DWORD CODE, int Kind)
{
	ItemData *pItem = 0;
	int i = 0;

	for (i = 0; i < INVENTORY_MAXITEM * 2; i++)
	{
		if (i < 100)
		{
			if (!cInvenTory.InvenItem[i].bValid)
				continue;
			pItem = &cInvenTory.InvenItem[i];
		}
		else
		{
			if (!cInvenTory.InvenItemTemp[i - 100].bValid)
				continue;
			pItem = &cInvenTory.InvenItemTemp[i - 100];
		}

		if (pItem->sItem.sItemID.ToInt() == CODE)
		{
			if (Kind == 0)
				pItem->bValid = 0;
			else
			{
				if (pItem->sItem.eCraftType == Kind)
					pItem->bValid = 0;
			}
			if (i < 100)
			{
				if (pItem->iItemSlot)
				{
					sInven[pItem->iItemSlot - 1].ItemIndex = 0;
					if (pItem->iVisibleItemType)
						sinSetCharItem(pItem->sBaseItemID.ToInt(), pItem->iVisibleItemType, FALSE);
				}
			}
		}
	}

	cInvenTory.ReFormInvenItem();
	ReformCharForm();
	cInvenTory.ReFormPotionNum();
	cInvenTory.SetItemToChar();
	cInvenTory.CheckWeight();
	return TRUE;
}
int  QuestMonsterCount[] = { 30,40,50,25,35,45,50,70,100 };

int CheckChangeJob3QuestItem(DWORD Monster_CODE)
{
	if (Monster_CODE == 100)
		return FALSE;

	char szTemp[128];
	char szBuff[128];
	memset(&szTemp, 0, sizeof(szTemp));
	//100º∂»ŒŒÒ
	if (chaQuest.sHaQuest100LV.CODE)
	{
		if (chaQuest.sHaQuest100LV.Kind)
		{
			if (chaQuest.sHaQuest100LV.State == 2 && STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == 28)
			{
				chaQuest.sHaQuest100LV.Monster[0]++;

				if (chaQuest.sHaQuest100LV.Monster[0] >= chaQuest.sHaQuest100LV.Monster[1])
				{
					wsprintf(szBuff, "Quest> %s %d number of monster needed    ", szQuestMonsterName, chaQuest.sHaQuest100LV.Monster[1]);
					cMessageBox.ShowMessageEvent(szBuff);
					chaQuest.sHaQuest100LV.Kind = 0;
					chaQuest.sHaQuest100LV.State = 3;
				}
			}
			if (chaQuest.sHaQuest100LV.State == 7 && STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == MAPID_GallubiaValley)
			{
				chaQuest.sHaQuest100LV.Monster[0]++;

				if (chaQuest.sHaQuest100LV.Monster[0] >= chaQuest.sHaQuest100LV.Monster[1])
				{
					wsprintf(szBuff, "Quest> %s %d number of monster needed   ", szQuestMonsterName, chaQuest.sHaQuest100LV.Monster[1]);
					cMessageBox.ShowMessageEvent(szBuff);
					chaQuest.sHaQuest100LV.Kind = 0;
					chaQuest.sHaQuest100LV.State = 8;
				}
			}
		}
	}
	//¡‘…±Ω© ¨
	if (chaQuest.sHaQuestElementary[Quest_C].CODE)
	{
		if (chaQuest.sHaQuestElementary[Quest_C].Kind &&chaQuest.sHaQuestElementary[Quest_C].Kind == Monster_CODE)
		{
			chaQuest.sHaQuestElementary[Quest_C].Monster[0]++;

			if (chaQuest.sHaQuestElementary[Quest_C].Monster[0] >= chaQuest.sHaQuestElementary[Quest_C].Monster[1])
			{
				wsprintf(szBuff, "Quest> %s %d number of monster needed    ", szQuestMonsterName, chaQuest.sHaQuestElementary[Quest_C].Monster[1]);
				cMessageBox.ShowMessageEvent(szBuff);
				chaQuest.sHaQuestElementary[Quest_C].Kind = 0;
				chaQuest.sHaQuestElementary[Quest_C].State = 2;
				SetQuestBoard();
				SaveGameData();
			}
		}
	}
	//¡‘…±»Îµÿ¡˙
	if (chaQuest.sHaQuestElementary[Quest_E].CODE)
	{
		if (chaQuest.sHaQuestElementary[Quest_E].Kind &&chaQuest.sHaQuestElementary[Quest_E].Kind == Monster_CODE)
		{
			chaQuest.sHaQuestElementary[Quest_E].Monster[0]++;

			if (chaQuest.sHaQuestElementary[Quest_E].Monster[0] >= chaQuest.sHaQuestElementary[Quest_E].Monster[1])
			{
				wsprintf(szBuff, "Quest> %s %d number of monster needed    ", szQuestMonsterName, chaQuest.sHaQuestElementary[Quest_E].Monster[1]);
				cMessageBox.ShowMessageEvent(szBuff);
				chaQuest.sHaQuestElementary[Quest_E].Kind = 0;
				chaQuest.sHaQuestElementary[Quest_E].State = 2;
				SetQuestBoard();
				SaveGameData();
			}
		}
	}
	//¡‘…±ƒßΩ£ ø
	if (chaQuest.sHaQuestElementary[Quest_F].CODE)
	{
		if (chaQuest.sHaQuestElementary[Quest_F].Kind &&chaQuest.sHaQuestElementary[Quest_F].Kind == Monster_CODE)
		{
			chaQuest.sHaQuestElementary[Quest_F].Monster[0]++;

			if (chaQuest.sHaQuestElementary[Quest_F].Monster[0] >= chaQuest.sHaQuestElementary[Quest_F].Monster[1])
			{
				wsprintf(szBuff, "Quest> %s %d number of monster needed    ", szQuestMonsterName, chaQuest.sHaQuestElementary[Quest_F].Monster[1]);
				cMessageBox.ShowMessageEvent(szBuff);
				chaQuest.sHaQuestElementary[Quest_F].Kind = 0;
				chaQuest.sHaQuestElementary[Quest_F].State = 2;
				SetQuestBoard();
				SaveGameData();
			}
		}
	}
	//¡‘…±¬Ã÷ﬁπ÷ŒÔ
	if (chaQuest.sHaQuestElementary[Quest_G].CODE)
	{
		if (chaQuest.sHaQuestElementary[Quest_G].Kind)
		{
			if (chaQuest.sHaQuestElementary[Quest_G].State == 1 &&
				STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == MAPID_Oasis)
			{
				chaQuest.sHaQuestElementary[Quest_G].Monster[0]++;

				if (chaQuest.sHaQuestElementary[Quest_G].Monster[0] >= chaQuest.sHaQuestElementary[Quest_G].Monster[1])
				{
					wsprintf(szBuff, "Quest> %s %d number of monster needed    ", szQuestMonsterName, chaQuest.sHaQuestElementary[Quest_G].Monster[1]);
					cMessageBox.ShowMessageEvent(szBuff);
					chaQuest.sHaQuestElementary[Quest_G].Kind = 0;
					chaQuest.sHaQuestElementary[Quest_G].State = 2;
					SetQuestBoard();
					SaveGameData();
				}
			}
		}
	}
	//¡‘…±µÿ¿Œ2≤„π÷ŒÔ
	if (chaQuest.sHaQuestElementary[Quest_H].CODE)
	{
		if (chaQuest.sHaQuestElementary[Quest_H].Kind)
		{
			if (chaQuest.sHaQuestElementary[Quest_H].State == 1 &&
				STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == MAPID_AncientPrisonF2)
			{
				chaQuest.sHaQuestElementary[Quest_H].Monster[0]++;

				if (chaQuest.sHaQuestElementary[Quest_H].Monster[0] >= chaQuest.sHaQuestElementary[Quest_H].Monster[1])
				{
					wsprintf(szBuff, "Quest> %s %d number of monster needed    ", szQuestMonsterName, chaQuest.sHaQuestElementary[Quest_H].Monster[1]);
					cMessageBox.ShowMessageEvent(szBuff);
					chaQuest.sHaQuestElementary[Quest_H].Kind = 0;
					chaQuest.sHaQuestElementary[Quest_H].State = 2;
					SetQuestBoard();
					SaveGameData();
				}
			}
		}
	}
	//¡‘…±∞µ∫⁄ •µÓπ÷ŒÔ
	if (chaQuest.sHaQuestElementary[Quest_I].CODE)
	{
		if (chaQuest.sHaQuestElementary[Quest_I].Kind)
		{
			if (chaQuest.sHaQuestElementary[Quest_I].State == 1 &&
				STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == MAPID_DarkSanctuary)
			{
				chaQuest.sHaQuestElementary[Quest_I].Monster[0]++;

				if (chaQuest.sHaQuestElementary[Quest_I].Monster[0] >= chaQuest.sHaQuestElementary[Quest_I].Monster[1])
				{
					wsprintf(szBuff, "Quest> %s %d number of monster needed    ", szQuestMonsterName, chaQuest.sHaQuestElementary[Quest_I].Monster[1]);
					cMessageBox.ShowMessageEvent(szBuff);
					chaQuest.sHaQuestElementary[Quest_I].Kind = 0;
					chaQuest.sHaQuestElementary[Quest_I].State = 2;
					SetQuestBoard();
					SaveGameData();
				}
			}
		}
	}
	// ¡‘…±ªﬁ∆¯À¬√Ì2≤„π÷ŒÔ
	if (chaQuest.sHaQuestElementary[Quest_J].CODE)
	{
		if (chaQuest.sHaQuestElementary[Quest_J].Kind)
		{
			if (chaQuest.sHaQuestElementary[Quest_J].State == 1 &&
				STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == MAPID_CursedTempleF2)
			{
				chaQuest.sHaQuestElementary[Quest_J].Monster[0]++;

				if (chaQuest.sHaQuestElementary[Quest_J].Monster[0] >= chaQuest.sHaQuestElementary[Quest_J].Monster[1])
				{
					wsprintf(szBuff, "Quest> %s %d number of monster needed    ", szQuestMonsterName, chaQuest.sHaQuestElementary[Quest_J].Monster[1]);
					cMessageBox.ShowMessageEvent(szBuff);
					chaQuest.sHaQuestElementary[Quest_J].Kind = 0;
					chaQuest.sHaQuestElementary[Quest_J].State = 2;
					SetQuestBoard();
					SaveGameData();
				}
			}
		}
	}

	// ¡‘…±∆’¡˙–ƒ‘‡µƒπ÷ŒÔ
	if (chaQuest.sHaQuestElementary[Quest_K].CODE)
	{
		if (chaQuest.sHaQuestElementary[Quest_K].Kind)
		{
			if (chaQuest.sHaQuestElementary[Quest_K].State == 1 &&
				STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == MAPID_HeartOfPerum)
			{
				chaQuest.sHaQuestElementary[Quest_K].Monster[0]++;

				if (chaQuest.sHaQuestElementary[Quest_K].Monster[0] >= chaQuest.sHaQuestElementary[Quest_K].Monster[1])
				{
					wsprintf(szBuff, "Quest> %s %d number of monster needed    ", szQuestMonsterName, chaQuest.sHaQuestElementary[Quest_K].Monster[1]);
					cMessageBox.ShowMessageEvent(szBuff);
					chaQuest.sHaQuestElementary[Quest_K].Kind = 0;
					chaQuest.sHaQuestElementary[Quest_K].State = 2;
					SetQuestBoard();
					SaveGameData();
				}
			}
		}
	}

	//¡‘…±∞Õ±À˛
	if (chaQuest.sHaQuestElementary[Quest_L].CODE)
	{
		if (chaQuest.sHaQuestElementary[Quest_L].Kind &&chaQuest.sHaQuestElementary[Quest_L].Kind == Monster_CODE)
		{
			chaQuest.sHaQuestElementary[Quest_L].Monster[0]++;

			if (chaQuest.sHaQuestElementary[Quest_L].Monster[0] >= chaQuest.sHaQuestElementary[Quest_L].Monster[1])
			{
				CTITLEBOX->SetText("Quest> %s %d number of monster needed", szQuestMonsterName, chaQuest.sHaQuestElementary[Quest_F].Monster[1]);
			}
		}
	}
	//4◊™»ŒŒÒ
	if (sinQuest_ChangeJob4.CODE)
	{
		if (sinQuest_ChangeJob4.Kind &&Monster_CODE == sinQuest_ChangeJob4.Kind && sinQuest_ChangeJob4.State <= 4)
		{
			sinQuest_ChangeJob4.Monster[0]++;

			if (sinQuest_ChangeJob4.Monster[0] >= sinQuest_ChangeJob4.Monster[1])
			{
				CTITLEBOX->SetText("Quest> %s %d number of monster needed", szQuestMonsterName, sinQuest_ChangeJob4.Monster[1]);
				sinQuest_ChangeJob4.Kind = 0;
			}
		}
	}

	//30º∂»ŒŒÒ
	if (sinQuest_Level30.CODE)
	{
		if (sinQuest_Level30.State == 1 && Monster_CODE == MONSTER_BAGON)
		{
			sinQuest_Level30.Monster[0]++;

			if (sinQuest_Level30.Monster[0] >= sinQuest_Level30.Monster[1])
			{
				wsprintf(szBuff, "Quest> %s %d number of monster needed    ", szQuestMonsterName, sinQuest_Level30.Monster[1]);
				cMessageBox.ShowMessageEvent(szBuff);
				sinQuest_Level30.State = 2;
				SetQuestBoard();
				SaveGameData();
			}
		}
	}

	//55º∂»ŒŒÒ
	if (sinQuest_Level55.CODE)
	{
		if (sinQuest_Level55.State == 1 && MONSTER_MURPIN == Monster_CODE)
		{
			sinQuest_Level55.Monster[0]++;

			if (sinQuest_Level55.Monster[0] >= sinQuest_Level55.Monster[1])
			{
				wsprintf(szBuff, "Quest> %s %d number of monster needed    ", szQuestMonsterName, sinQuest_Level55.Monster[1]);
				cMessageBox.ShowMessageEvent(szBuff);
				sinQuest_Level55.State = 2;
				SetQuestBoard();
				SaveGameData();
			}
		}
	}
	//55º∂µ⁄2∏ˆ»ŒŒÒ
	if (sinQuest_Level55_2.CODE)
	{
		if (sinQuest_Level55_2.State == 1 && MONSTER_DIREBEE == Monster_CODE)
		{
			sinQuest_Level55_2.Monster[0]++;

			if (sinQuest_Level55_2.Monster[0] >= sinQuest_Level55_2.Monster[1])
			{
				wsprintf(szBuff, "Quest> %s %d number of monster needed    ", szQuestMonsterName, sinQuest_Level55_2.Monster[1]);
				cMessageBox.ShowMessageEvent(szBuff);
				sinQuest_Level55_2.State = 2;
				SetQuestBoard();
				SaveGameData();
			}
		}
	}

	//70º∂»ŒŒÒ
	if (sinQuest_Level70.CODE)
	{
		if (sinQuest_Level70.State == 1 && MONSTER_TYPOON == Monster_CODE)
		{
			sinQuest_Level70.Monster[0]++;

			if (sinQuest_Level70.Monster[0] >= sinQuest_Level70.Monster[1])
			{
				wsprintf(szBuff, "Quest> %s %d number of monster needed    ", szQuestMonsterName, sinQuest_Level70.Monster[1]);
				cMessageBox.ShowMessageEvent(szBuff);
				sinQuest_Level70.State = 2;
				SetQuestBoard();
				SaveGameData();
			}
		}
	}
	//80º∂»ŒŒÒ
	if (sinQuest_Level80.CODE)
	{
		if (sinQuest_Level80.State == 1 && MONSTER_RATOO == Monster_CODE)
		{
			sinQuest_Level80.Monster[0]++;

			if (sinQuest_Level80.Monster[0] >= sinQuest_Level80.Monster[1])
			{
				wsprintf(szBuff, "Quest> %s %d number of monster needed    ", szQuestMonsterName, sinQuest_Level80.Monster[1]);
				cMessageBox.ShowMessageEvent(szBuff);
				sinQuest_Level80.State = 2;
				SetQuestBoard();
				SaveGameData();
			}
		}
	}
	//85º∂»ŒŒÒ
	if (sinQuest_Level85.CODE)
	{
		if (sinQuest_Level85.State == 2 && MONSTER_GROTESQUE == Monster_CODE)
		{
			sinQuest_Level85.Monster[0]++;

			if (sinQuest_Level85.Monster[0] >= sinQuest_Level85.Monster[1])
			{
				wsprintf(szBuff, "Quest> %s %d number of monster needed    ", szQuestMonsterName, sinQuest_Level85.Monster[1]);
				cMessageBox.ShowMessageEvent(szBuff);
				sinQuest_Level85.State = 3;
				SetQuestBoard();
				SaveGameData();
			}
		}
	}
	//90º∂»ŒŒÒ
	if (sinQuest_Level90.CODE)
	{
		if (sinQuest_Level90.State == 1 && MONSTER_IRONFIST == Monster_CODE)
		{
			sinQuest_Level90.Monster[0]++;

			if (sinQuest_Level90.Monster[0] >= sinQuest_Level90.Monster[1])
			{
				wsprintf(szBuff, "Quest> %s %d number of monster needed    ", szQuestMonsterName, sinQuest_Level90.Monster[1]);
				cMessageBox.ShowMessageEvent(szBuff);
				sinQuest_Level90.State = 2;
				SetQuestBoard();
				SaveGameData();
			}
		}
	}
	//90º∂µ⁄2∏ˆ»ŒŒÒ
	if (sinQuest_Level90_2.CODE)
	{
		if (sinQuest_Level90_2.State == 2 && sinQuest_Level90_2.Kind && sinQuest_Level90_2.Kind == Monster_CODE)
		{
			sinQuest_Level90_2.Monster[0] ++;

			if (sinQuest_Level90_2.Monster[0] >= sinQuest_Level90_2.Monster[1])
			{
				wsprintf(szBuff, "Quest> %s %d number of monster needed    ", sinLevelQuest90_2Mon[sinQuest_Level90_2.Kind - 13], sinQuest_Level90_2.Monster[1]);
				cMessageBox.ShowMessageEvent(szBuff);
				sinQuest_Level90_2.State = 3;
			}
		}
	}

	ItemData *pItem = 0;
	if (sInven[0].ItemIndex)
	{
		pItem = &cInvenTory.InvenItem[sInven[0].ItemIndex - 1];
	}
	if (!pItem)
		return FALSE;

	if (pItem->sItem.sAgeLevel > 3 || pItem->sItem.eCraftType != ITEMCRAFTTYPE_QuestWeapon)
		return FALSE;

	if (pItem->sItem.eCraftType == ITEMCRAFTTYPE_QuestWeapon)
	{
		switch (sinChar->iClass)
		{
		case CHARACTERCLASS_Fighter:
		case CHARACTERCLASS_Mechanician:
		case CHARACTERCLASS_Pikeman:
		case CHARACTERCLASS_Knight:
		case CHARACTERCLASS_Archer:
		case CHARACTERCLASS_Atalanta:
		case CHARACTERCLASS_Assassin:
			if ((pItem->sItem.bMaturing + 1) == Monster_CODE)
				pItem->sItem.sMatureBar.sMin--;
			break;
		case CHARACTERCLASS_Magician:
		case CHARACTERCLASS_Priestess:
		case CHARACTERCLASS_Shaman:
			if (pItem->sItem.sAgeLevel == 1)
			{
				if (STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == MAPID_ForgottenLand)
					pItem->sItem.sMatureBar.sMin--;
			}
			if (pItem->sItem.sAgeLevel == 2)
			{
				if (STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == MAPID_Oasis)
					pItem->sItem.sMatureBar.sMin--;
			}
			if (pItem->sItem.sAgeLevel == 3)
			{
				if (STAGE_MAP[lpCurPlayer->iLoadedMapIndex]->iMapID == MAPID_AncientPrisonF1)
					pItem->sItem.sMatureBar.sMin--;
			}
			break;
		}
	}

	if ((pItem->sItem.sMatureBar.sMin < 1) || (ResetQuset3Flag == 2))
	{
		NotChangeSetItemFlag = 1;
		ZeroMemory(&sAging_Send, sizeof(sCRAFTITEM_SERVER));
		memcpy(&sAging_Send.DesCraftItem, pItem, sizeof(ItemData));
		SendAgingItemToServer(&sAging_Send);

		memcpy(&TempQuestItem, pItem, sizeof(ItemData));
	}
	return TRUE;

}
int SetChangeJob3QuestItem(Item *pItem, int Down)
{
	int Temp = 0;
	float fTemp = 0;
	if (pItem->sAgeLevel > 3)
		return FALSE;

	switch (pItem->sItemID.ToItemType())
	{
	case sinWA1:
	case sinWC1:
	case sinWP1:
	case sinWS2:
	case sinWD1:
		if (Down)
		{

		}
		else
		{
			if (pItem->sAgeLevel)
			{
				pItem->fAddHP += 4;
				Temp = GetRandomPos(1, 2);
				pItem->sDamage.sMin += Temp;
				pItem->sDamage.sMax += Temp;
				Temp = GetRandomPos(10, 15);
				pItem->iAttackRating += Temp;
				pItem->eMixEffect = SIN_ADD_DAMAGE_MIN | SIN_ADD_DAMAGE_MAX | SIN_ADD_ATTACK_RATE | SIN_ADD_LIFE;
			}
			pItem->bMaturing = pItem->sAgeLevel;
			pItem->sMatureBar.sMax = QuestMonsterCount[pItem->bMaturing];
			pItem->sAgeLevel++;

		}
		break;
	case sinWS1:
	case sinWT1:
		if (Down)
		{

		}
		else
		{
			if (pItem->sAgeLevel)
			{
				pItem->fAddHP += 4;
				Temp = GetRandomPos(1, 2);
				pItem->sDamage.sMin += Temp;
				pItem->sDamage.sMax += Temp;
				Temp = GetRandomPos(10, 15);
				pItem->iAttackRating += Temp;
				pItem->eMixEffect = SIN_ADD_DAMAGE_MIN | SIN_ADD_DAMAGE_MAX | SIN_ADD_ATTACK_RATE | SIN_ADD_LIFE;
			}

			pItem->bMaturing = 3 + pItem->sAgeLevel;
			pItem->sMatureBar.sMax = QuestMonsterCount[pItem->bMaturing];
			pItem->sAgeLevel++;

		}
		break;
	case sinWM1:
	case sinWN1:
		if (Down)
		{

		}
		else
		{
			if (pItem->sAgeLevel)
			{
				pItem->fAddHP += 4;
				Temp = GetRandomPos(1, 2);
				pItem->sDamage.sMin += Temp;
				pItem->sDamage.sMax += Temp;
				Temp = GetRandomPos(3, 6);
				fTemp = (float)Temp / 10.0f;
				pItem->fMPRegen += fTemp;
				pItem->eMixEffect = SIN_ADD_DAMAGE_MIN | SIN_ADD_DAMAGE_MAX | SIN_ADD_MANAREGEN | SIN_ADD_LIFE;

			}
			pItem->bMaturing = 6 + pItem->sAgeLevel;
			pItem->sMatureBar.sMax = QuestMonsterCount[pItem->bMaturing];
			pItem->sAgeLevel++;

		}
		break;
	}
	pItem->sMatureBar.sMin = pItem->sMatureBar.sMax;
	ReformItem(pItem);
	return TRUE;
}

int CheckQuestItemDownFlag = 0;

int CheckChangeJob_QuestItem()
{
	int ItemIndex = 0;
	ItemData *pTempItem = 0;
	if (sinQuest_ChangeJob3.CODE && sinQuest_ChangeJob3.State == 5 && sinChar->iRank == 2)
	{
		while (1)
		{
			ItemIndex = cInvenTory.SearchItemIndex(0, ITEMCRAFTTYPE_QuestWeapon);
			if (ItemIndex)
			{
				if (ItemIndex < 100)
					pTempItem = &cInvenTory.InvenItem[ItemIndex - 1];
				else
					pTempItem = &cInvenTory.InvenItemTemp[(ItemIndex - 100) - 1];

				if (sinItemTime > pTempItem->sItem.dwCreateTime + (60 * 60 * 24 * 5))
				{
					cInvenTory.DeleteInvenItemToServer(pTempItem->sItem.sItemID.ToInt(), pTempItem->sItem.iChk1, pTempItem->sItem.iChk2);
					DeleteQuestItem(sinOR2 | sin02);
					DeleteQuestItem(sinOR2 | sin03);
					DeleteQuestItem(sinOR2 | sin04);

					if (MouseItem.bValid && MouseItem.sItem.eCraftType == ITEMCRAFTTYPE_QuestWeapon)
						cInvenTory.DeleteInvenItemToServer(MouseItem.sItem.sItemID.ToInt(), MouseItem.sItem.iChk1, MouseItem.sItem.iChk2);
				}
				else
					break;
			}
			else
				break;
		}
	}

	if (sinQuest_ChangeJob3.CODE && sinQuest_ChangeJob3.State == 5 && sinChar->iRank == 2)
	{
		if (!cInvenTory.SearchItemCode(0, ITEMCRAFTTYPE_QuestWeapon))
		{
			switch (sinChar->iClass)
			{
			case CHARACTERCLASS_Fighter:
				lstrcpy(sLost_Item.szDoc, Quest3ItemName[0]);
				sLost_Item.LostItem[0].sBaseItemID = (sinWA1 | sin08);
				sLost_Item.LostItem[1].sBaseItemID = (sinOR2 | sin02);
				break;
			case CHARACTERCLASS_Mechanician:
				lstrcpy(sLost_Item.szDoc, Quest3ItemName[1]);
				sLost_Item.LostItem[0].sBaseItemID = (sinWC1 | sin08);
				sLost_Item.LostItem[1].sBaseItemID = (sinOR2 | sin02);
				break;
			case CHARACTERCLASS_Archer:
				lstrcpy(sLost_Item.szDoc, Quest3ItemName[2]);
				sLost_Item.LostItem[0].sBaseItemID = (sinWS1 | sin10);
				sLost_Item.LostItem[1].sBaseItemID = (sinOR2 | sin03);
				break;
			case CHARACTERCLASS_Pikeman:
				lstrcpy(sLost_Item.szDoc, Quest3ItemName[3]);
				sLost_Item.LostItem[0].sBaseItemID = (sinWP1 | sin09);
				sLost_Item.LostItem[1].sBaseItemID = (sinOR2 | sin02);
				break;
			case CHARACTERCLASS_Atalanta:
				lstrcpy(sLost_Item.szDoc, Quest3ItemName[4]);
				sLost_Item.LostItem[0].sBaseItemID = (sinWT1 | sin09);
				sLost_Item.LostItem[1].sBaseItemID = (sinOR2 | sin03);
				break;
			case CHARACTERCLASS_Knight:
				lstrcpy(sLost_Item.szDoc, Quest3ItemName[5]);
				sLost_Item.LostItem[0].sBaseItemID = (sinWS2 | sin10);
				sLost_Item.LostItem[1].sBaseItemID = (sinOR2 | sin02);
				break;
			case CHARACTERCLASS_Magician:
			case CHARACTERCLASS_Priestess:
				lstrcpy(sLost_Item.szDoc, Quest3ItemName[6]);
				sLost_Item.LostItem[0].sBaseItemID = (sinWM1 | sin09);
				sLost_Item.LostItem[1].sBaseItemID = (sinOR2 | sin04);
				break;
			case CHARACTERCLASS_Assassin:
				lstrcpy(sLost_Item.szDoc, Quest3ItemName[7]);
				sLost_Item.LostItem[0].sBaseItemID = (sinWD1 | sin09);
				sLost_Item.LostItem[1].sBaseItemID = (sinOR2 | sin03);
				break;
			case CHARACTERCLASS_Shaman:
				lstrcpy(sLost_Item.szDoc, Quest3ItemName[8]);
				sLost_Item.LostItem[0].sBaseItemID = (sinWN1 | sin09);
				sLost_Item.LostItem[1].sBaseItemID = (sinOR2 | sin04);
				break;
			}
			sinQuest_ChangeJob3.State = 6;
			sLost_Item.Flag = 1;
			cInvenTory.CheckInvenEmpty(&sLost_Item.LostItem[0]);
			cInvenTory.CheckInvenEmpty(&sLost_Item.LostItem[1]);
		}
	}

	ItemIndex = 0;
	if (sinQuest_ChangeJob3.CODE && !CheckQuestItemDownFlag)
	{
		ItemIndex = cInvenTory.SearchItemIndex(0, ITEMCRAFTTYPE_QuestWeapon);
		if (ItemIndex)
		{
			if (sinChar->iLevel > sinQuest_ChangeJob3.StartLevel + 2)
			{
				sinQuest_ChangeJob3.StartLevel = sinChar->iLevel;
				CheckQuestItemDownFlag = 1;
			}
		}
	}

	if (sinChar->iRank >= 1)
	{
		DeleteQuestItem(sinQT1 | sin01);
		DeleteQuestItem(sinQT1 | sin02);
		DeleteQuestItem(sinQT1 | sin03);
		DeleteQuestItem(sinQT1 | sin04);
		DeleteQuestItem(sinQT1 | sin05);
	}
	if (sinChar->iRank >= 2 && !sinQuest_ChangeJob3.CODE)
	{
		DeleteQuestItem(sinQT1 | sin06);
		DeleteQuestItem(sinOR2 | sin02);
		DeleteQuestItem(sinOR2 | sin03);
		DeleteQuestItem(sinOR2 | sin04);
	}
	return TRUE;
}
int sinCheckLevelQuest30()
{
	if (chaQuest.haQuestCheck(0) == FALSE)
		return TRUE;
	if (CheckNowQuestState(SIN_QUEST_CODE_LEVEL30) == FALSE)
		return TRUE;
	if (sinChar->iLevel >= 30 && sinChar->iRank >= 1 && (sinQuest_levelLog & QUESTBIT_LEVEL_30) == 0)
	{
		switch (sinQuest_Level30.State)
		{
		case 0:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL30, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\LevelQuest30start.sin");
			return TRUE;
		case 1:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL30, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\LevelQuest30Path.sin");
			return TRUE;
		case 2:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL30, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\LevelQuest30end.sin");
			return TRUE;
		}
	}

	return FALSE;
}
int sinCheckLevelQuest55()
{
	if (chaQuest.haQuestCheck(0) == FALSE)
		return TRUE;
	if (CheckNowQuestState(SIN_QUEST_CODE_LEVEL55) == FALSE)
		return TRUE;
	if (sinChar->iLevel >= 55 && sinChar->iRank >= 2 && (sinQuest_levelLog & (QUESTBIT_LEVEL_30 | QUESTBIT_LEVEL_55)) == QUESTBIT_LEVEL_30)
	{
		switch (sinQuest_Level55.State)
		{
		case 0:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL55, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\LevelQuest55start.sin");
			return TRUE;
		case 1:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL55, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\LevelQuest55Path.sin");
			return TRUE;
		case 2:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL55, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\LevelQuest55end.sin");
			return TRUE;
		}
	}
	return FALSE;
}
int sinCheckLevelQuest55_2()
{
	if (chaQuest.haQuestCheck(0) == FALSE)
		return TRUE;
	if (CheckNowQuestState(SIN_QUEST_CODE_LEVEL55_2) == FALSE)
		return TRUE;
	if (sinChar->iLevel >= 55 && sinChar->iRank >= 2 && (sinQuest_levelLog & (QUESTBIT_LEVEL_30 | QUESTBIT_LEVEL_55)) == QUESTBIT_LEVEL_30)
	{
		switch (sinQuest_Level55_2.State)
		{
		case 0:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL55_2, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\LevelQuest55-2start.sin");
			return TRUE;
		case 1:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL55_2, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\LevelQuest55-2Path.sin");
			return TRUE;
		case 2:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL55_2, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\LevelQuest55-2end.sin");
			return TRUE;
		}
	}
	return FALSE;
}
int sinCheckLevelQuest70()
{
	if (chaQuest.haQuestCheck(0) == FALSE)
		return TRUE;
	if (CheckNowQuestState(SIN_QUEST_CODE_LEVEL70) == FALSE)
		return TRUE;
	if (sinChar->iLevel >= 70 && sinChar->iRank >= 3 && (sinQuest_levelLog & (QUESTBIT_LEVEL_55 | QUESTBIT_LEVEL_70)) == QUESTBIT_LEVEL_55)
	{
		switch (sinQuest_Level70.State)
		{
		case 0:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL70, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\LevelQuest70start.sin");
			return TRUE;
		case 1:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL70, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\LevelQuest70Path.sin");
			return TRUE;
		case 2:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL70, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\LevelQuest70end.sin");
			return TRUE;
		}
	}
	return FALSE;
}
int sinCheckLevelQuest80()
{
	if (chaQuest.haQuestCheck(0) == FALSE)
		return TRUE;
	if (CheckNowQuestState(SIN_QUEST_CODE_LEVEL80) == FALSE)
		return TRUE;
	if (sinChar->iLevel >= 80 && sinChar->iRank >= 4 && (sinQuest_levelLog & (QUESTBIT_LEVEL_70 | QUESTBIT_LEVEL_80)) == QUESTBIT_LEVEL_70)
	{
		switch (sinQuest_Level80.State)
		{
		case 0:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL80, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\LevelQuest80start.sin");
			return TRUE;
		case 1:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL80, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\LevelQuest80Path.sin");
			return TRUE;
		case 2:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL80, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\LevelQuest80end.sin");
			return TRUE;
		}
	}
	return FALSE;
}
int sinCheckLevelQuest85()
{
	if (!chaQuest.haQuestCheck(0))
		return TRUE;
	if (!CheckNowQuestState(SIN_QUEST_CODE_LEVEL85))
		return TRUE;
	if (sinChar->iLevel >= 85 && sinChar->iRank >= 4 && (sinQuest_levelLog & (QUESTBIT_LEVEL_80 | QUESTBIT_LEVEL_85)) == QUESTBIT_LEVEL_80)
	{
		switch (sinQuest_Level85.State)
		{
		case 0:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL85, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\LevelQuest85start.sin");
			return TRUE;
		case 1:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL85, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\LevelQuest85Path.sin");
			return TRUE;
		case 2:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL85, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\LevelQuest85Path2.sin");
			return TRUE;
		case 3:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL85, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\LevelQuest85end.sin");
			return TRUE;
		}
	}

	return FALSE;
}

int sinCheckQuest85Die()
{
	if (sinQuest_Level85.CODE && sinQuest_Level85.State)
	{
		sinQuest_Level85.State = 1;
		DeleteQuestItem(sinQT1 | sin08);
	}
	if (sinQuest_Level90_2.CODE && sinQuest_Level90_2.State == 2)
	{
		sinQuest_Level90_2.State = 1;
		sinQuest_Level90_2.Monster[0] = 0;
		sinQuest_Level90_2.Monster[1] = 0;
		sinQuest_Level90_2.Kind = 0;
		cMessageBox.ShowMessage(MESSAGE_PLUS_POINT_90_2_MON);
		cSkill.CancelContinueSkill(CHANGE_JOB3_QUEST);
		cInvenTory.SetItemToChar();
		SetQuestBoard();
	}
	return TRUE;
}
int sinCheckLevelQuest90()
{
	if (chaQuest.haQuestCheck(0) == FALSE)
		return TRUE;
	if (CheckNowQuestState(SIN_QUEST_CODE_LEVEL90) == FALSE)
		return TRUE;
	if (sinChar->iLevel >= 90 && sinChar->iRank >= 4 && (sinQuest_levelLog & (QUESTBIT_LEVEL_85 | QUESTBIT_LEVEL_90)) == QUESTBIT_LEVEL_85)
	{
		switch (sinQuest_Level90.State)
		{
		case 0:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL90, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\LevelQuest90start.sin");
			break;
		case 1:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL90, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\LevelQuest90Path.sin");
			break;
		case 2:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL90, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\LevelQuest90end.sin");
			break;
		}
	}
	return TRUE;
}
int sinCheckLevelQuest80_2(int NpcNum)
{
	switch (NpcNum)
	{
	case 0:
		if (chaQuest.haQuestCheck(0) == FALSE)
			return TRUE;
		if (CheckNowQuestState(SIN_QUEST_CODE_LEVEL80_2) == FALSE)
			return TRUE;
		if (sinChar->iLevel >= 80 && sinChar->iRank >= 4 && (sinQuest_levelLog & QUESTBIT_LEVEL_80_2) == 0)
		{
			switch (sinQuest_Level80_2.State)
			{
			case 0:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL80_2, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\LevelQuest80_2start.sin");
				return TRUE;
			case 1:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL80_2, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\LevelQuest80_2pass.sin");
				return TRUE;
			case 2:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL80_2, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\LevelQuest80_2pass1.sin");
				return TRUE;
			case 3:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL80_2, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\LevelQuest80_2end.sin");
				return TRUE;
			}
		}
		break;
	case 1:
		if (chaQuest.haQuestCheck(0) == FALSE)
			return TRUE;
		if (CheckNowQuestState(SIN_QUEST_CODE_LEVEL80_2) == FALSE)
			return TRUE;
		if (sinChar->iLevel >= 80 && sinChar->iRank >= 4 && (sinQuest_levelLog & QUESTBIT_LEVEL_80_2) == 0)
		{
			switch (sinQuest_Level80_2.State)
			{
			case 1:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL80_2, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\LevelQuest80_2start2.sin", NpcNum);
				return TRUE;
			case 2:
				if (cInvenTory.SearchItemCode(sinQT1 | sin09) && cInvenTory.SearchItemCode(sinQT1 | sin10) && cInvenTory.SearchItemCode(sinQT1 | sin11))
					cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL80_2, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\LevelQuest80_2end2.sin", NpcNum);
				else
					cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL80_2, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\LevelQuest80_2Path2.sin", NpcNum);
				return TRUE;
			}
		}
		break;
	}

	return FALSE;
}
int sinCheckLevelQuest90_2(int NpcNum)
{
	switch (NpcNum)
	{
	case 0:
		if (chaQuest.haQuestCheck(0) == FALSE)
			return TRUE;

		if (CheckNowQuestState(SIN_QUEST_CODE_LEVEL90_2) == FALSE)
			return TRUE;

		if (sinChar->iLevel >= 90 && sinChar->iRank >= 4 && (sinQuest_levelLog & QUESTBIT_LEVEL_90_2) == 0)
		{
			switch (sinQuest_Level90_2.State)
			{
			case 0:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL90_2, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest90_2Doc[0]);
				return TRUE;
			case 1:
			case 2:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL90_2, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest90_2Doc[2]);
				return TRUE;
			}
		}
		break;
	case 1:
		if (chaQuest.haQuestCheck(0) == FALSE)
			return TRUE;

		if (CheckNowQuestState(SIN_QUEST_CODE_LEVEL90_2) == FALSE)
			return TRUE;

		if (sinChar->iLevel >= 90 && sinChar->iRank >= 4 && (sinQuest_levelLog & QUESTBIT_LEVEL_90_2) == 0)
		{
			switch (sinQuest_Level90_2.State)
			{
			case 1:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL90_2, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest90_2Doc[1], NpcNum);
				return TRUE;
			case 2:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL90_2, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest90_2Doc[3], NpcNum);
				return TRUE;
			case 3:
				cSinHelp.sinShowHelp(SIN_HELP_KIND_Q_LEVEL90_2, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), LevelQuest90_2Doc[4], NpcNum);
				return TRUE;
			}
		}
		break;
	}
	return FALSE;
}

void *pQuestCode[] =
{
	&sinQuest_ChangeJob,
	&sinQuest_ChangeJob2,
	&sinQuest_ChangeJob3,
	&sinQuest_Level30,
	&sinQuest_Level55,
	&sinQuest_Level55_2,
	&sinQuest_Level70,
	&sinQuest_Level80,
	&sinQuest_Level85,
	&sinQuest_Level90,
	&sinQuest_Level80_2,
	&sinQuest_Level90_2,
	&sinQuest_ChangeJob4,
	0,
};

struct QuestCodeFlag
{
	DWORD	CODE;
};
int CheckNowQuestState(DWORD CODE)
{
	int cnt = 0;
	while (pQuestCode[cnt] != 0)
	{
		if (((QuestCodeFlag *)pQuestCode[cnt])->CODE && ((QuestCodeFlag *)pQuestCode[cnt])->CODE != CODE)
		{
			cMessageBox.ShowMessage(MESSAGE_QUEST_NOW_EXIT);
			return FALSE;
		}
		cnt++;
	}
	return TRUE;
}
int ClearNowQuest()
{
	int cnt = 0;
	while (1)
	{
		if (pQuestCode[cnt] == 0)
			break;
		if (((QuestCodeFlag *)pQuestCode[cnt])->CODE)
		{
			((QuestCodeFlag *)pQuestCode[cnt])->CODE = 0;
			return FALSE;
		}
		cnt++;
	}
	return TRUE;
}

int sinChangeJob4MonCode[][2] =
{
	{MONSTER_MURPIN,MONSTER_SKELETON_KNIGHT },
	{MONSTER_HEAD_CUTTER,MONSTER_SOLID_SNAIL},
	{MONSTER_THORN_CROWLER,MONSTER_MUMMY},
	{MONSTER_DOOM_GUARD ,MONSTER_FIGON},
	{MONSTER_STONE_GIANT,MONSTER_STONE_COLEM},
	{MONSTER_IRON_GUARD,MONSTER_AVELLRIN},
};
int sinChangeJob4MonCode2[][2] =
{
	{MONSTER_AVELRISK_L,MONSTER_BEEBUL},
	{MONSTER_ILLUSION_KNIGHT,MONSTER_NIGHT_MARE },
	{MONSTER_WITCH,MONSTER_HEAVY_GOBLIN},
	{MONSTER_DAWLIN ,MONSTER_STYGIAN},
	{MONSTER_INCUBUS,MONSTER_CHAIN_GOLEM},
	{MONSTER_DARK_SPECTOR,MONSTER_METRON},
};
int sinChangeJob4MonCode3[] =
{
	MONSTER_SOLID_SNAIL,
	MONSTER_ILLUSION_KNIGHT,
	MONSTER_AVELRISK_LOAD,
	MONSTER_DUSK,
	MONSTER_CHAIN_GOLEM ,
	MONSTER_SADNESS
};
char *sinGetMonsterName(int CODE)
{
	return sinMonCodeName[CODE];
}

int QuestLevelTable[7] = { 60,65,70,75,80,85,200 };
char szQuestMonsterName[64];

int sinChangeJob4MonSet(sQUEST_CHANGEJOB3 *pQuset)
{
	int QuestLevel = 0;
	char szBuff[128];

	for (int i = 0; i < 6; i++)
	{
		if (sinChar->iLevel >= QuestLevelTable[i] && sinChar->iLevel < QuestLevelTable[i + 1])
			QuestLevel = i;
	}
	int RandomIndex = 0;
	switch (pQuset->State)
	{
	case 1:
		RandomIndex = GetRandomPos(0, 1);
		if (QuestLevel < 4)
			pQuset->Monster[1] = 50;
		else
			pQuset->Monster[1] = 30;

		pQuset->Kind = sinChangeJob4MonCode[QuestLevel][RandomIndex];
		lstrcpy(szQuestMonsterName, sinGetMonsterName(pQuset->Kind));

#ifdef ENGLISH_LANGUAGE
		wsprintf(szBuff, "Quest> %s %d number of monster needed    ", szQuestMonsterName, pQuset->Monster[1]);
#else
		wsprintf(szBuff, "ƒ˙–Ë“™»•·˜¡‘ %d ∏ˆ %s    ", pQuset->Monster[1], szQuestMonsterName);
#endif

		cMessageBox.ShowMessageEvent(szBuff);
		sinSetQuestTimer(SIN_QUEST_CODE_CHANGEJOB4, 4200);
		break;
	case 2:
		RandomIndex = GetRandomPos(0, 1);
		if (QuestLevel < 4)
			pQuset->Monster[1] = 50;
		else
			pQuset->Monster[1] = 30;

		pQuset->Kind = sinChangeJob4MonCode2[QuestLevel][RandomIndex];
		lstrcpy(szQuestMonsterName, sinGetMonsterName(pQuset->Kind));

#ifdef ENGLISH_LANGUAGE
		wsprintf(szBuff, "Quest> %s %d number of monster needed    ", szQuestMonsterName, pQuset->Monster[1]);
#else
		wsprintf(szBuff, "ƒ˙–Ë“™»•·˜¡‘ %d ∏ˆ %s    ", pQuset->Monster[1], szQuestMonsterName);
#endif

		cMessageBox.ShowMessageEvent(szBuff);
		sinSetQuestTimer(SIN_QUEST_CODE_CHANGEJOB4, 4200);
		break;
	case 4:
		pQuset->Kind = sinChangeJob4MonCode3[QuestLevel];
		lstrcpy(szQuestMonsterName, sinGetMonsterName(pQuset->Kind));
#ifdef ENGLISH_LANGUAGE
		wsprintf(szBuff, "<Quest> Get the item from %s", szQuestMonsterName);
#else
		wsprintf(szBuff, "–Ë“™¥” %s ªÒµ√’‚∏ˆŒÔ∆∑", szQuestMonsterName);
#endif
		cMessageBox.ShowMessageEvent(szBuff);
		break;
	}

	return TRUE;
}
int sinCheckChangeJobQuest4()
{
	if (chaQuest.haQuestCheck(0) == FALSE)
		return FALSE;
	if (CheckNowQuestState(SIN_QUEST_CODE_CHANGEJOB4) == FALSE)
		return FALSE;
	if (sinQuest_ChangeJob4.CODE && sinChar->iLevel >= 60)
	{
		switch (sinQuest_ChangeJob4.State)
		{
		case 0:
			if (sinQuest_ChangeJob4.Monster[1])
				cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath4[0]);
			break;
		case 1:
			if (sinQuest_ChangeJob4.Monster[0] == sinQuest_ChangeJob4.Monster[1])
			{
				sinQuest_ChangeJob4.State = 2;
				sinCheckChangeJobQuest4();
				SetQuestBoard();
			}
			else
				cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath4[1]);
			break;
		case 2:
			if (cSkill.SearchContiueSkill(CHANGE_JOB3_QUEST))
			{
				cSkill.CancelContinueSkill(CHANGE_JOB3_QUEST);
				sinQuest_ChangeJob4.Monster[0] = 0;
				sinQuest_ChangeJob4.Monster[1] = 0;
				sinQuest_ChangeJob4.Kind = 0;
			}
			cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath4[2]);
			break;
		case 3:
			if (sinQuest_ChangeJob4.Monster[0] == sinQuest_ChangeJob4.Monster[1])
			{
				sinQuest_ChangeJob4.State = 4;
				sinCheckChangeJobQuest4();
				SetQuestBoard();
			}
			else
				cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath4[3]);
			break;
		case 4:
		case 7:
			if (cSkill.SearchContiueSkill(CHANGE_JOB3_QUEST))
			{
				cSkill.CancelContinueSkill(CHANGE_JOB3_QUEST);
				sinQuest_ChangeJob4.Monster[0] = 0;
				sinQuest_ChangeJob4.Monster[1] = 0;
				sinQuest_ChangeJob4.Kind = 0;
			}
			cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath4[4]);
			break;
		case 5:
			if (cInvenTory.SearchItemCode(sinQT1 | sin13))
			{
				sinQuest_ChangeJob4.State = 6;
				sinCheckChangeJobQuest4();
				SetQuestBoard();
			}
			else
				cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath4[5]);
		case 6:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath4[6]);
			break;
		case 8:
			cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath4[7]);
			break;
		}
	}
	return TRUE;
}

//…Ë÷√»ŒŒÒ ±º‰
int sinSetQuestTimer(DWORD dwCode, int UseTime, int CheckTime)
{
	sSKILL TempSkill;
	int Flag;
	memset(&TempSkill, 0, sizeof(sSKILL));

	char *Path = "image\\Sinimage\\skill\\keep\\QuestTimer.tga";
	if (!MatQuestTimer)
	{
		MatQuestTimer = CreateTextureMaterial(Path, 0, 0, 0, SMMAT_BLEND_ALPHA);
		ReadTextures();
	}

	TempSkill.CODE = CHANGE_JOB3_QUEST;

	if (UseTime == 0)
	{
		TempSkill.UseTime = 70 * 70;
		Flag = TRUE;
	}
	else
	{
		TempSkill.UseTime = UseTime;
		Flag = FALSE;
	}
	if (CheckTime)
		TempSkill.CheckTime = CheckTime;
	TempSkill.Point = 1;
	TempSkill.MatIcon = MatQuestTimer;
	sinContinueSkillSet(&TempSkill, Flag);
	sinPlaySound(SIN_SOUND_EAT_POTION2);

	Quest_Flag = dwCode;
	return TRUE;
}
int sinBattleNpcResult(int WinFlag)
{
	if (WinFlag)
	{
		sinQuest_ChangeJob4.State = 8;
		SetQuestBoard();
		cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath4[7]);
	}
	else
	{
		sinQuest_ChangeJob4.State = 4;
		SetQuestBoard();
	}
	return TRUE;
}
int sinCompleteChangeJob4(int Index)
{
	if (cSkill.SearchContiueSkill(CHANGE_JOB3_QUEST))
	{
		cSkill.CancelContinueSkill(CHANGE_JOB3_QUEST);
		sinQuest_ChangeJob4.Monster[0] = 0;
		sinQuest_ChangeJob4.Monster[1] = 0;
		sinQuest_ChangeJob4.Kind = 0;
	}
	switch (Index)
	{
	case 1:
		if (sinQuest_ChangeJob4.State == 8)
			break;
		sinQuest_ChangeJob4.CODE = SIN_QUEST_CODE_CHANGEJOB4;
		StartQuest_Code(sinQuest_ChangeJob4.CODE);

		cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath4[0]);
		sinQuest_ChangeJob4.State = 1;
		SetQuestBoard();
		sinChangeJob4MonSet(&sinQuest_ChangeJob4);
		SaveGameData();
		break;
	case 2:
		if (sinQuest_ChangeJob4.State == 8)
			break;
		sinQuest_ChangeJob4.CODE = SIN_QUEST_CODE_CHANGEJOB4;
		StartQuest_Code(sinQuest_ChangeJob4.CODE);

		sinQuest_ChangeJob4.State = 2;
		sinCheckChangeJobQuest4();
		SaveGameData();
		break;
	case 3:
		if (sinQuest_ChangeJob4.State == 8)
			break;
		sinQuest_ChangeJob4.CODE = SIN_QUEST_CODE_CHANGEJOB4;
		StartQuest_Code(sinQuest_ChangeJob4.CODE);

		sinQuest_ChangeJob4.State = 3;
		sinCheckChangeJobQuest4();
		SaveGameData();
		break;
	case 4:
		if (sinQuest_ChangeJob4.State == 8)
			break;
		sinQuest_ChangeJob4.CODE = SIN_QUEST_CODE_CHANGEJOB4;
		StartQuest_Code(sinQuest_ChangeJob4.CODE);

		cSinHelp.sinShowHelp(SIN_HELP_KIND_QUEST, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), QuestFilePath4[7]);
		sinQuest_ChangeJob4.State = 8;
		SetQuestBoard();
		SaveGameData();
		break;
	}
	return TRUE;
}
int CancelQuest()
{
	if (sinQuest_ChangeJob.CODE)
	{
		ZeroMemory(&sinQuest_ChangeJob, sizeof(sQUEST_CHANGEJOB));
		cSkill.CancelContinueSkill(CHANGE_JOB3_QUEST);
		if (cInvenTory.SearchItemCode(sinQT1 | sin01))
			DeleteQuestItem(sinQT1 | sin01);
		if (cInvenTory.SearchItemCode(sinQT1 | sin02))
			DeleteQuestItem(sinQT1 | sin02);
		if (cInvenTory.SearchItemCode(sinQT1 | sin03))
			DeleteQuestItem(sinQT1 | sin03);
	}
	if (sinQuest_ChangeJob2.CODE)
	{
		switch (sinQuest_ChangeJob2.CODE)
		{
		case SIN_QUEST_CODE_CHANGEJOB2_NPC_M:
			for (int i = 0; i < 9; i++)
			{
				if (cInvenTory.SearchItemCode(sinMA2 | sin01))
					DeleteQuestItem(sinMA2 | sin01);
			}
			if (cInvenTory.SearchItemCode(sinQT1 | sin04))
				DeleteQuestItem(sinQT1 | sin04);
			break;
		case SIN_QUEST_CODE_CHANGEJOB2_NPC_D:
			for (int i = 0; i < 7; i++)
			{
				if (cInvenTory.SearchItemCode(sinMA2 | sin02))
					DeleteQuestItem(sinMA2 | sin02);
			}
			if (cInvenTory.SearchItemCode(sinQT1 | sin05))
				DeleteQuestItem(sinQT1 | sin05);
			break;
		}
		if (cInvenTory.SearchItemCode(sinMA1 | sin01))
			DeleteQuestItem(sinMA1 | sin01);

		ZeroMemory(&sinQuest_ChangeJob2, sizeof(sQUEST_CHANGEJOB));
	}
	if (sinQuest_ChangeJob3.CODE)
	{
		for (int i = 0; i < 3; i++)
		{
			if (cInvenTory.SearchItemCode(sinQT1 | sin06))
				DeleteQuestItem(sinQT1 | sin06);
		}
		switch (sinChar->iClass)
		{
		case CHARACTERCLASS_Fighter:
			if (cInvenTory.SearchItemCode(0, ITEMCRAFTTYPE_QuestWeapon))
				DeleteQuestItem(sinWA1 | sin08, ITEMCRAFTTYPE_QuestWeapon);
			if (cInvenTory.SearchItemCode(sinOR2 | sin02))
				DeleteQuestItem(sinOR2 | sin02);
			break;
		case CHARACTERCLASS_Mechanician:
			if (cInvenTory.SearchItemCode(0, ITEMCRAFTTYPE_QuestWeapon))
				DeleteQuestItem(sinWC1 | sin08, ITEMCRAFTTYPE_QuestWeapon);
			if (cInvenTory.SearchItemCode(sinOR2 | sin02))
				DeleteQuestItem(sinOR2 | sin02);
			break;
		case CHARACTERCLASS_Archer:
			if (cInvenTory.SearchItemCode(0, ITEMCRAFTTYPE_QuestWeapon))
				DeleteQuestItem(sinWS1 | sin10, ITEMCRAFTTYPE_QuestWeapon);
			if (cInvenTory.SearchItemCode(sinOR2 | sin03))
				DeleteQuestItem(sinOR2 | sin03);
			break;
		case CHARACTERCLASS_Pikeman:
			if (cInvenTory.SearchItemCode(0, ITEMCRAFTTYPE_QuestWeapon))
				DeleteQuestItem(sinWP1 | sin09, ITEMCRAFTTYPE_QuestWeapon);
			if (cInvenTory.SearchItemCode(sinOR2 | sin02))
				DeleteQuestItem(sinOR2 | sin02);
			break;
		case CHARACTERCLASS_Atalanta:
			if (cInvenTory.SearchItemCode(0, ITEMCRAFTTYPE_QuestWeapon))
				DeleteQuestItem(sinWT1 | sin09, ITEMCRAFTTYPE_QuestWeapon);
			if (cInvenTory.SearchItemCode(sinOR2 | sin03))
				DeleteQuestItem(sinOR2 | sin03);
			break;
		case CHARACTERCLASS_Knight:
			if (cInvenTory.SearchItemCode(0, ITEMCRAFTTYPE_QuestWeapon))
				DeleteQuestItem(sinWS2 | sin10, ITEMCRAFTTYPE_QuestWeapon);
			if (cInvenTory.SearchItemCode(sinOR2 | sin02))
				DeleteQuestItem(sinOR2 | sin02);
			break;
		case CHARACTERCLASS_Magician:
		case CHARACTERCLASS_Priestess:
			if (cInvenTory.SearchItemCode(0, ITEMCRAFTTYPE_QuestWeapon))
				DeleteQuestItem(sinWM1 | sin09, ITEMCRAFTTYPE_QuestWeapon);
			if (cInvenTory.SearchItemCode(sinOR2 | sin04))
				DeleteQuestItem(sinOR2 | sin04);
			break;
		case CHARACTERCLASS_Assassin:
			if (cInvenTory.SearchItemCode(0, ITEMCRAFTTYPE_QuestWeapon))
				DeleteQuestItem(sinWD1 | sin09, ITEMCRAFTTYPE_QuestWeapon);
			if (cInvenTory.SearchItemCode(sinOR2 | sin03))
				DeleteQuestItem(sinOR2 | sin03);
			break;
		case CHARACTERCLASS_Shaman:
			if (cInvenTory.SearchItemCode(0, ITEMCRAFTTYPE_QuestWeapon))
				DeleteQuestItem(sinWN1 | sin09, ITEMCRAFTTYPE_QuestWeapon);
			if (cInvenTory.SearchItemCode(sinOR2 | sin04))
				DeleteQuestItem(sinOR2 | sin04);
			break;
		}
		ZeroMemory(&sinQuest_ChangeJob3, sizeof(sQUEST_CHANGEJOB3));
	}
	if (sinQuest_ChangeJob4.CODE)
	{
		if (cInvenTory.SearchItemCode(sinQT1 | sin13))
			DeleteQuestItem(sinQT1 | sin13);
		ZeroMemory(&sinQuest_ChangeJob4, sizeof(sQUEST_CHANGEJOB3));
		cSkill.CancelContinueSkill(CHANGE_JOB3_QUEST);
	}
	if (sinQuest_Level30.CODE)
	{
		ZeroMemory(&sinQuest_Level30, sizeof(sQUEST_CHANGEJOB3));
		cSkill.CancelContinueSkill(CHANGE_JOB3_QUEST);
	}
	if (sinQuest_Level55.CODE)
	{
		ZeroMemory(&sinQuest_Level55, sizeof(sQUEST_CHANGEJOB3));
		cSkill.CancelContinueSkill(CHANGE_JOB3_QUEST);
	}
	if (sinQuest_Level55_2.CODE)
	{
		ZeroMemory(&sinQuest_Level55_2, sizeof(sQUEST_CHANGEJOB3));
		cSkill.CancelContinueSkill(CHANGE_JOB3_QUEST);
	}
	if (sinQuest_Level70.CODE)
	{
		ZeroMemory(&sinQuest_Level70, sizeof(sQUEST_CHANGEJOB3));
		cSkill.CancelContinueSkill(CHANGE_JOB3_QUEST);
	}
	if (sinQuest_Level80.CODE)
	{
		ZeroMemory(&sinQuest_Level80, sizeof(sQUEST_CHANGEJOB3));
		cSkill.CancelContinueSkill(CHANGE_JOB3_QUEST);
	}
	if (sinQuest_Level80_2.CODE)
	{
		if (cInvenTory.SearchItemCode(sinQT1 | sin09))
			DeleteQuestItem(sinQT1 | sin09);
		if (cInvenTory.SearchItemCode(sinQT1 | sin10))
			DeleteQuestItem(sinQT1 | sin10);
		if (cInvenTory.SearchItemCode(sinQT1 | sin11))
			DeleteQuestItem(sinQT1 | sin11);
		if (cInvenTory.SearchItemCode(sinQT1 | sin12))
			DeleteQuestItem(sinQT1 | sin12);

		ZeroMemory(&sinQuest_Level80_2, sizeof(sQUEST_CHANGEJOB3));
		cSkill.CancelContinueSkill(CHANGE_JOB3_QUEST);
	}
	if (sinQuest_Level85.CODE)
	{
		if (cInvenTory.SearchItemCode(sinQT1 | sin08))
			DeleteQuestItem(sinQT1 | sin08);
		ZeroMemory(&sinQuest_Level85, sizeof(sQUEST_CHANGEJOB3));
		cSkill.CancelContinueSkill(CHANGE_JOB3_QUEST);
	}
	if (sinQuest_Level90.CODE)
	{
		ZeroMemory(&sinQuest_Level90, sizeof(sQUEST_CHANGEJOB3));
		cSkill.CancelContinueSkill(CHANGE_JOB3_QUEST);
	}
	if (sinQuest_Level90_2.CODE)
	{
		ZeroMemory(&sinQuest_Level90_2, sizeof(sQUEST_CHANGEJOB3));
		cSkill.CancelContinueSkill(CHANGE_JOB3_QUEST);
		cInvenTory.SetItemToChar();
	}
	chaQuest.CancelQuest();
	return TRUE;
}